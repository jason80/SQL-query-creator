#include <connection_window.hpp>

#include <application.hpp>
#include <main_window.hpp>

ConnectionWindow::ConnectionWindow(BaseObjectType* cobject,
	const Glib::RefPtr<Gtk::Builder> builder,
	std::shared_ptr<SQLApp> app) : Gtk::Window(cobject), app(app) {

	this->set_transient_for(*app->get_main_window());

	auto connect_button = builder->get_widget<Gtk::Button>("connect-button");
	connect_button->signal_clicked().connect([this]() {
		this->close();
	});
}

void ConnectionWindow::show(std::shared_ptr<SQLApp> app) {
	auto builder = Gtk::Builder::create_from_file("res/query-creator.ui");

	auto window = Gtk::Builder::get_widget_derived<ConnectionWindow>(
			builder, "connection-window", app);

	window->present();
}
