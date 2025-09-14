#include <myerror.hpp>

#include <mysql/mysql.h>

#include <connection.hpp>

#include <libintl.h>
#define _(STRING) gettext(STRING)

MySQLError::MySQLError() {
	code = mysql_errno(Connection::connection);
	const char *e = mysql_error(Connection::connection);
	message = e ? e : _("(no message)");


	const char *ss = mysql_sqlstate(Connection::connection);
	if (ss && ss[0] != '\0') sqlstate = ss;	
}
