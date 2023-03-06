#include <iostream>
#include <chrono>
#include <ctime>
#include <algorithm>

#define SIZE_SMALL 100
#define SIZE_LARGE 100000

using namespace std;

void timeSystemSort(int theArray[], int size)
{
    // get start time
    auto start = chrono::steady_clock::now();

    // sort using system sort
    sort(theArray, theArray + size);

    // get end time
    auto end = chrono::steady_clock::now();

    // calculate & print the amount of time taken
    cout << "Elapsed time in nanoseconds for " << size << " elements using system sort: "
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;
}

void timeBubbleSort(int theArray[], int size)
{
    // get start time
    auto start = chrono::steady_clock::now();

    // sort using bubble sort
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (theArray[j] > theArray[j + 1]) {
                int temp = theArray[j];
                theArray[j] = theArray[j + 1];
                theArray[j + 1] = temp;
            }
        }
    }

    // get end time
    auto end = chrono::steady_clock::now();

    // calculate & print the amount of time taken
    cout << "Elapsed time in nanoseconds for " << size << " elements using bubble sort: "
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;
}

void merge(int theArray[], int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // create temp arrays
    int L[n1], R[n2];

    // copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++) {
        L[i] = theArray[left + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = theArray[middle + 1 + j];
    }

    // merge the temp arrays back into theArray[left..right]
    i = 0; // initial index of first sub-array
    j = 0; // initial index of second sub-array
    k = left; // initial index of merged sub-array

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            theArray[k] = L[i];
            i++;
        }
        else {
            theArray[k] = R[j];
            j++;
        }
        k++;
    }

    // copy the remaining elements of L[], if there are any
    while (i < n1) {
        theArray[k] = L[i];
        i++;
        k++;
    }

    // copy the remaining elements of R[], if there are any
    while (j < n2) {
        theArray[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int theArray[], int left, int right) {
    if (left >= right) {
        return;
    }
    int middle = left + (right - left) / 2;
    mergeSort(theArray, left, middle);
   mergeSort(theArray, middle + 1, right);
   merge(theArray, left, middle, right);
}

void timeMergeSort(int theArray[], int size)
{
// get start time
auto start = chrono::steady_clock::now();

// sort using merge sort
mergeSort(theArray, 0, size - 1);

// get end time
auto end = chrono::steady_clock::now();

// calculate & print the amount of time taken
cout << "Elapsed time in nanoseconds for " << size << " elements using merge sort: "
     << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;
}

int main()
{
int small[SIZE_SMALL];
int large[SIZE_LARGE];
// fill arrays with random integers
srand(time(NULL));
for (int i = 0; i < SIZE_SMALL; i++) {
    small[i] = rand() % 1000;
}
for (int i = 0; i < SIZE_LARGE; i++) {
    large[i] = rand() % 1000;
}

// time system sort on small array
timeSystemSort(small, SIZE_SMALL);

// time bubble sort on small array
timeBubbleSort(small, SIZE_SMALL);

// time merge sort on small array
timeMergeSort(small, SIZE_SMALL);

// time system sort on large array
timeSystemSort(large, SIZE_LARGE);

// time bubble sort on large array
timeBubbleSort(large, SIZE_LARGE);

// time merge sort on large array
timeMergeSort(large, SIZE_LARGE);

return 0;

}
