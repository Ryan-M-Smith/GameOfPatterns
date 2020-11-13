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
#include <map>

using std::vector;
using std::map;

class Solver {
public:
	int GenNext(vector<int> pattern, ushort id) const;
	vector<int> Solve(vector<int> pattern, ushort id);
};

int Solver::GenNext(vector<int> pattern, ushort id) const {
	// Generate the next element in a given pattern
	map<int, int> solutions = {
		{0, pow(pattern.size() + 1, 2)},						// Square the position of the next item in the sequence (5th element is 25)
		{1, (pattern.back() + pattern.at(pattern.size() - 2))},	// Fibonacci Sequence
		{2, pow(pattern.size() + 1, 3)},						// Cube the position of the next item in the sequence (5th element is 125)
		{3, (pow(pattern.back(), 2) - 1)},						// Square the next element then subtract 1
		{
			4, ((pattern.at(pattern.size() - 2) - 3) == pattern.back())? \
			(pattern.back() + 1) /* Add 1 if 3 was subtracted last */ : \
			(pattern.back() - 3) /* Subtract 3 if 1 was added last */
		},														// Subtract 3, add 1
		{5, pattern.back() * 3},								// Multiply by 3
		{6, pow(10, pattern.size() + 1)},						// Raise the next element's position to the 10th power
		{7, pattern.back() * pattern.size()},					// Multiply the last element by the position
		{8, pattern.back() + 17},								// Add 17
		{9, pattern.back() * 8},								// Multiply by 8
	};
	
	return solutions[id];
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