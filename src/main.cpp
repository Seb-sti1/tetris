//
// Created by seb on 06/12/22.
//

#include <gtkmm/application.h>
#include "ui/MainWindow.h"
#include "multiplayer/client.h"


int main (int argc, char *argv[])
{

    int argcount = 0;

    auto app = Gtk::Application::create(argcount, argv, "org.tetris");

    Game g;

    if(argc > 1)
    {
    }
    else
    {
        auto c = Client(g);
        c.connectToServer("127.0.0.1", "Moi");
    }

    MainWindow w(g);

    //Shows the window and returns when it is closed.
    return app->run(w);

}
