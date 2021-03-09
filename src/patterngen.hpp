//
// FILENAME: cache.py | GameOfPatterns
// DESCRIPTION: The PatternGen class for choosing a pattern to prompt the player with
// CREATED: 2020-06-22 @ 3:24 AM
// COPYRIGHT: Copyright (c) 2020 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef PATTERNGEN_HPP
#define PATTERNDEF_HPP

#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using std::string;
using std::vector;
using std::pair;
using std::find;

class PatternGen {
public:
	// Return the pattern and its ID number (position in the vector)
	pair<vector<int>, ushort> GetPattern();

	bool UsedAll(); // Check if all of the patterns have been used
 
private:
	// Store the patterns
	vector<vector<int>> m_Patterns = {
		{1, 4, 9, 16},   	    // Square the position of the next number in the sequence (next: 5 -> 25, 6 -> 36 ...)
		{1, 1, 2, 3},    	    // Fibonacci Sequence (next: 5, 8, 13...)
		{1, 8, 27, 64},  	    // Cube the position of the next number in the sequence (next: 5 -> 125, 6 -> 216 ...)
		{2, 3, 8, 63},   	    // Square the next element then subtract 1 (next: 63^2 - 1 ...)
		{10, 7, 8, 5},   	    // Subtract 3, add 1 (next: 6, 3, 4...)
		{7, 21, 63, 189}, 	    // Multiply by 3 (next: 567, 1701, 5103...)
		{10, 100, 1000, 10000}, // Raise 10 to the power of the position of the next number in the sequence (next: 10^5, 10^6)
		{1, 2, 6, 24},        	// Multiply by an incremental value of one 
		{17, 34, 51, 68},		// Count by 17s (next: 85, 102, 119...)
		{5, 40, 320, 2560},		// Multiply by 8 (next: 20544, 164325...)
		{1, 7, 21, 35},		    // The 7th row of Pascal's triangle (next: 35, 21, 7, 1)
	};

	vector<ushort> m_UsedIDs; // Used to prevent repeat patterns
};

pair<vector<int>, ushort> PatternGen::GetPattern() {
	pair<vector<int>, ushort> returnPair;
	
	vector<ushort>::iterator iter;
	
	srand(static_cast<unsigned int>(time(0)));
	int randomNum = rand() % m_Patterns.size();
	
	// Randomly select a pattern to be used
	if (!this->m_UsedIDs.empty()) {
		do {
			// Pick a random number
			srand(static_cast<unsigned int>(time(0)));
			randomNum = rand() % m_Patterns.size();
			
			iter = find(this->m_UsedIDs.begin(), this->m_UsedIDs.end(), randomNum); // Check for repeats
		} while (iter != this->m_UsedIDs.end()); // Will loop until an ID is not found in the vector
	}

	this->m_UsedIDs.push_back(randomNum); // Record the pattern ID

	returnPair.first = m_Patterns[randomNum]; // The pattern
	returnPair.second = static_cast<ushort>(randomNum); // The pattern ID

	return returnPair;
}

bool PatternGen::UsedAll() {
	return (this->m_UsedIDs.size() == this->m_Patterns.size());
}

#endif // PATERNGEN_HPP
