//
// Created by seb & billy on 13/12/22.
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
#include "../game.h"
#include "graphicmatrix.h"
#include "../multiplayer/server.h"
#include "../multiplayer/client.h"

enum Page {HOME, GAME, AFTER_GAME, SERVER_MULTI};

class MainWindow : public Gtk::Window {

public:
    explicit MainWindow(Game& g);

private:
    Game& game;
    Page state;

    // main page
    Gtk::ButtonBox homeContainer;
    Gtk::Button b_start, b_join_multi, b_create_multi, b_help;
    Gtk::Label homeUndertext;

    // Multiplayer page
    Gtk::ButtonBox serverMultiplayerContainer;
    Gtk::Label infoText;
    Gtk::Button startGame;
    Server server;
    Client client;

    // game page
    Gtk::Grid playingGrid;
    GraphicMatrix gameMatrix;
    Gtk::Label score;
    Gtk::Button gameQuit;
    GraphicMatrix previewMatrix;

    // after game page
    Gtk::ButtonBox afterGameContainer;
    Gtk::Label congratulation;
    Gtk::Button afterGameQuit;
    Gtk::Label afterGameUndertext;

protected:
    bool onKeyPress(GdkEventKey *event);
    void changeToPage(Page p);

    bool update();
};


#endif //TETRIS_MAINWINDOW_H
