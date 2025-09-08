#include <application.hpp>

#include <main_window.hpp>

SQLApp::SQLApp() : Gtk::Application("com.codigoymate.sql-creator") {}

void SQLApp::on_activate() {

	main_window = std::make_shared<MainWindow>(shared_from_this());
	main_window->init();

	this->add_window(*main_window);

	// Style
	auto provider = Gtk::CssProvider::create();
	provider->load_from_path("res/style.css");
	auto display = Gdk::Display::get_default();
	Gtk::StyleContext::add_provider_for_display(
		display, provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	main_window->present();
}

int main(int argc, char *argv[]) {
	auto app = std::make_shared<SQLApp>();
	return app->run(argc, argv);
}
