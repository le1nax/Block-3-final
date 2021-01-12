#include "Simulation.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Tempolimit.h"
#include "SimuClient.h"
#include <string>
#include <cmath>

extern double dGlobaleZeit;

void Simulation::vEinlesen(std::istream& in, bool mitGrafik)
{
	std::string sTyp;
	int iZeile = 1;

	if (mitGrafik) {
		bInitialisiereGrafik(1600, 1000);
	}

	try {
		while (!in.eof()) {
			in >> sTyp;

			if ("KREUZUNG" == sTyp) {
				auto kreuzung = std::make_shared<Kreuzung>();
				in >> *kreuzung;

				if (p_pKreuzungen.end() != p_pKreuzungen.find(kreuzung->getName())) {
					throw std::runtime_error("Die Kreuzung \"" + kreuzung->getName() + "\" existiert bereits.");
				}

				p_pKreuzungen[kreuzung->getName()] = std::move(kreuzung);

				if (mitGrafik) {
					int iXPos, iYPos;
					in >> iXPos >> iYPos;
					bZeichneKreuzung(iXPos, iYPos);
				}
			}
			else if ("STRASSE" == sTyp) {
				std::string sNameQ, sNameZ, sNameW1, sNameW2;
				double dLaenge;
				Tempolimit tempolimit;
				int iUeberholverbot;

				in >> sNameQ >> sNameZ >> sNameW1 >> sNameW2
					>> dLaenge >> tempolimit >> iUeberholverbot;

				auto itQ = p_pKreuzungen.find(sNameQ);
				if (p_pKreuzungen.end() == itQ) {
					throw std::runtime_error("Die Kreuzung \"" + sNameQ + "\"konnte nicht gefunden werden.");
				}
				auto itZ = p_pKreuzungen.find(sNameZ);
				if (p_pKreuzungen.end() == itZ) {
					throw std::runtime_error("Die Kreuzung \"" + sNameZ + "\"konnte nicht gefunden werden.");
				}

				Kreuzung::vVerbinde(sNameW1, sNameW2, dLaenge, itQ->second, itZ->second, tempolimit, (bool)iUeberholverbot);

				if (mitGrafik) {
					int iAnzahl;
					in >> iAnzahl;

					int* iKoordinaten = new int[static_cast<__int64>(iAnzahl) * 2];
					for (int i = 0; i < iAnzahl * 2; i++) {
						in >> iKoordinaten[i];
					}

					bZeichneStrasse(sNameW1, sNameW2, (int)std::round(dLaenge), iAnzahl, iKoordinaten);
					delete[] iKoordinaten;
				}
			}
			else if ("PKW" == sTyp or "FAHRRAD" == sTyp) {
				std::unique_ptr<Fahrzeug> fahrzeug;
				if ("PKW" == sTyp) {
					fahrzeug = std::make_unique<PKW>();
				}
				else {
					fahrzeug = std::make_unique<Fahrrad>();
				}

				std::string sNameS;
				double dStartzeit;

				in >> *fahrzeug
					>> sNameS
					>> dStartzeit;

				auto it = p_pKreuzungen.find(sNameS);
				if (p_pKreuzungen.end() == it) {
					throw std::runtime_error("Die Kreuzung \"" + sNameS + "\"konnte nicht gefunden werden.");
				}

				it->second->vAnnahme(std::move(fahrzeug), dStartzeit);
			}
			else {
				throw std::runtime_error("Unbekanntes Schluesselwort in Zeile " + std::to_string(iZeile));
			}

			iZeile++;
		}

		p_bGrafik = mitGrafik;
	}
	catch (std::runtime_error e) {
		std::cout << "Fehler in Zeile " << iZeile << ": \"" << e.what() << "\"" << std::endl;
	}
}

void Simulation::vSimulieren(double dDauer, double dZeitschritt)
{
	while (dGlobaleZeit < dDauer) {
		dGlobaleZeit += dZeitschritt;
		if (p_bGrafik) {
			vSetzeZeit(dGlobaleZeit);
		}

		for (const auto& it : p_pKreuzungen) {
			it.second->vSimulieren();
		}
	}
}