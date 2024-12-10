#include <iostream>
#include "organizm.h"
#include "ustawienia.h"
#include "generatorlosowy.h"
#include "sasiedztwo.h"
#include "mieszkaniec.h"
#include "osobniki.h"
#include "nisza.h"
#include "srodowisko.h"
#include <fstream>

using namespace std;

void drukujOrganizm(const Organizm & o)
{
    cout << "licznikZycia: "<< o.stanLicznikaZycia() << " licznikPosilkow: " << o.stanLicznikaPosilkow() << endl << "limitPosilkow: " << o.limitPosilkow << " kosztPotomka: " << o.kosztPotomka << endl << "głodny: " << o.glodny() << " pączkujący: "<< o.paczkujacy() << endl << endl;
}

void wyswietl(UstawieniaSymulacji & UST)
{
    cout << "Znak glon:" << UST.znakGlon << " zycieMin=" << UST.glonZycieMin << " zycieMax=" << UST.glonZycieMax << endl;
}

string nazwaRodzaju(RodzajMieszkanca rodzaj)
{
    switch (rodzaj)
    {
        case GLON: return "GLON";
        case GRZYB: return "GRZYB";
        case BAKTERIA: return "BAKTERIA";
        case PUSTKA: return "PUSTKA";
        case SCIANA: return "ŚCIANA";
        case TRUP: return "TRUP";
        case NIEZNANE: return "NIEZNANE";
    }
}

static Nisza n1, n2, n3;
static char sep = UstawieniaSymulacji::pobierzUstawienia().znakSeparator;

void wyswietlNisze()
{
    cout << n1.jakiSymbol() << sep << n2.jakiSymbol() << sep << n3.jakiSymbol() << endl;
}

void Srodowisko::wykonajAkcje(unsigned int wiersz,unsigned int kolumna)
{
    if(!nisza[wiersz][kolumna].lokatorZywy())
        return;
    Sasiedztwo sasiedztwo = ustalSasiedztwo(wiersz,kolumna);
    ZamiarMieszkanca zamiar = nisza[wiersz][kolumna].aktywujLokatora(sasiedztwo);
    unsigned int wiersz1 = wiersz, kolumna1 = kolumna;
    Sasiedztwo::zmienIdeksyWgPolozenia(zamiar.gdzie, wiersz1, kolumna1);
    Mieszkaniec *m =nullptr;
    switch (zamiar.akcja)
    {
        case NIC:
            wykonajSkok(wiersz,kolumna);
            break;
        case POTOMEK:
            m = nisza[wiersz][kolumna].wypuscPotomka();
            nisza[wiersz1][kolumna1].przyjmijLokatora(m);
            break;
        case POLOWANIE:
        case ROZKLAD:
            m = nisza[wiersz1][kolumna1].oddajLokatora();
            nisza[wiersz][kolumna].
            przyjmijZdobycz(m);
            break;
    }
}

void Srodowisko::wykonajKrokSymulacji()
{
    WektorIndeksow2D indeksyLosowe = GeneratorLosowy::indeksyLosowe(wiersze,kolumny);
    for(Indeks2D indeks : indeksyLosowe)
        wykonajAkcje(indeks.wiersz, indeks.kolumna);
}

int main() {
    Srodowisko ekoSystem=Srodowisko::czytajZPliku("/Users/martynageca/Desktop/tekst.txt");
    ofstream plikWynikowy("symulacja.txt");
    if(!plikWynikowy.is_open()) return 1;
    string stanSymulacji;
    unsigned long i = 0;
    do{
        system("clear");
        cout << "Krok symulacji: " << i << endl;
        plikWynikowy << "Krok symulacji: " << i << endl;
        stanSymulacji = ekoSystem.doTekstu();
        cout << endl << stanSymulacji << endl;
        plikWynikowy << stanSymulacji << endl;
        cin.ignore(1);
        ekoSystem++;
        i++;
    } while(i < 200 && !ekoSystem);
    cout << endl;
    plikWynikowy.close();
    return 0;
}



/*int main()
  {
  Organizm organizm1(8,3,2);
  Organizm organizm2 = organizm1;
  Organizm organizm3(organizm1);
  cout << "Wynik testu kreacji obiektów:" << endl << endl;
  cout << "Organizm1:" << endl;
  drukujOrganizm(organizm1);
  cout << "Organizm2" << endl;
  drukujOrganizm(organizm1);
  cout << "Organizm3" << endl;
  drukujOrganizm(organizm2);
  organizm1.posilek();
  organizm1.posilek();
  organizm2.posilek();
  organizm3.krokSymulacji();
  cout << "Wynik testu niezależności obiektów:" << endl << endl;
  cout << "Organizm1:" << endl;
  drukujOrganizm(organizm1);
  cout << "Organizm2" << endl;
  drukujOrganizm(organizm2);
  cout << "Organizm3" << endl;
  drukujOrganizm(organizm3);
  Organizm organizm4(8,3,2);
  cout << "Wynik testu symulacji:" << endl << endl;
  cout << "Stan początkowy:" << endl;
  drukujOrganizm(organizm4);
  for(int i=1; i<11; i++)
    {
    organizm4.krokSymulacji();
    if(organizm4.paczkujacy())
      {
      organizm4.potomek();
      cout << "---> Potomek" << endl;
      }
    else
      organizm4.posilek();
    cout << "Po wykonaniu kroku symulacji: " << i << endl;
    drukujOrganizm(organizm4);
    }
  return 0;
  }*/



