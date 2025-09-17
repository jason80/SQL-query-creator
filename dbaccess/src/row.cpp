#include <row.hpp>

Row::Row(char **mysql_row, std::unordered_map<std::string, unsigned> &fields) :
		mysql_row{mysql_row}, fields{fields} {}

const std::string Row::get_string(const std::string field_name) const {
	if (!mysql_row[fields[field_name]]) return "NULL";
	return mysql_row[fields[field_name]];
}

const std::string Row::get_string(const unsigned field_id) const {
	if (!mysql_row[field_id]) return "NULL";
	return mysql_row[field_id];
}

const unsigned Row::get_unsigned(const std::string field_name) const {
	return get_unsigned(fields[field_name]);
}

const unsigned Row::get_unsigned(const unsigned field_id) const {
	return unsigned(std::stoul(mysql_row[field_id]));
}

const signed Row::get_signed(const std::string field_name) const {
	return get_signed(fields[field_name]);
}

const signed Row::get_signed(const unsigned field_id) const {
	return std::stoul(mysql_row[field_id]);
}
