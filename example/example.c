#include <stdio.h>
#include <stdlib.h>
#include <stm.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

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

int main(void)
{
	int err = 0;

	struct menu menu_example[] = {
		{ 0, label("Create file"), NULL, HAVE_SUBMENU, label("Create your super file") },
		  { 1, label("Are you sure?"), create_file },
		  { 1, label("Back"), NULL, EXIT },

		{ 0, label("Delete file"), NULL, HAVE_SUBMENU },
		  { 1, label("Are you sure?"), delete_file },
		  { 1, label("Back"), NULL, EXIT },
		
		{ 0, label("ls $pwd"), ls },
		
		{ 0, label("We need to go deeper [0]"), NULL, HAVE_SUBMENU,
			label("want more and more") },
		  { 1, label("And Deeper [1]"), NULL, HAVE_SUBMENU },
		    { 2, label("And Deeper [2]"), NULL, HAVE_SUBMENU },
		      { 3, label("And Deeper [3]"), stop_it, HAVE_SUBMENU },
		        { 4, label("And Deeper [4]"), stop_it },
		        { 4, label("Exit"), NULL, EXIT },
		      { 3, label("Exit"), NULL, EXIT },
		    { 2, label("Exit"), NULL, EXIT },
		  { 1, label("Exit"), NULL, EXIT },

		{ 0, label("Exit"), NULL, EXIT }
	};

	err = show_menu(&menu_example[0], ARRAY_SIZE(menu_example));

	return err;
}
