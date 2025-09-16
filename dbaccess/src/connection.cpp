#include <connection.hpp>

#include <resultset.hpp>

#include <mysql/mysql.h>
#include <iostream>
using std::cout;
using std::endl;

MYSQL *Connection::connection = nullptr;

const bool Connection::connect(const std::string host,
		const std::string user, const std::string pass, const std::string database) {
	connection = mysql_init(nullptr);
	if (!mysql_real_connect(connection, host.c_str(),
			user.c_str(), pass.c_str(), database.c_str(),
			0, nullptr, 0)) {
		cout << "MySQL connection error." << endl;
		cout << mysql_error(connection) << endl;
		return false;
	}

	cout << "Connected to \"" << database << "\"." << endl;
	return true;
}

void Connection::disconnect() {
	mysql_close(connection);
	connection = nullptr;
	cout << "Disconnected." << endl;
}

std::shared_ptr<ResultSet> Connection::db_query(const std::string sql) {

#ifdef SHOW_SQL
	cout << sql << endl;
#endif

	if (mysql_query(connection, sql.c_str())) {
		cout << mysql_error(connection) << endl;
		return nullptr;
	}

	return std::make_shared<ResultSet>();
}
