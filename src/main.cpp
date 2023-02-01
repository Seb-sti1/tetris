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


    /*
    for (int n=0; n<100; ++n)
        //Use `distrib` to transform the random unsigned int generated by gen into an int in [1, 6]
        std::cout << distrib(gen) << ' ';
    std::cout << '\n';*/


    //Shows the window and returns when it is closed.
    return app->run(w);

}
