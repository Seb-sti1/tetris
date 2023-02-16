#pragma once

#include <ctime>
#include "tetromino.h"
#include <vector>
#include <random>
#include <thread>
#include <ctime>
#include <chrono>
#include <queue>
#include <mutex>

enum GameState {WAITING, IN_GAME, DEAD, FINISH};

class Game {

public:
    /**
     * Current state of the game. When IN_GAME the gameLoop function
     * should be running
     */
    GameState state;

    /**
     * The game matrix. It contains all tetrominos (also the one currently played)
     */
    Matrix<tetromino_type> matrix; // Matrix of the game 20*10

    /**
     * The matrix of the next tetromino for preview
     */
    Matrix<tetromino_type> next_tetromino_matrix;// TODO change this


    /**
     * Current level of the game
     */
    unsigned int level;
    /**
     * The number of completed lines
     */
    unsigned int completed_lines;
    /**
     * Current score of the game
     */
    unsigned int score;

    /**
     * The game object that
     */
    Game();

    /**
     * Start the game. Will generate the first piece and
     * start the game loop
     * @param seed the seed of the random piece generator
     */
    void startGame(long seed);

    /**
     * Indicate that the player leaved the game page
     */
    void stopGame();

    /**
     * @param direction when a player press a arrow key of the keyboard
     */
    void registerKeyPress(orient direction);

private:
    /**
     * Date of start of the game
     */
    time_t start_date;




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
    /**
     * @return a new random tetromino
     */
    Tetromino generateTetromino();




    /**
     * The thread use to run the game loop
     */
    std::thread gameLogicThread;
    /**
     * The game loop function.
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
     * Calculate the score to add when completing completedLines
     * @param completedLines the number of lines just completed
     * @return the score to add
     */
    unsigned getScore(int completedLines) const;

    /**
     * When a tetromino has landed :
     *  - check for completed lines
     *  - change current_tetromino
     */
    void tetrominoHasLanded();
    int checkForCompletedLines();



    /**
     * Draw or undraw a the tetromino t in the matrix
     * @param t the tetromino
     * @param draw if it should draw or undraw the tetromino
     */
    void drawTetromino(const Tetromino& t, bool draw);


    /**
     * The queue that stores the key pressed
     */
    std::queue<orient> keyQueue;
    /**
     * The mutex to coordinate the mutex
     */
    std::mutex queueMutex;
    /**
     * @return the last key pressed by the user
     */
    orient getKeyPress();
};