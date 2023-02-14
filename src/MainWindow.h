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
#include <gtkmm/grid.h>
#include "game.h"
#include "graphicmatrix.h"

enum Page {HOME, GAME};

class MainWindow : public Gtk::Window {

public:
    explicit MainWindow(Game& g);
    ~MainWindow();
    void startGame();

private:
    Gtk::Button b_start, b_join_multi, b_create_multi, b_help, b_quit;
    Gtk::Label l_undertext;

    Game& game;

    Gtk::ButtonBox homeButtonsContainer;
    GraphicMatrix gameMatrix;

    Gtk::Grid playingGrid;
    Gtk::Label score;
    GraphicMatrix previewMatrix;

    Page state;

protected:
    bool onKeyPress(GdkEventKey *event);
    void changeToPage(Page p);

    bool update();
};


#endif //TETRIS_MAINWINDOW_H
