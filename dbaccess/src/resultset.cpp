#include <resultset.hpp>

#include <mysql/mysql.h>

#include <connection.hpp>
#include <row.hpp>

ResultSet::ResultSet() {
	res = mysql_store_result(Connection::connection);

	if (res) {

		auto _fields = mysql_fetch_fields(res);

		// Store field names
		for (unsigned i = 0; i < mysql_num_fields(res); i ++) {
			fields[std::string(_fields[i].name)] = i;
		}
	}
}

ResultSet::~ResultSet() {
	mysql_free_result(res);
}

std::shared_ptr<Row> ResultSet::fetch_row() {
	auto row = mysql_fetch_row(res);
	if (!row) return nullptr;
	return std::make_shared<Row>(row, fields);
}