/*int main()
  {
  UstawieniaSymulacji & UST1 = UstawieniaSymulacji::pobierzUstawienia();
  UstawieniaSymulacji & UST2 = UstawieniaSymulacji::pobierzUstawienia();
  UstawieniaSymulacji & UST3 = UstawieniaSymulacji::pobierzUstawienia();
  cout << "Pobranie ustawien 3x" << endl;
  cout << "UST1: "; wyswietl(UST1);
  cout << "UST2: "; wyswietl(UST2);
  cout << "UST3: "; wyswietl(UST3);
  cout << endl << "Zmiana wartości tylko 1x" << endl;
  UST2.glonZycieMax = 100;
  cout << "UST1: "; wyswietl(UST1);
  cout << "UST2: "; wyswietl(UST2);
  cout << "UST3: "; wyswietl(UST3);
  return 0;
  }*/



/*int main()
  {
  cout << "Liczby losowe typu int:" << endl;
  cout << " od 0 do 5: ";
  for(int i=0; i<10; i++)
    cout << GEN::losujOdZeraDo(5) << " ";
  cout << endl << " od 0 do 3: ";
  for(int i=0; i<10; i++)
    cout << GEN::losujOdZeraDo(3) << " ";
  cout << endl << " od 0 do 20: ";
  for(int i=0; i<10; i++)
    cout << GEN::losujOdZeraDo(20) << " ";
  cout << endl << endl;
  cout << "Liczby losowe typu long: " << endl;
  cout << " od -2 do 2:";
  for(int i=0; i<10; i++)
    cout << GEN::losujPomiedzy(-2L, 2L) <<" ";
  cout << endl << endl << "Liczby losowe typu unsigned short: " << endl;
  cout << " od 2 do 6: ";
  unsigned short min=2, max=6;
  for(int i=0; i<10; i++)
    cout << GEN::losujPomiedzy(max, min) <<" ";
  cout << endl << endl;
  for(Indeks2D & I : GEN::indeksyLosowe(2,4))
    cout << "{" <<I.wiersz << ", " << I.kolumna << "}\n";
  return 0;
  }*/



/*int main()
  {
  Sasiedztwo sasiedztwo;
  sasiedztwo.okreslSasiada(P,GLON);
  sasiedztwo.okreslSasiada(PG,GRZYB);
  sasiedztwo.okreslSasiada(G,GRZYB);
  sasiedztwo.okreslSasiada(LG,GLON);
  sasiedztwo.okreslSasiada(L,BAKTERIA);
  sasiedztwo.okreslSasiada(LD,BAKTERIA);
  sasiedztwo.okreslSasiada(D,GLON);
  sasiedztwo.okreslSasiada(PD,PUSTKA);
  cout << "Przegląd sąsiedztwa:" << endl;
  for(int i=0; i<8; i++)
    {
    Polozenie p = static_cast<Polozenie>(i);
    RodzajMieszkanca r = sasiedztwo.ktoJestSasiadem(p);
    cout << "polozenie=" << p << " rodzaj=" << nazwaRodzaju(r) << endl;
    }
  cout << endl << "Policzenie sasiadów" << "określonego rodzaju:" << endl << " glony=" << sasiedztwo.ile(GLON) << endl << " grzyby=" << sasiedztwo.ile(GRZYB) << endl << " trupy=" << sasiedztwo.ile(TRUP) << endl;
  cout << endl << "Wylosowanie sasiada:" << endl << " glon -> " << sasiedztwo.losujSasiada(GLON) << endl << " pustka -> " << sasiedztwo.losujSasiada(PUSTKA) << endl << " trup -> " << sasiedztwo.losujSasiada(TRUP) << endl;
  long wiersz, kolumna;
  cout << endl << "Zmiana indeksów [5][7]" << "wg polozenia:" << endl;
  for(int i=0; i<8; i++)
    {
    Polozenie p = static_cast<Polozenie>(i);
    wiersz = 5; kolumna = 7;
    Sasiedztwo::zmienIdeksyWgPolozenia(p,wiersz,kolumna);
    cout << " położenie: " << p << " ->[" << wiersz << "][" << kolumna << "]" << endl;
    }
  cout << endl;
  return 0;
  }*/



/*int main()
  {
  cout << "Puste nisze: ";
  wyswietlNisze();
  cout << "Lokowanie mieszkańców: ";
  n1.przyjmijLokatora(new Glon());
  n3.przyjmijLokatora(new Grzyb());
  wyswietlNisze();
  cout << "Przesuwanie lokatorów: ";
  n2 = n1;
  wyswietlNisze();
  cout << "Przesuwanie lokatorów:";
  n3 = n2;
  wyswietlNisze();
  cout << endl;
  return 0;
  }*/



/*int main()
  {
  Nisza nisza;
  nisza.przyjmijLokatora(new Bakteria());
  cout << "Kto w niszy: " << nisza.ktoTuMieszka() << endl;
  cout << "Czy żywy: " << nisza.lokatorZywy() << endl;
  Sasiedztwo sasiedztwo;
  sasiedztwo.okreslSasiada(P,GLON);
  sasiedztwo.okreslSasiada(PG,GRZYB);
  sasiedztwo.okreslSasiada(G,GRZYB);
  sasiedztwo.okreslSasiada(LG,GLON);
  sasiedztwo.okreslSasiada(L,BAKTERIA);
  sasiedztwo.okreslSasiada(LD,BAKTERIA);
  sasiedztwo.okreslSasiada(D,GLON);
  sasiedztwo.okreslSasiada(PD,PUSTKA);
  ZamiarMieszkanca zamiar = nisza.aktywujLokatora(sasiedztwo);
  cout << "Akjca: " << zamiar.akcja << " gdzie: " << zamiar.gdzie << endl;
  cout << endl;
  return 0;
  }*/
