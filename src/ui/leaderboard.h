//
// Created by seb on 05/03/23.
//

#ifndef TETRIS_LEADERBOARD_H
#define TETRIS_LEADERBOARD_H


#include <vector>
#include <gtkmm.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/liststore.h>
#include "../multiplayer/messages/player.h"

class Leaderboard : public Gtk::ScrolledWindow {
public:
    explicit Leaderboard(std::vector<Player*>& players, int width, int height);

    class ModelColumns : public Gtk::TreeModel::ColumnRecord
    {
    public:

        ModelColumns()
        {
            add(name);
            add(score);
        }

        Gtk::TreeModelColumn<Glib::ustring> name;
        Gtk::TreeModelColumn<int> score;
    };

    ModelColumns m_Columns;

protected:
    Glib::RefPtr<Gtk::ListStore> m_refListStore; //The Tree Model.
    Gtk::TreeView m_TreeView; //The Tree View.
    std::vector<Player*>& players;

    bool on_draw(const Cairo::RefPtr<::Cairo::Context> &cr) override;
};


#endif //TETRIS_LEADERBOARD_H
