
#include "Simulationsobjekt.h"
#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Weg.h"
#include "Kreuzung.h"
#include "vertagt_liste.h"
#include "SimuClient.h"
#include "Simulation.h"


#include <fstream>
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <string>
#include <random>
using namespace std;

//Funktionsdeklarationen (keine Definitionen!):
void vAufgabe_1();
void vAufgabe_1a();
void vAufgabe_2();
void vAufgabe_3();
void vAufgabe_4();
void vAufgabe_5();
void vAufgabe_6();
void vAufgabe_6a();
void vAufgabe_7();
void vAufgabe_8();
void vAufgabe_9();
void vAufgabe_9a();


//globale Uhr
double dGlobaleZeit = 0.0;

//Rundungstoleranz bei double-Vergleichen: Wähle hinreichend kleines Epsilon
double dToleranz = 0.001;

int main()
{
	
	
	
	return 0;
}

void vAufgabe_1()
{
	Fahrzeug tFahrzeug;
	Fahrzeug tFahrrad("Fahrrad");

	Fahrzeug* pFahrzeug = new Fahrzeug();
	Fahrzeug* pMotorrad = new Fahrzeug("Motorrad");
	delete pFahrzeug;
	delete pMotorrad;

	auto pRoller =  make_unique<Fahrzeug>("Roller");
	auto pCamper =  make_unique<Fahrzeug>("Camper");

	auto pSportwagen =  make_shared<Fahrzeug>("Sportwagen");
	auto pLaster =  make_shared<Fahrzeug>();

	// Erzeugen eines zweiten Pointers auf Laster.
	auto pLaster2 = pLaster;
	 cout << "Anzahl der Laster-Referenzen: " << pLaster.use_count() <<  endl;

	auto pCamper2 =  move(pCamper);

	 vector< unique_ptr<Fahrzeug>> uVector;
	uVector.push_back( move(pRoller));
	uVector.push_back( move(pCamper2));
	 cout << "Clear Vektor aus  unique_ptr<Fahrzeug>" <<  endl;
	// Löscht den Roller und den Camper.
	uVector.clear();

	 vector< shared_ptr<Fahrzeug>> sVector;
	// Neuer shared_ptr auf Sportwagen im Vektor.
	sVector.push_back(pSportwagen);
	 cout << "Anzahl der Sportwagen-Referenzen: " << pSportwagen.use_count() <<  endl;
	// Der shared_ptr von pLaster wird in den Vektor verschoben.
	sVector.push_back( move(pLaster));
	 cout << "Anzahl der Laster-Referenzen (mit Vektor und move): " << pLaster2.use_count() <<  endl;
	 cout << "Clear Vektor aus  shared_ptr<Fahrzeug>" <<  endl;
	// Der zweite shared_ptr und der verschobene pLaster wird gelöscht.
	sVector.clear();

	// Scope endet und damit wird der letzte shared_ptr auf Sportwagen und auf Laster gelöscht -> die Objekte werden ebenfalls gelöscht.
	 cout << "Scope Ende" <<  endl;
}

void vAufgabe_1a()
{
	 vector< unique_ptr<Fahrzeug>> vector;

	vector.push_back( make_unique<Fahrzeug>("PKW1", 40.0));
	vector.push_back( make_unique<Fahrzeug>("AUTO3", 30.0));
	vector.push_back( make_unique<Fahrzeug>("LKW2", 25.0));
	 cout <<  endl;

	double intervals[5] = { 0.2, 0.5, 1.0, 0.1, 0.7 };
	for (auto dInterval : intervals) {
		dGlobaleZeit += dInterval;

		Fahrzeug::vKopf();
		for ( unique_ptr<Fahrzeug>& fahrzeug : vector) {
			fahrzeug->vSimulieren();
			//fahrzeug->vAusgeben();
			 cout <<  endl;
		}
		 cout <<  endl;
	}
}

