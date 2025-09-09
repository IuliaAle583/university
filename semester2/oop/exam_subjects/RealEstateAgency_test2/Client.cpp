#include "Client.h"

string Client::toString()
{
	return "Name " + this->name + "\nIncome " + to_string(this->salary) + "\n";
}



bool NormalClient::isInterested(Dwelling d)
{
	return d.normalBankRate()  <= this->totalIncome();
}

double WealthyClient::totalIncome()
{
	return this->salary+this->moneyFromInvestments;
}

string WealthyClient::toString()
{
	return "Wealthy\n"+Client::toString()+"Money from investments "+to_string(moneyFromInvestments)+"\n"+"Total income "+to_string(this->totalIncome())+"\n";
}

bool WealthyClient::isInterested(Dwelling d)
{
	return d.largeBankRate()<=this->totalIncome()&&d.Profitable();
}
