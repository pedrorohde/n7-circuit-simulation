// classes des EDOs

// la classe m�re g�nerale:
class EDO{
public:
	EDO(); // constructeur
	~EDO(); // destructeur
	// m�thodes:
	virtual float euler(float,float) = 0;
	virtual float getU(unsigned short) = 0;
	// m�thodes sont purement virtuelles => classe abstraite
	// ces m�thodes seront surcharg�es par les filles
protected: // attributs priv�s qui peuvent �tre acc�d�s par les filles
	float t_pre,h; // le temps pr�cedent et le pas
};

class EDO1 : public EDO{ // classe fille qui h�rite de EDO
public:
	EDO1(); // constructeur d�faut
	EDO1(float y0); // constructeur avec un argument: condition initiale y(0)
	~EDO1(); // destructeur
	float euler(float up, float t); // m�thode pour impl�menter la m�thode d'Euler
                                   //// arguments: valeur de y'(ti) et ti
	float getU(unsigned short i); // m�thode pour obtenir la valeur de U
private: // attribut priv�
    float U; // U
};

class EDO2 : public EDO{ // classe fille qui h�rite de EDO
public:
	EDO2(); // constructeur d�faut
	EDO2(float y0, float yp0); // constructeur avec 2 arguments:
                              ////  conditions initiales y'(0) et y(0)
	~EDO2(); // destructeur
	float euler(float, float); // m�thode pour impl�menter la m�thode d'Euler
                              //// arguments: valeur de y'(ti) et ti
	float getU(unsigned short); // m�thode pour obtenir la valeur de U
private:
	float U[2]; // vecteur U = [U, U']
};
