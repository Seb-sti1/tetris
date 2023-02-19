//
// Created by seb on 06/12/22.
//

#include <gtkmm/application.h>
#include "ui/MainWindow.h"
#include "multiplayer/server.h"
#include "multiplayer/client.h"


int main (int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.tetris");

    Game g;

    if(strcmp(argv[1],"server") == 0)
    {
        auto s = Server(g);


    }
    else
    {
        auto c = Client("127.0.0.1");
    }



    //MainWindow w(g);

    //Shows the window and returns when it is closed.
    return app->run(w);

}
