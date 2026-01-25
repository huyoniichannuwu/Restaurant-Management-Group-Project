#include "InventoryItemMenu.h"
#include "Database.h"


InventoryItemMenu::InventoryItemMenu(const std::string& menu_item_id) :
    menu_item_id(menu_item_id){}


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

void InventoryItemMenu::updateRequirement(const std::string& menu_item_id, const std::string& inventory_item_id, float quantity_required)
{
    auto& db = Database::getDB();
    auto stmt = db.prepare("Update InventoryItemMenu set quantity_required = ? where item_id = ? and inventory_id = ?");
    stmt->setDouble(1, quantity_required);
    stmt->setString(2, menu_item_id);
    stmt->setString(3, inventory_item_id);
    int affected = stmt->executeUpdate();
    if (affected != 1) {
        throw std::runtime_error("Update requirement failed");
    }
}


bool InventoryItemMenu::hasRequirement(const std::string& item_id)
{
    auto& db = Database::getDB();
    auto stmt = db.prepare(
        "SELECT 1 FROM InventoryItemMenu WHERE item_id = ? LIMIT 1"
    );
    stmt->setString(1, item_id);

    auto rs = stmt->executeQuery();
    return rs->next();
}






bool InventoryItemMenu::checkAvailability(int quantity)
{
    auto& db = Database::getDB();

    auto stmt = db.prepare(
        "SELECT quantity_required, serving_size, inv.quantity "
        "FROM InventoryItemMenu iim "
        "JOIN InventoryItem inv ON iim.inventory_id = inv.inventory_id "
        "WHERE iim.item_id = ?"
    );

    stmt->setString(1, menu_item_id);
    auto rs = stmt->executeQuery();

    //check if the ingredient is enough for the customer
    while (rs->next())
    {
        float need =
            (rs->getDouble("quantity_required") / rs->getInt("serving_size"))
            * quantity;

        if (rs->getDouble("quantity") < need)
            return false;
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
        "WHERE iim.item_id = ?"
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

void InventoryItemMenu::deduct(int order_quantity)
{
    auto& db = Database::getDB();
    auto stmt = db.prepare(
        "SELECT inventory_id, quantity_required, serving_size "
        "FROM InventoryItemMenu WHERE item_id = ?"
    );

    stmt->setString(1, menu_item_id);
    auto rs = stmt->executeQuery();

    while (rs->next())
    {
        float need = (rs->getDouble("quantity_required") / rs->getInt("serving_size")) * order_quantity;

        InventoryItem inv(rs->getString("inventory_id"));
        inv.deductQuantity(need);
    }
}
