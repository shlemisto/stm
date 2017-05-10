#ifndef __MENULIB_H
#define __MENULIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef u8
#define u8  unsigned char
#define u16 unsigned short
#define u32 unsigned int
#endif

#define BIT(b) (1 << (b))

#define MAX_LABEL_LEN 25

enum MENU_OPTIONS {
	EXIT = BIT(0),
	HAVE_SUBMENU = BIT(1)
};

/*
 * @level - menu entry level
 * @label - menu entry label
 *   !!! we truncate too long string to MAX_LABEL_LEN
 * @action - menu entry payload function
 * @options - some options
 *
 */
struct menu {
	u8 level;
	char *label;
	void (*action)();
	u8 options;
};

/*
 * @parent - parent of meny entry
 * @option_number - this value corresponds to user choice
 *
 */
struct menu_subinfo {
	u16 parent;
	u8 option_number;
};

char *label(const char *label);
int show_menu(struct menu *m, int menu_len);

#ifdef __cplusplus
}
#endif

#endif
