#include "StatBoxRow.h"
#include "../common/functions.h"

#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/label.h>

StatBoxRow::StatBoxRow(const StatValue_t& data) 
: m_data(data)
{
    std::string stat_title_text, escaped_name;

    escaped_name = data.display_name;
    escape_html(escaped_name);
    stat_title_text = "<b>" + escaped_name + "</b>";

    Gtk::Box* layout = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::ORIENTATION_HORIZONTAL, 0);
    Gtk::Box* title_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::ORIENTATION_VERTICAL, 0);
    Gtk::Box* type_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::ORIENTATION_VERTICAL, 0);
    Gtk::Box* values_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::ORIENTATION_VERTICAL, 0);
    Gtk::Label* title_label = Gtk::make_managed<Gtk::Label>("");
    Gtk::Label* type_label = Gtk::make_managed<Gtk::Label>("");
    Gtk::Label* cur_value_label = Gtk::make_managed<Gtk::Label>("");
    // TODO: This will be an input box
    Gtk::Label* new_value_label = Gtk::make_managed<Gtk::Label>("");

    set_size_request(-1, 40);
    type_box->set_size_request(150, -1);
    values_box->set_size_request(150, -1);

    if (data.type == UserStatType::Integer) {
        type_label->set_label("Type: Integer");
        // TODO: may want to bound the size of this
        cur_value_label->set_label("Current value: " + std::to_string(std::any_cast<long long>(data.value)));
    } else if (data.type == UserStatType::Float) {
        type_label->set_label("Type: Float");
        // TODO: may want to bound the size of this
        cur_value_label->set_label("Current value: " + std::to_string(std::any_cast<double>(data.value)));
    } else {
        type_label->set_label("Type: Unknown");
        cur_value_label->set_label("Current value: Unknown");
    }

    new_value_label->set_label("Placeholder");

    title_label->set_markup(stat_title_text);
    title_box->pack_start(*title_label, true, true, 0);
    type_box->pack_start(*type_label, false, true, 0);
    values_box->pack_start(*cur_value_label, false, true, 0);
    values_box->pack_start(*new_value_label, false, true, 0);
    layout->pack_start(*title_box, true, true, 0);
    layout->pack_start(*type_box, false, true, 0);
    layout->pack_start(*values_box, false, true, 0);

    add(*layout);
}

StatBoxRow::~StatBoxRow() {}