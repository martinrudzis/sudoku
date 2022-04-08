/*
Puzzle.h
Created by Martin Rudzis
5/14/2021

Input & output: 
This program will read in a stream of 81 digits having values from 0 to 9 using the >> operator. It will simply read in the 
first 81 values that can be read as integers between 0-9. It will then use these to create a 9x9 Sudoku puzzle. This means that, 
if it is passed a string of more than 81 elements, it will simply disregard the remaining ones. The program will treat zeros as 
representing empty locations in the puzzle. Input must be provided on a single line. With regard to output, the program will print 
the input puzzle, followed by the solution. If there is no solution, then the program will print a message stating this. If the 
input puzzle contains no variable elements (i.e. is completely filled-in) then the program will state this, and not attempt to 
solve it. The program will also print the number of variable items in the input, as well as the number of variable items remaining 
after solving the puzzle. (This should be zero, but is there as a precaution to verify the solve function.)

Program Use:
After running the executable file, a prompt will appear to enter a puzzle. Enter a puzzle input as described in the "Input & output" 
section above. Then press "Enter". The program will display the input, followed by the puzzle solution, if a solution exists.

Assumptions: 
It is assumed that the user will enter no less than 81 digits on a single line for the puzzle. It is also assumed that the input is 
ordered such that every group of nine digits represents a row in the puzzle, where the first nine digits is the first row, the 
seconde nine digits is the second row, etc. It is assumed that the completed puzzles cannot be solved, and therefore will not be 
verified, so the program will drow no conclusions regarding the legality of completed puzzles -- i.e., the program will not state 
whether or not input puzzles that contain no variable elements are valid.

Description: 
The primary functionality used by this program is the solve method which uses recursion and backtracking to reach a solution, if one exists. 
The overall workings of this algorithm can be described as follows. It takes coordinates representing the location of the upper left
corner of the puzzle and searches row by row for the first empty location. Once it finds an empty location, it searches for a value 
that can be added to that location. A value is allowed to be added to an empty location if (1) it is the only instance of the value in 
its row and column, and (2) if it is the only instance the value in its region. If the value can be legally added, then the algorithm moves 
calls itself on the next empty location in the puzzle. If no value can legally be added there, then it returns to the previous location 
and tries a different value. It repeats this process until it has found a legal value for every empty location and reached the lower right 
corner of the puzzle. On the other hand, if it has tried every value from the upper left corner without reaching a solution, then the 
algorithm has been given an unsolveable puzzle, ending the process.

*/

#pragma once

#include <iostream>
#include <iterator>

using namespace std;

class Puzzle {

// Function purpose: Print a Puzzle using cout <<
// Parameters: N/A
// Preconditions: An initialized Puzzle
// Postconditions: Each value in the puzzle is printed divided into 9 regions
// Return value: ostream&
// Functions called: Square::getValue()
friend ostream& operator<<(ostream &out, const Puzzle& p);

// Function purpose: Read-in a puzzle from a stream
// Parameters: N/A
// Preconditions: An initialized Puzzle
// Postconditions: The Squares in the puzzle contain the values read from the stream
// Return value: istream&
// Functions called: set()
friend istream& operator>>(istream &input, Puzzle& p);

public:

   // Function purpose: To provide a default constructor for Puzzle objects
   // Parameters: N/A
   // Preconditions: N/A
   // Postconditions: A Puzzle with all data members intialized
   // Return value: iN/A
   // Functions called: N/A
   Puzzle();

   // Function purpose: To return the current number of Squares whose values have not been set
   // Parameters: N/A
   // Preconditions: An initialized Puzzle
   // Postconditions: The number of Squares whose values have not been set in the puzzle is returned
   // Return value: int
   // Functions called: N/A
   int numEmpty() const;
   
   // Function purpose: To return the number of variable Square found in the puzzle, when read-in
   // Parameters: N/A
   // Preconditions: An initialized Puzzle
   // Postconditions: The number of variable entries in the puzzle is returned
   // Return value: int
   // Functions called: N/A
   int size() const;

