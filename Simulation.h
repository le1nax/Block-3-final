#pragma once

#include "Kreuzung.h"
#include <map>
#include <memory>
#include <iostream>

class Simulation
{
private:
	bool p_bGrafik = false;
	std::map<std::string, std::shared_ptr<Kreuzung>> p_pKreuzungen;
public:
	Simulation() = default;
	void vEinlesen(std::istream&, bool bMitGrafik = false);
	void vSimulieren(double, double);
};