#pragma once
#include "Invoice.h"
#include "Staff.h"

class Cashier: public Staff
{
public:
	Cashier(const std::string& id, const std::string& name, const std::string& password,
		const std::string& phone);
	std::vector<Order> viewCompletedOrders();
	void ProcessPayment(Order order,Invoice invoice);
};