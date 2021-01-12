#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"
#include "vertagt_liste.h"

Weg::Weg(string initName, double initLaenge, Tempolimit initTempolimit) :
	Simulationsobjekt(initName), p_dLaenge(initLaenge), p_eTempolimit(initTempolimit), p_dVirtuelleSchranke(0.0), p_bUeberholverbot(false)
{
}

Weg::Weg(string initName, double initLaenge, weak_ptr<Kreuzung> initStartkreuzung, weak_ptr<Kreuzung> initZielkreuzung, Tempolimit initTempolimit, bool initUeberholverbot, weak_ptr<Weg> initRueckweg) : 
	Simulationsobjekt(initName), p_dLaenge(initLaenge), p_eTempolimit(initTempolimit), p_bUeberholverbot(initUeberholverbot), p_dVirtuelleSchranke(0.0), p_pStartkreuzung(initStartkreuzung),
	p_pZielkreuzung(initZielkreuzung), p_pRueckweg(initRueckweg)
{
}




const double Weg::getTempolimit() const 
{
	double dLimit = (double)(p_eTempolimit);
	return dLimit;
}

const double Weg::getLaenge() const
{ 
	return p_dLaenge;
}

bool Weg::getUeberholverbot() const
{
	return p_bUeberholverbot;
}

double Weg::getVirtuelleSchranke() const
{
	return !p_bUeberholverbot ? 0.0 : p_dVirtuelleSchranke;
}

void Weg::vSetzeRueckweg(std::weak_ptr<Weg> pRueckweg)
{
	p_pRueckweg = pRueckweg;
}

std::shared_ptr<Weg> Weg::pGetRueckweg() const
{
	return p_pRueckweg.lock();
}


shared_ptr<Kreuzung> Weg::pGetStartkreuzung() const
{
	return p_pStartkreuzung.lock();
}

shared_ptr<Kreuzung> Weg::pGetZielkreuzung() const
{
	return p_pZielkreuzung.lock();
}

void Weg::vSimulieren()
{
	p_pFahrzeuge.vAktualisieren();

	for (auto& pFahrzeug : p_pFahrzeuge) {
		try {
			pFahrzeug->vSimulieren();
			p_dVirtuelleSchranke = pFahrzeug->getAbschnittStrecke();
			pFahrzeug->vZeichnen(*this);
			
		}
		catch (const Fahrausnahme& exc) {
			exc.vBearbeiten();
		}
	}

	p_dVirtuelleSchranke = 0.0;

	p_pFahrzeuge.vAktualisieren();
}


void Weg::vAnnahme(unique_ptr<Fahrzeug> aFzg, double dStartZeit)
{
	(*aFzg).vNeueStrecke(*this, dStartZeit);


	if (std::numeric_limits<double>::infinity() == dStartZeit) {
		p_pFahrzeuge.push_back(std::move(aFzg));
	}
	else {
		p_pFahrzeuge.push_front(std::move(aFzg));
	}
}


std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& pFahrzeug)
{
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++) {
		if (*(*it) == pFahrzeug) {
			auto pDel = move(*it);
			p_pFahrzeuge.erase(it);
			return pDel;
		}
	}

	throw runtime_error("Fahrzeug für pAbgabe befindet sich nicht auf dem Weg!");
}

void Weg::vAusgeben(ostream& out) const 
{
	cout << "|" << setw(3) << resetiosflags(ios::left) << setiosflags(ios::right) << p_iID << "|";
	cout << "|" << "  " << "|";
	cout << "|" << setw(20) << resetiosflags(ios::left) << setiosflags(ios::right) << p_sName << "|";
	cout << "|" << setw(20) << resetiosflags(ios::left) << setiosflags(ios::right) << p_dLaenge << "||";

	if (auto it = p_pFahrzeuge.empty())
	{
	}
	else
	{

		cout << setw(23) << resetiosflags(ios::left) << setiosflags(ios::right) << "(";
		for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
		{
			cout << (*it)->getName();
			if (it != p_pFahrzeuge.end())
			{
				cout << ", ";
			}
			else
			{
				cout << ")" << "\n";
			}
		}
	}

}

void Weg::vKopf()
{
	cout << "|" << setw(3) << resetiosflags(ios::right) << setiosflags(ios::left) << "ID" << "|";
	cout << "|" << "  " << "|";
	cout << "|" << setw(20) << resetiosflags(ios::right) << setiosflags(ios::left) << "Name" << "|";
	cout << "|" << setw(20) << resetiosflags(ios::right) << setiosflags(ios::left) << "Laenge" << "|";
	cout << "|" << setw(23) << resetiosflags(ios::right) << setiosflags(ios::left) << "Fahrzeuge" << "\n";
}

