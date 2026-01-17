#include "Order.h"
#pragma once

enum class PaymentStatus
{
	PENDING,
	PAID,
	REFUNDED
};

class Invoice
{
private:
	int invoice_id;
	int order_id;
	std::chrono::system_clock::time_point issue_date;
	PaymentStatus payment_status;
	float total_price;
public:
	static Invoice generate(const Order& order);
	float calculateTotal(Order order);
	float calculateTotalSales();
	void markPaid();
	void markRefunded();
};
