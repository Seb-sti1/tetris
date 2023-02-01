#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>
#include "matrix.h"

/*

SOUTENANCE :
Aux alentours des vacances de février
Créneaux proposés sur des trous dans l'emploi du temps
Au moins 48h avant soutenance, envoi du projet (lien GitHub) à l'examinateur
Document présentant ce que fait le logiciel avec quelques schémas présentant l'architecture logiciel

Présentation :
Présenter la démarche réalisée pour créer le logiciel 
Analyse des fonctions
Déduction des objets
Possibilités d'évolution (maintenance, amélioration, ajout de fonctionnalités)
Présenter le fonctionnement du logiciel (aspect architecture ou aspect code)
Il ne faut pas présenter le code en détail
Code lisible, commentaires utiles/pertinents uniquement

*/

int main(){

    int rows = 4;
    int cols = 5;
    Matrix<int> Mat(rows, cols);


    Mat.Print();

    Matrix<int> MatB = Mat;

    printf("%d\n", Mat.GetNumColumns());

    MatB.To(2,2,5);
    std::cout << MatB.At(2,2) << std::endl;

    MatB.Print();

    int tetromino_rows = 4;
    int tetromino_cols = 3;

    Matrix<bool> I_matrix(tetromino_rows, tetromino_cols);
    for(int i=0; i<tetromino_rows; i++) I_matrix.To(i,1,true);

    I_matrix.Print();

    Matrix<bool> O_matrix(tetromino_rows, tetromino_cols);
    O_matrix.To(0,0,true);
    O_matrix.To(0,1,true);
    O_matrix.To(1,0,true);
    O_matrix.To(1,1,true);
    O_matrix.Print();

    Matrix<bool> T_matrix(tetromino_rows, tetromino_cols);
    T_matrix.To(0,0,true);
    T_matrix.To(0,1,true);
    T_matrix.To(0,2,true);
    T_matrix.To(1,1,true);
    T_matrix.Print();

    Matrix<bool> L_matrix(tetromino_rows, tetromino_cols);
    L_matrix.To(0,0,true);
    L_matrix.To(1,0,true);
    L_matrix.To(2,0,true);
    L_matrix.To(2,1,true);
    L_matrix.Print();

    Matrix<bool> J_matrix(tetromino_rows, tetromino_cols);
    J_matrix.To(0,1,true);
    J_matrix.To(1,1,true);
    J_matrix.To(2,1,true);
    J_matrix.To(2,0,true);
    J_matrix.Print();

    Matrix<bool> Z_matrix(tetromino_rows, tetromino_cols);
    Z_matrix.To(0,0,true);
    Z_matrix.To(0,1,true);
    Z_matrix.To(1,1,true);
    Z_matrix.To(1,2,true);
    Z_matrix.Print();

    Matrix<bool> S_matrix(tetromino_rows, tetromino_cols);
    S_matrix.To(0,1,true);
    S_matrix.To(0,2,true);
    S_matrix.To(1,0,true);
    S_matrix.To(1,1,true);
    S_matrix.Print();

}