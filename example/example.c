#include <stdio.h>
#include <stdlib.h>
#include <stm.h>

void create_file()
{
	char filename[51] = { 0 };

	printf("Enter a filename to crete:\n");
	scanf("%50s", filename);

	// ...
	
	printf("file %s created successfully\n", filename);
	getchar();
	getchar();
}

void delete_file()
{
	char filename[51] = { 0 };

	printf("Enter a filename to delete:\n");
	scanf("%50s", filename);

	// ...
	
	printf("file %s deleted successfully\n", filename);
	getchar();
	getchar();
}

void ls()
{
	system("ls");

	getchar();
	getchar();
}

void stop_it()
{
	printf("!!! stop it !!!\n");
	getchar();
	getchar();
}

void and_deeper()
{
	char *title = "And deeper";
	show_menu_title(title, strlen(title));
}

void main_title()
{
	char *title = "\x1b[31m" "stm example" "\x1b[0m";
	show_menu_title(title, strlen(title) + 11);
}

int main(void)
{
	int err = 0;

	struct menu menu_example[] = {
		{ -1, NO_LABEL, ACTION2(main_title) },

		{ 0, label("Create file"), NO_ACTION, HAVE_SUBMENU },
		  { 1, label("Are you sure?"), ACTION1(create_file) },
		  { 1, label("Back"), NO_ACTION, EXIT },

		{ 0, label("Delete file"), NO_ACTION, HAVE_SUBMENU },
		  { 1, label("Are you sure?"), ACTION1(delete_file) },
		  { 1, label("Back"), NO_ACTION, EXIT },
		
		{ 0, label("ls $pwd"), ACTION1(ls) },
		
		{ 0, label("We need to go deeper [0]"), NO_ACTION, HAVE_SUBMENU },
		  { 1, label("And Deeper [1]"), ACTION2(and_deeper), HAVE_SUBMENU },
		    { 2, label("And Deeper [2]"), NO_ACTION, HAVE_SUBMENU },
		      { 3, label("And Deeper [3]"), ACTION12(stop_it, and_deeper), HAVE_SUBMENU },
		        { 4, label("And Deeper [4]"), ACTION1(stop_it) },
		        { 4, label("Exit"), NO_ACTION, EXIT },
		      { 3, label("Exit"), NO_ACTION, EXIT },
		    { 2, label("Exit"), NO_ACTION, EXIT },
		  { 1, label("Exit"), NO_ACTION, EXIT },

		{ 0, label("Exit"), NO_ACTION, EXIT }
	};

	err = show_menu(&menu_example[0], ARRAY_SIZE(menu_example));

	return err;
}
