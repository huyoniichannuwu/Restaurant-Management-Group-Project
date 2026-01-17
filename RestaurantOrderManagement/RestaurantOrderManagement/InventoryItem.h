#pragma once
#include "common.h"

class InventoryItem
{
private:
	std::string inventory_id;
	std::string item_name;
	float quantity;
	std::string unit;
public:
	void deductQuantity(float amount);
};