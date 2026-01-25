#pragma once
#include "common.h"

class InventoryItem
{
private:
	std::string inventory_id;
public:
	InventoryItem(const std::string& inventory_id);
	void deductQuantity(float amount);
	static bool exists(const std::string& inventory_id);
};