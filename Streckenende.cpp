
#include "Streckenende.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Kreuzung.h"

extern double dGlobaleZeit;

Streckenende::Streckenende(Fahrzeug& aFzg, Weg& aWeg) : Fahrausnahme(aFzg, aWeg)
{
}


void Streckenende::vBearbeiten() const
{
	std::cout << "Fahrzeug " << p_pFahrzeug.getName() << " auf" << p_pWeg.getName() << " geendet.\n";

	auto pFahrzeug = p_pWeg.pAbgabe(p_pFahrzeug);
	auto pKreuzung = p_pWeg.pGetZielkreuzung();

	// Wege ohne Kreuzungen aus Aufgabenblock 2
	if (nullptr == pKreuzung) {
		return;
	}

	pKreuzung->vTanken(*pFahrzeug);
	auto& neuerWeg = pKreuzung->pZufaelligerWeg(p_pWeg);
	neuerWeg.vAnnahme(std::move(pFahrzeug));

	std::cout << "ZEIT        : " << dGlobaleZeit << std::endl
		<< "KREUZUNG    : " << pKreuzung->getName() << std::endl
		<< "WECHSEL     : " << p_pWeg.getName() << " -> " << neuerWeg.getName() << std::endl
		<< "FAHRZEUG    : " << p_pFahrzeug << std::endl;

}

