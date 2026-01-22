#include "MainMenu.h"

void printLine(char c, const int width = 75)
{
	std::cout << std::string(width, c) << std::endl;
}



void printMenu(std::vector<MenuItem> menu_list)
{
	printLine('-');

}

void loginScreen()
{
	printLine('=');
	std::cout << "SON TUNG ATM RESTAURANT" << std::endl;
	printLine('=');
	std::cout << "1.Customer" << std::endl;
	std::cout << "2.Staff" << std::endl;
	std::cout << "3.Exit" << std::endl;
	printLine('-');
}

//void printOrderMenu(std::vector<Order> order_list);
//void printOrderItemList(std::vector<OrderItem> order_item_list);
//void printOrder(Order order);
//void printStaff(std::vector<Staff> staff_list);