#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>

#define LENGTH 50

using namespace std;

void setRule30Display(vector<int> state) {
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
    currentState[(LENGTH) / 2 - 1] = 1; // creates the first x

    setRule30Display(currentState); // to display the first line

    int i;
    for (i=0; i<reps-1; i++) {
        // for the total number of repitions:

        updateState.assign(LENGTH, 0); // to erase the old state

        int s1, s2, s3;
        for (int j = 0; j < LENGTH; j++) {
            if (j == 0) {
                s1 = currentState[LENGTH-1];
            }
            else s1 = currentState[j-1];

            s2 = currentState[j];
            
            if (j == LENGTH-1) {
                s3 = currentState[0];
            }
            else s3 = currentState[j+1];
            
            
        
            vector<int> current;

            current.push_back(s1);
            current.push_back(s2);
            current.push_back(s3);

            int r1 = current[1] | current[2];
            updateState[j] = current[0] ^ r1; 
        }

        // assign() assigns new values to the vector by replacing old ones
        currentState.assign(updateState.begin(), updateState.end()); // to update the current state
        setRule30Display(currentState); // to display the current state
    }
}

int main() {
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

    // To display a decimal in its binary form
    // toBinary(10);

    return 0;
}