#include "Schachbrett.h"

Spielzug Schachbrett::Zug(std::string pQuelle, std::string pZiel)
{
#pragma region InputTesting


	uint8_t QuelleX;

	if (pQuelle[0] < 97)
		QuelleX = pQuelle[0] - 65;
	else
		QuelleX = pQuelle[0] - 97;


	uint8_t QuelleY = pQuelle[1] - 49;
	uint8_t ZielX;

	if (pZiel[0] < 97)
		ZielX = pZiel[0] - 65;
	else
		ZielX = pZiel[0] - 97;

	uint8_t ZielY = pZiel[1] - 49;

	if (QuelleX > 7 ||
		QuelleY > 7 ||
		ZielX > 7 ||
		ZielY > 7 ||
		(QuelleX == ZielX && QuelleY == ZielY) ||
		Spielfeld[QuelleY][QuelleX] == SpielfeldEintrag::Leer)	//TODO: Ghosts d�rfen angesprungen werden
	{
		return Spielzug::Illegal;
	}

	if ((SpielerWeissAmZug && (int)(Spielfeld[QuelleY][QuelleX]) > 7) ||
		(!SpielerWeissAmZug && (int)(Spielfeld[QuelleY][QuelleX]) < 8) ||
		(!SpielerWeissAmZug && (int)(Spielfeld[ZielY][ZielX]) > 7) ||
		(SpielerWeissAmZug && (int)(Spielfeld[ZielY][ZielX]) < 8 && (Spielfeld[ZielY][ZielX]) != SpielfeldEintrag::Leer) // auf das leere feld 0 achten
		)
	{
		return Spielzug::Illegal;
	}

#pragma endregion
	// eingaben verarbeiten

	switch (Spielfeld[QuelleY][QuelleX])
	{
	case SpielfeldEintrag::WeissBauer:
		//TODO: noch nicht implementiert
#pragma region WeissBauer

		// quelle 1 1
		// ziel   2 1
		if (QuelleY == 1 &&
			Spielfeld[QuelleY + 1][QuelleX] == SpielfeldEintrag::Leer &&
			Spielfeld[QuelleY + 2][QuelleX] == SpielfeldEintrag::Leer &&
			ZielY == 3&&
			QuelleX == ZielX) // doppelmove erlaubt
		{
			Spielfeld[QuelleY][QuelleX] == SpielfeldEintrag::Leer;
			Spielfeld[QuelleY + 1][QuelleX] == SpielfeldEintrag::WeissBauerGeist;
			Spielfeld[QuelleY + 2][QuelleX] == SpielfeldEintrag::WeissBauer;
			// darf sich positiv auf Y achse zwei felder bewegen (ghost mode)
		}

		if (Spielfeld[ZielY][ZielX] == SpielfeldEintrag::Leer && // darf sich positiv auf Y achse ein feld bewegen
			QuelleY + 1 == ZielY &&
			QuelleX == ZielX)
		{
			Spielfeld[QuelleY][QuelleX] == SpielfeldEintrag::Leer;
			Spielfeld[ZielY][ZielX] == SpielfeldEintrag::WeissBauer;
		}


		if (QuelleY + 1 == ZielY &&// schlagen
			abs(ZielX-QuelleX) == 1 &&
			Spielfeld[ZielY][ZielX] != SpielfeldEintrag::Leer)
		{
			Spielfeld[QuelleY][QuelleX] == SpielfeldEintrag::Leer;
			Spielfeld[ZielY][ZielX] == SpielfeldEintrag::WeissBauer;
		}
		


		// darf sich positiv auf Y achse ein feld und ein feld x (absolut) bewegen wenn dort ein gegner ist
		// wenn Y achse 7 erreicht wird er zu einer SpielfeldEintrag::WeissDame
#pragma endregion
		break;
	case SpielfeldEintrag::WeissTurm:
#pragma region WeissTurm
		//  wenn Turm -> nur horizontal oder vertikal, solange nix im weg steht
		if ((QuelleX == ZielX && QuelleY != ZielY) ||  // Vertikaler Move
			(QuelleY == ZielY && QuelleX != ZielX))
		{
			uint8_t queryX = QuelleX;
			uint8_t queryY = QuelleY;

			while (queryX != ZielX || queryY != ZielY)
			{
				if (queryX < ZielX) queryX++;// z�hlen X
				else if (queryX > ZielX) queryX--;// z�hlen X

				if (queryY < ZielY) queryY++;// z�hlen Y
				else if (queryY > ZielY) queryY--;

				if (Spielfeld[queryY][queryX] != SpielfeldEintrag::Leer &&
					(queryX != ZielX || queryY != ZielY))// feld nicht leer?
					return Spielzug::Illegal;
			}
			Spielfeld[QuelleY][QuelleX] = SpielfeldEintrag::Leer;
			Spielfeld[ZielY][ZielX] = SpielfeldEintrag::WeissTurm;

		}
		else
			return Spielzug::Illegal;
#pragma endregion
		break;
	case SpielfeldEintrag::WeissSpringer:
#pragma region WeissSpringer



		if ((abs(QuelleX - ZielX) == 2 && abs(QuelleY - ZielY) == 1) ||// wenn x entfernung 2 ist und y entfernung 1
			(abs(QuelleY - ZielY) == 2 && abs(QuelleX - ZielX) == 1))// wenn y entfernung 2 ist und x entfernung 1	
		{
			Spielfeld[ZielY][ZielX] = Spielfeld[QuelleY][QuelleX];
			Spielfeld[QuelleY][QuelleX] = SpielfeldEintrag::Leer;
		}
		else
		{
			return Spielzug::Illegal;
		}
#pragma endregion
		break;
	case SpielfeldEintrag::WeissLaufer:
#pragma region WeissLaufer

		if ((ZielX - QuelleX == ZielY - QuelleY) ||    // Diagonal1
			(QuelleX - ZielX == ZielY - QuelleY))      // Diagnonal2
		{
			uint8_t queryX = QuelleX;
			uint8_t queryY = QuelleY;

			while (queryX != ZielX || queryY != ZielY)
			{
				if (queryX < ZielX) queryX++;// z�hlen X
				else if (queryX > ZielX) queryX--;// z�hlen X

				if (queryY < ZielY) queryY++;// z�hlen Y
				else if (queryY > ZielY) queryY--;

				if (Spielfeld[queryY][queryX] != SpielfeldEintrag::Leer &&
					(queryX != ZielX || queryY != ZielY))// feld nicht leer?
					return Spielzug::Illegal;
			}
			Spielfeld[QuelleY][QuelleX] = SpielfeldEintrag::Leer;
			Spielfeld[ZielY][ZielX] = SpielfeldEintrag::WeissLaufer;

		}
		else
			return Spielzug::Illegal;
#pragma endregion 
		break;
	case SpielfeldEintrag::WeissDame:
#pragma region WeissDame

		if ((QuelleX == ZielX && QuelleY != ZielY) ||  // Vertikaler Move
			(QuelleY == ZielY && QuelleX != ZielX) ||  // horizontal
			(ZielX - QuelleX == ZielY - QuelleY) ||    // Diagonal1
			(QuelleX - ZielX == ZielY - QuelleY))      // Diagnonal2
		{
			uint8_t queryX = QuelleX;
			uint8_t queryY = QuelleY;

			while (queryX != ZielX || queryY != ZielY)
			{
				if (queryX < ZielX) queryX++;// z�hlen X
				else if (queryX > ZielX) queryX--;// z�hlen X

				if (queryY < ZielY) queryY++;// z�hlen Y
				else if (queryY > ZielY) queryY--;

				if (Spielfeld[queryY][queryX] != SpielfeldEintrag::Leer &&
					(queryX != ZielX || queryY != ZielY))// feld nicht leer?
					return Spielzug::Illegal;
			}
			Spielfeld[QuelleY][QuelleX] = SpielfeldEintrag::Leer;
			Spielfeld[ZielY][ZielX] = SpielfeldEintrag::WeissDame;

		}
		else
			return Spielzug::Illegal;

#pragma endregion
		break;
	case SpielfeldEintrag::WeissKoenig:
#pragma region WeissKoenig
		if (ZielX > QuelleX - 2 && ZielX < QuelleX + 2 && //  wenn K�nig -> nur ein feld in jede richtung
			ZielY > QuelleY - 2 && ZielY < QuelleY + 2)
		{
			Spielfeld[QuelleY][QuelleX] = SpielfeldEintrag::Leer;//		quelle auf leer �ndern
			Spielfeld[ZielY][ZielX] = SpielfeldEintrag::WeissKoenig;//		ziel auf k�nig �ndern
		}
		else
			return Spielzug::Illegal;
		//TODO:rochade -> der K�nig kann mit Turm getauscht werden wenn zwischen ihnen platz ist und sich beide noch nicht bewegt haben
#pragma endregion
		break;
	case SpielfeldEintrag::SchwarzBauer:
		//TODO: noch nicht implementiert
#pragma region SchwarzBauer


		//	wenn bauer -> ziel nur in Y koordinate 1 feld verschieben * (ausser beim ersten mal)
#pragma endregion
		break;
	case SpielfeldEintrag::SchwarzTurm:
#pragma region SchwarzTurm
		if ((QuelleX == ZielX && QuelleY != ZielY) ||  // Vertikaler Move
			(QuelleY == ZielY && QuelleX != ZielX))
		{
			uint8_t queryX = QuelleX;
			uint8_t queryY = QuelleY;

			while (queryX != ZielX || queryY != ZielY)
			{
				if (queryX < ZielX) queryX++;// z�hlen X
				else if (queryX > ZielX) queryX--;// z�hlen X

				if (queryY < ZielY) queryY++;// z�hlen Y
				else if (queryY > ZielY) queryY--;

				if (Spielfeld[queryY][queryX] != SpielfeldEintrag::Leer &&
					(queryX != ZielX || queryY != ZielY))// feld nicht leer?
					return Spielzug::Illegal;
			}
			Spielfeld[QuelleY][QuelleX] = SpielfeldEintrag::Leer;
			Spielfeld[ZielY][ZielX] = SpielfeldEintrag::SchwarzTurm;

		}
		else
			return Spielzug::Illegal;
#pragma endregion
		break;
	case SpielfeldEintrag::SchwarzSpringer:
#pragma region SchwarzSpringer
		if ((abs(QuelleX - ZielX) == 2 && abs(QuelleY - ZielY) == 1) ||// wenn x entfernung 2 ist und y entfernung 1
			(abs(QuelleY - ZielY) == 2 && abs(QuelleX - ZielX) == 1))// wenn y entfernung 2 ist und x entfernung 1	
		{
			Spielfeld[ZielY][ZielX] = Spielfeld[QuelleY][QuelleX];
			Spielfeld[QuelleY][QuelleX] = SpielfeldEintrag::Leer;
		}
		else
		{
			return Spielzug::Illegal;
		}
#pragma endregion
		break;
	case SpielfeldEintrag::SchwarzLaufer:
#pragma region SchwarzLaufer
		if ((ZielX - QuelleX == ZielY - QuelleY) ||    // Diagonal1
			(QuelleX - ZielX == ZielY - QuelleY))      // Diagnonal2
		{
			uint8_t queryX = QuelleX;
			uint8_t queryY = QuelleY;

			while (queryX != ZielX || queryY != ZielY)
			{
				if (queryX < ZielX) queryX++;// z�hlen X
				else if (queryX > ZielX) queryX--;// z�hlen X

				if (queryY < ZielY) queryY++;// z�hlen Y
				else if (queryY > ZielY) queryY--;

				if (Spielfeld[queryY][queryX] != SpielfeldEintrag::Leer &&
					(queryX != ZielX || queryY != ZielY))// feld nicht leer?
					return Spielzug::Illegal;
			}
			Spielfeld[QuelleY][QuelleX] = SpielfeldEintrag::Leer;
			Spielfeld[ZielY][ZielX] = SpielfeldEintrag::SchwarzLaufer;

		}
		else
			return Spielzug::Illegal;
#pragma endregion
		break;
	case SpielfeldEintrag::SchwarzDame:
#pragma region SchwarzDame
		if ((QuelleX == ZielX && QuelleY != ZielY) ||  // Vertikaler Move
			(QuelleY == ZielY && QuelleX != ZielX) ||  // horizontal
			(ZielX - QuelleX == ZielY - QuelleY) ||    // Diagonal1
			(QuelleX - ZielX == ZielY - QuelleY))      // Diagnonal2
		{
			uint8_t queryX = QuelleX;
			uint8_t queryY = QuelleY;

			while (queryX != ZielX || queryY != ZielY)
			{
				if (queryX < ZielX) queryX++;// z�hlen X
				else if (queryX > ZielX) queryX--;// z�hlen X

				if (queryY < ZielY) queryY++;// z�hlen Y
				else if (queryY > ZielY) queryY--;

				if (Spielfeld[queryY][queryX] != SpielfeldEintrag::Leer &&
					(queryX != ZielX || queryY != ZielY))// feld nicht leer?
					return Spielzug::Illegal;
			}
			Spielfeld[QuelleY][QuelleX] = SpielfeldEintrag::Leer;
			Spielfeld[ZielY][ZielX] = SpielfeldEintrag::SchwarzDame;

		}
		else
			return Spielzug::Illegal;
#pragma endregion
		break;
	case SpielfeldEintrag::SchwarzKoenig:
#pragma region SchwarzKoenig
		if (ZielX > QuelleX - 2 && ZielX < QuelleX + 2 && //  wenn K�nig -> nur ein feld in jede richtung
			ZielY > QuelleY - 2 && ZielY < QuelleY + 2)
		{
			Spielfeld[QuelleY][QuelleX] = SpielfeldEintrag::Leer;//		quelle auf leer �ndern
			Spielfeld[ZielY][ZielX] = SpielfeldEintrag::SchwarzKoenig;//		ziel auf k�nig �ndern
		}
		else
			return Spielzug::Illegal;
		//TODO:rochade -> der K�nig kann mit Turm getauscht werden wenn zwischen ihnen platz ist und sich beide noch nicht bewegt haben
#pragma endregion
		break;
	default:
		std::cerr << "Fehler: unbekannter Spielfeldinhalt\n";
		break;
	}

	mZugZaehler++;
	SpielerWeissAmZug = !SpielerWeissAmZug;
	return Spielzug::Konform;
}

