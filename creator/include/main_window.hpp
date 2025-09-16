#pragma once

#include <gtkmm.h>
#include <memory>
#include <list>

class SQLApp;
class ResultSet;

class MainWindow : public Gtk::ApplicationWindow {
public:

	MainWindow(BaseObjectType* cobject,
            const Glib::RefPtr<Gtk::Builder>& builder,
			std::shared_ptr<SQLApp> app);

private:
	std::shared_ptr<SQLApp> app;
	Gtk::TextView *sql_entry;
	Gtk::ColumnView *rs_table;

	std::list<Glib::RefPtr<Gtk::ColumnViewColumn>> created_columns;

	bool sql_entry_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state);

	void load_table(std::shared_ptr<ResultSet> res);
	void remove_columns();
};
