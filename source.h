#include <iostream>
#include <math.h>
#include <fstream>
// quelques constantes utiles:
#define MILLI 0.001
#define MICRO 0.000001
#define NANO 0.000000001
#define PICO 0.000000000001

// classes des sources:

// classe mère génerale
class source{

	public:
		source(); // constructeur défaut
		source(float A, float start); // constructeur
		~source(); // destructeur
		// méthode:
		virtual float Ve(float t) = 0; // pour calculer la tension de la source
		// méthode est purement virtuelle => classe abstraite
        // cette méthode sera surchargée par les filles
	protected: // attributs privés qui peuvent être accédés par les filles
               // toutes les filles en auront besoin
		float Vo, phi; // l'amplitude et la décalage
};

// classe des sources périodiques:
class periodique : public source{ // classe fille qui hérite de source
	public:
		periodique(); // constructeur défaut
		periodique(float A, float start, float period); // constructeur
		// arguments: amplitude, décalage et période
		~periodique(); // destructeur
		// méthode:
		virtual float Ve(float t) = 0; // pour calculer la tension de la source
		// méthode est purement virtuelle => classe abstraite
        // cette méthode sera surchargée par les filles
    protected: // attribut privé qui peut être accédé par les filles
               // toutes les filles en auront besoin
        float T; // période
};

// classe des sources non-périodiques:
class non_periodique : public source{ // classe fille qui hérite de source
	public:
		non_periodique(); // constructeur défaut
		non_periodique(float A, float start); // constructeur
		// arguments: amplitude, décalage
		~non_periodique(); // destructeur
		// méthode:
		virtual float Ve(float t) = 0; // pour calculer la tension de la source
		// méthode est purement virtuelle => classe abstraite
        // cette méthode sera surchargée par les filles
};

// classe des sources réctangulaires:
class rect : public non_periodique{ // classe fille qui hérite de non_periodique
	public:
		rect(); // constructeur défaut
		rect(float A, float start, float Thigh); // constructeur
		// arguments: amplitude, décalage, durée du signal
		~rect(); // destructeur
		// méthode surchargée:
		float Ve(float t); // pour calculer la tension de la source
    private: // attribut privé
        float duree; // durée du signal
};

// classe des sources créneaux:
class creneau : public periodique{ // classe fille qui hérite de periodique
	public:
		creneau(); // constructeur défaut
		creneau(float A, float start, float period, float dc); // constructeur
		// arguments: amplitude, décalage, période, rapport cyclique
		~creneau(); // destructeur
		// méthode surchargée:
		float Ve(float t); // pour calculer la tension de la source
    private: // attribut privé
		float duty_cycle; // rapport cyclique du signal
};

// classe des sources échelon:
class echelon : public non_periodique{ // classe fille qui hérite de non_periodique
	public:
		echelon(); // constructeur défaut
		echelon(float A, float start); // constructeur
		// arguments: amplitude, décalage
		~echelon(); // destructeur
		// méthode surchargée:
		float Ve(float t); // pour calculer la tension de la source
};

// classes des sources triangulaires:
class triang : public periodique{ // classe fille qui hérite de periodique
	public:
		triang(); // constructeur défaut
		triang(float A, float start, float period); // constructeur
		// arguments: amplitude, décalage, période
		~triang(); // destructeur
		// méthode surchargée:
		float Ve(float t); // pour calculer la tension de la source
};

// classes des sources sinusoïdales:
class sinus : public periodique{ // classe fille qui hérite de periodique
	public:
		sinus(); // constructeur défaut
		sinus(float A, float start, float period); // constructeur
		// arguments: amplitude, décalage, période
		~sinus(); // destructeur
		// méthode surchargée:
		float Ve(float t); // pour calculer la tension de la source
};
