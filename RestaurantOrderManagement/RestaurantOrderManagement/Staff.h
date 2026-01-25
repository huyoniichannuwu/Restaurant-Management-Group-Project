#pragma once
#include "common.h"
class Staff
{
private:
	std::string staff_id;
	std::string staff_name;
	std::string password;
	std::string phone;
	std::string role;
public:
	Staff(const std::string& staff_id,const std::string& staff_name,const std::string& password,const std::string& phone,const std::string& role);
	~Staff() = default;
	std::string getName() const;
	std::string getId() const;
	std::string getPhone() const;
	std::string getPassword() const;
	//kiem tra lai login
	static std::optional<Staff> login(const std::string& staff_id,const std::string& hashed_password);
	static std::vector<Staff> getAllStaff();//return staff list for manager later
	std::string getRole() const;
};

