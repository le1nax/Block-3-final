#pragma once
#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include <list>
#include <memory>
#include <string>

class Weg;
class Fahrzeug;

class Kreuzung :
    public Simulationsobjekt
{
private:
    list< shared_ptr<Weg>> p_pWege;
    double p_dTankstelle;
public:
    Kreuzung( string = "", double = 0.0);
    void vEinlesen( istream&) override;
    static void vVerbinde( string,  string, double,  shared_ptr<Kreuzung>&,  shared_ptr<Kreuzung>&, Tempolimit, bool);
    void vWegHinzufuegen( shared_ptr<Weg>);
    void vTanken(Fahrzeug&);
    void vAnnahme( unique_ptr<Fahrzeug>, double);
    Weg& pZufaelligerWeg(Weg&);
    void vSimulieren() override;
};