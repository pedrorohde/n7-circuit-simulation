#include "circuit.h"

//// circuit ///////////////////////////////////////////////

// constructeur défaut
circuit::circuit() {
	// on définit les attributs avec des valeurs standard
	src = new rect(1,0,0.5);
	eq_diff = new EDO1();
}

// constructeur
circuit::circuit(source *gen) {
    // on définit les attributs avec les paramètres précisés
	src = gen;
	eq_diff = new EDO1();
}

// destructeur
circuit::~circuit(){
}

// pour calculer la tension de la source
float circuit::getVg(){
    return Vg;
};

//// circuit_1 /////////////////////////////////////////////

// constructeur défaut
circuit_1::circuit_1() {
	// on définit les attributs avec des valeurs standard
	src = new echelon(1,0);
	eq_diff = new EDO1(0);
}

// constructeur avec source seulement
circuit_1::circuit_1(source *gen) {
    // on définit l'attribut src avec le paramètre
	src = gen;
	// et eq_diff avec un valeur standard
	eq_diff = new EDO1(0);
}

// constructeur avec source et condition initiale
circuit_1::circuit_1(source *gen, float Vout0){
    // on définit les attributs avec les paramètres précisés
	src = gen;
	eq_diff = new EDO1(Vout0);
}

// destructeur
circuit_1::~circuit_1(){
}

//// circuit_2 /////////////////////////////////////////////

// constructeur défaut
circuit_2::circuit_2() {
	// on définit les attributs avec des valeurs standard
	src = new echelon(1,0);
	eq_diff = new EDO2(0,0);
}

// constructeur avec source seulement
circuit_2::circuit_2(source *gen) {
    // on définit l'attribut src avec le paramètre
	src = gen;
	// et eq_diff avec des valeurs standard
	eq_diff = new EDO2(0,0);
}

// constructeur avec source et conditions initiales
circuit_2::circuit_2(source *gen, float Vout0, float Voutp0){
    // on définit les attributs avec les paramètres précisés
	src = gen;
	eq_diff = new EDO2(Vout0,Voutp0);

}

// destructeur
circuit_2::~circuit_2(){
}

//// circuitA /////////////////////////////////////////////

// constructeur défaut
circuitA::circuitA(){
	// on définit les attributs avec des valeurs standard
	R1 = 50;
	C1 = 1*NANO;
	src = new echelon(1,0);
	eq_diff = new EDO1(0);
	Vs = 0;
}

// constructeur avec source seulement
circuitA::circuitA(source *gen){
    // on définit l'attribut src avec le paramètre
	src = gen;
	// et les autres avec des valeurs standard
	R1 = 50;
	C1 = 1*NANO;
	eq_diff = new EDO1(0);
	Vs = 0;
}

// constructeur avec tous les attributs
circuitA::circuitA(source *gen, float Vout0, float Res1, float Cap1){
    // on définit les attributs avec les paramètres précisés
	R1 = Res1;
	C1 = Cap1;
	src = gen;
	eq_diff = new EDO1(Vout0);
	Vs = Vout0;
}

// destructeur
circuitA::~circuitA(){
}

// pour calculer la tension de sortie
float circuitA::Vout(float t){
    Vg = (*src).Ve(t); // tension de la source
    Vsp = (Vg - Vs)/(R1*C1); // l'equation differentielle
    /*Vsp_rk2 = (Vg - (Vs + h/2*Vsp) )/(R1*C1);
    Vsp_rk3 = (Vg - (Vs + h/2*Vsp_rk2) )/(R1*C1);
    Vsp_rk4 = (Vg - (Vs + h*Vsp_rk3) )/(R1*C1);
    Vs = (*eq_diff).euler((Vsp + 2*Vsp_rk2 + 2*Vsp_rk3 + Vsp_rk4)/6,t);*/
    Vs = (*eq_diff).euler(Vsp,t); // on la résout
    return Vs;
}

//// circuitB /////////////////////////////////////////////

// constructeur défaut
circuitB::circuitB(){
	// on définit les attributs avec des valeurs standard
	R1 = 120;
	C1 = 0.1*NANO;
	L1 = 1*MICRO;
	src = new echelon(1,0);
	eq_diff = new EDO2(0,0);
	Vs = 0;
	Vsp = 0;
}

// constructeur avec source seulement
circuitB::circuitB(source *gen){
    // on définit l'attribut src avec le paramètre
	src = gen;
	// et les autres avec des valeurs standard
	R1 = 120;
	C1 = 0.1*NANO;
	L1 = 1*MICRO;
	eq_diff = new EDO2(0,0);
	Vs = 0;
	Vsp = 0;
}

// constructeur avec tous les attributs
circuitB::circuitB(source *gen, float Vout0, float Voutp0, float Res1, float Cap1, float Ind1){
    // on définit les attributs avec les paramètres précisés
	R1 = Res1;
	C1 = Cap1;
	L1 = Ind1;
	src = gen;
	eq_diff = new EDO2(Vout0,Voutp0);
	Vs = Vout0;
	Vsp = Voutp0;
}

