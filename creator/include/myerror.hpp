#pragma once

#include <string>

class MySQLError {
public:
	MySQLError();

	const int get_code() const { return code; }
	const std::string get_message() const { return message; }
	const std::string get_sqlstate() const { return sqlstate; }

private:
	int code;
	std::string message, sqlstate;
};
