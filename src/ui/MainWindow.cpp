//
// Created by seb & billy on 13/12/22.
//

#include "MainWindow.h"
#include <iostream>
#include <glibmm/main.h>

MainWindow::MainWindow(Game& g) :
        homeContainer(Gtk::ORIENTATION_VERTICAL),
        afterGameContainer(Gtk::ORIENTATION_VERTICAL),
        game(g),
        server(g),
        client(g),
        state(HOME),
        gameMatrix(game.matrix),
        previewMatrix(game.next_tetromino_matrix)
{

    /* ============================ CREATE HOME PAGE ====== */
    homeContainer.set_margin_top(50);

    b_start.set_label("Commencer une partie");

    b_start.signal_button_release_event().connect([&](GdkEventButton*) {
        game.startGame(std::time(nullptr));

        changeToPage(GAME);
        return true;
    });
    homeContainer.add(b_start);

    b_join_multi.set_label("Rejoindre une partie multijoueur");
    b_join_multi.signal_button_release_event().connect([&](GdkEventButton*) {
        std::cout << "Join multiplayer game" << std::endl;
        return true;
    });
    homeContainer.add(b_join_multi);

    b_create_multi.set_label("Créer une partie multijoueur");
    b_create_multi.signal_button_release_event().connect([&](GdkEventButton*) {
        changeToPage(SERVER_MULTI);
        return true;
    });
    homeContainer.add(b_create_multi);

    b_help.set_label("Aide");
    b_help.signal_button_release_event().connect([&](GdkEventButton*) {
        std::cout << "Help" << std::endl;
        return true;
    });
    homeContainer.add(b_help);

    homeUndertext.set_label("Tetris by Billy & Sébastien.");
    homeContainer.add(homeUndertext);

    /* ======================= CREATE GAME PAGE =================== */
    gameMatrix.set_margin_right(20);
    playingGrid.attach(gameMatrix, 0, 0, 1, 3);

    playingGrid.attach(previewMatrix, 1, 0);

    score.set_text("Your score is " + std::to_string(game.score));
    playingGrid.attach(score, 1, 1);

    gameQuit.set_label("Quitter la partie");
    gameQuit.signal_button_release_event().connect([&](GdkEventButton*) {
        game.stopGame();
        changeToPage(HOME);
        return true;
    });
    playingGrid.attach(gameQuit, 1, 2);

    /* ======================= CREATE AFTER GAME PAGE =================== */
    afterGameContainer.add(congratulation);

    afterGameQuit.set_label("Quitter la partie");
    afterGameQuit.signal_button_release_event().connect([&](GdkEventButton*) {
        game.stopGame();
        changeToPage(HOME);
        return true;
    });
    afterGameContainer.add(afterGameQuit);

    afterGameUndertext.set_label("Tetris by Billy & Sébastien.");
    afterGameContainer.add(afterGameUndertext);

    /* ======================= CREATE SERVER MULTIPLAYER PAGE =================== */

    startGame.set_label("Lancer la partie");
    startGame.signal_button_release_event().connect([&](GdkEventButton*) {
        long date = std::time(nullptr);

        server.startGame(date);

        game.startGame(date);
        return true;
    });

    // TODO add list of connected player in gui
    // TODO ask for name (in pop up)
    serverMultiplayerContainer.add(infoText);
    serverMultiplayerContainer.add(startGame);

    /* ======================== OPTIONS OF THE MAIN WINDOW ============== */
    set_default_size(500, 500);
    set_border_width(10);
    set_title("Tetris");

    add(homeContainer);

    Glib::signal_timeout().connect(sigc::mem_fun(*this, &MainWindow::update), 1000 / 30);
    this->signal_key_press_event().connect( sigc::mem_fun( *this, &MainWindow::onKeyPress ), false );

    show_all();
}

void MainWindow::changeToPage(Page p)
{
    remove();

    switch (p) {
        case HOME:
            add(homeContainer);
            break;
        case GAME:
            add(playingGrid);
            break;
        case AFTER_GAME:
            add(afterGameContainer);
            break;
        case SERVER_MULTI:
            infoText.set_text("Le serveur multijoueur est ouvert !");
            server.start();


            add(serverMultiplayerContainer);
            break;
    }

    state = p;

    show_all();
}

bool MainWindow::onKeyPress(GdkEventKey* event)
{
    if (game.state != IN_GAME)
        return false;

    std::cout << event->keyval << ' ' << event->hardware_keycode << ' ' << event->state << std::endl;
    // UP 65362
    // DOWN 65364
    // RIGHT 65363
    // LEFT 65361
    // Esc 65307

    switch(event->keyval) {
        case 65307:
            game.stopGame();
            changeToPage(HOME);
            break;
        case 65364:
            game.registerKeyPress(DOWN);
            break;
        case 65363:
            game.registerKeyPress(RIGHT);
            break;
        case 65362:
            game.registerKeyPress(UP);
            break;
        case 65361:
            game.registerKeyPress(LEFT);
            break;
    }

    return true;
}

bool MainWindow::update()
{
    switch (game.state) {
        case WAITING:
            break;
        case IN_GAME:
            score.set_text("Your score is " + std::to_string(game.score));

            queue_draw();
            break;
        case FINISH:

            if (state != AFTER_GAME)
            {
                changeToPage(AFTER_GAME);

                std::string scores = "You completed " + std::to_string(game.completed_lines) + " line(server), scored " + std::to_string(game.score) + " point(server)\n and reached the level " + std::to_string(game.level);

                congratulation.set_margin_top(50);
                congratulation.set_markup("<span size='large'><b>The game is over!</b></span>\n\n\n"
                                          "<span size='large'>" + scores + ".</span>");
                congratulation.set_alignment(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
            }

            break;
    }
    return true;
}