void Schachbrett::Draw()
{

	//�berschrift ausgeben
	//Koordinatenachsen
	system("cls");

	std::cout << "Schachspiel ZugNr.: " << mZugZaehler << "\n";
	std::cout << " A B C D E F G H\n";
	for (size_t Y = 0; Y < 8; Y++)
	{
		std::cout << Y + 1;
		for (size_t X = 0; X < 8; X++)
		{
			if ((X + Y) % 2 == 0)
			{
				std::cout << ColorCode(Color::BGWhite);
			}
			else
			{
				std::cout << ColorCode(Color::BGBlack);
			}

			switch (Spielfeld[Y][X])
			{
			case SpielfeldEintrag::SchwarzBauerGeist:
			case SpielfeldEintrag::WeissBauerGeist:
			case SpielfeldEintrag::Leer:
				std::cout << "  ";
				break;
			case SpielfeldEintrag::WeissBauer:
				std::cout << ColorCode(Color::Yellow) << "B ";
				break;
			case SpielfeldEintrag::WeissTurm:
				std::cout << ColorCode(Color::Yellow) << "T ";
				break;
			case SpielfeldEintrag::WeissSpringer:
				std::cout << ColorCode(Color::Yellow) << "S ";
				break;
			case SpielfeldEintrag::WeissLaufer:
				std::cout << ColorCode(Color::Yellow) << "L ";
				break;
			case SpielfeldEintrag::WeissDame:
				std::cout << ColorCode(Color::Yellow) << "D ";
				break;
			case SpielfeldEintrag::WeissKoenig:
				std::cout << ColorCode(Color::Yellow) << "K ";
				break;
			case SpielfeldEintrag::SchwarzBauer:
				std::cout << ColorCode(Color::Red) << "B ";
				break;
			case SpielfeldEintrag::SchwarzTurm:
				std::cout << ColorCode(Color::Red) << "T ";
				break;
			case SpielfeldEintrag::SchwarzSpringer:
				std::cout << ColorCode(Color::Red) << "S ";
				break;
			case SpielfeldEintrag::SchwarzLaufer:
				std::cout << ColorCode(Color::Red) << "L ";
				break;
			case SpielfeldEintrag::SchwarzDame:
				std::cout << ColorCode(Color::Red) << "D ";
				break;
			case SpielfeldEintrag::SchwarzKoenig:
				std::cout << ColorCode(Color::Red) << "K ";
				break;
			default:
				std::cout << "Unbekannte Daten im Spielfeld :(";
				break;
			}
			std::cout << ColorCode(Color::Reset);
		}
		std::cout << "\n";
	}

	//inhalt des Feldes
	//Abschluss des Spielfeldes

}

