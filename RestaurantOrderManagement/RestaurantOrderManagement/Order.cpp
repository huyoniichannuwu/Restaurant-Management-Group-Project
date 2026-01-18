#include"Order.h"
#include"Database.h"

Database db;

Order::Order(const int order_id,const int table_number,const std::chrono::system_clock::time_point& order_time,const OrderStatus status,
	const float total_amount,const std::string& note,const std::string& customer_name):
	order_id(order_id), table_number(table_number), order_time(order_time), status(status),
	total_amount(total_amount), note(note), customer_name(customer_name)
{
}

int Order::getOrderId() const
{
	return this->order_id;
}
int Order::getTableNumber() const
{
	return this->table_number;
}
std::chrono::system_clock::time_point Order::getOrderTime() const
{
	return this->order_time;
}
OrderStatus Order::getStatus() const
{
	return this->status;
}


void Order::cancel()
{
	if (this->status == OrderStatus::COMPLETED || this->status == OrderStatus::PREPARING || this->status == OrderStatus::READY)
	{
		throw std::logic_error("Order already cooked, can't cancel");
	}
	this->status = OrderStatus::CANCELLED;
}
void Order::sendToKitchen()
{
	this->status = OrderStatus::PENDING;
	auto& db = Database::getDB();
	std::string mysql_status = enumToString(this->status);
	auto stmt = db.prepare("Update OrderTable set order_status = ? where order_id = ?");
	stmt->setString(1, mysql_status);
	stmt->setInt(2, this->order_id);
	stmt->execute(); delete stmt;
}
void Order::markPreparing()
{
	this->status = OrderStatus::PREPARING;
	auto& db = Database::getDB();
	std::string mysql_status = enumToString(this->status);
	auto stmt = db.prepare("Update OrderTable set order_status = ? where order_id = ?");
	stmt->setString(1, mysql_status);
	stmt->setInt(2, this->order_id);
	stmt->execute(); delete stmt;
}
void Order::markReady()
{
	this->status = OrderStatus::READY;
	auto& db = Database::getDB();
	std::string mysql_status = enumToString(this->status);
	auto stmt = db.prepare("Update OrderTable set order_status = ? where order_id = ?");
	stmt->setString(1, mysql_status);
	stmt->setInt(2, this->order_id);
	stmt->execute(); delete stmt;
}
void Order::markCompleted()
{
	this->status = OrderStatus::COMPLETED;
	auto& db = Database::getDB();
	std::string mysql_status = enumToString(this->status);
	auto stmt = db.prepare("Update OrderTable set order_status = ? where order_id = ?");
	stmt->setString(1, mysql_status);
	stmt->setInt(2, this->order_id);
	stmt->execute(); delete stmt;
}