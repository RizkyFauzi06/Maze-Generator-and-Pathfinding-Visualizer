Maze Generator & Pathfinding Visualizer

A real-time maze generation and pathfinding visualizer built with C++ and Raylib.

This project demonstrates procedural maze generation and graph traversal through an interactive grid-based visualization. It focuses on fundamental concepts such as DFS, BFS, stacks, queues, path reconstruction, and finite state machines.

Features
Maze Generation

Generates a randomized perfect maze using a stack-based Depth-First Search (DFS) backtracking algorithm.

Randomized neighbor selection
Stack-based backtracking
Four-directional wall management
Step-by-step generation visualization
Perfect maze generation
Breadth-First Search

Visualizes Breadth-First Search (BFS) for shortest-path finding in an unweighted maze.

Uses std::queue
Tracks visited cells
Stores parent relationships
Reconstructs the final path
Visualizes the search process in real time
Guarantees the shortest path in the generated unweighted maze
Depth-First Search

Visualizes Depth-First Search (DFS) as a pathfinding algorithm.

Uses std::stack
Performs depth-oriented traversal
Tracks visited cells
Stores parent relationships
Reconstructs the discovered path
Allows direct comparison with BFS traversal behavior
Finite State Machine

The application uses a simple Finite State Machine (FSM) to control the different stages of the application.

+-----------+
|   IDLE    |
+-----+-----+
      |
      v
+-------------------+
| GENERATE MAZE     |
+---------+---------+
          |
          v
+-------------------+
|      WAITING      |
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
|      WAITING      |
+-------------------+


Application states:

FASE_IDLE
FASE_GENERATE_MAZE
FASE_MENUNGGU
FASE_BFS_JALAN
FASE_DFS_JALAN


The state system prevents incompatible operations from running simultaneously and keeps the generation, searching, and rendering flow predictable.

Architecture

The project is built around fundamental C++ data structures and a grid-based representation of the maze.

Component	Purpose
cell	Stores cell state and wall information
GridPos	Represents a grid coordinate
std::stack	Maze generation and DFS traversal
std::queue	BFS traversal
std::vector	Temporary neighbors and reconstructed paths
GameState	Controls application states
CustomButton	Handles UI interaction
Peta	Stores the maze grid
AsalUsulBFS	Stores BFS parent relationships
AsalUsulDFS	Stores DFS parent relationships
Algorithms
1. Maze Generation

The maze generator uses randomized DFS backtracking.

The basic process is:

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


The process continues until all cells have been visited.

Because the generator removes walls while performing DFS backtracking, the resulting structure forms a perfect maze.

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


Each discovered cell stores its predecessor in AsalUsulBFS.

When the target is reached, the algorithm reconstructs the path by following the predecessor relationships from the target back to the start.

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


Because every movement has the same cost, BFS produces the shortest path in this maze.

3. Depth-First Search

DFS uses a stack to explore the maze depth-first.

When no valid unvisited neighbor exists, the algorithm backtracks by popping the current position from the stack.

Like BFS, DFS stores predecessor information in AsalUsulDFS to reconstruct the discovered route.

Unlike BFS, DFS does not guarantee the shortest path in a general unweighted graph.

Tech Stack
Language: C++
Graphics Library: Raylib
Data Structures: std::vector, std::stack, std::queue, 2D arrays
Concepts: Graph Traversal, Backtracking, Procedural Generation, FSM
Rendering: Raylib 2D primitives
UI: Custom immediate-mode UI
Requirements

Before building the project, make sure you have:

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


The exact command may need to be adjusted depending on your Raylib installation and compiler configuration.

Running

After compilation:

PathfindingVisualizer.exe

Usage
Launch the application.
Click Generate Maze.
Wait until maze generation is complete.
Click Start BFS to visualize BFS traversal.
Click Start DFS to visualize DFS traversal.
Click Generate Maze again to reset the board and create a new maze.
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
Project Structure

Learning Objectives

This project was created to practice:

C++ standard library data structures
Stack-based algorithms
Queue-based algorithms
Graph traversal
Backtracking
Path reconstruction
Grid-based graph representation
Procedural maze generation
Finite State Machines
Frame-based algorithm visualization
Basic UI implementation with Raylib
Current Limitations

The current implementation is intentionally focused on learning and visualization.

Most application logic is contained in main.cpp.
Grid dimensions are compile-time constants.
Cell size is fixed.
Build configuration is compiler-command based.
There is currently no CMake configuration.
Algorithm statistics are not yet displayed.
Future Improvements

Potential improvements for future iterations include:

 Refactor the code into multiple classes and source files
 Add CMake build configuration
 Add path length and visited-node statistics
 Add configurable grid dimensions
 Add animation speed controls
 Add Dijkstra's algorithm
 Add A* pathfinding
 Improve separation between rendering and algorithm logic
 Add automated tests
 Improve cross-platform build support
License

This project is currently intended as a personal learning and algorithm visualization project.

If you plan to distribute or reuse the project, add an appropriate license to the repository.