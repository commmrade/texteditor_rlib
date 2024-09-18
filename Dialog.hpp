#pragma once

#include "glibmm/refptr.h"
#include "gtkmm/window.h"
#include "sigc++/functors/mem_fun.h"
#include <gtkmm/application.h>
#include<iostream>
#include "sigc++/functors/mem_fun.h"
#include <string>
#include<fstream>
#include<gtkmm/filechooser.h>
#include<gtkmm.h>
#include<gtkmm/filechooser.h>
#include<gtkmm/filedialog.h>
#include "TextState.hpp"

enum Action {
    SAVE,
    OPEN
};


class Main : public Gtk::Application
{
    //Glib::RefPtr<Gtk::FileDialog> dialog;
    TextState &state;

    Action currentAction;
public:
    Main(TextState &state);


    void saveFile();
    void openFile();
  
    void on_file_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result, const Glib::RefPtr<Gtk::FileDialog>& dialog);
    
};