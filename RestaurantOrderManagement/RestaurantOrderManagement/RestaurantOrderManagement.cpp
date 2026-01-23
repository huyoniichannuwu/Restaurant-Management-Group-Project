#include "MainMenu.h"
#pragma once
int main()
{
    bool logging_screen = true;
	do
	{
		char choice_logging_screen;
		std::vector<MenuItem> menu_list;
		menu_list = MenuItem::getAllMenuItems();
		loginScreen();
		std::cout << "Please enter your choice: "; std::cin >> choice_logging_screen;
		if (choice_logging_screen == '1')
		{
			bool customer_screen = true;
			do
			{
				printMenu(menu_list);
			} while (customer_screen == true);
		}
		else if(choice_logging_screen == '3')
		{
			logging_screen = false;
		}
		
		

	} while (logging_screen == true);
	return 0;
}
