#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>
#include "tetromino.h"
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
    Matrix Mat(rows, cols);

    Mat.Print();

    Matrix MatB = Mat;

    std::cout << MatB.At(2,2) << std::endl;

    MatB.Print();

}