double dRandInRange(double dMin, double dMax)
{
	double dRand = ((double) rand() / (double)RAND_MAX);
	return dRand * (dMax - dMin) + dMin;
}

void vAufgabe_2()
{
	int iAnzahlPKWs, iAnzahlFahrraeder;

	 cout << "Wieviele PKWs sollen erstellt werden?" <<  endl;
	 cin >> iAnzahlPKWs;
	 cout << "Wieviele Fahrr" << (unsigned char)132 << "der sollen erstellt werden?" <<  endl;
	 cin >> iAnzahlFahrraeder;

	 vector< unique_ptr<Fahrzeug>> fahrzeugVector;

	for (int i = 0; i < iAnzahlPKWs; i++) {
		fahrzeugVector.push_back( make_unique<PKW>(
			"PKW" +  to_string(i + 1),
			dRandInRange(60.0, 180.0),
			dRandInRange(4.0, 13.8),
			dRandInRange(35.0, 80.7)
			));
	}

	for (int i = 0; i < iAnzahlFahrraeder; i++) {
		fahrzeugVector.push_back( make_unique<Fahrrad>(
			"RAD" +  to_string(i + 1),
			dRandInRange(12.0, 39.6)
			));
	}

	bool bGetankt = false;
	while (dGlobaleZeit < 4.0) {
		dGlobaleZeit += dRandInRange(0.1, 0.7);

		if (!bGetankt and dGlobaleZeit >= 3.0) {
			for ( unique_ptr<Fahrzeug>& fahrzeug : fahrzeugVector) {
				fahrzeug->dTanken( numeric_limits<double>::infinity());	
			}
			bGetankt = true;
		}

		 cout <<  endl << "Globale Zeit: " <<  setprecision(2) <<  setiosflags( ios::fixed) << dGlobaleZeit <<  endl;
		Fahrzeug::vKopf();
		for ( unique_ptr<Fahrzeug>& fahrzeug : fahrzeugVector) {
			fahrzeug->vSimulieren();
			//fahrzeug->vAusgeben();
			 cout <<  endl;
		}
	}
}

void vTriggerCopyConstructor(Fahrzeug fahrzeug)
{
}

void vAufgabe_3()
{
	auto pkw1 =  make_unique<PKW>("PKW1", 129.9, 7.6, 55.0);
	auto pkw2 =  make_unique<PKW>("PKW2", 95.7, 6.1, 60.0);
	auto rad =  make_shared<Fahrrad>("RAD1", 18.5);

	dGlobaleZeit = 0.5;
	pkw1->vSimulieren();
	pkw2->vSimulieren();
	rad->vSimulieren();

	Fahrzeug::vKopf();
	 cout << *pkw1 <<  endl
		<< *pkw2 <<  endl
		<< *rad <<  endl;

	if (*pkw2 < *pkw1) {
		 cout <<  endl << "PKW2 < PKW1" <<  endl;
	}

	if (*rad < *pkw2) {
		 cout << "RAD < PKW2" <<  endl;
	}

	*pkw2 = *pkw1;

	 cout <<  endl << "Gleichsetzen von PKW2 und PKW1:" <<  endl;
	Fahrzeug::vKopf();
	 cout << *pkw1 <<  endl
		<< *pkw2 <<  endl
		<< *rad <<  endl <<  endl;

	//vTriggerCopyConstructor(*rad); //Error
}

void vAufgabe_4()
{
	auto weg =  make_unique<Weg>("WEG1", 356.9);

	Weg::vKopf();
	 cout << *weg <<  endl;
}

void vAufgabe_5()
{
	auto weg =  make_unique<Weg>("WEG1", 30);
	weg->vAnnahme( make_unique<Fahrrad>("RAD1", 15));
	weg->vAnnahme( make_unique<Fahrrad>("RAD2", 25), 2.0);
	weg->vAnnahme( make_unique<PKW>("PKW1", 100, 5, 60));

	while (dGlobaleZeit < 4.0) {
		dGlobaleZeit += 0.5;

		weg->vSimulieren();

		Weg::vKopf();
		 cout << *weg <<  endl;
	}
}

