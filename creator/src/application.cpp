#include <application.hpp>

#include <main_window.hpp>

#include <connection_window.hpp>

#include <locale.h>
#include <libintl.h>

#include <connection.hpp>

#include <utils.hpp>

SQLApp::SQLApp() : Gtk::Application("org.jason80.SQL-creator") {}

void SQLApp::on_activate() {

	// Actions
	this->add_action("connect", [this](){
		ConnectionWindow::show(this->shared_from_this());
	});
	this->add_action("disconnect", [this](){
		Connection::disconnect();
	});

	// Style
	auto provider = Gtk::CssProvider::create();
	provider->load_from_path(valid_path("res/style.css"));
	auto display = Gdk::Display::get_default();
	Gtk::StyleContext::add_provider_for_display(
		display, provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	// Builder

	auto builder = Gtk::Builder::create_from_file(valid_path("res/query-creator.ui"));

	main_window = Gtk::Builder::get_widget_derived<MainWindow>(
			builder, "main-window", shared_from_this());

	this->add_window(*main_window);

	main_window->present();
}

int main(int argc, char *argv[]) {

	setlocale(LC_ALL, "");
    bindtextdomain("SQL-creator", "./locales");
    textdomain("SQL-creator");

	auto app = std::make_shared<SQLApp>();
	return app->run(argc, argv);
}
