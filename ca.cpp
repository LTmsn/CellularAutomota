// AC21009: Assignment3 --> Cellular automation
/*
Group K
Lirit Dampier 2560877
Lucy Thomson 2505312
Ahmid Omarzada 2527809
*/

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <stdint.h>
#include <bitset>
#include <limits>

#define LENGTH 50

using namespace std;


const int rows = 20;
const int columns = 40;

// All possible state patterns
//vector<vector<int> > states = { { 1, 1, 1 }, { 1, 1, 0 }, { 1, 0, 1 }, { 1, 0, 0 }, { 0, 1, 1 }, { 0, 1, 0 }, { 0, 0, 1 }, { 0, 0, 0} };


// FOR 1 DIMENSIONAL CELLULAR AUTOMATION:

// a void function to display set rule 30
void setRuleDisplay(vector<int> state) {
    cout << "\t\t";
    for (int i = 0; i < LENGTH; i++) {
        // for the length (set length)
        if (state[i] == 1) {
            // if the current state is a one then print an x
            cout << "x";}
        else if (state[i] == 0) {
            // if the current state is zero then print a space
            cout << " "; }
    }
    cout << "\n"; // to print a line
}

void setRule30(bool isWrap) {
    cout << "For set rule 30: " << endl;

    int reps;
    // Ask the user how many repitions they want:
    cout << "How many repitions: ";
    cin >> reps;
    while (reps < 1) {
        // If reps is less than one it is an invalid rep
        cout << "How many repitions: ";
        cin >> reps;
    }

    // To initialise the state as vectors
    vector<int> currentState(LENGTH);
    vector<int> updateState(LENGTH);
    currentState[(LENGTH) / 2 - 1] = 1;

    setRuleDisplay(currentState); // to display the first line

    int i;
    for (i=0; i<reps-1; i++) {
        // for the total number of repitions:

        updateState.assign(LENGTH, 0); // to erase the old state

        for (int j=0; j<LENGTH; j++) {
            // for the total length:
            

            /*
                x x x
                O   <- each j is looking at the top 3 to valuate what it should be next
            */
            int s1, s2, s3;
            if (isWrap == 1) {
                if (j == 0) {
                    s1 = currentState[LENGTH-1]; // will look at the value on the other end of the state
                }
                else s1 = currentState[j-1];

                s2 = currentState[j];
                
                if (j == LENGTH-1) {
                    s3 = currentState[0]; // will look at the value on the start of the state
                }
                else s3 = currentState[j+1];
                
            }
            else {
                s1 = currentState[j-1];
                s2 = currentState[j];
                s3 = currentState[j+1];
            }

            // to create an array for just the current pattern
            vector<int> current;
            // push_back() is used to push elements into a vector from the tail
            current.push_back(s1);
            current.push_back(s2);
            current.push_back(s3);

            // state = left XOR (central OR right)
            int r1 = current[1] | current[2]; // OR operation between the middle and right bit of the current pattern
            updateState[j] = current[0] ^ r1; // XOR operation between the first bit and the result of the OR operation between the middle and right bit
        }

        // assign() assigns new values to the vector by replacing old ones
        currentState.assign(updateState.begin(), updateState.end()); // to update the current state
        setRuleDisplay(currentState); // to display the current state
    }
}


// Function to convert a decimal number to a binary number
int toBinary(int decNum) {
    int binaryNumArray[100]; // an array to store binary numbers
    int count=0;
    int value;
    while (decNum>0) {
        // while the decimal number is greater than 0, mod the decimal number by 2 and store the result (aka 0 or 1)
        value = decNum%2;
        binaryNumArray[count] = value;
        decNum = decNum/2;
        count+=1;
    }
    // reverse the order of the array
    int i;
    for (i=count-1; i>= 0; i--) {
        cout << binaryNumArray[i]; // to print the array of binary numbers
    }
    
    return 0;
}

// Function to convert a binary number to a decimal number
int toDecimal(int binaryNum) {
    //int num = binaryNum;
    int decimal = 0;
    int base = 1;
    int temp = binaryNum;
    while (temp) {
        int last = temp % 10;
        temp = temp/10;
        decimal += last * base;
        base = base * 2;
    }
    cout << decimal << endl;

    return 0;
}

