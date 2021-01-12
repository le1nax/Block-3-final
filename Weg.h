#pragma once

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"

#include <memory>
#include <limits>


extern double dToleranz;

class Kreuzung;
class Fahrzeug;

class Weg : public Simulationsobjekt

{
protected:
	Tempolimit p_eTempolimit = Tempolimit::autobahn;
	vertagt::VListe< unique_ptr<Fahrzeug>> p_pFahrzeuge;
	//list<unique_ptr<Fahrzeug>>::iterator it;

	double p_dLaenge = 0;
	bool p_bUeberholverbot = true;
	double p_dVirtuelleSchranke = 0.0;
	weak_ptr<Weg> p_pRueckweg;
	const weak_ptr<Kreuzung> p_pStartkreuzung;
	const weak_ptr<Kreuzung> p_pZielkreuzung;

	

public:
	Weg(string sName, double dLaenge, Tempolimit eTempolimit = Tempolimit::autobahn);
	Weg(string sName, double dLaenge, weak_ptr<Kreuzung> pStartkreuzung, weak_ptr<Kreuzung> pZielkreuzung, 
		Tempolimit eTempolimit = Tempolimit::autobahn, bool bUeberholverbot = true, weak_ptr<Weg> pRueckweg = weak_ptr<Weg>());
	const double getTempolimit() const;
	const double getLaenge() const;
	bool getUeberholverbot() const;
	double getVirtuelleSchranke() const;
	shared_ptr<Kreuzung> pGetStartkreuzung() const;
	 shared_ptr<Kreuzung> pGetZielkreuzung() const;
	void vSetzeRueckweg(weak_ptr<Weg>);
	 shared_ptr<Weg> pGetRueckweg() const;
	unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug&);
	void vSimulieren() override;
	void vAnnahme(unique_ptr<Fahrzeug> aFzg, double dStartZeit = numeric_limits<double>::infinity());
	virtual void vAusgeben(ostream& out = cout) const override;
	static void vKopf();
};
	