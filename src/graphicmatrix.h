//
// Created by seb on 13/12/22.
//

#ifndef TETRIS_GRAPHICMATRIX_H
#define TETRIS_GRAPHICMATRIX_H

#include <gtkmm/drawingarea.h>
#include "tetromino.h"
#include "matrix.h"

class GraphicMatrix : public Gtk::DrawingArea
{
public:
    GraphicMatrix(Matrix* matrix);
    virtual ~GraphicMatrix();

protected:
    //Override default signal handler:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

private:
    Matrix* matrix;
};


Gdk::Color tetrominoTypeToColor(tetromino_type t);

#endif //TETRIS_GRAPHICMATRIX_H
