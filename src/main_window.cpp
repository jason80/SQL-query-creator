#include <main_window.hpp>

#include <application.hpp>

MainWindow::MainWindow(std::shared_ptr<SQLApp> app) : app{app} {}

void MainWindow::init() {
	set_title("SQL Query Creator");
	set_default_size(1000, 600);
	
	
}
