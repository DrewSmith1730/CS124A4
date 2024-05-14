#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "TennisWinners.h"

using namespace std;

template<typename Comparable>
void printVec(const vector<Comparable> &v) {
    for (int i = 0; i < v.size(); ++i) {
        if (i != 0) {
            cout << ", ";
        }
        cout << v[i];
    }
    cout << endl;
}


// reads and writes for bubble sort
template<typename Comparable>
void bubbleSort(vector<Comparable> vec, int* r, int* w) {
    bool haveSwapped = true;
    int numPasses = 0;
    while (haveSwapped) {
        haveSwapped = false;
        for (int i = 0; i+1 < vec.size() - numPasses; ++i) {
            if (vec[i] > vec[i+1]) { // 2 reads here
                // The two elements are out of order. Swap them.
                Comparable temp = vec[i]; // write and read
                vec[i] = vec[i+1]; // write and a read
                vec[i+1] = temp; // write and a read
                // Update haveSwapped
                haveSwapped = true;
                *w = *w + 3;
                *r = *r + 3;
            }
            *r = *r + 2;
        }
        ++numPasses;
    }
}

// reads and writes for selection sort
template<typename Comparable>
void selectionSort(vector<Comparable> vec, int* r, int* w) {
    int swapIndex, i, minIndex;
    Comparable temp;
    for (swapIndex = 0; swapIndex < vec.size(); ++swapIndex) {
        minIndex = swapIndex;
        for (i = swapIndex + 1; i < vec.size(); ++i) {
            if (vec[i] < vec[minIndex]) {
                // We have found a new minimum
                minIndex = i;
            }
            *r = *r + 2;
        }
        temp = vec[minIndex];
        vec[minIndex] = vec[swapIndex];
        vec[swapIndex] = temp;
        // printVec(vec);
        *r = *r + 3;
        *w = *w + 3;
    }
}

// reads and writes for insertion sort
template<typename Comparable>
void insertionSort(vector<Comparable> vec, int* r, int* w) {
    int unsortedStartIndex, insertIndex;
    Comparable toBeInserted;
    for (unsortedStartIndex = 1; unsortedStartIndex < vec.size(); ++unsortedStartIndex) {
        toBeInserted = vec[unsortedStartIndex]; // read and write
        *w = *w + 1;
        *r = *r + 1;
        insertIndex = unsortedStartIndex - 1;
        while (insertIndex >= 0 && vec[insertIndex] > toBeInserted) { // two reads
            // Shift the larger item over
            vec[insertIndex + 1] = vec[insertIndex]; // read and write
            *r = *r + 1;
            *w = *w + 1;
            // Update insertIndex
            --insertIndex;
        }
        *r = *r + 2;
        vec[insertIndex + 1] = toBeInserted; // write
        *w = *w + 1;
        // printVec(vec);
    }
}

// reads and writes for merge sort
template<typename Comparable>
void mergeSortRec(vector<Comparable> &vec, int startIndex, int endIndex, vector<Comparable> &temp, int* r, int* w) {
    // Recursive base case
    if (startIndex == endIndex) {
        // We are down to one element. Nothing to split or sort.
        return;
    }

    // Recursive calls
    int centerIndex = (startIndex + endIndex) / 2;
    // Recursive call for the left half
    mergeSortRec(vec, startIndex, centerIndex, temp, r, w);
    // Recursive call for the right half
    mergeSortRec(vec, centerIndex + 1, endIndex, temp, r, w);

    // Merge
    //vector<Comparable> temp;
    int leftIndex = startIndex;
    int rightIndex = centerIndex + 1;
    int tempIndex = 0;
    while (leftIndex <= centerIndex && rightIndex <= endIndex) {
        if (vec[leftIndex] <= vec[rightIndex]) {
            // Take the element from the left half
            temp[tempIndex] = vec[leftIndex];
            ++tempIndex;
            ++leftIndex;

            *w = *w + 1;
            *r = *r + 1;
        } else {
            // Take the element from the right half
            temp[tempIndex] = vec[rightIndex];
            ++tempIndex;
            ++rightIndex;

            *w = *w + 1;
            *r = *r + 1;
        }
        *r = *r + 2;
    }
    // At this point, one of the halves has been copied into temp
    // and there is at least one element left in the other half
    while (leftIndex <= centerIndex) {
        // This is the case when there are still elements in the left half
        // Copy them over
        temp[tempIndex] = vec[leftIndex];
        ++tempIndex;
        ++leftIndex;

        *w = *w + 1;
        *r = *r + 1;
    }
    while (rightIndex <= endIndex) {
        // This is the case when there are still elements in the right half
        // Copy them over
        temp[tempIndex] = vec[rightIndex];
        ++tempIndex;
        ++rightIndex;

        *w = *w + 1;
        *r = *r + 1;
    }

    // Now all of the elements are sorted in temp
    // Copy them all back to vec
    for (int i = 0; i <= (endIndex - startIndex); ++i) {
        vec[startIndex + i] = temp[i];

        *w = *w + 1;
        *r = *r + 1;
    }

    // printVec(vec);
}

