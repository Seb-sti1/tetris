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
        next_tetromino(NONE),
        next_tetromino_matrix(TETROMINO_ROWS, TETROMINO_COLS)
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
    Tetromino t(static_cast<tetromino_type>(distrib(gen)),
                0,0, UP);

    t.x = -t.getSpawningX();

    return t;
}

void Game::startGame(long seed)
{
    state = IN_GAME;

    gen = std::mt19937(seed);
    start_date = std::time(nullptr);

    // generate the first two tetrominos
    current_tetromino = generateTetromino();
    next_tetromino = generateTetromino();

    auto collision = next_tetromino.get_collision_matrix();
    for (int i = 0; i < collision.getNumRows(); i++) {
        for (int j = 0; j < collision.getNumColumns(); j++) {
            next_tetromino_matrix.To(i, j, (collision.At(i, j)) ? next_tetromino.type : NONE);
        }
    }

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
            if (level < 20)
                return 0.0333;
            return 0.0166;
    }
}

unsigned Game::getScore(int completedLines) const
{
    switch (completedLines) {
        case 1:
            return 40*(level + 1);
        case 2:
            return 100*(level + 1);
        case 3:
            return 300*(level + 1);
        case 4:
            return 1200*(level + 1);
        default:
            return 0;
    }
}

int Game::checkForCompletedLines()
{
    int completeLine = -1;

    for (int i = matrix.getNumRows() - 1; i >= 0; i--)
    {
        bool complete = true;

        // Try to find a complete line starting from the ground
        for (int j = 0; j < matrix.getNumColumns(); j++)
        {
            if (matrix.At(i, j) == NONE)
            {
                complete = false;
                break;
            }
        }

        // exit the loops when such line found
        if (complete)
        {
            completeLine = i;
            break;
        }
    }

    // if a complete line was found
    if (completeLine != -1)
    {
        // copy the line above
        for (int i = completeLine; i > 0; i--)
        {
            matrix.Print();
            for (int j = 0; j < matrix.getNumColumns(); j++)
            {
                matrix.To(i, j, matrix.At(i - 1,j));
            }
        }

        // reset the top line
        for (int j = 0; j < matrix.getNumColumns(); j++)
        {
            matrix.To(0, j, NONE);
        }

        return checkForCompletedLines() + 1;
    }


    return 0;
}



void Game::tetrominoHasLanded()
{
    std::cout << "Tetromino has landed" << std::endl;
    // TODO change level
    auto numberOfCompletedLines = checkForCompletedLines();

    completed_lines += numberOfCompletedLines;
    score += getScore(numberOfCompletedLines);

    current_tetromino = next_tetromino; // TODO check for memory leak

    if (current_tetromino.verify_move_validity(matrix))
    {// possible to spawn
        next_tetromino = generateTetromino();

        auto collision = next_tetromino.get_collision_matrix();
        for (int i = 0; i < collision.getNumRows(); i++) {
            for (int j = 0; j < collision.getNumColumns(); j++) {
                next_tetromino_matrix.To(i, j, (collision.At(i, j)) ? next_tetromino.type : NONE);
            }
        }

        // draw current_tetromino
        drawTetromino(current_tetromino, true);
    }
    else
    {
        // this state will be detected by the window
        // that will change to the after game screen
        state = FINISH;
    }

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
                    // TODO verify that the next line properly works (spoiler it doesn't and its behaviour has to be corriged)
                    new_current_tetromino.orientation = static_cast<orient>((new_current_tetromino.orientation+1)%7); // 7 tetromino types
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

    keyQueue.empty();

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
