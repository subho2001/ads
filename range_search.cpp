#include <iostream>

using namespace std;

void customSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int customLowerBound(int arr[], int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] >= value) {
            return i;
        }
    }
    return size;
}

int customUpperBound(int arr[], int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] > value) {
            return i;
        }
    }
    return size;
}

int main() {
    // Take user input for the size of the array
    cout << "Enter the size of the array: ";
    int size;
    cin >> size;

    // Declare an array of integers
    int numbers[size];

    // Take user input for the array of integers
    cout << "Enter " << size << " numbers separated by spaces:\n";
    for (int i = 0; i < size; ++i) {
        cin >> numbers[i];
    }

    // Take user input for the range
    int lower_bound_value, upper_bound_value;
    cout << "Enter the lower bound: ";
    cin >> lower_bound_value;

    cout << "Enter the upper bound: ";
    cin >> upper_bound_value;

    // Sort the array using the custom sorting function
    customSort(numbers, size);

    // Find elements within the specified range using custom lower and upper bound functions
    int lower_it = customLowerBound(numbers, size, lower_bound_value);
    int upper_it = customUpperBound(numbers, size, upper_bound_value);

    // Display the elements within the range
    cout << "Elements within the range [" << lower_bound_value << ", " << upper_bound_value << "]: ";
    for (int i = lower_it; i < upper_it; ++i) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    return 0;
}