// reads and writes for merge sort
template<typename Comparable>
void mergeSort(vector<Comparable> vec, int* r, int* w) {
    // Create a temporary vector that is the same size as vec
    vector<Comparable> temp(vec.size());
    mergeSortRec(vec, 0, vec.size() - 1, temp, r, w);
}


// TODO: reads and writes for quick sort
template<typename Comparable>
void quickSortStableRec(vector<Comparable> &vec, int* r, int* w) {
    // Recursive base case
    if (vec.size() < 2) {
        // There is nothing to sort
        return;
    }
    // Choose a partition element
    Comparable partition = vec[0]; // read and write
    vector<Comparable> smaller, equal, larger;
    // Loop through vec and populate smaller, equal, larger
    int i;
    for (i = 0; i < vec.size(); ++i) {
        if (vec[i] < partition) { // 1 read
            smaller.push_back(vec[i]);
            *w = *w + 1;
            *r = *r + 1;
        } else if (vec[i] > partition) { // 1 read
            larger.push_back(vec[i]);
            *w = *w + 1;
            *r = *r + 1;
        } else {
            equal.push_back(vec[i]);
            *w = *w + 1;
            *r = *r + 2;
        }
        *r = *r + 1;
    }
    // Recursive calls
    quickSortStableRec(smaller, r, w);
    quickSortStableRec(larger, r, w);
    // Copy everything back into vec
    for (i = 0; i < smaller.size(); ++i) {
        vec[i] = smaller[i];

        // reads and writes
        *w = *w + 1;
        *r = *r + 1;
    }
    for (; i < smaller.size() + equal.size(); ++i) {
        vec[i] = equal[i - smaller.size()];

        // reads and writes
        *w = *w + 1;
        *r = *r + 1;
    }
    for (; i < vec.size(); ++i) {
        vec[i] = larger[i - smaller.size() - equal.size()];

        // reads and writes
        *w = *w + 1;
        *r = *r + 1;
    }
    // printVec(vec);
}

// reads and writes for quick sort stable
template<typename Comparable>
void quickSortStable(vector<Comparable> vec, int* r, int* w) {
    quickSortStableRec(vec, r, w);
}

//template<typename Comparable>
//void mergeSort(vector<Comparable> vec) {
//    mergeSortRec(vec, 0, vec.size() - 1);
//}

// heap sort
// Helper function for heapSort
inline int leftChild(int i) {
    return 2 * i + 1;
}

// Helper function for heapSort
// i is the index of the value being percolated down
// n is the number of items in the heap
template <typename Comparable>
void percolateDown(vector<Comparable> &items, int i, int n, int child, Comparable tmp, int* r, int* w) {
    //int child;
    //Comparable tmp;

    for(tmp = items[i]; leftChild(i) < n; i = child) {
        child = leftChild(i);
        // choose the child with the larger value
        if (child != n - 1 && items[child] < items[child + 1]) {
            ++child;
        }
        // if the parent is less than the child, swap them
        if (tmp < items[child]) {
            items[i] = items[child];

            // reads and writes
            *w = *w + 1;
            *r = *r + 1;
        } else {
            // parent is >= both children. nothing more to do.
            break;
        }
        // reads and writes
        *w = *w + 1;
        *r = *r + 5;
    }
    items[i] = tmp;

    // reads and writes
    *w = *w + 1;
    *r = *r + 1;
}

