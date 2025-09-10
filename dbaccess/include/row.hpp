#pragma once

#include <memory.h>
#include <unordered_map>
#include <string>

class Row {
public:
	Row(char **mysql_row, std::unordered_map<std::string, unsigned> &fields);

	const std::string get_string(const std::string field_name) const;
	const std::string get_string(const unsigned field_id) const;

	const unsigned get_unsigned(const std::string field_name) const;
	const unsigned get_unsigned(const unsigned field_id) const;

	const signed get_signed(const std::string field_name) const;
	const signed get_signed(const unsigned field_id) const;

private:
	char **mysql_row;
	std::unordered_map<std::string, unsigned> &fields;
};
