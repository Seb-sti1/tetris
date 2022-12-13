//
// Created by seb on 13/12/22.
//

#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow()
{
    set_default_size(500, 500);
    set_border_width(10);
    set_title("TesTriste");

    this->signal_key_press_event().connect( sigc::mem_fun( *this, &MainWindow::onKeyPress ), false );

}

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