// Jarod Graygo
// Programming Assignment #2


#include<iostream>

using std::cout;
  
// Number of processes and number of resources
const unsigned int NUM_PROCESSES = 5;
const unsigned int NUM_RESOURCES = 3;
  
// Function to find the system is in safe state or not
bool safeState(int processes[], int available_resources[], int max_required[][NUM_RESOURCES], int alloted[][NUM_RESOURCES]) {
    int need[NUM_PROCESSES][NUM_RESOURCES];

    // Calculates the need of all processes and assigns it to the matrix "need"
    for (int i = 0 ; i < NUM_PROCESSES ; i++) {
        for (int j = 0 ; j < NUM_RESOURCES ; j++) {
            need[i][j] = max_required[i][j] - alloted[i][j];
        }
    }

    bool finish[NUM_PROCESSES] = {0};
  
    int safe_sequence[NUM_PROCESSES];
    
    // Copy current available resources
    int curr_available[NUM_RESOURCES];
    for (int i = 0; i < NUM_RESOURCES ; i++) curr_available[i] = available_resources[i];

    int index = 0;
    while (index < NUM_PROCESSES) {
        bool found = false;

        for (int p = 0; p < NUM_PROCESSES; p++) {
            if (finish[p] == 0) {
                int j;

                for (j = 0; j < NUM_RESOURCES; j++) {
                    if (need[p][j] > curr_available[j]) break;
                }

                if (j == NUM_RESOURCES) {
                    for (int k = 0 ; k < NUM_RESOURCES ; k++) {
                        curr_available[k] += alloted[p][k];
                    }

                    safe_sequence[index] = p;
                    ++index;
                    finish[p] = 1;
  
                    found = true;
                }
            }
        }
  
        // If the system is not in a safe state, print out that result
        if (found == false) {
            cout << "NOT SAFE";
            return false;
        }
    }
  
    // If the system is in a safe state, print that it is
    // and the safe sequence
    cout << "SAFE STATE\nSafe sequence is: ";
    for (int i = 0; i < NUM_PROCESSES ; i++) cout << safe_sequence[i] << " ";
    cout << "\n";
  
    return true;
}
  
// Driver code
int main() {
    int processes[] = {0, 1, 2, 3, 4};
  
    // Available instances of resources
    int available_resources[] = {3, 3, 2};
  
    // Matrix of currently allocated resources per process
    int alloted[][NUM_RESOURCES] = {{0, 1, 0},
                                    {2, 0, 0},
                                    {3, 0, 2},
                                    {2, 1, 1},
                                    {0, 0, 2}};
  
    // Matrix of maximum requested resources per process
    int max_required[][NUM_RESOURCES] = {{7, 5, 3},
                                         {3, 2, 2},
                                         {9, 0, 2},
                                         {2, 2, 2},
                                         {4, 3, 3}};
  
    // Check system is in safe state or not
    safeState(processes, available_resources, max_required, alloted);
}