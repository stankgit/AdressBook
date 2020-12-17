#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


//------------------------------------------------------------------------

struct przyjaciel
{
    int id, iduzytkownika;
    string imie, nazwisko, adres, numer;
};
//------------------------------------------------------------------------

struct uzytkownik
{
    int iduz;
    string login, haslo;
};
//------------------------------------------------------------------------

void przypisanie_uz(vector<uzytkownik>& uzytkownicy)
{
    string idd,loginn,hasloo;
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);
    int nr=0;

    while(getline(plik,idd,'.')&&getline(plik,loginn,'|')&&getline(plik,hasloo))
    {
        uzytkownicy.push_back(uzytkownik());
        uzytkownicy[nr].iduz=stoi(idd);
        uzytkownicy[nr].login=loginn;
        uzytkownicy[nr].haslo=hasloo;
        nr++;
    }
}
//------------------------------------------------------------------------

void rejestracja(vector<uzytkownik>& uzytkownicy, int ilosc)
{

    int idd;

    if (ilosc!=0)
    {
        idd=uzytkownicy[ilosc-1].iduz+1;
    }
    else
    {
        idd=1;
    }

    string login,haslo;

    do
    {
        cout<<"Login: ";
        int zmienna=1;
        cin>>login;
        for (int x=0; x<ilosc; x++)
        {
            if(uzytkownicy[x].login==login)
            {
                cout<<"Uzytkownik o podanej nazwie juz istnieje"<<endl;
                zmienna=0;
                break;
            }
        }
        if (zmienna==1) break;
    }
    while(true);


    cout<<"Password: ";
    cin>>haslo;

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);
    if (ilosc!=0) plik<<endl;
    plik<<idd<<"."<<login<<"|"<<haslo;
    plik.close();


}
//------------------------------------------------------------------------

