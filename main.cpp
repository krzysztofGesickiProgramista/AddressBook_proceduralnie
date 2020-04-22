#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <cstdio>

using namespace std;

string addressesFileName = "addresses.txt";
string usersFileName = "users.txt";

struct Contact {
    int id, userID;
    string name, surname, phoneNumber, email, address;
};

struct User {
    int id;
    string name, password;
};

void showContacts(int _contactsNumber, vector <Contact> _contacts) {
    cout << "Lista zapisanych kontaktow: " << endl << endl;

    for (int i = 0; i < _contactsNumber; i++) {
        cout << "ID kontaktu: " << _contacts[i].id << endl;
        cout << "Imie: " << _contacts[i].name << endl;
        cout << "Nazwisko: " << _contacts[i].surname << endl;
        cout << "Numer telefonu: " << _contacts[i].phoneNumber << endl;
        cout << "Adres e-mail: " << _contacts[i].email << endl;
        cout << "Adres: " << _contacts[i].address << endl;
        cout << endl;
    }
    cout << endl << "(wcisnij enter aby wrocic do menu glownego)";
    cin.sync();
    cin.get();
}

int checkLastID () {
    string textLine = "";
    string idToConvert = "";
    int lastID = 0;
    fstream textFile;
    textFile.open(addressesFileName.c_str(), ios::in);
    if (textFile.good() == false) {
        cout << "Nie udalo sie otworzyc pliku z Kontaktami!";
        Sleep(2000);
        exit(0);
    }
    int i = 0;
    while (getline(textFile, textLine)) {
        if (textLine[0] != ' ') {
            idToConvert = "";
            i = 0;
            while (textLine[i] != '|') {
                idToConvert += textLine[i];
                i++;
            }
        }
    }
    lastID = atoi(idToConvert.c_str());
    return lastID;
}

int addNewContact(int _contactsNumber, vector <Contact> & _contacts, int _loggedUserID) {
    Contact temporaryContact;
    int ID = 0;
    ID = checkLastID();
    temporaryContact.id = ID + 1;
    temporaryContact.userID = _loggedUserID;
    cin.ignore();
    cout << "Podaj imie: ";
    getline(cin, temporaryContact.name);
    cout << endl << "Podaj nazwisko: ";
    getline(cin, temporaryContact.surname);
    cout << endl << "Podaj numer telefonu: ";
    getline(cin, temporaryContact.phoneNumber);
    cout << endl << "Podaj adres e-mail: ";
    getline(cin, temporaryContact.email);
    cout << endl << "Podaj adres: ";
    getline(cin, temporaryContact.address);
    _contacts.push_back(temporaryContact);

    fstream textFile;
    textFile.open(addressesFileName.c_str(), ios::out|ios::app);
    if (textFile.good() == false) {
        cout << "Nie udalo sie otworzyc pliku z Kontaktami!";
        Sleep(2000);
        exit(0);
    }
    textFile << _contacts[_contactsNumber].id << "|";
    textFile << _contacts[_contactsNumber].userID << "|";
    textFile << _contacts[_contactsNumber].name << "|";
    textFile << _contacts[_contactsNumber].surname << "|";
    textFile << _contacts[_contactsNumber].phoneNumber << "|";
    textFile << _contacts[_contactsNumber].email << "|";
    textFile << _contacts[_contactsNumber].address << "|" << endl;
    textFile.close();

    cout << "Kontakt dodany! ";
    cout << endl << "(wcisnij enter aby wrocic do menu glownego)";
    cin.sync();
    cin.get();

    return _contactsNumber+1;
}

void searchContactByName(int _contactsNumber, vector <Contact> _contacts) {
    string searchFor;
    cout << "Podaj szukana fraze (imie): ";
    cin.ignore();
    getline(cin, searchFor);
    for (int i = 0; i < _contactsNumber; i++) {
        if (searchFor == _contacts[i].name) {
            cout << "ID kontaktu: " << _contacts[i].id << endl;
            cout << "Imie: " << _contacts[i].name << endl;
            cout << "Nazwisko: " << _contacts[i].surname << endl;
            cout << "Numer telefonu: " << _contacts[i].phoneNumber << endl;
            cout << "Adres e-mail: " << _contacts[i].email << endl;
            cout << "Adres: " << _contacts[i].address << endl;
            cout << endl;
        }
    }
    cout << endl << "(wcisnij enter aby wrocic do menu glownego)";
    cin.sync();
    cin.get();
}

