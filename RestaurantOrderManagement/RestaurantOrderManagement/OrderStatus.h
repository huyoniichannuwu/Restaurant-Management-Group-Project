#pragma once
#include "common.h"

enum class OrderStatus
{
	CREATED,
	PENDING,
	PREPARING,
	READY,
	COMPLETED,
	CANCELLED
};

//map enum c++ sang mysql
std::string enumToString(const OrderStatus& status);

//map mysql sang enum c++
OrderStatus stringToEnum(const std::string& str);