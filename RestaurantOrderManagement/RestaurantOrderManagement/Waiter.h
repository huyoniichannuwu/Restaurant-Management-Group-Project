#pragma once
#include "Order.h"

class Waiter: public Staff
{
public:
	Waiter(const std::string& id, const std::string& name,
		const std::string& password, const std::string& phone);
	Order createOrder(int table_number, std::string customer_name, std::string note);
	std::vector<Order> viewActiveOrder(); //return list of order which status is not COMPLETED,PAID,CANCELLED
};