int logowanie(vector<uzytkownik>& uzytkownicy, int ilosc)
{
    int id;

    string login,haslo;
    cout<<"Login: ";
    cin>>login;
    cout<<"Haslo: ";
    cin>>haslo;
    int zmienna=1;

    for (int x=0; x<ilosc; x++)
    {
        if((uzytkownicy[x].login==login)&&(uzytkownicy[x].haslo==haslo))
        {
            id=uzytkownicy[x].iduz;
            zmienna=0;
            break;
        }
    }
    if (zmienna!=0)
    {
        cout<<"Login lub haslo nieprawidlowe!"<<endl<<endl<<"Nacisnij dowolony klawisz aby wrocic do glownego menu"<<endl;
        getchar();getchar();
        return -1;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout<< "Witaj ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout<<login;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout<<" w Twojej ksiazce adresowej. "<<endl<<endl<<"Nacisnij dowolny klawisz zeby wyswietlic menu...";
    getchar();getchar();
    return id;

}
//------------------------------------------------------------------------
int wyswietl_ksiazke(vector<przyjaciel>& kontakty, int iduz)
{
    system("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    cout<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<"KSIAZKA ADRESOWA:"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<"  IMIE  |  NAZWISKO  |  ADRES  |  NR TELEFONU"<<endl;
    cout<<"------------------------------------------------"<<endl;

    for (int i=0; i<kontakty.size(); i++)
    {
        cout<<kontakty[i].id<<"."<<kontakty[i].iduzytkownika<<"|"<<kontakty[i].imie<<"|"<<kontakty[i].nazwisko<<"|"<<kontakty[i].adres<<"|"<<kontakty[i].numer<<"|"<<endl;
    }
    cout << "------------------------------------------------"<<endl<<endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
//------------------------------------------------------------------------
int oblicz_ilosc()
{
    fstream plik;
    string linia;
    plik.open("Kontakty.txt", ios::in);
    int nr_linii=1;

    while(getline(plik,linia))
    {
        nr_linii++;
    }

    plik.close();

    return nr_linii-1;
}
//------------------------------------------------------------------------
int menu_wstepne()
{
    int wybor1, iduzytkownika;
    do
    {
        vector<uzytkownik> uzytkownicy;
        fstream plik;
        string linia, login, haslo;
        plik.open("Uzytkownicy.txt", ios::in);
        int nr_linii=1;

        while(getline(plik,linia))
        {
            cout<<linia<<endl;
            nr_linii++;
        }

        plik.close();
        int ilosc = nr_linii-1;
        if (ilosc!=0) przypisanie_uz(uzytkownicy);

        system("CLS");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
        cout << endl << "WITAMY W PROGRAMIE 'LOOK LOOK - ADRESS BOOK'"<<endl;
        cout << "------------------------------------------"<<endl;
        cout << "1. Rejestracja "<<endl;
        cout << "2. Logowanie"<<endl;
        cout << "9. Wyjdz z programu "<<endl;
        cout << "------------------------------------------"<<endl;
        cout << "Wybor: ";
        cin >> wybor1;

        switch (wybor1)
        {
        case 1:
            rejestracja(uzytkownicy, ilosc);
            break;

        case 2:
            iduzytkownika = logowanie(uzytkownicy, ilosc);
            break;
        case 9:
            exit(0);
        }
    }
    while ((wybor1 == 1)||(iduzytkownika==-1));
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    return iduzytkownika;
}
//------------------------------------------------------------------------
void wyswietl(vector<przyjaciel>& kontakty, int numerro)
{
    cout<<kontakty[numerro].id<<". "<<kontakty[numerro].iduzytkownika<< " | "<<kontakty[numerro].imie<<" | "<<kontakty[numerro].nazwisko<<" | "<<kontakty[numerro].adres<<" | "<<kontakty[numerro].numer<<endl;
}
//------------------------------------------------------------------------

int przypisanie(vector<przyjaciel>& kontakty, int idduzytk)
{
    string imiee, nazwiskoo,adress,numerr, idd, idduz;
    fstream plik;
    plik.open("Kontakty.txt", ios::in);
    int nr=0;
    int ostatni_id;
    while(getline(plik,idd,'.')&&getline(plik,idduz,'|')&&getline(plik,imiee,'|')&&getline(plik,nazwiskoo,'|')&&getline(plik,adress,'|')&&getline(plik,numerr,'|'))
    {
        if (stoi(idduz)==idduzytk)
        {
            kontakty.push_back(przyjaciel());
            kontakty[nr].id=stoi(idd);
            kontakty[nr].iduzytkownika=stoi(idduz);
            kontakty[nr].imie=imiee;
            kontakty[nr].nazwisko=nazwiskoo;
            kontakty[nr].adres=adress;
            kontakty[nr].numer=numerr;
            nr++;
        }
        ostatni_id=stoi(idd);
    }
    return ostatni_id;
}
//------------------------------------------------------------------------

void dodaj(vector<przyjaciel>& kontakty,int ilosc, int iduzytk, int ost_id)
{
    string imiee, nazwiskoo,adress,numerr;
    int idd;
    int idduz=iduzytk;
    if (ilosc!=0)
    {
        idd=ost_id+1;
    }
    else
    {
        idd=1;
    }
    cin.sync();
    cout<<"Wprowadz imie: ";
    getline(cin,imiee);
    cout<<"Wprowadz nazwisko: ";
    getline(cin,nazwiskoo);
    cout<<"Wprowadz adres: ";
    getline(cin,adress);
    cout<<"Wprowadz numer telefonu: ";
    getline(cin,numerr);
    fstream plik;
    plik.open("Kontakty.txt", ios::out | ios::app); //otwarcie pliku do zapisu
    if (ilosc!=0) plik<<endl;
    plik<<idd<<"."<<idduz<<"|"<<imiee<<"|"<<nazwiskoo<<"|"<<adress<<"|"<<numerr<<"|";
    plik.close();
    cout<<"Zapisywanie...";
    Sleep(1000);
}

//------------------------------------------------------------------------

void szukaj_imie(vector<przyjaciel>& kontakty)
{
    string szuk_imie;
    cin.sync();
    cout<<"Podaj szukane imie: ";
    cin>>szuk_imie;
    for (int j=0;j<kontakty.size();j++)
    {
        if (kontakty[j].imie==szuk_imie)
        {
            wyswietl(kontakty, j);
        }
    }
    system("pause");
}
//------------------------------------------------------------------------

void szukaj_nazwisko(vector<przyjaciel>& kontakty)
{
    string szuk_nazw;
    cin.sync();
    cout<<"Podaj szukane nazwisko: ";
    cin>>szuk_nazw;
    for (int j=0; j<kontakty.size(); j++)
    {
        if (kontakty[j].nazwisko==szuk_nazw)
        {
            wyswietl(kontakty, j);
        }
    }
    system("pause");
}

//------------------------------------------------------------------------

void zapisdopliku(string pozycjaedytowana, string findid, int numerpozycji)
{
        string nowa_pozycja;
        string linia, idd;
        cin.sync();
        getline(cin,nowa_pozycja);
        fstream plik;
        plik.open("Kontakty.txt", ios::in);
        fstream temp;
        temp.open("temp.txt", ios::out | ios::app);
        while(getline(plik,linia))
        {
            idd=linia.substr(0,linia.find("."));
            int position = linia.find('|');
            int position2 = linia.find('|', position+1);
            int position3 = linia.find('|', position2+1);
            int position4 = linia.find('|', position3+1);

            if (findid==idd)
            {
                if (numerpozycji==2) linia.replace(linia.find(pozycjaedytowana, position2),pozycjaedytowana.length(),nowa_pozycja);
                else if (numerpozycji==3)linia.replace(linia.find(pozycjaedytowana, position3+1),pozycjaedytowana.length(),nowa_pozycja);
                else if (numerpozycji==4)linia.replace(linia.find(pozycjaedytowana, position4+1),pozycjaedytowana.length(),nowa_pozycja);
                else linia.replace(linia.find(pozycjaedytowana),pozycjaedytowana.length(),nowa_pozycja);
            }

            temp << linia;
            if (!plik.eof()) temp<<endl;
        }
        temp.close();
        plik.close();
        remove("Kontakty.txt");
        rename("temp.txt","Kontakty.txt");
        cout<<"Zapisywanie...";
        Sleep(2000);
        return;
}

//------------------------------------------------------------------------

void edytuj_kontakt(vector<przyjaciel>& kontakty)
{
    string foundstatement;
    int szuk_id,position;
    int wybor2;
    cin.sync();
    cout<<endl<<"Podaj ID kontaktu, ktory chcesz zedytowac: ";
    cin>>szuk_id;
    for (int j=0; j<kontakty.size(); j++)
    {
        if (kontakty[j].id==szuk_id)
        {
            cout<<endl;
            wyswietl(kontakty, j);
            position = j;
            foundstatement = "Found";
            break;
        }
    }
    if (foundstatement!="Found")
    {
        cout<<endl<<"Pozycja o podanym ID nie istnieje..."<<endl<<endl;
        Sleep(3000);
        return;
    }
    string findid = to_string(kontakty[position].id);



    cout<<endl<<"Ktora pozycje chcesz edytowac?"<<endl;
    cout << "------------------------------------------"<<endl;
    cout << "1. Imie "<<endl;
    cout << "2. Nazwisko "<<endl;
    cout << "3. Adres "<<endl;
    cout << "4. Nr telefonu "<<endl;
    cout << "5. Powrot do Menu Glownego "<<endl;
    cout << "------------------------------------------"<<endl;
    cout << "Wybor: ";
    cin >> wybor2;

    switch (wybor2)
    {
    case 1:
    {
        cout<<"Wprowadz nowe imie: "<<endl;
        zapisdopliku(kontakty[position].imie, findid,wybor2);
        return;
    }

    case 2:
    {
        cout<<"Wprowadz nowe nazwisko: "<<endl;
        zapisdopliku(kontakty[position].nazwisko, findid,wybor2);
        return;
    }

    case 3:
    {
        cout<<"Wprowadz nowy adres: "<<endl;
        zapisdopliku(kontakty[position].adres, findid,wybor2);
        return;
    }

    case 4:
    {
        cout<<"Wprowadz nowy numer telefonu: "<<endl;
        zapisdopliku(kontakty[position].numer, findid,wybor2);
        return;
    }

    case 5:
    {
        cout<<"Powrot do glownego menu. Prosze czekac..."<<endl;
        Sleep(2000);
        return;
    }

    default:
    {
        cout<<"Nie wybrales zadnej z wymienionych opcji. Zegnam!"<<endl;
        Sleep(2000);
        return;
    }

    }
}

//------------------------------------------------------------------------


void usun_kontakt(vector<przyjaciel>& kontakty, int ostatni_id)
{
    string foundstatement;
    int szuk_id,position;
    int wybor2;
    cin.sync();
    cout<<endl<<"Podaj ID kontaktu, ktory chcesz usunac: ";
    cin>>szuk_id;
    for (int j=0; j<kontakty.size(); j++)
    {
        if (kontakty[j].id==szuk_id)
        {
            cout<<endl;
            wyswietl(kontakty, j);
            cout<<endl;
            position = j;
            foundstatement = "Found";
            break;
        }
    }
    if (foundstatement!="Found")
    {
        cout<<endl<<"Pozycja o podanym ID nie istnieje..."<<endl<<endl;
        Sleep(3000);
        return;
    }
    string continuechar;
    cout<<"Czy jestes pewny, ze chcesz usunac ten kontakt (t/n)?";
    cin>>continuechar;
    if (continuechar!="t")
    {
        cout<< "Jesli nie jestes pewny, to zapraszam z powrotem do glownego menu...";
        Sleep(3500);
        return;
    }
    string findid = to_string(kontakty[position].id);
    string linia, idd;
    fstream plik;
    plik.open("Kontakty.txt", ios::in);
    fstream temp;
    temp.open("temp.txt", ios::out | ios::app);
    while(getline(plik,linia))
    {
        idd=linia.substr(0,linia.find("."));
        if (findid!=idd)
        {
            temp << linia;
            if ((stoi(idd)==(ostatni_id-1))&&(stoi(findid)==ostatni_id));
            else if (!plik.eof()) temp<<endl;
        }
    }
    temp.close();
    plik.close();
    remove("Kontakty.txt");
    rename("temp.txt","Kontakty.txt");
    cout<<"Zapisywanie...";
    Sleep(2000);

}
//------------------------------------------------------------------------
int main()
{
    int iduzytkownika = menu_wstepne();
    int wybor, ost_id;
    do
    {
        vector<przyjaciel> kontakty;
        int ilosc=oblicz_ilosc();
        if (ilosc!=0)
        {
            ost_id=przypisanie(kontakty, iduzytkownika);
        }
        else
        {
            ost_id=0;
        }
        wyswietl_ksiazke(kontakty, iduzytkownika);

        cout << "MENU GLOWNE KSIAZKI ADRESOWEJ:"<<endl;
        cout << "------------------------------------------"<<endl;
        cout << "1. Dodaj kontakt "<<endl;
        cout << "2. Wyszukaj kontakt po imieniu "<<endl;
        cout << "3. Wyszukaj kontakt po nazwisku "<<endl;
        cout << "4. Edytuj kontakt "<<endl;
        cout << "5. Usun kontakt "<<endl;
        cout << "9. Koniec programu "<<endl;
        cout << "------------------------------------------"<<endl;
        cout << "Wybor: ";
        cin >> wybor;

        switch (wybor)
        {
        case 1:
            dodaj(kontakty,ilosc, iduzytkownika, ost_id);
            break;

        case 2:
            if (kontakty.size()!=0) szukaj_imie(kontakty);
            else
            {
                cout<< "Lista kontaktow jest pusta. Najpierw dodaj pozycje...";
                Sleep(3000);
            }
            break;

        case 3:
            if (kontakty.size()!=0) szukaj_nazwisko(kontakty);
            else
            {
                cout<< "Lista kontaktow jest pusta. Najpierw dodaj pozycje...";
                Sleep(3000);
            }
            break;
        case 4:
            if (kontakty.size()!=0) edytuj_kontakt(kontakty);
            else
            {
                cout<< "Lista kontaktow jest pusta. Najpierw dodaj pozycje...";
                Sleep(3000);
            }
            break;
        case 5:
            if (kontakty.size()!=0) usun_kontakt(kontakty, ost_id);
            else
            {
                cout<< "Lista kontaktow jest pusta. Najpierw dodaj pozycje...";
                Sleep(3000);
            }
            break;
        }
    }
    while (wybor != 9);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout<<endl << "---------------------------------------------------------------------------";
    cout<<endl<< "DZIEKUJEMY ZA KORZYSTANIE Z APLIKACJI KSIAZKI ADRESOWEJ. ZAPRASZAMY PONOWNIE!"<<endl;
    cout << "---------------------------------------------------------------------------"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    return 0;
}
