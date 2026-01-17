#pragma once
#include "Order.h"
#include "Staff.h"

class KitchenStaff:public Staff
{
public:
	std::vector<std::vector<Order>> viewPendingOrders(); // return a list with pending, preparing and ready status
};