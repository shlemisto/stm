#include "stm.h"

char *label(const char *label)
{
	size_t len = strlen(label);
	char *l;

	if (len > MAX_LABEL_LEN) {
		printf("truncate %s to %-25s\n", label, label);
		len = MAX_LABEL_LEN;
	}

	l = malloc(len + 1);
	if (!l)
		return NULL;

	strncpy(l, label, len);
	l[len] = 0;

	return l;
}

static struct menu_subinfo *__get_menu_subinfo(struct menu *m, int size)
{
	int i, parent;
	u8 level,
	   max_level = 0;
	struct menu_subinfo *subinfo;
	u8 *option_number;

	subinfo = malloc(sizeof(struct menu_subinfo) * size);
	if (!subinfo)
		return NULL;
	memset(subinfo, 0, sizeof(struct menu_subinfo) * size);

	// find menu's depth
	for (i = 0; i < size; ++i) {
		if (m[i].level > max_level)
			++max_level;
	}

	if (max_level)
		++max_level;

	option_number = malloc(max_level);
	if (!option_number) {
		free(subinfo);
		return NULL;
	}

	memset(option_number, 0, max_level);

	// fill subinfo structure
	for (i = 0; i < size; ++i) {
		for (level = 0; level < max_level; ++level) {
			if (m[i].level == level) {
				// update option_number for a new level#0 menu
				// and reset it for its submenu
				if (level == 0) {
					u8 last_option_number = option_number[0];
					memset(option_number, 0, max_level);
					option_number[0] = last_option_number;
				}

				// find a parent of menu
				for (parent = i; parent > 0; --parent) {
					if (m[parent].level + 1 == m[i].level) {
						subinfo[i].parent = parent - 1;
						break;
					}
				}

				// this value correspond to user choice
				subinfo[i].option_number = ++option_number[level];
			}
		}
	}

	free(option_number);

	return subinfo;
}


int show_menu(struct menu *m, int menu_len)
{
	u8 current_level = 0,
	   choice;
	char read_buf[2+1];
	int i,
	    option_number,
	    submenu,
	    current_menu = 0;
	bool submenu_end = false,
	     is_running = true;
	struct menu_subinfo *subinfo;

	subinfo = __get_menu_subinfo(m, menu_len);
	if (!subinfo)
		return -ENOMEM;

	while (is_running) {
		system("clear");

		printf("+-------------------------------+\n");
		// print menu
		for (i = current_menu, option_number = 0; i < menu_len; ++i) {
			if (m[i].level == current_level) {
				if (current_level == 0) {
					++option_number;
					if (m[i].label)
						printf("| %2d: %-25s |\n", option_number, m[i].label);
					else
						printf("| %2d: %-25s |\n", option_number, "NULL");
				} else {
					// find submenu only for this option
					submenu_end = false;
					for (submenu = i; submenu < menu_len; ++submenu) {
						if (m[submenu].level > current_level)
							continue;
						else if (m[submenu].level < current_level) {
							submenu_end = true;
							break;
						}

						++option_number;
						if (m[submenu].label)
							printf("| %2d: %-25s |\n", option_number, m[submenu].label);
						else
							printf("| %2d: %-25s |\n", option_number, "NULL");
					}

					if (submenu_end || submenu == menu_len)
						break;
				}
			}
		}
		printf("+-------------------------------+\n");

		printf("> ");
		fflush(stdin);
		scanf("%2s", read_buf);
		choice = atoi(read_buf);

		// convert user choice to menu
		for (i = current_menu; i < menu_len; ++i) {
			if ((m[i].level == current_level) && (subinfo[i].option_number == choice)) {
				if (m[i].options & EXIT) {
					if (current_level) {
						--current_level;
						if (current_level)
							current_menu = subinfo[i].parent;
						else
							current_menu = 0;
					} else
						is_running = false;
				} else {
					if (m[i].options & HAVE_SUBMENU) {
						++current_level;
						current_menu = i + 1;
					}

					if (m[i].action)
						m[i].action();
				}

				break;
			}
		}
	}

	// execute only at level#0
	if (m[i].action)
		m[i].action();

	free(subinfo);

	for (i = 0; i < menu_len; ++i)
		free(m[i].label);

	return 0;
}
