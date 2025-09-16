#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <vector>

#include <mysql/mysql.h>

class Row;

class ResultSet {
public:
	ResultSet();
	virtual ~ResultSet();

	std::shared_ptr<Row> fetch_row();
	std::vector<std::string> get_field_names() const { return field_names; }
	const unsigned field_count() const { return field_names.size(); }

private:
	MYSQL_RES *res;
	std::unordered_map<std::string, unsigned> fields;
	std::vector<std::string> field_names;
};