// function for the set rule of the user's choice or random
void setRule(int rule) {
    int reps;
    // Ask the user how many repetitions they want:
    cout << "How many repetitions: ";
    cin >> reps;
    while (reps < 1) {
        // If reps is less than one, it is an invalid input
        cout << "How many repetitions: ";
        cin >> reps;
    }

    std::bitset<8> ruleBinary(rule);
    std::cout << ruleBinary << endl;
    string ruleBinaryString = ruleBinary.to_string();
    cout << ruleBinaryString[1];

    // Initialize the state as vectors
    vector<int> currentState(LENGTH);
    vector<int> updateState(LENGTH);
    currentState[(LENGTH) / 2 - 1] = 1;

    setRuleDisplay(currentState);

    for (int i = 0; i < reps - 1; i++) {
        // Loop for the total number of repetitions

        updateState.assign(LENGTH, 0); // Erase the old state

        for (int j = 1; j < LENGTH - 1; j++) {
            // Loop for the total length:

            int s1 = currentState[j - 1];
            int s2 = currentState[j];
            int s3 = currentState[j + 1];

            // Create an array for the current pattern
            vector<int> current;
            current.push_back(s1);
            current.push_back(s2);
            current.push_back(s3);

            if (current[0] == 1) {
                // 1
                if (current[1] == 0) {
                    // 10
                    if (current[2] == 0) {
                        // 100
                        updateState[j] = ruleBinaryString[3] - '0';
                    } else {
                        // 101
                        updateState[j] = ruleBinaryString[2] - '0';
                    }
                } else {
                    // 11
                    if (current[2] == 0) {
                        // 110
                        updateState[j] = ruleBinaryString[1] - '0';
                    } else {
                        // 111
                        updateState[j] = ruleBinaryString[0] - '0';
                    }
                }
            } else {
                // 0
                if (current[1] == 0) {
                    // 00
                    if (current[2] == 0) {
                        // 000
                        updateState[j] = ruleBinaryString[7] - '0';
                    } else {
                        // 001
                        updateState[j] = ruleBinaryString[6] - '0';
                    }
                } else {
                    // 01
                    if (current[2] == 0) {
                        // 010
                        updateState[j] = ruleBinaryString[5] - '0';
                    } else {
                        // 011
                        updateState[j] = ruleBinaryString[4] - '0';
                    }
                }
            }
        }

        // Assign new values to the vector by replacing old ones
        currentState = updateState;
        setRuleDisplay(currentState); // Display the current state
    }
}

// Function to initialize the grid with random values
void initializeGrid(vector<vector<bool> >& grid) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            grid[i][j] = rand() % 2; 
        }
    }
}

// Function to display the grid
void displayGrid(const vector<vector<bool> >& grid) {
    cout << "+";
    for (int j = 0; j < columns; j++) {
        cout << "-";
    }
    cout << "+" << endl;

    for (int i = 0; i < rows; i++) {
        cout << "|";
        for (int j = 0; j < columns; j++) {
            if (grid[i][j]) {
                cout << "0"; // Alive cell
            } else {
                cout << " "; // Dead cell
            }
        }
        cout << "|" << endl;
    }

    cout << "+";
    for (int j = 0; j < columns; j++) {
        cout << "-";
    }
    cout << "+" << endl;
}

// Function to update the grid based on Game of Life rules
void updateGrid(vector<vector<bool> >& grid) {
    vector<vector<bool> > newGrid = grid;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int aliveNeighbors = 0;

            // Check the 8 neighbors
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (x == 0 && y == 0) continue; // Skip the current cell
                    int ni = i + x;
                    int nj = j + y;

                    // Ensure the neighbor is within bounds
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < columns && grid[ni][nj]) {
                        aliveNeighbors++;
                    }
                }
            }

            if (grid[i][j]) {
                // Cell is currently alive
                if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                    newGrid[i][j] = false; // Cell dies
                }
            } else {
                // Cell is currently dead
                if (aliveNeighbors == 3) {
                    newGrid[i][j] = true; // Cell becomes alive
                }
            }
        }
    }

    grid = newGrid;
}

enum Direction { NORTH, EAST, SOUTH, WEST };

struct Ant {
    int x;
    int y;
    Direction dir;
};

// Function to initialize the grid
void initialize_Grid(vector<vector<bool> >& grid) {
    for (int i = 0; i < rows; i++) {
        vector<bool> row;
        for (int j = 0; j < columns; j++) {
            row.push_back(false);
        }
        grid.push_back(row);
    }
}

// Function to display the grid with the ant's position
void displayGrid(const vector<vector<bool> >& grid, const Ant& ant) {
    system("clear"); // Clear the console

    cout << "+";
    for (int j = 0; j < columns; j++) {
        cout << "-";
    }
    cout << "+" << endl;


    for (int i = 0; i < rows; i++) {
        cout << "|";

        for (int j = 0; j < columns; j++) {
            if (i == ant.y && j == ant.x) {
                cout << "*"; // Ant's position
            } else {
                cout << (grid[i][j] ? "#" : " "); // Black cell or empty cell
            }
        }
        cout << "|" << endl;
    }
    cout << "+";
    for (int j = 0; j < columns; j++) {
        cout << "-";
    }
    cout << "+" << endl;
}

