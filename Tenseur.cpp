#include "Matrice.h" 
#include <iostream>
#include "Vector.h" 
#include "Tenseur.h"
#include <assert.h>
using namespace std;


// basic constructor
Tenseur::Tenseur(int t[], int ordre) {

    order = ordre;
    nbelts = 1;
    dims = new int[order];

    for (int i = 0; i < order; i++) {

        dims[i] = t[i];
        nbelts = nbelts * dims[i];

    }

    tensor = *new Vector(nbelts);

}


// 2d constructor
Tenseur::Tenseur(int t[], int ordre, Vector v) {

    order = ordre;
    nbelts = 1;
    dims = new int[order];
    for (int i = 0; i < order; i++) {

        dims[i] = t[i];
        nbelts = nbelts * dims[i];

    }

    tensor = *new Vector(v);

}




// phi inverse for kth mode constructor

int* phi_inverse_k(int j, int order, int dims[], int k, int ik) {

    static int* indexes = new int[order];

    int f_t = j;

    indexes[order-1] = f_t % dims[order-1];

    if ( order > 1) {
        for (int t = order - 2; t  >= k   ; t--) {
            // t = order -1; t >= k+1; 
       

            f_t = (f_t - indexes[t+1]) / dims[t+1] + 1;
            indexes[t] = f_t % dims[t];

       

        }
    
        // breaking the chain : k step
        indexes[k - 1] = ik;

        // breaking the chain : k-1 step

        f_t = (f_t - indexes[k]) / dims[k] + 1;
        indexes[k - 2] = f_t % dims[k - 2];

        for (int t = k-3; t >= 0; t--) {
            // t = k*2, t = 1;
            f_t = (f_t - indexes[t + 1]) / dims[t + 1] + 1;
            indexes[t] = f_t % dims[t];

        }

    }
    return indexes;

}







int phi( int order, int dims[], int indexes[] ) {


    int index = indexes[order - 1];
    int prod = 1;
    for (int i = order -2 ; i >= 0; i-- ){

        prod = prod * dims[i+1];
        index = index + prod*(indexes[i] - 1);
            
    }

    return index;
}





// 3d constructor
Tenseur::Tenseur(int t[], int ordre, Matrice A, int k) {

    order = ordre;
    nbelts = 1;

    assert((k <= ordre && k!=0) && "Tensor Constructor: k > order");
    dims = new int[order];
    for (int i = 0; i < order; i++) {

        dims[i] = t[i];
        nbelts = nbelts * dims[i];

    }


    int* indexes;
    int index;
     
    float* tab = new float[nbelts];
    
    for (int j = 0; j < A.dim[1]; j++) { //  nb col of the transpose
        for (int i= 0; i < A.dim[0]; i++) {
            
            indexes = phi_inverse_k(j+1, order, dims, k, i+1);

            index = phi( order,  dims,  indexes);

            
            tab[index-1] = A[j][i];
            
        }
    }
    tensor = *new Vector(tab, nbelts);

}



// Copy constructor
Tenseur::Tenseur( Tenseur& t) {

    order = t.order;
    nbelts = t.nbelts;
    dims = new int[order];
    for (int i = 0; i < order; i++) {

        dims[i] = t.dims[i];
    }
        
        
    
    tensor = *new Vector(t.tensor);

}




// Destructor
Tenseur::~Tenseur() {
    delete[]dims;
    tensor.~Vector();
}


//printing

void Tenseur::affiche() {

    tensor.affiche();
}


// Assignment

Tenseur& Tenseur::operator=(const Tenseur& t) {



    if (this != &t) {
        delete[]dims;
        order = t.order;
        nbelts = t.nbelts;
        dims = new int[order];
        for (int i = 0; i < order; i++) {

            dims[i] = t.dims[i];
        }

        tensor = t.tensor;
        
    }
    return *this;
}




//[] operator

float Tenseur::operator[](int index)
{


    assert(nbelts > index && " Matrix Index out of bound");
    // return value
    return tensor[index];
}



/// Addition
Tenseur  Tenseur::operator+(Tenseur& t) {

    for (int i = 0; i < order; i++) {

        assert((dims[i] == t.dims[i]) && "Addition: Both Tensor do not have same dim");
        
    }
   


    Vector sum(nbelts);
    sum = t.tensor + tensor; // nb col
    
    Tenseur result (dims, order, sum);
    return result;
}




/// Substract
Tenseur  Tenseur::operator-(Tenseur& t) {

    for (int i = 0; i < order; i++) {

        assert((dims[i] == t.dims[i]) && "Substraction: Both Tensor do not have same dim");

    }


    Vector diff(nbelts);
    diff = t.tensor - tensor; // nb col

    Tenseur result(dims, order, diff);
    return result;
}


// modal unfolding 

int* phi_inverse(int i, int order, int dims[]) {

    static int* indexes = new int[order];

    int f_t = i;

    indexes[order - 1] = f_t % dims[order - 1];

    if (order > 1) {
        for (int t = order - 2; t >= 0; t--) {
            // t = order -1; t >= k+1; 


            f_t = (f_t - indexes[t + 1]) / dims[t + 1] + 1;
            indexes[t] = f_t % dims[t];
        }

        
    }
    return indexes;

}






Matrice Tenseur::mode(int k) {

    assert((k<=order && k !=0) && " modal unfolding : k is not less than order");

    Matrice  A = *new Matrice(dims[k - 1], nbelts/dims[k-1]);
    int* indexes;
    int index;
    int* dims_k = new int[order - 1];
    int ik;
    int jk;
    for (int i = 0; i < nbelts; i++) {
        
        
        indexes = phi_inverse(i,order,  dims);

        ik = indexes[k - 1];

        for (int t = 0; t < k-1; t++) {
            
            dims_k[t] = dims[t];
           
        }


        for (int t = k+1-1; t < order; t++) {
            

            dims_k[t-1] = dims[t];

        }

        jk = phi(order-1, dims_k, indexes);

        A[jk][ik] = tensor[i];

    }


    return A;

}


// modal product 

Tenseur pmode(Tenseur t, Matrice M, int k) {

    int* dims_k = new int[t.order];
    int* indexes;
    int* indexes_S;
    int index_S;
    int* dim_M;
    dim_M = M.get_dim();

    for (int i = 0; i< k - 1; i++) {

        dims_k[i] = t.dims[i];

    }

    
    dims_k[k - 1] = dim_M[0];// nb lines

    for (int i = k + 1 - 1; i < t.order; i++) {


        dims_k[i] = t.dims[i];

    }



    //

    int nbelts_k = 1;
    for (int i = 0; i < t.order; i++) {

        nbelts_k = nbelts_k * dims_k[i];
    }

    float*  result = new float(nbelts_k );


    // loooping through t vector
    for (int i = 0; i < nbelts_k; i++) {
    
        indexes = phi_inverse(i, t.order, dims_k);
        for (int  l= 0; l< t.order; l++) {

            indexes_S[l] = indexes[l];
        }

       
        int value = 0;
        for (int j = 0; j < t.dims[k - 1]; j++) {

            indexes_S[k - 1] = j;
            index_S = phi(t.order, t.dims, indexes_S);
            value = value + M[j][indexes[k - 1]] * t[index_S];

        }

        result[i] = value;

    }

    return *new Tenseur(dims_k, t.order, *new Vector(result, nbelts_k));
}
