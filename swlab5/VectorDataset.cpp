// VectorDataset.cpp

#include <bits/stdc++.h>
#include "VectorDataset.h"
#include <chrono>
using namespace std;

// Constructor: Initializes the VectorDataset with a specified number of DataVector objects
VectorDataset::VectorDataset(int numdatavectors)
{
    dataset.resize(numdatavectors);
}

// Destructor: Cleans up resources when the VectorDataset object is destroyed
VectorDataset::~VectorDataset()
{
    dataset.clear();
}

// Getter method: Returns the dimension of the vectors in the dataset
int VectorDataset::getDimention()
{
    return dataset[0].getDimension();
}

// Getter method: Returns the entire dataset as a vector of DataVector objects
vector<DataVector> VectorDataset::getDataset()
{
    return dataset;
}

// Getter method: Returns the DataVector at the specified index in the dataset
DataVector VectorDataset::getDatavector(int index)
{
    return dataset[index];
}

// Reads the dataset from a file with the specified file name
void VectorDataset::ReadDataset(string fname)
{
    auto start = chrono::high_resolution_clock::now();
    ifstream file(fname);
    string line;

    if (file.is_open())
    {
        cout << "Reading dataset..." << endl;
        int index = 0;
        while (getline(file, line) && index < dataset.size())
        {
            stringstream ss(line);
            string value;
            vector<double> vectorData;

            // Parse the comma-separated values in each line and convert them to doubles
            while (getline(ss, value, ','))
            {
                vectorData.push_back(stod(value));
            }

            // Assign the vector data to the DataVector at the current index
            dataset[index].AssignVector(vectorData);
            index++;
        }
        file.close();
        auto stop = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        int ms = duration.count() % 1000;
        int s = (duration.count() / 1000) % 60;
        int m = (duration.count() / (1000 * 60)) % 60;
        int h = (duration.count() / (1000 * 60 * 60)) % 24;

        cout << "Time taken to read the dataset: ";
        if (h > 0)
            cout << h << "h ";
        if (m > 0 || h > 0)
            cout << m << "m ";
        if (s > 0 || m > 0 || h > 0)
            cout << s << "s ";
        cout << ms << "ms" << endl;
    }
    else
    {
        cout << "Unable to open file: " << fname << endl;
    }
}

// Performs k-nearest neighbor algorithm on the dataset for a given DataVector and returns the result
VectorDataset VectorDataset::knearestneighbor(DataVector a, int k)
{
    VectorDataset result(k);

    // Calculating the distance of the given vector from all the vectors in the dataset and storing them in a vector of pairs
    vector<pair<double, int>> distancesAndIndices;

    for (int i = 0; i < dataset.size(); ++i)
    {
        double distance = a.dist(dataset[i]);
        distancesAndIndices.push_back({distance, i});
    }

    // Sorting the vector of pairs in ascending order of distance
    sort(distancesAndIndices.begin(), distancesAndIndices.end());

    // Storing the k-nearest neighbors in the result vector
    for (int i = 0; i < k; ++i)
    {
        int index = distancesAndIndices[i].second;
        result.dataset[i] = dataset[index];
    }

    return result;
}

// Prints the entire dataset to the console
void VectorDataset::printDataset()
{
    for (int i = 0; i < dataset.size(); i++)
    {
        for (int j = 0; j < dataset[i].getDimension(); j++)
            cout << dataset[i].getVector()[j] << " ";
        cout << endl;
    }
}