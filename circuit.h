#include <iostream>
#include "source.h"
#include "EDO.h"

// classes des circuits:

// classe m�re g�nerale
class circuit{
public: circuit(); // constructeur d�faut
        circuit(source *gen); // constructeur
        // argument: source du circuit
        ~circuit(); // destructeur
        // m�thodes:
        float getVg(); // pour calculer la tension de la source
        virtual float Vout(float t) = 0; // pour calculer la tension de sortie
        // Vout: purement virtuelle => classe circuit abstraite
        // cette m�thode sera surcharg�e par les filles
protected: // attributs priv�s qui peuvent �tre acc�d�s par les filles
           // toutes les filles en auront besoin
    float Vg,Vs,Vsp;//,t_pre,h,Vsp_rk2,Vsp_rk3,Vsp_rk4; // tension de la source, de sortie et d�riv�e de la sortie
    source *src; // source du circuit
    EDO *eq_diff; // EDO du circuit
};

// classe des circuits d'ordre 1
class circuit_1 : public circuit{ // classe fille qui h�rite de circuit
public: circuit_1(); // constructeur d�faut
        circuit_1(source *gen); // constructeur
        // argument: source du circuit
        circuit_1(source *gen, float Vout0); // constructeur
        // arguments: source du circuit et Vs(0)
        ~circuit_1(); // destructeur
        // m�thode:
        virtual float Vout(float t) = 0; // pour calculer la tension de sortie
        // m�thode purement virtuelle => classe circuit_1 abstraite
        // cette m�thode sera surcharg�e par les filles
};

// classe des circuits d'ordre 2
class circuit_2 : public circuit{ // classe fille qui h�rite de circuit
public: circuit_2(); // constructeur d�faut
        circuit_2(source *gen); // constructeur
        // argument: source du circuit
        circuit_2(source *gen, float Vout0, float Voutp0); // constructeur
        // arguments: source du circuit, Vs(0) et Vs'(0)
        ~circuit_2(); // destructeur
        // m�thode:
        virtual float Vout(float t) = 0; // pour calculer la tension de sortie
        // m�thode purement virtuelle => classe circuit_2 abstraite
        // cette m�thode sera surcharg�e par les filles
protected: // attribut priv� qui peut �tre acc�d� par les filles
           // toutes les filles en auront besoin
    float Vs2p; // Vs''(ti) - d�riv�e seconde du signal de sortie
};

// classe des circuits du type A (1er ordre)
class circuitA : public circuit_1{ // classe fille qui h�rite de circuit_1
public: circuitA(); // constructeur d�faut
        circuitA(source *gen); // constructeur
        // argument: source du circuit
        circuitA(source *gen, float Vout0, float Res1, float Cap1); // constructeur
        // arguments: source du circuit, Vs(0), R1 et C1
        ~circuitA(); // destructeur
        // m�thode surcharg�e:
        float Vout(float t); // pour calculer la tension de sortie
private: // attributs priv�s
    float R1,C1; // R1 et C1
};

// classe des circuits du type B (2e ordre)
class circuitB : public circuit_2{  // classe fille qui h�rite de circuit_2
public: circuitB(); // constructeur d�faut
        circuitB(source *gen); // constructeur
        // argument: source du circuit
        circuitB(source *gen, float Vout0, float Voutp0, float Res1, float Cap1, float Ind1); // constructeur
        // arguments: source du circuit, Vs(0), Vs'(0), R1, C1 et L1
        ~circuitB(); // destructeur
        // m�thode surcharg�e:
        float Vout(float t); // pour calculer la tension de sortie
private: // attributs priv�s
    float L1,R1,C1; // L1, R1 et C1
};

// classe des circuits du type C (1er ordre)
class circuitC : public circuit_1{ // classe fille qui h�rite de circuit_1
public: circuitC(); // constructeur d�faut
        circuitC(source *gen); // constructeur
        // argument: source du circuit
        circuitC(source *gen, float Vout0, float Res1, float Cap1, float Res2); // constructeur
        // arguments: source du circuit, Vs(0), R1, C1 et R2
        ~circuitC(); // destructeur
        // m�thode surcharg�e:
        float Vout(float t); // pour calculer la tension de sortie
private: // attributs priv�s
	float R1,C1,R2; // R1, C1 et R2
};

// classe des circuits du type D (2e ordre)
class circuitD : public circuit_2{ // classe fille qui h�rite de circuit_2
public: circuitD(); // constructeur d�faut
        circuitD(source *gen); // constructeur
        // argument: source du circuit
        circuitD(source *gen, float Vout0, float Voutp0, float Res1, float Cap1, float Ind1); // constructeur
        // arguments: source du circuit, Vs(0), Vs'(0), R1, C1 et L1
        ~circuitD(); // destructeur
        // m�thode surcharg�e:
        float Vout(float t); // pour calculer la tension de sortie
private: // attributs priv�s
    float L1,R1,C1; // L1, R1, C1
    float Vgp, Vg_pre, t_pre; // Ve'(t_i) - d�riv�e du signal d'entr�e
                              // Vg(t_i-1) - valeur pr�cedente de Vg
};                            // t_i-1 - temps pr�cedent
