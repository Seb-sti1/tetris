//
// Created by seb on 06/12/22.
//

#include <gtkmm/application.h>
#include "MainWindow.h"




int main (int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.tetris");


    for (int j = I; j != S + 1; j++)
    {
        for (int i = UP; i != RIGHT + 1; i++)
        {
            auto t = static_cast<tetromino_type>(j);
            auto o = static_cast<orient>(i);

            std::cout << t << " " << o << std::endl;
            Tetromino tetromino(t, 0, 0, o);

            tetromino.print();
        }
    }


    Game g;
    MainWindow w(g);

    //Shows the window and returns when it is closed.
    return app->run(w);

}
