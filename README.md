# Chess Game in C++ 
A chess game built using C++ with Qt for a graphical user interface. 
This project offers a classic chess experience, where two players can play according to traditional chess rules. 
The game includes a fully functional chessboard, player-controlled piece movements, game state management, and a simple, intuitive interface.

## Overview
This chess game project is developed using C++ and Qt, featuring:

- A standard 8x8 chessboard.
- Fully implemented movements for all selected chess pieces.
- Player turn system with indicators.
- Game state tracking, including check conditions.

This game was created to provide a complete chess experience with basic functionalities, allowing two players to play directly on the computer interface. It also offers special game indicators like the current player turn and a warning for check.

## Table of Content
- [Project Structure](#project-structure)
- [Gameplay](#gameplay)
- [Learning Experience](#learning-experience)

## Project Structure
This project has a modular structure with three main classes: ``Board``, ``Piece``, and ``Project``. Each of these classes plays a distinct role:

- ### ``Board`` __Class__:
  
  - __Purpose__: Acts as the manager for all chess pieces. It oversees and ensures the correct placement and movement of pieces.
  - __Responsibilites__:
    
    - Keeps track of piece positions
    - Validates the number of pieces in the board
    - Manages the state of the board, including checking the game situation and tracking available moves for each piece

- ### ``Square`` __Class__:
  
  - __Purpose__: Defines the state of a case in the board. The board as a list of squares, which themselves can possess a piece, or be empty.

- ### ``Piece`` __Class__:
  
  - __Purpose__: Defines the attributes and possible movements of each chess piece.
  - __Responsibilites__:
    
    - Stores essential attributes for each piece, such as its type, color, and current position.
    - Implements movement logic specific to each piece type (e.g., bishops can move diagonally).
    - Interacts with ``Board`` to ensure that movements respect chess rules.
      
- ### ``Project`` __Class__:
  
  - __Purpose__: Manages the user interface and interactions, handling the Qt components of the project.
  - __Responsibilites__:
    
    - Connects with the ``Board`` and ``Piece`` classes to reflect the game state on the UI.
    - Responds to user interactions, like selecting and moving pieces.
    - Provides features such as restart and visual feedback for moves and game states.
   
## Gameplay
The game follows traditional chess rules, allowing players to move pieces (kings, bishops and rooks) with standard movements. 

### Features
The game's UI is pretty straightfoward with its controls. It includes:
- __Piece Movements__: Implemented according to standard chess logic.
- __Turn-Based System__: Alternates between White and Black players, with an indicator of turn on the right
- __Check Indicator__: Notifies the players when the king is in check
> Note: Some advanced moves (like _castling_ and _en passant_) may not be fully implemented.

### Home Screen
![image](https://github.com/user-attachments/assets/7c5b62ce-4659-458d-9ba6-4f6c04fd42e5)
> Displays the initial view of the chessboard and game controls, allowing users to start a new game.

### Piece Movement
![image](https://github.com/user-attachments/assets/dba11ddb-374b-4c00-b56b-fdfd4150d9a4)
> Shows the selection and movement of a piece on the board. The board updates in real-time to reflect valid moves based on the chess rules.

### Check Indicator
![image](https://github.com/user-attachments/assets/870f6665-ad6e-4f5f-82ba-e527c8fab632)
> Demonstrates the check warning, where text is shown in red to alert the player of potential check conditions.

### Restart and Menu
![image](https://github.com/user-attachments/assets/9f485967-c759-4fce-bc49-03b1554c9bfd)
> Provides access to the restart button for resetting the game to its initial state, and choosing between initial game situations.
   
## Learning Experience
This project served as an introduction to GUI development in Qt and enhanced my understanding of object-oriented programming in C++. 
Developing this game allowed me to explore event handling, piece movement logic, and efficient ways to manage a game state. 
