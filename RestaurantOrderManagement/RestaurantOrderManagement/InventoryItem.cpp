#include "InventoryItem.h"
#include "Database.h"

InventoryItem::InventoryItem(const std::string& inventory_id) :
    inventory_id(inventory_id){}


void InventoryItem::deductQuantity(float amount)
{
    if (amount <= 0) {
        throw std::invalid_argument("Amount must be positive");
    }

    auto& db = Database::getDB();
    auto stmt = db.prepare(
        "UPDATE InventoryItem "
        "SET quantity = quantity - ? "
        "WHERE inventory_id = ? AND quantity >= ?"
    );

    stmt->setDouble(1, amount);
    stmt->setString(2, this->inventory_id);
    stmt->setDouble(3, amount);

    int affected = stmt->executeUpdate();
    if (affected != 1) {
        throw std::runtime_error("Not enough inventory or inventory not found");
    }
}

bool InventoryItem::exists(const std::string& inventory_id)
{
    auto& db = Database::getDB();
    auto stmt = db.prepare(
        "SELECT 1 FROM InventoryItem WHERE inventory_id = ? LIMIT 1"
    );
    stmt->setString(1, inventory_id);

    auto rs = stmt->executeQuery();
    return rs->next();
}

