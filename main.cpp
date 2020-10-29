#include "circuit.h"
#include <cstring>

void menu(); // déclaration de la fonction menu

// déclarations de variables qui seront utilisées dans ce fichier:
static char source_type, circuit_type;
static float t, deltat = 0.1*NANO, tf = 500*NANO;
static float y, Ve, u0, up0, R1, R2, C1, L1, A, phi, duty, T, f;
static char nom_fichier[20] = "out.txt";

static source *gen; // on définira la source après
static circuit *circ; // on définira le circuit après


main(){

    /*EDO1 eqdf1(1);
    EDO2 eqdf2(1,1);*/

    menu(); // menu pour définir les paramètres de simulation

    // quelques exemples de déclaration de sources:
	///// SOURCES /////
	//gen = new echelon(1,1*NANO);
	//gen = new echelon();
	//gen = new creneau(1,0,100*NANO,0.5);
	//gen = new creneau();
	//gen = new rect(1,50*NANO,100*NANO);
	//gen = new rect();
	//gen = new sinus(1,0,100*NANO);
	//gen = new sinus();
	//gen = new triang(1,0,100*NANO);
	//gen = new triang();

	// quelques exemples de déclaration de circuits:
	///// CIRCUITS /////
	//circ = new circuitA(gen,0,50,1*NANO);
	//circ = new circuitA(gen);
	//circ = new circuitB(gen,0,0,120,0.1*NANO,1*MICRO);
	//circ = new circuitB(gen);
	//circ = new circuitC(gen,0,36,1*NANO,180);
	//circ = new circuitC(gen);
    //circ = new circuitD(gen,0,0,1.2,0.1*MICRO,10*NANO);
    //circ = new circuitD(gen);

    // on initialise le fichier de sortie:
	std::ofstream outfile;
    outfile.open(nom_fichier);
	outfile << "circuit " << circuit_type << "\nt\tVe\tVs" << std::endl;

    /*deltat = 0.001;
    tf = 10;*/

	// simulation de t = 0 à tf (temps final),
	//  avec un pas deltat
	for(t = 0; t < tf; t+=deltat) {

        //******** CIRCUITS *****************
        // ici, on utilise du polymorphisme
        // les méthodes Vout et getVg dépendent du type de circuit
        // la méthode correspondante de ce type de circuit va être automatiquement appellé
		y = (*circ).Vout(t);    //  on calcule la tension de sortie du circuit
                                ////    à chaque instant de temps
        Ve = (*circ).getVg();   //  on prend aussi la tension de la source
		// on les écrit dans le fichier de sortie:
		//************************************/

		/******** EDOs *********************
		y = eqdf1.euler(-3*y-3*t,t);
		y = eqdf2.euler(-y,t);
		//************************************/


		outfile << t << "\t" << Ve << "\t" << y << std::endl;

	}
	outfile.close(); // fermeture du fichier de sortie
	return 0; // fin du programme
}

