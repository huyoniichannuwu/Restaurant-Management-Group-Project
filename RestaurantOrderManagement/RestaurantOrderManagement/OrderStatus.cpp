#include "OrderStatus.h"

//map enum c++ sang mysql
std::string enumToString(const OrderStatus& status)
{
	switch (status)
	{
	case OrderStatus::CREATED: return "CREATED";
	case OrderStatus::PENDING:   return "PENDING";
	case OrderStatus::PREPARING: return "PREPARING";
	case OrderStatus::READY:     return "READY";
	case OrderStatus::COMPLETED: return "COMPLETED";
	case OrderStatus::CANCELLED: return "CANCELLED";
	}
	return "CREATED"; // fallback
}

//map mysql sang enum c++
OrderStatus stringToEnum(const std::string& str)
{
	if (str == "CREATED")   return OrderStatus::CREATED;
	if (str == "PENDING")   return OrderStatus::PENDING;
	if (str == "PREPARING") return OrderStatus::PREPARING;
	if (str == "READY")     return OrderStatus::READY;
	if (str == "COMPLETED") return OrderStatus::COMPLETED;
	if (str == "CANCELLED") return OrderStatus::CANCELLED;

	throw std::invalid_argument("Unknown OrderStatus: " + str);
}
