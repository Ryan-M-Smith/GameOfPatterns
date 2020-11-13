//
// FILENAME: main.cpp | GameOfPatterns
// DESCRIPTION: The source file for GameOfPatterns
// CREATED: 2020-06-22 @ 3:27 AM
// COPYRIGHT: Copyright (c) 2020 by Ryan Smith <rysmith2113@gmail.com>
//
a
#include <iostream>
#include <utility>
#include <cstdlib>
#include <csignal>

#include "patterngen.hpp"
#include "solver.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::signal;

void sigHandler(int signo);

bool dispTitle(); // Returns `true` if the user wants to play
bool rePrompt(); // Prompts the user to play again 

int main() {
	PatternGen* pg = new PatternGen;
	Solver* solver = new Solver;

	// Register a signal handler
	signal(SIGINT, sigHandler); // CTRL-C/CTRL-D

	system("clear"); // Clear the console

	bool willPlay = dispTitle(); // Run the title sequence

	if (!willPlay) {
		cout << "Quitting...\n";
		return 0;
	}

	game:
		system("clear");

		pair<vector<int>, ushort> patternData = pg->GetPattern();

		bool completed = false, incorrect = false;

		int userNext; // The next item the user enters
		int itemsSolved = 0;

		// Split the pair
		vector<int> pattern = patternData.first;
		ushort patternID = patternData.second;

		system("clear");

		while (!completed && !incorrect) {
			cout << "\033[1;31m"
				<< "Here is your pattern:"
				<< "\033[0m\n";

			// Iterate through the pattern and disply it
			for (unsigned int i = 0; i < pattern.size(); i++) {
				cout << pattern[i] << ", ";
			}

			// Next item "?"
			cout << "\033[;40m\033[7;37m"
				<< "?"
				<< "\033[0m\n";

			bool good = false;

			while (!good) {
				cin.clear(); // Reset cin flags

				cout << "Next item: ";
				cin.ignore();
				cin >> userNext;

				if (!cin.good()) {
					cout << endl;
				}

				good = cin.good();
			}

			cin.clear();

			int next = solver->GenNext(pattern, patternID);

			system("clear"); // Clear for formatting

			if (next == userNext) {
				cout << "\033[1;32m"
				<< "Correct!"
				<< "\033[0m\n\n";

				pattern.push_back(userNext); // Add the next item to the pattern
				itemsSolved++;
			}
			else {
				cout << "\033[1;31m"
				<< "Incorrect!"
				<< "\033[0m\n\n";

				incorrect = true;
			}

			// Check to see if the pattern was completed
			if (itemsSolved == 4) {
				completed = true;
			}
		}

		if (completed) {
			cout << "\033[1;34m"
				<< "You finished the pattern!"
				<< "\033[0m\n\n";
		}
		else {
			cout << "\033[1;34m"
				<< "You got " << itemsSolved << "/6 additional items in the pattern."
				<< "\033[0m\n\n";

			cout << "\033[1;34m"
			<< "Final pattern:"
			<< "\033[0m\n\n";

			for (unsigned int i = 0; i < pattern.size(); i++) {
				cout << pattern[i] << ", ";
			}

			cout << "\033[;31m" << userNext << "\033[0m";
			cout << "\033[;32m" << " (" << solver->GenNext(pattern, patternID) << ")" << endl;
			cout << endl << endl;
		}

	if ((rePrompt()) && (!pg->UsedAll())) {
		goto game;
	}

	return 0;
}

void sigHandler(int signo) {
	cout << "\nQuitting...\n";
	exit(signo);
}

bool dispTitle() {
	// Title - red with bold and underline
	cout << "\033[4;31m\033[1;31m"
		 << "Welcome to the Game of Patterns"
		 << "\033[0m\n\n";

	// Prompt - Blue text with bold; "y/n" - green/red (respectively) with bold
	cout << "\033[1;34m"
		 << "Would you like to play ("
		 << "\033[1;32m" << "y"
		 << "\033[1;34m" << "/"
		 << "\033[1;31m" << "n"
		 << "\033[1;34m" << ")?"
		 << "\033[0m\n\n";

	char answer = ' ';

	do {
		cout << ">>> ";
		cin >> answer;
	} while ((answer == ' ') || ((answer != 'y') && (answer != 'n')));

	return (answer == 'y')? true : false; // Whether or not the user wants to play
}

bool rePrompt() {
	// Prompt - Blue with bold; "y/n" - green/red (respectively) with bold
	cout << "\033[1;34m"
		 << "Would you like to play again ("
		 << "\033[1;32m" << "y"
		 << "\033[1;34m" << "/"
		 << "\033[1;31m" << "n"
		 << "\033[1;34m" << ")?"
		 << "\033[0m\n\n";

	char answer = ' ';

	do {
		cout << ">>> ";
		cin >> answer;
	} while ((answer == ' ') || ((answer != 'y') && (answer != 'n')));

	return (answer == 'y')? true : false; // Whether or not the user wants to play
}
