# Monopoly Circular Linked List

This project implements a simple Monopoly board using a circular linked list in C++. The Monopoly board contains 10 properties, each storing a name, cost, owner, and a pointer to the next property. 

Two players take turns moving around the board, checking whether properties are owned, and buying unowned properties. The program also includes functions to add, remove, and search for properties in the circular linked list. It uses random dice rolls to determine how many spaces each player moves on their turn. 

The program simulates 10 turns and prints the results and final board.

## How to Compile

Compile the program using a C++ compiler:

g++ -std=c++17 monopoly.cpp -o monopoly

## How to Run

Run the compiled program:

On Windows:

monopoly.exe

On Mac/Linux:

./monopoly
