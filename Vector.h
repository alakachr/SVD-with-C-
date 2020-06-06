#pragma once
//#include "Matrice.h" 
class Vector {

    float* tab;
    int dim;
    friend class Matrice;
public:
    //Constructors & Destructor
    Vector();
    Vector(int);
    Vector(float*, int);
    Vector( Vector&); // deep copy
    ~Vector();
    // Operators
    Vector& operator=(const Vector&);
    //void operator=(Vector&&);
    float& operator[](int);

    //Other methods
    void affiche();
    int get_dim();
    float* get_tab();
    //Vector subvec(int , int );
    float norm();
    Vector subvec(int , int );
};

// Addition
Vector operator+(Vector& , Vector& );




// Substraction
Vector operator-(Vector& , Vector& ); 


//Scalar multiplication
Vector operator*(Vector& , float );


// Dot product
float dot(Vector& , Vector& );
    



