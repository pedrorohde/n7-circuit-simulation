#define PI 3.14159265358979323846
#include "source.h"

//// source //////////////////////////////////////////////////

// constructeur d�faut
source::source(){
	// on d�finit les attributs avec des valeurs standard
	Vo = 1;
	phi = 0;}

// constructeur
source::source(float A, float start){
    // on d�finit les attributs avec les param�tres pr�cis�s
	Vo = A;
	phi = start;}

// destructeur
source::~source(){
}

///// periodique ///////////////////////////////////////////

// constructeur d�faut
periodique::periodique(){
    // on d�finit les attributs avec des valeurs standard
	Vo = 1;
	T = 1;
	phi = 0;}

// constructeur
periodique::periodique(float A, float start, float period){
    // on d�finit les attributs avec les param�tres pr�cis�s
	Vo = A;
	T = period;
	phi = start;}

// destructeur
periodique::~periodique(){
}

///// non_periodique ///////////////////////////////////////

// constructeur d�faut
non_periodique::non_periodique(){
    // on d�finit les attributs avec des valeurs standard
	Vo = 1;
	phi = 0;}

// constructeur
non_periodique::non_periodique(float A, float start){
    // on d�finit les attributs avec les param�tres pr�cis�s
	Vo = A;
	phi = start;}

// destructeur
non_periodique::~non_periodique(){
}

///// rect ///////////////////////////////////////////////////

// constructeur d�faut
rect::rect(){
    // on d�finit les attributs avec des valeurs standard
	Vo = 1;
	duree = 100*NANO;
	phi = 50*NANO;}

// constructeur
rect::rect(float A, float start, float Thigh){
    // on d�finit les attributs avec les param�tres pr�cis�s
	Vo = A;
	duree = Thigh;
	phi = start;}

// destructeur
rect::~rect(){
}

// pour calculer la tension de la source
float rect::Ve(float t){
    // Ve = A si t entre phi et dur�e
	if (t < 0) return 0;
	else if (t >= phi && t < phi+duree) return Vo;
	else return 0;
}

///// creneau /////////////////////////////////////////////////

// constructeur d�faut
creneau::creneau(){
    // on d�finit les attributs avec des valeurs standard
	Vo = 1;
	T = 100*NANO;
	phi = 0;
	duty_cycle = 0.5;}

// constructeur
creneau::creneau(float A, float start, float period, float dc){
    // on d�finit les attributs avec les param�tres pr�cis�s
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

// constructeur d�faut
echelon::echelon(){
    // on d�finit les attributs avec des valeurs standard
	Vo = 1;
	phi = 1*NANO;}

// constructeur
echelon::echelon(float A, float start){
    // on d�finit les attributs avec les param�tres pr�cis�s
	Vo = A;
	phi = start;}

// destructeur
echelon::~echelon(){
}

// pour calculer la tension de la source
float echelon::Ve(float t){
	if (t >= phi) return Vo; // Ve = toujours A apr�s phi secondes
	else return 0;
}

///// triang //////////////////////////////////////////////////

// constructeur d�faut
triang::triang(){
    // on d�finit les attributs avec des valeurs standard
	Vo = 1;
	T = 100*NANO;
	phi = 0;}

// constructeur
triang::triang(float A, float start, float period){
    // on d�finit les attributs avec les param�tres pr�cis�s
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

// constructeur d�faut
sinus::sinus(){
    // on d�finit les attributs avec des valeurs standard
	Vo = 1;
	T = 100*NANO;
	phi = 0;}

// constructeur
sinus::sinus(float A, float start, float period){
    // on d�finit les attributs avec les param�tres pr�cis�s
	Vo = A;
	T = period;
	phi = start;}

// destructeur
sinus::~sinus(){
}

// pour calculer la tension de la source
float sinus::Ve(float t){
	if (t < 0) return 0;
	else return Vo*sin((2*PI/T)*t - phi); // sinus d�fini en <math.h>
}
