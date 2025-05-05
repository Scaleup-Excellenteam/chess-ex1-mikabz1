# ♟️ Chess AI with Minimax and Alpha-Beta Pruning

This project implements a chess AI using the **Minimax** algorithm enhanced with **Alpha-Beta pruning**, written in modern C++. The AI simulates and evaluates possible future game states to determine the most optimal move.

## 🎯 Algorithm Overview

The AI is based on the **Minimax algorithm**, a decision rule for minimizing the possible loss in a worst-case scenario. It recursively evaluates all possible moves (and countermoves) up to a specified depth, assuming that both players play optimally.

To make this computationally feasible, we apply **Alpha-Beta pruning**, which eliminates branches that cannot influence the final decision. This drastically reduces the number of nodes evaluated.

### 🔍 Time Complexity

Let:
- `b` = average branching factor (number of legal moves per position, typically ~35 in chess)
- `d` = search depth (plies — half-moves)

Then:
- **Without pruning (basic Minimax)**:  
  ⏱️ Time complexity = **O(b^d)**
  
- **With Alpha-Beta pruning (optimal move ordering)**:  
  ⏱️ Time complexity = **O(b^(d/2))**

This optimization allows us to search deeper in the game tree, improving move quality without exponential growth in runtime.

### Heuristic Evaluation Function

The leaf nodes (non-terminal board states) are scored using a custom heuristic function that considers:

- **Material value** — based on predefined constants for each piece (e.g., Queen = 9, Rook = 5)
- **Threat level** — rewards piece safety and penalizes exposed pieces
- **Center control** — prioritizes control over central squares
- **Checkmate detection** — immediate +∞ / −∞ evaluation when a terminal state is reached

## ✅ Features

- Minimax algorithm with Alpha-Beta pruning
- Heuristic board evaluation
- Custom exceptions for error handling
- Move simulation with state undoing
- Priority queue to sort and explore best moves first
- Easy extension for GUI or FEN parsing

## 🚨 Exception Classes

Custom exceptions ensure safe runtime behavior:

- `WrongPromotionInput` — thrown when an invalid piece type is chosen during pawn promotion.
- `NullPiece` — thrown when attempting to access a null piece pointer (usually due to board misconfiguration or faulty logic).
