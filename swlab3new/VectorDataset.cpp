
#include <bits/stdc++.h>
#include "VectorDataset.h"
#include <chrono>
using namespace std;

// Constructor: Initializes the VectorDataset with a given number of DataVector objects
VectorDataset::VectorDataset(int num)
{
    dataset.resize(num);
}
// Destructor: 
VectorDataset::~VectorDataset()
{
    dataset.clear();
}

// Getter method: for dimention 
int VectorDataset::getDimention()
{
    return dataset[0].getDimension();
}

// Getter method: for dataset
vector<DataVector> VectorDataset::getDataset()
{
    return dataset;
}

// Getter method: for index
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

// Performs k-nearest neighbor algorithm on the dataset for a given DataVector and returns the ans
VectorDataset VectorDataset::knearestneighbor(DataVector a, int k)
{
    VectorDataset ans(k);

    // Calculating the distance of the given vector from all the vectors in the dataset and storing them in a vector of pairs
    vector<pair<double, int>> distancesAndIndices;

    for (int i = 0; i < dataset.size(); ++i)
    {
        double distance = a.dist(dataset[i]);
        distancesAndIndices.push_back({distance, i});
    }

    // Sorting the vector of pairs in ascending order of distance
    sort(distancesAndIndices.begin(), distancesAndIndices.end());

    // Storing the k-nearest neighbors in the ans vector
    for (int i = 0; i < k; ++i)
    {
        int index = distancesAndIndices[i].second;
        ans.dataset[i] = dataset[index];
    }

    return ans;
}
// Prints the entire dataset 

void VectorDataset::printDataset()
{
    for (int i = 0; i < dataset.size(); i++)
    {
        for (int j = 0; j < dataset[i].getDimension(); j++)
            cout << dataset[i].getVector()[j] << " ";
        cout << endl;
    }
}