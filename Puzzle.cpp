/*
Puzzle.cpp
Created by Martin Rudzis
5/14/2021
*/

#include "Puzzle.h" 

// Function purpose: Print a Puzzle using cout <<
// Parameters: N/A
// Preconditions: An initialized Puzzle
// Postconditions: Each value in the puzzle is printed divided into 9 regions
// Return value: ostream&
// Functions called: Square::getValue()
ostream& operator<<(ostream &out, const Puzzle& p) {
   for (int i = 0; i < 9; i++) {
      if (i == 3 || i == 6) { 
         cout << "------+-----+------" << endl; 
      }
      for (int j = 0; j < 9; j++) {
         int data = p.grid_[j][i].getValue();
         if (data == -1) { data++; }
         if (j == 3 || j == 6) {
            cout << "|" << data;
         }
         else {
            cout << " " << data;
         }
      }
      cout << endl;
   }
   cout << endl;
   return out;
}

// Function purpose: Read-in a puzzle from a stream
// Parameters: N/A
// Preconditions: An initialized Puzzle
// Postconditions: The Squares in the puzzle contain the values read from the stream
// Return value: istream&
// Functions called: set()
istream& operator>>(istream &input, Puzzle &p) {
   p.numEmpty_ = 0;
   istream_iterator<char> itr(input);
   for (int i = 0; i < 9; i++) {
      int j = 0;
      while(j < 9) {
         if (isdigit(*itr)) {
            int value = *itr - '0';
            p.set(j, i, value);
            j++;
         }
         itr++;
      }
   }
   return input;
}

// Function purpose: Initialize a Square using a default constructor
// Parameters: N/A
// Preconditions: N/A
// Postconditions: An initialized Square object
// Return value: N/A
// Functions called: N/A
Puzzle::Square::Square() {
   value_ = -1;
   flag_ = true;
}

// Function purpose: Initialize a Square using an integer
// Parameters: int
// Preconditions: N/A
// Postconditions: An initialized Square object with value_ set to int parameter
// Return value: N/A
// Functions called: N/A
Puzzle::Square::Square(int value) {
   if (value >= 10) { cout << "Invalid value for puzzle" << endl; }
   else if (value <= 9) { value_ = value; }
   if (value == 0) { flag_ = true; }
   else { flag_ = false; }
}

// Function purpose: To return the value_ of the Square object
// Parameters: N/A
// Preconditions: An initialized Square object
// Postconditions: A value; -1 if the value is 0, the actual value otherwise
// Return value: int
// Functions called: N/A
int Puzzle::Square::getValue() const {
   if (value_ == 0) { return -1; }
   else if (value_ == -1) { return 0; }
   return value_;
}

// Function purpose: To change a Square's value_ 
// Parameters: int
// Preconditions: An initialized Square object that is flagged as modifiable
// Postconditions: A Square whose value equals the int parameter
// Return value: bool
// Functions called: N/A   
bool Puzzle::Square::setValue(int value) {
   if (flag_) {
      value_ = value;
   }
   else { cout << "Error: Cannot modify preset value" << endl; }
   return value_ == value;
}

// Function purpose: To provide a default constructor for Puzzle objects
// Parameters: N/A
// Preconditions: N/A
// Postconditions: A Puzzle with all data members intialized
// Return value: iN/A
// Functions called: N/A
Puzzle::Puzzle() {
   numEmpty_ = 0;
   numVariable_ = 0;
   for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
         Square s;
         grid_[i][j] = s;
      }
   }
}

// Function purpose: To return the current number of Squares whose values have not been set
// Parameters: N/A
// Preconditions: An initialized Puzzle
// Postconditions: The number of Squares whose values have not been set in the puzzle is returned
// Return value: int
// Functions called: N/A
int Puzzle::numEmpty() const {
   return numEmpty_;
}

// Function purpose: To return the number of variable Square found in the puzzle, when read-in
// Parameters: N/A
// Preconditions: An initialized Puzzle
// Postconditions: The number of variable entries in the puzzle is returned
// Return value: int
// Functions called: N/A
int Puzzle::size() const {
   return numVariable_;
}

// Function purpose: To return the value_ of the Square at a given x, y coordinate
// Parameters: ints for coordinates
// Preconditions: An initialized Puzzle
// Postconditions: The value of the Square at the given location
// Return value: int
// Functions called: Square::getValue()
int Puzzle::get(int x, int y) const {
   bool outsideBoundary = (x > 8 || y > 8);
   if (outsideBoundary) {
      return 10;
   }
   return grid_[x][y].getValue();
}

// Function purpose: To change the value_ of the Square at the given location (if it is variable)
// Parameters: ints for coordinates, new value
// Preconditions: An initialized Puzzle
// Postconditions: The value_ of the Square at the coordinates is changed to value, assuming that it is a variable Square
// Return value: bool
// Functions called: Square::setValue(), Square::getValue
bool Puzzle::set(const int x, const int y, const int value) {
   bool outsideBoundary = (x > 8 || y > 8);
   if (value > 9) { return false; }
   else if (outsideBoundary) {
      cout << "Error: Cannot modify value outside puzzle boundaries" << endl;
      return false;
   }
   else if (!grid_[x][y].flag_) {
      return false;
   }

   if (value == 0 && grid_[x][y].getValue() == 0) {
      numEmpty_++;
      numVariable_++;
   }
   else if (value != 0 && grid_[x][y].getValue() == -1) {
      numEmpty_--;
   }
   else if (value == 0) {
      numEmpty_++;
   }
   
   grid_[x][y].setValue(value);

   return grid_[x][y].getValue() == value;
}

