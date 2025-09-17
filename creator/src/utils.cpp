#include <utils.hpp>

#include <mysql/mysql.h>

#include <myerror.hpp>

#include <libintl.h>
#define _(STRING) gettext(STRING)

void mysql_error_dialog(Gtk::Window *parent) {
	auto error = std::make_shared<MySQLError>();

	std::ostringstream header_ss;
	header_ss << _("MySQL Error");
	std::string header = header_ss.str();

	std::ostringstream secondary_ss;
	secondary_ss << _("Code: ") << error->get_code() << "\n";
	secondary_ss << _("Message: ") << error->get_message();
	std::string secondary = secondary_ss.str();

	auto dialog = Gtk::make_managed<Gtk::MessageDialog>(
		header,
		false,
		Gtk::MessageType::ERROR,
		Gtk::ButtonsType::NONE,
		true
	);

	dialog->set_secondary_text(secondary);
	dialog->set_transient_for(*parent);
	dialog->set_modal(true);


	dialog->add_button(_("Close"), Gtk::ResponseType::CLOSE);
	dialog->add_button(_("Copy"), Gtk::ResponseType::APPLY);


	Gtk::Expander *exp = Gtk::make_managed<Gtk::Expander>(_("Details"));
	Gtk::Box *exp_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 6);

	Gtk::TextView *tv = Gtk::make_managed<Gtk::TextView>();
	tv->set_editable(false);
	tv->set_cursor_visible(false);
	tv->set_wrap_mode(Gtk::WrapMode::WORD_CHAR);


	auto buffer = Gtk::TextBuffer::create();
	std::ostringstream details_ss;
	if (error->get_code() != 0) details_ss << "Errno: " << error->get_code() << "\n";
	if (!error->get_sqlstate().empty()) details_ss << "SQLSTATE: " << error->get_sqlstate() << "\n";
	details_ss << "Message: " << error->get_message() << "\n";

	buffer->set_text(details_ss.str());
	tv->set_buffer(buffer);

	Gtk::ScrolledWindow *scrolled = Gtk::make_managed<Gtk::ScrolledWindow>();
	scrolled->set_min_content_height(120);
	scrolled->set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
	scrolled->set_child(*tv);

	exp_box->append(*scrolled);
	exp->set_child(*exp_box);

	auto *content = dialog->get_content_area();
	content->append(*exp);

	std::string details = details_ss.str();

	dialog->signal_response().connect([dialog, details](int response) {
		if (response == Gtk::ResponseType::CLOSE) {
			dialog->destroy();
		}

		if (response == Gtk::ResponseType::APPLY) {
			auto display = Gdk::Display::get_default();
			if (display) {
				auto clipboard = display->get_clipboard();
				clipboard->set_text(details);
			}
		}
	});

	dialog->show();
}

const std::string valid_path(const std::string path) {
	if (access(path.c_str(), F_OK) == 0) {
		return path;
	}

	return "/usr/local/share/SQL-creator/" + path;
}
