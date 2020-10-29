#define PI 3.14159265358979323846
#include "source.h"

//// source //////////////////////////////////////////////////

// constructeur défaut
source::source(){
	// on définit les attributs avec des valeurs standard
	Vo = 1;
	phi = 0;}

// constructeur
source::source(float A, float start){
    // on définit les attributs avec les paramètres précisés
	Vo = A;
	phi = start;}

// destructeur
source::~source(){
}

///// periodique ///////////////////////////////////////////

// constructeur défaut
periodique::periodique(){
    // on définit les attributs avec des valeurs standard
	Vo = 1;
	T = 1;
	phi = 0;}

// constructeur
periodique::periodique(float A, float start, float period){
    // on définit les attributs avec les paramètres précisés
	Vo = A;
	T = period;
	phi = start;}

// destructeur
periodique::~periodique(){
}

///// non_periodique ///////////////////////////////////////

// constructeur défaut
non_periodique::non_periodique(){
    // on définit les attributs avec des valeurs standard
	Vo = 1;
	phi = 0;}

// constructeur
non_periodique::non_periodique(float A, float start){
    // on définit les attributs avec les paramètres précisés
	Vo = A;
	phi = start;}

// destructeur
non_periodique::~non_periodique(){
}

///// rect ///////////////////////////////////////////////////

// constructeur défaut
rect::rect(){
    // on définit les attributs avec des valeurs standard
	Vo = 1;
	duree = 100*NANO;
	phi = 50*NANO;}

// constructeur
rect::rect(float A, float start, float Thigh){
    // on définit les attributs avec les paramètres précisés
	Vo = A;
	duree = Thigh;
	phi = start;}

// destructeur
rect::~rect(){
}

// pour calculer la tension de la source
float rect::Ve(float t){
    // Ve = A si t entre phi et durée
	if (t < 0) return 0;
	else if (t >= phi && t < phi+duree) return Vo;
	else return 0;
}

///// creneau /////////////////////////////////////////////////

// constructeur défaut
creneau::creneau(){
    // on définit les attributs avec des valeurs standard
	Vo = 1;
	T = 100*NANO;
	phi = 0;
	duty_cycle = 0.5;}

// constructeur
creneau::creneau(float A, float start, float period, float dc){
    // on définit les attributs avec les paramètres précisés
	Vo = A;
	T = period;
	phi = start;
	duty_cycle = dc;}

// destructeur
creneau::~creneau(){
}

// pour calculer la tension de la source
float creneau::Ve(float t){
	if(t < 0)
		return 0;
	while(phi >= T) phi -= T; // normalisation de phi (phi -> [0,T[)
	t += (T-phi);
	while(t >= T) t -= T; // normalisation de t (t -> [0,T[)
	if(t < duty_cycle*T) return Vo; // Ve = A si t E [0, duty_cycle[)
	else return 0;

}

///// echelon //////////////////////////////////////////////////

// constructeur défaut
echelon::echelon(){
    // on définit les attributs avec des valeurs standard
	Vo = 1;
	phi = 1*NANO;}

// constructeur
echelon::echelon(float A, float start){
    // on définit les attributs avec les paramètres précisés
	Vo = A;
	phi = start;}

// destructeur
echelon::~echelon(){
}

// pour calculer la tension de la source
float echelon::Ve(float t){
	if (t >= phi) return Vo; // Ve = toujours A après phi secondes
	else return 0;
}

///// triang //////////////////////////////////////////////////

// constructeur défaut
triang::triang(){
    // on définit les attributs avec des valeurs standard
	Vo = 1;
	T = 100*NANO;
	phi = 0;}

// constructeur
triang::triang(float A, float start, float period){
    // on définit les attributs avec les paramètres précisés
	Vo = A;
	T = period;
	phi = start;}

// destructeur
triang::~triang(){
}

// pour calculer la tension de la source
float triang::Ve(float t){
	if(t < 0) return 0;
	t -= phi; // normalisation de t
	while(t >= T) t -= T; // normalisation de t
	// droites du triangle:
	if (t <= 0) return (-(2*Vo/T)*(t));
    else if (t <= T/2) return ((2*Vo/T)*(t));
	else return (Vo - (2*Vo/T)*(t-T/2));

}

///// sinus //////////////////////////////////////////////////

// constructeur défaut
sinus::sinus(){
    // on définit les attributs avec des valeurs standard
	Vo = 1;
	T = 100*NANO;
	phi = 0;}

// constructeur
sinus::sinus(float A, float start, float period){
    // on définit les attributs avec les paramètres précisés
	Vo = A;
	T = period;
	phi = start;}

// destructeur
sinus::~sinus(){
}

// pour calculer la tension de la source
float sinus::Ve(float t){
	if (t < 0) return 0;
	else return Vo*sin((2*PI/T)*t - phi); // sinus défini en <math.h>
}
