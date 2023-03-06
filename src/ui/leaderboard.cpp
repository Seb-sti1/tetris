//
// Created by seb on 05/03/23.
//

#include "leaderboard.h"


Leaderboard::Leaderboard(std::vector<Player *>& players, int width, int height) : players(players)
{
    set_size_request(width, height);

    // Create a new scrolled window, with scrollbars only if needed
    set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    add(m_TreeView);

    // create list store
    m_refListStore = Gtk::ListStore::create(m_Columns);

    m_TreeView.set_model(m_refListStore);

    //Add the Model's column to the View's columns:
    m_TreeView.append_column("Pseudo", m_Columns.name);
    m_TreeView.append_column("Score", m_Columns.score);

    show_all_children();
}

bool Leaderboard::on_draw(const ::Cairo::RefPtr<::Cairo::Context> &cr)
{
    bool changed = false;

    // for every player, either update the existing row or add one
    for(auto player : players)
    {
        bool found = false;
        auto children = m_refListStore->children();

        for (auto iter = children.begin(); iter != children.end(); ++iter)
        {
            Glib::ustring name = (*iter)[m_Columns.name];

            if (strcmp(name.c_str(), player->name.c_str()) == 0)
            {
                if ((*iter)[m_Columns.score] != (int) player->score)
                {
                    (*iter)[m_Columns.score] = (int) player->score;
                    changed = true;
                }
                found = true;
                break;
            }
        }

        if (!found)
        {
            changed = true;

            Gtk::TreeModel::Row row = *(m_refListStore->append());
            row[m_Columns.name] = (player->name + ((player->alive) ? "" : "💀")).c_str();
            row[m_Columns.score] = (int) player->score;
        }
    }

    if (changed)
    {
        m_TreeView.get_column(1)->set_sort_column(m_Columns.score);
        m_TreeView.get_column(1)->set_sort_order(Gtk::SORT_DESCENDING);
    }

    return Gtk::ScrolledWindow::on_draw(cr);
}