void searchContactBySurname(int _contactsNumber, vector <Contact> _contacts) {
    string searchFor;
    cout << "Podaj szukana fraze (nazwisko): ";
    cin.ignore();
    getline(cin, searchFor);
    for (int i = 0; i < _contactsNumber; i++) {
        if (searchFor == _contacts[i].surname) {
            cout << "ID kontaktu: " << _contacts[i].id << endl;
            cout << "Imie: " << _contacts[i].name << endl;
            cout << "Nazwisko: " << _contacts[i].surname << endl;
            cout << "Numer telefonu: " << _contacts[i].phoneNumber << endl;
            cout << "Adres e-mail: " << _contacts[i].email << endl;
            cout << "Adres: " << _contacts[i].address << endl;
            cout << endl;
        }
    }
    cout << endl << "(wcisnij enter aby wrocic do menu glownego)";
    cin.sync();
    cin.get();
}

string explodeStringLine (int position, string _textLine) {
    string singleObject = "";
    int countPosition = 1;
    int stringSize = _textLine.size();
    for (int i = 0; i < stringSize; i++) {
        if (_textLine[i] == '|') {
            if (countPosition == position) {
                return singleObject;
            } else {
                countPosition++;
                singleObject = "";
            }
        } else
            singleObject += _textLine[i];
    }
}

int loadAddressesTextFile(vector <Contact> & _contacts, int _loggedUserID) {
    fstream textFile;
    string textLine;
    string idToConvert;
    textFile.open(addressesFileName.c_str(), ios::in);
    if (textFile.good() == false) {
        ofstream temp (addressesFileName.c_str());
        textFile.open(addressesFileName.c_str(), ios::in);
        if (textFile.good() == false) {
            cout << "Nie udalo sie otworzyc pliku z Kontaktami!";
            Sleep(2000);
            exit(0);
        }
    }
    _contacts = vector <Contact> ();
    Contact temporaryContact;
    int contactsNumber = 0;
    while (getline(textFile,textLine)) {
        idToConvert = explodeStringLine(1, textLine);
        temporaryContact.id = atoi(idToConvert.c_str());
        idToConvert = explodeStringLine(2, textLine);
        temporaryContact.userID = atoi(idToConvert.c_str());
        if (temporaryContact.userID == _loggedUserID)
        {
            temporaryContact.name = explodeStringLine(3, textLine);
            temporaryContact.surname = explodeStringLine(4, textLine);
            temporaryContact.phoneNumber = explodeStringLine(5, textLine);
            temporaryContact.email = explodeStringLine(6, textLine);
            temporaryContact.address = explodeStringLine(7, textLine);
            contactsNumber++;
            _contacts.push_back(temporaryContact);
        }
    }
    textFile.close();
    return contactsNumber;
}

void showMenuLogged () {
    system("cls");
    cout << "1. Dodaj adresata"  <<  endl;
    cout << "2. Wyszukaj po imieniu"  <<  endl;
    cout << "3. Wyszukaj po nazwisku"  <<  endl;
    cout << "4. Wyswietl wszystkich adresatow"  <<  endl;
    cout << "5. Usun adresata"  <<  endl;
    cout << "6. Edytuj adresata"  <<  endl;
    cout << "7. Zmien haslo"  <<  endl;
    cout << "8. Wyloguj sie"  <<  endl;
    cout << endl;
    cout << "Twoj wybor: ";
}

void showMenuUnLogged () {
    system("cls");
    cout << "1. Logowanie"  <<  endl;
    cout << "2. Rejestracja"  <<  endl;
    cout << "9. Zamknij program"  <<  endl;
    cout << endl;
    cout << "Twoj wybor: ";
}

int checkIdFromStringLine (string textLine) {
    string idToConvert;
    int i = 0;
    int ID = 0;
    if (textLine[0] != ' ') {
        idToConvert = "";
        i = 0;
        while (textLine[i] != '|') {
            idToConvert += textLine[i];
            i++;
        }
    }
    ID = atoi(idToConvert.c_str());
    return ID;
}

