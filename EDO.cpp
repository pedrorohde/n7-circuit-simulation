#include "EDO.h"

//// EDO ///////////////////////////////////////////////

// constructeur d�faut
EDO::EDO(){
	// on d�finit les attributs
	t_pre = 0; h = 0;
}

// destructeur
EDO::~EDO(){
}

//// EDO1 ///////////////////////////////////////////////

// constructeur d�faut
EDO1::EDO1(){
	// on d�finit les attributs avec des valeurs standard
	U = 0; // condition initiale y(0) = 0
	t_pre = 0; h = 0;
}

// destructeur
EDO1::~EDO1(){
}

// constructeur
EDO1::EDO1(float y0){
    // on d�finit l'attribut avec le param�tre
	U = y0; // condition initiale y(0)
	// les autres attributs restent avec ces valeurs standard
	t_pre = 0; h = 0;
}

// m�thode d'Euler de r�solution d'EDOs
float EDO1::euler(float up, float t) {
	h = t-t_pre; // on calcule le pas
	// le pas peut changer d'une it�ration � l'autre
    U = U + h*up; // on calcule U (Euler)
    t_pre = t; // on sauvegarde le temps pour la prochaine it�ration
	return U;
}

// m�thode pour obtenir la valeur de U
float EDO1::getU(unsigned short i) {
    // le param�tre i n'importe pas puisque U n'est pas un vecteur
	return U;
}

//// EDO2 ///////////////////////////////////////////////

// constructeur d�faut
EDO2::EDO2(){
	// on d�finit les attributs avec des valeurs standard
	U[0] = 0; // condition initiale y(0) = 0
	U[1] = 0; // condition initiale y'(0) = 0
	t_pre = 0; h = 0;
}

// destructeur
EDO2::~EDO2(){
}

// constructeur
EDO2::EDO2(float y0, float yp0){
    // on d�finit les attributs avec les param�tres
	U[0] = y0; // condition initiale y(0)
	U[1] = yp0; // condition initiale y'(0)
	// les autres attributs restent avec ces valeurs standard
	t_pre = 0; h = 0;
}

// m�thode d'Euler de r�solution d'EDOs
float EDO2::euler(float u2p, float t) {
	h = t-t_pre; // on calcule le pas
	// le pas peut changer d'une it�ration � l'autre
    // on calcule le vecteur U (d'apr�s Euler):
    U[0] = U[0] + h*U[1];
    U[1] = U[1] + h*u2p;
	t_pre = t; // on sauvegarde le temps pour la prochaine it�ration
	return U[0];
}

// m�thode pour obtenir la valeur de U[i]
float EDO2::getU(unsigned short i) {
	if (i <= 1) return U[i];
	else return 0;
}
