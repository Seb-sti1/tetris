//
// Created by seb on 13/12/22.
//

#ifndef TETRIS_MAINWINDOW_H
#define TETRIS_MAINWINDOW_H

#include <gtkmm/window.h>

class MainWindow : public Gtk::Window {

public:
    MainWindow();
    ~MainWindow();


protected:
    bool onKeyPress(GdkEventKey *event);

};


#endif //TETRIS_MAINWINDOW_H