void loadEditedVectorToFile (vector <Contact> & _contacts, int _editedContactID, int _position) {
    int contactID = 0;
    fstream originalTextFile;
    string originalTextLine;
    fstream temporaryTextFile;
    ofstream temp ("addressesTemp.txt");
    originalTextFile.open(addressesFileName.c_str(), ios::in);
    temporaryTextFile.open("addressesTemp.txt", ios::out|ios::app);
    if (originalTextFile.good() == false) {
        cout << "Nie udalo sie otworzyc pliku z Kontaktami!";
        Sleep(2000);
        exit(0);
    }
    while (getline(originalTextFile,originalTextLine))
    {
        contactID = checkIdFromStringLine(originalTextLine);
        if (contactID != _editedContactID) {
            temporaryTextFile << originalTextLine << endl;
        } else {
            temporaryTextFile << _contacts[_position].id << "|";
            temporaryTextFile << _contacts[_position].userID << "|";
            temporaryTextFile << _contacts[_position].name << "|";
            temporaryTextFile << _contacts[_position].surname << "|";
            temporaryTextFile << _contacts[_position].phoneNumber << "|";
            temporaryTextFile << _contacts[_position].email << "|";
            temporaryTextFile << _contacts[_position].address << "|" << endl;
        }
    }
    originalTextFile.close();
    temporaryTextFile.close();
    temp.close();
    if (remove (addressesFileName.c_str()) != 0)
    {
        cout << "Blad przy zapisie!";
    }
    if (rename ("addressesTemp.txt", addressesFileName.c_str()) != 0)
    {
        cout << "Blad przy zapisie!";
    }
}

void loadDeletedVectorToFile (vector <Contact> & _contacts, int _deletedContactID) {
    int contactID = 0;
    fstream originalTextFile;
    string originalTextLine;
    fstream temporaryTextFile;
    ofstream temp ("addressesTemp.txt");
    originalTextFile.open(addressesFileName.c_str(), ios::in);
    temporaryTextFile.open("addressesTemp.txt", ios::out|ios::app);
    if (originalTextFile.good() == false) {
        cout << "Nie udalo sie otworzyc pliku z Kontaktami!";
        Sleep(2000);
        exit(0);
    }
    while (getline(originalTextFile,originalTextLine)) {
        contactID = checkIdFromStringLine(originalTextLine);
        if (contactID != _deletedContactID) {
            temporaryTextFile << originalTextLine << endl;
        }
    }
    originalTextFile.close();
    temporaryTextFile.close();
    temp.close();
    if (remove (addressesFileName.c_str()) != 0) {
        cout << "Blad przy zapisie!";
    }
    if (rename ("addressesTemp.txt", addressesFileName.c_str()) != 0) {
        cout << "Blad przy zapisie!";
    }
}

int deleteContact (vector <Contact> & _contacts) {
    int id;
    int vectorSize = _contacts.size();
    system("cls");
    cout << "Podaj ID kontaktu do usuniecia: ";
    while(!(cin >> id))
    {
        cout << "Podano niepoprawny nr ID!";
        cin.clear();
        cin.sync();
        Sleep(2000);
        return vectorSize;
    }
    char choice;
    while (true) {
        cout << "Na pewno chcesz usunac kontakt o numerze ID: " << id << "? (t/n) ";
        cin >> choice;
        if (choice == 'n') {
            return vectorSize;
        }
        if (choice == 't') {
            int position = -1;
            for (int i = 0; i < vectorSize; i++) {
                if (_contacts[i].id == id) {
                    position = i;
                    break;
                }
            }
            if (position == -1) {
                cout << "Nie ma takiego kontaktu!";
                Sleep(2000);
                return vectorSize;
            }
            _contacts.erase(_contacts.begin()+position);
            vectorSize = _contacts.size();
            loadDeletedVectorToFile(_contacts, id );
            return vectorSize;
        } else {
            cout << "Wybierz poprawna opcje!" << endl;
            continue;
        }
    }
}

