# 9Puzzle

‘9Puzzle’ is an Artificial Intelligence program for a tile based puzzle game, in which the goal is to slide the tiles to transform a puzzle from disorderly state to an orderly state. This implementation is written ground-up in C++, and it uses the SwinGame library to render the solve and to represent graphically. This program utilise both Blind and Heuristic search strategies to reach the answer, in the least number of search nodes.
This program’s design is fully Object Oriented.


9PuzzleI/O provide the following core functionalities.
- Allows you to solve puzzles with n x m, where n and m are variable sizes. 
- Allows you to solve puzzles with variable number of empty slots
- A choice of 4 search strategies to choose from (BFS,DFS,GBFS,A*)
  - Allows you choose the algorithm as an argument
- A Random ‘Solvable’ Puzzle Generator, if you don't feel like entering numbers down, and testing if they are solvable.
  - User can choose enter the sequence of tiles in the reading order, or even declare -random to generate a solvable random sequence of
numbers (which is convenient to the user).
- Visualise the Solve, in a graphics window, so even you can follow whats going on
  -if the user left -render argument, it’ll visualise the solve and perform the solve step by step.

To use these features, refer the ‘Usage’ section, with more information.

## Usage
The 9PuzzleI/O has two functional modes,
 1. Direct Input Mode; Directly input the puzzle size and tiles through arguments
 2. Batch Input Mode; Use a text file to input the puzzle size and tiles
Direct mode is extremely user friendly as it allows the user to pass the arguments through the command line to solve any n*m puzzle with i number empty tiles.
The Batch mode allow the user to automate the solves with more than just one test, if need be. Batch mode only accepts ‘.txt’ files for now. 

```
9Puzzle rows cols [-random] {sequence} [-s {solved-state}] [-bfs|dfs|bgfs|astar] [-render]
  rows : number of rows of the puzzle to solve
  cols : number of columns of the puzzle to solve
  [-random] : feeling lazy? solvable random sequence of numbers (optional)
  {sequence} : sequence of tiles in reading order, 0 denoting empty slot(s)
  [-s {solved-state}] : sequence of tiles of the solved state, in reading order (optional)
  [-bfs|dfs|bgfs|astar] : algorithm to search (optional - defaults to bfs)
  [-render] : render the solve (optional - defaults to false)
```

```Batch Mode
9Puzzle <filepath> [-bfs|dfs|bgfs|astar] [-render]
  <filepath> : batch file path
  [-bfs|dfs|bgfs|astar] : algorithm to search (optional - defaults to bfs)
  [-render]: render the solve (optional - defaults to false)
```