// Function to update the ant's position and the grid
void updateAntAndGrid(Ant& ant, vector<vector<bool> >& grid) {
    if (grid[ant.y][ant.x]) {
        // Turn right
        switch (ant.dir) {
            case NORTH: ant.dir = EAST; break;
            case EAST: ant.dir = SOUTH; break;
            case SOUTH: ant.dir = WEST; break;
            case WEST: ant.dir = NORTH; break;
        }
        grid[ant.y][ant.x] = false; // Flip the cell
    } else {
        // Turn left
        switch (ant.dir) {
            case NORTH: ant.dir = WEST; break;
            case EAST: ant.dir = NORTH; break;
            case SOUTH: ant.dir = EAST; break;
            case WEST: ant.dir = SOUTH; break;
        }
        grid[ant.y][ant.x] = true; // Flip the cell
    }

    // Move the ant
    switch (ant.dir) {
        case NORTH: ant.y--; break;
        case EAST: ant.x++; break;
        case SOUTH: ant.y++; break;
        case WEST: ant.x--; break;
    }

    // Wrap around the grid
    if (ant.x < 0) ant.x = columns - 1;
    if (ant.x >= columns) ant.x = 0;
    if (ant.y < 0) ant.y = rows - 1;
    if (ant.y >= rows) ant.y = 0;
}



// The driver function:
void menu() {
    cout << "Menu \n";
    cout << "1. Generate set rule 30 \n";
    cout << "2. Generate a set rule of your choice \n";
    cout << "3. Generate a random set rule \n";
    cout << "4. Convert from decimal to binary \n";
    cout << "5. Convert from binary to decimal \n";
    cout << "6. Play Conway's Game of Life \n";
    cout << "7. Play Langton's Ant \n";


    cout << "Enter your choice: \n";
    int choice;
    cin >> choice;
    if (choice == 1) {
        // If the user chose option 1
        bool isWrap = false;
        cout << "Would you like the pattern to wrap around? (Y/N) ";
        string input;
        cin >> input;
        if (input.compare("y") == 0 || input.compare("Y") == 0 || input.compare("yes") == 0 || input.compare("Yes") == 0) {
        isWrap = true;
        }
        // To display cellular automation for the set rule 30
        setRule30(isWrap);
        cout << "\n";
    } else if (choice == 2) {
        // If the user chose option 2
        int rule;
        cout << "Enter a set rule: ";
        cin >> rule;
        // rule must be 0-255
        if ((rule > 0) && (rule < 256)) {
            setRule(rule);
        } else {
            cout << "The rule must be in the range of 0-255";
        }

    } else if (choice == 3) {
        // If the user chose option 3
        int random = 1 + (rand() % 256); // to generate a random number between 1 and 99
        setRule(random);
    } else if (choice == 4) {
        // If the user chose option 4
        int num;
        cout << "Enter a decimal number that you want to convert into binary: ";
        cin >> num;
        toBinary(num);
        cout << "\n";
    } else if (choice == 5) {
        // If the user chose option 5
        int binaryNum;
        cout << "Enter a binary number: ";
        cin >> binaryNum;
        toDecimal(binaryNum);
    }else if(choice == 6){
        // If the user chose option 6

        srand(time(0));
        vector<vector<bool> > grid(rows, vector<bool>(columns, false));
        initializeGrid(grid);
        cout << endl;
        cout << "\n";


        while (true) {
            system("clear"); // Clear the console
            displayGrid(grid);
            updateGrid(grid);
        
            cout << "Press any key to continue (or 'q' to quit): ";
            int userInput = getchar();

            if (userInput == 'q') {
              break; // Exit if 'q' is pressed
            }
    
        }

    }else if(choice == 7){
        // If the user chose option 7

        vector<vector<bool> > grid;
        initialize_Grid(grid);

        Ant ant;
        ant.x = columns / 2;
        ant.y = rows / 2;
        ant.dir = NORTH;

        char userInput;

        while (true) {
            displayGrid(grid, ant);
            updateAntAndGrid(ant, grid);

            cout << "Press any key to continue (or 'q' to quit): ";
            userInput = cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (tolower(userInput) == 'q') {
                break; // Exit if 'q' is pressed (case-insensitive)
            }
        }
    }else {
        cout << "Invalid choice";
        }
}

// The driver function
int main() {
    bool x = true;
    while (x == true) {
        menu();
        char exit;
        cout << "Would you like to choose another menu option (y/n): ";
        cin >> exit;
        if (exit == 'n') {
            // If the user wants to exit the menu
            x = false;
        }
    }
    return 0;
}