// destructeur
circuitB::~circuitB(){
}

// pour calculer la tension de sortie
float circuitB::Vout(float t){
    Vg = (*src).Ve(t); // tension de la source
    Vs2p = -(R1/L1)*Vsp + (Vg - Vs)/(L1*C1); // EDO
    // Vsp = Vs' de l'itération précedente
    // Vs = Vs de l'itération précedente
	Vs = (*eq_diff).euler(Vs2p,t); // on résoud l'EDO
	// et sauvegarde Vs (pour la prochaine itération)
	Vsp = (*eq_diff).getU(1); // on sauvegarde Vs'
                             // (pour la prochaine itération)
	return Vs;
}

//// circuitC /////////////////////////////////////////////

// constructeur défaut
circuitC::circuitC(){
	// on définit les attributs avec des valeurs standard
	R1 = 36;
	C1 = 1*NANO;
	R2 = 180;
	src = new echelon(1,0);
	eq_diff = new EDO1(0);
	Vs = 0;
}

// constructeur avec source seulement
circuitC::circuitC(source *gen){
    // on définit l'attribut src avec le paramètre
    src = gen;
	// et les autres avec des valeurs standard
	R1 = 36;
	C1 = 1*NANO;
	R2 = 180;
	eq_diff = new EDO1(0);
	Vs = 0;
}

// constructeur avec tous les attributs
circuitC::circuitC(source *gen, float Vout0, float Res1, float Cap1, float Res2){
    // on définit les attributs avec les paramètres précisés
    R1 = Res1;
	C1 = Cap1;
	R2 = Res2;
	src = gen;
	eq_diff = new EDO1(Vout0);
	Vs = Vout0;
}

// destructeur
circuitC::~circuitC(){
}

// pour calculer la tension de sortie
float circuitC::Vout(float t){
	Vg = (*src).Ve(t); // on prend la tension de la source
	// on calcule Vs' (d'après l'EDO):
	if(Vg > 0.6)
		Vsp = -(1/C1)*(1/R1+1/R2)*Vs+(Vg - 0.6)/(R1*C1);
	else
		Vsp = -Vs/(R2*C1);
    // Vs = Vs de l'itération précedente
    Vs = (*eq_diff).euler(Vsp,t); // on résoud l'EDO
    // et sauvegarde Vs (pour la prochaine itération)
    return Vs;
}

//// circuitC /////////////////////////////////////////////

// constructeur défaut
circuitD::circuitD(){
	// on définit les attributs avec des valeurs standard
	R1 = 1.2;
	C1 = 0.1*MICRO;
	L1 = 10*NANO;
	src = new echelon(1,0);
	eq_diff = new EDO2(0,0);
	Vs = 0;
	Vsp = 0;
	Vg_pre = 0;
	t_pre = 0;
	Vgp = 0;
}

// constructeur avec source seulement
circuitD::circuitD(source *gen){
    // on définit l'attribut src avec le paramètre
	src = gen;
	// et les autres avec des valeurs standard
	R1 = 1.2;
	C1 = 0.1*MICRO;
	L1 = 10*NANO;
	eq_diff = new EDO2(0,0);
	Vs = 0;
	Vsp = 0;
	Vg_pre = 0;
	t_pre = 0;
	Vgp = (*src).Ve(0);
}

// constructeur avec tous les attributs
circuitD::circuitD(source *gen, float Vout0, float Voutp0, float Res1, float Cap1, float Ind1){
    // on définit les attributs avec les paramètres précisés
	R1 = Res1;
	C1 = Cap1;
	L1 = Ind1;
	src = gen;
	eq_diff = new EDO2(Vout0,Voutp0);
	Vs = Vout0;
	Vsp = Voutp0;
	Vg_pre = 0;
	t_pre = 0;
	Vgp = (*src).Ve(0);
}

// destructeur
circuitD::~circuitD(){
}

// pour calculer la tension de sortie
float circuitD::Vout(float t){
	if(t){ // si t = 0, les valeurs définies dans le constructeur restent les mêmes
        Vg = (*src).Ve(t); // on prend la tension de la source
        if (t-t_pre) Vgp = (Vg-Vg_pre)/(t-t_pre); // on calcule sa dérivée (Vg')
        // si temps = temps précedent, Vg' est le même
        Vs2p = (Vgp-Vsp)/(R1*C1) - Vs/(L1*C1); // Vs'' (d'après l'EDO)
        // Vsp = Vs' de l'itération précedente
        // Vs = Vs de l'itération précedente
        Vs = (*eq_diff).euler(Vs2p,t); // on résout l'EDO et sauvegarde Vs
        Vsp = (*eq_diff).getU(1); // on sauvegarde la valeur de Vs' pour la prochaine itération
        Vg_pre = Vg; // on sauvegarde Ve pour la prochaine itération (calcul de Vg')
        t_pre = t; // on sauvegarde le temps pour la prochaine itération (calcul de Vg')
	}
	return Vs;
}
