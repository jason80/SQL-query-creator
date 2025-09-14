#include <connection_window.hpp>

#include <application.hpp>
#include <main_window.hpp>

#include <connection.hpp>

ConnectionWindow::ConnectionWindow(BaseObjectType* cobject,
	const Glib::RefPtr<Gtk::Builder> builder,
	std::shared_ptr<SQLApp> app) : Gtk::Window(cobject), app(app) {

	this->set_transient_for(*app->get_main_window());

	host_entry = builder->get_widget<Gtk::Entry>("host-entry");
	user_entry = builder->get_widget<Gtk::Entry>("user-entry");
	pass_entry = builder->get_widget<Gtk::Entry>("pass-entry");
	database_entry = builder->get_widget<Gtk::Entry>("database-entry");

	auto connect_button = builder->get_widget<Gtk::Button>("connect-button");
	connect_button->signal_clicked().connect([this]() {
		this->close();
		Connection::connect(host_entry->get_text(),
				user_entry->get_text(), pass_entry->get_text(),
				database_entry->get_text());
	});
}

void ConnectionWindow::show(std::shared_ptr<SQLApp> app) {
	auto builder = Gtk::Builder::create_from_file("res/query-creator.ui");

	auto window = Gtk::Builder::get_widget_derived<ConnectionWindow>(
			builder, "connection-window", app);

	window->present();
}
