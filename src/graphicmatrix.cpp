#include <cairomm/context.h>
#include <gdkmm/color.h>

#include "graphicmatrix.h"

#define w 4
#define h 4
#define w_space 0.8
#define h_space 0.8

GraphicMatrix::GraphicMatrix(Matrix<tetromino_type>& matrix) : matrix(matrix) {}

GraphicMatrix::~GraphicMatrix() {
    std::cout << "good bye" << std::endl;

}

/**
 * The callback function to draw the matrix
 * @param cr the context (a class from GtK lib)
 * @return ??
 */
bool GraphicMatrix::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    std::cout << "coucou" << std::endl;

    cr->scale((float) width/100, (float) height/100);

    for (int i = 0; i < matrix.GetNumRows(); i++) {
        for (int j = 0; j < matrix.GetNumColumns(); j++) {
            std::cout << i << ", " << j << std::endl;

            Gdk::Color c = tetrominoTypeToColor(matrix.At(i, j));
            cr->set_source_rgba(c.get_red(), c.get_green(), c.get_blue(), 1.0);   // green
            cr->rectangle(0, 0, w, h);
            cr->fill_preserve();

            cr->translate(w + w_space, 0);
        }
        cr->translate(- matrix.GetNumColumns() * (w + w_space), h + h_space);
    }
    cr->save();

    return true;
}

Gdk::Color tetrominoTypeToColor(tetromino_type t) {
    Gdk::Color c;
    switch (t) {
        case I:
            c.set_rgb(0.0, 1.0, 1.0);
            break;
        case O:
            c.set_rgb(1.0, 1.0, 0.0);
            break;
        case T:
            c.set_rgb(1.0, 1.0, static_cast<gushort>(0.4));
            break;
        case L:
            c.set_rgb(1.0, static_cast<gushort>(0.4), 1.0);
            break;
        case J:
            c.set_rgb(static_cast<gushort>(0.4), static_cast<gushort>(0.4), 1.0);
            break;
        case Z:
            c.set_rgb(1.0, static_cast<gushort>(0.4), static_cast<gushort>(0.4));
            break;
        case S:
            c.set_rgb(static_cast<gushort>(0.4), 1.0, static_cast<gushort>(0.4));
            break;
        case NONE:
            c.set_rgb(0.0, 0.0, 0.0);
            break;
    }

    return c;
}