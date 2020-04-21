#include <iostream>
/*#include <stdio.h>
#include <io.h>
#include <fcntl.h>*/
#include "Schachbrett.h"

int main()
{
	//_setmode(_fileno(stdout), _O_U16TEXT);
	Schachbrett meinSchachbrett;
	meinSchachbrett.Reset();
	std::string ZugQuelle;
	std::string ZugZiel;
	Spielzug ZugErgebnis;
	meinSchachbrett.Draw();
	while (true)
	{
		do
		{
			if (meinSchachbrett.SpielerWeissAmZug)
			{
				std::cout << "Spieler Weiss Figur wählen: ";
				std::cin >> ZugQuelle;
				std::cout << "Spieler Weiss Ziel wählen: ";
				std::cin >> ZugZiel;
			}
			else
			{
				std::cout << "Spieler Schwarz Figur wählen: ";
				std::cin >> ZugQuelle;
				std::cout << "Spieler Schwarz Ziel wählen: ";
				std::cin >> ZugZiel;
			}

			ZugErgebnis = meinSchachbrett.Zug(ZugQuelle, ZugZiel);

		} while (ZugErgebnis == Spielzug::Illegal);

		switch (ZugErgebnis)
		{
		case Spielzug::Patt:
			std::cout << "Remis / Patt";
			return 0;
		case Spielzug::SchachMatt:
			if (meinSchachbrett.SpielerWeissAmZug)
				std::cout << "Spielende durch Sieg von Weiss";
			else
				std::cout << "Spielende durch Sieg von Schwarz";
			return 0;
		case Spielzug::Figurentausch:
			// TODO: Spieler nach neuer figur fragen der eigenen farbe
			//(alles ausser Bauer und König)
			break;
		default:
			meinSchachbrett.Draw();
			if (ZugErgebnis == Spielzug::Schach)
			{
				std::cout << meinSchachbrett.ColorCode(Color::Red) << "Vorsicht Schach \n" << meinSchachbrett.ColorCode(Color::Reset);
			}
		}


	}

	return 0;
}