void vAufgabe_6()
{
	bInitialisiereGrafik(1600, 1000);
	int iKoordinaten[4] = { 700, 250, 200, 250 };
	bZeichneStrasse("WEG1", "WEG2", 500, 2, iKoordinaten);

	auto weg1 =  make_unique<Weg>("WEG1", 500, Tempolimit::autobahn);
	weg1->vAnnahme( make_unique<Fahrrad>("FAHRRAD1", 15), 2.0);
	weg1->vAnnahme( make_unique<PKW>("PKW1", 150, 7, 80));
	weg1->vAnnahme( make_unique<Fahrrad>("FAHRRAD2", 23));

	auto weg2 =  make_unique<Weg>("WEG2", 500, Tempolimit::ausserorts);
	weg2->vAnnahme( make_unique<PKW>("PKW2", 75, 8, 20));
	weg2->vAnnahme( make_unique<PKW>("PKW3", 155, 7, 70), 3.0);
	weg2->vAnnahme( make_unique<Fahrrad>("FAHRRAD3", 23));

	Weg::vKopf();
	 cout << *weg1 <<  endl
		<< *weg2 <<  endl;

	while (dGlobaleZeit < 10.0) {
		dGlobaleZeit += 0.05;
		vSetzeZeit(dGlobaleZeit);
		 cout <<  endl << "Globale Zeit: " <<  setprecision(2) << dGlobaleZeit <<  endl;

		weg1->vSimulieren();
		weg2->vSimulieren();

	}
}

void vAufgabe_6a()
{
	vertagt::VListe<int> liste;

	static mt19937 device(0);
	uniform_int_distribution <int> dist(0, 10);

	for (int i = 0; i < 7; i++) {
		liste.push_back(dist(device));
	}

	liste.vAktualisieren();

	 cout << "Liste:" <<  endl;
	for (auto& iValue : liste) {
		 cout << iValue <<  endl;
	}

	for (auto it = liste.begin(); it != liste.end(); it++) {
		if (*it > 5) {
			liste.erase(it);
		}
	}

	 cout <<  endl << "Liste:" <<  endl;
	for (auto& iValue : liste) {
		 cout << iValue <<  endl;
	}

	liste.vAktualisieren();

	 cout <<  endl << "Liste:" <<  endl;
	for (auto& iValue : liste) {
		 cout << iValue <<  endl;
	}

	liste.push_front(dist(device));
	liste.push_front(dist(device));
	liste.push_back(dist(device));
	liste.push_back(dist(device));
	liste.vAktualisieren();

	 cout <<  endl << "Liste:" <<  endl;
	for (auto& iValue : liste) {
		 cout << iValue <<  endl;
	}
}

