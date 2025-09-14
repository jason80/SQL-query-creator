#pragma once

#include <gtkmm.h>
#include <memory>

class SQLApp;

class ConnectionWindow : public Gtk::Window {
public:
	ConnectionWindow(BaseObjectType* cobject,
		const Glib::RefPtr<Gtk::Builder> builder,
		std::shared_ptr<SQLApp> app);

	static void show(std::shared_ptr<SQLApp> app);

private:
	std::shared_ptr<SQLApp> app;
	static std::shared_ptr<ConnectionWindow> window;
};
