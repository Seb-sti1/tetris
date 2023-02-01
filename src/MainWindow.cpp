//
// Created by seb on 13/12/22.
//

#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow(Game& g) :
    homeButtonsContainer(Gtk::ORIENTATION_VERTICAL),
    game(g),
    state(HOME),
    graphicMatrix(game.matrix)
{

    /* ============================ CREATE HOME PAGE ====== */
    homeButtonsContainer.set_margin_top(50);

    b_start.set_label("Commencer une partie");

    b_start.signal_clicked().connect(
            sigc::mem_fun(*this, &MainWindow::startGame));
    homeButtonsContainer.add(b_start);

    b_join_multi.set_label("Rejoindre une partie multijoueur");
    b_join_multi.signal_button_release_event().connect([&](GdkEventButton*) {
        std::cout << "Join multiplayer game" << std::endl;
        return true;
    });
    homeButtonsContainer.add(b_join_multi);

    b_create_multi.set_label("Créer une partie multijoueur");
    b_create_multi.signal_button_release_event().connect([&](GdkEventButton*) {
        std::cout << "Start multiplayer game" << std::endl;
        return true;
    });
    homeButtonsContainer.add(b_create_multi);

    b_help.set_label("Aide");
    b_help.signal_button_release_event().connect([&](GdkEventButton*) {
        std::cout << "Help" << std::endl;
        return true;
    });
    homeButtonsContainer.add(b_help);

    l_undertext.set_label("Tetris by Billy & Sébastien.");
    homeButtonsContainer.add(l_undertext);

    /* ======================= CREATE GAME PAGE =================== */
    playingGrid.attach(graphicMatrix, 0, 0);

    b_quit.set_label("Quitter la partie");
    b_quit.signal_button_release_event().connect([&](GdkEventButton*) {
        changeToPage(HOME);
        return true;
    });
    playingGrid.attach(b_quit, 1, 0);

    /* ======================== OPTIONS OF THE MAIN WINDOW ============== */
    set_default_size(500, 500);
    set_border_width(10);
    set_title("Tetris");

    add(homeButtonsContainer);

    this->signal_key_press_event().connect( sigc::mem_fun( *this, &MainWindow::onKeyPress ), false );

    show_all();
}

void MainWindow::changeToPage(Page p)
{
    remove();

    switch (p) {
        case HOME:
            add(homeButtonsContainer);
            break;
        case GAME:
            add(playingGrid);
            break;
    }

    state = p;

    show_all();
}

void MainWindow::startGame()
{
    game.StartGame(std::time(nullptr));

    changeToPage(GAME);
};



MainWindow::~MainWindow() = default;

bool MainWindow::onKeyPress(GdkEventKey* event)
{
    std::cout << event->keyval << ' ' << event->hardware_keycode << ' ' << event->state << std::endl;
    // UP 65362
    // DOWN 65364
    // RIGHT 65363
    // LEFT 65361
    // Esc 65307
    return false;
}