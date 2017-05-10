# What is STM?
STM is a simple text menu libary written in C.

It allows to easily create text-based menu interface.

# How do I use it?

It's very easy.

Firstly create menu structure by filling array:

	struct menu menu_example[] = {
		{ 0, label("Create file"), NULL, HAVE_SUBMENU },
		  { 1, label("Are you sure?"), create_file },
		  { 1, label("Back"), NULL, EXIT },

		{ 0, label("Delete file"), NULL, HAVE_SUBMENU },
		  { 1, label("Are you sure?"), delete_file },
		  { 1, label("Back"), NULL, EXIT },
		
		{ 0, label("ls $pwd"), ls },
		
		{ 0, label("We need to go deeper [0]"), NULL, HAVE_SUBMENU },
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
	
  Where each entry have format:
  
  	{ level, label (truncate to 25), action, some options (EXIT or HAVE_SUBMENU) }
	
  To show menu just call `show_menu`:
    
    show_menu(&menu_example[0], ARRAY_SIZE(menu_example))
    
  Example output (from `example/example.c`):
  
    +-------------------------------+
    |  1: Create file               |
    |  2: Delete file               |
    |  3: ls $pwd                   |
    |  4: We need to go deeper [0]  |
    |  5: Exit                      |
    +-------------------------------+
    > 

  Use digit keys then Enter to navigate through the menu.
    