void vAufgabe_7()
{
	bInitialisiereGrafik(1600, 1000);

	auto kreuzungWest = std::make_shared<Kreuzung>("kreuzungWest");
	bZeichneKreuzung(680, 40);
	auto kreuzungSued = std::make_shared<Kreuzung>("kreuzungSued", 1000);
	bZeichneKreuzung(680, 300);
	auto kr3 = std::make_shared<Kreuzung>("Kr3");
	bZeichneKreuzung(680, 570);
	auto kr4 = std::make_shared<Kreuzung>("Kr4");
	bZeichneKreuzung(320, 300);

	Kreuzung::vVerbinde("W12", "W21", 40, kreuzungWest, kreuzungSued, Tempolimit::innerorts, true);
	int koordinatenS1[4] = { 680, 40, 680, 300 };
	bZeichneStrasse("W12", "W21", 40, 2, koordinatenS1);
	Kreuzung::vVerbinde("W23a", "W32a", 115, kreuzungSued, kr3, Tempolimit::autobahn, false);
	int koordinatenS2[12] = { 680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570 };
	bZeichneStrasse("W23a", "W32a", 115, 6, koordinatenS2);
	Kreuzung::vVerbinde("W23b", "W32b", 40, kreuzungSued, kr3, Tempolimit::innerorts, true);
	int koordinatenS3[4] = { 680, 300, 680, 570 };
	bZeichneStrasse("W23b", "W32b", 40, 2, koordinatenS3);
	Kreuzung::vVerbinde("W24", "W42", 55, kreuzungSued, kr4, Tempolimit::innerorts, true);
	int koordinatenS4[4] = { 680, 300, 320, 300 };
	bZeichneStrasse("W24", "W42", 40, 2, koordinatenS4);
	Kreuzung::vVerbinde("W34", "W43", 85, kr3, kr4, Tempolimit::autobahn, false);
	int koordinatenS5[10] = { 680, 570, 500, 570, 350, 510, 320, 420, 320, 300 };
	bZeichneStrasse("W34", "W43", 40, 5, koordinatenS5);
	Kreuzung::vVerbinde("W44a", "W44b", 130, kr4, kr4, Tempolimit::ausserorts, false);
	int koordinatenS6[14] = { 320, 300, 320, 150, 200, 60, 80, 90, 70, 250, 170, 300, 320, 300 };
	bZeichneStrasse("W44a", "W44b", 40, 7, koordinatenS6);

	kreuzungWest->vAnnahme(std::make_unique<Fahrrad>("FAHRRAD1", 30), 3.0);
	kreuzungWest->vAnnahme(std::make_unique<Fahrrad>("FAHRRAD2", 25), 0.1);
	kreuzungWest->vAnnahme(std::make_unique<Fahrrad>("FAHRRAD3", 20), 5.4);
	kreuzungWest->vAnnahme(std::make_unique<Fahrrad>("FAHRRAD4", 40), 6.5);
	kreuzungWest->vAnnahme(std::make_unique<PKW>("PKW1", 150, 7, 60), 2.5);
	kreuzungWest->vAnnahme(std::make_unique<PKW>("PKW2", 90, 10, 70), 10.0);
	kreuzungWest->vAnnahme(std::make_unique<PKW>("PKW3", 200, 8, 50), 5.0);
	kreuzungWest->vAnnahme(std::make_unique<PKW>("PKW4", 98, 6, 60), 0.2);

	while (dGlobaleZeit < 30.0) {
		dGlobaleZeit += 0.05;
		vSetzeZeit(dGlobaleZeit);

		kreuzungWest->vSimulieren();
		kreuzungSued->vSimulieren();
		kr3->vSimulieren();
		kr4->vSimulieren();
	}


}
void vAufgabe_8()
{
	std::ifstream fin("VO.dat");
	fin.exceptions(std::ios_base::eofbit | std::ios_base::failbit | std::ios_base::badbit);

	try {
		auto pkw = std::make_unique<PKW>();
		auto fahrrad = std::make_unique<Fahrrad>();
		auto kreuzung = std::make_unique<Kreuzung>();

		fin >> *pkw
			>> *fahrrad
			>> *kreuzung;

		std::cout << *pkw << std::endl << *fahrrad << std::endl << *kreuzung << std::endl;
	}
	catch (std::ios::failure e) {
		std::cout << e.what();
		return;
	}
}

void vAufgabe_9()
{
	auto sim = std::make_unique<Simulation>();

	std::ifstream fin("SimuV.dat");
	fin.exceptions(std::ios_base::failbit | std::ios_base::badbit);

	try {
		sim->vEinlesen(fin);
	}
	catch (std::ios::failure e) {
		std::cout << e.what();
		return;
	}
}

void vAufgabe_9a()
{
	auto sim = std::make_unique<Simulation>();

	std::ifstream fin("SimuDisplay.dat");
	sim->vEinlesen(fin, true);
	sim->vSimulieren(10, 0.05);
}