void menu(){
    // ce menu va permettre à l'utilisateur de choisir les paramètres de la simulation
    // il peut prendre les valeurs standard (ceux des exemples) ou choisir d'autres
    // ses choix vont être sauvegardées dans les variables déclarées au début de ce fichier
    // notamment, l'utilisateur choisira une source et un circuit
    char c;
    std::cout << "\n\nChoisissez un circuit:\n";
    std::cout << "A, B, C ou D\n";
    std::cin >> circuit_type;
    std::cout << "\n\nChoisissez une source:\n";
    std::cout << "rectangulaire(R)\ncreneau (C)\nechelon(E)\n";
    std::cout << "triangulaire(T)\nsinusoidal(S)\n\nVotre choix: ";
    std::cin >> source_type;
    std::cout << "\nUtiliser source comme dans les examples? (o/n) ";
    std::cin >> c;
    switch(source_type){
        case 'r': case 'R':
            if(c == 'n' || c == 'N'){
                std::cout << "Amplitude: "; std::cin >> A;
                std::cout << "phi: "; std::cin >> phi;
                std::cout << "Duree: "; std::cin >> duty;
                gen = new rect(A,phi,duty);} // allocation dynamique
            else gen = new rect(); // allocation dynamique, constructeur défaut
            break;
        case 'c': case 'C':
            if(c == 'n' || c == 'N'){
                std::cout << "Amplitude: "; std::cin >> A;
                std::cout << "phi: "; std::cin >> phi;
                std::cout << "Period: "; std::cin >> T;
                std::cout << "Duty cycle: "; std::cin >> duty;
                gen = new creneau(A,phi,T,duty);} // allocation dynamique
            else gen = new creneau(); // allocation dynamique, constructeur défaut
            break;
        case 'e': case 'E':
            if(c == 'n' || c == 'N'){
                std::cout << "Amplitude: "; std::cin >> A;
                std::cout << "phi: "; std::cin >> phi;
                gen = new echelon(A,phi);} // allocation dynamique
            else gen = new echelon(); // allocation dynamique, constructeur défaut
            break;
        case 't': case 'T':
            if(c == 'n' || c == 'N'){
                std::cout << "Amplitude: "; std::cin >> A;
                std::cout << "phi: "; std::cin >> phi;
                std::cout << "Period: "; std::cin >> T;
                gen = new triang(A,phi,T);} // allocation dynamique
            else gen = new triang(); // allocation dynamique, constructeur défaut
            break;
        case 's': case 'S':
            if(c == 'n' || c == 'N'){
                std::cout << "Amplitude: "; std::cin >> A;
                std::cout << "phi: "; std::cin >> phi;
                std::cout << "Frequence: "; std::cin >> f; T = 1.0/f;
                gen = new sinus(A,phi,T);} // allocation dynamique
            else gen = new sinus(); // allocation dynamique, constructeur défaut
            break;
        default: break;};

    std::cout << "\nUtiliser circuit comme dans les examples? (o/n) "; std::cin >> c;
    switch(circuit_type){
        case 'a': case 'A':
            if(c == 'n' || c == 'N'){
                std::cout << "condition initiale u(0) = "; std::cin >> u0;
                std::cout << "R1 = "; std::cin >> R1;
                std::cout << "C1 = "; std::cin >> C1;
                circ = new circuitA(gen,u0,R1,C1);} // allocation dynamique
            else circ = new circuitA(gen); // allocation dynamique
            break;
        case 'b': case 'B':
            if(c == 'n' || c == 'N'){
                std::cout << "condition initiale u(0) = "; std::cin >> u0;
                std::cout << "condition initiale u'(0) = "; std::cin >> up0;
                std::cout << "R1 = "; std::cin >> R1;
                std::cout << "L1 = "; std::cin >> L1;
                std::cout << "C1 = "; std::cin >> C1;
                circ = new circuitB(gen,u0,up0,R1,C1,L1);} // allocation dynamique
            else circ = new circuitB(gen); // allocation dynamique
            break;
        case 'c': case 'C':
            if(c == 'n' || c == 'N'){
                std::cout << "condition initiale u(0) = "; std::cin >> u0;
                std::cout << "R1 = "; std::cin >> R1;
                std::cout << "R2 = "; std::cin >> R2;
                std::cout << "C1 = "; std::cin >> C1;
                circ = new circuitC(gen,u0,R1,C1,R2);} // allocation dynamique
            else circ = new circuitC(gen); // allocation dynamique
            break;
        case 'd': case 'D':
            if(c == 'n' || c == 'N'){
                std::cout << "condition initiale u(0) = "; std::cin >> u0;
                std::cout << "condition initiale u'(0) = "; std::cin >> up0;
                std::cout << "R1 = "; std::cin >> R1;
                std::cout << "L1 = "; std::cin >> L1;
                std::cout << "C1 = "; std::cin >> C1;
                circ = new circuitD(gen,u0,up0,R1,C1,L1);} // allocation dynamique
            else circ = new circuitD(gen); // allocation dynamique
            break;
        default: break;};

    std::cout << "Parametres de simulation:\n";
    std::cout << "Pas (delta t) standard? (o/n) "; std::cin >> c;
	if(c == 'n' || c == 'N'){
        std::cout << "delta t = "; std::cin >> deltat;}
	std::cout << "Temps final standard? (o/n) "; std::cin >> c;
	if(c == 'n' || c == 'N'){
        std::cout << "tf = "; std::cin >> tf;}
	std::cout << "Fichier de sortie standard? (o/n) "; std::cin >> c;
	if(c == 'n' || c == 'N'){
        std::cout << "nom du fichier: "; std::cin >> nom_fichier;}}
