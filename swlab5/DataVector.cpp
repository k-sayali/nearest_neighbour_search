// DataVector.cpp

#include <iostream>
#include <vector>
#include "DataVector.h"
#include <cmath>
using namespace std;

// Constructor: Initializes the DataVector with a specified dimension
DataVector::DataVector(int dimension)
{
    v.resize(dimension, 0.0);  // Initialize the vector with zeros
}

// Destructor: Cleans up resources when the DataVector object is destroyed
DataVector::~DataVector()
{
    v.clear();  // Clear the vector
}

// Getter method: Returns the dimension of the vector
int DataVector::getDimension() const
{
    return v.size();
}

// Function to assign vector components from a given vector
void DataVector::AssignVector(vector<double> other)
{
    v.resize(other.size());
    v = other;
}

// Copy constructor: Creates a new DataVector object as a copy of another DataVector
DataVector::DataVector(const DataVector &other)
{
    v = other.v;  // Copy constructor
}

// Getter method: Returns the vector components as a vector of doubles
vector<double> DataVector::getVector() const
{
    return v;
}

// Compare operator
bool DataVector::operator==(const DataVector &other)
{
    if(v.size()!=other.v.size()){
        return false;
    }
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] != other.v[i])
            return false;
    }
    return true;
}

// Copy assignment operator: Assigns the content of another DataVector to this DataVector
DataVector &DataVector::operator=(const DataVector &other)
{
    // Assignment operator
    // Check for self-assignment
    if (this != &other)
    {
        v = other.v;
    }
    return *this;
}

// Setter method: Sets the dimension of the vector
void DataVector::setDimension(int dimension)
{
    v.clear();            // Clear the vector
    v.resize(dimension, 0.0);  // Resize the vector with new dimension and initialize with zeros
}

// Operator + for vector addition
DataVector DataVector::operator+(const DataVector &other)
{
    if(v.size()!=other.v.size()){
        cout << "Error: Vectors are not of the same dimension" << endl;
        return DataVector(0);
    }
    // Operator overload for vector addition
    DataVector result(v.size());
    for (int i = 0; i < v.size(); i++)
        result.v[i] = v[i] + other.v[i];
    return result;
}

// Operator - for vector subtraction
DataVector DataVector::operator-(const DataVector &other)
{
    if(v.size()!=other.v.size()){
        cout << "Error: Vectors are not of the same dimension" << endl;
        return DataVector(0);
    }
    // Operator overload for vector subtraction
    DataVector result(v.size());
    for (int i = 0; i < v.size(); i++)
        result.v[i] = v[i] - other.v[i];
    return result;
}

// Operator * for dot product
double DataVector::operator*(const DataVector &other)
{
    if(v.size()!=other.v.size()){
        cout << "Error: Vectors are not of the same dimension" << endl;
        return 0;
    }
    // Operator overload for dot product
    double result = 0.0;
    for (int i = 0; i < v.size(); i++)
        result += v[i] * other.v[i];
    return result;
}

// Method to calculate the Euclidean norm of the vector
double DataVector::norm() const
{
    double result = 0.0;
    for (int i = 0; i < v.size(); i++)
        result += v[i] * v[i];
    return sqrt(result);
}

// Method to calculate the Euclidean distance between two vectors
double DataVector::dist(const DataVector &other)
{
    // Calculate the distance between two vectors using the Euclidean norm
    return (*this - other).norm();
}

// Output stream operator overload for printing the vector
ostream &operator<<(ostream &os, const DataVector &dv)
{
    for (int i = 0; i < dv.v.size(); i++)
        os << dv.v[i] << " ";
    return os;
}