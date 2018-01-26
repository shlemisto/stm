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
#define MENU_BORDER "+-------------------------------+"
#define MENU_BORDER_LEN 33

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))
#endif

#define NO_LABEL NULL
#define NO_ACTION { NULL, NULL }
#define ACTION1(a) { a, NULL }
#define ACTION2(a) { NULL, a }
#define ACTION12(a,b) { a, b }

enum MENU_OPTIONS {
	EXIT = BIT(0),
	HAS_SUBMENU = BIT(1)
};

/*
 * @level - menu entry level
 * @label - menu entry label
 *   !!! we truncate too long string to MAX_LABEL_LEN
 * @action - menu entry payload function[0], menu label [1]
 * @options - some options
 * @title - menu title
 *
 */
struct menu {
	u8 level;
	char *label;
	void (*action[2])();
	u8 options;
	char *title;
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
void show_menu_title(char *title, int len);

#ifdef __cplusplus
}
#endif

#endif
