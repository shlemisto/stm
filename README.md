# What is STM?
STM is a simple text menu libary written in C.

It allows to easily create text-based menu interface.

# How do I use it?

It's very easy.

Firstly create menu structure by filling an array:

	struct menu menu_example[] = {
		{ -1, NO_LABEL, ACTION2(main_title) },

		{ 0, label("Create file"), NO_ACTION, HAS_SUBMENU },
		  { 1, label("Are you sure?"), ACTION1(create_file) },
		  { 1, label("Back"), NO_ACTION, EXIT },

		{ 0, label("Delete file"), NO_ACTION, HAS_SUBMENU },
		  { 1, label("Are you sure?"), ACTION1(delete_file) },
		  { 1, label("Back"), NO_ACTION, EXIT },
		
		{ 0, label("ls $pwd"), ACTION1(ls) },
		
		{ 0, label("We need to go deeper [0]"), NO_ACTION, HAS_SUBMENU },
		  { 1, label("And Deeper [1]"), ACTION2(and_deeper), HAS_SUBMENU },
		    { 2, label("And Deeper [2]"), NO_ACTION, HAS_SUBMENU },
		      { 3, label("And Deeper [3]"), ACTION12(stop_it, and_deeper), HAS_SUBMENU },
		        { 4, label("And Deeper [4]"), ACTION1(stop_it) },
		        { 4, label("Exit"), NO_ACTION, EXIT },
		      { 3, label("Exit"), NO_ACTION, EXIT },
		    { 2, label("Exit"), NO_ACTION, EXIT },
		  { 1, label("Exit"), NO_ACTION, EXIT },

		{ 0, label("Exit"), NO_ACTION, EXIT }
	};
	
  Where each entry have format:
  
  	{ level, label (truncate to 25), action, some options (EXIT or HAS_SUBMENU) }
	
  To show menu just call `show_menu`:
    
    show_menu(&menu_example[0], ARRAY_SIZE(menu_example))
    
  Example output (from `example/example.c`):
  
		    stm example
	+-------------------------------+
	|  1: Create file               |
	|  2: Delete file               |
	|  3: ls $pwd                   |
	|  4: We need to go deeper [0]  |
	|  5: Exit                      |
	+-------------------------------+
	> 


  Use digit keys then Enter to navigate through the menu.
    
