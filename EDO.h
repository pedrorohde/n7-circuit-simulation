// classes des EDOs

// la classe mère génerale:
class EDO{
public:
	EDO(); // constructeur
	~EDO(); // destructeur
	// méthodes:
	virtual float euler(float,float) = 0;
	virtual float getU(unsigned short) = 0;
	// méthodes sont purement virtuelles => classe abstraite
	// ces méthodes seront surchargées par les filles
protected: // attributs privés qui peuvent être accédés par les filles
	float t_pre,h; // le temps précedent et le pas
};

class EDO1 : public EDO{ // classe fille qui hérite de EDO
public:
	EDO1(); // constructeur défaut
	EDO1(float y0); // constructeur avec un argument: condition initiale y(0)
	~EDO1(); // destructeur
	float euler(float up, float t); // méthode pour implémenter la méthode d'Euler
                                   //// arguments: valeur de y'(ti) et ti
	float getU(unsigned short i); // méthode pour obtenir la valeur de U
private: // attribut privé
    float U; // U
};

class EDO2 : public EDO{ // classe fille qui hérite de EDO
public:
	EDO2(); // constructeur défaut
	EDO2(float y0, float yp0); // constructeur avec 2 arguments:
                              ////  conditions initiales y'(0) et y(0)
	~EDO2(); // destructeur
	float euler(float, float); // méthode pour implémenter la méthode d'Euler
                              //// arguments: valeur de y'(ti) et ti
	float getU(unsigned short); // méthode pour obtenir la valeur de U
private:
	float U[2]; // vecteur U = [U, U']
};
