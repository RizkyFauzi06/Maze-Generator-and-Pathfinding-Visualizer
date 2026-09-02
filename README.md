Bisa. Kalau maksudmu jangan pakai writing block/editor, tapi langsung berikan dalam Markdown/code biasa yang bisa di-copy ke README.md di platform apa pun, berikut formatnya.

# Maze Generator & Pathfinding Visualizer

An interactive maze generation and pathfinding visualizer built with **C++** and **Raylib**.

This project demonstrates how fundamental algorithms and data structures can be applied to a grid-based environment through real-time visualization. It combines **procedural maze generation, graph traversal, backtracking, path reconstruction, and finite state machines** into an interactive application.

The system allows users to generate randomized mazes and visualize how **Breadth-First Search (BFS)** and **Depth-First Search (DFS)** explore the maze and construct paths to a target.

> **Note:** This project was developed as a learning project to explore graph algorithms, data structures, procedural generation, and real-time visualization using C++ and Raylib.

## Overview

Maze Generator & Pathfinding Visualizer was developed as a practical project for understanding graph algorithms and fundamental C++ data structures through visual interaction.

The application consists of two main algorithmic stages:

1. **Maze Generation** — creates a randomized perfect maze using stack-based DFS backtracking.
2. **Pathfinding** — searches for a route between the start and target positions using either BFS or DFS.

Each algorithm runs incrementally across rendering frames, allowing the user to observe the traversal and decision-making process in real time.

A simple **Finite State Machine (FSM)** controls the application flow and ensures that maze generation, pathfinding, user interaction, and rendering operate in predictable states.

## Key Features

- Randomized perfect maze generation
- Stack-based DFS backtracking
- Randomized neighbor selection
- Four-directional wall management
- Step-by-step maze generation
- Breadth-First Search pathfinding
- Depth-First Search pathfinding
- Shortest-path reconstruction with BFS
- Parent relationship tracking
- Real-time traversal visualization
- Finite State Machine for application flow
- Interactive custom UI
- Grid-based maze representation
- Visual comparison between BFS and DFS

## Algorithm Architecture

The application follows a multi-stage algorithmic pipeline:

```text
Application Start
       |
       v
     IDLE
       |
       v
 Generate Maze
       |
       v
Randomized DFS
 Backtracking
       |
       v
  Maze Complete
       |
       v
    WAITING
       |
    +--+--+
    |     |
    v     v
   BFS   DFS
    |     |
    +--+--+
       |
       v
Path Reconstruction
       |
       v
  Display Result
       |
       v
    WAITING


The state machine prevents incompatible operations from running simultaneously. For example, pathfinding cannot begin while the maze is still being generated.

Maze Generation

The maze generator uses a randomized Depth-First Search backtracking algorithm implemented with std::stack.

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
Continue traversal
  |
  +---- No unvisited neighbors ----+
                                    |
                                    v
                              Pop from stack
                                    |
                                    v
                                Backtrack


The process continues until every cell in the grid has been visited.

Because the generator removes walls while traversing and backtracking, the resulting maze forms a perfect maze.

A perfect maze has:

Every cell reachable from every other cell
No isolated regions
Exactly one path between any two cells
Breadth-First Search

BFS is implemented to demonstrate shortest-path traversal in an unweighted grid.

The algorithm uses std::queue and explores cells level by level.

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


Whenever an unvisited cell is discovered, the system records its predecessor in AsalUsulBFS.

Once the target is reached, the path is reconstructed by following the predecessor relationships from the target back to the starting position.

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


Since every movement between adjacent cells has the same cost, BFS guarantees the shortest path in the generated maze.

Depth-First Search

DFS is implemented as an alternative pathfinding algorithm using std::stack.

Instead of exploring the maze level by level, DFS follows one branch as deeply as possible before backtracking.

The traversal process can be summarized as:

Start
  |
  v
Stack
  |
  v
Explore Neighbor
  |
  v
Explore Deeper
  |
  v
No Valid Neighbor
  |
  v
Backtrack


Like BFS, DFS stores predecessor relationships in AsalUsulDFS to reconstruct the discovered path.

However, DFS does not guarantee the shortest path in a general unweighted graph. Its purpose in this project is primarily to demonstrate depth-first traversal and provide a direct visual comparison with BFS.

Finite State Machine

The application uses a simple Finite State Machine to manage its execution flow.

The available states are:

FASE_IDLE
FASE_GENERATE_MAZE
FASE_MENUNGGU
FASE_BFS_JALAN
FASE_DFS_JALAN

State	Purpose
FASE_IDLE	Initial application state
FASE_GENERATE_MAZE	Runs the maze generation algorithm
FASE_MENUNGGU	Waits for user interaction
FASE_BFS_JALAN	Runs BFS pathfinding
FASE_DFS_JALAN	Runs DFS pathfinding

The FSM provides a clear separation between the application's major operations and prevents multiple algorithms from being executed at the same time.

Data Structures

The project uses several fundamental C++ data structures to implement the algorithms.

Data Structure	Usage
std::stack	Maze generation and DFS traversal
std::queue	BFS traversal
std::vector	Temporary neighbor lists and path storage
2D arrays	Grid and cell representation
GridPos	Represents grid coordinates
AsalUsulBFS	Stores BFS predecessor relationships
AsalUsulDFS	Stores DFS predecessor relationships

These structures demonstrate how standard C++ containers can be applied to graph traversal and backtracking problems.

Project Architecture

The maze is represented as a two-dimensional grid.

Each cell stores its state and wall information, while GridPos represents a position within the grid.

The main components are:

Component	Responsibility
cell	Stores cell state and wall information
GridPos	Represents grid coordinates
Peta	Stores the maze grid
AsalUsulBFS	Stores BFS parent relationships
AsalUsulDFS	Stores DFS parent relationships
GameState	Controls the application state
CustomButton	Handles UI interaction

The current implementation keeps most of the application logic in main.cpp to keep the project simple and focused on the underlying algorithms.

Visualization

The application uses different colors to represent the state of the maze and pathfinding process.

Element	Color
Maze background	Light
Maze walls	Dark
Start position	Red
Target position	Green
BFS exploration	Blue
BFS path	Yellow
DFS exploration	Red
DFS path	Purple

The algorithms are processed incrementally across rendering frames so that each stage of the traversal can be observed visually.

Technology Stack
Technology	Purpose
C++	Core programming language
Raylib	Graphics and rendering
std::vector	Dynamic collections and path storage
std::stack	DFS and maze generation
std::queue	BFS traversal
2D Arrays	Grid representation
Custom UI	User interaction
Requirements

Before building the project, make sure the following are installed and configured:

C++ compiler
GCC / MinGW
Clang
MSVC
Raylib
A configured C++ development environment
Building
GCC / MinGW

Example compilation command for Windows:

g++ main.cpp -o PathfindingVisualizer.exe -O2 -Wall -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm


The exact command may need to be adjusted depending on the Raylib installation, compiler, and project directory structure.

Running

After compilation, run:

PathfindingVisualizer.exe

Usage
Launch the application.
Select Generate Maze.
Wait until the maze generation process is complete.
Select Start BFS to visualize Breadth-First Search.
Select Start DFS to visualize Depth-First Search.
Generate a new maze to reset the board and start another visualization.

The application prevents pathfinding from starting while maze generation is still in progress.

Project Structure
Maze-Generator-Pathfinding-Visualizer/
│
├── main.cpp
├── README.md
│
├── include/
│   └── ...
│
├── lib/
│   └── ...
│
└── assets/
    └── screenshots/
        ├── maze-generation.png
        ├── bfs-pathfinding.png
        └── dfs-pathfinding.png


Update the structure above to match the actual repository contents.

Learning Objectives

This project was created to practice and visualize several fundamental Computer Science and C++ concepts:

C++ Standard Library data structures
Stack-based algorithms
Queue-based algorithms
Graph traversal
DFS backtracking
BFS shortest-path traversal
Path reconstruction
Grid-based graph representation
Procedural maze generation
Finite State Machines
Frame-based algorithm visualization
Basic UI implementation with Raylib

The primary goal is to make algorithmic behavior easier to understand by connecting the underlying data structures and algorithms directly to a visual representation.

Current Limitations

The current implementation is intentionally focused on learning and visualization.

Most application logic is contained in main.cpp
Grid dimensions are compile-time constants
Cell size is fixed
Build configuration relies on compiler commands
No CMake configuration
Algorithm statistics are not currently displayed
Rendering and algorithm logic are not fully separated
No automated test suite
Cross-platform build configuration is limited
Future Improvements

Potential improvements for future versions include:

Refactor the application into multiple classes and source files
Add CMake build configuration
Add path length and visited-node statistics
Add configurable grid dimensions
Add animation speed controls
Implement Dijkstra's algorithm
Implement A* pathfinding
Improve separation between rendering and algorithm logic
Add automated tests
Improve cross-platform build support
Add algorithm performance comparison
Add configurable start and target positions
License

This project is currently intended as a personal learning and algorithm visualization project.

If you plan to distribute or reuse the project, add an appropriate open-source license to the repository.