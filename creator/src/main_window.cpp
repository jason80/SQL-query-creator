#include <main_window.hpp>

#include <application.hpp>

#include <libintl.h>

#define _(STRING) gettext(STRING)


MainWindow::MainWindow(BaseObjectType* obj,
            const Glib::RefPtr<Gtk::Builder>& builder,
			std::shared_ptr<SQLApp> app) : Gtk::ApplicationWindow(obj), app(app) {}

void MainWindow::init() {
	
}
