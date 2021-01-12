#include "Tempolimit.h"
#include <iostream>
#include <string>

std::istream& operator>>(std::istream& in, Tempolimit& tempolimit)
{
	int integer;
	in >> integer;

	switch (integer) {
	case 1:
		tempolimit = Tempolimit::innerorts;
		break;
	case 2:
		tempolimit = Tempolimit::ausserorts;
		break;
	case 3:
		tempolimit = Tempolimit::autobahn;
		break;
	default:
		throw std::runtime_error("Es kann kein Tempolimit aus \"" + std::to_string(integer) + "\" gelesen werden.");
	}

	return in;
}