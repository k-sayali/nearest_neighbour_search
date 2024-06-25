// VectorDataset.h

#ifndef VECTORDATASET_H
#define VECTORDATASET_H

#include "DataVector.h"
#include <vector>
using namespace std;

class VectorDataset
{
private:
    // Intialize a vector of DataVector objects to store the dataset
    vector<DataVector> dataset;

public:
    // Constructor: Initializes the VectorDataset with a specified number of DataVector objects
    VectorDataset(int numdatavectors = 0);

    // Destructor: Cleans up resources when the VectorDataset object is destroyed
    ~VectorDataset();

    // Getter method: Returns the dimension of the vectors in the dataset
    int getDimention();

    // Getter method: Returns the entire dataset as a vector of DataVector objects
    vector<DataVector> getDataset();

    // Getter method: Returns the DataVector at the specified index in the dataset
    DataVector getDatavector(int index);

    // Reads the dataset from a file with the specified file name
    void ReadDataset(string fname);

    // Performs k-nearest neighbor algorithm on the dataset for a given DataVector and returns the result
    VectorDataset knearestneighbor(DataVector a, int k);

    // Prints the entire dataset to the console
    void printDataset();
};

#endif // VECT