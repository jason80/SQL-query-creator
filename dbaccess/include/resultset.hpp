#pragma once

#include <memory>
#include <unordered_map>
#include <string>

class MYSQL_RES;
class Row;

class ResultSet {
public:
	ResultSet();
	virtual ~ResultSet();

	std::shared_ptr<Row> fetch_row();

private:
	MYSQL_RES *res;
	std::unordered_map<std::string, unsigned> fields;
};