template <typename Comparable>
vector<Comparable> heapSort(vector<Comparable> items, int* r, int* w) {
    int i, j, child;
    Comparable temp, tmp;
    // build the heap (with max value at root)
    for (i = items.size() / 2 - 1; i >= 0; --i) {
        percolateDown(items, i, items.size(), child, tmp, r, w);
    }
    // printVec(items);
    // keep deleting the max
    for (j = items.size() - 1; j > 0; --j) {
        // swap the maximum out
        temp = items[0];
        items[0] = items[j];
        items[j] = temp;

        // make it into a heap again
        percolateDown(items, 0, j, child, tmp, r, w);

        // printVec(items);

        // reads and writes
        *w = *w + 3;
        *r = *r + 3;
    }
    return items;
}

// insertion sort for two sort
void insertionSortTwoSort(vector<TennisWinners> vec, int* r, int* w) {
    int unsortedStartIndex, insertIndex;
    TennisWinners toBeInserted;
    for (unsortedStartIndex = 1; unsortedStartIndex < vec.size(); ++unsortedStartIndex) {
        toBeInserted = vec[unsortedStartIndex];
        *w = *w + 1;
        insertIndex = unsortedStartIndex - 1;
        while (insertIndex >= 0 && vec[insertIndex].getTour() > toBeInserted.getTour()) { // one read
            // Shift the larger item over
            vec[insertIndex + 1] = vec[insertIndex]; // read and write
            *r = *r + 1;
            *w = *w + 1;
            // Update insertIndex
            --insertIndex;
        }
        *r = *r + 1;
        vec[insertIndex + 1] = toBeInserted; // write
        // printVec(vec);
    }
}

// TODO: add two-sort here
template<typename Comparable>
void twoSort(vector<Comparable> vec, int* r, int* w){
    vector<Comparable> firstSort = heapSort(vec, r, w);
    insertionSortTwoSort(firstSort, r, w);
}

int main() {
    // Project 4 Main.cpp file
    // Sorting algorithm Project
    vector<int> numbers = {3, 44, 38, 5, 47, 15, 36, 26, 27, 2, 46, 4, 19, 50, 48};
    printVec(numbers);
    // reads and writes variables
    int r = 0, w = 0;

    // tennis winners vector
    vector<TennisWinners> tWinners;
    getTennisWinnersFromFile("TennisWins2000.csv", tWinners);

    /*
    Original Line was random_shuffle(tWinners.begin(), tWinners.end()); however random_shuffle has since not only been depricated but altogether removed in c++17
    link to solution https://stackoverflow.com/questions/45013977/random-shuffle-is-not-a-member-of-std-error
    */

    random_device rd;
    mt19937 g(rd()); // mt19937 (mersenne twister engine) is the type of random sorter i am using for these randoms
    shuffle(tWinners.begin(), tWinners.end(), g); 


    for(int i = 100; i <= 1000; i+= 100){
        // every iteration will increase the length of the vector by 100 until it is 1000
        vector<TennisWinners> tWinnersIncreasing(tWinners.cbegin(), tWinners.cbegin() + i);

        cout << "Number of items in the vector " << i << endl;

        r = 0, w = 0;
        bubbleSort(tWinnersIncreasing, &r, &w);
        cout << "Bubble Sort" << endl;
        cout << "Reads: " << r << endl;
        cout << "Writes: " << w << endl;

        // running selection sort
        r = 0, w = 0;
        selectionSort(tWinnersIncreasing, &r, &w);
        cout << "Selection sort" << endl;
        cout << "Reads: " << r << endl;
        cout << "Writes: " << w << endl;

        r = 0, w = 0;
        insertionSort(tWinnersIncreasing, &r, &w);
        cout << "Insertion Sort" << endl;
        cout << "Reads: " << r << endl;
        cout << "Writes: " << w << endl;

        r = 0, w = 0;
        mergeSort(tWinnersIncreasing, &r, &w);
        cout << "Merge Sort" << endl;
        cout << "Reads: " << r << endl;
        cout << "Writes: " << w << endl;

        r = 0, w = 0;
        quickSortStable(tWinnersIncreasing, &r, &w);
        cout << "Quick Sort Stable" << endl;
        cout << "Reads: " << r << endl;
        cout << "Writes: " << w << endl;

        r = 0, w = 0;
        heapSort(tWinnersIncreasing, &r, &w);
        cout << "Heap Sort" << endl;
        cout << "Reads: " << r << endl;
        cout << "Writes: " << w << endl;

        r = 0, w = 0;
        twoSort(tWinnersIncreasing, &r, &w);
        cout << "Two sort" << endl;
        cout << "Reads: " << r << endl;
        cout << "Writes: " << w << endl;

    }

    // returning 0 means there were no errors in the run any other number means error
    return 0;
}
