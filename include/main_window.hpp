#pragma once

#include <gtkmm.h>
#include <memory>

class SQLApp;

class MainWindow : public Gtk::ApplicationWindow {
public:
	MainWindow(std::shared_ptr<SQLApp> app);

	void init();

private:
	std::shared_ptr<SQLApp> app;
};
