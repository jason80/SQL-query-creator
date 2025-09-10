#pragma once

#include <string>
#include <memory>

class MYSQL;
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

private:
	static MYSQL *connection;
};
