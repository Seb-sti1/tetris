//
// Created by seb on 06/12/22.
//

#include <iostream>
#include "HelloWorld.h"

HelloWorld::HelloWorld()
        : m_button("Hello World")   // creates a new button with label "Hello World".
{
    // Sets the border width of the window.
    set_border_width(10);

    // When the button receives the "clicked" signal, it will call the
    // on_button_clicked() method defined below.
    m_button.signal_clicked().connect(sigc::mem_fun(*this,
                                                    &HelloWorld::on_button_clicked));

    this->signal_key_press_event().connect( sigc::mem_fun( *this, &HelloWorld::onKeyPress ), false );
    // This packs the button into the Window (a container).
    add(m_button);

    // The final step is to display this newly created widget...
    m_button.show();
}

HelloWorld::~HelloWorld()
{
}

void HelloWorld::on_button_clicked()
{
    std::cout << "Hello World" << std::endl;
}

bool HelloWorld::onKeyPress(GdkEventKey* event)
{
    std::cout << event->keyval << ' ' << event->hardware_keycode << ' ' << event->state << std::endl;
    // UP 65362
    // DOWN 65364
    // RIGHT 65363
    // LEFT 65361
    // Esc 65307
    return false;
}