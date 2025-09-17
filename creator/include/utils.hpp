#pragma once

#include <gtkmm.h>

void mysql_error_dialog(Gtk::Window *parent);

const std::string valid_path(const std::string path);
