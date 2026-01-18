#include "KitchenStaff.h"
#include "Database.h"


KitchenStaff::KitchenStaff(const std::string& id, const std::string& name,
	const std::string& password, const std::string& phone) :
	Staff(id, name, password, phone, "KitchenStaff")
{
}

std::vector<std::vector<Order>> KitchenStaff::viewPendingOrders()
{
	Database db;
	std::vector<std::vector<Order>> order_list;
	//tr? v? 1 resultset, r?i chuy?n sang vector
	auto stmt = db.select("Select * from OrderTable where order_status = 'PENDING' or order_status = 'PREPARING' or order_status = 'READY'")
}