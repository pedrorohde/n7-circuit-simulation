#include <iostream>
#include <math.h>
#include <fstream>
// quelques constantes utiles:
#define MILLI 0.001
#define MICRO 0.000001
#define NANO 0.000000001
#define PICO 0.000000000001

// classes des sources:

// classe m�re g�nerale
class source{

	public:
		source(); // constructeur d�faut
		source(float A, float start); // constructeur
		~source(); // destructeur
		// m�thode:
		virtual float Ve(float t) = 0; // pour calculer la tension de la source
		// m�thode est purement virtuelle => classe abstraite
        // cette m�thode sera surcharg�e par les filles
	protected: // attributs priv�s qui peuvent �tre acc�d�s par les filles
               // toutes les filles en auront besoin
		float Vo, phi; // l'amplitude et la d�calage
};

// classe des sources p�riodiques:
class periodique : public source{ // classe fille qui h�rite de source
	public:
		periodique(); // constructeur d�faut
		periodique(float A, float start, float period); // constructeur
		// arguments: amplitude, d�calage et p�riode
		~periodique(); // destructeur
		// m�thode:
		virtual float Ve(float t) = 0; // pour calculer la tension de la source
		// m�thode est purement virtuelle => classe abstraite
        // cette m�thode sera surcharg�e par les filles
    protected: // attribut priv� qui peut �tre acc�d� par les filles
               // toutes les filles en auront besoin
        float T; // p�riode
};

// classe des sources non-p�riodiques:
class non_periodique : public source{ // classe fille qui h�rite de source
	public:
		non_periodique(); // constructeur d�faut
		non_periodique(float A, float start); // constructeur
		// arguments: amplitude, d�calage
		~non_periodique(); // destructeur
		// m�thode:
		virtual float Ve(float t) = 0; // pour calculer la tension de la source
		// m�thode est purement virtuelle => classe abstraite
        // cette m�thode sera surcharg�e par les filles
};

// classe des sources r�ctangulaires:
class rect : public non_periodique{ // classe fille qui h�rite de non_periodique
	public:
		rect(); // constructeur d�faut
		rect(float A, float start, float Thigh); // constructeur
		// arguments: amplitude, d�calage, dur�e du signal
		~rect(); // destructeur
		// m�thode surcharg�e:
		float Ve(float t); // pour calculer la tension de la source
    private: // attribut priv�
        float duree; // dur�e du signal
};

// classe des sources cr�neaux:
class creneau : public periodique{ // classe fille qui h�rite de periodique
	public:
		creneau(); // constructeur d�faut
		creneau(float A, float start, float period, float dc); // constructeur
		// arguments: amplitude, d�calage, p�riode, rapport cyclique
		~creneau(); // destructeur
		// m�thode surcharg�e:
		float Ve(float t); // pour calculer la tension de la source
    private: // attribut priv�
		float duty_cycle; // rapport cyclique du signal
};

// classe des sources �chelon:
class echelon : public non_periodique{ // classe fille qui h�rite de non_periodique
	public:
		echelon(); // constructeur d�faut
		echelon(float A, float start); // constructeur
		// arguments: amplitude, d�calage
		~echelon(); // destructeur
		// m�thode surcharg�e:
		float Ve(float t); // pour calculer la tension de la source
};

// classes des sources triangulaires:
class triang : public periodique{ // classe fille qui h�rite de periodique
	public:
		triang(); // constructeur d�faut
		triang(float A, float start, float period); // constructeur
		// arguments: amplitude, d�calage, p�riode
		~triang(); // destructeur
		// m�thode surcharg�e:
		float Ve(float t); // pour calculer la tension de la source
};

// classes des sources sinuso�dales:
class sinus : public periodique{ // classe fille qui h�rite de periodique
	public:
		sinus(); // constructeur d�faut
		sinus(float A, float start, float period); // constructeur
		// arguments: amplitude, d�calage, p�riode
		~sinus(); // destructeur
		// m�thode surcharg�e:
		float Ve(float t); // pour calculer la tension de la source
};
