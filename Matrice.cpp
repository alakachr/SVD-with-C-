#include "Matrice.h" 
#include <iostream>

#include <assert.h>
using namespace std;





// This function print the Matrice
void Matrice::affiche() {
    cout << "Dimension of the Matrix " << dim[0] << " " << dim[1]<< "\n";
    
    for (int i = 0; i < dim[0]; i++) {//
        cout << "[";
        for (int j = 0; j < dim[1]; j++) {//
            cout << mat[j][i] << " "; // columns then rows
        }
        cout << "], \n";
        
    }
    //cout << "] \n";
}



// Basic constructor
Matrice::Matrice (const int l, const int col) {
    dim[0] = l;
    dim[1] = col;
  
    mat = new Vector[l];
    // Array of columns
    for (int i = 0; i < dim[1]; i++) {
        mat[i] = *new Vector(l) ;
    }
}

// diagonal Constructor
Matrice::Matrice(Vector& diag) {
    
    dim[0] = diag.dim;
    dim[1] = diag.dim;

    mat = new Vector[dim[1]];
    for (int i = 0; i < dim[1]; i++) {
        mat[i] = *new Vector(dim[0]);
    }

    for (int i = 0; i < dim[1]; i++) {
       // cout <<"i" << i<<"diag" << diag[i];
        mat[i][i] = diag[i];
    }
}

// 3rd constructor
Matrice::Matrice(Vector* matrix, const int size) {

    dim[1] = size; // nb columns
    dim[0] = matrix[0].dim; // nb rows

    mat = new Vector[dim[1]];

    // Array of columns
    for (int i = 0; i < dim[1]; i++) {
        mat[i] = matrix[i];
    }

}


// Copy constructor
Matrice::Matrice( Matrice& m) {

    dim[0] = m.dim[0];
    dim[1] = m.dim[1];

    mat = new Vector[dim[1]];
    for (int i = 0; i < dim[1]; i++) {
        mat[i] = m[i];
    }

}


// Destructor
Matrice::~Matrice() {
    delete[]mat;
}





// assignmnent Operator
Matrice& Matrice::operator=(const Matrice& m) {


   
    if (this != &m) {
        delete [] mat;
        dim[0] = m.dim[0];
        dim[1] = m.dim[1];

        
        mat = new Vector[dim[1]]; // nb col
        for (int i = 0; i < dim[1]; i++) {
            mat[i] = m.mat[i];
        }
    }
    return *this;
}


//[] operator

Vector& Matrice::operator[](int index)
{
    
    
    assert(dim[1]>index && " Matrix Index out of bound");
    // return columns
    return mat[index];
}





// Addition
Matrice  Matrice::operator+(Matrice& m) {
    
    assert((dim[0] == m.dim[0] && dim[1] == m.dim[1])&& "Addition: Both Matrice do not have same dim");


    Vector* matrix = new Vector[dim[1]]; // nb col
    // adding columns
    for (int i = 0; i < dim[1]; i++) {
        matrix[i] = mat[i] + m.mat[i];
    }
    Matrice result(matrix, dim[1]);
    return result;
}





// Multiplication with scalar 
Matrice  Matrice::operator*(float k) {

   

    Vector* matrix = new Vector[dim[1]];
    
    for (int i = 0; i < dim[1]; i++) {
        matrix[i] = mat[i]*k;
    }

    Matrice result(matrix, dim[1]);
    return result;
}



// Multiplication with vect 
Vector  Matrice::mvprod(Vector& v) {



    //float* arr = new float[dim[0]];


    Vector result(dim[0]);
    Vector temp(1);
    
    
    for (int i = 0; i < dim[1]; i++) {
        temp = mat[i] * v[i];
        result = temp + result;
        
    }

    
    return result;

}


//Transpose
Matrice  Matrice::transpose() {



    Vector* matrix = new Vector[dim[0]];

    for (int i = 0; i < dim[0]; i++) {
        matrix[i] = *new Vector(dim[1]);
    }

    for (int i = 0; i < dim[0]; i++) { //  nb col of the transpose
        for (int j = 0; j < dim[1]; j++) {
            matrix[i][j] = mat[j][i];
        }     
    }

    cout << "transpositoion" << endl;

    Matrice result(matrix, dim[0]);

    cout << "constructeur transpositoion" << endl;
    return result;
}




// Multiplication
Matrice  Matrice::operator*(Matrice& m) {

    assert((dim[1] == m.dim[0]) && "Mutiplying : Both Matrice are not compatible same dim");

    cout << "1ere indexation"<<endl;

    Vector* matrix = new Vector[m.dim[1]];
    cout << "nb col " << m.dim[1] << endl;
    for (int i = 0; i < m.dim[1]; i++) {

        cout << i << endl;
        matrix[i] = *new Vector(dim[0]);
    }


    cout << "transpose "<<endl;
    Matrice mt(1, 1);
    mt = (*this).transpose();

    cout << "multiplication" << endl;
    for (int i = 0; i < dim[0]; i++) {
        for (int j = 0; j < m.dim[1]; j++) {

            
            matrix[j][i] = dot(mt.mat[i], m.mat[j] );
        }
    }
    Matrice result(matrix, dim[1]);
    return result;
}

// Substraction
Matrice  Matrice::operator-(Matrice& m) {

    assert((dim[0] == m.dim[0] && dim[1] == m.dim[1]) && "Both Matrice do not have same dim");


    Vector* matrix = new Vector[dim[1]];
    for (int i = 0; i < dim[1]; i++) {
        matrix[i] = mat[i] - m.mat[i];
    }
    Matrice result(matrix, dim[1]);
    return result;
}


Matrice  Matrice::submat(int il, int jl, int ic, int jc) {

    // asserting 

    assert(il <= jl && "First index  bigger than second index");
    assert(ic<= jc && " First index  bigger than second index");


    int l = jl - il + 1;
    int c = jc - ic + 1;

    Vector* matrix = new Vector[c];
    
    for (int i = ic; i <= jc; i++) {
        matrix[i-ic] = *new Vector(l);
    }

    for (int i = il; i <= jl; i++) {
        for (int j = ic; j <= jc; j++) {
            matrix[j-ic][i-il] = mat[j][i];
        }
    }

    Matrice result(matrix, c);
    //cout << " nb col " << c << "\n";
   // result.affiche();
    cout << "\n";
    return result;
}


int *Matrice::get_dim(){
    return dim;
}


