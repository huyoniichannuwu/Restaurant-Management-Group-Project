#include "MenuItem.h"
#pragma once

class OrderItem
{
private:
	std::string order_item_id;
	int quantity;
	float price;
	static std::string generateId() {
		static int counter = 0;
		return "OI_" + std::to_string(++counter);
	}
public:
	OrderItem(const std::string& order_item_id,const int quantity,const float price);
	float calculateCost();
};