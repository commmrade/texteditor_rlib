#include "Dialog.hpp"
#include "gtkmm/application.h"
#include <exception>

Main::Main(TextState &state) : state(state)
{
    create("org.gtkmm.example");   
}



void Main::saveFile()
{
    currentAction = SAVE; //Set action to save

    auto dialog = Gtk::FileDialog::create();
    
    dialog->set_title("Save a file");
    dialog->set_modal(true); //blocks main window
    

    dialog->save(sigc::bind(sigc::mem_fun(
    *this, &Main::on_file_dialog_finish), dialog));

    hold(); //So the app works
    run(); 
}
void Main::openFile()
{
    currentAction = OPEN; //Setting mode to open
    auto dialog = Gtk::FileDialog::create();
    
    dialog->set_title("Open a file");
    dialog->set_modal(true); //blocks main window
    
    dialog->open(sigc::bind(sigc::mem_fun(
    *this, &Main::on_file_dialog_finish), dialog));
    
    hold(); //So the app works
    run();  
}


void Main::on_file_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result, const Glib::RefPtr<Gtk::FileDialog>& dialog)
{
    try 
    {
        if(currentAction == SAVE)
        {
            std::ofstream file;
            file.open(dialog->save_finish(result)->get_path(), std::ios_base::out);

            if(file.is_open())
            {
                for(auto &line : state.lines)
                {
                    file << line << "\n";
                } //Writing lines line one by one
            }
            file.flush();
            file.close();
        }
        else if (currentAction == OPEN) {
            std::ifstream file;
            file.open(dialog->open_finish(result)->get_path());


            std::string line;
            state.lines.clear();
            if(file.is_open())
            {
                while (std::getline(file, line)) {
                    state.lines.push_back(line);
                } //Reading line by line from file
            }
            file.close();
        }
    }
    catch (std::exception exception)
    {
        std::cout << "except\n";
    }
    


    release();    
    quit();

}