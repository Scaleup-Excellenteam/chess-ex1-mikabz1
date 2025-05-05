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

- ## 👑 Pawn Promotion Logic

This project includes full logic for **pawn promotion**. When a pawn reaches the opposite end of the board, the user is prompted to select one of four valid promotion options:

- Queen  
- Rook  
- Bishop  
- Knight

If the user enters an invalid option, a custom exception `WrongPromotionInput` is thrown to ensure valid input.

### 🔧 Internal Handling

- Promotion is handled via the `Pawn::userPromotionChoice()` method.
- The promoted piece is stored in the `promotedPiece` member as a `std::shared_ptr<Piece>`.
- The method `Pawn::canPromote()` checks whether the pawn has reached the correct row for promotion.
- The promoted piece is fully integrated into the game's logic, including movement, threat evaluation, and AI calculations.

### ⚠️ Limitation

Due to assignment constraints, the provided `Chess` class could not be modified. As a result:

> **The visual board display does not show the promoted piece.**

However, the internal logic of the game correctly treats the promoted piece according to its new type (e.g., a promoted queen moves and attacks like a queen). The AI and game engine fully support promotions in gameplay logic, including during simulations.

