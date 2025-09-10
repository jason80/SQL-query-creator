#include <main_window.hpp>

#include <application.hpp>

#include <libintl.h>

#define _(STRING) gettext(STRING)

MainWindow::MainWindow(std::shared_ptr<SQLApp> app) : app{app} {}

void MainWindow::init() {
	set_title(_("SQL Query Creator"));
	set_default_size(1000, 600);
}
