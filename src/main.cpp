//
// Created by seb & billy on 06/12/22.
//

#include <gtkmm/application.h>
#include "ui/MainWindow.h"


int main (int argc, char *argv[])
{
    auto app = Gtk::Application::create("org.tetris",Gio::APPLICATION_NON_UNIQUE );

    Game g;
    MainWindow w(g);

    //Shows the window and returns when it is closed.
    return app->run(w);
}
