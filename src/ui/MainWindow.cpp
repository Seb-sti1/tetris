//
// Created by seb & billy on 13/12/22.
//

#include "MainWindow.h"
#include <iostream>
#include <glibmm/main.h>

MainWindow::MainWindow(Game& g) :
        homeContainer(Gtk::ORIENTATION_VERTICAL),
        afterGameContainer(Gtk::ORIENTATION_VERTICAL),
        serverMultiplayerContainer(Gtk::ORIENTATION_VERTICAL),
        game(g),
        server(g),
        client(g),
        state(HOME),
        gameMatrix(game.matrix),
        previewMatrix(game.next_tetromino_matrix),
        leaderboard(server.clients, 400, 300)
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
        isMulti = true;

        try {
            client.connectToServer(ask("Quelle est l'ip du serveur ?"),
                                   ask("Quel est votre pseudo ?"));
            changeToPage(MULTI);
        } catch (const std::system_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            popupError(e.what());
        }

        return true;
    });
    homeContainer.add(b_join_multi);

    b_create_multi.set_label("Créer une partie multijoueur");
    b_create_multi.signal_button_release_event().connect([&](GdkEventButton*) {
        server.self.name = ask("Quel est votre pseudo ?");

        isMulti = true;
        isServer = true;

        serverMultiplayerContainer.add(startGame); // TODO remove add the end
        multiAfterGameGrid.add(multiAfterGameQuit); // TODO remove add the end

        server.start();

        changeToPage(MULTI);
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

    /* ======================= CREATE MULTIPLAYER PAGE =================== */

    startGame.set_label("Lancer la partie");
    startGame.signal_button_release_event().connect([&](GdkEventButton*) {
        long date = std::time(nullptr);

        server.startGame(date);

        game.startGame(date);
        return true;
    });

    serverMultiplayerContainer.add(infoText);

    /* ======================= MULTIPLAYER AFTER GAME PAGE =================== */

    paratext.set_text("Tu as fini ta partie. Cependant d'autres joueurs jouent encore."
                      "Le créateur de la partie pourra la terminer quand tout le monde aura fini !");
    multiAfterGameGrid.add(paratext);

    multiAfterGameGrid.add(leaderboard);

    multiAfterGameQuit.set_label("Lancer la partie");
    multiAfterGameQuit.signal_button_release_event().connect([&](GdkEventButton*) {
        server.stop();



        return true;
    });

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
        case MULTI:
            add(serverMultiplayerContainer);
            break;
        case MULTI_AFTER_GAME:
            add(multiAfterGameGrid);
            break;
    }

    state = p;

    show_all();
}

bool MainWindow::onKeyPress(GdkEventKey* event)
{
    if (game.state != IN_GAME)
        return false;

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
            if (state == MULTI)
            {
                std::vector<Player*> players = (isServer) ? server.clients : client.clients;

                std::string baseText = (isServer) ? "Le serveur multijoueur est ouvert !\n" : "Vous êtes connecté à une partie multijoueur !\n";

                if (!players.empty())
                {
                    baseText += "Joueurs connectés : ";

                    for (auto player : players)
                    {
                        baseText += player->name + ", ";
                    }

                    baseText += (isServer) ? server.self.name : client.self.name;

                    baseText += "(Vous).";
                }
                else
                {
                    baseText += "Aucun joueur connecté.";
                }


                infoText.set_text(baseText);
            }
            break;
        case IN_GAME:

            if (state == MULTI)
            {
                changeToPage(GAME);
            }

            score.set_text("Ton score est " + std::to_string(game.score));

            queue_draw();
            break;
        case FINISH:
            if (isMulti)
            {
                if (state != AFTER_GAME)
                {
                    changeToPage(AFTER_GAME);

                    std::string scores = "Tu as complété " + std::to_string(game.completed_lines) + " ligne(s), marqué " + std::to_string(game.score) + " point(s)\n et atteint le niveau " + std::to_string(game.level);

                    congratulation.set_margin_top(50);
                    congratulation.set_markup("<span size='large'><b>La partie est terminée !</b></span>\n\n\n"
                                              "<span size='large'>" + scores + ".</span>");
                    congratulation.set_alignment(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
                }
            }
            else
            {
                if (state != MULTI_AFTER_GAME)
                {
                    changeToPage(MULTI_AFTER_GAME);
                }
            }
            break;
    }
    return true;
}

std::string MainWindow::ask(const std::string& question)
{
    Gtk::Dialog dialog(question, true);
    dialog.set_default_size(200, 100);

    // add an entry in the popup window
    Gtk::Entry entry;
    dialog.get_content_area()->pack_start(entry, Gtk::PACK_SHRINK);

    dialog.add_button("_OK", Gtk::RESPONSE_OK);

    dialog.show_all_children();
    dialog.run();

    return entry.get_text();
}


void popupError(const char* error)
{
    auto popup = Gtk::Application::create();

    Gtk::MessageDialog dialog(error, false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE, true);
    dialog.set_title("Erreur");
    dialog.run();
}