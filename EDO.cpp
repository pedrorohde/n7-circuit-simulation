#include "EDO.h"

//// EDO ///////////////////////////////////////////////

// constructeur défaut
EDO::EDO(){
	// on définit les attributs
	t_pre = 0; h = 0;
}

// destructeur
EDO::~EDO(){
}

//// EDO1 ///////////////////////////////////////////////

// constructeur défaut
EDO1::EDO1(){
	// on définit les attributs avec des valeurs standard
	U = 0; // condition initiale y(0) = 0
	t_pre = 0; h = 0;
}

// destructeur
EDO1::~EDO1(){
}

// constructeur
EDO1::EDO1(float y0){
    // on définit l'attribut avec le paramètre
	U = y0; // condition initiale y(0)
	// les autres attributs restent avec ces valeurs standard
	t_pre = 0; h = 0;
}

// méthode d'Euler de résolution d'EDOs
float EDO1::euler(float up, float t) {
	h = t-t_pre; // on calcule le pas
	// le pas peut changer d'une itération à l'autre
    U = U + h*up; // on calcule U (Euler)
    t_pre = t; // on sauvegarde le temps pour la prochaine itération
	return U;
}

// méthode pour obtenir la valeur de U
float EDO1::getU(unsigned short i) {
    // le paramètre i n'importe pas puisque U n'est pas un vecteur
	return U;
}

//// EDO2 ///////////////////////////////////////////////

// constructeur défaut
EDO2::EDO2(){
	// on définit les attributs avec des valeurs standard
	U[0] = 0; // condition initiale y(0) = 0
	U[1] = 0; // condition initiale y'(0) = 0
	t_pre = 0; h = 0;
}

// destructeur
EDO2::~EDO2(){
}

// constructeur
EDO2::EDO2(float y0, float yp0){
    // on définit les attributs avec les paramètres
	U[0] = y0; // condition initiale y(0)
	U[1] = yp0; // condition initiale y'(0)
	// les autres attributs restent avec ces valeurs standard
	t_pre = 0; h = 0;
}

// méthode d'Euler de résolution d'EDOs
float EDO2::euler(float u2p, float t) {
	h = t-t_pre; // on calcule le pas
	// le pas peut changer d'une itération à l'autre
    // on calcule le vecteur U (d'après Euler):
    U[0] = U[0] + h*U[1];
    U[1] = U[1] + h*u2p;
	t_pre = t; // on sauvegarde le temps pour la prochaine itération
	return U[0];
}

// méthode pour obtenir la valeur de U[i]
float EDO2::getU(unsigned short i) {
	if (i <= 1) return U[i];
	else return 0;
}