void Schachbrett::Reset()
{
	Spielfeld[0][0] = SpielfeldEintrag::WeissTurm;
	Spielfeld[0][1] = SpielfeldEintrag::WeissSpringer;
	Spielfeld[0][2] = SpielfeldEintrag::WeissLaufer;
	Spielfeld[0][3] = SpielfeldEintrag::WeissDame;
	Spielfeld[0][4] = SpielfeldEintrag::WeissKoenig;
	Spielfeld[0][5] = SpielfeldEintrag::WeissLaufer;
	Spielfeld[0][6] = SpielfeldEintrag::WeissSpringer;
	Spielfeld[0][7] = SpielfeldEintrag::WeissTurm;

	for (size_t i = 0; i < 8; i++) Spielfeld[1][i] = SpielfeldEintrag::Leer; //Hack: WeissBauer

	for (size_t j = 2; j < 6; j++)	for (size_t i = 0; i < 8; i++) Spielfeld[j][i] = SpielfeldEintrag::Leer;

	for (size_t i = 0; i < 8; i++) Spielfeld[6][i] = SpielfeldEintrag::Leer; //Hack: SchwarzBauer

	Spielfeld[7][0] = SpielfeldEintrag::SchwarzTurm;
	Spielfeld[7][1] = SpielfeldEintrag::SchwarzSpringer;
	Spielfeld[7][2] = SpielfeldEintrag::SchwarzLaufer;
	Spielfeld[7][3] = SpielfeldEintrag::SchwarzDame;
	Spielfeld[7][4] = SpielfeldEintrag::SchwarzKoenig;
	Spielfeld[7][5] = SpielfeldEintrag::SchwarzLaufer;
	Spielfeld[7][6] = SpielfeldEintrag::SchwarzSpringer;
	Spielfeld[7][7] = SpielfeldEintrag::SchwarzTurm;

	SpielerWeissAmZug = true;
}

std::string Schachbrett::ColorCode(Color pColor)
{
	switch (pColor)
	{
	case Color::Green:
		return "\x1b[32m";
	case Color::Red:
		return "\x1b[31m";
	case Color::Blue:
		return "\x1b[34m";
	case Color::Yellow:
		return "\x1b[33m";
	case Color::Reset:
		return "\033[0m";
	case Color::BGBlack:
		return "\x1b[40m";
	case Color::BGWhite:
		return "\x1b[47m";
	default:
		std::cerr << "Farbe nicht unterst�tzt";
		return "\x1b[37m";
	}
}