#pragma once
#include <iostream>
//#include "Color.h"

// NICHT Ändern!!
enum class SpielfeldEintrag : unsigned char
{
	Leer,
	WeissBauer,
	WeissTurm,
	WeissSpringer,
	WeissLaufer,
	WeissDame,
	WeissKoenig,
	WeissBauerGeist,
	SchwarzBauer,
	SchwarzTurm,
	SchwarzSpringer,
	SchwarzLaufer,
	SchwarzDame,
	SchwarzKoenig,
	SchwarzBauerGeist
};

enum class Spielzug : unsigned char
{
	Konform, Illegal, Schach, SchachMatt, Patt, Figurentausch
};

enum class Color : uint8_t
{
	Green,
	Red,
	Blue,
	Yellow,
	BGWhite,
	BGBlack,
	Reset
};

class Schachbrett
{
public:

	bool SpielerWeissAmZug = true;
	//TODO: Killliste aller zerstörten Einheiten :D
	//TODO: Zeitanzeige (vorsicht mit Input vom Spieler)

	/*	Zahl Koordinate X, Buchstabe für Koordinate Y
		Prüft ob ein Zug regelkonform ist.
		Retuns: Konform, Illegal, Schach ,SchachMatt, Patt*/
	Spielzug Zug(std::string pQuelle, std::string pZiel);
	void Draw();

	/*
		Setzt das Schachbrett auf die Anfangsposition
	*/
	void Reset();
	std::string ColorCode(Color pColor);
private:
	SpielfeldEintrag Spielfeld[8][8];
	uint16_t mZugZaehler=1;

};

