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
    DataVector result(*this);
        // if(this->coordinates.size()!=other.coordinates.size()) return;
       // else
        for (size_t i = 0; i < v.size(); ++i) {
            result.v[i] += other.v[i];
        }
        return result;
}

// Operator - for vector subtraction
DataVector DataVector::operator-(const DataVector &other)
{
     DataVector result(*this);
        // if(this->coordinates.size()!=other.coordinates.size()) return;
       // else
        for (size_t i = 0; i < v.size(); ++i) {
            result.v[i] -= other.v[i];
        }
        return result;
}

// Operator * for dot product
double DataVector::operator*(const DataVector &other)
{
    double result = 0.0;
        for (size_t i = 0; i < v.size(); ++i) {
            result += v[i] * other.v[i];
        }
        return result;
}

// Method to calculate the Euclidean norm of the vector
double DataVector::norm() const
{
    
     double sum = 0.0;
        for (double val : v) {
            sum += val * val;
        }
        return sqrt(sum);
}

// Method to calculate the Euclidean distance between two vectors
double DataVector::dist(const DataVector &other)
{
     DataVector diff = *this - other;  // DataVector subtraction
        return diff.norm();
}

// Output stream operator overload for printing the vector
ostream &operator<<(ostream &os, const DataVector &dv)
{
    for (int i = 0; i < dv.v.size(); i++)
        os << dv.v[i] << " ";
    return os;
}