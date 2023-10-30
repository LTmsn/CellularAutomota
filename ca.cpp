// AC21009: Assignment3 --> Cellular automation
/*
Group K
Lirit Dampier 2560877
*/

#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>

#define LENGTH 31

using namespace std;

// All possible state patterns
vector<vector<int> > states = { { 1, 1, 1 }, { 1, 1, 0 }, { 1, 0, 1 }, { 1, 0, 0 }, { 0, 1, 1 }, { 0, 1, 0 }, { 0, 0, 1 }, { 0, 0, 0} };

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

void setRule30() {
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

    setRule30Display(currentState); // to display the first line

    int i;
    for (i=0; i<reps-1; i++) {
        // for the total number of repitions:

        updateState.assign(LENGTH, 0); // to erase the old state

        int j;
        for (j=1; j<LENGTH -1; j++) {
            // for the total length:

            int s1 = currentState[j-1];
            int s2 = currentState[j];
            int s3 = currentState[j+1];

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
        setRule30Display(currentState); // to display the current state
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


// The driver function:
int main() {
    // To display cellular automation for the set rule 30
    setRule30();

    cout << "\n";

    // To display a decimal in its binary form
    toBinary(10);

    return 0;
}
