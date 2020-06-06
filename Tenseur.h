#pragma once
#include "Vector.h" 
#include "Matrice.h"





class Tenseur {


    int order;
    int* dims;
    int nbelts;

    Vector tensor;
    

public:

    /* Constructors */
    Tenseur(int[], int);
    Tenseur(int[], int, Vector);
    Tenseur (int[], int,  Matrice, int k );
    Tenseur ( Tenseur &);
    ~Tenseur();

    void affiche();

    // Operators
    Tenseur& operator=(const Tenseur&);

    float operator[](int);

    Tenseur operator+(Tenseur&);
    Tenseur operator-(Tenseur&);


    //
    Matrice mode(int k); //modal unfolding

    friend Tenseur pmode(Tenseur t, Matrice M, int k);
    

};




int* phi_inverse_k(int j, int order, int dims[], int k, int ik);

int phi(int order, int dims[], int indexes[]);

