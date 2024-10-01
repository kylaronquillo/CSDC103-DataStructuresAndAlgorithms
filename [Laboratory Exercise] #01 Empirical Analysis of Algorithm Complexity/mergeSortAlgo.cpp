#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// Function to merge two subarrays
void merge(vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    vector<int> leftArray(n1);
    vector<int> rightArray(n2);

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (int i = 0; i < n1; i++) {
        leftArray[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArray[i] = arr[middle + 1 + i];
    }

    // Merge the two subarrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            arr[k] = leftArray[i];
            i++;
        } else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArray[], if any
    while (i < n1) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArray[], if any
    while (j < n2) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

// Main merge sort function
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // Merge the sorted halves
        merge(arr, left, middle, right);
    }
}

int main() {
    vector<int> dataset;
    ifstream inputFile("large.txt");

    if (!inputFile) {
        cerr << "Error: Unable to open the input file." << endl;
    }

    int number;
    while (inputFile >> number) {
        dataset.push_back(number);
    }

    inputFile.close();

    // Record the start time
    auto start = high_resolution_clock::now();

    // Perform merge sort on the dataset
    mergeSort(dataset, 0, dataset.size() - 1);

    // Record the end time
    auto end = high_resolution_clock::now();

    // Calculate the elapsed time in seconds
    auto durationNanoseconds = duration_cast<nanoseconds>(end - start);
    auto durationSeconds = durationNanoseconds.count() / 1e9; // Convert nanoseconds to seconds

    /*Print the sorted dataset
    cout << "Sorted Dataset:" << endl;
    for (int num : dataset) {
        cout << num << " ";
    }
    cout << endl;*/
    
        cout << "\nMerge Sort Runtime: " << fixed << setprecision(9) << durationSeconds << " seconds." << endl;


    return 0;
}
