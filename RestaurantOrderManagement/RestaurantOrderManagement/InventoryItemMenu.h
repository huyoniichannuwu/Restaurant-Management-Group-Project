#pragma once
#include "common.h"
#include "InventoryItem.h"
class InventoryItemMenu
{
private:
	std::string menu_item_id;
public:
	InventoryItemMenu(const std::string& menu_item_id);

	static void createRequirement(std::string item_id, std::string inventory_id, float quantity, std::string unit, int serving_size);
	static void updateRequirement(const std::string& menu_item_id, const std::string& inventory_item_id, float quantity_required);


	static bool hasRequirement(const std::string& item_id);

	std::string getIngredientDetail();
	bool checkAvailability(int quantity);
	void deduct(int order_quantity);

};