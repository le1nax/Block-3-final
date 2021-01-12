#pragma once 

#include <iostream>
#include <vector>
#include <list>
#include <iomanip>
#include <string>
#include <limits>
#include <cmath>
using namespace std;


class Simulationsobjekt
{
private: 
	static int p_iMaxID;	//Deklaration einer Klassenvariable, die im Konstruktor hochzählt

protected:
	double p_dZeit = 0;
	const int p_iID = 0;
	string p_sName = "";


public:

	Simulationsobjekt();
	Simulationsobjekt(string initName);
	virtual ~Simulationsobjekt(); //virtueller Destruktor
	Simulationsobjekt (const Simulationsobjekt&) = delete; //verbiete Copyconstruktor
	int getID() const;
	virtual void vSimulieren() = 0;
	virtual void vAusgeben(ostream& out= cout) const;
	Simulationsobjekt& operator=(const Simulationsobjekt& simObj);
	virtual void vEinlesen(std::istream&);
	


	//Name des Objektes returnen
	virtual string getName() const;

};

ostream& operator<<(ostream&, const Simulationsobjekt&);
istream& operator>>(istream&, Simulationsobjekt&);
bool operator==(const Simulationsobjekt&, const Simulationsobjekt&);
