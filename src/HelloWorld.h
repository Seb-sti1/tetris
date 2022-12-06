//
// Created by seb on 06/12/22.
//

#ifndef TETRIS_HELLOWORLD_H
#define TETRIS_HELLOWORLD_H


#include <gtkmm/button.h>
#include <gtkmm/window.h>

class HelloWorld : public Gtk::Window
{

public:
    HelloWorld();
    virtual ~HelloWorld();

protected:
    //Signal handlers:
    void on_button_clicked();

    //Member widgets:
    Gtk::Button m_button;
};


#endif //TETRIS_HELLOWORLD_H
