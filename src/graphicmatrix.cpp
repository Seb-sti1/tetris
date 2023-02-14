#include <cairomm/context.h>
#include <gdkmm/color.h>

#include "graphicmatrix.h"

#define w 20
#define h 20
#define w_space 4
#define h_space 4

GraphicMatrix::GraphicMatrix(Matrix<tetromino_type>& matrix) : matrix(matrix)
{
    this->set_margin_top(15);

    this->set_size_request((w + w_space) * ((int) matrix.getNumColumns()),
                     (h + h_space) * ((int) matrix.getNumRows()));
}

/**
 * The callback function to draw the matrix
 * @param cr the context (a class from GtK lib)
 * @return drawing successful
 */
bool GraphicMatrix::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    for (int i = 0; i < matrix.getNumRows(); i++) {
        for (int j = 0; j < matrix.getNumColumns(); j++) {
            Gdk::Color c = tetrominoTypeToColor(matrix.At(i, j));

            cr->set_source_rgba(c.get_red_p(), c.get_green_p(), c.get_blue_p(), 1.0);   // green
            cr->rectangle((w + w_space)*j, (h + h_space)*i, w, h);
            cr->fill();
        }
    }
    cr->stroke();

    return true;
}


Gdk::Color tetrominoTypeToColor(tetromino_type t) {
    Gdk::Color c;
    switch (t) {
        case I:
            c.set_rgb_p(0.0, 1.0, 1.0);
            break;
        case O:
            c.set_rgb_p(1.0, 1.0, 0.0);
            break;
        case T:
            c.set_rgb_p(1.0, 1.0, 0.4);
            break;
        case L:
            c.set_rgb_p(1.0, 0.4, 1.0);
            break;
        case J:
            c.set_rgb_p(0.4, 0.4, 1.0);
            break;
        case Z:
            c.set_rgb_p(1.0, 0.4, 0.4);
            break;
        case S:
            c.set_rgb_p(0.4, 1.0, 0.4);
            break;
        case NONE:
            c.set_rgb_p(0.3, 0.3, 0.3);
            break;
    }

    return c;
}