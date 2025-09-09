#include "domain.h"

//deci cand are alt type fata de string sa pun to_string() si dupa numele si e ok


string Building::toString()
{
	return "Address : " + address + "\nConstruction Year : " + to_string(constructionYear) + "\n";
}

//aici trb sa pun 0.ceva in loc de procentajul normal
bool Block::mustBeRestored()
{
	double percentage;
	percentage = double(occupiedApartments) / double(totalApartments);
	if (percentage > 0.80 and 2024 - constructionYear >= 40) return true;
	return false;
}

bool Block::canBeDemolished()
{
	double percentage;
	percentage = double(occupiedApartments) / double(totalApartments);
	if (percentage <= 0.05) return true;
	return false;
}

string Block::toString()
{
	return "Block\n" + Building::toString() + "nrApp : " + to_string(totalApartments) + "\noccupiedApp : " + to_string(occupiedApartments);
}

bool House::mustBeRestored()
{
	if (2024 - constructionYear >= 100) return true;
	return false;
}

bool House::canBeDemolished()
{
	return isHistorical;
}

string House::toString()
{
	return "House\n" + Building::toString() + "type :" + type + "\nisHistorical : " + to_string(isHistorical);
}



