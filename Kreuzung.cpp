#include "Kreuzung.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include <memory>
#include <random>

Kreuzung::Kreuzung(string sName, double dTankinhalt) :
	Simulationsobjekt(sName),
	p_pWege(),
	p_dTankstelle(dTankinhalt)
{
}


void Kreuzung::vVerbinde(string sNameHinweg, string sNameRueckweg, double dWeglaenge, shared_ptr<Kreuzung>& startkreuzung, shared_ptr<Kreuzung>& zielkreuzung, Tempolimit eTempolimit, bool bUeberholverbot)
{
	auto hinweg = make_shared<Weg>(sNameHinweg, dWeglaenge, startkreuzung, zielkreuzung, eTempolimit, bUeberholverbot);
	auto rueckweg = make_shared<Weg>(sNameRueckweg, dWeglaenge, zielkreuzung, startkreuzung, eTempolimit, bUeberholverbot);

	hinweg->vSetzeRueckweg(rueckweg);
	rueckweg->vSetzeRueckweg(hinweg);

	startkreuzung->vWegHinzufuegen(hinweg);
	zielkreuzung->vWegHinzufuegen(rueckweg);
}

void Kreuzung::vWegHinzufuegen(shared_ptr<Weg> pWeg)
{
	p_pWege.push_back(pWeg);
}

void Kreuzung::vAnnahme(unique_ptr<Fahrzeug> aFzg, double dZeit)
{
	vTanken(*aFzg);
	auto weg = p_pWege.front();
	weg->vAnnahme(move(aFzg), dZeit);
}


void Kreuzung::vTanken(Fahrzeug& aFzg)
{
	if (abs(p_dTankstelle) < 0.001)
	{
		return;
	}

	double dMenge = aFzg.dTanken();
	p_dTankstelle -= dMenge;

	if (p_dTankstelle < 0.0)
	{
		p_dTankstelle = 0.0;
	}
}

void Kreuzung::vEinlesen(istream& in)
{
	Simulationsobjekt::vEinlesen(in);

	in >> p_dTankstelle;
}


Weg& Kreuzung::pZufaelligerWeg(Weg& weg)
{
	size_t iAnzahlWege = p_pWege.size();

	if (iAnzahlWege == 0)
	{
		throw exception("Kreuzung hat keinen moeglichen Weg");
	}
	else if (iAnzahlWege == 1)
	{
		return *p_pWege.front();
	}

	static mt19937 device(0);
	uniform_int_distribution<int> dist(0, (int)iAnzahlWege - 1);

	while (true) {
		int iZuf = dist(device);

		auto it = p_pWege.begin();
		for (int i = 0; i < iZuf; i++) {
			it++;
		}

		if (*it == weg.pGetRueckweg()) {
			// schleife wird erneut aufgerufen.
		}
		else {
			return *(*it);
		}
	}
}


void Kreuzung::vSimulieren()
{
	for (auto& pWeg : p_pWege) {
		pWeg->vSimulieren();
	}
}