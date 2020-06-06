// Projetcpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Done by Christian Alaka . Code inspired by OpenClassroom.fr

#include <iostream>

#include <assert.h> 
#include "Vector.h" 
#include  "Matrice.h"
#include  "Tenseur.h"
using namespace std;





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


 int main()
 {
     std::cout << "Hello World!\n" << 0 << "\n";
     // Validation 1
     float* arr = new float[3]{ 1,1,1 };
     Vector u(arr, 3);
     arr = new float[4]{ 3,4,0,0 };
     Vector v(arr, 4);

     u.affiche();
     v.affiche();

     Vector t(u);
     Vector temp(new float[3]{ 1,1,0 }, 3);
     u = temp;
     cout << "t:";
     t.affiche();
     cout << "u:";
     u.affiche();
     float norme = v.norm();
     cout << " \n dot product " << dot(v, v);
     cout << "\n norm of v " << norme;
     Vector w(2);

     Vector v_normed(2);
     v_normed = v * (1 / norme);
     
     // 6 - subvec
     w = v.subvec(1, 3);
     cout << "\n w:";
     w.affiche();
     cout << "\n v:";
     v.affiche();
     Vector somme(2);
     Vector diff(2);
     somme = (u + w);
     diff = u - w;
     cout << "u + w: \n";
     somme.affiche();
     diff.affiche();

     /********************  MATRICE        ********************************/
    
     // creating B matrix
     float* arr2 = new float[2]{ -2, 0 };
     Vector u2(arr2, 2);
     float* arr3 = new float[2]{ 3, 1 };
     Vector u3(arr3, 2);

     Vector* matrix = new Vector[2];
     matrix[0] = u2;
   
     matrix[1]= u3;
    
     Matrice B(matrix, 2);
     cout << "B \n";
     B.affiche();


     // creating A matrix 
     matrix = new Vector[3];
    
        
         
     arr2 = new float[3]{ 1,1, 0 };
     u2 = Vector(arr2, 3);
     matrix[0] = u2;

     arr2 = new float[3]{ -0.5, 2 ,-1 };
     u2 = Vector(arr2, 3);
     matrix[1] = u2;


     arr2 = new float[3]{ 0 ,-1 ,1 };
     u2 = Vector(arr2, 3);
     matrix[2] = u2;

     Matrice A(matrix, 3);
     cout << "A \n";
     A.affiche();

     Matrice C(2, 2);
     C = B;
     B[0][1] = 0;

     cout << "\n B \n";
     B.affiche();

     cout << "\n C \n";
     C.affiche();

     //3- Submatrix

     Matrice D(3, 2);
     D = A.submat(0, 2, 0, 1);

     cout << "D \n";
     D.affiche();

     // 4- diagonal
    

     u2 = Vector(new float[3]{ 3,2,1 }, 3);
     
     Matrice E(u2);
     
     cout <<" \n E \n";
     E.affiche();

     //5- sum, diff, product

     cout << " \n calculs \n";

     Matrice somme_M(2, 2);
     Matrice diff_M(2, 2);
     Matrice prod_M(2, 2);
     somme_M = B + C;

     cout << " \n calculs 2 \n";
     diff_M = C - B;

     cout << " \n calculs 3 \n";
     prod_M = D * C;
    
     cout << " \n B+C  \n";
     somme_M.affiche();

     cout << " \n C-B  \n";
     diff_M.affiche();

     cout << " \n D*C \n";
     prod_M.affiche();

     //6 - norm frobenius

     // default constructor ??????
     //7 - operation
     Matrice operation_M(1,1);
     Matrice B_T(1, 1);
     
     B_T = B.transpose();
     operation_M =  (B + B_T) * 0.5;
     cout << " \n B trans \n"  ;
     B_T.affiche();
     cout << "\n  0.5(B+B^t \n";
     operation_M.affiche();

     



     /*/////*  PART 1 TENSORS
******************************************************************************///////////////

int dims[3] = { 3, 4, 2 };

     int* indexes = phi_inverse_k(1, 3, dims, 2, 2);

     int index = phi(3, dims, indexes);

     cout << "  index " << endl;

     for (int i = 0; i < 3  ; i++) {
         cout << indexes[i] << ";";
     }
     cout << endl;

     cout << "  index 1er" << endl;
     cout << index << endl;

     

     return 0;
 }