// Function purpose: To determine which of the nin regions of the puzzle a specific coordinate falls within
// Parameters: ints for coordinates
// Preconditions: An initialized Puzzle
// Postconditions: int representing the appropriate region for the coordinates (1-9)
// Return value: int
// Functions called: N/A
int Puzzle::findRegion(const int x, const int y) const {
   if (x > 8 || y > 8) { return -1; }
   else if (x > y) {
      if (y < 3) {
         if (x > 5) { return 3; } 
         else if (x > 2) { return 2; }
         return 1;
      }
      else if (y < 6) {
         if (x > 5) { return 6; }
         return 5; 
      }
      return 9;
   }
   else if (x == y) {
      if (y < 3) { return 1; }
      else if (y < 6) { return 5; }
      return 9;
   }
   else {
      if (x < 3) {
         if (y > 5) { return 7; }  
         else if (y > 2) { return 4; } 
         return 1; 
      }
      else if (x < 6) {
         if (y > 5) { return 8; } 
         return 5; 
      }
      return 9;
   }
   return -1;
}

// Function purpose: To determine whether a value exists within a given 3x3 grid
// Parameters: int coordinates for upper left corner of grid, value to check for
// Preconditions: An initialized Puzzle
// Postconditions: bool representing whether the value was found
// Return value: bool
// Functions called: N/A
bool Puzzle::evaluateGrid(const int x, const int y, const int value, const int xToIgnore, const int yToIgnore) const {
   if (x > 8 || y > 8) { return false; }
   for (int i = x; i < x + 3; i++) {
      for (int j = y; j < y + 3; j++) {
         if (i != xToIgnore && j != yToIgnore && get(i, j) == value) { return false; }
      }
   }
   return true;
}

// Function purpose: To call evaluate grid on the appropriate coordinates for a given region
// Parameters: int coordinates, value to check for in region
// Preconditions: An initialized Puzzle
// Postconditions: bool representing whther the value was found in the 3x3 region checked
// Return value: bool
// Functions called: evaluateGrid()
bool Puzzle::checkLocalGrid(const int x, const int y, const int value) const {
   int region = findRegion(x, y);
   bool regionIsClear = false;
   if (region == -1) { return false; }
   else if (region == 1) { regionIsClear = evaluateGrid(0, 0, value, x, y); }
   else if (region == 2) { regionIsClear = evaluateGrid(3, 0, value, x, y); }
   else if (region == 3) { regionIsClear = evaluateGrid(6, 0, value, x, y); }
   else if (region == 4) { regionIsClear = evaluateGrid(0, 3, value, x, y); }
   else if (region == 5) { regionIsClear = evaluateGrid(3, 3, value, x, y); }
   else if (region == 6) { regionIsClear = evaluateGrid(6, 3, value, x, y); }
   else if (region == 7) { regionIsClear = evaluateGrid(0, 6, value, x, y); }
   else if (region == 8) { regionIsClear = evaluateGrid(3, 6, value, x, y); }
   else { regionIsClear = evaluateGrid(6, 6, value, x, y); }
   return regionIsClear;
}

// Function purpose: To determine whether a value can be inserted at a particular location, per Sudoku rules
// Parameters: int coordinates, value to check for 
// Preconditions: An initialized Puzzle
// Postconditions: bool representing whether the value can be inserted at the location
// Return value: bool
// Functions called: checkLocalGrid()
bool Puzzle::isLegalValue(const int x, const int y, const int value) const {
   for (int i = 0; i < 9; i++) {
      if (i != x && get(i, y) == value) { return false; }
   }
   for (int j = 0; j < 9; j++) {
      if (j != y && get(x, j) == value) { return false; }
   }
   return checkLocalGrid(x, y, value);
}

// Function purpose: To verify that the input puzzle does not already violate Sudoku rules
// Parameters: int coordinates for upper left corner of puzzle
// Preconditions: An initialized Puzzle 
// Postconditions: bool representing whether all fixed values in puzzle comply with Sudoku rules
// Return value: bool
// Functions called: get(), isLegalValue()
bool Puzzle::isValidPuzzle(const int x, const int y) const {
   for (int i = x; i < 9; i++) {
      for (int j = y; j < 9; j++) {
         if (get(j, i) != -1 && !isLegalValue(j, i, get(j, i))) {
            return false;
         }
      }
   }
   return true;
}

// Function purpose: To solve the Puzzle using recursive backtracking
// Parameters: int coordinates for the upper left corner of the puzzle to solve
// Preconditions: An initialized Puzzle
// Postconditions: bool representing whether the puzzle can be solved; solution is printable with cout <<
// Return value: bool
// Functions called: set(), isLegalValue() 
bool Puzzle::solve(int x, int y) {
   if (numEmpty() == size()) {
      bool isValid = isValidPuzzle(x, y);
      if (!isValid) { return false; }
   }
   while(y <= 8) {
      if (get(x, y) == -1) { break; }
      if (x < 8) { x++; }
      else if (y < 8) {
         x = 0;
         y++;
      }
      else {
         y = x = 9;
      }
   }
   if (x == 9 && y == 9) { return true; }
   for (int i = 1; i <= 9; i++) {
      if (isLegalValue(x, y, i)) {
         // cout << x << " " << y << " " << i << endl;
         set(x, y, i);
         if (solve(x, y)) {
            return true;
         }
         set(x, y, 0);
      }
   }
   return false;
}