void editContact (vector <Contact> & _contacts) {
    int id;
    system("cls");
    cout << "Podaj ID adresata do edycji: ";
    while(!(cin >> id))
    {
        cout << "Podano niepoprawny nr ID!";
        cin.clear();
        cin.sync();
        Sleep(2000);
        return;
    }
    int vectorSize = _contacts.size();
    int position = -1;
    for (int i = 0; i < vectorSize; i++) {
        if (_contacts[i].id == id) {
            position = i;
            break;
        }
    }
    if (position == -1) {
        cout << "Nie ma takiego kontaktu!";
        Sleep(2000);
        return;
    }
    cout << "Edytujesz ponizszy kontakt:" << endl;
    cout << "ID kontaktu: " << _contacts[position].id << endl;
    cout << "Imie: " << _contacts[position].name << endl;
    cout << "Nazwisko: " << _contacts[position].surname << endl;
    cout << "Numer telefonu: " << _contacts[position].phoneNumber << endl;
    cout << "Adres e-mail: " << _contacts[position].email << endl;
    cout << "Adres: " << _contacts[position].address << endl;
    cout << endl;
    cout << "Co chcesz edytowac?" << endl;

    cout << "1-imie" << endl;
    cout << "2-nazwisko" << endl;
    cout << "3-numer telefonu" << endl;
    cout << "4-email" << endl;
    cout << "5-adres" << endl;
    cout << "6-powrot do menu" << endl;

    int choice;
    cin >> choice;
    string newValue;
    switch (choice) {
    case 1:
        cout << "Nowe imie: ";
        cin.ignore();
        getline(cin,newValue);
        _contacts[position].name = newValue;
        loadEditedVectorToFile(_contacts, _contacts[position].id, position);
        cout << "Zapisano zmiany!";
        Sleep(1500);
        break;
    case 2:
        cout << "Nowe nazwisko: ";
        cin.ignore();
        getline(cin,newValue);
        _contacts[position].surname = newValue;
        loadEditedVectorToFile(_contacts, _contacts[position].id, position);
        cout << "Zapisano zmiany!";
        Sleep(1500);
        break;
    case 3:
        cout << "Nowy numer telefonu: ";
        cin.ignore();
        getline(cin,newValue);
        _contacts[position].phoneNumber = newValue;
        loadEditedVectorToFile(_contacts, _contacts[position].id, position);
        cout << "Zapisano zmiany!";
        Sleep(1500);
        break;
    case 4:
        cout << "Nowy email: ";
        cin.ignore();
        getline(cin,newValue);
        _contacts[position].email = newValue;
        loadEditedVectorToFile(_contacts, _contacts[position].id, position);
        cout << "Zapisano zmiany!";
        Sleep(1500);
        break;
    case 5:
        cout << "Nowy adres: ";
        cin.ignore();
        getline(cin,newValue);
        _contacts[position].address = newValue;
        loadEditedVectorToFile(_contacts, _contacts[position].id, position);
        cout << "Zapisano zmiany!";
        Sleep(1500);
        break;
    case 6:
        return;
    default:
        cout << "Nie ma takiej opcji!";
        Sleep(2000);
        return;
    }
}

int loadUsersTextFile (vector <User> & _users) {
    fstream textFile;
    string textLine;
    string idToConvert;
    textFile.open(usersFileName.c_str(), ios::in);
    if (textFile.good() == false) {
        ofstream temp (usersFileName.c_str());
        textFile.open(usersFileName.c_str(), ios::in);
        if (textFile.good() == false) {
            cout << "Nie udalo sie otworzyc pliku z Kontaktami!";
            Sleep(2000);
            exit(0);
        }
    }
    User temporaryUser;
    int usersNumber = 0;
    while (getline(textFile,textLine)) {
        idToConvert = explodeStringLine(1, textLine);
        temporaryUser.id = atoi(idToConvert.c_str());
        temporaryUser.name = explodeStringLine(2, textLine);
        temporaryUser.password = explodeStringLine(3, textLine);
        usersNumber++;
        _users.push_back(temporaryUser);
    }
    textFile.close();
    return usersNumber;
}

