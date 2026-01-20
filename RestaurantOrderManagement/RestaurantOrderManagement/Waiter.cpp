#include"Waiter.h"
#include"Database.h"

Waiter::Waiter(const std::string& id, const std::string& name,
	const std::string& password, const std::string& phone) :
	Staff(id, name, password, phone, "Waiter")
{
}


Order Waiter::createOrder(int table_number, std::string customer_name, std::string note)
{
	Order order = Order::create(table_number, note, customer_name);
	auto& db = Database::getDB();
	auto stmt = db.prepare(
		"Insert into OrderTable (table_number,customer_name,note,order_status,total_amount,order_time)"
		"values (?,?,?,?,?,now())"
	);
	stmt->setInt(1, table_number);
	stmt->setString(2, customer_name);
	stmt->setString(3, note);
	stmt->setString(4, enumToString(order.getStatus()));
	stmt->setDouble(5, 0.0);
	stmt->execute();


	int order_id = db.getLastInsertOrderId();
	order.setOrderId(order_id);
	return order;
}