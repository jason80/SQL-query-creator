#include <main_window.hpp>

#include <application.hpp>

MainWindow::MainWindow(BaseObjectType* obj,
            const Glib::RefPtr<Gtk::Builder>& builder,
			std::shared_ptr<SQLApp> app) : Gtk::ApplicationWindow(obj), app(app) {

	sql_entry = builder->get_widget<Gtk::TextView>("sql-entry");

	auto key_controller = Gtk::EventControllerKey::create();
	key_controller->signal_key_pressed().connect(
		sigc::mem_fun(*this, &MainWindow::sql_entry_key_pressed), false
	);
	sql_entry->add_controller(key_controller);
}

bool MainWindow::sql_entry_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state) {
	
	return false;
}