int logIn (vector <User> & users, int _usersNumber) {
    string name, password;
    cout << "Podaj nazwe uzytkownika: ";
    cin.ignore();
    getline(cin, name);
    int i = 0;
    while (i < _usersNumber) {
        if (users[i].name == name) {
            for (int attempt = 0; attempt < 3; attempt++) {
                cout << "Podaj haslo: ";
                getline(cin, password);
                if (users[i].password == password) {
                    cout << "Zalogowales sie" << endl;
                    Sleep (1000);
                    return users[i].id;
                }
            }
            cout << "Podales 3 razy bledne haslo. Sprobuj ponownie.";
                 Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma takiego uzytkownika!";
    Sleep(1500);
    return 0;
}

int signIn (vector <User> & _users, int _usersNumber) {
    User temporaryUser;
    string name;
    int i = 0;
    cin.ignore();
    cout << "Podaj nazwe uzytkownika: ";
    getline(cin, name);
    while (i < _usersNumber)
    {
        if (_users[i].name == name)
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            getline(cin, name);
            i = 0;
        }
        else i++;
    }
    temporaryUser.name = name;
    cout << "Podaj haslo: ";
    getline(cin, temporaryUser.password);
    if (_usersNumber == 0)
        temporaryUser.id = _usersNumber+1;
    else
        temporaryUser.id = (_users[_usersNumber-1].id+1);
    _users.push_back(temporaryUser);

    fstream textFile;
    textFile.open(usersFileName.c_str(), ios::out|ios::app);
    if (textFile.good() == false) {
        cout << "Nie udalo sie otworzyc pliku z Kontaktami!";
        Sleep(2000);
        exit(0);
    }
    textFile << _users[_usersNumber].id << "|";
    textFile << _users[_usersNumber].name << "|";
    textFile << _users[_usersNumber].password << "|" << endl;
    textFile.close();
    cout << "Uzytkownik dodany! ";
    cout << endl << "(wcisnij enter aby wrocic do menu glownego)";
    cin.sync();
    cin.get();
    return _usersNumber+1;
}

void changePassword (vector <User> & _users, int _usersNumber, int _loggedUserID) {
    string password;
    cout<<"Podaj nowe haslo: ";
    cin.ignore();
    getline(cin, password);
    for (int i = 0; i < _usersNumber; i++) {
        if (_users[i].id == _loggedUserID) {
            _users[i].password = password;
        }
    }
    fstream textFile;
    textFile.open(usersFileName.c_str(), ios::out);
    if (textFile.good() == false) {
        cout << "Nie udalo sie otworzyc pliku z Kontaktami!";
        Sleep(2000);
        exit(0);
    }
    for (int i = 0; i < _usersNumber; i++) {
        textFile << _users[i].id << "|";
        textFile << _users[i].name << "|";
        textFile << _users[i].password << "|" << endl;
    }
    textFile.close();
    cout << "Haslo zostalo zmienione! ";
    cout << endl << "(wcisnij enter aby wrocic do menu glownego)";
    cin.sync();
    cin.get();
}

int main() {
    char selection;
    vector <Contact> contacts;
    vector <User> users;
    int contactsNumber;
    int usersNumber = loadUsersTextFile(users);
    int loggedUserID = 0;

    while (true)
    {
        if (loggedUserID == 0) {
            system("cls");
            showMenuUnLogged();
            cin >> selection;
            if (selection == '1') {
                system("cls");
                loggedUserID = logIn(users, usersNumber);
            } else if (selection == '2') {
                system("cls");
                usersNumber = signIn(users, usersNumber);
            } else if (selection == '9') {
                exit(0);
            } else {
                cout << "Wybrano niepoprawna opcje! Sprobuj ponownie ";
                cin.sync();
                cin.get();
            }
        }

        else {
            contactsNumber = loadAddressesTextFile(contacts, loggedUserID);
            showMenuLogged();
            cin >> selection;

            if (selection == '1') {
                system("cls");
                contactsNumber = addNewContact(contactsNumber, contacts, loggedUserID);
            }

            else if (selection == '2') {
                system("cls");
                searchContactByName(contactsNumber, contacts);
            }

            else if (selection == '3') {
                system("cls");
                searchContactBySurname(contactsNumber, contacts);
            }

            else if (selection == '4') {
                system("cls");
                showContacts(contactsNumber, contacts);
            }

            else if (selection == '5') {
                system("cls");
                contactsNumber = deleteContact(contacts);
            }

            else if (selection == '6') {
                system("cls");
                editContact(contacts);
            }

            else if (selection == '7') {
                system("cls");
                changePassword(users, usersNumber, loggedUserID);
            }

            else if (selection == '8') {
                loggedUserID = 0;
            }

            else {
                cout << "Wybrano niepoprawna opcje! Sprobuj ponownie ";
                cin.sync();
                cin.get();
            }
        }
    }
    return 0;
}
