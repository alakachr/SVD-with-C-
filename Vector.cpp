#include "Vector.h" 
#include <iostream>

#include <assert.h>
using namespace std;


// Constructeur par defaut ?

Vector::Vector() {
    dim = 0;
    tab = new float[0];
   
}

// Basic constructor
Vector::Vector(const int size) {
    dim = size;
    tab = new float[size];
    for (int i = 0; i < size; i++) {
        tab[i] = 0;
    }
}

// 2d Constructor
Vector::Vector(float* arr, const int size) {
    dim = size;
    tab = new float[size];
    for (int i = 0; i < size; i++) {
        tab[i] = arr[i];
    }

}

// Copy constructor
Vector::Vector( Vector& v) {

    dim = v.dim;
    tab = new float[dim];
    for (int i = 0; i < dim; i++) {
        tab[i] = v[i];
    }

}

// This function print the Vector
void Vector::affiche() {
    cout << "Dimension of the vector " << dim << "\n";
    cout << "Value [ ";
    for (int i = 0; i < dim; i++) { cout << tab[i] << " "; }
    cout << "] \n";
}



// Destructor
Vector::~Vector() {
    delete[]tab;
}

//Get dim
int Vector::get_dim() {
    return dim;
}

//Get tab
/**
float* Vector::get_tab() {
    return tab;
}*/

// assignmnent Operator
Vector& Vector::operator=(const Vector& v) {
    if (this != &v) {
        delete tab;
        dim = v.dim;
        tab = new float[dim];
        for (int i = 0; i < v.dim; i++) {
            tab[i] = v.tab[i];
        }
    }
    return *this;
}




float& Vector::operator[](int index)
{
    
    assert(index < dim && "Vector index out of bound " );
    return tab[index];
}


Vector  Vector::subvec(int i, int j) {
    // asserting 

    assert(i <= j && "First index  bigger than second index");
    // assert((j < dim && i<dim ) && " Index out of bound");


    int l = j - i + 1;
    float* arr;
    arr = new float[l];
    for (int k = i; k <= j; k++) {
        arr[k - i] = tab[k];
        //cout << "\n subvecing " << tab[k] << " ";
    }

    Vector resultat(arr, l);
    return resultat;
}


// Addition
Vector operator+(Vector& v1, Vector& v2) {
    int size = v1.get_dim();
    assert(size == v2.get_dim() && "Both vectors do not have same dimB");


    float* tab = new float[size];
    for (int i = 0; i < size; i++) {
        tab[i] = v1[i] + v2[i];
    }
    Vector result(tab, size);
    return result;
}




// Substraction
Vector operator-(Vector& v1, Vector& v2) {
    int size = v1.get_dim();
    assert(size == v2.get_dim() && "Substract: Both vectors do not have same dimB");
    float* tab = new float[size];
    for (int i = 0; i < size; i++) {
        tab[i] = v1[i] - v2[i];
    }
    Vector result(tab, size);
    return result;
}


//Scalar multiplication
Vector operator*(Vector& v1, float k) {
    int size = v1.get_dim();
    float* tab = new float[size];
    for (int i = 0; i < size; i++) {
        tab[i] = k * v1[i];
    }
    Vector result(tab, size);
    return result;
}


// Dot product
float dot(Vector& v1, Vector& v2) {
    int size = v1.get_dim();
    assert(size == v2.get_dim() && "Both vectors do not have same dim for Dot Product");
    float result = 0;
    for (int i = 0; i < size; i++) {
        result += v1[i] * v2[i];
    }

    return result;
}



// nORM 

float Vector::norm() {

    float result = 0;
    for (int i = 0; i < dim; i++) {
        result += tab[i] * tab[i];
    }
    return sqrt(result);
}