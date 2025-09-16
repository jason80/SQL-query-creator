#include <main_window.hpp>

#include <application.hpp>
#include <connection.hpp>
#include <utils.hpp>

#include <resultset.hpp>
#include <row.hpp>

class RowObject : public Glib::Object {
public:
    RowObject(const std::vector<std::string>& values) {
        this->values = values;
    }

	static Glib::RefPtr<RowObject> create(const std::vector<std::string>& values) {
        return Glib::make_refptr_for_instance<RowObject>(new RowObject(values));
    }

    const std::string& get_value(int i) const {
        return values.at(i);
    }

	unsigned size() const { return values.size(); }

private:
    std::vector<std::string> values;
};

MainWindow::MainWindow(BaseObjectType* obj,
            const Glib::RefPtr<Gtk::Builder>& builder,
			std::shared_ptr<SQLApp> app) : Gtk::ApplicationWindow(obj), app(app) {

	sql_entry = builder->get_widget<Gtk::TextView>("sql-entry");
	rs_table = builder->get_widget<Gtk::ColumnView>("rs-table");

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
			} else {
				load_table(res);
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

void MainWindow::load_table(std::shared_ptr<ResultSet> res) {
	// Create store
	using RowStore = Glib::RefPtr<Gio::ListStore<RowObject>>;
	RowStore store = Gio::ListStore<RowObject>::create();

	// Load table
	while (auto row = res->fetch_row()) {
		std::vector<std::string> values;
		for (unsigned i = 0; i < res->field_count(); i++) {
			values.push_back(row->get_string(i));
		}
		store->append(RowObject::create(values));
	}

	remove_columns();

	// Crear columnas dinámicamente
    for (unsigned col = 0; col < res->field_count(); col++) {
        // Factory para esta columna
        auto factory = Gtk::SignalListItemFactory::create();

        factory->signal_setup().connect([](const Glib::RefPtr<Gtk::ListItem>& list_item) {
            auto label = Gtk::make_managed<Gtk::Label>();
            label->set_xalign(0.0f); // alineación a la izquierda
            list_item->set_child(*label);
        });

        factory->signal_bind().connect([col](const Glib::RefPtr<Gtk::ListItem>& list_item) {
            auto rowobj = std::dynamic_pointer_cast<RowObject>(list_item->get_item());
            auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());

            if (rowobj && label) {
                if (col < rowobj->size())
                    label->set_text(rowobj->get_value(col));
                else
                    label->set_text("");
            }
        });

        // Nombre de la columna: podés obtenerlo de ResultSet (ej: res->field_name(col))
        auto column = Gtk::ColumnViewColumn::create(res->get_field_names().at(col), factory);
		created_columns.push_back(column);
        rs_table->append_column(column);
    }

	// Conectar modelo
	auto selection = Gtk::SingleSelection::create(store);
	rs_table->set_model(selection);
}

void MainWindow::remove_columns() {
	for (auto column : created_columns) {
    	rs_table->remove_column(column);
	}

	created_columns.clear();
}
