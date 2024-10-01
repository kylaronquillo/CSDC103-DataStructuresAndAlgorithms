#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// Function for Bubble Sort on a vector
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    do {
        swapped = false;
        for (int i = 1; i < n; i++) {
            if (arr[i - 1] > arr[i]) {
                // Swap arr[i-1] and arr[i]
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
    } while (swapped);
}

int main() {
    vector<int> data;
    string filename;

    ifstream inputFile("medium.txt"); // input file

    if (!inputFile) {
        cerr << "Error: Unable to open the input file." << endl;
    }

    int number;

    // Read numbers from the file and store them in the vector
    while (inputFile >> number) {
        data.push_back(number);
    }

    inputFile.close();

    // Record the start time
    auto start = high_resolution_clock::now();

    // Perform Bubble Sort on the vector
    bubbleSort(data);

    // Record the end time
    auto end = high_resolution_clock::now();

   // Calculate the elapsed time in seconds
    auto durationNanoseconds = duration_cast<nanoseconds>(end - start);
    auto durationSeconds = durationNanoseconds.count() / 1e9; // Convert nanoseconds to seconds
    
    cout << "\nBubble Sort Runtime: " << fixed << setprecision(9) << durationSeconds << " seconds." << endl;

      /* Output the sorted data
    cout << "Sorted Data:" << endl;
    for (int num : data) {
        cout << num << " ";
    }*/

    return 0;
}
