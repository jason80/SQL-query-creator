#pragma once

#include <gtkmm.h>

#include <memory>

class MainWindow;

class SQLApp: public Gtk::Application, public std::enable_shared_from_this<SQLApp> {
public:
	SQLApp();

	void on_activate() override;

	MainWindow *get_main_window() { return main_window; }

private:
	MainWindow *main_window;
};
