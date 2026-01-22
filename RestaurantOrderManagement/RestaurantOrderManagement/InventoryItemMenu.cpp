#include "InventoryItemMenu.h"
#include "Database.h"

void InventoryItemMenu::createRequirement(std::string item_id, std::string inventory_id, float quantity, std::string unit, int serving_size)
{
	auto& db = Database::getDB();
    auto stmt = db.prepare(
        "INSERT INTO InventoryItemMenu "
        "(item_id, inventory_id, quantity_required, unit, serving_size) "
        "VALUES (?, ?, ?, ?, ?)"
    );
    stmt->setString(1, item_id);
    stmt->setString(2, inventory_id);
    stmt->setDouble(3, quantity);
    stmt->setString(4, unit);
    stmt->setInt(5, serving_size);
    int affected = stmt->executeUpdate();
    if (affected != 1) {
        throw std::runtime_error("Create requirement: failed");
    }
}

std::string InventoryItemMenu::updateRequirement(float quantity)
{
    auto& db = Database::getDB();
    auto stmt = db.prepare("Update InventoryItemMenu set quantity = ? where item_id = ? and inventory_id = ?");
    stmt->setDouble(1, quantity);
    stmt->setString(2, this->menu_item_id);
    stmt->setString(3, this->inventory_item_id);
    int affected = stmt->executeUpdate();
    if (affected != 1) {
        throw std::runtime_error("Update requirement failed");
    }
}

bool InventoryItemMenu::checkAvailability(int order_quantity)
{
    auto& db = Database::getDB();

    auto stmt = db.prepare(
        "SELECT iim.quantity_required, iim.serving_size, inv.quantity "
        "FROM InventoryItemMenu iim "
        "JOIN InventoryItem inv ON iim.inventory_id = inv.inventory_id "
        "WHERE iim.item_id = ?"
    );

    stmt->setString(1, this->menu_item_id);
    auto rs = stmt->executeQuery();

    while (rs->next()) {
        float required = rs->getDouble("quantity_required");
        int serving = rs->getInt("serving_size");
        float stock = rs->getDouble("quantity");

        float need = (required / serving) * order_quantity;

        if (stock < need) {
            return false;
        }
    }
    return true;
}

std::string InventoryItemMenu::getIngredientDetail()
{
    auto& db = Database::getDB();
    auto stmt = db.prepare(
        "SELECT inv.item_name, iim.quantity_required, iim.unit, iim.serving_size "
        "FROM InventoryItemMenu iim "
        "JOIN InventoryItem inv ON iim.inventory_id = inv.inventory_id "
        "WHERE iim.menu_item_id = ?"
    );

    stmt->setString(1, this->menu_item_id);
    auto rs = stmt->executeQuery();

    std::ostringstream oss;
    oss << "Dish recipe:\n";

    while (rs->next()) {
        oss << "- " << rs->getString("item_name")
            << ": " << rs->getDouble("quantity_required")
            << " " << rs->getString("unit")
            << " / " << rs->getInt("serving_size")
            << " phan\n";
    }

    return oss.str();
}

