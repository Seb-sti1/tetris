#pragma once

#include <ctime>
#include "tetromino.h"
#include <vector>
#include <random>
#include <thread>
#include <ctime>
#include <chrono>

enum GameState {WAITING, IN_GAME};

class Game {

public:
    // Attributes
    Matrix<tetromino_type> matrix; // Matrix of the game 20*10

    // Constructor
    Game();
    // Destructor
    //~Game();

    /**
     * Start the game. Will generate the first piece and
     * start the game loop
     * @param seed the seed of the random piece generator
     */
    void startGame(long seed);


private:
    /**
     * Current state of the game. When IN_GAME the gameLoop function
     * should be running
     */
    GameState state;

    /**
     * Date of start of the game
     */
    time_t start_date;

    /**
     * Current level of the game
     */
    unsigned int level;
    /**
     * Current score of the game
     */
    unsigned int score;
    /**
     * The number of completed lines
     */
    unsigned int completed_lines;

    /**
     * The current tetromino controlled by the user
     */
    Tetromino current_tetromino;
    /**
     * The next tetromino (displayed in the corner of the frame)
     */
    Tetromino next_tetromino;

    /**
     * The distribution to generate the pieces
     */
    std::uniform_int_distribution<> distrib;
    /**
     * The random generator
     */
    std::mt19937 gen;
    Tetromino generateTetromino();

    /**
     * The thread use to run the game loop
     */
    std::thread gameLogicThread;
    /**
     * The game loop function. TODO
     */
    void gameLoop();

    /**
     * The last date when a piece was move downward.
     */
    std::chrono::system_clock::time_point lastFallDate;
    /**
     * @return The function that calculate the delay before a piece should fall
     */
    double getPieceFallDelay() const;

    /**
     * When a tetromino has landed :
     *  - check for completed lines
     *  - change current_tetromino
     */
    void tetrominoHasLanded();

    /**
     * Draw or undraw a the tetromino t in the matrix
     * @param t the tetromino
     * @param draw if it should draw or undraw the tetromino
     */
    void drawTetromino(Tetromino t, bool draw);

};