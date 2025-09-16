#include <main_window.hpp>

#include <application.hpp>
#include <connection.hpp>
#include <utils.hpp>

MainWindow::MainWindow(BaseObjectType* obj,
            const Glib::RefPtr<Gtk::Builder>& builder,
			std::shared_ptr<SQLApp> app) : Gtk::ApplicationWindow(obj), app(app) {

	sql_entry = builder->get_widget<Gtk::TextView>("sql-entry");

	auto key_controller = Gtk::EventControllerKey::create();
	key_controller->signal_key_pressed().connect(
		[this](guint keyval, guint keycode, Gdk::ModifierType state) {
			return sql_entry_key_pressed(keyval, keycode, state);
		},
		false
	);
	sql_entry->add_controller(key_controller);
}

bool MainWindow::sql_entry_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state) {

	auto mods = state & Gdk::ModifierType::SHIFT_MASK;
	if (keyval == GDK_KEY_Return &&
		mods == Gdk::ModifierType::SHIFT_MASK) {

		auto sql = sql_entry->get_buffer()->get_text();

		if (Connection::is_connected()) {
			auto res = Connection::db_query(sql);

			if (!res) {
				mysql_error_dialog(this);
			}

		}

		// select all text:
		sql_entry->get_buffer()->select_range(
			sql_entry->get_buffer()->get_iter_at_offset(0),
			sql_entry->get_buffer()->get_iter_at_offset(sql.size())
		);

		return true;
	}

	return false;
}
