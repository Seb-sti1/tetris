//
// Created by seb on 06/12/22.
//

#include <gtkmm/application.h>
#include "MainWindow.h"




int main (int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.tetris");

    Game g;
    MainWindow w(g);

    //Shows the window and returns when it is closed.
    return app->run(w);

}
