#pragma once
#include "Vector.h" 
//#include "Tenseur.h" 

class Matrice {

    Vector *mat;
    int dim [2];
    friend class Tenseur;
public:
    //Constructors & Destructor

    Matrice(int, int); // line then col
    Matrice(Vector&); // diag
    Matrice(Vector*, int);
    Matrice( Matrice&); // deep copy
    ~Matrice();
    
    // Operators
    Matrice& operator=(const Matrice&);

    Vector& operator[]( int);

    Matrice operator+(Matrice&);
    Matrice operator-(Matrice&);

    Matrice operator*(Matrice&);

    //Vector  operator*(Vector&);
    Matrice operator*(float);



    //Other methods
    void affiche();
    Matrice transpose();
    Vector mvprod(Vector&);
    int* get_dim();

   
    Matrice submat(int , int, int, int );
   // float norm();
  //  friend Tenseur pmode(Tenseur t, Matrice M, int k);
};





