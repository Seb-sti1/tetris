# tetris

This is a beautiful tetris that you'll be able to play in multiplayer!

<img style="align-content: center" src="images/tetris.png">

# Development

## Use-Case

* The user can start a game. Then the tetris grid appears and some random pieces (I, O, T, L, J
Z, S) are generated. The player can move the piece horizontally and rotate them and every tick the
piece goes down. When the piece collides with either the floor or another piece, it stops and is
blocked in place and a new piece is generated at the top of the grid. Every time a line is full
it is remove and the player earn points (more points if multiples lines are removed at the same 
time). Points allow the player to gain levels, the more the levels is high the more the pieces
fall rapidly. 
* The user can start a multiplayer game. Then other players can join the game and play along.
The pieces generated will be the same for all the players.

## Functional Design

* start the game
* Generate random pieces (in a way that would be easy to transmit on a network)
* The game routine : the piece fall and the player control the movements
* Remove the complete lines and add points to the score

* start a multiplayer game
* Retrieve the status of the game
* The server can send the random generator and start the game

## How it works

```mermaid
flowchart TB

    O(startGame \nstate = IN_GAME)
    A(gameLoop \nwhile state == IN_GAME)
    C(Lecture des inputs acquis)
    F(Application du mouvement si valide lié à l'input)
    G(MàJ de l'affichage)
    H{Tetromino doit tomber ?}
    H2(Le tetromino descend)
    I{Collision ?}
    J(Comptage des lignes validées + MàJ Score/Level)
    K{Place pour un \nnouveau tetromino ?}
    L(Nouveau tetromino à jouer \n+ tetromino à venir)
    M(Tetromort stopGame : \nstate = WAITING \n+ remise à zéro de game)

    O --> A
    A --> C 
    C --> F
    F --> G 

    G --> H  
    H2 --> I 
    H -->|Oui| H2
    H --> |Non| A
    I -->|Oui : Le tetromino a touché le fond| J
    I -->|Non| A
    J --> K
    K -->|Oui| L
    K --> |Non : Tetromort| M
    L --> A
```

```mermaid
flowchart LR
    I[État actuel]
    A[Vers page de jeu et MàJ du texte]
    B[MàJ la liste des joueurs]
    D[Affichage de la page de fin\net MàJ du texte des scores]
    C[Affichage de la page de fin\navec le leaderboard]

    I -->|Game.state == IN_GAME| A
    I -->|Game.state == WAITING && page == MULTI| B
    I -->|Game.state == FINISH && !isMulti| D
    I -->|Game.state == FINISH && isMulti| C
```


<img style="align-content: center" src="images/home.png" width="300">
<img style="align-content: center" src="images/multi.png" width="300">
<img style="align-content: center" src="images/help.png" width="300">

```mermaid
sequenceDiagram
    participant Alice (S)
    
    Bob->>Alice (S): Player data (Bob)
    Alice (S)->>Bob: Player data (Alice)

    loop
    Alice (S)->>+Bob: Get player data
    Alice (S)->>Bob: Player data (Alice)
    
    Bob->>-Alice (S): Player data (Bob)
    end

    Note right of Alice (S): Alice lance la partie

    Alice (S)->>Bob: Game start

    Note right of Alice (S): Alice termine la partie

    Alice (S)->>Bob: Disconnect
```


```mermaid
sequenceDiagram
    participant Bob
    participant Alice (S)
    participant Carole
    
    loop
    Alice (S)->>+Bob: Get player data
    Alice (S)->>Bob: Player data (Alice)
    Alice (S)->>+Carole: Get player data
    Alice (S)->>Carole: Player data (Alice)
    
    Bob->>+Alice (S): Player data (Bob)
    deactivate Bob
    Alice (S)->>Carole: Player data (Bob)
    deactivate Alice (S)
    Carole->>Alice (S): Player data (Carole)
    deactivate Carole
    activate Alice (S)
    Alice (S)->>Bob: Player data (Carole)
    deactivate Alice (S)
    end
```


# Installation

You need at least cmake version 3.16

Install GTK :
- `sudo apt install libgtkmm-3.0-dev`

# Build

```bash
mkdir build; cd build

cmake ..
make
./tetris
```

# Useful links

- [gtkmm with CMake](https://stackoverflow.com/questions/46791091/how-to-set-up-cmakelists-with-gtk)
