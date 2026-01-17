#pragma once
#include "common.h"
class InventoryItemMenu
{
private:
	std::string menu_item_id;
	std::string inventory_item_id;
	float quantity_required;
	std::string unit;
	int serving_size;
public:
	void createRequirement(std::string item_id, std::string inventory_id, float quantity, std::string unit, int serving_size);
	std::string updateRequirement(float quantity);
	std::string getIngredientDetail();
	bool checkAvailability(int quantity);
};