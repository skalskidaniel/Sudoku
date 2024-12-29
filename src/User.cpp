//
// Created by Daniel Skalski on 28/12/2024.
//

#include <User.h>
#include <iostream>

std::pair<std::pair<int, int>, char> User::takeTurn() {
    char row, col, choice;
    while (true) {
        std::cout << "Select row where you want to insert a digit (A-I):\t";
        std::cin >> row;
        row = std::toupper(row);
        if (row < 'A' || row > 'I') {
            std::cout << "Invalid row. Please enter a letter between A and I.\n";
            continue;
        }

        std::cout << "\nSelect column where you want to insert a digit (1-9):\t";
        std::cin >> col;
        if (col < '1' || col > '9') {
            std::cout << "Invalid column. Please enter a number between 1 and 9.\n";
            continue;
        }

        std::cout << "\nWhich digit would you like to insert? (1-9, type X to cancel):\t";
        std::cin >> choice;
        choice = std::toupper(choice);
        if ((choice < '1' || choice > '9') && choice != 'X') {
            std::cout << "Invalid choice. Please enter a number between 1 and 9, or X to cancel.\n";
            continue;
        }

        if (choice == 'X') {
            choice = -1;
        }

        break;
    }

    return {{row, col}, choice};
}
