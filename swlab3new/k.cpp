#include <bits/stdc++.h>
#include <chrono>
#include "VectorDataset.h"

using namespace std;

int main()
{
    // Enter the dataset file name
    string fln;
    cout << "Enter Dataset File Name: ";
    cin >> fln;

    // Open the file and check if it is successfully opened
    ifstream file(fln);
    if (!file.is_open())
    {
        cout << "File not found!" << endl;
        return 0;
    }

    // Enter the dataset size
    int size_of_data;
    cout << "Enter Dataset Size: ";
    cin >> size_of_data;

    // Create a VectorDataset object with the specified size and read the dataset from the file
    VectorDataset dataset(size_of_data);
    dataset.ReadDataset(fln);

    // Get the dimension of the vectors in the dataset
    int vectorSize = dataset.getDimention();

    // Create a DataVector object for the test vector
    DataVector testVector(vectorSize);

#ifdef USERMODE
    // If in USERMODE, prompt the user to enter the index of the vector to be used as the test vector
    cout << "Enter the index of the vector in the dataset to be used as the test vector: ";
    int index;
    cin >> index;
    testVector = dataset.getDatavector(index);
#endif

    // Enter the value of k for k-nearest neighbor algorithm
    int k;
    cout << "Enter k: ";
    cin >> k;

    // Measure the time taken to run the k-nearest neighbor algorithm
    auto start = chrono::high_resolution_clock::now();

#ifndef USERMODE
    // If not in USERMODE, run the k-nearest neighbor algorithm for the first 100 vectors in the dataset
    cout << "Running " << k << "-nearest neighbour algorithm on the dataset..." << endl;
    for (int i = 0; i < 100; i++)
    {
        testVector = dataset.getDatavector(i);
        cout << "Calculating neighbors for " << (i + 1) << "th vector..." << endl<<endl<<endl;
        VectorDataset result = dataset.knearestneighbor(testVector, k);
    }
#endif

#ifdef USERMODE
    // If in USERMODE, run the k-nearest neighbor algorithm for the specified test vector
    VectorDataset result = dataset.knearestneighbor(testVector, k);
#endif

    auto stop = chrono::high_resolution_clock::now();

#ifdef USERMODE
    // If in USERMODE, print the k nearest neighbors of the test vector
    cout << "The " << k << " nearest neighbors of the test vector are: " << endl;
    result.printDataset();
#endif

    // Calculate and display the time taken to run the algorithm
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

    int ms = duration.count() % 1000;
    int s = (duration.count() / 1000) % 60;
    int m = (duration.count() / (1000 * 60)) % 60;
    int h = (duration.count() / (1000 * 60 * 60)) % 24;

    cout << "Time taken: ";
    if (h > 0)
        cout << h << "h ";
    if (m > 0 || h > 0)
        cout << m << "m ";
    if (s > 0 || m > 0 || h > 0)
        cout << s << "s ";
    cout << ms << "ms";

    return 0;
}