   // Function purpose: To return the value_ of the Square at a given x, y coordinate
   // Parameters: ints for coordinates
   // Preconditions: An initialized Puzzle
   // Postconditions: The value of the Square at the given location
   // Return value: int
   // Functions called: Square::getValue()
   int get(const int x, const int y) const;

   // Function purpose: To change the value_ of the Square at the given location (if it is variable)
   // Parameters: ints for coordinates, new value
   // Preconditions: An initialized Puzzle
   // Postconditions: The value_ of the Square at the coordinates is changed to value, assuming that it is a variable Square
   // Return value: bool
   // Functions called: Square::setValue(), Square::getValue
   bool set(const int x, const int y, const int value);

   // Function purpose: To determine which of the nin regions of the puzzle a specific coordinate falls within
   // Parameters: ints for coordinates
   // Preconditions: An initialized Puzzle
   // Postconditions: int representing the appropriate region for the coordinates (1-9)
   // Return value: int
   // Functions called: N/A
   int findRegion(const int x, const int y) const;

   // Function purpose: To determine whether a value exists within a given 3x3 grid
   // Parameters: int coordinates for upper left corner of grid, value to check for
   // Preconditions: An initialized Puzzle
   // Postconditions: bool representing whether the value was found
   // Return value: bool
   // Functions called: N/A
   bool evaluateGrid(const int x, const int y, const int value, const int xToIgnore, const int yToIgnore) const;

   // Function purpose: To call evaluate grid on the appropriate coordinates for a given region
   // Parameters: int coordinates, value to check for in region
   // Preconditions: An initialized Puzzle
   // Postconditions: bool representing whther the value was found in the 3x3 region checked
   // Return value: bool
   // Functions called: evaluateGrid()
   bool checkLocalGrid(const int x, const int y, const int value) const;

   // Function purpose: To determine whether a value can be inserted at a particular location, per Sudoku rules
   // Parameters: int coordinates, value to check for 
   // Preconditions: An initialized Puzzle
   // Postconditions: bool representing whether the value can be inserted at the location
   // Return value: bool
   // Functions called: checkLocalGrid()
   bool isLegalValue(const int x, const int y, const int value) const;

   
   // Function purpose: To verify that the input puzzle does not already violate Sudoku rules
   // Parameters: int coordinates for upper left corner of puzzle
   // Preconditions: An initialized Puzzle 
   // Postconditions: bool representing whether all fixed values in puzzle comply with Sudoku rules
   // Return value: bool
   // Functions called: get(), isLegalValue()
   bool isValidPuzzle(const int x, const int y) const;

   // Function purpose: To solve the Puzzle using recursive backtracking
   // Parameters: int coordinates for the upper left corner of the puzzle to solve
   // Preconditions: An initialized Puzzle
   // Postconditions: bool representing whether the puzzle can be solved; solution is printable with cout <<
   // Return value: bool
   // Functions called: set(), isLegalValue() 
   bool solve(int x, int y);


private:

   class Square {
      public:
      int value_;
      bool flag_;
      
      // Function purpose: Initialize a Square using a default constructor
      // Parameters: N/A
      // Preconditions: N/A
      // Postconditions: An initialized Square object
      // Return value: N/A
      // Functions called: N/A
      Square();

      // Function purpose: Initialize a Square using an integer
      // Parameters: int
      // Preconditions: N/A
      // Postconditions: An initialized Square object with value_ set to int parameter
      // Return value: N/A
      // Functions called: N/A
      Square(int value);

      // Function purpose: To return the value_ of the Square object
      // Parameters: N/A
      // Preconditions: An initialized Square object
      // Postconditions: A value; -1 if the value is 0, the actual value otherwise
      // Return value: int
      // Functions called: N/A
      int getValue() const;

      // Function purpose: To change a Square's value_ 
      // Parameters: int
      // Preconditions: An initialized Square object that is flagged as modifiable
      // Postconditions: A Square whose value equals the int parameter
      // Return value: bool
      // Functions called: N/A      
      bool setValue(int value);
   };


   int numVariable_;
   int numEmpty_;

   Square grid_[9][9];

};