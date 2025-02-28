#include <iostream>

using namespace std;

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << "$" << arr[i] << " ";
    }
    cout << endl;
}

void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int binarySearch(int arr[], int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        cout << "Searching in range: [" << low << " - " << high << "], Middle index: " << mid << endl;
        
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

void findAllOccurrences(int arr[], int size, int target) {
    int index = binarySearch(arr, size, target);
    if (index == -1) {
        cout << "Stock price $" << target << " not found." << endl;
        return;
    }
    
    cout << "Stock price $" << target << " found at indices: ";
    int left = index;
    while (left >= 0 && arr[left] == target) {
        cout << left << " ";
        left--;
    }
    
    int right = index + 1;
    while (right < size && arr[right] == target) {
        cout << right << " ";
        right++;
    }
    cout << endl;
}

int main() {
    
    cout << "=== Binary Search Simulation For Stock Prices ===" << endl;
    srand(42); 
    int N;
    
    while (true) {
    cout << "Enter the number of stock prices to generate: ";
    if (cin >> N && N > 0) {
        break;
    }
    cout << "Invalid input. Please enter a positive integer." << endl;
    cin.clear();
    cin.ignore(10000, '\n');
}

    
    int stockPrices[N];
    for (int i = 0; i < N; i++) {
        stockPrices[i] = 100 + rand() % 101;
    }
    
    insertionSort(stockPrices, N);
    
    cout << "Sorted Stock Prices: ";
    printArray(stockPrices, N);
    

  while (true) {
    int target;
    while (true) {
        cout << "Enter stock price to search (or -1 to exit): ";
        if (cin >> target) {
            break;
        }
        cout << "Invalid input. Please enter an integer." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }

    if (target == -1) {
        cout << "Exiting program." << endl;
        break;
    }

    findAllOccurrences(stockPrices, N, target);
}


    
    return 0;
}

