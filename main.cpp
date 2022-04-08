/*
main.cpp
Created by Martin Rudzis
5/14/2021
*/

#include "Puzzle.h"
#include <sstream>


int main() {
   
   Puzzle p;

   string input;

   cout << "Enter a puzzle: >> ";
   getline(cin, input);

   istringstream ss(input);

   ss >> p;

   cout << endl << "Input:" << endl;
   cout << p;
   cout << "Empty locations in input: " << p.size() << endl;
   cout << "Remaining empty locations: " << p.numEmpty() << endl << endl;

   if (p.numEmpty() == 0) {
      cout << "Puzzle already complete:" << endl;
   }
   else {
      bool canSolve = p.solve(0, 0); 
      if (canSolve) {
         cout << "Puzzle Solution:" << endl;
         cout << p;
         cout << "Empty locations in input: " << p.size() << endl;
         cout << "Remaining empty locations: " << p.numEmpty() << endl;
      }
      else {
         cout << "Puzzle cannot be solved:" << endl;
      }
   }

}