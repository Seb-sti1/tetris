//
// Created by seb on 01/02/23.
//
#include "game.h"


Game::Game() :
        matrix(20, 10),
        distrib(1, 7),
        level(0),
        score(0),
        completed_lines(0),
        current_tetromino(NONE),
        next_tetromino(NONE)
{
    state = WAITING;

    // TODO init matrix to a default value ?
    for (int i = 0; i < matrix.getNumRows(); i++) {
        for (int j = 0; j < matrix.getNumColumns(); j++) {
            matrix.To(i, j, NONE);
        }
    }
}

Tetromino Game::generateTetromino()
{
    return {static_cast<tetromino_type>(distrib(gen)),
                     0,0, UP};
}

void Game::startGame(long seed)
{
    state = IN_GAME;

    gen = std::mt19937(seed);
    start_date = std::time(nullptr);

    // generate the first two tetrominos
    current_tetromino = generateTetromino();
    next_tetromino = generateTetromino();

    drawTetromino(current_tetromino, true);
    lastFallDate = std::chrono::system_clock::now();

    // start game loop
    gameLogicThread = std::thread(&Game::gameLoop, this);
    gameLogicThread.detach();
}


double Game::getPieceFallDelay() const
{
    // use for the timings https://harddrop.com/wiki/Tetris_(NES,_Nintendo)
    switch (level) {
        case 0:
            return 0.8;
        case 1:
            return 0.7167;
        case 2:
            return 0.6333;
        case 3:
            return 0.55;
        case 4:
            return 0.4667;
        case 5:
            return 0.333;
        case 6:
            return 0.3;
        case 7:
            return 0.21666;
        case 8:
            return 0.133;
        case 9:
            return 0.1;
        case 10:
        case 11:
        case 12:
            return 0.083;
        case 13:
        case 14:
        case 15:
            return 0.0667;
        case 16:
        case 17:
        case 18:
            return 0.05;
        default:
            if (level < 2)
                return 0.0333;
            return 0.0166;
    }
}

void Game::tetrominoHasLanded()
{
    std::cout << "Tetromino has landed" << std::endl;
    // TODO check for completed lines (+ move down + score)

    current_tetromino = next_tetromino; // TODO check for memory leak
    next_tetromino = generateTetromino();

    // draw current_tetromino
    drawTetromino(current_tetromino, true);
}

void Game::gameLoop()
{

    while (state == IN_GAME)
    {

        if (!keyQueue.empty()) // only read access so no collision issues
        {
            std::cout << "Should move" << std::endl;

            // If there is any move + collision check
            orient direction = getKeyPress();
            // TODO rotation

            // move the piece
            auto new_current_tetromino(current_tetromino);

            switch (direction) {
                case UP:
                    break;
                case RIGHT:
                    new_current_tetromino.y++;
                    break;
                case DOWN:
                    new_current_tetromino.x++;
                    break;
                case LEFT:
                    new_current_tetromino.y--;
                    break;
            }

            // undraw current_tetromino : necessary for the validity check
            drawTetromino(current_tetromino, false);

            if (new_current_tetromino.verify_move_validity(matrix))
            {
                current_tetromino = new_current_tetromino;
            }

            // draw the new (if valid) state or the old one otherwise
            drawTetromino(current_tetromino, true);
        }


        std::chrono::duration<double> durationSinceLastFall = std::chrono::system_clock::now() - lastFallDate;
        if (durationSinceLastFall.count() > getPieceFallDelay()) {
            lastFallDate = std::chrono::system_clock::now();

            // move the piece downward
            auto new_current_tetromino(current_tetromino);
            new_current_tetromino.x++;

            // undraw current_tetromino : necessary for the validity check
            drawTetromino(current_tetromino, false);

            std::cout << "Tetromino is falling" << std::endl;

            if (new_current_tetromino.verify_move_validity(matrix))
            {
                // change the tetromino
                current_tetromino = new_current_tetromino; // TODO check for memory leak
                // draw (new) current_tetromino
                drawTetromino(current_tetromino, true);
            }
            else
            {
                // redraw current_tetromino (without moving it)
                drawTetromino(current_tetromino, true);
                // when the tetromino touch the ground
                tetrominoHasLanded();
            }
        }
    }
}

void Game::drawTetromino(Tetromino t, bool draw)
{
    auto collision = t.get_collision_matrix();

    for (int i = 0; i < collision.getNumRows(); i++)
    {
        for (int j = 0; j < collision.getNumColumns(); j++)
        {
            if (collision.At(i, j))
            {
                matrix.To(t.x + i, t.y + j, (draw) ? t.type : NONE);
            }
        }
    }
}

void Game::stopGame() {
    state = WAITING;

    for (int i = 0; i < matrix.getNumRows(); i++) {
        for (int j = 0; j < matrix.getNumColumns(); j++) {
            matrix.To(i, j, NONE);
        }
    }
}

void Game::registerKeyPress(orient direction) {
    // need to lock the mutex (this is executed in the graphic thread)
    std::unique_lock<std::mutex> lck(queueMutex);

    keyQueue.push(direction);
}

orient Game::getKeyPress() {
    // need to lock the mutex (this is executed in gameLogicThread)
    std::unique_lock<std::mutex> lck(queueMutex);

    orient direction = keyQueue.front();
    keyQueue.pop();

    return direction;
}
