//
// Created by seb on 06/12/22.
//

#include <gtkmm/application.h>
#include "clock.h"
#include "MainWindow.h"

int main (int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    MainWindow w;

    Clock c;
    w.add(c);
    c.show();

    //HelloWorld helloworld;

    //helloworld.drawRectangle(10,10, 50, 50);

    /*std::mt19937 gen(26565332123465); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 6);

    for (int n=0; n<100; ++n)
        //Use `distrib` to transform the random unsigned int generated by gen into an int in [1, 6]
        std::cout << distrib(gen) << ' ';
    std::cout << '\n';*/


    //Shows the window and returns when it is closed.
    return app->run(w);

}
