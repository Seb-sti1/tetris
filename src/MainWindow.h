//
// Created by seb on 13/12/22.
//

#ifndef TETRIS_MAINWINDOW_H
#define TETRIS_MAINWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/fixed.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/frame.h>


class MainWindow : public Gtk::Window {

public:
    MainWindow();
    ~MainWindow();

private:
    Gtk::Button b_start, b_join_multi, b_create_multi, b_help;
    Gtk::Label l_undertext;

    Gtk::ButtonBox container;


protected:
    bool onKeyPress(GdkEventKey *event);

};


#endif //TETRIS_MAINWINDOW_H
