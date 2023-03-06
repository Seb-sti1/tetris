//
// Created by seb & billy on 13/12/22.
//

#ifndef TETRIS_MAINWINDOW_H
#define TETRIS_MAINWINDOW_H

#include <gtkmm.h>
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
#include "leaderboard.h"
#include "../multiplayer/server.h"
#include "../multiplayer/client.h"

enum Page {HOME, GAME, AFTER_GAME, MULTI, MULTI_AFTER_GAME};

// TODO create a graphic scoreboard
// TODO add graphic scoreboard to game if isMulti

class MainWindow : public Gtk::Window {

public:
    explicit MainWindow(Game& g);

private:
    Game& game;
    Page state;

    // HOME page
    Gtk::ButtonBox homeContainer;
    Gtk::Button b_start, b_join_multi, b_create_multi, b_help;
    Gtk::Label homeUndertext;

    // GAME page
    Gtk::Grid playingGrid;
    GraphicMatrix gameMatrix;
    Gtk::Label score;
    Gtk::Button gameQuit;
    GraphicMatrix previewMatrix;

    // AFTER_GAME page
    Gtk::ButtonBox afterGameContainer;
    Gtk::Label congratulation;
    Gtk::Button afterGameQuit;
    Gtk::Label afterGameUndertext;

    // MULTI page
    Gtk::ButtonBox serverMultiplayerContainer;
    Gtk::Label infoText;
    Gtk::Button startGame;
    bool isMulti = false;
    bool isServer = false;
    Server server;
    Client client;

    // MULTI_AFTER_GAME page
    Gtk::Grid multiAfterGameGrid;
    Leaderboard leaderboard;
    Gtk::Label paratext;
    Gtk::Button multiAfterGameQuit;



protected:
    bool onKeyPress(GdkEventKey *event);
    void changeToPage(Page p);

    /**
     * Ask a question to the user
     * @param question the question
     * @return the answer of the user
     */
    std::string ask(const std::string& question);

    bool update();
};

void popupError(const char* error); 

#endif //TETRIS_MAINWINDOW_H
