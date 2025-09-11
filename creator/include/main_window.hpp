#pragma once

#include <gtkmm.h>
#include <memory>

class SQLApp;

class MainWindow : public Gtk::ApplicationWindow {
public:

	MainWindow(BaseObjectType* cobject,
            const Glib::RefPtr<Gtk::Builder>& builder,
			std::shared_ptr<SQLApp> app);

    /*MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;*/

	void init();

private:
	std::shared_ptr<SQLApp> app;
};
