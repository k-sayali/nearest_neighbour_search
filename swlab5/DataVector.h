// DataVector.h

#ifndef DATAVECTOR_H
#define DATAVECTOR_H
#include <iostream>
#include <vector>
using namespace std;

class DataVector
{
private:
    // Vector to store the components of the data vector
    vector<double> v;

public:
    // Constructor: Initializes the DataVector with a specified dimension (default is 0)
    DataVector(int dimension = 0);

    // Destructor: Cleans up resources when the DataVector object is destroyed
    ~DataVector();

    // Copy constructor: Creates a new DataVector object as a copy of another DataVector
    DataVector(const DataVector &other);

    // Copy assignment operator: Assigns the content of another DataVector to this DataVector
    DataVector &operator=(const DataVector &other);

    // Function to assign vector components from a given vector
    void AssignVector(vector<double> other);

    // Setter method: Sets the dimension of the vector
    void setDimension(int dimension = 0);

    // Getter method: Returns the dimension of the vector
    int getDimension() const;

    // Getter method: Returns the vector components as a vector of doubles
    vector<double> getVector() const;

    // Operator + for vector addition
    DataVector operator+(const DataVector &other);

    // Operator - for vector subtraction
    DataVector operator-(const DataVector &other);

    // Operator * for dot product
    double operator*(const DataVector &other);

    // Method to calculate the Euclidean norm of the vector
    double norm() const;

    // Method to calculate the Euclidean distance between two vectors
    double dist(const DataVector &other);

    // Output stream operator overload for printing the vector
    friend ostream &operator<<(ostream &os, const DataVector &dv);
};

#endif // DATAVECTOR_H
