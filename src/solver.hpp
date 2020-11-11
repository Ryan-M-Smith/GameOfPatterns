//
// FILENAME: solver.hpp | GameOfPatterns
// DESCRIPTION: The solver class for calculating the next number in apattern or completeting the pattern
// CREATED: 2020-06-22 @ 2:16 AM
// COPYRIGHT: Copyright (c) 2020 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <cmath>
#include <vector>
#include <iostream>

using std::vector;

class Solver {
public:
	int GenNext(vector<int> pattern, ushort id);
	vector<int> Solve(vector<int> pattern, ushort id);
};

int Solver::GenNext(vector<int> pattern, ushort id) {
	int next = 0;
	
	switch (id) {
		case 0: // Square the position of the next item in the sequence (5th element is 25)
			next = pow(pattern.size() + 1, 2);
			break;
		case 1: // Fibonacci Sequence
			next = (pattern.back() + pattern.at(pattern.size() - 2));
			break;
		case 2: // Cube the position of the next item in the sequence (5th element is 125)
			next = pow(pattern.size() + 1, 3);
			break;
		case 3: // Square the next element then subtract 1
			next = (pow(pattern.back(), 2) - 1);
			break;
		case 4: // Subtract 3, add 1
			// Decide whether to subtract 3 or add 1
			if ((pattern.at(pattern.size() - 2) - 3) == pattern.back()) { // Check for a subtraction of 3
				next = pattern.back() + 1; // Add 1 because 3 was subtracted to get the last element 
			}
			else {
				next = pattern.back() - 3; // Subtract 3
			}

			break;
		case 5:
			next = pattern.back() * 3; // Multiply by 3
			break;
		case 6:
			next = pow(10, pattern.size() + 1); // A power of 10 with the next element in the sequence
			break;
		case 7:
			next = pattern.back() * pattern.size(); // Multiply by an incremental value of 1 each time
			break;
		[[unlikely]] default:
			break;	
	}

	return next;
}

vector<int> Solver::Solve(vector<int> pattern, ushort id) {
	vector<int> solvedPattern;

	// The pattern after a new element is added; passed into this->GenNext(vector<int>, ushort)
	vector<int> incrPattern = pattern;

	// Solve the pattern (complete it with the 6 remaining items)
	for (unsigned int i = pattern.size() /* 4 */; i < 10 /* Future size */; i++) {
		incrPattern.push_back(this->GenNext(incrPattern, id));
	}

	solvedPattern = incrPattern;

	return solvedPattern;
}

#endif // SOLVER_HPP