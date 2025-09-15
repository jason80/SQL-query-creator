#pragma once

#include <string>
#include <memory>

struct st_mysql;
typedef struct st_mysql MYSQL;

class ResultSet;

class Connection {
private:
	Connection() = default;

public:
	static const bool connect(const std::string host, const std::string user,
			const std::string pass, const std::string database);
	static void disconnect();

	static std::shared_ptr<ResultSet> db_query(const std::string sql);

	friend ResultSet;
	friend class MySQLError;

private:
	static MYSQL *connection;
};
