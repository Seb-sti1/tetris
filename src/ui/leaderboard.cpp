//
// Created by seb & billy on 05/03/23.
//

#include "leaderboard.h"


Leaderboard::Leaderboard(int width, int height,
                         std::vector<Player *> &players,
                         Player &self) : players(players), self(self)
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
    m_TreeView.append_column("", m_Columns.status);
    m_TreeView.append_column("Score", m_Columns.score);

    show_all_children();
}

bool Leaderboard::addOrUpdateRow(const Player& p)
{
    if (strcmp(p.name.c_str(), "") != 0)
    {

        // try to update row
        for (const auto & iter : m_refListStore->children())
        {
            Glib::ustring name = iter[m_Columns.name];

            if (strcmp(name.c_str(), p.name.c_str()) == 0)
            {
                if (iter[m_Columns.score] != (int) p.score)
                {
                    iter[m_Columns.score] = (int) p.score;
                    iter[m_Columns.status] = (p.alive) ? "" : "💀";
                    return true;
                }
                return false;
            }
        }

        // create new one if necessary
        Gtk::TreeModel::Row row = *(m_refListStore->append());
        row[m_Columns.name] = p.name.c_str();
        row[m_Columns.score] = (int) p.score;
        row[m_Columns.status] = (p.alive) ? "" : "💀";

        return true;
    }
    return false;
}


bool Leaderboard::on_draw(const ::Cairo::RefPtr<::Cairo::Context> &cr)
{
    bool changed = false;

    // for every player, either update the existing row or add one
    for(auto player : players)
    {
        changed = changed || addOrUpdateRow(*player);
    }

    changed = changed || addOrUpdateRow(self);

    if (changed)
    {
        m_TreeView.get_column(1)->set_sort_column(m_Columns.score);
        m_TreeView.get_column(1)->set_sort_order(Gtk::SORT_DESCENDING);
    }

    return Gtk::ScrolledWindow::on_draw(cr);
}
