//
// Created by seb & billy on 05/03/23.
//

#ifndef TETRIS_LEADERBOARD_H
#define TETRIS_LEADERBOARD_H


#include <vector>
#include <gtkmm.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treemodelsort.h>
#include <gtkmm/liststore.h>
#include "../multiplayer/messages/player.h"

class Leaderboard : public Gtk::ScrolledWindow {
public:
    Leaderboard(std::vector<Player *> &players, Player &self);

    class ModelColumns : public Gtk::TreeModelSort::ColumnRecord
    {
    public:

        ModelColumns()
        {
            add(name);
            add(status);
            add(score);
        }

        Gtk::TreeModelColumn<Glib::ustring> name;
        Gtk::TreeModelColumn<Glib::ustring> status;
        Gtk::TreeModelColumn<int> score;
    };

    ModelColumns m_Columns;

    bool removeChildren();

protected:
    Glib::RefPtr<Gtk::ListStore> m_refListStore; //The Tree Model.
    Gtk::TreeView m_TreeView; //The Tree View.

    std::vector<Player*>& players;
    Player& self;

    bool addOrUpdateRow(const Player& p);

    bool on_draw(const Cairo::RefPtr<::Cairo::Context> &cr) override;

};


#endif //TETRIS_LEADERBOARD_H
