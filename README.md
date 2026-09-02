Maze Generator & Pathfinding Visualizer

A real-time maze generation and pathfinding visualizer built with C++ and Raylib.

This project demonstrates how fundamental algorithms and data structures can be applied to an interactive grid-based environment. It focuses on procedural maze generation, graph traversal, backtracking, path reconstruction, and finite state machines (FSM) through real-time visualization.

The application allows users to generate randomized mazes and visually compare Breadth-First Search (BFS) and Depth-First Search (DFS) pathfinding behavior.

Features
Maze Generation

The maze is generated using a randomized, stack-based Depth-First Search backtracking algorithm.

Randomized neighbor selection
Stack-based backtracking
Four-directional wall management
Step-by-step generation visualization
Generates a perfect maze
Real-time algorithm visualization
Breadth-First Search

BFS is implemented to find the shortest path through the generated unweighted maze.

Uses std::queue
Tracks visited cells
Stores parent relationships
Reconstructs the final path
Visualizes the search process in real time
Guarantees the shortest path when all movements have equal cost
Depth-First Search

DFS is implemented as an alternative pathfinding algorithm to demonstrate depth-oriented graph traversal.

Uses std::stack
Performs depth-first traversal
Tracks visited cells
Stores parent relationships
Reconstructs the discovered path
Provides a direct comparison with BFS traversal behavior
Does not guarantee the shortest path in a general unweighted graph
Finite State Machine

A simple Finite State Machine (FSM) controls the application's workflow and prevents incompatible operations from running simultaneously.

+-----------+
|   IDLE    |
+-----+-----+
      |
      v
+-------------------+
|  GENERATE MAZE    |
+---------+---------+
          |
          v
+-------------------+
|     WAITING       |
+---------+---------+
          |
       +--+--+
       |     |
       v     v
     +---+ +---+
     |BFS| |DFS|
     +---+ +---+
       |     |
       +--+--+
          |
          v
+-------------------+
|     WAITING       |
+-------------------+


Application states:

FASE_IDLE
FASE_GENERATE_MAZE
FASE_MENUNGGU
FASE_BFS_JALAN
FASE_DFS_JALAN


The state system keeps maze generation, pathfinding, user interaction, and rendering flow predictable and prevents multiple algorithms from running at the same time.

Architecture

The application uses a grid-based representation of the maze and several fundamental C++ standard library data structures.

Component	Purpose
cell	Stores cell state and wall information
GridPos	Represents a grid coordinate
std::stack	Used for maze generation and DFS traversal
std::queue	Used for BFS traversal
std::vector	Stores temporary neighbors and reconstructed paths
GameState	Controls the current application state
CustomButton	Handles UI interaction
Peta	Stores the maze grid
AsalUsulBFS	Stores BFS parent relationships
AsalUsulDFS	Stores DFS parent relationships
Algorithms
1. Maze Generation

The maze generator uses randomized DFS backtracking.

The algorithm follows this general process:

Start
  |
  v
Mark current cell as visited
  |
  v
Find unvisited neighbors
  |
  v
Choose a random neighbor
  |
  v
Remove wall between cells
  |
  v
Push neighbor onto stack
  |
  v
Repeat
  |
  +---- No neighbors ----> Pop stack
                              |
                              v
                           Backtrack


The process continues until every cell has been visited.

By removing walls during DFS traversal and backtracking, the generator produces a perfect maze: a maze in which every cell is reachable and there is exactly one path between any two cells.

2. Breadth-First Search

BFS explores the maze level by level using a queue.

Start
  |
  v
Queue
  |
  +--> Neighbor
  |
  +--> Neighbor
  |
  +--> Neighbor
          |
          v
       Continue


Whenever a cell is discovered, its predecessor is stored in AsalUsulBFS.

Once the target is reached, the final path is reconstructed by following the parent relationships from the target back to the starting position.

Target
  |
  v
Parent
  |
  v
Parent
  |
  v
Start


Since every movement in the maze has the same cost, BFS guarantees the shortest path.

3. Depth-First Search

DFS explores the maze by following one branch as deeply as possible before backtracking.

A stack is used to manage the traversal, while AsalUsulDFS stores predecessor relationships for path reconstruction.

Unlike BFS, DFS does not guarantee the shortest path. Its primary purpose in this project is to demonstrate and visualize the difference between depth-first and breadth-first graph traversal.

Tech Stack
Language: C++
Graphics Library: Raylib
Data Structures: std::vector, std::stack, std::queue, 2D arrays
Algorithms: DFS, BFS, randomized backtracking
Concepts: Graph Traversal, Procedural Generation, Path Reconstruction, Finite State Machines
Rendering: Raylib 2D primitives
UI: Custom immediate-mode UI
Requirements

Before building the project, make sure the following are installed and configured:

A C++ compiler
GCC / MinGW
Clang
MSVC
Raylib
A configured C++ development environment
Building
GCC / MinGW

Example compilation command for Windows:

g++ main.cpp -o PathfindingVisualizer.exe -O2 -Wall -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm


The exact command may need to be adjusted depending on your Raylib installation, directory structure, and compiler configuration.

Running

After successfully compiling the project, run:

PathfindingVisualizer.exe

Usage
Launch the application.
Select Generate Maze.
Wait until maze generation is complete.
Select Start BFS to visualize Breadth-First Search.
Select Start DFS to visualize Depth-First Search.
Select Generate Maze again to reset the board and generate a new maze.
Visualization
Element	Color
Maze background	Light
Maze walls	Dark
Start position	Red
Target position	Green
BFS exploration	Blue
BFS path	Yellow
DFS exploration	Red
DFS path	Purple

The visualization is designed to make the behavior of each algorithm observable while it is running rather than only displaying the final result.

Project Structure

The current implementation is intentionally kept compact, with most application logic contained in:

main.cpp


The project may be refactored into separate headers, source files, and modules as development continues.

Learning Objectives

This project was created as a practical exercise to understand and visualize:

C++ Standard Library data structures
Stack-based algorithms
Queue-based algorithms
Graph traversal
DFS backtracking
Path reconstruction
Grid-based graph representation
Procedural maze generation
Finite State Machines
Frame-based algorithm visualization
Basic UI implementation with Raylib

Rather than treating the algorithms as purely theoretical concepts, the project provides a visual representation of how they behave step by step.

Current Limitations

The current implementation is intentionally focused on learning and algorithm visualization.

Most application logic is contained in main.cpp
Grid dimensions are defined as compile-time constants
Cell size is fixed
Build configuration relies on compiler commands
No CMake configuration
Algorithm statistics are not currently displayed
Rendering and algorithm logic are not yet fully separated
No automated test suite
Future Improvements

Planned or potential improvements include:

Refactor the code into multiple classes and source files
Add CMake build configuration
Display path length and visited-node statistics
Support configurable grid dimensions
Add animation speed controls
Implement Dijkstra's algorithm
Implement A* pathfinding
Improve separation between rendering and algorithm logic
Add automated tests
Improve cross-platform build support
License

This project is currently intended as a personal learning and algorithm visualization project.

If you plan to distribute, modify, or reuse this project, add an appropriate open-source license to the repository.