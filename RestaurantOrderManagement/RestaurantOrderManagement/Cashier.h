#pragma once
#include "Invoice.h"
#include "Staff.h"

class Cashier: public Staff
{
public:
	std::vector<std::vector<Order>> viewCompletedOrders();
	void ProcessPayment(Invoice invoice);
};