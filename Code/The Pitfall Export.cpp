// // // // // \\ \\ \\ \\ \\ \\ \\ POTRZEBNE BIBLIOTEKI 
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib") // DO DZWIEKU
using namespace std;
// // // // // \\ \\ \\ \\ \\ \\ \\ DEFINICJE KLAS
class Gracz {
public:
    int x;
    int y;
};

class Laser {
public:
    int x;
    int y;
    int x1;
    int y1;
    bool active = false;
};

class Pistolet {
public:
    int x;
    int y;
    int x1;
    int y1;
};

class Figer {
public:
    int x;
    int y;
};

class Checkpoint {
public:
    int x;
    int y;
};

class Zbierane {
public:
    int x;
    int y;
};

class Respawn {
public:
    int x;
    int y;
};

class Finish {
public:
    int x;
    int y;
};

class Switch {
public:
    int x;
    int y;
};
class Drzwi {
public:
    int x;
    int y;
};
class Box {
public:
    int x;
    int y;
};
class Chains {
public:
    int x;
    int y;
};

class Roll {
public:
    int x;
    int y;
    int x1;
    int x2;
    int x3;
    int x4;
    int y1;
    int y2;
    int y3;
    int y4;
};
class Teleport {
public:
    int x1;
    int y1;
    int x2;
    int y2;
};
// // // // // \\ \\ \\ \\ \\ \\ \\ DEKLARACJE KLAS
Pistolet pistoletdown[50];
Pistolet pistoletup[50];
Pistolet pistoletright[50];
Pistolet pistoletleft[50];
Laser laserdown[50];
Laser laserup[50];
Laser laserright[50];
Laser laserleft[50];
Figer figer[500];
Figer figerReverse[500];
Roll rollside[10];
Roll rollup[10];
Switch przycisk[5];
Respawn spawn;
Checkpoint checkpoint[3];
Gracz gracz;
Gracz boss;
Chains chain[25];
Zbierane heart[15];
Zbierane gwiazdy[3];
Zbierane zielonegwiazdy[25];
Zbierane klucze[9];
Zbierane kluczeinne[8];
Box boxdestroy[200];
Box box[200];
Drzwi drzwi[10];
Drzwi drzwiinne[10];
Finish finish;
Teleport teleport[20];
Finish finishi[6];
// // // // // \\ \\ \\ \\ \\ \\ \\  ZMIENNE
char c; // KLAWISZE, KTORE BEDZIE WYPISYWAL UZYTKOWNIK
string plansza, mainmenu[28][130]; // POZIOM TESTOWY y,x
int starslevel[4][5];
int starslevelzapis[4][5];
char player; // IKONA GRACZA
bool ok = false; // CZY GRACZ ZYJE
bool grazaczeta = false; // CZY GRA SIE ROZPOCZELA
bool utratazycia = false; // CZY GRACZ UTRACIL ZYCIE
bool zebraneZycie = false; // CZY GRACZ ZEBRAL ZYCIE
bool zebranaGwiazda = false; // CZY GRACZ ZEBRAL GWIAZDE
bool IsMusicOn = true; // CZY MUZYKA JEST WLACZONA
bool playing = false, playingmusic = false;
bool poczatek = true;
bool restart = false;
bool wyjscie = false;
bool enter = true;
bool zebranaZielonaGwiazda = false;
bool czyjesttutorial = true;
int zycia, respawn = -1, zebranegwiazdy = 0, x, y, liczbakluczy = 0, n = 0, m = 0, wybranapostac = 1, world = 0, level = 0, tutorial = 0, zapisX, zapisY, intersection = 0, kolorgracza = 1;// ZYCIA GRACZA, RESPAWN, ZEBRANE GWIAZDY ZE WSZYSTKICH POZIOMOW, ZAPISANE GWIAZDY, X,Y = KOORDYNATY, LICZBE ZEBRANYCH KLUCZY MAGNETYCZNYCH
bool unlocked[3];
bool unlockedlevels[4][4];
int seconds, ultrastars;
int wybuch[1000][1000];
int muzyka;


bool zapalony = false; // CZY FIGER JEST ZAPALONY
bool klucz = false; // CZY ZEBRANO ZWYKLY KLUCZ

// // // // // \\ \\ \\ \\ \\ \\ \\  NIEWAZNE
void Postac();
void restartlevel();
void deleteobjects();
void worldmenu();
void planszaLevel1_1();
void planszaLevel1_2();
void planszaLevel1_3();
void planszaLevel1_4();
void planszaLevel1_5();
void planszaLevel2_1();
void planszaLevel2_2();
void planszaLevel2_3();
void planszaLevel2_4();
void planszaLevel2_5();
void planszaLevel3_1();
void planszaLevel3_2();
void planszaLevel3_3();
void planszaLevel3_4();
void planszaLevel3_5();
void planszaLevel4_1();
void planszaLevel4_2();
void planszaLevel4_3();
void planszaLevel4_4();
void planszaLevel4_5();
void world1tutorial();
void world1tutorial2();
void world1level1();
void world1level3();
void world2level1();
void world2level4();
void menu();
void reset();
void shop();
void startmenu();
void world1menu();
void world2menu();
void world3menu();
void world4menu();
void worldmenu();
void nextlevel();
void restartlevel();
void dead();
void ThePitfall();
void poruszanie();
void planszaThePitfall1();
void planszaThePitfall2();
void planszaThePitfall3();
void planszaThePitfallBoss();
void worldThePitfall1();
void worldThePitfall2();
void worldThePitfall3();
void worldThePitfallBoss();
void world3level1();
void world3level3();
void world4level1();
void world4level3();
void informacjeinfo();
void start();
// // // // // \\ \\ \\ \\ \\ \\ \\  

void gotoxy(int x, int y) { // FUNKCJA ODPOWIADAJACA ZA KOORDYNATY (W SUMIE JEDNA Z WAZNEJSZYCH FUNKCJI, DZIEKI CZEMU TO WSZYSTKO DZIALA)
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

char getCursorChar()    /// Funkcja zwracajaca, gdzie jest konsolowy kursor
{
    char d = '\0';
    CONSOLE_SCREEN_BUFFER_INFO con;
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hcon != INVALID_HANDLE_VALUE &&
        GetConsoleScreenBufferInfo(hcon, &con))
    {
        DWORD read = 0;
        if (!ReadConsoleOutputCharacterA(hcon, &d, 1,
            con.dwCursorPosition, &read) || read != 1
            )
            d = '\0';
    }
    return d;
}

void setCursorInvisible(bool showFlag) { // Niewidzialnosc kursoru
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

char readChar(int x, int y)  // Odczytywanie znaku gdzie jest kursor
{
    gotoxy(x, y);
    char miejsce = getCursorChar();
    return miejsce;
}

void CreatePistoletDownEnemy(int liczba, int x, int y) { // Pistolet strzelajacy na dol
    pistoletdown[liczba].x = x;
    pistoletdown[liczba].y = y;
    pistoletdown[liczba].x1 = pistoletdown[liczba].x;
    pistoletdown[liczba].y1 = pistoletdown[liczba].y + 1;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    gotoxy(x, y);
    cout << "V";
}

void CreatePistoletUpEnemy(int liczba, int x, int y) { // Pistolet strzelajacy do gory
    pistoletup[liczba].x = x;
    pistoletup[liczba].y = y;
    pistoletup[liczba].x1 = pistoletup[liczba].x;
    pistoletup[liczba].y1 = pistoletup[liczba].y - 1;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    gotoxy(x, y);
    cout << "^";
}

void CreatePistoletRightEnemy(int liczba, int x, int y) { // Pistolet strzelajacy w prawo
    pistoletright[liczba].x = x;
    pistoletright[liczba].y = y;
    pistoletright[liczba].x1 = pistoletright[liczba].x + 1;
    pistoletright[liczba].y1 = pistoletright[liczba].y;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    gotoxy(x, y);
    cout << ">";
}

void CreatePistoletLeftEnemy(int liczba, int x, int y) { // Pistolet strzelajacy w lewo
    pistoletleft[liczba].x = x;
    pistoletleft[liczba].y = y;
    pistoletleft[liczba].x1 = pistoletleft[liczba].x - 1;
    pistoletleft[liczba].y1 = pistoletleft[liczba].y;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    gotoxy(x, y);
    cout << "<";
}

void CreateLaserDownEnemy(int liczba, int x, int y) { // Laser strzelajacy na dol
    laserdown[liczba].x = x;
    laserdown[liczba].y = y;
    laserdown[liczba].x1 = laserdown[liczba].x;
    laserdown[liczba].y1 = laserdown[liczba].y + 1;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    gotoxy(x, y);
    cout << "M";
}

void CreateLaserUpEnemy(int liczba, int x, int y) {  // Laser strzelajacy do gory
    laserup[liczba].x = x;
    laserup[liczba].y = y;
    laserup[liczba].x1 = laserup[liczba].x;
    laserup[liczba].y1 = laserup[liczba].y - 1;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    gotoxy(x, y);
    cout << "W";
}

void CreateLaserRightEnemy(int liczba, int x, int y) { // Laser strzelajacy w prawo
    laserright[liczba].x = x;
    laserright[liczba].y = y;
    laserright[liczba].x1 = laserright[liczba].x + 1;
    laserright[liczba].y1 = laserright[liczba].y;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    gotoxy(x, y);
    cout << "E";
}

void CreateLaserLeftEnemy(int liczba, int x, int y) { // Laser strzelajacy w lewo
    laserleft[liczba].x = x;
    laserleft[liczba].y = y;
    laserleft[liczba].x1 = laserleft[liczba].x - 1;
    laserleft[liczba].y1 = laserleft[liczba].y;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    gotoxy(x, y);
    cout << char(174);
}

void CreateFigerEnemy(int liczba, int x, int y) { // Tworzy figera (ogien, mroz)
    figer[liczba].x = x;
    figer[liczba].y = y;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    gotoxy(x, y);
    cout << char(254);
}

void CreateFigerEnemyReverse(int liczba, int x, int y) {
    figerReverse[liczba].x = x;
    figerReverse[liczba].y = y;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(x, y);
    cout << "&";
}

void CreateRollSideEnemy(int liczba, int x, int y) {
    rollside[liczba].x = x;
    rollside[liczba].y = y;

    rollside[liczba].x1 = x - 1;
    rollside[liczba].y1 = y - 1;

    rollside[liczba].x2 = x + 1;
    rollside[liczba].y2 = y - 1;

    rollside[liczba].x3 = x + 1;
    rollside[liczba].y3 = y + 1;

    rollside[liczba].x4 = x - 1;
    rollside[liczba].y4 = y + 1;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    gotoxy(x, y);
    cout << "Y";
}

void CreateRollUpEnemy(int liczba, int x, int y) {
    rollup[liczba].x = x;
    rollup[liczba].y = y;

    rollup[liczba].x1 = x;
    rollup[liczba].y1 = y - 1;

    rollup[liczba].x2 = x + 1;
    rollup[liczba].y2 = y;

    rollup[liczba].x3 = x;
    rollup[liczba].y3 = y + 1;

    rollup[liczba].x4 = x - 1;
    rollup[liczba].y4 = y;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    gotoxy(x, y);
    cout << "+";
}

void CreateHeart(int liczba, int x, int y) {
    heart[liczba].x = x;
    heart[liczba].y = y;
    gotoxy(x, y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    cout << "H";
}

void CreateStar(int i, int x, int y) {
    gwiazdy[i].x = x;
    gwiazdy[i].y = y;
    gotoxy(x, y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "*";
}

void CreateGreenStar(int i, int x, int y) {
    zielonegwiazdy[i].x = x;
    zielonegwiazdy[i].y = y;
    gotoxy(x, y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "*";
}

void CreateBoss(int x, int y) {
    boss.x = x;
    boss.y = y;
    gotoxy(x, y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << player;
}

void CreateChain(int i, int x, int y) {
    chain[i].x = x;
    chain[i].y = y;
    gotoxy(x, y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "+";
}

void CheckpointArea(int liczba, int x, int y) {
    checkpoint[liczba].x = x;
    checkpoint[liczba].y = y;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    gotoxy(x, y);
    cout << "C";
}

void FinishArea(int x, int y) {
    finish.x = x;
    finish.y = y;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
    gotoxy(x, y);
    cout << char(207);
}

void FakeFinishArea(int x, int y) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
    gotoxy(x, y);
    cout << char(207);
}

void CreateDoor(int i, int x, int y) {
    drzwi[i].x = x;
    drzwi[i].y = y;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    gotoxy(x, y);
    cout << "%";
}

void CreateDoorDifferent(int i, int x, int y) {
    drzwiinne[i].x = x;
    drzwiinne[i].y = y;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    gotoxy(x, y);
    cout << char(245);
}

void CreateKey(int i, int x, int y) {
    klucze[i].x = x;
    klucze[i].y = y;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    gotoxy(x, y);
    cout << char(140);
}

void CreateKeyDifferent(int i, int x, int y) {
    kluczeinne[i].x = x;
    kluczeinne[i].y = y;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    gotoxy(x, y);
    cout << char(254);
}

void CreateTeleport(int i, int x1, int y1, int x2, int y2) {
    teleport[i].x1 = x1;
    teleport[i].y1 = y1;
    gotoxy(x1, y1);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "T";
    teleport[i].x2 = x2;
    teleport[i].y2 = y2;
    gotoxy(x2, y2);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << "T";
}

void CreateBox(int i, int x, int y) {
    box[i].x = x;
    box[i].y = y;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    gotoxy(x, y);
    cout << "0";
}

void CreateBoxDestroy(int i, int x, int y) {
    boxdestroy[i].x = x;
    boxdestroy[i].y = y;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    gotoxy(x, y);
    cout << "Q";
}

void CreateSwitch(int liczba, int x, int y) {
    przycisk[liczba].x = x;
    przycisk[liczba].y = y;
    gotoxy(x, y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "X";
}

void CreateTheEnd(int liczba, int x, int y) {
    finishi[liczba].x = x;
    finishi[liczba].y = y;
}

void PudloDestroy() {
    for (int i = 0; i < 50; i++) {
        if (boxdestroy[i].x != 0 && boxdestroy[i].y != 0) {
            if (readChar(boxdestroy[i].x, boxdestroy[i].y) == ' ' || readChar(boxdestroy[i].x, boxdestroy[i].y) == 'Q') {
                gotoxy(boxdestroy[i].x, boxdestroy[i].y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                cout << "Q";
            }
            if ((gracz.x == boxdestroy[i].x && gracz.y == boxdestroy[i].y)) {
                if (c == 'a' || c == toupper('a')) {
                    boxdestroy[i].x -= 1;
                    if (readChar(boxdestroy[i].x - 1, boxdestroy[i].y) == 'B') {
                        gotoxy(boxdestroy[i].x, boxdestroy[i].y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                        cout << "Q";
                        gracz.x += 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else {
                        gotoxy(boxdestroy[i].x, boxdestroy[i].y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                        cout << "Q";
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                }
                else if (c == 'd' || c == toupper('d')) {
                    if (readChar(boxdestroy[i].x + 1, boxdestroy[i].y) == 'B') {
                        gotoxy(boxdestroy[i].x, boxdestroy[i].y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                        cout << "Q";
                        gracz.x -= 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else {
                        boxdestroy[i].x += 1;
                        gotoxy(boxdestroy[i].x, boxdestroy[i].y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                        cout << "Q";
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                }
                else if (c == 'w' || c == toupper('w')) {
                    if (readChar(boxdestroy[i].x, boxdestroy[i].y - 1) == 'B') {
                        gotoxy(boxdestroy[i].x, boxdestroy[i].y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                        cout << "Q";
                        gracz.y += 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else {
                        boxdestroy[i].y -= 1;
                        gotoxy(boxdestroy[i].x, boxdestroy[i].y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                        cout << "Q";
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                }

                else if (c == 's' || c == toupper('s')) {
                    if (readChar(boxdestroy[i].x, boxdestroy[i].y + 1) == 'B') {
                        gotoxy(boxdestroy[i].x, boxdestroy[i].y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                        cout << "Q";
                        gracz.y -= 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else {
                        boxdestroy[i].y += 1;
                        gotoxy(boxdestroy[i].x, boxdestroy[i].y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                        cout << "Q";
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                }
                for (int y = 0; y < 50; y++) {
                    if (boxdestroy[i].x == box[y].x && boxdestroy[i].y == box[y].y) {
                        box[y].x = 0;
                        box[y].y = 0;
                    }

                }
            }
        }
    }
}

void Pudlo() {
    for (int i = 0; i < 200; i++) {
        if (box[i].x != 0 && box[i].y != 0) {
            if (readChar(box[i].x, box[i].y) == ' ' || readChar(box[i].x, box[i].y) == '@') {
                gotoxy(box[i].x, box[i].y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
                cout << "0";
            }
            if (gracz.x == box[i].x && gracz.y == box[i].y) {
                if (c == 'a' || c == toupper('a')) {
                    box[i].x -= 1;
                    if (readChar(box[i].x, box[i].y) == '#' || readChar(box[i].x, box[i].y) == '0' || readChar(box[i].x, box[i].y) == 'Q' || readChar(box[i].x, box[i].y) == 'V' || readChar(box[i].x, box[i].y) == '%' || readChar(box[i].x, box[i].y) == '*' || readChar(box[i].x, box[i].y) == 'H' || readChar(box[i].x, box[i].y) == '>' || readChar(box[i].x, box[i].y) == '<' || readChar(box[i].x, box[i].y) == 'C' || readChar(box[i].x, box[i].y) == '&' || readChar(box[i].x, box[i].y) == char(245) || readChar(box[i].x, box[i].y) == char(174) || readChar(box[i].x, box[i].y) == 'M' || readChar(box[i].x, box[i].y) == 'W' || readChar(box[i].x, box[i].y) == 'E') {
                        box[i].x += 1;
                        gotoxy(box[i].x, box[i].y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
                        cout << "0";
                        gracz.x += 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else {
                        gotoxy(box[i].x, box[i].y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
                        cout << "0";

                    }
                }
                else if (c == 'd' || c == toupper('d')) {
                    box[i].x += 1;
                    if (readChar(box[i].x, box[i].y) == '#' || readChar(box[i].x, box[i].y) == '0' || readChar(box[i].x, box[i].y) == 'Q' || readChar(box[i].x, box[i].y) == 'V' || readChar(box[i].x, box[i].y) == '%' || readChar(box[i].x, box[i].y) == '*' || readChar(box[i].x, box[i].y) == 'H' || readChar(box[i].x, box[i].y) == '>' || readChar(box[i].x, box[i].y) == '<' || readChar(box[i].x, box[i].y) == 'C' || readChar(box[i].x, box[i].y) == '&' || readChar(box[i].x, box[i].y) == char(245) || readChar(box[i].x, box[i].y) == char(174) || readChar(box[i].x, box[i].y) == 'M' || readChar(box[i].x, box[i].y) == 'W' || readChar(box[i].x, box[i].y) == 'E') {
                        box[i].x -= 1;
                        gotoxy(box[i].x, box[i].y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
                        cout << "0";
                        gracz.x -= 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else {
                        gotoxy(box[i].x, box[i].y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
                        cout << "0";

                    }
                }
                else if (c == 'w' || c == toupper('w')) {
                    box[i].y -= 1;
                    if (readChar(box[i].x, box[i].y) == '#' || readChar(box[i].x, box[i].y) == '0' || readChar(box[i].x, box[i].y) == 'Q' || readChar(box[i].x, box[i].y) == 'V' || readChar(box[i].x, box[i].y) == '%' || readChar(box[i].x, box[i].y) == '*' || readChar(box[i].x, box[i].y) == 'H' || readChar(box[i].x, box[i].y) == '>' || readChar(box[i].x, box[i].y) == '<' || readChar(box[i].x, box[i].y) == 'C' || readChar(box[i].x, box[i].y) == '&' || readChar(box[i].x, box[i].y) == char(245) || readChar(box[i].x, box[i].y) == char(174) || readChar(box[i].x, box[i].y) == 'M' || readChar(box[i].x, box[i].y) == 'W' || readChar(box[i].x, box[i].y) == 'E') {
                        box[i].y += 1;
                        gotoxy(box[i].x, box[i].y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
                        cout << "0";
                        gracz.y += 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else {
                        gotoxy(box[i].x, box[i].y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
                        cout << "0";

                    }
                }
                else if (c == 's' || c == toupper('s')) {
                    box[i].y += 1;
                    if (readChar(box[i].x, box[i].y) == '#' || readChar(box[i].x, box[i].y) == '0' || readChar(box[i].x, box[i].y) == 'Q' || readChar(box[i].x, box[i].y) == 'V' || readChar(box[i].x, box[i].y) == '%' || readChar(box[i].x, box[i].y) == '*' || readChar(box[i].x, box[i].y) == 'H' || readChar(box[i].x, box[i].y) == '>' || readChar(box[i].x, box[i].y) == '<' || readChar(box[i].x, box[i].y) == 'C' || readChar(box[i].x, box[i].y) == '&' || readChar(box[i].x, box[i].y) == char(245) || readChar(box[i].x, box[i].y) == char(174) || readChar(box[i].x, box[i].y) == 'M' || readChar(box[i].x, box[i].y) == 'W' || readChar(box[i].x, box[i].y) == 'E') {
                        box[i].y -= 1;
                        gotoxy(box[i].x, box[i].y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
                        cout << "0";
                        gracz.y -= 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else {
                        gotoxy(box[i].x, box[i].y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
                        cout << "0";

                    }
                }
            }
        }
    }
}

void PistoletDownEnemy() {
    for (int i = 0; i < 50; i++) {
        if (pistoletdown[i].x != 0 && pistoletdown[i].y != 0) {
            if (readChar(pistoletdown[i].x1, pistoletdown[i].y1) == 'V') {
                pistoletdown[i].y1 = pistoletdown[i].y;
                gotoxy(pistoletdown[i].x, pistoletdown[i].y1);
            }
            else {
                if (readChar(pistoletdown[i].x1, pistoletdown[i].y1) == '#' || readChar(pistoletdown[i].x1, pistoletdown[i].y1) == 'M' || readChar(pistoletdown[i].x1, pistoletdown[i].y1) == '0' || readChar(pistoletdown[i].x1, pistoletdown[i].y1) == 'Q' || readChar(pistoletdown[i].x1, pistoletdown[i].y1) == 'W' || readChar(pistoletdown[i].x1, pistoletdown[i].y1) == 'E' || readChar(pistoletdown[i].x1, pistoletdown[i].y1) == char(174) || readChar(pistoletdown[i].x1, pistoletdown[i].y1) == '=' || readChar(pistoletdown[i].x1, pistoletdown[i].y1) == 'I' || readChar(pistoletdown[i].x1, pistoletdown[i].y1) == '^') {
                    gotoxy(pistoletdown[i].x1, pistoletdown[i].y1 - 1);
                    cout << " ";
                    gotoxy(pistoletdown[i].x, pistoletdown[i].y);
                    pistoletdown[i].y1 = pistoletdown[i].y + 1;
                }
                else {
                    gotoxy(pistoletdown[i].x1, pistoletdown[i].y1);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    cout << "|";
                    gotoxy(pistoletdown[i].x1, pistoletdown[i].y1 - 1);
                    cout << " ";
                    pistoletdown[i].y1 += 1;
                }
            }

            gotoxy(pistoletdown[i].x, pistoletdown[i].y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << "V";
            if (readChar(gracz.x, gracz.y) == readChar(pistoletdown[i].x1, pistoletdown[i].y1)) {
                utratazycia = true;
                break;
            }
        }
    }
}

void LaserDownEnemy() {
    for (int i = 0; i < 50; i++) {
        if (laserdown[i].x != 0 && laserdown[i].y != 0) {
            if (readChar(laserdown[i].x, laserdown[i].y) == ' ') {
                gotoxy(laserdown[i].x, laserdown[i].y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                cout << "M";
            }
            if (laserdown[i].active == true) {
                if (readChar(laserdown[i].x1, laserdown[i].y1) == '0' && readChar(laserdown[i].x1, laserdown[i].y1 + 1) == ' ' && readChar(laserdown[i].x1, laserdown[i].y1 + 2) == '=') {
                    laserdown[i].y1 = laserdown[i].y1 + 2;
                }
                else if (readChar(laserdown[i].x1, laserdown[i].y1) == '0' && readChar(laserdown[i].x1, laserdown[i].y1 + 1) == 'I') {

                }
                else if (readChar(laserdown[i].x1, laserdown[i].y1) == '0' && readChar(laserdown[i].x1, laserdown[i].y1 + 1) != 'I') {
                    gotoxy(laserdown[i].x, laserdown[i].y);
                    laserdown[i].y1 = laserdown[i].y + 1;
                    laserdown[i].active = false;
                }
                else {
                    if (readChar(laserdown[i].x1, laserdown[i].y1) == '#' || readChar(laserdown[i].x1, laserdown[i].y1) == 'M' || readChar(laserdown[i].x1, laserdown[i].y1) == 'E' || readChar(laserdown[i].x1, laserdown[i].y1) == 'R' || readChar(laserdown[i].x1, laserdown[i].y1) == 'W' || readChar(laserdown[i].x1, laserdown[i].y1) == '<' || readChar(laserdown[i].x1, laserdown[i].y1) == '>' || readChar(laserdown[i].x1, laserdown[i].y1) == '^' || readChar(laserdown[i].x1, laserdown[i].y1) == 'V' || readChar(laserdown[i].x1, laserdown[i].y1) == char(174)) {
                        gotoxy(laserdown[i].x, laserdown[i].y);
                        laserdown[i].y1 = laserdown[i].y + 1;
                        laserdown[i].active = false;
                    }
                    else {
                        gotoxy(laserdown[i].x1, laserdown[i].y1);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                        cout << " ";
                        gotoxy(laserdown[i].x1, laserdown[i].y1 - 1);
                        laserdown[i].y1 += 1;
                    }
                }
            }
            else {
                if (readChar(laserdown[i].x1, laserdown[i].y1) == '#' || readChar(laserdown[i].x1, laserdown[i].y1) == 'M' || readChar(laserdown[i].x1, laserdown[i].y1) == 'E' || readChar(laserdown[i].x1, laserdown[i].y1) == 'R' || readChar(laserdown[i].x1, laserdown[i].y1) == 'W' || readChar(laserdown[i].x1, laserdown[i].y1) == '<' || readChar(laserdown[i].x1, laserdown[i].y1) == '>' || readChar(laserdown[i].x1, laserdown[i].y1) == '^' || readChar(laserdown[i].x1, laserdown[i].y1) == 'V' || readChar(laserdown[i].x1, laserdown[i].y1) == char(174) || readChar(laserdown[i].x1, laserdown[i].y1) == '0') {
                    gotoxy(laserdown[i].x, laserdown[i].y);
                    laserdown[i].y1 = laserdown[i].y + 1;
                    laserdown[i].active = true;
                }
                else {
                    gotoxy(laserdown[i].x1, laserdown[i].y1);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    cout << "I";
                    gotoxy(laserdown[i].x1, laserdown[i].y1 - 1);
                    laserdown[i].y1 += 1;
                }
            }
            if (readChar(gracz.x, gracz.y) == readChar(laserdown[i].x1, laserdown[i].y1)) {
                utratazycia = true;
                break;
            }
        }
    }
}

void FigerEnemy() {
    for (int i = 0; i < 500; i++) {
        if (figer[i].x != 0 && figer[i].y != 0) {
            if (zapalony == false) {
                gotoxy(figer[i].x, figer[i].y);
                if (readChar(gracz.x, gracz.y) != readChar(figer[i].x, figer[i].y)) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    cout << char(254);
                }
            }
            else if (zapalony == true) {
                gotoxy(figer[i].x, figer[i].y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                cout << "&";
                if (readChar(gracz.x, gracz.y) == readChar(figer[i].x, figer[i].y)) {
                    utratazycia = true;
                    break;
                }
            }

        }
    }
}

void FigerEnemyReverse() {
    for (int i = 0; i < 500; i++) {
        if (figerReverse[i].x != 0 && figerReverse[i].y != 0) {
            if (zapalony == false) {
                gotoxy(figerReverse[i].x, figerReverse[i].y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                cout << "&";
                if (readChar(gracz.x, gracz.y) == readChar(figerReverse[i].x, figerReverse[i].y)) {
                    utratazycia = true;
                    break;
                }

            }
            else if (zapalony == true) {
                gotoxy(figerReverse[i].x, figerReverse[i].y);
                if (readChar(gracz.x, gracz.y) != readChar(figerReverse[i].x, figerReverse[i].y)) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    cout << char(254);
                }
            }
        }
    }
}

void Przycisk() {
    for (int z = 0; z < 5; z++) {
        if (przycisk[z].x != 0 && przycisk[z].y != 0) {
            gotoxy(przycisk[z].x, przycisk[z].y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            cout << "X";
            if (gracz.x == przycisk[z].x && gracz.y == przycisk[z].y) {
                if (c == 'a' || c == toupper('a')) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";
                    gracz.x += 1;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    cout << player;
                }
                else if (c == 'd' || c == toupper('d')) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";
                    gracz.x -= 1;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    cout << player;
                }
                else if (c == 'w' || c == toupper('w')) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";
                    gracz.y += 1;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    cout << player;
                }
                else if (c == 's' || c == toupper('s')) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";
                    gracz.y -= 1;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    cout << player;
                }

                if (zapalony == true) {
                    zapalony = false;

                }
                else {
                    zapalony = true;
                }
            }
        }
    }
}

void Check() {
    for (int z = 0; z < 3; z++) {
        if (checkpoint[z].x != 0 && checkpoint[z].y != 0) {
            if (readChar(checkpoint[z].x, checkpoint[z].y) == ' ') {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                gotoxy(checkpoint[z].x, checkpoint[z].y);
                cout << "C";
            }
            if (gracz.x == checkpoint[z].x && gracz.y == checkpoint[z].y) {
                respawn = z;
            }
        }
    }
}

void Fin() {
    if (finish.x != 0 && finish.y != 0) {
        if (readChar(finish.x, finish.y) == ' ') {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
            gotoxy(finish.x, finish.y);
            cout << char(207);
        }
        if (gracz.x == finish.x && gracz.y == finish.y) {
            playing = false;
            grazaczeta = false;
        }
    }
}

void FinI() {
    for (int i = 0; i < 6; i++) {
        if (finishi[i].x != 0 && finishi[i].y != 0) {
            if (gracz.x == finishi[i].x && gracz.y == finishi[i].y) {
                playing = false;
                grazaczeta = false;
            }
        }
    }
}

void HeartCollectible() {
    for (int z = 0; z < 15; z++) {
        if (heart[z].x != 0 && heart[z].y != 0) {
            if (readChar(heart[z].x, heart[z].y) == ' ') {
                gotoxy(heart[z].x, heart[z].y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
                cout << "H";
            }
            if (gracz.x == heart[z].x && gracz.y == heart[z].y) {
                zebraneZycie = true;
                heart[z].x = 0;
                heart[z].y = 0;
            }
        }
    }
}

void StarCollectible() {
    for (int z = 0; z < 5; z++) {
        if (gwiazdy[z].x != 0 && gwiazdy[z].y != 0) {
            if (readChar(gwiazdy[z].x, gwiazdy[z].y) == ' ') {
                gotoxy(gwiazdy[z].x, gwiazdy[z].y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                cout << "*";
            }
            if (gracz.x == gwiazdy[z].x && gracz.y == gwiazdy[z].y) {
                zebranaGwiazda = true;
                gwiazdy[z].x = 0;
                gwiazdy[z].y = 0;
            }
        }
    }
}

void GreenStarCollectible() {
    for (int z = 0; z < 25; z++) {
        if (zielonegwiazdy[z].x != 0 && zielonegwiazdy[z].y != 0) {
            if (readChar(zielonegwiazdy[z].x, zielonegwiazdy[z].y) == ' ') {
                gotoxy(zielonegwiazdy[z].x, zielonegwiazdy[z].y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << "*";
            }
            if (zebranaZielonaGwiazda != true) {
                if (gracz.x == zielonegwiazdy[z].x && gracz.y == zielonegwiazdy[z].y) {
                    zebranaZielonaGwiazda = true;
                    zielonegwiazdy[z].x = 0;
                    zielonegwiazdy[z].y = 0;
                }
            }
            else {
                gotoxy(zielonegwiazdy[z].x, zielonegwiazdy[z].y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << "*";
            }
        }
    }
}

void Boss() {
    if (readChar(boss.x, boss.y) == 'Q') {
        grazaczeta = false;
        playing = false;
    }
}

void ChainWall() {
    for (int z = 0; z < 25; z++) {
        if (chain[z].x != 0 && chain[z].y != 0) {
            if (ultrastars == 20) {
                gotoxy(chain[z].x, chain[z].y);
                cout << " ";
                chain[z].x = NULL;
                chain[z].y = NULL;
            }
        }
    }
}

void Gate() {
    for (int z = 0; z < 10; z++) {
        if (drzwi[z].x != 0 && drzwi[z].y != 0) {
            if (readChar(drzwi[z].x, drzwi[z].y) == 'Q') {
                drzwi[z].x = 0;
                drzwi[z].y = 0;
            }
            if (readChar(drzwi[z].x, drzwi[z].y) == ' ') {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
                gotoxy(drzwi[z].x, drzwi[z].y);
                cout << "%";
            }
            if (gracz.x == drzwi[z].x && gracz.y == drzwi[z].y) {
                if (klucz == true) {
                    drzwi[z].x = 0;
                    drzwi[z].y = 0;
                    klucz = false;
                    informacjeinfo();
                }
                else if (klucz == false) {
                    if (c == 'a' || c == toupper('a')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.x += 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else if (c == 'd' || c == toupper('d')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.x -= 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else if (c == 'w' || c == toupper('w')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.y += 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else if (c == 's' || c == toupper('s')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.y -= 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                }
            }
        }
    }
}

void GateDifferent() {
    for (int z = 0; z < 10; z++) {
        if (drzwiinne[z].x != 0 && drzwiinne[z].y != 0) {
            if (readChar(drzwiinne[z].x, drzwiinne[z].y) == 'Q') {
                drzwiinne[z].x = 0;
                drzwiinne[z].y = 0;
            }
            if (readChar(drzwiinne[z].x, drzwiinne[z].y) == ' ') {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                gotoxy(drzwiinne[z].x, drzwiinne[z].y);
                cout << char(245);
            }
            if (gracz.x == drzwiinne[z].x && gracz.y == drzwiinne[z].y) {
                if (liczbakluczy < 3) {
                    if (c == 'a' || c == toupper('a')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.x += 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else if (c == 'd' || c == toupper('d')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.x -= 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else if (c == 'w' || c == toupper('w')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.y += 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else if (c == 's' || c == toupper('s')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.y -= 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                }
                else if (liczbakluczy >= 3) {
                    drzwiinne[z].x = 0;
                    drzwiinne[z].y = 0;
                    liczbakluczy -= 3;
                    informacjeinfo();
                }
            }
        }
    }
}

void KeyDifferent() {
    for (int z = 0; z < 9; z++) {
        if (kluczeinne[z].x != 0 && kluczeinne[z].y != 0) {
            if (readChar(kluczeinne[z].x, kluczeinne[z].y) == ' ') {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                gotoxy(x, y);
                cout << char(254);
            }

            if (gracz.x == kluczeinne[z].x && gracz.y == kluczeinne[z].y) {
                liczbakluczy += 1;
                informacjeinfo();
                kluczeinne[z].x = 0;
                kluczeinne[z].y = 0;
            }
        }
    }
}

void Key() {
    for (int z = 0; z < 9; z++) {
        if (klucze[z].x != 0 && klucze[z].y != 0) {
            if (readChar(klucze[z].x, klucze[z].y) == ' ') {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                gotoxy(klucze[z].x, klucze[z].y);
                cout << char(140);
            }
            if (gracz.x == klucze[z].x && gracz.y == klucze[z].y) {
                if (klucz == false) {
                    klucz = true;
                    klucze[z].x = 0;
                    klucze[z].y = 0;
                    informacjeinfo();
                }
                else if (klucz == true) {
                    if (c == 'a' || c == toupper('a')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.x += 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else if (c == 'd' || c == toupper('d')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.x -= 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else if (c == 'w' || c == toupper('w')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.y += 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else if (c == 's' || c == toupper('s')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.y -= 1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                }
            }
        }
    }
}

void RollSideEnemy() {
    Sleep(50);
    for (int i = 0; i < 10; i++) {
        if (rollside[i].x != 0 && rollside[i].y != 0) {
            if (readChar(rollside[i].x1, rollside[i].y1) == 'Y') {
                rollside[i].y1 = rollside[i].y;
                rollside[i].x1 = rollside[i].x;
                gotoxy(rollside[i].x1, rollside[i].y1);
            }
            if (readChar(rollside[i].x2, rollside[i].y2) == 'Y') {
                rollside[i].y2 = rollside[i].y;
                rollside[i].x2 = rollside[i].x;
                gotoxy(rollside[i].x2, rollside[i].y2);
            }
            if (readChar(rollside[i].x3, rollside[i].y3) == 'Y') {
                rollside[i].y3 = rollside[i].y;
                rollside[i].x3 = rollside[i].x;
                gotoxy(rollside[i].x3, rollside[i].y3);
            }
            if (readChar(rollside[i].x4, rollside[i].y4) == 'Y') {
                rollside[i].y4 = rollside[i].y;
                rollside[i].x4 = rollside[i].x;
                gotoxy(rollside[i].x4, rollside[i].y4);
            }
            else {
                if (readChar(rollside[i].x1, rollside[i].y1) == '#' || readChar(rollside[i].x1, rollside[i].y1) == 'M' || readChar(rollside[i].x1, rollside[i].y1) == '0' || readChar(rollside[i].x1, rollside[i].y1) == 'Q' || readChar(rollside[i].x1, rollside[i].y1) == 'Y' || readChar(rollside[i].x1, rollside[i].y1) == 'X' || readChar(rollside[i].x1, rollside[i].y1) == 'V' || readChar(rollside[i].x1, rollside[i].y1) == '+' || readChar(rollside[i].x1, rollside[i].y1) == '=' || readChar(rollside[i].x1, rollside[i].y1) == 'I' || readChar(rollside[i].x1, rollside[i].y1) == '^') {
                    gotoxy(rollside[i].x1 + 1, rollside[i].y1 + 1);
                    cout << " ";
                    gotoxy(rollside[i].x, rollside[i].y);
                    rollside[i].x1 = rollside[i].x - 1;
                    rollside[i].y1 = rollside[i].y - 1;
                }
                else {
                    gotoxy(rollside[i].x1, rollside[i].y1);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    cout << "\\";
                    gotoxy(rollside[i].x1 + 1, rollside[i].y1 + 1);
                    cout << " ";
                    rollside[i].y1 -= 1;
                    rollside[i].x1 -= 1;
                }

                if (readChar(rollside[i].x2, rollside[i].y2) == '#' || readChar(rollside[i].x2, rollside[i].y2) == 'M' || readChar(rollside[i].x2, rollside[i].y2) == '0' || readChar(rollside[i].x2, rollside[i].y2) == 'Q' || readChar(rollside[i].x2, rollside[i].y2) == 'Y' || readChar(rollside[i].x2, rollside[i].y2) == 'X' || readChar(rollside[i].x2, rollside[i].y2) == 'V' || readChar(rollside[i].x2, rollside[i].y2) == '+' || readChar(rollside[i].x2, rollside[i].y2) == '=' || readChar(rollside[i].x2, rollside[i].y2) == 'I' || readChar(rollside[i].x2, rollside[i].y2) == '^') {
                    gotoxy(rollside[i].x2 - 1, rollside[i].y2 + 1);
                    cout << " ";
                    gotoxy(rollside[i].x, rollside[i].y);
                    rollside[i].x2 = rollside[i].x + 1;
                    rollside[i].y2 = rollside[i].y - 1;
                }
                else {
                    gotoxy(rollside[i].x2, rollside[i].y2);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    cout << "/";
                    gotoxy(rollside[i].x2 - 1, rollside[i].y2 + 1);
                    cout << " ";
                    rollside[i].y2 -= 1;
                    rollside[i].x2 += 1;
                }

                if (readChar(rollside[i].x3, rollside[i].y3) == '#' || readChar(rollside[i].x3, rollside[i].y3) == 'M' || readChar(rollside[i].x3, rollside[i].y3) == '0' || readChar(rollside[i].x3, rollside[i].y3) == 'Q' || readChar(rollside[i].x3, rollside[i].y3) == 'Y' || readChar(rollside[i].x3, rollside[i].y3) == 'X' || readChar(rollside[i].x3, rollside[i].y3) == 'V' || readChar(rollside[i].x3, rollside[i].y3) == '+' || readChar(rollside[i].x3, rollside[i].y3) == '=' || readChar(rollside[i].x3, rollside[i].y3) == 'I' || readChar(rollside[i].x3, rollside[i].y3) == '^') {
                    gotoxy(rollside[i].x3 - 1, rollside[i].y3 - 1);
                    cout << " ";
                    gotoxy(rollside[i].x, rollside[i].y);
                    rollside[i].x3 = rollside[i].x + 1;
                    rollside[i].y3 = rollside[i].y + 1;
                }
                else {
                    gotoxy(rollside[i].x3, rollside[i].y3);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    cout << "\\";
                    gotoxy(rollside[i].x3 - 1, rollside[i].y3 - 1);
                    cout << " ";
                    rollside[i].y3 += 1;
                    rollside[i].x3 += 1;
                }

                if (readChar(rollside[i].x4, rollside[i].y4) == '#' || readChar(rollside[i].x4, rollside[i].y4) == 'M' || readChar(rollside[i].x4, rollside[i].y4) == '0' || readChar(rollside[i].x4, rollside[i].y4) == 'Q' || readChar(rollside[i].x4, rollside[i].y4) == 'Y' || readChar(rollside[i].x4, rollside[i].y4) == 'X' || readChar(rollside[i].x4, rollside[i].y4) == 'V' || readChar(rollside[i].x4, rollside[i].y4) == '+' || readChar(rollside[i].x4, rollside[i].y4) == '=' || readChar(rollside[i].x4, rollside[i].y4) == 'I' || readChar(rollside[i].x4, rollside[i].y4) == '^') {
                    gotoxy(rollside[i].x4 + 1, rollside[i].y4 - 1);
                    cout << " ";
                    gotoxy(rollside[i].x, rollside[i].y);
                    rollside[i].x4 = rollside[i].x - 1;
                    rollside[i].y4 = rollside[i].y + 1;
                }
                else {
                    gotoxy(rollside[i].x4, rollside[i].y4);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    cout << "/";
                    gotoxy(rollside[i].x4 + 1, rollside[i].y4 - 1);
                    cout << " ";
                    rollside[i].y4 += 1;
                    rollside[i].x4 -= 1;
                }
            }
            gotoxy(rollside[i].x, rollside[i].y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
            cout << "Y";
            if (readChar(gracz.x, gracz.y) == readChar(rollside[i].x1, rollside[i].y1) || readChar(gracz.x, gracz.y) == readChar(rollside[i].x2, rollside[i].y2) || readChar(gracz.x, gracz.y) == readChar(rollside[i].x3, rollside[i].y3) || readChar(gracz.x, gracz.y) == readChar(rollside[i].x4, rollside[i].y4)) {
                utratazycia = true;
                break;
            }
        }
    }
}

void RollUpEnemy() {
    for (int i = 0; i < 10; i++) {
        if (rollup[i].x != 0 && rollup[i].y != 0) {
            if (readChar(rollup[i].x1, rollup[i].y1) == '+') {
                rollup[i].y1 = rollup[i].y;
                rollup[i].x1 = rollup[i].x;
                gotoxy(rollup[i].x1, rollup[i].y1);
            }
            if (readChar(rollup[i].x2, rollup[i].y2) == '+') {
                rollup[i].y2 = rollup[i].y;
                rollup[i].x2 = rollup[i].x;
                gotoxy(rollup[i].x2, rollup[i].y2);
            }
            if (readChar(rollup[i].x3, rollup[i].y3) == '+') {
                rollup[i].y3 = rollup[i].y;
                rollup[i].x3 = rollup[i].x;
                gotoxy(rollup[i].x3, rollup[i].y3);
            }
            if (readChar(rollup[i].x4, rollup[i].y4) == '+') {
                rollup[i].y4 = rollup[i].y;
                rollup[i].x4 = rollup[i].x;
                gotoxy(rollup[i].x4, rollup[i].y4);
            }
            else {
                if (readChar(rollup[i].x1, rollup[i].y1) == '#' || readChar(rollup[i].x1, rollup[i].y1) == 'M' || readChar(rollup[i].x1, rollup[i].y1) == '0' || readChar(rollup[i].x1, rollup[i].y1) == 'Q' || readChar(rollup[i].x1, rollup[i].y1) == 'Y' || readChar(rollup[i].x1, rollup[i].y1) == 'X' || readChar(rollup[i].x1, rollup[i].y1) == 'V' || readChar(rollup[i].x1, rollup[i].y1) == '+' || readChar(rollup[i].x1, rollup[i].y1) == '=' || readChar(rollup[i].x1, rollup[i].y1) == 'I') {
                    gotoxy(rollup[i].x1, rollup[i].y1 + 1);
                    cout << " ";
                    gotoxy(rollup[i].x, rollup[i].y);
                    rollup[i].x1 = rollup[i].x;
                    rollup[i].y1 = rollup[i].y - 1;
                }
                else {
                    gotoxy(rollup[i].x1, rollup[i].y1);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    cout << "|";
                    gotoxy(rollup[i].x1, rollup[i].y1 + 1);
                    cout << " ";
                    rollup[i].y1 -= 1;
                }

                if (readChar(rollup[i].x2, rollup[i].y2) == '#' || readChar(rollup[i].x2, rollup[i].y2) == 'M' || readChar(rollup[i].x2, rollup[i].y2) == '0' || readChar(rollup[i].x2, rollup[i].y2) == 'Q' || readChar(rollup[i].x2, rollup[i].y2) == 'Y' || readChar(rollup[i].x2, rollup[i].y2) == 'X' || readChar(rollup[i].x2, rollup[i].y2) == 'V' || readChar(rollup[i].x2, rollup[i].y2) == '+' || readChar(rollup[i].x2, rollup[i].y2) == '=' || readChar(rollup[i].x2, rollup[i].y2) == 'I') {
                    gotoxy(rollup[i].x2 - 1, rollup[i].y2);
                    cout << " ";
                    gotoxy(rollup[i].x, rollup[i].y);
                    rollup[i].x2 = rollup[i].x + 1;
                    rollup[i].y2 = rollup[i].y;
                }
                else {
                    gotoxy(rollup[i].x2, rollup[i].y2);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    cout << "-";
                    gotoxy(rollup[i].x2 - 1, rollup[i].y2);
                    cout << " ";
                    rollup[i].x2 += 1;
                }

                if (readChar(rollup[i].x3, rollup[i].y3) == '#' || readChar(rollup[i].x3, rollup[i].y3) == 'M' || readChar(rollup[i].x3, rollup[i].y3) == '0' || readChar(rollup[i].x3, rollup[i].y3) == 'Q' || readChar(rollup[i].x3, rollup[i].y3) == 'Y' || readChar(rollup[i].x3, rollup[i].y3) == 'X' || readChar(rollup[i].x3, rollup[i].y3) == 'V' || readChar(rollup[i].x3, rollup[i].y3) == '+' || readChar(rollup[i].x3, rollup[i].y3) == '=' || readChar(rollup[i].x3, rollup[i].y3) == 'I') {
                    gotoxy(rollup[i].x3, rollup[i].y3 - 1);
                    cout << " ";
                    gotoxy(rollup[i].x, rollup[i].y);
                    rollup[i].x3 = rollup[i].x;
                    rollup[i].y3 = rollup[i].y + 1;
                }
                else {
                    gotoxy(rollup[i].x3, rollup[i].y3);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    cout << "|";
                    gotoxy(rollup[i].x3, rollup[i].y3 - 1);
                    cout << " ";
                    rollup[i].y3 += 1;
                }

                if (readChar(rollup[i].x4, rollup[i].y4) == '#' || readChar(rollup[i].x4, rollup[i].y4) == 'M' || readChar(rollup[i].x4, rollup[i].y4) == '0' || readChar(rollup[i].x4, rollup[i].y4) == 'Q' || readChar(rollup[i].x4, rollup[i].y4) == 'Y' || readChar(rollup[i].x4, rollup[i].y4) == 'X' || readChar(rollup[i].x4, rollup[i].y4) == 'V' || readChar(rollup[i].x4, rollup[i].y4) == '+' || readChar(rollup[i].x4, rollup[i].y4) == '=' || readChar(rollup[i].x4, rollup[i].y4) == 'I') {
                    gotoxy(rollup[i].x4 + 1, rollup[i].y4);
                    cout << " ";
                    gotoxy(rollup[i].x, rollup[i].y);
                    rollup[i].x4 = rollup[i].x - 1;
                    rollup[i].y4 = rollup[i].y;
                }
                else {
                    gotoxy(rollup[i].x4, rollup[i].y4);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    cout << "-";
                    gotoxy(rollup[i].x4 + 1, rollup[i].y4);
                    cout << " ";
                    rollup[i].x4 -= 1;
                }
            }
            gotoxy(rollup[i].x, rollup[i].y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
            cout << "+";
            if (readChar(gracz.x, gracz.y) == readChar(rollup[i].x1, rollup[i].y1) || readChar(gracz.x, gracz.y) == readChar(rollup[i].x2, rollup[i].y2) || readChar(gracz.x, gracz.y) == readChar(rollup[i].x3, rollup[i].y3) || readChar(gracz.x, gracz.y) == readChar(rollup[i].x4, rollup[i].y4)) {
                utratazycia = true;
                break;
            }
        }
    }
}

void PistoletRightEnemy() {
    for (int i = 0; i < 50; i++) {
        if (pistoletright[i].x != 0 && pistoletright[i].y != 0) {
            if (readChar(pistoletright[i].x1, pistoletright[i].y1) == '>') {
                pistoletright[i].y1 = pistoletright[i].y;
                gotoxy(pistoletright[i].x, pistoletright[i].y1);
            }
            else {
                if (readChar(pistoletright[i].x1, pistoletright[i].y1) == '#' || readChar(pistoletright[i].x1, pistoletright[i].y1) == 'M' || readChar(pistoletright[i].x1, pistoletright[i].y1) == '0' || readChar(pistoletright[i].x1, pistoletright[i].y1) == 'Q' || readChar(pistoletright[i].x1, pistoletright[i].y1) == 'V' || readChar(pistoletright[i].x1, pistoletright[i].y1) == '<' || readChar(pistoletright[i].x1, pistoletright[i].y1) == '>' || readChar(pistoletright[i].x1, pistoletright[i].y1) == 'W' || readChar(pistoletright[i].x1, pistoletright[i].y1) == 'E' || readChar(pistoletright[i].x1, pistoletright[i].y1) == char(174) || readChar(pistoletright[i].x1, pistoletright[i].y1) == '=' || readChar(pistoletright[i].x1, pistoletright[i].y1) == 'I' || readChar(pistoletright[i].x1, pistoletright[i].y1) == char(245)) {
                    gotoxy(pistoletright[i].x1 - 1, pistoletright[i].y1);
                    cout << " ";
                    gotoxy(pistoletright[i].x, pistoletright[i].y);
                    pistoletright[i].x1 = pistoletright[i].x + 1;
                }
                else {
                    gotoxy(pistoletright[i].x1, pistoletright[i].y1);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    cout << "-";
                    gotoxy(pistoletright[i].x1 - 1, pistoletright[i].y1);
                    cout << " ";
                    pistoletright[i].x1 += 1;
                }
            }

            gotoxy(pistoletright[i].x, pistoletright[i].y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << ">";
            if (readChar(gracz.x, gracz.y) == readChar(pistoletright[i].x1, pistoletright[i].y1)) {
                utratazycia = true;
                break;
            }
        }
    }
}

void PistoletUpEnemy() {
    for (int i = 0; i < 50; i++) {
        if (pistoletup[i].x != 0 && pistoletup[i].y != 0) {
            if (readChar(pistoletup[i].x1, pistoletup[i].y1) == '^') {
                pistoletup[i].y1 = pistoletup[i].y;
                gotoxy(pistoletup[i].x, pistoletup[i].y1);
            }
            else {
                if (readChar(pistoletup[i].x1, pistoletup[i].y1) == '#' || readChar(pistoletup[i].x1, pistoletup[i].y1) == 'M' || readChar(pistoletup[i].x1, pistoletup[i].y1) == '0' || readChar(pistoletup[i].x1, pistoletup[i].y1) == 'Q' || readChar(pistoletup[i].x1, pistoletup[i].y1) == 'V' || readChar(pistoletup[i].x1, pistoletup[i].y1) == 'W' || readChar(pistoletup[i].x1, pistoletup[i].y1) == 'E' || readChar(pistoletup[i].x1, pistoletup[i].y1) == char(174) || readChar(pistoletup[i].x1, pistoletup[i].y1) == char(207) || readChar(pistoletup[i].x1, pistoletup[i].y1) == '=' || readChar(pistoletup[i].x1, pistoletup[i].y1) == 'I') {
                    gotoxy(pistoletup[i].x1, pistoletup[i].y1 + 1);
                    cout << " ";
                    gotoxy(pistoletup[i].x, pistoletup[i].y);
                    pistoletup[i].y1 = pistoletup[i].y - 1;
                }
                else {
                    gotoxy(pistoletup[i].x1, pistoletup[i].y1);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    cout << "|";
                    gotoxy(pistoletup[i].x1, pistoletup[i].y1 + 1);
                    cout << " ";
                    pistoletup[i].y1 -= 1;
                }
            }

            gotoxy(pistoletup[i].x, pistoletup[i].y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << "^";
            if (readChar(gracz.x, gracz.y) == readChar(pistoletup[i].x1, pistoletup[i].y1)) {
                utratazycia = true;
                break;
            }
        }
    }
}

void PistoletLeftEnemy() {
    for (int i = 0; i < 50; i++) {
        if (pistoletleft[i].x != 0 && pistoletleft[i].y != 0) {
            if (readChar(pistoletleft[i].x1, pistoletleft[i].y1) == '<') {
                pistoletleft[i].y1 = pistoletleft[i].y;
                gotoxy(pistoletleft[i].x, pistoletleft[i].y1);
            }
            else {
                if (readChar(pistoletleft[i].x1, pistoletleft[i].y1) == '#' || readChar(pistoletleft[i].x1, pistoletleft[i].y1) == 'M' || readChar(pistoletleft[i].x1, pistoletleft[i].y1) == '0' || readChar(pistoletleft[i].x1, pistoletleft[i].y1) == 'Q' || readChar(pistoletleft[i].x1, pistoletleft[i].y1) == 'V' || readChar(pistoletleft[i].x1, pistoletleft[i].y1) == '<' || readChar(pistoletleft[i].x1, pistoletleft[i].y1) == '>' || readChar(pistoletleft[i].x1, pistoletleft[i].y1) == 'W' || readChar(pistoletleft[i].x1, pistoletleft[i].y1) == 'E' || readChar(pistoletleft[i].x1, pistoletleft[i].y1) == char(174) || readChar(pistoletleft[i].x1, pistoletleft[i].y1) == '=' || readChar(pistoletleft[i].x1, pistoletleft[i].y1) == 'I' || readChar(pistoletleft[i].x1, pistoletleft[i].y1) == char(245)) {
                    gotoxy(pistoletleft[i].x1 + 1, pistoletleft[i].y1);
                    cout << " ";
                    gotoxy(pistoletleft[i].x, pistoletleft[i].y);
                    pistoletleft[i].x1 = pistoletleft[i].x - 1;
                }
                else {
                    gotoxy(pistoletleft[i].x1, pistoletleft[i].y1);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    cout << "-";
                    gotoxy(pistoletleft[i].x1 + 1, pistoletleft[i].y1);
                    cout << " ";
                    pistoletleft[i].x1 -= 1;
                }
            }

            gotoxy(pistoletleft[i].x, pistoletleft[i].y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << "<";
            if (readChar(gracz.x, gracz.y) == readChar(pistoletleft[i].x1, pistoletleft[i].y1)) {
                utratazycia = true;
                break;
            }
        }
    }
}

void LaserRightEnemy() {
    for (int i = 0; i < 50; i++) {
        if (laserright[i].x != 0 && laserright[i].y != 0) {
            if (readChar(laserright[i].x, laserright[i].y) == ' ') {
                gotoxy(laserright[i].x, laserright[i].y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                cout << "E";
            }
            if (laserright[i].active == true) {
                if (readChar(laserright[i].x1, laserright[i].y1) == '0' && readChar(laserright[i].x1 + 1, laserright[i].y1) == ' ' && readChar(laserright[i].x1 + 2, laserright[i].y1) == '=') {
                    laserright[i].x1 = laserright[i].x1 + 2;
                }
                else if (readChar(laserright[i].x1, laserright[i].y1) == '0' && readChar(laserright[i].x1 + 1, laserright[i].y1) == 'I' || readChar(laserright[i].x1, laserright[i].y1) == '0' && readChar(laserright[i].x1 + 1, laserright[i].y1) == '=') {
                    laserright[i].x1 = laserright[i].x1 + 1;
                }
                else if (readChar(laserright[i].x1, laserright[i].y1) == '0' && readChar(laserright[i].x1 + 1, laserright[i].y1) != 'I') {
                    gotoxy(laserright[i].x, laserright[i].y);
                    laserright[i].x1 = laserright[i].x + 1;
                    laserright[i].active = false;
                }
                else {
                    if (readChar(laserright[i].x1, laserright[i].y1) == '#' || readChar(laserright[i].x1, laserright[i].y1) == 'M' || readChar(laserright[i].x1, laserright[i].y1) == 'E' || readChar(laserright[i].x1, laserright[i].y1) == 'R' || readChar(laserright[i].x1, laserright[i].y1) == 'W' || readChar(laserright[i].x1, laserright[i].y1) == '<' || readChar(laserright[i].x1, laserright[i].y1) == '>' || readChar(laserright[i].x1, laserright[i].y1) == '^' || readChar(laserright[i].x1, laserright[i].y1) == 'V' || readChar(laserright[i].x1, laserright[i].y1) == char(174) || readChar(laserright[i].x1, laserright[i].y1) == 'Y') {
                        gotoxy(laserright[i].x, laserright[i].y);
                        laserright[i].x1 = laserright[i].x + 1;
                        laserright[i].active = false;
                    }
                    else {
                        gotoxy(laserright[i].x1, laserright[i].y1);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                        cout << " ";
                        gotoxy(laserright[i].x1 - 1, laserright[i].y1);
                        laserright[i].x1 += 1;
                    }
                }
            }
            else {
                if (readChar(laserright[i].x1, laserright[i].y1) == '#' || readChar(laserright[i].x1, laserright[i].y1) == '0' || readChar(laserright[i].x1, laserright[i].y1) == 'M' || readChar(laserright[i].x1, laserright[i].y1) == 'E' || readChar(laserright[i].x1, laserright[i].y1) == 'R' || readChar(laserright[i].x1, laserright[i].y1) == 'W' || readChar(laserright[i].x1, laserright[i].y1) == '<' || readChar(laserright[i].x1, laserright[i].y1) == '>' || readChar(laserright[i].x1, laserright[i].y1) == '^' || readChar(laserright[i].x1, laserright[i].y1) == 'V' || readChar(laserright[i].x1, laserright[i].y1) == char(174) || readChar(laserright[i].x1, laserright[i].y1) == 'Y') {
                    gotoxy(laserright[i].x, laserright[i].y);
                    laserright[i].x1 = laserright[i].x + 1;
                    laserright[i].active = true;
                }
                else {
                    gotoxy(laserright[i].x1, laserright[i].y1);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    cout << "=";
                    gotoxy(laserright[i].x1 - 1, laserright[i].y1);
                    laserright[i].x1 += 1;
                }
            }
            if (readChar(gracz.x, gracz.y) == readChar(laserright[i].x1, laserright[i].y1)) {
                utratazycia = true;
                break;
            }
        }
    }
}

void LaserUpEnemy() {
    for (int i = 0; i < 50; i++) {
        if (laserup[i].x != 0 && laserup[i].y != 0) {
            if (readChar(laserup[i].x, laserup[i].y) == ' ') {
                gotoxy(laserup[i].x, laserup[i].y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                cout << "W";
            }
            if (laserup[i].active == true) {
                if (readChar(laserup[i].x1, laserup[i].y1) == '0' && readChar(laserup[i].x1, laserup[i].y1 - 1) == ' ' && readChar(laserup[i].x1, laserup[i].y1 - 2) == '=') {
                    laserup[i].y1 = laserup[i].y1 - 2;
                }
                else if (readChar(laserup[i].x1, laserup[i].y1) == '0' && readChar(laserup[i].x1, laserup[i].y1 - 1) == 'I') {

                }
                else if (readChar(laserup[i].x1, laserup[i].y1) == '0' && readChar(laserup[i].x1, laserup[i].y1 - 1) != 'I') {
                    gotoxy(laserup[i].x, laserup[i].y);
                    laserup[i].y1 = laserup[i].y - 1;
                    laserup[i].active = false;
                }
                else {
                    if (readChar(laserup[i].x1, laserup[i].y1) == '#' || readChar(laserup[i].x1, laserup[i].y1) == 'M' || readChar(laserup[i].x1, laserup[i].y1) == 'E' || readChar(laserup[i].x1, laserup[i].y1) == 'R' || readChar(laserup[i].x1, laserup[i].y1) == 'W' || readChar(laserup[i].x1, laserup[i].y1) == '<' || readChar(laserup[i].x1, laserup[i].y1) == '>' || readChar(laserup[i].x1, laserup[i].y1) == '^' || readChar(laserup[i].x1, laserup[i].y1) == 'V' || readChar(laserup[i].x1, laserup[i].y1) == char(174)) {
                        gotoxy(laserup[i].x, laserup[i].y);
                        laserup[i].y1 = laserup[i].y - 1;
                        laserup[i].active = false;
                    }
                    else {
                        gotoxy(laserup[i].x1, laserup[i].y1);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                        cout << " ";
                        gotoxy(laserup[i].x1, laserup[i].y1 + 1);
                        laserup[i].y1 -= 1;
                    }
                }
            }
            else {
                if (readChar(laserup[i].x1, laserup[i].y1) == '#' || readChar(laserup[i].x1, laserup[i].y1) == '0' || readChar(laserup[i].x1, laserup[i].y1) == 'M' || readChar(laserup[i].x1, laserup[i].y1) == 'E' || readChar(laserup[i].x1, laserup[i].y1) == 'R' || readChar(laserup[i].x1, laserup[i].y1) == 'W' || readChar(laserup[i].x1, laserup[i].y1) == '<' || readChar(laserup[i].x1, laserup[i].y1) == '>' || readChar(laserup[i].x1, laserup[i].y1) == '^' || readChar(laserup[i].x1, laserup[i].y1) == 'V' || readChar(laserup[i].x1, laserup[i].y1) == char(174)) {
                    gotoxy(laserup[i].x, laserup[i].y);
                    laserup[i].y1 = laserup[i].y - 1;
                    laserup[i].active = true;
                }
                else {
                    gotoxy(laserup[i].x1, laserup[i].y1);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    cout << "I";
                    gotoxy(laserup[i].x1, laserup[i].y1 + 1);
                    laserup[i].y1 -= 1;
                }
            }
            if (readChar(gracz.x, gracz.y) == readChar(laserup[i].x1, laserup[i].y1)) {
                utratazycia = true;
                break;
            }
        }
    }
}

void LaserLeftEnemy() {
    for (int i = 0; i < 50; i++) {
        if (laserleft[i].x != 0 && laserleft[i].y != 0) {
            if (readChar(laserleft[i].x, laserleft[i].y) == ' ') {
                gotoxy(laserleft[i].x, laserleft[i].y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                cout << char(174);
            }
            if (laserleft[i].active == true) {
                if (readChar(laserleft[i].x1, laserleft[i].y1) == '0' && readChar(laserleft[i].x1 - 1, laserleft[i].y1) == 'I' && readChar(laserleft[i].x1 - 2, laserleft[i].y1) == '=') {
                    laserleft[i].x1 = laserleft[i].x1 - 2;
                }
                else if (readChar(laserleft[i].x1, laserleft[i].y1) == '0' && readChar(laserleft[i].x1 - 1, laserleft[i].y1) == 'I' || readChar(laserleft[i].x1, laserleft[i].y1) == '0' && readChar(laserleft[i].x1 - 1, laserleft[i].y1) == '=') {
                    laserleft[i].x1 = laserleft[i].x1 - 1;
                }
                else if (readChar(laserleft[i].x1, laserleft[i].y1) == '0' && readChar(laserleft[i].x1 - 1, laserleft[i].y1) != 'I') {
                    gotoxy(laserleft[i].x, laserleft[i].y);
                    laserleft[i].x1 = laserleft[i].x - 1;
                    laserleft[i].active = false;
                }
                else {
                    if (readChar(laserleft[i].x1, laserleft[i].y1) == '#' || readChar(laserleft[i].x1, laserleft[i].y1) == 'M' || readChar(laserleft[i].x1, laserleft[i].y1) == 'E' || readChar(laserleft[i].x1, laserleft[i].y1) == 'R' || readChar(laserleft[i].x1, laserleft[i].y1) == 'W' || readChar(laserleft[i].x1, laserleft[i].y1) == '<' || readChar(laserleft[i].x1, laserleft[i].y1) == '>' || readChar(laserleft[i].x1, laserleft[i].y1) == '^' || readChar(laserleft[i].x1, laserleft[i].y1) == 'V' || readChar(laserleft[i].x1, laserleft[i].y1) == char(174)) {
                        gotoxy(laserleft[i].x, laserleft[i].y);
                        laserleft[i].x1 = laserleft[i].x - 1;
                        laserleft[i].active = false;
                    }
                    else {
                        gotoxy(laserleft[i].x1, laserleft[i].y1);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                        cout << " ";
                        gotoxy(laserleft[i].x1 + 1, laserleft[i].y1);
                        laserleft[i].x1 -= 1;
                    }
                }
            }
            else {
                if (readChar(laserleft[i].x1, laserleft[i].y1) == '#' || readChar(laserleft[i].x1, laserleft[i].y1) == '0' || readChar(laserleft[i].x1, laserleft[i].y1) == 'M' || readChar(laserleft[i].x1, laserleft[i].y1) == 'E' || readChar(laserleft[i].x1, laserleft[i].y1) == 'R' || readChar(laserleft[i].x1, laserleft[i].y1) == 'W' || readChar(laserleft[i].x1, laserleft[i].y1) == '<' || readChar(laserleft[i].x1, laserleft[i].y1) == '>' || readChar(laserleft[i].x1, laserleft[i].y1) == '^' || readChar(laserleft[i].x1, laserleft[i].y1) == 'V' || readChar(laserleft[i].x1, laserleft[i].y1) == char(174)) {
                    gotoxy(laserleft[i].x, laserleft[i].y);
                    laserleft[i].x1 = laserleft[i].x - 1;
                    laserleft[i].active = true;
                }
                else {
                    gotoxy(laserleft[i].x1, laserleft[i].y1);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    cout << "=";
                    gotoxy(laserleft[i].x1, laserleft[i].y1 - 1);
                    laserleft[i].x1 -= 1;
                }
            }
            if (readChar(gracz.x, gracz.y) == readChar(laserleft[i].x1, laserleft[i].y1)) {
                utratazycia = true;
                break;
            }
        }
    }
}

void TeleportEntity() {
    for (int z = 0; z < 20; z++) {
        if (teleport[z].x1 != 0 && teleport[z].y1 != 0) {
            if (teleport[z].x2 != 0 && teleport[z].y2 != 0) {
                if (readChar(gracz.x, gracz.y) != readChar(teleport[z].x1, teleport[z].y1)) {
                    gotoxy(teleport[z].x1, teleport[z].y1);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                    cout << "T";
                }
                if (readChar(gracz.x, gracz.y) != readChar(teleport[z].x2, teleport[z].y2)) {
                    gotoxy(teleport[z].x2, teleport[z].y2);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    cout << "T";
                }
                if (gracz.x == teleport[z].x1 && gracz.y == teleport[z].y1) {
                    if (c == 'a' || c == toupper('a')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.x = teleport[z].x2;
                        gracz.y = teleport[z].y2;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else if (c == 'd' || c == toupper('d')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.x = teleport[z].x2;
                        gracz.y = teleport[z].y2;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else if (c == 'w' || c == toupper('w')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.x = teleport[z].x2;
                        gracz.y = teleport[z].y2;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else if (c == 's' || c == toupper('s')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.x = teleport[z].x2;
                        gracz.y = teleport[z].y2;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }

                }
                else if (gracz.x == teleport[z].x2 && gracz.y == teleport[z].y2) {
                    if (c == 'a' || c == toupper('a')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.x = teleport[z].x1;
                        gracz.y = teleport[z].y1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else if (c == 'd' || c == toupper('d')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.x = teleport[z].x1;
                        gracz.y = teleport[z].y1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else if (c == 'w' || c == toupper('w')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.x = teleport[z].x1;
                        gracz.y = teleport[z].y1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    else if (c == 's' || c == toupper('s')) {
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        gracz.x = teleport[z].x1;
                        gracz.y = teleport[z].y1;
                        gotoxy(gracz.x, gracz.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                        cout << player;
                    }
                    break;
                }
            }
        }
    }
}

// // // // // \\ \\ \\ \\ \\ \\ \\  

void LoadLevel() {
    if (world == 1) {
        if (level == 1) {
            planszaLevel1_1();
        }
        else if (level == 2) {
            planszaLevel1_2();
        }
        else if (level == 3) {
            planszaLevel1_3();
        }
        else if (level == 4) {
            planszaLevel1_4();
        }
        else if (level == 5) {
            planszaLevel1_5();
        }
    }
    if (world == 2) {
        if (level == 1) {
            planszaLevel2_1();
        }
        else if (level == 2) {
            planszaLevel2_2();
        }
        else if (level == 3) {
            planszaLevel2_3();
        }
        else if (level == 4) {
            planszaLevel2_4();
        }
        else if (level == 5) {
            planszaLevel2_5();
        }
    }
    if (world == 3) {
        if (level == 1) {
            planszaLevel3_1();
        }
        else if (level == 2) {
            planszaLevel3_2();
        }
        else if (level == 3) {
            planszaLevel3_3();
        }
        else if (level == 4) {
            planszaLevel3_4();
        }
        else if (level == 5) {
            planszaLevel3_5();
        }
    }
    if (world == 4) {
        if (level == 1) {
            planszaLevel4_1();
        }
        else if (level == 2) {
            planszaLevel4_2();
        }
        else if (level == 3) {
            planszaLevel4_3();
        }
        else if (level == 4) {
            planszaLevel4_4();
        }
        else if (level == 5) {
            planszaLevel4_5();
        }
    }
    if (world == 5) {
        if (intersection == 1) {
            planszaThePitfall1();
        }
        else if (intersection == 2) {
            planszaThePitfall2();
        }
        else if (intersection == 3) {
            planszaThePitfall3();
        }
        else if (intersection == 4) {
            planszaThePitfallBoss();
        }
    }
}

void LoadLevelTutorial() {
    if (tutorial == 1) {
        restart = false;
        world1level1();
    }
    else if (tutorial == 2) {
        world1level3();
        restart = false;
    }
    else if (tutorial == 3) {
        world2level1();
        restart = false;
    }
    else if (tutorial == 4) {
        world2level4();
        restart = false;
    }
    else if (tutorial == 5) {
        world3level1();
        restart = false;
    }
    else if (tutorial == 6) {
        world3level3();
        restart = false;
    }
    else if (tutorial == 7) {
        world4level1();
        restart = false;
    }
    else if (tutorial == 8) {
        world4level3();
        restart = false;
    }
}

void PauseMenu() {
    zapisX = gracz.x;
    zapisY = gracz.y;

    system("CLS");
    if (world == 1) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    }
    else if (world == 2) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    }
    else if (world == 3) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    }
    else if (world == 4) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    }
    else if (world == 5) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    }

    ifstream pause("interface/PAUSE.txt");
    if (pause.is_open()) {
        while (getline(pause, plansza)) {
            cout << plansza << endl;
        }
    }
    pause.close();

    grazaczeta = true;
    playing = false;
    gracz.x = 53;
    gracz.y = 12;

    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    n = 0;
    while (playing == false && world != 0) {
        char d = _getch();
        if (d == 'w' || d == toupper('w')) {
            if (n <= 0) {
                if (readChar(gracz.x, gracz.y) == player) {

                }
                else {
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                }

            }
            else {
                gotoxy(gracz.x, gracz.y);
                cout << " ";
                gracz.y -= 2;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n -= 1;
            }
        }
        else if (d == 's' || d == toupper('s')) {
            if (n >= 2) {
                if (readChar(gracz.x, gracz.y) == player) {
                    gotoxy(gracz.x - 1, gracz.y);
                    cout << " ";
                }
                else {
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                }
            }
            else {
                gotoxy(gracz.x, gracz.y);
                cout << " ";
                gracz.y += 2;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n += 1;
            }
        }
        else if (d == ' ') {
            if (n == 0) {
                d = 'h';
                deleteobjects();
                seconds = 0;
                ultrastars = 0;
                restartlevel();
                playing = true;
            }
            else if (n == 1) {
                d = 'h';
                system("cls");
                LoadLevel();
                gracz.x = zapisX;
                gracz.y = zapisY;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                cout << player;
                playing = true;
            }
            else if (n == 2) {
                d = 'h';
                czyjesttutorial = true;
                grazaczeta = false;
                ultrastars = 0;
                seconds = 0;
                deleteobjects();
                worldmenu();
            }

        }

    }
}

void MusicBox() {
    if (IsMusicOn == true) {
        if (world == 0) {
            PlaySound(TEXT("Imprisoned.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        }
        else if (world == 1) {
            if (playing == false) {
                PlaySound(TEXT("Panic.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                playing = true;
            }

        }
        else if (world == 2) {
            if (playing == false) {
                PlaySound(TEXT("Tear Apart.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                playing = true;
            }

        }
        else if (world == 3) {
            if (playing == false) {
                PlaySound(TEXT("A Way Out.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                playing = true;
            }


        }
        else if (world == 4) {
            if (level == 5) {
                if (playing == false) {
                    PlaySound(TEXT("ESCAPE! (bit).wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                    playing = true;
                }

            }
            else {
                if (playing == false) {
                    PlaySound(TEXT("ESCAPE!.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                    playing = true;
                }

            }
        }
        else if (world == 5) {
            if (intersection > 0 && intersection <= 3) {
                if (playing == false) {
                    PlaySound(TEXT("At Long Last.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                    playing = true;
                }
            }
            else if (intersection == 4) {
                PlaySound(TEXT("FIGHT!.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                playing = true;
            }
            else {
                if (playing == false) {
                    PlaySound(TEXT("The Pitfall.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                    playing = true;
                }
            }

        }
    }
}

void MusicBoxTutorial() {
    if (IsMusicOn == true) {
        PlaySound(TEXT("Confusion.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }
}

void informacje1() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(35, 30);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(65, 30);
    cout << "STARS: " << starslevelzapis[world - 1][level - 1] << " / 3";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
}

void informacje1_1() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(45, 20);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(68, 20);
    cout << "STARS: " << starslevelzapis[world - 1][level - 1] << " / 3";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
}

void informacje1_2() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(50, 57);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(75, 57);
    cout << "STARS: " << starslevelzapis[world - 1][level - 1] << " / 3";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
}

void informacje2() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(28, 35);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(53, 35);
    cout << "STARS: " << starslevelzapis[world - 1][level - 1] << " / 3";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
}

void informacje2_1() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(30, 32);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(55, 32);
    cout << "STARS: " << starslevelzapis[world - 1][level - 1] << " / 3";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
}

void informacje2_2() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(54, 31);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(79, 31);
    cout << "STARS: " << starslevelzapis[world - 1][level - 1] << " / 3";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
}

void informacje2_3() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(35, 28);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(60, 28);
    cout << "STARS: " << starslevelzapis[world - 1][level - 1] << " / 3";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(35, 30);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "KEY: " << klucz;
}

void informacje2_4() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(40, 34);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(65, 34);
    cout << "STARS: " << starslevelzapis[world - 1][level - 1] << " / 3";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(40, 36);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "KEY: " << klucz;
}

void informacje3() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(40, 25);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(65, 25);
    cout << "STARS: " << starslevelzapis[world - 1][level - 1] << " / 3";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(40, 27);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "KEY: " << klucz;
}

void informacje3_1() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(40, 34);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(65, 34);
    cout << "STARS: " << starslevelzapis[world - 1][level - 1] << " / 3";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(40, 36);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "KEY: " << klucz;
}

void informacje3_2() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(40, 34);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(65, 34);
    cout << "STARS: " << starslevelzapis[world - 1][level - 1] << " / 3";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(40, 36);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "KEY: " << klucz;
    gotoxy(65, 36);
    cout << "MAGNETIC KEYS: " << liczbakluczy;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
}

void informacje3_3() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(40, 34);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(65, 34);
    cout << "STARS: " << starslevelzapis[world - 1][level - 1] << " / 3";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(40, 36);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "KEY: " << klucz;
    gotoxy(65, 36);
    cout << "MAGNETIC KEYS: " << liczbakluczy;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
}

void informacje3_4() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(20, 36);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(45, 36);
    cout << "STARS: " << starslevelzapis[world - 1][level - 1] << " / 3";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(20, 38);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "KEY: " << klucz;
    gotoxy(45, 38);
    cout << "MAGNETIC KEYS: " << liczbakluczy;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
}

void informacje4() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(40, 34);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(65, 34);
    cout << "STARS: " << starslevelzapis[world - 1][level - 1] << " / 3";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(40, 36);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "KEY: " << klucz;
}

void informacje4_1() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(40, 34);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(65, 34);
    cout << "STARS: " << starslevelzapis[world - 1][level - 1] << " / 3";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(40, 36);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "KEY: " << klucz;
    gotoxy(65, 36);
    cout << "MAGNETIC KEYS: " << liczbakluczy;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
}

void informacje4_2() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(20, 31);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(45, 31);
    cout << "STARS: " << starslevelzapis[world - 1][level - 1] << " / 3";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(20, 33);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "KEY: " << klucz;
    gotoxy(45, 33);
    cout << "MAGNETIC KEYS: " << liczbakluczy;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
}

void informacje4_3() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(40, 36);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(65, 36);
    cout << "STARS: " << starslevelzapis[world - 1][level - 1] << " / 3";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(40, 38);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "KEY: " << klucz;
    gotoxy(65, 38);
    cout << "MAGNETIC KEYS: " << liczbakluczy;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
}

void informacje4_4() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(65, 3);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    gotoxy(80, 3);
    cout << "STARS: " << starslevelzapis[world - 1][level - 1] << " / 3";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(65, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "KEY: " << klucz;
    gotoxy(80, 5);
    cout << "MAGNETIC KEYS: " << liczbakluczy;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
}

void informacjeThePitfall1() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(40, 38);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(65, 38);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "KEY: " << klucz;
}

void informacjeThePitfall2() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(54, 32);
    cout << "LIVES: " << zycia;
}

void informacjeThePitfall3() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(44, 40);
    cout << "LIVES: " << zycia;
}

void informacjeThePitfallBoss() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    gotoxy(50, 7);
    cout << "LIVES: " << zycia;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    gotoxy(130, 7);
    cout << "ULTRA STARS " << ultrastars << "/20";
}

void informacjeinfo() {
    if (world == 1) {
        if (level == 1) {
            informacje1();
        }
        else if (level == 2) {
            informacje1();
        }
        else if (level == 3) {
            informacje1();
        }
        else if (level == 4) {
            informacje1_1();
        }
        else if (level == 5) {
            informacje1_2();
        }
    }
    if (world == 2) {
        if (level == 1) {
            informacje2();
        }
        else if (level == 2) {
            informacje2_1();
        }
        else if (level == 3) {
            informacje2_2();
        }
        else if (level == 4) {
            informacje2_3();
        }
        else if (level == 5) {
            informacje2_4();
        }
    }
    if (world == 3) {
        if (level == 1) {
            informacje3();
        }
        else if (level == 2) {
            informacje3_1();
        }
        else if (level == 3) {
            informacje3_2();
        }
        else if (level == 4) {
            informacje3_3();
        }
        else if (level == 5) {
            informacje3_4();
        }
    }
    if (world == 4) {
        if (level == 1) {
            informacje4();
        }
        else if (level == 2) {
            informacje4_1();
        }
        else if (level == 3) {
            informacje4_2();
        }
        else if (level == 4) {
            informacje4_3();
        }
        else if (level == 5) {
            informacje4_4();
        }
    }
    if (world == 5) {
        if (intersection == 1) {
            informacjeThePitfall1();
        }
        else if (intersection == 2) {
            informacjeThePitfall2();
        }
        else if (intersection == 3) {
            informacjeThePitfall3();
        }
        else if (intersection == 4) {
            informacjeThePitfallBoss();
        }
    }
}

void Postac() {
    if (wybranapostac == 1) {
        player = char(111);
    }
    else if (wybranapostac == 2) {
        player = char(79);
    }
    else if (wybranapostac == 3) {
        player = char(142);
    }
    else if (wybranapostac == 4) {
        player = char(139);
    }
    else if (wybranapostac == 5) {
        player = char(154);
    }
    else if (wybranapostac == 6) {
        player = char(153);
    }
    // 111, 79, 153, 142, 139, 154
}

void updateEntities() {
    PudloDestroy();
    Pudlo();
    PistoletDownEnemy();
    PistoletUpEnemy();
    PistoletRightEnemy();
    PistoletLeftEnemy();
    LaserDownEnemy();
    LaserUpEnemy();
    LaserRightEnemy();
    LaserLeftEnemy();
    FigerEnemy();
    FigerEnemyReverse();
    Przycisk();
    Check();
    Fin();
    FinI();
    HeartCollectible();
    StarCollectible();
    GreenStarCollectible();
    Boss();
    ChainWall();
    Gate();
    GateDifferent();
    KeyDifferent();
    Key();
    RollSideEnemy();
    RollUpEnemy();
    TeleportEntity();
}

void sprawdz() {
    if (starslevelzapis[world - 1][level - 1] > 3) {
        starslevelzapis[world - 1][level - 1] = 3;
    }
}

void respawnArea() {
    if (respawn == 0) {
        gracz.x = checkpoint[0].x;
        gracz.y = checkpoint[0].y;
        gotoxy(gracz.x, gracz.y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
        cout << player;
    }
    else if (respawn == 1) {
        gracz.x = checkpoint[1].x;
        gracz.y = checkpoint[1].y;
        gotoxy(gracz.x, gracz.y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
        cout << player;
    }
    else if (respawn == 2) {
        gracz.x = checkpoint[2].x;
        gracz.y = checkpoint[2].y;
        gotoxy(gracz.x, gracz.y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
        cout << player;
    }
    else {
        gracz.x = spawn.x;
        gracz.y = spawn.y;
        gotoxy(spawn.x, spawn.y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
        cout << player;
    }
}

void sterowanie() {
    if (c == 'a' || c == toupper('a')) {
        if (readChar(gracz.x - 1, gracz.y) != '#' && readChar(gracz.x - 1, gracz.y) != 'V' && readChar(gracz.x - 1, gracz.y) != 'M' && readChar(gracz.x - 1, gracz.y) != '|' && readChar(gracz.x - 1, gracz.y) != 'I' && readChar(gracz.x - 1, gracz.y) != 'Y' && readChar(gracz.x - 1, gracz.y) != '=' && readChar(gracz.x - 1, gracz.y) != 'W' && readChar(gracz.x - 1, gracz.y) != 'E' && readChar(gracz.x - 1, gracz.y) != 'R' && readChar(gracz.x - 1, gracz.y) != '<' && readChar(gracz.x - 1, gracz.y) != '>' && readChar(gracz.x - 1, gracz.y) != '^' && readChar(gracz.x - 1, gracz.y) != '+') {
            gotoxy(gracz.x, gracz.y);
            cout << " ";
            gracz.x -= 1;
            gotoxy(gracz.x, gracz.y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
            cout << player;

        }
    }
    else if (c == 'd' || c == toupper('d')) {
        if (readChar(gracz.x + 1, gracz.y) != '#' && readChar(gracz.x + 1, gracz.y) != 'V' && readChar(gracz.x + 1, gracz.y) != 'M' && readChar(gracz.x + 1, gracz.y) != '|' && readChar(gracz.x + 1, gracz.y) != 'I' && readChar(gracz.x + 1, gracz.y) != 'Y' && readChar(gracz.x + 1, gracz.y) != '=' && readChar(gracz.x + 1, gracz.y) != 'W' && readChar(gracz.x + 1, gracz.y) != 'E' && readChar(gracz.x + 1, gracz.y) != 'R' && readChar(gracz.x + 1, gracz.y) != '<' && readChar(gracz.x + 1, gracz.y) != '>' && readChar(gracz.x + 1, gracz.y) != '^' && readChar(gracz.x + 1, gracz.y) != '+') {
            gotoxy(gracz.x, gracz.y);
            cout << " ";
            gracz.x += 1;
            gotoxy(gracz.x, gracz.y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
            cout << player;

        }
    }
    else if (c == 'w' || c == toupper('w')) {
        if (readChar(gracz.x, gracz.y - 1) != '#' && readChar(gracz.x, gracz.y - 1) != 'V' && readChar(gracz.x, gracz.y - 1) != 'M' && readChar(gracz.x, gracz.y - 1) != '|' && readChar(gracz.x, gracz.y - 1) != 'I' && readChar(gracz.x, gracz.y - 1) != 'Y' && readChar(gracz.x, gracz.y - 1) != '=' && readChar(gracz.x, gracz.y - 1) != 'W' && readChar(gracz.x, gracz.y - 1) != 'E' && readChar(gracz.x, gracz.y - 1) != 'R' && readChar(gracz.x, gracz.y - 1) != '<' && readChar(gracz.x, gracz.y - 1) != '>' && readChar(gracz.x, gracz.y - 1) != '^' && readChar(gracz.x, gracz.y - 1) != '+') {
            gotoxy(gracz.x, gracz.y);
            cout << " ";
            gracz.y -= 1;
            gotoxy(gracz.x, gracz.y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
            cout << player;

        }
    }
    else if (c == 's' || c == toupper('s')) {
        if (readChar(gracz.x, gracz.y + 1) != '#' && readChar(gracz.x, gracz.y + 1) != 'V' && readChar(gracz.x, gracz.y + 1) != 'M' && readChar(gracz.x, gracz.y + 1) != '|' && readChar(gracz.x, gracz.y + 1) != 'I' && readChar(gracz.x, gracz.y + 1) != 'Y' && readChar(gracz.x, gracz.y + 1) != '=' && readChar(gracz.x, gracz.y + 1) != 'W' && readChar(gracz.x, gracz.y + 1) != 'E' && readChar(gracz.x, gracz.y + 1) != 'R' && readChar(gracz.x, gracz.y + 1) != '<' && readChar(gracz.x, gracz.y + 1) != '>' && readChar(gracz.x, gracz.y + 1) != '^' && readChar(gracz.x, gracz.y + 1) != '+') {
            gotoxy(gracz.x, gracz.y);
            cout << " ";
            gracz.y += 1;
            gotoxy(gracz.x, gracz.y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
            cout << player;

        }
    }
    else if (c == VK_ESCAPE) {
        if (world != 0) {
            PauseMenu();
            informacjeinfo();
        }
    }
}

void sterowanietutorial() {
    if (c == 'a' || c == toupper('a')) {
        if (readChar(gracz.x - 1, gracz.y) != '#' && readChar(gracz.x - 1, gracz.y) != 'V' && readChar(gracz.x - 1, gracz.y) != 'M' && readChar(gracz.x - 1, gracz.y) != '|' && readChar(gracz.x - 1, gracz.y) != 'I' && readChar(gracz.x - 1, gracz.y) != 'Y' && readChar(gracz.x - 1, gracz.y) != '=' && readChar(gracz.x - 1, gracz.y) != 'W' && readChar(gracz.x - 1, gracz.y) != 'E' && readChar(gracz.x - 1, gracz.y) != 'R' && readChar(gracz.x - 1, gracz.y) != '<' && readChar(gracz.x - 1, gracz.y) != '>' && readChar(gracz.x - 1, gracz.y) != '^' && readChar(gracz.x - 1, gracz.y) != '+') {
            gotoxy(gracz.x, gracz.y);
            cout << " ";
            gracz.x -= 1;
            gotoxy(gracz.x, gracz.y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
            cout << player;

        }
    }
    else if (c == 'd' || c == toupper('d')) {
        if (readChar(gracz.x + 1, gracz.y) != '#' && readChar(gracz.x + 1, gracz.y) != 'V' && readChar(gracz.x + 1, gracz.y) != 'M' && readChar(gracz.x + 1, gracz.y) != '|' && readChar(gracz.x + 1, gracz.y) != 'I' && readChar(gracz.x + 1, gracz.y) != 'Y' && readChar(gracz.x + 1, gracz.y) != '=' && readChar(gracz.x + 1, gracz.y) != 'W' && readChar(gracz.x + 1, gracz.y) != 'E' && readChar(gracz.x + 1, gracz.y) != 'R' && readChar(gracz.x + 1, gracz.y) != '<' && readChar(gracz.x + 1, gracz.y) != '>' && readChar(gracz.x + 1, gracz.y) != '^' && readChar(gracz.x + 1, gracz.y) != '+') {
            gotoxy(gracz.x, gracz.y);
            cout << " ";
            gracz.x += 1;
            gotoxy(gracz.x, gracz.y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
            cout << player;

        }
    }
    else if (c == 'w' || c == toupper('w')) {
        if (readChar(gracz.x, gracz.y - 1) != '#' && readChar(gracz.x, gracz.y - 1) != 'V' && readChar(gracz.x, gracz.y - 1) != 'M' && readChar(gracz.x, gracz.y - 1) != '|' && readChar(gracz.x, gracz.y - 1) != 'I' && readChar(gracz.x, gracz.y - 1) != 'Y' && readChar(gracz.x, gracz.y - 1) != '=' && readChar(gracz.x, gracz.y - 1) != 'W' && readChar(gracz.x, gracz.y - 1) != 'E' && readChar(gracz.x, gracz.y - 1) != 'R' && readChar(gracz.x, gracz.y - 1) != '<' && readChar(gracz.x, gracz.y - 1) != '>' && readChar(gracz.x, gracz.y - 1) != '^' && readChar(gracz.x, gracz.y - 1) != '+') {
            gotoxy(gracz.x, gracz.y);
            cout << " ";
            gracz.y -= 1;
            gotoxy(gracz.x, gracz.y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
            cout << player;

        }
    }
    else if (c == 's' || c == toupper('s')) {
        if (readChar(gracz.x, gracz.y + 1) != '#' && readChar(gracz.x, gracz.y + 1) != 'V' && readChar(gracz.x, gracz.y + 1) != 'M' && readChar(gracz.x, gracz.y + 1) != '|' && readChar(gracz.x, gracz.y + 1) != 'I' && readChar(gracz.x, gracz.y + 1) != 'Y' && readChar(gracz.x, gracz.y + 1) != '=' && readChar(gracz.x, gracz.y + 1) != 'W' && readChar(gracz.x, gracz.y + 1) != 'E' && readChar(gracz.x, gracz.y + 1) != 'R' && readChar(gracz.x, gracz.y + 1) != '<' && readChar(gracz.x, gracz.y + 1) != '>' && readChar(gracz.x, gracz.y + 1) != '^' && readChar(gracz.x, gracz.y + 1) != '+') {
            gotoxy(gracz.x, gracz.y);
            cout << " ";
            gracz.y += 1;
            gotoxy(gracz.x, gracz.y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
            cout << player;

        }
    }
}

void update1() {
    Sleep(75);
    sterowanie();
    if (readChar(gracz.x, gracz.y) == '|' || readChar(gracz.x, gracz.y) == 'I') {
        utratazycia = true;
    }

    if (zebranaGwiazda == true) {
        starslevelzapis[world - 1][level - 1] += 1;
        sprawdz();
        informacjeinfo();
        zebranaGwiazda = false;
    }

    if (zebranaZielonaGwiazda == true) {
        ultrastars += 1;
        informacjeinfo();
        zebranaZielonaGwiazda = false;
    }

    if (zebraneZycie == true) {
        zycia += 1;
        informacjeinfo();
        zebraneZycie = false;
    }

    if (utratazycia == true) {
        zycia -= 1;
        utratazycia = false;
        informacjeinfo();
        if (zycia == 0) {
            grazaczeta = false;
            playing = false;
            dead();
        }
        respawnArea();
    }
}

void updateTutorial1() {
    Sleep(75);
    sterowanietutorial();

    if (c == 'r' || c == toupper('r')) {
        system("cls");
        deleteobjects();
        LoadLevelTutorial();
    }

    else if (readChar(gracz.x, gracz.y) == '|' || readChar(gracz.x, gracz.y) == 'I') {
        utratazycia = true;
    }

    if (utratazycia == true) {
        zycia -= 1;
        utratazycia = false;
        if (zycia == 0) {
            grazaczeta = false;
            playing = false;
        }
        if (respawn == 0) {
            gracz.x = checkpoint[0].x;
            gracz.y = checkpoint[0].y;
            gotoxy(gracz.x, gracz.y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
            cout << player;
        }
        else if (respawn == 1) {
            gracz.x = checkpoint[1].x;
            gracz.y = checkpoint[1].y;
            gotoxy(gracz.x, gracz.y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
            cout << player;
        }
        else if (respawn == -1) {
            gracz.x = spawn.x;
            gracz.y = spawn.y;
            gotoxy(spawn.x, spawn.y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
            cout << player;
        }
    }
}

void deleteobjects() {
    for (int i = 0; i < 50; i++) {
        if (pistoletdown[i].x != 0 && pistoletdown[i].y != 0) {
            pistoletdown[i].y = NULL;
            pistoletdown[i].x = NULL;
        }
        if (pistoletup[i].x != 0 && pistoletup[i].y != 0) {
            pistoletup[i].y = NULL;
            pistoletup[i].x = NULL;
        }
        if (pistoletright[i].x != 0 && pistoletright[i].y != 0) {
            pistoletright[i].y = NULL;
            pistoletright[i].x = NULL;
        }
        if (pistoletleft[i].x != 0 && pistoletleft[i].y != 0) {
            pistoletleft[i].y = NULL;
            pistoletleft[i].x = NULL;
        }
        if (laserdown[i].x != 0 && laserdown[i].y != 0) {
            laserdown[i].y = NULL;
            laserdown[i].x = NULL;
            laserdown[i].active = NULL;
        }
        if (laserup[i].x != 0 && laserup[i].y != 0) {
            laserup[i].y = NULL;
            laserup[i].x = NULL;
            laserup[i].active = NULL;
        }
        if (laserright[i].x != 0 && laserright[i].y != 0) {
            laserright[i].y = NULL;
            laserright[i].x = NULL;
            laserright[i].active = NULL;
        }
        if (laserleft[i].x != 0 && laserleft[i].y != 0) {
            laserleft[i].y = NULL;
            laserleft[i].x = NULL;
            laserleft[i].active = NULL;
        }
    }
    for (int i = 0; i < 500; i++) {
        if (figer[i].x != 0 && figer[i].y != 0) {
            figer[i].y = NULL;
            figer[i].x = NULL;
        }
        if (figerReverse[i].x != 0 && figerReverse[i].y != 0) {
            figerReverse[i].y = NULL;
            figerReverse[i].x = NULL;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (checkpoint[i].x != 0 && checkpoint[i].y != 0) {
            checkpoint[i].y = NULL;
            checkpoint[i].x = NULL;
        }
        if (gwiazdy[i].x != 0 && gwiazdy[i].y != 0) {
            gwiazdy[i].y = NULL;
            gwiazdy[i].x = NULL;
        }
    }
    for (int i = 0; i < 10; i++) {
        if (drzwi[i].x != 0 && drzwi[i].y != 0) {
            drzwi[i].y = NULL;
            drzwi[i].x = NULL;
        }
        if (drzwiinne[i].x != 0 && drzwiinne[i].y != 0) {
            drzwiinne[i].y = NULL;
            drzwiinne[i].x = NULL;
        }
    }
    if (finish.x != 0 && finish.y != 0) {
        finish.y = NULL;
        finish.x = NULL;
    }

    for (int i = 0; i < 6; i++) {
        if (finishi[i].x != 0 && finishi[i].y != 0) {
            finishi[i].y = NULL;
            finishi[i].x = NULL;
        }
    }
    for (int i = 0; i < 200; i++) {
        if (box[i].x != 0 && box[i].y != 0) {
            box[i].y = NULL;
            box[i].x = NULL;
        }
        if (boxdestroy[i].x != 0 && boxdestroy[i].y != 0) {
            boxdestroy[i].y = NULL;
            boxdestroy[i].x = NULL;
        }
    }
    for (int i = 0; i < 10; i++) {
        if (rollside[i].x != 0 && rollside[i].y != 0) {
            rollside[i].y = NULL;
            rollside[i].x = NULL;
        }
        if (rollup[i].x != 0 && rollup[i].y != 0) {
            rollup[i].y = NULL;
            rollup[i].x = NULL;
        }
    }
    for (int i = 0; i < 5; i++) {
        if (przycisk[i].x != 0 && przycisk[i].y != 0) {
            przycisk[i].y = NULL;
            przycisk[i].x = NULL;
        }
    }
    for (int i = 0; i < 15; i++) {
        if (heart[i].x != 0 && heart[i].y != 0) {
            heart[i].y = NULL;
            heart[i].x = NULL;
        }
    }
    for (int i = 0; i < 9; i++) {
        if (klucze[i].x != 0 && klucze[i].y != 0) {
            klucze[i].y = NULL;
            klucze[i].x = NULL;
        }
    }
    for (int i = 0; i < 8; i++) {
        if (kluczeinne[i].x != 0 && kluczeinne[i].y != 0) {
            kluczeinne[i].y = NULL;
            kluczeinne[i].x = NULL;
        }
    }
    for (int i = 0; i < 20; i++) {
        if (teleport[i].x1 != 0 && teleport[i].y1 != 0 && teleport[i].x2 != 0 && teleport[i].y2 != 0) {
            teleport[i].x1 = NULL;
            teleport[i].x2 = NULL;
            teleport[i].y1 = NULL;
            teleport[i].y2 = NULL;
        }
    }
    for (int i = 0; i < 25; i++) {
        if (chain[i].x != 0 && chain[i].y != 0) {
            chain[i].x = NULL;
            chain[i].y = NULL;
        }
        if (zielonegwiazdy[i].x != 0 && zielonegwiazdy[i].y != 0) {
            zielonegwiazdy[i].x = NULL;
            zielonegwiazdy[i].y = NULL;
        }
    }
    boss.x = NULL;
    boss.y = NULL;
    respawn = -1;
    klucz = false;
    liczbakluczy = 0;
}

//
void createEntitiesTutorial1() {

    CreatePistoletUpEnemy(0, 9, 5);
    CreatePistoletRightEnemy(0, 25, 5);
    CreatePistoletDownEnemy(0, 40, 5);
    CreatePistoletLeftEnemy(0, 55, 5);
    CreatePistoletDownEnemy(1, 41, 10);
    CreatePistoletLeftEnemy(1, 61, 12);
    CreatePistoletRightEnemy(1, 2, 15);
    FinishArea(57, 13);

}

void createEntitiesTutorial2() {
    CreateBox(0, 7, 6);
    CreateBox(1, 21, 11);
    CreateBox(2, 15, 5);
    CreateBox(3, 15, 7);
    CreateBox(4, 27, 5);
    CreatePistoletDownEnemy(0, 11, 6);
    CreatePistoletDownEnemy(1, 18, 4);
    CreatePistoletDownEnemy(2, 25, 4);
    CreatePistoletDownEnemy(3, 35, 5);
    FinishArea(39, 8);
}

void createEntitiesTutorial3() {
    CreateLaserDownEnemy(0, 32, 6);
    CreateLaserDownEnemy(1, 42, 6);
    CreateLaserUpEnemy(0, 42, 16);
    CreateLaserUpEnemy(1, 60, 16);
    CreateLaserRightEnemy(0, 27, 9);
    CreateLaserRightEnemy(1, 27, 15);
    CreateLaserLeftEnemy(0, 71, 8);
    CreateLaserLeftEnemy(1, 71, 10);
    CreateLaserLeftEnemy(2, 71, 12);
    FinishArea(69, 7);
}

void createEntitiesTutorial4() {
    CreateDoor(0, 21, 9);
    CreateDoor(1, 38, 11);
    CreateDoor(2, 72, 12);
    CreateKey(1, 21, 13);
    CreateKey(2, 36, 9);
    CreateKey(3, 69, 7);
    CreateLaserDownEnemy(0, 43, 7);
    CreateLaserDownEnemy(1, 75, 7);
    CreateLaserDownEnemy(2, 81, 7);
    CreateLaserUpEnemy(1, 50, 14);
    CreateLaserUpEnemy(2, 60, 14);
    CreateLaserRightEnemy(0, 39, 8);
    CreateLaserLeftEnemy(0, 71, 8);
    CreatePistoletUpEnemy(0, 54, 14);
    CreatePistoletDownEnemy(0, 41, 7);
    CreatePistoletDownEnemy(1, 48, 7);
    CreatePistoletDownEnemy(3, 63, 7);
    CreatePistoletLeftEnemy(0, 83, 9);
    CreatePistoletLeftEnemy(1, 83, 11);
    FinishArea(83, 10);
}

void createEntitiesTutorial5() {
    CreateSwitch(0, 15, 14);
    CreateSwitch(1, 20, 17);
    CreateSwitch(2, 65, 17);
    CreateLaserDownEnemy(0, 38, 8);
    CreateLaserUpEnemy(0, 41, 14);
    CreateLaserUpEnemy(1, 57, 14);
    CreateLaserUpEnemy(2, 65, 14);
    CreatePistoletUpEnemy(0, 48, 14);
    CreatePistoletDownEnemy(0, 68, 8);

    CreateFigerEnemyReverse(0, 26, 8);
    CreateFigerEnemyReverse(1, 27, 8);
    CreateFigerEnemyReverse(2, 28, 8);
    CreateFigerEnemyReverse(3, 29, 8);
    CreateFigerEnemyReverse(4, 30, 8);
    CreateFigerEnemyReverse(5, 31, 8);

    CreateFigerEnemyReverse(6, 26, 9);
    CreateFigerEnemy(7, 27, 9);
    CreateFigerEnemyReverse(8, 28, 9);
    CreateFigerEnemyReverse(9, 29, 9);
    CreateFigerEnemy(10, 30, 9);
    CreateFigerEnemyReverse(11, 31, 9);

    CreateFigerEnemyReverse(12, 26, 10);
    CreateFigerEnemy(13, 27, 10);
    CreateFigerEnemyReverse(14, 28, 10);
    CreateFigerEnemyReverse(15, 29, 10);
    CreateFigerEnemy(16, 30, 10);
    CreateFigerEnemyReverse(17, 31, 10);

    CreateFigerEnemyReverse(18, 26, 11);
    CreateFigerEnemy(19, 27, 11);
    CreateFigerEnemyReverse(20, 28, 11);
    CreateFigerEnemyReverse(21, 29, 11);
    CreateFigerEnemy(22, 30, 11);
    CreateFigerEnemyReverse(23, 31, 11);

    CreateFigerEnemyReverse(24, 26, 12);
    CreateFigerEnemy(25, 27, 12);
    CreateFigerEnemyReverse(26, 28, 12);
    CreateFigerEnemyReverse(27, 29, 12);
    CreateFigerEnemy(28, 30, 12);
    CreateFigerEnemyReverse(29, 31, 12);

    CreateFigerEnemyReverse(30, 26, 13);
    CreateFigerEnemy(31, 27, 13);
    CreateFigerEnemyReverse(32, 28, 13);
    CreateFigerEnemyReverse(33, 29, 13);
    CreateFigerEnemy(34, 30, 13);
    CreateFigerEnemyReverse(35, 31, 13);

    CreateFigerEnemyReverse(36, 26, 14);
    CreateFigerEnemyReverse(37, 27, 14);
    CreateFigerEnemyReverse(38, 28, 14);
    CreateFigerEnemyReverse(39, 29, 14);
    CreateFigerEnemyReverse(40, 30, 14);
    CreateFigerEnemyReverse(41, 31, 14);

    CreateFigerEnemy(42, 72, 8);
    CreateFigerEnemy(43, 72, 9);
    CreateFigerEnemy(44, 72, 10);
    CreateFigerEnemy(45, 72, 11);
    CreateFigerEnemy(46, 72, 12);
    CreateFigerEnemy(47, 72, 13);
    CreateFigerEnemy(48, 72, 14);


    FinishArea(79, 11);
}

void createEntitiesTutorial6() {
    CreateDoorDifferent(0, 50, 23);
    CreateDoorDifferent(1, 77, 15);
    CreateKeyDifferent(0, 64, 23);
    CreateKeyDifferent(1, 51, 19);
    CreateKeyDifferent(2, 30, 13);
    CreateKeyDifferent(3, 76, 9);

    CreateFigerEnemyReverse(0, 43, 9);
    CreateFigerEnemyReverse(1, 55, 10);
    CreateFigerEnemyReverse(2, 68, 10);
    CreateFigerEnemyReverse(3, 80, 10);
    CreateFigerEnemyReverse(4, 37, 11);
    CreateFigerEnemyReverse(5, 46, 12);
    CreateFigerEnemyReverse(6, 61, 12);
    CreateFigerEnemyReverse(7, 70, 13);
    CreateFigerEnemyReverse(8, 39, 15);
    CreateFigerEnemyReverse(9, 70, 17);
    CreateFigerEnemyReverse(10, 32, 18);
    CreateFigerEnemyReverse(11, 43, 18);
    CreateFigerEnemyReverse(12, 60, 18);
    CreateFigerEnemyReverse(13, 77, 18);
    CreateFigerEnemyReverse(14, 70, 19);

    CreatePistoletUpEnemy(0, 34, 20);
    CreatePistoletUpEnemy(1, 49, 20);
    CreatePistoletUpEnemy(2, 63, 20);
    CreatePistoletUpEnemy(3, 76, 20);


    CreatePistoletDownEnemy(0, 50, 8);
    CreatePistoletDownEnemy(1, 67, 8);
    CreatePistoletDownEnemy(2, 80, 8);

    CreatePistoletRightEnemy(1, 29, 9);
    CreatePistoletRightEnemy(2, 39, 13);
    CreatePistoletRightEnemy(3, 29, 16);

    CreateLaserDownEnemy(0, 39, 8);
    CreateLaserDownEnemy(1, 62, 8);
    CreateLaserDownEnemy(2, 73, 8);

    CreateLaserUpEnemy(0, 40, 20);
    CreateLaserUpEnemy(1, 38, 12);

    CreateLaserRightEnemy(0, 60, 14);
    CreateLaserRightEnemy(1, 29, 11);
    CreateLaserRightEnemy(2, 29, 18);

    FinishArea(82, 15);

}

void createEntitiesTutorial7() {
    FinishArea(76, 12);


    CreateRollSideEnemy(0, 26, 13);
    CreateRollSideEnemy(1, 36, 14);
    CreateRollSideEnemy(2, 49, 9);
    CreateRollSideEnemy(3, 60, 13);
    CreateRollSideEnemy(4, 52, 21);

    CreateRollUpEnemy(0, 19, 10);
    CreateRollUpEnemy(1, 40, 11);
    CreateRollUpEnemy(2, 56, 14);
    CreateRollUpEnemy(3, 63, 9);
    CreateRollUpEnemy(4, 33, 21);
}

void createEntitiesTutorial8() {
    FinishArea(88, 26);

    CreateDoor(2, 137, 15);
    CreateKey(2, 128, 10);

    CreateLaserUpEnemy(0, 38, 15);
    CreateLaserUpEnemy(1, 63, 15);

    CreateBox(0, 41, 10);


    CreatePistoletDownEnemy(0, 52, 9);

    CreateLaserDownEnemy(0, 121, 7);
    CreateLaserDownEnemy(1, 134, 7);

    CreateRollSideEnemy(0, 125, 15);
    CreateRollSideEnemy(1, 65, 29);

    CreateRollUpEnemy(0, 57, 29);
    CreateRollUpEnemy(1, 75, 25);

    CreateTeleport(0, 50, 14, 57, 14);
    CreateTeleport(1, 71, 11, 107, 15);
    CreateTeleport(2, 144, 15, 42, 26);

}
//

void createEntitiesLevel1_1() {
    CreatePistoletDownEnemy(0, 18, 4);
    CreatePistoletDownEnemy(1, 21, 4);
    CreatePistoletDownEnemy(2, 71, 9);
    CreatePistoletDownEnemy(3, 76, 9);
    CreatePistoletDownEnemy(4, 74, 4);
    CreatePistoletDownEnemy(5, 78, 4);
    CreatePistoletDownEnemy(6, 53, 13);
    CreatePistoletUpEnemy(0, 37, 16);
    CreatePistoletUpEnemy(1, 45, 23);
    CreatePistoletUpEnemy(2, 60, 23);
    CreatePistoletUpEnemy(3, 73, 23);
    CreatePistoletLeftEnemy(0, 78, 18);
    CreatePistoletLeftEnemy(1, 78, 19);
    CreateStar(0, 37, 7);
    CreateStar(1, 75, 18);
    CreateStar(2, 72, 6);
    FinishArea(90, 5);
    CheckpointArea(0, 34, 16);
}

void createEntitiesLevel1_2() {
    CreateStar(0, 46, 15);
    CreateStar(1, 54, 27);
    CreateStar(2, 66, 14);
    CheckpointArea(0, 40, 18);
    FinishArea(77, 17);
    CreatePistoletLeftEnemy(0, 29, 5);
    CreatePistoletLeftEnemy(1, 39, 7);
    CreatePistoletLeftEnemy(2, 56, 14);
    CreatePistoletLeftEnemy(3, 55, 23);
    CreatePistoletLeftEnemy(4, 55, 24);
    CreatePistoletRightEnemy(0, 31, 9);
    CreatePistoletRightEnemy(1, 14, 15);
    CreatePistoletRightEnemy(2, 38, 25);
    CreatePistoletUpEnemy(0, 33, 25);
    CreatePistoletUpEnemy(1, 34, 24);
    CreatePistoletUpEnemy(2, 35, 25);
    CreatePistoletUpEnemy(3, 36, 23);
    CreatePistoletUpEnemy(4, 37, 25);
    CreatePistoletUpEnemy(5, 60, 20);
    CreatePistoletUpEnemy(6, 65, 20);
    CreatePistoletUpEnemy(7, 66, 20);
    CreatePistoletUpEnemy(8, 67, 27);
    CreatePistoletUpEnemy(9, 68, 27);
    CreatePistoletUpEnemy(10, 71, 20);
    CreatePistoletDownEnemy(0, 62, 13);
    CreatePistoletDownEnemy(1, 67, 13);
    CreatePistoletDownEnemy(2, 68, 13);
    CreatePistoletDownEnemy(3, 73, 13);


}

void createEntitiesLevel1_3() {
    CreateStar(0, 32, 15);
    CreateStar(1, 28, 8);
    CreateStar(2, 83, 24);
    CreateHeart(0, 34, 7);
    CheckpointArea(0, 57, 17);
    FinishArea(79, 20);
    CreateBox(0, 22, 15);
    CreateBox(1, 57, 7);
    CreateBox(2, 60, 8);
    CreateBox(3, 62, 7);
    CreateBox(4, 64, 15);
    CreateBox(5, 73, 15);
    CreateBox(6, 53, 13);
    CreateBox(7, 53, 14);
    CreatePistoletLeftEnemy(0, 41, 15);
    CreatePistoletLeftEnemy(1, 41, 16);
    CreatePistoletLeftEnemy(2, 97, 16);
    CreatePistoletUpEnemy(0, 45, 17);
    CreatePistoletUpEnemy(1, 51, 17);
    CreatePistoletUpEnemy(2, 88, 28);
    CreatePistoletDownEnemy(0, 31, 4);
    CreatePistoletDownEnemy(1, 30, 6);
    CreatePistoletDownEnemy(2, 48, 7);
    CreatePistoletDownEnemy(3, 51, 7);
    CreatePistoletDownEnemy(4, 55, 15);
    CreatePistoletDownEnemy(5, 62, 12);
    CreatePistoletDownEnemy(6, 71, 9);
    CreatePistoletDownEnemy(7, 80, 7);
    CreatePistoletDownEnemy(8, 88, 14);

}

void createEntitiesLevel1_4() {
    CreateStar(0, 43, 17);
    CreateStar(1, 60, 16);
    CreateStar(2, 86, 10);
    FinishArea(91, 12);

    CreateBox(0, 82, 6);
    CreateBox(1, 85, 6);
    CreateBox(2, 87, 6);
    CreateBox(3, 48, 7);
    CreateBox(4, 55, 7);
    CreateBox(5, 62, 7);
    CreateBox(6, 66, 7);
    CreateBox(7, 71, 7);
    CreateBox(8, 82, 7);
    CreateBox(9, 84, 7);
    CreateBox(10, 77, 8);
    CreateBox(11, 82, 8);
    CreateBox(12, 84, 8);
    CreateBox(13, 86, 8);

    CreateBox(14, 39, 9);
    CreateBox(15, 40, 9);
    CreateBox(16, 41, 9);
    CreateBox(17, 42, 9);
    CreateBox(18, 43, 9);
    CreateBox(19, 44, 9);
    CreateBox(20, 45, 9);
    CreateBox(21, 75, 9);
    CreateBox(22, 82, 9);
    CreateBox(23, 83, 9);
    CreateBox(24, 86, 9);
    CreateBox(25, 88, 9);

    CreateBox(26, 41, 10);
    CreateBox(27, 45, 10);
    CreateBox(28, 54, 10);
    CreateBox(29, 57, 10);
    CreateBox(30, 63, 10);
    CreateBox(31, 85, 10);

    CreateBox(32, 40, 11);
    CreateBox(33, 42, 11);
    CreateBox(34, 44, 11);
    CreateBox(35, 50, 11);
    CreateBox(36, 61, 11);
    CreateBox(37, 74, 11);
    CreateBox(38, 80, 11);

    CreateBox(39, 39, 12);
    CreateBox(40, 42, 12);
    CreateBox(41, 43, 12);
    CreateBox(42, 47, 12);
    CreateBox(43, 49, 12);
    CreateBox(44, 52, 12);
    CreateBox(45, 54, 12);
    CreateBox(46, 55, 12);
    CreateBox(47, 56, 12);
    CreateBox(48, 67, 12);
    CreateBox(49, 78, 12);
    CreateBox(50, 88, 12);

    CreateBox(51, 39, 13);
    CreateBox(52, 40, 13);
    CreateBox(53, 41, 13);
    CreateBox(54, 42, 13);
    CreateBox(55, 43, 13);
    CreateBox(56, 44, 13);
    CreateBox(57, 45, 13);
    CreateBox(58, 62, 13);
    CreateBox(59, 63, 13);
    CreateBox(60, 73, 13);
    CreateBox(61, 78, 13);
    CreateBox(62, 84, 13);
    CreateBox(63, 85, 13);
    CreateBox(64, 86, 13);
    CreateBox(65, 87, 13);

    CreateBox(66, 42, 14);
    CreateBox(67, 48, 14);
    CreateBox(68, 56, 14);
    CreateBox(69, 61, 14);
    CreateBox(70, 63, 14);
    CreateBox(71, 86, 14);

    CreateBox(72, 40, 15);
    CreateBox(73, 42, 15);
    CreateBox(74, 44, 15);
    CreateBox(75, 51, 15);
    CreateBox(76, 56, 15);
    CreateBox(77, 60, 15);
    CreateBox(78, 61, 15);
    CreateBox(79, 63, 15);
    CreateBox(80, 64, 15);
    CreateBox(81, 67, 15);
    CreateBox(82, 75, 15);
    CreateBox(83, 84, 15);

    CreateBox(84, 39, 16);
    CreateBox(85, 43, 16);
    CreateBox(86, 45, 16);
    CreateBox(87, 55, 16);
    CreateBox(88, 59, 16);
    CreateBox(89, 63, 16);
    CreateBox(90, 70, 16);
    CreateBox(91, 77, 16);
    CreateBox(92, 81, 16);
    CreateBox(93, 82, 16);
    CreateBox(94, 85, 16);

    CreateBox(95, 40, 17);
    CreateBox(96, 42, 17);
    CreateBox(97, 44, 17);
    CreateBox(98, 50, 17);
    CreateBox(99, 55, 17);
    CreateBox(100, 60, 17);
    CreateBox(101, 62, 17);
    CreateBox(102, 69, 17);
    CreateBox(103, 76, 17);
    CreateBox(104, 80, 17);
    CreateBox(105, 86, 17);

}

void createEntitiesLevel1_5() {
    CreateStar(0, 48, 6);
    CreateStar(1, 66, 22);
    CreateStar(2, 43, 44);
    CreateHeart(0, 43, 39);
    CreateHeart(1, 43, 19);
    CreateHeart(2, 70, 17);
    CreateHeart(3, 93, 37);
    CreateHeart(4, 93, 36);
    CheckpointArea(0, 43, 35);
    CheckpointArea(1, 43, 20);
    CheckpointArea(2, 92, 36);
    FinishArea(68, 4);



    CreateBox(0, 66, 5);
    CreateBox(1, 67, 5);
    CreateBox(2, 68, 5);
    CreateBox(3, 69, 5);
    CreateBox(4, 70, 5);
    CreateBox(5, 65, 6);
    CreateBox(6, 66, 6);
    CreateBox(7, 67, 6);
    CreateBox(8, 68, 6);
    CreateBox(9, 69, 6);
    CreateBox(10, 70, 6);
    CreateBox(11, 71, 6);
    CreateBox(12, 64, 7);
    CreateBox(13, 65, 7);
    CreateBox(14, 66, 7);
    CreateBox(15, 67, 7);
    CreateBox(16, 68, 7);
    CreateBox(17, 69, 7);
    CreateBox(18, 70, 7);
    CreateBox(19, 71, 7);
    CreateBox(20, 72, 7);
    CreateBox(21, 77, 9);
    CreateBox(22, 83, 9);
    CreateBox(23, 86, 9);
    CreateBox(24, 89, 9);
    CreateBox(25, 91, 9);
    CreateBox(26, 93, 9);
    CreateBox(27, 61, 10);
    CreateBox(28, 72, 10);
    CreateBox(29, 74, 10);
    CreateBox(30, 77, 10);
    CreateBox(31, 80, 10);
    CreateBox(32, 83, 10);
    CreateBox(33, 88, 10);
    CreateBox(34, 91, 10);
    CreateBox(35, 71, 11);
    CreateBox(36, 74, 11);
    CreateBox(37, 78, 11);
    CreateBox(38, 80, 11);
    CreateBox(39, 81, 11);
    CreateBox(40, 84, 11);
    CreateBox(41, 87, 11);
    CreateBox(42, 90, 11);
    CreateBox(42, 93, 11);
    CreateBox(42, 63, 12);
    CreateBox(43, 73, 12);
    CreateBox(44, 76, 12);
    CreateBox(45, 80, 12);
    CreateBox(46, 83, 12);
    CreateBox(47, 84, 12);
    CreateBox(48, 85, 12);
    CreateBox(49, 87, 12);
    CreateBox(50, 90, 12);
    CreateBox(51, 91, 12);
    CreateBox(52, 74, 13);
    CreateBox(53, 78, 13);
    CreateBox(54, 82, 13);
    CreateBox(55, 85, 13);
    CreateBox(56, 88, 13);
    CreateBox(57, 90, 13);
    CreateBox(58, 91, 13);
    CreateBox(59, 92, 13);
    CreateBox(60, 58, 16);
    CreateBox(61, 59, 18);

    CreateBox(62, 55, 22);
    CreateBox(63, 77, 22);
    CreateBox(64, 90, 22);
    CreateBox(65, 90, 23);
    CreateBox(66, 44, 24);
    CreateBox(67, 55, 24);
    CreateBox(68, 63, 24);
    CreateBox(69, 66, 24);
    CreateBox(70, 90, 24);

    CreateBox(71, 45, 30);

    CreatePistoletUpEnemy(0, 43, 13);
    CreatePistoletUpEnemy(1, 51, 13);
    CreatePistoletUpEnemy(2, 59, 13);
    CreatePistoletUpEnemy(3, 51, 53);
    CreatePistoletUpEnemy(4, 73, 53);
    CreatePistoletUpEnemy(5, 57, 44);



    CreatePistoletRightEnemy(0, 43, 45);
    CreatePistoletRightEnemy(1, 43, 49);
    CreatePistoletRightEnemy(2, 43, 50);
    CreatePistoletRightEnemy(3, 58, 45);
    CreatePistoletRightEnemy(4, 63, 48);
    CreatePistoletRightEnemy(5, 46, 41);
    CreatePistoletRightEnemy(6, 46, 39);
    CreatePistoletRightEnemy(7, 46, 37);
    CreatePistoletRightEnemy(8, 43, 25);
    CreatePistoletRightEnemy(9, 43, 22);
    CreatePistoletRightEnemy(10, 43, 18);
    CreatePistoletRightEnemy(11, 43, 17);
    CreatePistoletRightEnemy(12, 43, 16);
    CreatePistoletRightEnemy(13, 61, 22);




    CreatePistoletDownEnemy(4, 62, 15);
    CreatePistoletDownEnemy(5, 47, 21);
    CreatePistoletDownEnemy(6, 59, 21);
    CreatePistoletDownEnemy(7, 72, 21);
    CreatePistoletDownEnemy(8, 82, 21);
    CreatePistoletDownEnemy(9, 88, 21);
    CreatePistoletDownEnemy(10, 49, 36);
    CreatePistoletDownEnemy(11, 56, 36);
    CreatePistoletDownEnemy(12, 64, 36);
    CreatePistoletDownEnemy(13, 75, 36);
    CreatePistoletDownEnemy(14, 82, 36);
    CreatePistoletDownEnemy(15, 49, 44);
    CreatePistoletDownEnemy(17, 62, 49);
    CreatePistoletDownEnemy(18, 66, 44);
    CreatePistoletDownEnemy(19, 75, 47);
    CreatePistoletDownEnemy(20, 80, 44);
    CreatePistoletDownEnemy(21, 87, 44);



    CreatePistoletLeftEnemy(0, 93, 15);
    CreatePistoletLeftEnemy(1, 93, 17);
    CreatePistoletLeftEnemy(2, 93, 19);
    CreatePistoletLeftEnemy(3, 70, 22);
    CreatePistoletLeftEnemy(4, 89, 27);
    CreatePistoletLeftEnemy(5, 93, 28);
    CreatePistoletLeftEnemy(6, 93, 29);
    CreatePistoletLeftEnemy(7, 93, 30);
    CreatePistoletLeftEnemy(8, 93, 31);
    CreatePistoletLeftEnemy(9, 93, 32);
    CreatePistoletLeftEnemy(10, 93, 33);
    CreatePistoletLeftEnemy(11, 93, 34);
    CreatePistoletLeftEnemy(12, 91, 38);
    CreatePistoletLeftEnemy(13, 91, 40);
    CreatePistoletLeftEnemy(14, 91, 42);
    CreatePistoletLeftEnemy(15, 91, 46);
    CreatePistoletLeftEnemy(16, 91, 48);
    CreatePistoletLeftEnemy(18, 74, 46);
    CreatePistoletLeftEnemy(19, 61, 48);
    CreatePistoletLeftEnemy(20, 56, 45);





}


void createEntitiesLevel2_1() {
    CreateLaserRightEnemy(0, 30, 10);
    CreateLaserRightEnemy(2, 56, 28);
    CreateLaserRightEnemy(3, 18, 27);
    CreateLaserRightEnemy(4, 18, 29);

    CreateLaserDownEnemy(0, 33, 6);
    CreateLaserDownEnemy(1, 39, 6);
    CreateLaserDownEnemy(2, 45, 6);
    CreateLaserDownEnemy(3, 52, 6);
    CreateLaserDownEnemy(4, 63, 3);
    CreateLaserDownEnemy(7, 66, 3);
    CreateLaserDownEnemy(9, 68, 6);
    CreateLaserDownEnemy(10, 67, 12);
    CreateLaserDownEnemy(11, 64, 18);
    CreateLaserDownEnemy(12, 65, 25);
    CreateLaserDownEnemy(14, 34, 23);
    CreateLaserDownEnemy(15, 21, 23);
    CreateLaserDownEnemy(16, 22, 23);
    CreateLaserDownEnemy(17, 23, 23);


    CreateLaserLeftEnemy(0, 57, 8);
    CreateLaserLeftEnemy(2, 68, 27);


    CreateLaserUpEnemy(2, 68, 24);
    CreateLaserUpEnemy(3, 60, 29);
    CreateLaserUpEnemy(4, 54, 29);
    CreateLaserUpEnemy(5, 46, 29);

    CheckpointArea(0, 62, 12);
    CheckpointArea(1, 55, 26);

    CreateStar(0, 57, 6);
    CreateStar(1, 68, 3);
    CreateStar(2, 26, 32);

    FinishArea(15, 24);

}

void createEntitiesLevel2_2() {

    CreateLaserDownEnemy(0, 23, 14);
    CreateLaserDownEnemy(1, 96, 4);
    CreateLaserDownEnemy(2, 100, 4);
    CreateLaserDownEnemy(3, 29, 14);
    CreateLaserDownEnemy(4, 40, 14);
    CreateLaserDownEnemy(5, 58, 10);
    CreateLaserDownEnemy(6, 70, 10);
    CreateLaserDownEnemy(7, 46, 7);

    CreateLaserLeftEnemy(0, 101, 5);
    CreateLaserLeftEnemy(1, 48, 27);
    CreateLaserLeftEnemy(2, 52, 22);
    CreateLaserLeftEnemy(3, 52, 20);
    CreateLaserLeftEnemy(4, 52, 17);
    CreateLaserLeftEnemy(6, 73, 15);
    CreateLaserLeftEnemy(7, 101, 10);
    CreateLaserLeftEnemy(8, 53, 10);
    CreateLaserLeftEnemy(9, 48, 24);

    CreatePistoletDownEnemy(0, 35, 14);
    CreatePistoletDownEnemy(1, 46, 14);
    CreatePistoletDownEnemy(3, 86, 4);



    CreatePistoletUpEnemy(0, 77, 18);



    CreatePistoletLeftEnemy(1, 101, 8);
    CreatePistoletLeftEnemy(3, 52, 15);
    CreatePistoletLeftEnemy(4, 81, 7);
    CreatePistoletRightEnemy(0, 50, 7);
    CreatePistoletRightEnemy(1, 21, 19);



    CreateLaserRightEnemy(1, 54, 13);
    CreateLaserRightEnemy(2, 54, 15);
    CreateLaserRightEnemy(4, 86, 10);
    CreateLaserRightEnemy(5, 19, 20);
    CreateLaserRightEnemy(6, 26, 22);
    CreateLaserRightEnemy(7, 34, 25);
    CreateLaserRightEnemy(8, 34, 28);

    CreateLaserUpEnemy(0, 76, 18);
    CreateLaserUpEnemy(1, 79, 18);


    CheckpointArea(0, 53, 18);

    CreateStar(0, 92, 10);
    CreateStar(1, 66, 11);
    CreateStar(2, 41, 29);

    FakeFinishArea(19, 21);
    FinishArea(18, 14);
}

void createEntitiesLevel2_3() {

    CreateBox(0, 61, 11);
    CreateBox(1, 66, 9);
    CreateBox(2, 64, 10);
    CreateBox(3, 66, 11);
    CreateBox(4, 71, 27);
    CreateBox(5, 74, 23);

    CreateLaserDownEnemy(0, 19, 2);
    CreateLaserDownEnemy(1, 38, 6);
    CreateLaserDownEnemy(3, 57, 8);
    CreateLaserDownEnemy(4, 59, 12);
    CreateLaserDownEnemy(7, 77, 21);
    CreateLaserDownEnemy(8, 88, 20);
    CreateLaserDownEnemy(9, 94, 20);
    CreateLaserDownEnemy(10, 115, 16);


    CreateLaserLeftEnemy(0, 46, 19);
    CreateLaserLeftEnemy(1, 114, 22);
    CreateLaserLeftEnemy(6, 117, 26);




    CreatePistoletDownEnemy(0, 51, 8);
    CreatePistoletDownEnemy(1, 53, 8);
    CreatePistoletDownEnemy(2, 60, 25);
    CreatePistoletDownEnemy(3, 82, 21);
    CreatePistoletDownEnemy(4, 39, 6);
    CreatePistoletDownEnemy(5, 40, 6);
    CreatePistoletDownEnemy(6, 41, 6);
    CreatePistoletDownEnemy(7, 42, 6);
    CreatePistoletDownEnemy(8, 43, 6);
    CreatePistoletDownEnemy(9, 44, 6);
    CreatePistoletDownEnemy(10, 45, 6);



    CreatePistoletUpEnemy(2, 102, 28);
    CreatePistoletUpEnemy(3, 122, 29);


    CreatePistoletLeftEnemy(0, 59, 24);



    CreatePistoletRightEnemy(0, 95, 20);
    CreatePistoletRightEnemy(1, 98, 19);
    CreatePistoletRightEnemy(2, 48, 13);
    CreatePistoletRightEnemy(3, 48, 17);



    CreateLaserRightEnemy(0, 26, 19);
    CreateLaserRightEnemy(3, 69, 24);


    CreateLaserUpEnemy(0, 37, 26);
    CreateLaserUpEnemy(4, 31, 14);

    CheckpointArea(0, 68, 27);
    CheckpointArea(1, 69, 11);

    CreateStar(0, 18, 5);
    CreateStar(1, 37, 19);
    CreateStar(2, 117, 19);

    FakeFinishArea(26, 22);
    FinishArea(122, 26);
}

void createEntitiesLevel2_4() {


    CreateBox(0, 70, 12);
    CreateBox(1, 83, 22);
    CreateBox(2, 98, 23);


    CreateLaserDownEnemy(0, 123, 10);
    CreateLaserDownEnemy(1, 124, 10);
    CreateLaserDownEnemy(2, 125, 10);
    CreateLaserDownEnemy(3, 119, 13);
    CreateLaserDownEnemy(4, 128, 13);
    CreateLaserDownEnemy(5, 136, 13);
    CreateLaserDownEnemy(6, 141, 13);




    CreateLaserLeftEnemy(0, 72, 19);
    CreateLaserLeftEnemy(1, 131, 26);
    CreateLaserLeftEnemy(2, 131, 27);
    CreateLaserLeftEnemy(3, 131, 28);



    CreatePistoletDownEnemy(0, 79, 9);
    CreatePistoletDownEnemy(1, 107, 21);
    CreatePistoletDownEnemy(2, 110, 21);



    CreatePistoletUpEnemy(1, 145, 24);


    CreatePistoletLeftEnemy(0, 86, 13);


    CreateLaserRightEnemy(0, 65, 9);
    CreateLaserRightEnemy(1, 65, 10);
    CreateLaserRightEnemy(2, 65, 21);
    CreateLaserRightEnemy(3, 65, 22);
    CreateLaserRightEnemy(4, 65, 23);
    CreateLaserRightEnemy(5, 87, 21);
    CreateLaserRightEnemy(7, 96, 22);
    CreateLaserRightEnemy(8, 116, 14);
    CreateLaserRightEnemy(10, 116, 19);
    CreateLaserRightEnemy(12, 116, 23);


    CreateLaserUpEnemy(1, 131, 24);
    CreateLaserUpEnemy(2, 139, 24);
    CreateLaserUpEnemy(4, 150, 24);
    CreateLaserUpEnemy(5, 151, 24);

    CheckpointArea(0, 62, 12);
    CheckpointArea(1, 115, 24);
    CheckpointArea(2, 64, 24);

    CreateStar(0, 89, 9);
    CreateStar(1, 123, 27);
    CreateStar(2, 128, 11);

    CreateHeart(0, 63, 11);
    CreateHeart(1, 111, 28);
    CreateHeart(2, 126, 11);
    CreateHeart(3, 146, 14);

    CreateKey(2, 87, 9); // 0 i 1 cursed
    CreateKey(3, 150, 14);

    CreateDoor(0, 27, 18);
    CreateDoor(1, 62, 14);

    FinishArea(27, 20);
}

void createEntitiesLevel2_5() {

    CreateBox(0, 55, 29);
    CreateBox(1, 54, 30);
    CreateBox(2, 144, 19);
    CreateBox(3, 145, 18);
    CreateBox(4, 70, 24);

    CreateLaserDownEnemy(0, 43, 8);
    CreateLaserDownEnemy(1, 58, 8);
    CreateLaserDownEnemy(2, 107, 11);
    CreateLaserDownEnemy(3, 110, 11);
    CreateLaserDownEnemy(4, 111, 11);
    CreateLaserDownEnemy(5, 115, 11);
    CreateLaserDownEnemy(8, 118, 11);
    CreateLaserDownEnemy(9, 120, 11);
    CreateLaserDownEnemy(12, 123, 11);
    CreateLaserDownEnemy(13, 125, 11);
    CreateLaserDownEnemy(14, 126, 11);
    CreateLaserDownEnemy(15, 128, 11);
    CreateLaserDownEnemy(16, 129, 11);
    CreateLaserDownEnemy(17, 131, 11);
    CreateLaserDownEnemy(20, 136, 11);
    CreateLaserDownEnemy(22, 138, 11);
    CreateLaserDownEnemy(23, 140, 11);




    CreateLaserLeftEnemy(0, 71, 6);
    CreateLaserLeftEnemy(1, 73, 15);
    CreateLaserLeftEnemy(2, 87, 25);
    CreateLaserLeftEnemy(3, 98, 26);
    CreateLaserLeftEnemy(4, 105, 27);
    CreateLaserLeftEnemy(5, 106, 28);
    CreateLaserLeftEnemy(6, 171, 12);
    CreateLaserLeftEnemy(9, 171, 15);
    CreateLaserLeftEnemy(10, 171, 16);


    CreatePistoletDownEnemy(0, 50, 8);
    CreatePistoletDownEnemy(1, 54, 8);

    CreatePistoletLeftEnemy(0, 72, 9);
    CreatePistoletLeftEnemy(1, 74, 12);
    CreatePistoletLeftEnemy(2, 107, 29);
    CreatePistoletLeftEnemy(3, 107, 30);


    CreateLaserRightEnemy(0, 41, 10);
    CreateLaserRightEnemy(1, 41, 13);
    CreateLaserRightEnemy(2, 61, 15);
    CreateLaserRightEnemy(5, 59, 29);
    CreateLaserRightEnemy(6, 59, 30);
    CreateLaserRightEnemy(7, 59, 31);
    CreateLaserRightEnemy(8, 21, 18);
    CreateLaserRightEnemy(9, 21, 19);
    CreateLaserRightEnemy(10, 21, 20);
    CreateLaserRightEnemy(11, 21, 21);
    CreateLaserRightEnemy(12, 106, 13);
    CreateLaserRightEnemy(13, 106, 15);
    CreateLaserRightEnemy(14, 106, 17);


    CreateLaserUpEnemy(1, 43, 14);
    CreateLaserUpEnemy(0, 118, 20);


    CheckpointArea(0, 67, 16);
    CheckpointArea(1, 67, 22);
    CheckpointArea(2, 103, 19);

    CreateStar(0, 64, 6);
    CreateStar(1, 124, 8);
    CreateStar(2, 151, 9);

    CreateHeart(0, 21, 24);
    CreateHeart(1, 22, 24);
    CreateHeart(2, 109, 30);
    CreateHeart(3, 110, 30);
    CreateHeart(4, 111, 8);
    CreateHeart(5, 124, 9);
    CreateHeart(6, 135, 8);
    CreateHeart(7, 153, 9);
    CreateHeart(8, 78, 18);
    CreateHeart(9, 88, 18);
    CreateHeart(10, 98, 18);


    CreateKey(2, 43, 10); // 0 i 1 cursed
    CreateKey(3, 23, 23);
    CreateKey(4, 111, 30);

    CreateDoor(0, 74, 19);
    CreateDoor(1, 82, 19);
    CreateDoor(2, 93, 19);

    FakeFinishArea(109, 9);
    FinishArea(165, 20);
}


void createEntitiesLevel3_1() {
    CreateDoor(2, 43, 10);
    CreateKey(2, 141, 22);
    CreateStar(0, 50, 6);
    CreateStar(1, 84, 5);
    CreateStar(2, 138, 6);
    CreateSwitch(0, 64, 7);
    CreateSwitch(1, 32, 11);
    CreateSwitch(2, 39, 19);
    CreateSwitch(3, 145, 21);
    CheckpointArea(0, 55, 7);
    FinishArea(108, 10);


    CreateFigerEnemy(0, 35, 5);
    CreateFigerEnemy(1, 47, 5);
    CreateFigerEnemy(2, 53, 5);
    CreateFigerEnemy(3, 61, 5);
    CreateFigerEnemy(4, 70, 5);
    CreateFigerEnemy(5, 79, 5);

    CreateFigerEnemy(6, 39, 6);
    CreateFigerEnemy(7, 62, 6);
    CreateFigerEnemy(8, 73, 6);
    CreateFigerEnemy(9, 86, 6);
    CreateFigerEnemy(369, 107, 6);
    CreateFigerEnemy(370, 108, 6);
    CreateFigerEnemy(371, 109, 6);
    CreateFigerEnemy(372, 110, 6);
    CreateFigerEnemy(373, 111, 6);
    CreateFigerEnemy(374, 112, 6);
    CreateFigerEnemy(375, 113, 6);
    CreateFigerEnemy(376, 114, 6);
    CreateFigerEnemy(377, 115, 6);
    CreateFigerEnemy(378, 116, 6);
    CreateFigerEnemy(379, 117, 6);
    CreateFigerEnemy(380, 118, 6);
    CreateFigerEnemy(381, 119, 6);
    CreateFigerEnemy(382, 120, 6);
    CreateFigerEnemy(383, 121, 6);
    CreateFigerEnemy(384, 122, 6);
    CreateFigerEnemy(385, 123, 6);
    CreateFigerEnemy(386, 124, 6);
    CreateFigerEnemy(387, 125, 6);
    CreateFigerEnemy(388, 126, 6);
    CreateFigerEnemy(389, 127, 6);





    CreateFigerEnemy(10, 34, 7);
    CreateFigerEnemy(11, 47, 7);
    CreateFigerEnemy(12, 60, 7);
    CreateFigerEnemy(13, 66, 7);
    CreateFigerEnemy(14, 76, 7);
    CreateFigerEnemy(15, 85, 7);
    CreateFigerEnemy(367, 107, 7);
    CreateFigerEnemy(368, 127, 7);




    CreateFigerEnemyReverse(16, 35, 8);
    CreateFigerEnemyReverse(17, 36, 8);
    CreateFigerEnemyReverse(18, 37, 8);
    CreateFigerEnemyReverse(19, 38, 8);
    CreateFigerEnemyReverse(20, 39, 8);
    CreateFigerEnemyReverse(21, 40, 8);
    CreateFigerEnemyReverse(22, 67, 8);
    CreateFigerEnemyReverse(23, 68, 8);
    CreateFigerEnemyReverse(24, 69, 8);
    CreateFigerEnemyReverse(25, 70, 8);
    CreateFigerEnemy(357, 107, 8);
    CreateFigerEnemy(358, 108, 8);
    CreateFigerEnemy(359, 109, 8);
    CreateFigerEnemy(360, 110, 8);
    CreateFigerEnemy(361, 111, 8);
    CreateFigerEnemy(362, 112, 8);
    CreateFigerEnemy(363, 113, 8);
    CreateFigerEnemy(364, 114, 8);
    CreateFigerEnemy(365, 115, 8);
    CreateFigerEnemy(366, 127, 8);




    CreateFigerEnemyReverse(26, 32, 9);
    CreateFigerEnemyReverse(27, 33, 9);
    CreateFigerEnemyReverse(28, 34, 9);
    CreateFigerEnemyReverse(29, 35, 9);
    CreateFigerEnemyReverse(30, 36, 9);
    CreateFigerEnemyReverse(31, 37, 9);
    CreateFigerEnemyReverse(32, 38, 9);
    CreateFigerEnemyReverse(33, 39, 9);
    CreateFigerEnemyReverse(34, 40, 9);
    CreateFigerEnemyReverse(35, 41, 9);
    CreateFigerEnemyReverse(36, 42, 9);
    CreateFigerEnemy(344, 59, 9);
    CreateFigerEnemy(345, 60, 9);
    CreateFigerEnemy(346, 61, 9);
    CreateFigerEnemy(347, 62, 9);
    CreateFigerEnemy(348, 63, 9);
    CreateFigerEnemy(349, 64, 9);
    CreateFigerEnemy(350, 65, 9);
    CreateFigerEnemy(351, 66, 9);
    CreateFigerEnemy(352, 73, 9);
    CreateFigerEnemy(353, 88, 9);
    CreateFigerEnemy(354, 95, 9);
    CreateFigerEnemy(355, 115, 9);
    CreateFigerEnemy(356, 127, 9);




    CreateFigerEnemyReverse(37, 32, 10);
    CreateFigerEnemyReverse(38, 33, 10);
    CreateFigerEnemyReverse(39, 34, 10);
    CreateFigerEnemyReverse(40, 35, 10);
    CreateFigerEnemyReverse(41, 36, 10);
    CreateFigerEnemyReverse(42, 37, 10);
    CreateFigerEnemyReverse(43, 38, 10);
    CreateFigerEnemyReverse(44, 39, 10);
    CreateFigerEnemyReverse(45, 40, 10);
    CreateFigerEnemy(304, 44, 10);
    CreateFigerEnemy(305, 45, 10);
    CreateFigerEnemy(306, 46, 10);
    CreateFigerEnemy(307, 47, 10);
    CreateFigerEnemy(308, 49, 10);
    CreateFigerEnemy(309, 50, 10);
    CreateFigerEnemy(310, 51, 10);
    CreateFigerEnemy(311, 52, 10);
    CreateFigerEnemy(312, 53, 10);
    CreateFigerEnemy(313, 56, 10);
    CreateFigerEnemy(314, 63, 10);
    CreateFigerEnemy(315, 80, 10);
    CreateFigerEnemy(316, 81, 10);
    CreateFigerEnemy(317, 82, 10);
    CreateFigerEnemy(318, 83, 10);
    CreateFigerEnemy(319, 84, 10);
    CreateFigerEnemy(320, 85, 10);
    CreateFigerEnemy(321, 86, 10);
    CreateFigerEnemy(322, 87, 10);
    CreateFigerEnemy(323, 88, 10);
    CreateFigerEnemy(324, 89, 10);
    CreateFigerEnemy(325, 90, 10);
    CreateFigerEnemy(326, 91, 10);
    CreateFigerEnemy(327, 92, 10);
    CreateFigerEnemy(328, 93, 10);
    CreateFigerEnemy(329, 94, 10);
    CreateFigerEnemy(330, 95, 10);
    CreateFigerEnemy(331, 96, 10);
    CreateFigerEnemy(332, 97, 10);
    CreateFigerEnemy(333, 98, 10);
    CreateFigerEnemy(334, 99, 10);
    CreateFigerEnemy(335, 100, 10);
    CreateFigerEnemy(336, 101, 10);
    CreateFigerEnemy(337, 102, 10);
    CreateFigerEnemyReverse(338, 104, 10);
    CreateFigerEnemyReverse(339, 105, 10);
    CreateFigerEnemyReverse(340, 106, 10);
    CreateFigerEnemyReverse(341, 107, 10);
    CreateFigerEnemy(342, 115, 10);
    CreateFigerEnemy(343, 127, 10);


    CreateFigerEnemy(46, 35, 11);
    CreateFigerEnemy(47, 39, 11);
    CreateFigerEnemyReverse(48, 42, 11);
    CreateFigerEnemy(294, 53, 11);
    CreateFigerEnemy(295, 62, 11);
    CreateFigerEnemy(296, 63, 11);
    CreateFigerEnemy(297, 64, 11);
    CreateFigerEnemy(298, 65, 11);
    CreateFigerEnemy(299, 71, 11);
    CreateFigerEnemy(300, 80, 11);
    CreateFigerEnemy(301, 95, 11);
    CreateFigerEnemy(302, 115, 11);
    CreateFigerEnemy(303, 127, 11);





    CreateFigerEnemy(272, 53, 12);
    CreateFigerEnemy(273, 57, 12);
    CreateFigerEnemy(274, 66, 12);
    CreateFigerEnemy(275, 80, 12);
    CreateFigerEnemy(276, 115, 12);
    CreateFigerEnemy(277, 119, 12);
    CreateFigerEnemy(278, 120, 12);
    CreateFigerEnemy(279, 121, 12);
    CreateFigerEnemy(280, 122, 12);
    CreateFigerEnemy(281, 123, 12);
    CreateFigerEnemy(282, 124, 12);
    CreateFigerEnemy(283, 125, 12);
    CreateFigerEnemy(284, 126, 12);
    CreateFigerEnemy(285, 127, 12);
    CreateFigerEnemy(286, 128, 12);
    CreateFigerEnemy(287, 129, 12);
    CreateFigerEnemy(288, 130, 12);
    CreateFigerEnemy(289, 131, 12);
    CreateFigerEnemy(290, 132, 12);
    CreateFigerEnemy(291, 133, 12);
    CreateFigerEnemy(292, 134, 12);
    CreateFigerEnemy(293, 135, 12);



    CreateFigerEnemy(245, 47, 13);
    CreateFigerEnemy(246, 53, 13);
    CreateFigerEnemy(247, 65, 13);
    CreateFigerEnemy(248, 72, 13);
    CreateFigerEnemy(249, 80, 13);
    CreateFigerEnemy(250, 81, 13);
    CreateFigerEnemy(251, 82, 13);
    CreateFigerEnemy(252, 83, 13);
    CreateFigerEnemy(253, 84, 13);
    CreateFigerEnemy(254, 85, 13);
    CreateFigerEnemy(255, 86, 13);
    CreateFigerEnemy(256, 87, 13);
    CreateFigerEnemy(257, 88, 13);
    CreateFigerEnemy(258, 89, 13);
    CreateFigerEnemy(259, 90, 13);
    CreateFigerEnemy(260, 91, 13);
    CreateFigerEnemy(261, 93, 13);
    CreateFigerEnemy(262, 94, 13);
    CreateFigerEnemy(263, 95, 13);
    CreateFigerEnemy(264, 96, 13);
    CreateFigerEnemy(265, 97, 13);
    CreateFigerEnemy(266, 98, 13);
    CreateFigerEnemy(267, 99, 13);
    CreateFigerEnemy(268, 100, 13);
    CreateFigerEnemy(269, 115, 13);
    CreateFigerEnemy(270, 119, 13);
    CreateFigerEnemy(271, 135, 13);


    CreateFigerEnemy(234, 53, 14);
    CreateFigerEnemy(235, 62, 14);
    CreateFigerEnemy(236, 65, 14);
    CreateFigerEnemy(237, 67, 14);
    CreateFigerEnemy(238, 80, 14);
    CreateFigerEnemy(239, 85, 14);
    CreateFigerEnemy(240, 95, 14);
    CreateFigerEnemyReverse(241, 104, 14);
    CreateFigerEnemy(242, 115, 14);
    CreateFigerEnemy(243, 119, 14);
    CreateFigerEnemy(244, 135, 14);


    CreateFigerEnemy(225, 53, 15);
    CreateFigerEnemy(226, 58, 15);
    CreateFigerEnemy(391, 80, 15);
    CreateFigerEnemy(228, 92, 15);
    CreateFigerEnemy(229, 95, 15);
    CreateFigerEnemyReverse(230, 104, 15);
    CreateFigerEnemy(231, 115, 15);
    CreateFigerEnemy(232, 119, 15);
    CreateFigerEnemy(233, 135, 15);




    CreateFigerEnemy(202, 53, 16);
    CreateFigerEnemy(203, 63, 16);
    CreateFigerEnemy(204, 67, 16);
    CreateFigerEnemy(205, 74, 16);
    CreateFigerEnemy(206, 84, 16);
    CreateFigerEnemy(207, 95, 16);
    CreateFigerEnemy(208, 99, 16);
    CreateFigerEnemyReverse(209, 104, 16);
    CreateFigerEnemy(210, 108, 16);
    CreateFigerEnemy(211, 109, 16);
    CreateFigerEnemy(212, 110, 16);
    CreateFigerEnemy(213, 111, 16);
    CreateFigerEnemy(214, 112, 16);
    CreateFigerEnemy(215, 113, 16);
    CreateFigerEnemy(216, 114, 16);
    CreateFigerEnemy(217, 115, 16);
    CreateFigerEnemy(218, 116, 16);
    CreateFigerEnemy(219, 117, 16);
    CreateFigerEnemy(220, 118, 16);
    CreateFigerEnemy(221, 119, 16);
    CreateFigerEnemy(222, 120, 16);
    CreateFigerEnemy(223, 121, 16);
    CreateFigerEnemy(224, 135, 16);



    CreateFigerEnemy(196, 46, 17);
    CreateFigerEnemy(197, 53, 17);
    CreateFigerEnemy(198, 80, 17);
    CreateFigerEnemy(199, 95, 17);
    CreateFigerEnemy(200, 108, 17);
    CreateFigerEnemy(201, 135, 17);


    CreateFigerEnemy(157, 53, 18);
    CreateFigerEnemy(158, 54, 18);
    CreateFigerEnemy(159, 55, 18);
    CreateFigerEnemy(160, 56, 18);
    CreateFigerEnemy(161, 57, 18);
    CreateFigerEnemy(162, 58, 18);
    CreateFigerEnemy(163, 59, 18);
    CreateFigerEnemy(164, 60, 18);
    CreateFigerEnemy(165, 61, 18);
    CreateFigerEnemy(166, 62, 18);
    CreateFigerEnemy(167, 63, 18);
    CreateFigerEnemy(168, 64, 18);
    CreateFigerEnemy(169, 65, 18);
    CreateFigerEnemy(170, 66, 18);
    CreateFigerEnemy(171, 67, 18);
    CreateFigerEnemy(172, 68, 18);
    CreateFigerEnemy(173, 69, 18);
    CreateFigerEnemy(174, 70, 18);
    CreateFigerEnemy(175, 71, 18);
    CreateFigerEnemy(176, 72, 18);
    CreateFigerEnemy(177, 73, 18);
    CreateFigerEnemy(178, 74, 18);
    CreateFigerEnemy(179, 75, 18);
    CreateFigerEnemy(180, 76, 18);
    CreateFigerEnemy(181, 77, 18);
    CreateFigerEnemy(182, 78, 18);
    CreateFigerEnemy(183, 79, 18);
    CreateFigerEnemy(184, 80, 18);
    CreateFigerEnemy(185, 81, 18);
    CreateFigerEnemy(186, 82, 18);
    CreateFigerEnemy(187, 83, 18);
    CreateFigerEnemy(188, 84, 18);
    CreateFigerEnemy(189, 85, 18);
    CreateFigerEnemy(190, 86, 18);
    CreateFigerEnemy(191, 95, 18);
    CreateFigerEnemy(192, 100, 18);
    CreateFigerEnemy(193, 108, 18);
    CreateFigerEnemy(194, 135, 18);
    CreateFigerEnemyReverse(195, 139, 18);




    CreateFigerEnemyReverse(49, 43, 19);
    CreateFigerEnemy(129, 49, 19);
    CreateFigerEnemy(130, 58, 19);
    CreateFigerEnemy(132, 83, 19);
    CreateFigerEnemy(133, 86, 19);
    CreateFigerEnemy(134, 95, 19);
    CreateFigerEnemy(135, 96, 19);
    CreateFigerEnemy(136, 97, 19);
    CreateFigerEnemy(137, 98, 19);
    CreateFigerEnemy(138, 99, 19);
    CreateFigerEnemy(139, 101, 19);
    CreateFigerEnemy(140, 102, 19);
    CreateFigerEnemy(141, 108, 19);
    CreateFigerEnemy(142, 121, 19);
    CreateFigerEnemy(143, 122, 19);
    CreateFigerEnemy(144, 123, 19);
    CreateFigerEnemy(145, 124, 19);
    CreateFigerEnemy(146, 125, 19);
    CreateFigerEnemy(147, 126, 19);
    CreateFigerEnemy(148, 127, 19);
    CreateFigerEnemy(149, 128, 19);
    CreateFigerEnemy(150, 129, 19);
    CreateFigerEnemy(151, 130, 19);
    CreateFigerEnemy(152, 131, 19);
    CreateFigerEnemy(153, 132, 19);
    CreateFigerEnemy(154, 133, 19);
    CreateFigerEnemy(155, 134, 19);
    CreateFigerEnemy(156, 135, 19);

    CreateFigerEnemy(122, 65, 20);
    CreateFigerEnemy(123, 72, 20);
    CreateFigerEnemy(124, 92, 20);
    CreateFigerEnemy(125, 102, 20);
    CreateFigerEnemy(126, 108, 20);
    CreateFigerEnemy(127, 129, 20);
    CreateFigerEnemyReverse(128, 143, 20);

    CreateFigerEnemy(50, 43, 21);
    CreateFigerEnemy(51, 44, 21);
    CreateFigerEnemy(52, 45, 21);
    CreateFigerEnemy(53, 46, 21);
    CreateFigerEnemy(54, 47, 21);
    CreateFigerEnemy(55, 48, 21);
    CreateFigerEnemy(56, 49, 21);
    CreateFigerEnemy(57, 50, 21);
    CreateFigerEnemy(58, 51, 21);
    CreateFigerEnemy(59, 52, 21);
    CreateFigerEnemy(60, 53, 21);
    CreateFigerEnemy(61, 54, 21);
    CreateFigerEnemy(62, 55, 21);
    CreateFigerEnemy(63, 56, 21);
    CreateFigerEnemy(64, 57, 21);
    CreateFigerEnemy(65, 58, 21);
    CreateFigerEnemy(66, 59, 21);
    CreateFigerEnemy(67, 60, 21);
    CreateFigerEnemy(68, 61, 21);
    CreateFigerEnemy(69, 62, 21);
    CreateFigerEnemy(70, 63, 21);
    CreateFigerEnemy(71, 64, 21);
    CreateFigerEnemy(72, 65, 21);
    CreateFigerEnemy(73, 66, 21);
    CreateFigerEnemy(74, 67, 21);
    CreateFigerEnemy(75, 68, 21);
    CreateFigerEnemy(76, 69, 21);
    CreateFigerEnemy(77, 70, 21);
    CreateFigerEnemy(78, 71, 21);
    CreateFigerEnemy(79, 72, 21);
    CreateFigerEnemy(80, 73, 21);
    CreateFigerEnemy(81, 74, 21);
    CreateFigerEnemy(82, 75, 21);
    CreateFigerEnemy(83, 76, 21);
    CreateFigerEnemy(84, 77, 21);
    CreateFigerEnemy(85, 78, 21);
    CreateFigerEnemy(86, 79, 21);
    CreateFigerEnemy(87, 80, 21);
    CreateFigerEnemy(88, 82, 21);
    CreateFigerEnemy(89, 82, 21);
    CreateFigerEnemy(90, 83, 21);
    CreateFigerEnemy(91, 84, 21);
    CreateFigerEnemy(92, 85, 21);
    CreateFigerEnemy(93, 86, 21);

    CreateFigerEnemy(94, 94, 21);
    CreateFigerEnemy(95, 102, 21);
    CreateFigerEnemy(96, 103, 21);
    CreateFigerEnemy(97, 104, 21);
    CreateFigerEnemy(98, 105, 21);
    CreateFigerEnemy(99, 106, 21);
    CreateFigerEnemy(100, 107, 21);
    CreateFigerEnemy(101, 108, 21);
    CreateFigerEnemy(102, 129, 21);

    CreateFigerEnemy(103, 129, 22);

    CreateFigerEnemy(104, 129, 23);

    CreateFigerEnemy(105, 129, 24);
    CreateFigerEnemy(106, 130, 24);
    CreateFigerEnemy(107, 131, 24);
    CreateFigerEnemy(108, 132, 24);
    CreateFigerEnemy(109, 133, 24);
    CreateFigerEnemy(110, 134, 24);
    CreateFigerEnemy(111, 135, 24);
    CreateFigerEnemy(112, 136, 24);
    CreateFigerEnemy(113, 137, 24);
    CreateFigerEnemy(114, 138, 24);
    CreateFigerEnemy(115, 139, 24);
    CreateFigerEnemy(116, 140, 24);
    CreateFigerEnemy(117, 141, 24);
    CreateFigerEnemy(118, 142, 24);
    CreateFigerEnemy(119, 143, 24);
    CreateFigerEnemy(120, 144, 24);
    CreateFigerEnemy(121, 145, 24);

}

void createEntitiesLevel3_2() {
    CreateDoor(2, 56, 14);
    CreateKey(2, 49, 31);
    CreateStar(0, 70, 14);
    CreateStar(1, 21, 8);
    CreateStar(2, 111, 10);
    CreateHeart(0, 68, 14);
    CreateSwitch(0, 50, 3);
    CreateSwitch(1, 13, 8);
    CreateSwitch(2, 49, 27);
    CreateBox(0, 82, 10);
    CreateBox(1, 30, 17);
    CheckpointArea(0, 93, 14);
    FinishArea(54, 5);

    CreateFigerEnemy(0, 8, 5);
    CreateFigerEnemy(1, 9, 5);
    CreateFigerEnemy(2, 10, 5);
    CreateFigerEnemy(3, 11, 5);
    CreateFigerEnemyReverse(4, 13, 5);
    CreateFigerEnemyReverse(5, 14, 5);
    CreateFigerEnemyReverse(6, 15, 5);
    CreateFigerEnemyReverse(7, 16, 5);
    CreateFigerEnemyReverse(8, 17, 5);
    CreateFigerEnemyReverse(9, 18, 5);
    CreateFigerEnemyReverse(10, 19, 5);
    CreateFigerEnemyReverse(11, 20, 5);
    CreateFigerEnemyReverse(12, 21, 5);
    CreateFigerEnemyReverse(13, 22, 5);
    CreateFigerEnemy(16, 63, 5);
    CreateFigerEnemy(17, 86, 5);
    CreateFigerEnemyReverse(18, 12, 6);
    CreateFigerEnemy(19, 33, 6);
    CreateFigerEnemy(20, 44, 6);
    CreateFigerEnemy(21, 77, 6);
    CreateFigerEnemy(22, 66, 7);
    CreateFigerEnemy(23, 85, 7);
    CreateFigerEnemyReverse(24, 10, 8);
    CreateFigerEnemy(25, 40, 9);
    CreateFigerEnemy(26, 72, 9);
    CreateFigerEnemyReverse(27, 65, 9);
    CreateFigerEnemy(28, 102, 9);
    CreateFigerEnemy(29, 24, 10);
    CreateFigerEnemyReverse(30, 31, 10);
    CreateFigerEnemy(32, 39, 11);
    CreateFigerEnemy(33, 57, 11);
    CreateFigerEnemy(35, 79, 12);
    CreateFigerEnemy(36, 97, 12);
    CreateFigerEnemyReverse(37, 66, 12);
    CreateFigerEnemy(38, 96, 13);
    CreateFigerEnemy(39, 105, 13);
    CreateFigerEnemyReverse(40, 58, 16);
    CreateFigerEnemyReverse(41, 46, 17);
    CreateFigerEnemyReverse(42, 36, 18);
    CreateFigerEnemyReverse(43, 40, 19);
    CreateFigerEnemyReverse(44, 67, 19);
    CreateFigerEnemyReverse(45, 60, 20);
    CreateFigerEnemyReverse(46, 68, 24);
    CreateFigerEnemyReverse(47, 60, 27);
    CreateFigerEnemyReverse(48, 57, 28);
    CreateFigerEnemy(49, 55, 29);
    CreateFigerEnemy(50, 56, 29);
    CreateFigerEnemyReverse(51, 73, 13);
    CreateFigerEnemyReverse(52, 74, 13);
    CreateFigerEnemyReverse(53, 75, 13);
    CreateFigerEnemyReverse(54, 46, 14);

    CreateLaserDownEnemy(0, 96, 5);
    CreateLaserDownEnemy(1, 105, 5);
    CreateLaserDownEnemy(2, 29, 6);
    CreateLaserDownEnemy(4, 42, 6);
    CreateLaserDownEnemy(5, 50, 6);


    CreateLaserLeftEnemy(0, 52, 4);
    CreateLaserLeftEnemy(1, 107, 6);
    CreateLaserLeftEnemy(2, 71, 16);
    CreateLaserLeftEnemy(3, 87, 11);

    CreateLaserRightEnemy(0, 24, 8);
    CreateLaserRightEnemy(1, 8, 10);
    CreateLaserRightEnemy(4, 94, 10);
    CreateLaserRightEnemy(5, 29, 20);
    CreateLaserRightEnemy(6, 49, 26);
    CreateLaserRightEnemy(7, 49, 30);



    CreatePistoletDownEnemy(0, 23, 9);
    CreatePistoletDownEnemy(1, 27, 6);
    CreatePistoletDownEnemy(2, 36, 6);
    CreatePistoletDownEnemy(4, 48, 6);
    CreatePistoletDownEnemy(5, 52, 6);
    CreatePistoletDownEnemy(6, 54, 8);

    CreatePistoletLeftEnemy(0, 107, 8);
    CreatePistoletLeftEnemy(1, 71, 18);

    CreatePistoletLeftEnemy(0, 29, 19);

    CreatePistoletUpEnemy(0, 50, 20);
    CreatePistoletUpEnemy(1, 69, 28);


}

void createEntitiesLevel3_3() {
    CreateDoorDifferent(0, 32, 9);
    CreateKeyDifferent(0, 19, 18);
    CreateKeyDifferent(1, 148, 19);
    CreateKeyDifferent(2, 12, 26);
    CreateStar(0, 73, 30);
    CreateStar(1, 19, 15);
    CreateStar(2, 103, 12);
    CreateSwitch(0, 25, 15);
    CheckpointArea(0, 26, 18);
    CreateHeart(0, 19, 16);
    CreateHeart(1, 20, 16);
    CreateHeart(2, 147, 19);
    CreateHeart(5, 72, 30);
    CreateBox(0, 67, 28);
    CreateBox(1, 67, 29);

    CreateFigerEnemyReverse(0, 65, 30);
    CreateFigerEnemyReverse(1, 69, 30);
    CreateFigerEnemyReverse(2, 56, 28);
    CreateFigerEnemyReverse(3, 61, 27);
    CreateFigerEnemyReverse(4, 64, 25);
    CreateFigerEnemyReverse(5, 50, 26);
    CreateFigerEnemyReverse(6, 42, 27);
    CreateFigerEnemyReverse(7, 41, 25);
    CreateFigerEnemyReverse(8, 33, 27);
    CreateFigerEnemyReverse(9, 26, 25);
    CreateFigerEnemyReverse(10, 14, 27);
    CreateFigerEnemyReverse(11, 37, 21);
    CreateFigerEnemyReverse(12, 47, 20);
    CreateFigerEnemyReverse(13, 48, 22);
    CreateFigerEnemyReverse(14, 58, 21);
    CreateFigerEnemyReverse(15, 25, 19);
    CreateFigerEnemyReverse(16, 80, 22);
    CreateFigerEnemyReverse(17, 84, 20);
    CreateFigerEnemyReverse(18, 96, 23);
    CreateFigerEnemyReverse(19, 106, 23);
    CreateFigerEnemyReverse(20, 118, 23);
    CreateFigerEnemyReverse(21, 126, 22);
    CreateFigerEnemyReverse(22, 114, 20);
    CreateFigerEnemyReverse(23, 113, 18);
    CreateFigerEnemyReverse(24, 124, 18);
    CreateFigerEnemyReverse(25, 51, 13);
    CreateFigerEnemyReverse(26, 61, 13);
    CreateFigerEnemyReverse(27, 32, 14);
    CreateFigerEnemyReverse(28, 34, 17);
    CreateFigerEnemyReverse(29, 46, 15);
    CreateFigerEnemyReverse(30, 48, 17);
    CreateFigerEnemyReverse(31, 70, 17);
    CreateFigerEnemyReverse(32, 72, 15);
    CreateFigerEnemyReverse(33, 83, 18);
    CreateFigerEnemyReverse(34, 95, 14);
    CreateFigerEnemyReverse(35, 100, 17);
    CreateFigerEnemyReverse(36, 98, 11);

    CreatePistoletDownEnemy(0, 54, 24);
    CreatePistoletDownEnemy(1, 59, 24);
    CreatePistoletDownEnemy(2, 19, 25);
    CreatePistoletDownEnemy(3, 119, 18);

    CreatePistoletRightEnemy(0, 33, 8);
    CreatePistoletRightEnemy(1, 33, 10);
    CreatePistoletRightEnemy(2, 51, 8);
    CreatePistoletRightEnemy(3, 65, 10);
    CreatePistoletRightEnemy(4, 27, 14);
    CreatePistoletRightEnemy(6, 84, 24);

    CreatePistoletLeftEnemy(0, 128, 24);
    CreatePistoletLeftEnemy(1, 97, 9);
    CreatePistoletLeftEnemy(2, 97, 12);
    CreatePistoletLeftEnemy(3, 105, 16);



    CreateLaserLeftEnemy(0, 68, 25);
    CreateLaserLeftEnemy(1, 68, 27);
    CreateLaserLeftEnemy(2, 97, 8);
    CreateLaserLeftEnemy(3, 97, 10);
    CreateLaserLeftEnemy(4, 105, 15);
    CreateLaserLeftEnemy(5, 128, 21);

    CreateLaserRightEnemy(0, 22, 20);
    CreateLaserRightEnemy(1, 70, 23);

    CreateLaserDownEnemy(0, 108, 18);
    CreateLaserDownEnemy(1, 29, 12);
    CreateLaserDownEnemy(2, 37, 12);
    CreateLaserDownEnemy(4, 140, 15);
    CreateLaserDownEnemy(5, 143, 15);
    CreateLaserDownEnemy(6, 145, 15);



    FinishArea(28, 9);
}

void createEntitiesLevel3_4() {
    CreateDoor(2, 94, 21);
    CreateDoor(3, 74, 19);
    CreateKey(2, 138, 21);
    CreateKey(3, 123, 18);
    CreateHeart(0, 65, 27);
    CreateHeart(1, 77, 27);
    CreateKeyDifferent(2, 30, 8);
    CreateKeyDifferent(3, 63, 11);
    CreateKeyDifferent(4, 93, 8);
    CreateDoorDifferent(0, 94, 17);
    CreateStar(0, 57, 5);
    CreateStar(1, 105, 16);
    CreateStar(2, 101, 27);
    CreateSwitch(0, 101, 24);
    CheckpointArea(0, 93, 21);
    FinishArea(93, 19);

    CreateLaserDownEnemy(0, 59, 3);
    CreateLaserDownEnemy(1, 60, 3);
    CreateLaserDownEnemy(2, 66, 21);
    CreateLaserDownEnemy(3, 53, 11);



    CreateLaserLeftEnemy(2, 93, 15);
    CreateLaserLeftEnemy(3, 93, 11);
    CreateLaserLeftEnemy(4, 74, 10);
    CreateLaserLeftEnemy(5, 136, 22);
    CreateLaserLeftEnemy(6, 92, 22);
    CreateLaserLeftEnemy(7, 93, 23);

    CreateLaserRightEnemy(0, 28, 9);
    CreateLaserRightEnemy(1, 28, 11);
    CreateLaserRightEnemy(4, 54, 10);
    CreateLaserRightEnemy(5, 43, 21);

    CreateLaserUpEnemy(0, 31, 14);
    CreateLaserUpEnemy(1, 37, 17);
    CreateLaserUpEnemy(2, 69, 17);
    CreateLaserUpEnemy(3, 82, 17);


    CreatePistoletUpEnemy(3, 39, 11);
    CreatePistoletUpEnemy(4, 95, 22);
    CreatePistoletUpEnemy(5, 100, 22);

    CreatePistoletDownEnemy(0, 46, 8);
    CreatePistoletDownEnemy(1, 67, 8);
    CreatePistoletDownEnemy(3, 39, 13);
    CreatePistoletDownEnemy(4, 134, 17);
    CreatePistoletDownEnemy(5, 136, 17);

    CreatePistoletRightEnemy(0, 40, 12);
    CreatePistoletRightEnemy(1, 43, 22);
    CreatePistoletRightEnemy(2, 43, 25);

    CreatePistoletLeftEnemy(0, 38, 12);
    CreatePistoletLeftEnemy(0, 93, 14);


    CreateFigerEnemyReverse(0, 40, 8);
    CreateFigerEnemy(1, 89, 8);
    CreateFigerEnemyReverse(2, 59, 7);
    CreateFigerEnemyReverse(3, 60, 7);
    CreateFigerEnemyReverse(4, 60, 9);
    CreateFigerEnemyReverse(5, 72, 9);
    CreateFigerEnemy(6, 36, 9);
    CreateFigerEnemyReverse(7, 88, 10);
    CreateFigerEnemyReverse(8, 32, 11);
    CreateFigerEnemy(9, 57, 12);
    CreateFigerEnemyReverse(10, 71, 12);
    CreateFigerEnemyReverse(11, 84, 12);
    CreateFigerEnemy(12, 45, 13);
    CreateFigerEnemy(13, 90, 13);
    CreateFigerEnemyReverse(14, 53, 14);
    CreateFigerEnemyReverse(15, 76, 14);
    CreateFigerEnemy(16, 68, 15);
    CreateFigerEnemyReverse(17, 39, 16);
    CreateFigerEnemyReverse(18, 84, 16);
    CreateFigerEnemy(19, 50, 16);
    CreateFigerEnemyReverse(20, 101, 16);
    CreateFigerEnemyReverse(21, 48, 17);
    CreateFigerEnemyReverse(22, 91, 17);
    CreateFigerEnemyReverse(23, 105, 18);
    CreateFigerEnemyReverse(24, 115, 18);
    CreateFigerEnemyReverse(25, 119, 18);
    CreateFigerEnemyReverse(26, 111, 19);
    CreateFigerEnemyReverse(27, 119, 19);
    CreateFigerEnemyReverse(28, 103, 20);
    CreateFigerEnemyReverse(29, 109, 20);
    CreateFigerEnemyReverse(30, 117, 20);
    CreateFigerEnemyReverse(31, 115, 21);
    CreateFigerEnemyReverse(32, 121, 21);
    CreateFigerEnemyReverse(33, 123, 21);
    CreateFigerEnemyReverse(34, 124, 21);
    CreateFigerEnemyReverse(35, 105, 22);
    CreateFigerEnemyReverse(36, 110, 22);
    CreateFigerEnemyReverse(37, 114, 22);
    CreateFigerEnemyReverse(38, 120, 22);
    CreateFigerEnemyReverse(39, 54, 22);
    CreateFigerEnemyReverse(40, 77, 22);
    CreateFigerEnemyReverse(41, 64, 24);
    CreateFigerEnemyReverse(42, 94, 24);
    CreateFigerEnemyReverse(43, 38, 25);
    CreateFigerEnemyReverse(44, 52, 25);
    CreateFigerEnemyReverse(45, 87, 25);
    CreateFigerEnemyReverse(46, 94, 25);
    CreateFigerEnemyReverse(47, 37, 26);
    CreateFigerEnemyReverse(48, 41, 26);
    CreateFigerEnemyReverse(48, 39, 27);
    CreateFigerEnemy(49, 49, 21);
    CreateFigerEnemy(50, 68, 22);
    CreateFigerEnemy(51, 86, 23);
    CreateFigerEnemy(52, 55, 24);
    CreateFigerEnemy(53, 71, 25);
    CreateFigerEnemy(54, 100, 26);




}

void createEntitiesLevel3_5() {
    CreateDoorDifferent(2, 88, 23);
    CreateKeyDifferent(0, 6, 10);
    CreateKeyDifferent(1, 73, 10);
    CreateKeyDifferent(2, 114, 18);
    CreateDoor(0, 95, 23);
    CreateDoor(1, 105, 23);
    CreateDoor(2, 118, 25);
    CreateKey(2, 71, 40);
    CreateKey(3, 31, 30);
    CreateKey(4, 147, 22);
    CreateHeart(0, 115, 23);
    CreateHeart(1, 120, 23);
    CreateHeart(2, 112, 10);
    CreateHeart(3, 112, 15);
    CreateStar(0, 110, 23);
    CreateStar(1, 142, 4);
    CreateStar(2, 29, 30);
    CreateSwitch(0, 112, 22);
    CheckpointArea(0, 100, 25);
    CheckpointArea(1, 121, 35);
    CheckpointArea(2, 118, 21);
    FinishArea(150, 7);

    CreateBox(0, 29, 29);
    CreateBox(1, 113, 38);
    CreateBox(2, 115, 39);
    CreateBox(3, 78, 11);
    CreateBox(4, 83, 11);
    CreateBox(5, 85, 13);
    CreateBox(6, 82, 15);
    CreateBox(7, 78, 16);
    CreateBox(8, 81, 17);

    CreateLaserDownEnemy(0, 10, 10);
    CreateLaserDownEnemy(1, 27, 10);
    CreateLaserDownEnemy(2, 37, 10);
    CreateLaserDownEnemy(3, 107, 7);
    CreateLaserDownEnemy(4, 108, 11);
    CreateLaserDownEnemy(7, 74, 39);
    CreateLaserDownEnemy(8, 94, 37);
    CreateLaserDownEnemy(9, 112, 26);
    CreateLaserDownEnemy(10, 115, 26);
    CreateLaserDownEnemy(11, 119, 26);
    CreateLaserDownEnemy(12, 121, 6);
    CreateLaserDownEnemy(13, 124, 22);
    CreateLaserDownEnemy(14, 132, 22);
    CreateLaserDownEnemy(15, 140, 22);
    CreateLaserDownEnemy(16, 151, 22);
    CreateLaserDownEnemy(17, 160, 22);
    CreateLaserDownEnemy(18, 165, 22);

    CreateLaserUpEnemy(0, 40, 18);
    CreateLaserUpEnemy(3, 107, 18);
    CreateLaserUpEnemy(4, 15, 17);

    CreateLaserLeftEnemy(0, 42, 12);
    CreateLaserLeftEnemy(1, 42, 15);
    CreateLaserLeftEnemy(4, 120, 41);
    CreateLaserLeftEnemy(5, 93, 35);
    CreateLaserLeftEnemy(6, 165, 32);
    CreateLaserLeftEnemy(7, 166, 26);


    CreateLaserRightEnemy(2, 76, 9);
    CreateLaserRightEnemy(4, 71, 32);
    CreateLaserRightEnemy(5, 123, 24);
    CreateLaserRightEnemy(6, 122, 33);

    CreatePistoletUpEnemy(0, 26, 18);
    CreatePistoletUpEnemy(1, 51, 18);
    CreatePistoletUpEnemy(3, 69, 18);
    CreatePistoletUpEnemy(5, 97, 18);
    CreatePistoletUpEnemy(6, 98, 16);
    CreatePistoletUpEnemy(7, 126, 35);
    CreatePistoletUpEnemy(8, 141, 35);
    CreatePistoletUpEnemy(9, 153, 35);
    CreatePistoletUpEnemy(10, 161, 35);

    CreatePistoletDownEnemy(0, 51, 9);
    CreatePistoletDownEnemy(1, 59, 9);
    CreatePistoletDownEnemy(2, 70, 9);
    CreatePistoletDownEnemy(4, 98, 7);
    CreatePistoletDownEnemy(5, 97, 11);
    CreatePistoletDownEnemy(6, 116, 6);
    CreatePistoletDownEnemy(7, 119, 6);
    CreatePistoletDownEnemy(8, 127, 6);

    CreatePistoletRightEnemy(0, 44, 12);
    CreatePistoletRightEnemy(2, 75, 38);
    CreatePistoletRightEnemy(3, 110, 30);
    CreatePistoletRightEnemy(4, 110, 32);
    CreatePistoletRightEnemy(5, 122, 28);
    CreatePistoletRightEnemy(6, 122, 31);
    CreatePistoletRightEnemy(7, 71, 28);
    CreatePistoletRightEnemy(8, 116, 14);

    CreatePistoletLeftEnemy(0, 74, 13);
    CreatePistoletLeftEnemy(1, 31, 27);
    CreatePistoletLeftEnemy(2, 129, 9);
    CreatePistoletLeftEnemy(3, 129, 20);

    CreateFigerEnemyReverse(0, 75, 29);
    CreateFigerEnemyReverse(1, 81, 30);
    CreateFigerEnemyReverse(2, 92, 32);
    CreateFigerEnemyReverse(3, 79, 35);
    CreateFigerEnemyReverse(4, 105, 37);
    CreateFigerEnemyReverse(5, 116, 37);
    CreateFigerEnemyReverse(6, 82, 39);
    CreateFigerEnemyReverse(7, 90, 40);
    CreateFigerEnemyReverse(8, 103, 40);
    CreateFigerEnemyReverse(9, 97, 27);
    CreateFigerEnemyReverse(10, 103, 27);
    CreateFigerEnemyReverse(11, 96, 29);
    CreateFigerEnemyReverse(12, 103, 30);
    CreateFigerEnemyReverse(13, 99, 31);
    CreateFigerEnemyReverse(14, 97, 33);
    CreateFigerEnemyReverse(15, 104, 33);
    CreateFigerEnemyReverse(16, 98, 34);
    CreateFigerEnemyReverse(17, 105, 35);
    CreateFigerEnemyReverse(18, 106, 35);
    CreateFigerEnemyReverse(19, 125, 20);
    CreateFigerEnemyReverse(20, 118, 19);
    CreateFigerEnemyReverse(21, 120, 18);
    CreateFigerEnemyReverse(22, 125, 18);
    CreateFigerEnemyReverse(23, 117, 16);
    CreateFigerEnemyReverse(24, 127, 16);
    CreateFigerEnemyReverse(25, 121, 15);
    CreateFigerEnemyReverse(26, 128, 15);
    CreateFigerEnemyReverse(27, 119, 13);
    CreateFigerEnemyReverse(28, 126, 13);
    CreateFigerEnemyReverse(29, 122, 12);
    CreateFigerEnemyReverse(30, 118, 11);
    CreateFigerEnemyReverse(31, 119, 10);
    CreateFigerEnemyReverse(32, 125, 10);
    CreateFigerEnemyReverse(33, 123, 8);
    CreateFigerEnemyReverse(34, 128, 8);
    CreateFigerEnemyReverse(35, 118, 7);
    CreateFigerEnemyReverse(36, 124, 6);

    CreateFigerEnemyReverse(37, 131, 6);
    CreateFigerEnemyReverse(38, 132, 6);
    CreateFigerEnemyReverse(39, 133, 6);
    CreateFigerEnemyReverse(40, 134, 6);
    CreateFigerEnemyReverse(41, 135, 6);
    CreateFigerEnemyReverse(42, 136, 6);
    CreateFigerEnemyReverse(43, 137, 6);
    CreateFigerEnemyReverse(44, 138, 6);
    CreateFigerEnemyReverse(45, 139, 6);
    CreateFigerEnemyReverse(46, 140, 6);
    CreateFigerEnemyReverse(47, 141, 6);
    CreateFigerEnemyReverse(48, 142, 6);
    CreateFigerEnemyReverse(49, 143, 6);
    CreateFigerEnemyReverse(50, 144, 6);
    CreateFigerEnemyReverse(51, 145, 6);
    CreateFigerEnemyReverse(52, 146, 6);
    CreateFigerEnemyReverse(53, 147, 6);
    CreateFigerEnemyReverse(54, 148, 6);
    CreateFigerEnemyReverse(55, 149, 6);
    CreateFigerEnemyReverse(56, 150, 6);
    CreateFigerEnemyReverse(57, 131, 8);
    CreateFigerEnemyReverse(58, 132, 8);
    CreateFigerEnemyReverse(59, 133, 8);
    CreateFigerEnemyReverse(60, 134, 8);
    CreateFigerEnemyReverse(61, 135, 8);
    CreateFigerEnemyReverse(62, 136, 8);
    CreateFigerEnemyReverse(63, 137, 8);
    CreateFigerEnemyReverse(64, 138, 8);
    CreateFigerEnemyReverse(65, 139, 8);
    CreateFigerEnemyReverse(66, 140, 8);
    CreateFigerEnemyReverse(67, 141, 8);
    CreateFigerEnemyReverse(68, 142, 8);
    CreateFigerEnemyReverse(69, 143, 8);
    CreateFigerEnemyReverse(70, 144, 8);
    CreateFigerEnemyReverse(71, 145, 8);
    CreateFigerEnemyReverse(72, 146, 8);
    CreateFigerEnemyReverse(73, 147, 8);
    CreateFigerEnemyReverse(74, 148, 8);
    CreateFigerEnemyReverse(75, 149, 8);
    CreateFigerEnemyReverse(76, 150, 8);



}


void createEntitiesLevel4_1() {
    CreateDoor(0, 21, 16);
    CreateDoor(1, 33, 17);

    CreateKey(2, 15, 23);
    CreateKey(3, 15, 10);


    CreateHeart(0, 15, 17);
    CreateHeart(1, 14, 26);
    CreateHeart(2, 118, 30);
    CreateHeart(3, 120, 31);

    CreateStar(0, 123, 30);
    CreateStar(1, 10, 24);
    CreateStar(2, 16, 9);

    CreateSwitch(0, 10, 17);
    CreateSwitch(1, 105, 22);

    FinishArea(11, 16);

    CreateBox(0, 24, 16);
    CreateBox(1, 25, 17);
    CreateBox(2, 29, 16);


    CreateFigerEnemyReverse(0, 36, 6);
    CreateFigerEnemyReverse(1, 75, 6);
    CreateFigerEnemyReverse(2, 29, 10);
    CreateFigerEnemyReverse(3, 63, 10);
    CreateFigerEnemyReverse(4, 45, 13);
    CreateFigerEnemyReverse(5, 88, 14);
    CreateFigerEnemyReverse(6, 43, 20);
    CreateFigerEnemyReverse(7, 81, 21);
    CreateFigerEnemyReverse(8, 26, 22);
    CreateFigerEnemyReverse(9, 60, 23);
    CreateFigerEnemyReverse(10, 84, 25);
    CreateFigerEnemyReverse(11, 29, 26);
    CreateFigerEnemyReverse(12, 82, 28);

    CreateFigerEnemy(0, 81, 29);
    CreateFigerEnemy(1, 82, 31);
    CreateFigerEnemy(2, 91, 31);
    CreateFigerEnemy(3, 105, 31);
    CreateFigerEnemy(4, 117, 31);
    CreateFigerEnemy(5, 112, 30);
    CreateFigerEnemy(6, 113, 23);
    CreateFigerEnemy(7, 100, 24);
    CreateFigerEnemy(8, 105, 24);
    CreateFigerEnemy(9, 112, 24);
    CreateFigerEnemy(10, 98, 26);
    CreateFigerEnemy(11, 109, 26);
    CreateFigerEnemy(12, 106, 27);
    CreateFigerEnemy(13, 97, 29);
    CreateFigerEnemy(14, 102, 29);
    CreateFigerEnemy(15, 108, 29);


    CreateRollSideEnemy(0, 48, 23);
    CreateRollSideEnemy(2, 81, 12);
    CreateRollSideEnemy(4, 66, 15);
    CreateRollSideEnemy(6, 35, 24);
    CreateRollSideEnemy(7, 112, 26);


    CreateRollUpEnemy(0, 12, 25);
    CreateRollUpEnemy(1, 25, 9);
    CreateRollUpEnemy(2, 44, 8);
    CreateRollUpEnemy(4, 15, 14);
    CreateRollUpEnemy(6, 78, 24);
    CreateRollUpEnemy(7, 105, 26);


}

void createEntitiesLevel4_2() {
    CreateDoor(0, 97, 17);
    CreateDoor(1, 101, 16);
    CreateDoorDifferent(1, 95, 25);

    CreateKeyDifferent(2, 40, 12);
    CreateKeyDifferent(3, 58, 15);
    CreateKeyDifferent(4, 94, 13);
    CreateKey(3, 15, 14);
    CreateKey(2, 52, 3);


    CreateHeart(0, 96, 7);
    CreateHeart(1, 98, 25);
    CreateHeart(2, 100, 25);

    CreateStar(0, 102, 25);
    CreateStar(1, 120, 25);
    CreateStar(2, 40, 5);

    CreateSwitch(0, 100, 7);

    FinishArea(110, 16);

    CreateBox(0, 16, 16);


    CreateFigerEnemyReverse(0, 47, 6);
    CreateFigerEnemyReverse(1, 16, 18);
    CreateFigerEnemyReverse(2, 9, 19);
    CreateFigerEnemyReverse(3, 11, 23);
    CreateFigerEnemyReverse(4, 17, 23);
    CreateFigerEnemyReverse(5, 18, 25);
    CreateFigerEnemyReverse(6, 26, 24);
    CreateFigerEnemyReverse(7, 37, 21);
    CreateFigerEnemyReverse(8, 37, 22);


    CreateRollSideEnemy(6, 79, 13);
    CreateRollSideEnemy(7, 53, 18);


    CreateRollSideEnemy(1, 14, 18);
    CreateRollUpEnemy(1, 23, 7);
    CreateRollSideEnemy(2, 66, 6);
    CreateRollUpEnemy(6, 38, 4);
    CreateRollUpEnemy(7, 70, 12);

    CreateLaserDownEnemy(0, 7, 8);
    CreateLaserDownEnemy(1, 11, 8);
    CreateLaserDownEnemy(2, 116, 24);

    CreatePistoletUpEnemy(0, 8, 25);
    CreatePistoletUpEnemy(1, 9, 25);

    CreatePistoletDownEnemy(0, 65, 18);
    CreatePistoletDownEnemy(1, 79, 18);

    CreatePistoletLeftEnemy(0, 42, 25);
    CreatePistoletRightEnemy(2, 63, 25);
    CreatePistoletRightEnemy(3, 78, 26);

    CreateLaserLeftEnemy(1, 110, 10);
    CreateLaserLeftEnemy(2, 113, 20);

    CreateLaserRightEnemy(0, 17, 9);
    CreateLaserRightEnemy(1, 13, 12);
    CreateLaserRightEnemy(2, 13, 15);
    CreateLaserRightEnemy(3, 24, 18);
    CreateLaserRightEnemy(4, 24, 19);
    CreatePistoletRightEnemy(1, 105, 19);


}

void createEntitiesLevel4_3() {
    CreateDoor(0, 96, 16);
    CreateDoorDifferent(1, 24, 20);

    CreateKeyDifferent(2, 25, 11);
    CreateKeyDifferent(3, 100, 15);
    CreateKeyDifferent(4, 94, 37);
    CreateKey(2, 26, 10);

    CreateHeart(0, 23, 22);
    CreateHeart(1, 24, 22);
    CreateHeart(2, 25, 22);
    CreateHeart(3, 107, 37);

    CreateStar(0, 98, 13);
    CreateStar(1, 9, 37);
    CreateStar(2, 80, 36);

    CreateSwitch(0, 55, 18);

    FinishArea(26, 11);

    CreateFigerEnemyReverse(0, 96, 17);
    CreateFigerEnemyReverse(1, 96, 18);

    CheckpointArea(0, 86, 14);
    CheckpointArea(1, 143, 25);

    CreateRollSideEnemy(0, 104, 30);
    CreateRollSideEnemy(1, 104, 34);
    CreateRollSideEnemy(2, 46, 7);
    CreateRollSideEnemy(3, 63, 9);

    CreateRollUpEnemy(0, 76, 7);
    CreateRollUpEnemy(1, 100, 31);
    CreateRollUpEnemy(2, 109, 33);

    CreateLaserDownEnemy(0, 38, 6);
    CreateLaserDownEnemy(1, 85, 10);
    CreateLaserDownEnemy(2, 45, 18);
    CreateLaserDownEnemy(3, 65, 18);

    CreatePistoletDownEnemy(0, 108, 18);
    CreatePistoletDownEnemy(1, 124, 18);
    CreatePistoletDownEnemy(2, 30, 6);

    CreatePistoletRightEnemy(0, 32, 23);


    CreateLaserLeftEnemy(0, 140, 21);
    CreateLaserLeftEnemy(1, 134, 36);

    CreateLaserRightEnemy(0, 39, 24);
    CreateLaserRightEnemy(1, 37, 14);


    CreateTeleport(0, 89, 32, 122, 32);
    CreateTeleport(1, 130, 38, 143, 27);
    CreateTeleport(2, 23, 18, 88, 14);
    CreateTeleport(3, 31, 21, 7, 37);


}

void createEntitiesLevel4_4() {
    CreateDoor(0, 77, 16);
    CreateDoorDifferent(1, 157, 33);

    CreateKeyDifferent(2, 109, 39);
    CreateKeyDifferent(3, 140, 6);
    CreateKeyDifferent(4, 116, 24);
    CreateKey(2, 21, 29);

    CreateStar(0, 105, 25);
    CreateStar(1, 22, 29);
    CreateStar(2, 79, 16);

    CreateSwitch(0, 112, 12);

    FinishArea(163, 32);

    CreateFigerEnemyReverse(0, 9, 6);
    CreateFigerEnemyReverse(1, 101, 25);
    CreateFigerEnemyReverse(2, 102, 25);
    CreateFigerEnemyReverse(3, 103, 25);
    CreateFigerEnemyReverse(4, 104, 25);

    CheckpointArea(0, 57, 27);

    CreateRollSideEnemy(0, 126, 39);

    CreateRollUpEnemy(0, 142, 19);
    CreateRollUpEnemy(1, 113, 16);
    CreateRollUpEnemy(2, 121, 12);
    CreateRollSideEnemy(3, 128, 15);

    CreateLaserDownEnemy(0, 94, 31);

    CreatePistoletDownEnemy(0, 147, 6);
    CreatePistoletDownEnemy(1, 152, 6);
    CreatePistoletDownEnemy(2, 160, 6);

    CreatePistoletUpEnemy(0, 134, 26);

    CreatePistoletRightEnemy(0, 139, 7);
    CreatePistoletRightEnemy(1, 139, 9);

    CreateLaserLeftEnemy(1, 81, 7);
    CreateLaserLeftEnemy(2, 76, 8);

    CreateLaserRightEnemy(0, 150, 24);

    CreateTeleport(0, 32, 15, 8, 6);
    CreateTeleport(1, 32, 17, 73, 16);
    CreateTeleport(2, 36, 15, 169, 11);
    CreateTeleport(3, 36, 17, 50, 7);
    CreateTeleport(4, 91, 7, 13, 21);
    CreateTeleport(5, 17, 23, 94, 39);
    CreateTeleport(6, 17, 21, 137, 32);
    CreateTeleport(7, 13, 23, 57, 28);
    CreateTeleport(8, 47, 28, 129, 43);
    CreateTeleport(9, 68, 28, 98, 25);
    CreateTeleport(10, 57, 31, 142, 21);
    CreateTeleport(11, 57, 24, 122, 17);
    CreateTeleport(12, 47, 24, 134, 24);
    CreateTeleport(13, 68, 24, 112, 24);
    CreateTeleport(14, 47, 31, 154, 24);
    CreateTeleport(15, 68, 31, 14, 29);

}

void createEntitiesLevel4_5() {
    CreateDoor(1, 69, 17);
    CreateDoorDifferent(5, 53, 7);
    CreateDoor(5, 71, 13);
    CreateDoor(6, 99, 17);
    CreateDoor(7, 75, 28);
    CreateDoor(8, 134, 38);
    CreateDoor(9, 111, 39);

    CreateHeart(0, 114, 6);
    CreateHeart(1, 14, 13);
    CreateHeart(2, 156, 17);
    CreateHeart(3, 157, 17);


    CreateKey(3, 66, 36);
    CreateKey(4, 65, 19);
    CreateKey(5, 38, 9);
    CreateKey(6, 99, 8);
    CreateKey(7, 84, 20);
    CreateKey(8, 143, 11);
    CreateKeyDifferent(2, 14, 12);
    CreateKeyDifferent(3, 15, 12);
    CreateKeyDifferent(4, 159, 19);

    CreateStar(0, 157, 15);
    CreateStar(1, 15, 13);
    CreateStar(2, 52, 6);

    CreateTheEnd(0, 151, 10);
    CreateTheEnd(1, 151, 11);
    CreateTheEnd(2, 151, 12);
    CreateTheEnd(3, 150, 10);
    CreateTheEnd(4, 150, 11);
    CreateTheEnd(5, 150, 12);

    CheckpointArea(0, 113, 6);
    CheckpointArea(1, 101, 18);
    CheckpointArea(2, 70, 18);

    CreateFigerEnemyReverse(0, 113, 10);
    CreateFigerEnemyReverse(1, 121, 12);
    CreateFigerEnemyReverse(2, 118, 15);
    CreateFigerEnemyReverse(3, 123, 15);
    CreateFigerEnemyReverse(4, 64, 18);
    CreateFigerEnemyReverse(5, 65, 18);
    CreateFigerEnemyReverse(6, 66, 18);
    CreateFigerEnemyReverse(7, 68, 18);
    CreateFigerEnemyReverse(8, 64, 19);
    CreateFigerEnemyReverse(9, 66, 19);
    CreateFigerEnemyReverse(10, 68, 19);
    CreateFigerEnemyReverse(11, 64, 20);
    CreateFigerEnemyReverse(12, 66, 20);
    CreateFigerEnemyReverse(14, 36, 21);
    CreateFigerEnemyReverse(15, 37, 21);
    CreateFigerEnemyReverse(16, 38, 21);
    CreateFigerEnemyReverse(17, 39, 21);
    CreateFigerEnemyReverse(18, 40, 21);
    CreateFigerEnemyReverse(19, 41, 21);
    CreateFigerEnemyReverse(20, 42, 21);
    CreateFigerEnemyReverse(21, 43, 21);
    CreateFigerEnemyReverse(22, 44, 21);
    CreateFigerEnemyReverse(23, 45, 21);
    CreateFigerEnemyReverse(24, 46, 21);
    CreateFigerEnemyReverse(25, 47, 21);
    CreateFigerEnemyReverse(26, 48, 21);
    CreateFigerEnemyReverse(27, 49, 21);
    CreateFigerEnemyReverse(28, 50, 21);
    CreateFigerEnemyReverse(29, 51, 21);
    CreateFigerEnemyReverse(30, 52, 21);
    CreateFigerEnemyReverse(31, 53, 21);
    CreateFigerEnemyReverse(32, 54, 21);
    CreateFigerEnemyReverse(33, 55, 21);
    CreateFigerEnemyReverse(34, 56, 21);
    CreateFigerEnemyReverse(35, 57, 21);
    CreateFigerEnemyReverse(36, 58, 21);
    CreateFigerEnemyReverse(37, 59, 21);
    CreateFigerEnemyReverse(38, 60, 21);
    CreateFigerEnemyReverse(39, 61, 21);
    CreateFigerEnemyReverse(40, 62, 21);
    CreateFigerEnemyReverse(41, 63, 21);
    CreateFigerEnemyReverse(42, 64, 21);
    CreateFigerEnemyReverse(43, 66, 21);
    CreateFigerEnemyReverse(44, 67, 21);
    CreateFigerEnemyReverse(45, 68, 21);
    CreateFigerEnemyReverse(46, 36, 22);
    CreateFigerEnemyReverse(47, 49, 22);
    CreateFigerEnemyReverse(48, 64, 22);
    CreateFigerEnemyReverse(49, 36, 23);
    CreateFigerEnemyReverse(50, 38, 23);
    CreateFigerEnemyReverse(51, 39, 23);
    CreateFigerEnemyReverse(52, 40, 23);
    CreateFigerEnemyReverse(53, 41, 23);
    CreateFigerEnemyReverse(54, 42, 23);
    CreateFigerEnemyReverse(55, 43, 23);
    CreateFigerEnemyReverse(56, 44, 23);
    CreateFigerEnemyReverse(57, 45, 23);
    CreateFigerEnemyReverse(58, 46, 23);
    CreateFigerEnemyReverse(59, 47, 23);
    CreateFigerEnemyReverse(60, 49, 23);
    CreateFigerEnemyReverse(61, 64, 23);
    CreateFigerEnemyReverse(62, 66, 23);
    CreateFigerEnemyReverse(63, 67, 23);
    CreateFigerEnemyReverse(64, 68, 23);
    CreateFigerEnemyReverse(65, 69, 23);
    CreateFigerEnemyReverse(66, 70, 23);
    CreateFigerEnemyReverse(67, 36, 24);
    CreateFigerEnemyReverse(68, 38, 24);
    CreateFigerEnemyReverse(69, 47, 24);
    CreateFigerEnemyReverse(70, 49, 24);
    CreateFigerEnemyReverse(71, 50, 24);
    CreateFigerEnemyReverse(72, 51, 24);
    CreateFigerEnemyReverse(73, 52, 24);
    CreateFigerEnemyReverse(74, 53, 24);
    CreateFigerEnemyReverse(75, 54, 24);
    CreateFigerEnemyReverse(76, 55, 24);
    CreateFigerEnemyReverse(77, 56, 24);
    CreateFigerEnemyReverse(78, 57, 24);
    CreateFigerEnemyReverse(79, 58, 24);
    CreateFigerEnemyReverse(80, 59, 24);
    CreateFigerEnemyReverse(81, 60, 24);
    CreateFigerEnemyReverse(82, 61, 24);
    CreateFigerEnemyReverse(83, 62, 24);
    CreateFigerEnemyReverse(84, 63, 24);
    CreateFigerEnemyReverse(85, 64, 24);
    CreateFigerEnemyReverse(86, 66, 24);
    CreateFigerEnemyReverse(87, 36, 25);
    CreateFigerEnemyReverse(88, 38, 25);
    CreateFigerEnemyReverse(89, 47, 25);
    CreateFigerEnemyReverse(90, 66, 25);
    CreateFigerEnemyReverse(93, 36, 26);
    CreateFigerEnemyReverse(94, 38, 26);
    CreateFigerEnemyReverse(95, 47, 26);
    CreateFigerEnemyReverse(96, 48, 26);
    CreateFigerEnemyReverse(97, 49, 26);
    CreateFigerEnemyReverse(98, 50, 26);
    CreateFigerEnemyReverse(99, 51, 26);
    CreateFigerEnemyReverse(100, 52, 26);
    CreateFigerEnemyReverse(101, 53, 26);
    CreateFigerEnemyReverse(102, 54, 26);
    CreateFigerEnemyReverse(103, 55, 26);
    CreateFigerEnemyReverse(104, 56, 26);
    CreateFigerEnemyReverse(105, 57, 26);
    CreateFigerEnemyReverse(106, 58, 26);
    CreateFigerEnemyReverse(107, 59, 26);
    CreateFigerEnemyReverse(108, 60, 26);
    CreateFigerEnemyReverse(109, 61, 26);
    CreateFigerEnemyReverse(110, 62, 26);
    CreateFigerEnemyReverse(111, 63, 26);
    CreateFigerEnemyReverse(112, 64, 26);
    CreateFigerEnemyReverse(113, 65, 26);
    CreateFigerEnemyReverse(114, 66, 26);
    CreateFigerEnemyReverse(91, 36, 27);
    CreateFigerEnemyReverse(92, 38, 27);

    CreateRollSideEnemy(1, 59, 29);
    CreateRollSideEnemy(2, 60, 18);
    CreateRollSideEnemy(4, 75, 35);
    CreateRollSideEnemy(6, 127, 9);
    CreateRollSideEnemy(7, 106, 14);
    CreateRollSideEnemy(8, 148, 29);
    CreateRollSideEnemy(9, 150, 18);

    CreateRollUpEnemy(0, 44, 31);
    CreateRollUpEnemy(1, 55, 37);
    CreateRollUpEnemy(2, 40, 19);
    CreateRollUpEnemy(3, 67, 20);
    CreateRollUpEnemy(4, 136, 15);
    CreateRollUpEnemy(6, 44, 40);
    CreatePistoletDownEnemy(0, 66, 40);
    CreatePistoletDownEnemy(1, 94, 40);
    CreatePistoletDownEnemy(2, 60, 8);
    CreatePistoletDownEnemy(3, 107, 18);
    CreatePistoletDownEnemy(4, 113, 18);
    CreatePistoletDownEnemy(5, 125, 18);

    CreatePistoletUpEnemy(0, 49, 16);
    CreatePistoletUpEnemy(1, 123, 27);

    CreatePistoletRightEnemy(0, 35, 14);
    CreatePistoletRightEnemy(1, 11, 41);
    CreatePistoletRightEnemy(2, 11, 42);

    CreatePistoletLeftEnemy(0, 101, 8);
    CreatePistoletLeftEnemy(1, 101, 9);
    CreatePistoletLeftEnemy(2, 101, 10);
    CreatePistoletLeftEnemy(3, 101, 11);
    CreatePistoletLeftEnemy(4, 101, 12);
    CreatePistoletLeftEnemy(5, 101, 14);
    CreatePistoletLeftEnemy(6, 101, 15);
    CreatePistoletLeftEnemy(7, 101, 16);
    CreatePistoletLeftEnemy(8, 133, 20);
    CreatePistoletLeftEnemy(9, 133, 24);
    CreatePistoletLeftEnemy(10, 133, 25);
    CreatePistoletLeftEnemy(11, 133, 26);
    CreatePistoletLeftEnemy(12, 133, 27);

    CreateLaserDownEnemy(0, 13, 12);
    CreateLaserDownEnemy(1, 38, 8);
    CreateLaserDownEnemy(2, 84, 18);
    CreateLaserDownEnemy(3, 93, 18);

    CreateLaserRightEnemy(6, 35, 33);

    CreateLaserUpEnemy(0, 115, 16);
    CreateLaserUpEnemy(1, 85, 27);
    CreateLaserUpEnemy(2, 97, 27);

    CreateLaserRightEnemy(1, 103, 22);

    CreateLaserRightEnemy(2, 72, 20);
    CreateLaserRightEnemy(4, 72, 24);


    CreateBox(0, 83, 13);
    CreateBox(1, 96, 13);
    CreateBox(2, 87, 37);
    CreateBox(3, 88, 37);
    CreateBox(4, 89, 37);
    CreateBox(5, 90, 37);
    CreateBox(6, 91, 37);
    CreateBox(7, 38, 41);
    CreateBox(8, 52, 41);
    CreateBox(9, 83, 41);
    CreateBox(10, 102, 41);
    CreateBox(11, 55, 42);
    CreateBox(12, 116, 29);
    CreateBox(15, 103, 30);
    CreateBox(16, 109, 30);
    CreateBox(17, 112, 30);
    CreateBox(18, 127, 30);

    CreateBox(19, 104, 31);
    CreateBox(21, 119, 31);
    CreateBox(22, 108, 32);
    CreateBox(23, 125, 32);
    CreateBox(24, 114, 33);
    CreateBox(26, 105, 34);
    CreateBox(27, 117, 34);
    CreateBox(28, 109, 35);
    CreateBox(29, 125, 35);
    CreateBox(30, 109, 36);
    CreateBox(31, 113, 36);
    CreateBox(32, 120, 36);
    CreateBox(33, 105, 37);
    CreateBox(34, 112, 37);
    CreateBox(36, 109, 38);
    CreateBox(38, 112, 38);
    CreateBox(39, 122, 38);

    CreateTeleport(0, 86, 38, 117, 6);
}

void createEntitiesThePitfall1() {
    CreateDoor(0, 57, 27);
    CreateDoor(1, 57, 18);
    CreateDoor(2, 57, 10);
    CreateDoor(3, 57, 5);

    CreateKey(2, 71, 31);
    CreateKey(3, 72, 26);
    CreateKey(4, 60, 12);
    CreateKey(5, 60, 6);

    FinishArea(57, 3);

    CreateRollSideEnemy(0, 46, 25);
    CreateRollSideEnemy(1, 66, 25);
    CreateRollSideEnemy(2, 47, 20);
    CreateRollSideEnemy(4, 52, 9);
    CreateRollSideEnemy(5, 62, 9);

    CreateRollUpEnemy(0, 43, 23);
    CreateRollUpEnemy(1, 52, 19);

    CreateLaserDownEnemy(0, 49, 11);
    CreateLaserDownEnemy(2, 51, 11);
    CreateLaserDownEnemy(5, 54, 11);
    CreateLaserDownEnemy(6, 55, 11);
    CreateLaserDownEnemy(7, 56, 11);
    CreateLaserDownEnemy(8, 58, 11);
    CreateLaserDownEnemy(9, 59, 11);
    CreateLaserDownEnemy(11, 61, 11);
    CreateLaserDownEnemy(14, 64, 11);


    CreatePistoletRightEnemy(0, 32, 28);
    CreatePistoletRightEnemy(1, 31, 29);
    CreatePistoletRightEnemy(2, 30, 30);
    CreatePistoletRightEnemy(3, 29, 31);
    CreatePistoletRightEnemy(4, 28, 32);
    CreatePistoletRightEnemy(5, 27, 33);
    CreatePistoletRightEnemy(6, 26, 34);
    CreatePistoletRightEnemy(7, 25, 35);

    CreatePistoletLeftEnemy(0, 82, 28);
    CreatePistoletLeftEnemy(1, 83, 29);
    CreatePistoletLeftEnemy(2, 84, 30);
    CreatePistoletLeftEnemy(3, 85, 31);
    CreatePistoletLeftEnemy(4, 86, 32);
    CreatePistoletLeftEnemy(5, 87, 33);
    CreatePistoletLeftEnemy(6, 88, 34);
    CreatePistoletLeftEnemy(7, 89, 35);

    CreateLaserLeftEnemy(2, 71, 17);

    CreateLaserRightEnemy(0, 47, 13);
    CreateLaserRightEnemy(1, 45, 15);

    CreateBox(0, 71, 26);
    CreateBox(1, 74, 26);
    CreateBox(2, 72, 25);
    CreateBox(3, 73, 25);
}

void createEntitiesThePitfall2() {
    CreateFigerEnemyReverse(0, 107, 7);
    CreateFigerEnemyReverse(1, 79, 11);
    CreateFigerEnemyReverse(2, 55, 13);
    CreateFigerEnemyReverse(3, 91, 13);
    CreateFigerEnemyReverse(4, 62, 14);
    CreateFigerEnemyReverse(5, 78, 16);
    CreateFigerEnemyReverse(6, 96, 17);
    CreateFigerEnemyReverse(7, 79, 19);
    CreateFigerEnemyReverse(8, 90, 20);
    CreateFigerEnemyReverse(9, 63, 26);
    CreateFigerEnemyReverse(10, 58, 28);

    CreateRollSideEnemy(0, 56, 9);
    CreateRollSideEnemy(1, 99, 11);
    CreateRollSideEnemy(2, 59, 17);
    CreateRollSideEnemy(3, 54, 24);
    CreateRollSideEnemy(4, 110, 25);
    CreateRollSideEnemy(5, 102, 19);

    CreateRollUpEnemy(0, 87, 9);
    CreateRollUpEnemy(1, 71, 10);
    CreateRollUpEnemy(2, 108, 15);
    CreateRollUpEnemy(3, 72, 23);
    CreateRollUpEnemy(4, 86, 26);


    CreateLaserDownEnemy(0, 64, 6);
    CreateLaserDownEnemy(1, 82, 6);
    CreateLaserDownEnemy(2, 90, 6);


    CreateLaserUpEnemy(0, 76, 29);
    CreateLaserUpEnemy(1, 83, 29);
    CreateLaserUpEnemy(2, 90, 29);


    CreatePistoletDownEnemy(0, 67, 6);
    CreatePistoletDownEnemy(1, 78, 6);
    CreatePistoletDownEnemy(2, 97, 6);

    CreatePistoletRightEnemy(0, 46, 10);
    CreatePistoletRightEnemy(1, 46, 17);
    CreatePistoletRightEnemy(2, 46, 20);

    CreatePistoletLeftEnemy(0, 118, 20);
    CreatePistoletLeftEnemy(1, 118, 27);


    CreateLaserLeftEnemy(0, 118, 10);
    CreateLaserLeftEnemy(1, 118, 17);
    CreateLaserLeftEnemy(2, 118, 22);

    CreateLaserRightEnemy(0, 46, 15);
    CreateLaserRightEnemy(1, 46, 25);


}

void createEntitiesThePitfall3() {
    CreateTheEnd(0, 55, 2);
    CreateTheEnd(1, 55, 3);

    CreateRollSideEnemy(0, 49, 9);
    CreateRollSideEnemy(1, 62, 21);
    CreateRollSideEnemy(2, 46, 25);
    CreateRollSideEnemy(4, 60, 31);
    CreateRollSideEnemy(5, 48, 34);

    CreateRollUpEnemy(0, 45, 13);
    CreateRollUpEnemy(1, 62, 13);


    CreateLaserDownEnemy(0, 47, 6);
    CreateLaserDownEnemy(1, 51, 6);
    CreateLaserDownEnemy(2, 59, 6);
    CreateLaserDownEnemy(3, 61, 6);
    CreateLaserDownEnemy(4, 54, 9);
    CreateLaserDownEnemy(5, 56, 9);
    CreateLaserDownEnemy(6, 55, 11);
    CreateLaserDownEnemy(7, 55, 21);



    CreatePistoletUpEnemy(1, 53, 37);
    CreatePistoletUpEnemy(2, 58, 37);


    CreatePistoletRightEnemy(0, 44, 18);

    CreatePistoletLeftEnemy(0, 65, 15);
    CreatePistoletLeftEnemy(1, 65, 29);


    CreateBox(0, 60, 36);
}

void createEntitiesThePitfallBoss() {
    CreateRollSideEnemy(0, 73, 17);
    CreateRollSideEnemy(1, 60, 24);
    CreateRollSideEnemy(2, 127, 15);
    CreateRollSideEnemy(3, 131, 30);

    CreateRollUpEnemy(0, 54, 18);
    CreateRollUpEnemy(1, 73, 30);
    CreateRollUpEnemy(2, 126, 19);

    CreateLaserDownEnemy(0, 89, 19);
    CreateLaserDownEnemy(1, 107, 19);
    CreateLaserDownEnemy(2, 92, 23);
    CreateLaserDownEnemy(3, 104, 23);

    CreateLaserLeftEnemy(0, 167, 17);
    CreateLaserLeftEnemy(1, 167, 18);
    CreateLaserLeftEnemy(2, 167, 19);
    CreateLaserLeftEnemy(3, 167, 20);

    CreateLaserRightEnemy(0, 27, 17);
    CreateLaserRightEnemy(1, 27, 18);
    CreateLaserRightEnemy(2, 27, 19);
    CreateLaserRightEnemy(3, 27, 20);

    CreateLaserUpEnemy(0, 94, 37);
    CreateLaserUpEnemy(1, 102, 37);



    CreatePistoletRightEnemy(0, 44, 25);
    CreatePistoletRightEnemy(1, 44, 28);

    CreatePistoletLeftEnemy(0, 152, 25);
    CreatePistoletLeftEnemy(1, 152, 28);


    CreateGreenStar(21, 61, 14);
    CreateGreenStar(20, 122, 31);
    CreateGreenStar(2, 142, 15);
    CreateGreenStar(3, 156, 19);
    CreateGreenStar(4, 48, 22);
    CreateGreenStar(5, 79, 14);
    CreateGreenStar(6, 116, 10);
    CreateGreenStar(7, 115, 34);
    CreateGreenStar(8, 49, 25);
    CreateGreenStar(9, 108, 20);
    CreateGreenStar(10, 47, 16);
    CreateGreenStar(11, 31, 20);
    CreateGreenStar(12, 98, 37);
    CreateGreenStar(13, 83, 24);
    CreateGreenStar(14, 139, 32);
    CreateGreenStar(15, 152, 26);
    CreateGreenStar(16, 92, 24);
    CreateGreenStar(17, 110, 13);
    CreateGreenStar(18, 94, 30);
    CreateGreenStar(19, 126, 15);



    CreateChain(0, 84, 10);
    CreateChain(1, 85, 10);
    CreateChain(2, 86, 10);
    CreateChain(3, 85, 11);
    CreateChain(4, 86, 11);
    CreateChain(5, 87, 11);
    CreateChain(6, 86, 12);
    CreateChain(7, 87, 12);
    CreateChain(8, 88, 12);
    CreateChain(9, 87, 13);
    CreateChain(10, 110, 10);
    CreateChain(11, 111, 10);
    CreateChain(12, 112, 10);
    CreateChain(13, 109, 11);
    CreateChain(14, 110, 11);
    CreateChain(15, 111, 11);
    CreateChain(16, 108, 12);
    CreateChain(17, 109, 12);
    CreateChain(18, 110, 12);
    CreateChain(19, 109, 13);

    CreateBoxDestroy(0, 98, 10);
    CreateBoss(98, 17);
}

//

void planszaLevel1_1() {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    gotoxy(1, 3);
    cout << "                ######             ###                               #########################";
    gotoxy(1, 4);
    cout << "                #    #             # #                               #                       #";
    gotoxy(1, 5);
    cout << "                #    #             # #                               #                       #";
    gotoxy(1, 6);
    cout << "                #    #             # #                               #                       #";
    gotoxy(1, 7);
    cout << "#################    ############### #                               #        ################";
    gotoxy(1, 8);
    cout << "#             #                      #                               ####  #  #";
    gotoxy(1, 9);
    cout << "#                                    #                               #        #";
    gotoxy(1, 10);
    cout << "#             #                      #                               #        #";
    gotoxy(1, 11);
    cout << "#################################### #                               #        #";
    gotoxy(1, 12);
    cout << "                                #    #             ###               #        #";
    gotoxy(1, 13);
    cout << "                                #    #             # #               #        #";
    gotoxy(1, 14);
    cout << "                                #    #             # #               #        #";
    gotoxy(1, 15);
    cout << "                                #    #             # #               #  #  ####";
    gotoxy(1, 16);
    cout << "                                # ## ############### #################        #";
    gotoxy(1, 17);
    cout << "                                #  ###                                        #";
    gotoxy(1, 18);
    cout << "                                #                                             #";
    gotoxy(1, 19);
    cout << "                                #                                             #";
    gotoxy(1, 20);
    cout << "                                ############ ############## ############ ######";
    gotoxy(1, 21);
    cout << "                                           # #            # #          # #";
    gotoxy(1, 22);
    cout << "                                           # #            # #          # #";
    gotoxy(1, 23);
    cout << "                                           # #            # #          # #";
    gotoxy(1, 24);
    cout << "                                           ###            ###          ###";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    gotoxy(11, 16);
    cout << "THAT'S CHECKPOINT ==>";

}

void planszaLevel1_2() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    ifstream level2("levels/levelmain/level12.txt");
    if (level2.is_open()) {
        while (getline(level2, plansza)) {
            cout << plansza << endl;
        }
    }
    level2.close();
}

void planszaLevel1_3() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    ifstream level3("levels/levelmain/level13.txt");
    if (level3.is_open()) {
        while (getline(level3, plansza)) {
            cout << plansza << endl;
        }
    }
    level3.close();
}

void planszaLevel1_4() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    ifstream level4("levels/levelmain/level14.txt");
    if (level4.is_open()) {
        while (getline(level4, plansza)) {
            cout << plansza << endl;
        }
    }
    level4.close();
}

void planszaLevel1_5() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    ifstream level5("levels/levelmain/level15.txt");
    if (level5.is_open()) {
        while (getline(level5, plansza)) {
            cout << plansza << endl;
        }
    }
    level5.close();
}

void planszaLevel2_1() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    ifstream level6("levels/levelmain/level21.txt");
    if (level6.is_open()) {
        while (getline(level6, plansza)) {
            cout << plansza << endl;
        }
    }
    level6.close();
}

void planszaLevel2_2() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    ifstream level7("levels/levelmain/level22.txt");
    if (level7.is_open()) {
        while (getline(level7, plansza)) {
            cout << plansza << endl;
        }
    }
    level7.close();
}

void planszaLevel2_3() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    ifstream level8("levels/levelmain/level23.txt");
    if (level8.is_open()) {
        while (getline(level8, plansza)) {
            cout << plansza << endl;
        }
    }
    level8.close();
}

void planszaLevel2_4() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    ifstream level9("levels/levelmain/level24.txt");
    if (level9.is_open()) {
        while (getline(level9, plansza)) {
            cout << plansza << endl;
        }
    }
    level9.close();
}

void planszaLevel2_5() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    ifstream level10("levels/levelmain/level25.txt");
    if (level10.is_open()) {
        while (getline(level10, plansza)) {
            cout << plansza << endl;
        }
    }
    level10.close();
}

void planszaLevel3_1() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    ifstream level11("levels/levelmain/level31.txt");
    if (level11.is_open()) {
        while (getline(level11, plansza)) {
            cout << plansza << endl;
        }
    }
    level11.close();
}

void planszaLevel3_2() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    ifstream level12("levels/levelmain/level32.txt");
    if (level12.is_open()) {
        while (getline(level12, plansza)) {
            cout << plansza << endl;
        }
    }
    level12.close();
}

void planszaLevel3_3() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    ifstream level13("levels/levelmain/level33.txt");
    if (level13.is_open()) {
        while (getline(level13, plansza)) {
            cout << plansza << endl;
        }
    }
    level13.close();
}

void planszaLevel3_4() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    ifstream level14("levels/levelmain/level34.txt");
    if (level14.is_open()) {
        while (getline(level14, plansza)) {
            cout << plansza << endl;
        }
    }
    level14.close();
}

void planszaLevel3_5() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    ifstream level15("levels/levelmain/level35.txt");
    if (level15.is_open()) {
        while (getline(level15, plansza)) {
            cout << plansza << endl;
        }
    }
    level15.close();
}

void planszaLevel4_1() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    ifstream level16("levels/levelmain/level41.txt");
    if (level16.is_open()) {
        while (getline(level16, plansza)) {
            cout << plansza << endl;
        }
    }
    level16.close();
}

void planszaLevel4_2() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    ifstream level17("levels/levelmain/level42.txt");
    if (level17.is_open()) {
        while (getline(level17, plansza)) {
            cout << plansza << endl;
        }
    }
    level17.close();
    gotoxy(33, 23);
    cout << char(219);
}

void planszaLevel4_3() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    ifstream level18("levels/levelmain/level43.txt");
    if (level18.is_open()) {
        while (getline(level18, plansza)) {
            cout << plansza << endl;
        }
    }
    level18.close();
}

void planszaLevel4_4() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    ifstream level19("levels/levelmain/level44.txt");
    if (level19.is_open()) {
        while (getline(level19, plansza)) {
            cout << plansza << endl;
        }
    }
    level19.close();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    gotoxy(23, 11);
    cout << "CAN YOU FIND A RIGHT WAY?";

}

void planszaLevel4_5() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    ifstream level20("levels/levelmain/level45.txt");
    if (level20.is_open()) {
        while (getline(level20, plansza)) {
            cout << plansza << endl;
        }
    }
    level20.close();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    gotoxy(141, 8);
    cout << "EXIT";
    gotoxy(151, 14);
    cout << char(254);
    for (int i = 0; i < 9; i++) {
        gotoxy(152 + i, 13);
        cout << '#';
    }
    for (int i = 0; i < 5; i++) {
        gotoxy(160, 13 + i);
        cout << '#';
    }


}

void planszaThePitfall1() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    ifstream level21("levels/levelmain/levelThePitfall1.txt");
    if (level21.is_open()) {
        while (getline(level21, plansza)) {
            cout << plansza << endl;
        }
    }
    level21.close();
}

void planszaThePitfall2() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    ifstream level22("levels/levelmain/levelThePitfall2.txt");
    if (level22.is_open()) {
        while (getline(level22, plansza)) {
            cout << plansza << endl;
        }
    }
    level22.close();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    gotoxy(78, 2);
    cout << "SURVIVE!";

}

void planszaThePitfall3() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    ifstream level23("levels/levelmain/levelThePitfall3.txt");
    if (level23.is_open()) {
        while (getline(level23, plansza)) {
            cout << plansza << endl;
        }
    }
    level23.close();
    gotoxy(45, 2);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "EXIT";
}

void planszaThePitfallBoss() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    ifstream level24("levels/levelmain/levelThePitfallBoss1.txt");
    if (level24.is_open()) {
        while (getline(level24, plansza)) {
            cout << plansza << endl;
        }
    }
    level24.close();

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    gotoxy(92, 7);
    cout << "BBBBBBBBBBBBB";
    gotoxy(76, 8);
    cout << "BBBBBBBBBBBBBBBBB";
    gotoxy(104, 8);
    cout << "BBBBBBBBBBBBBBBBBB";
    gotoxy(65, 9);
    cout << "BBBBBBBBBBB";
    gotoxy(121, 9);
    cout << "BBBBBBBBBBB";
    gotoxy(59, 10);
    cout << "BBBBBBB";
    gotoxy(131, 10);
    cout << "BBBBBBB";
    gotoxy(53, 11);
    cout << "BBBBBBB";
    gotoxy(137, 11);
    cout << "BBBBBBB";
    gotoxy(47, 12);
    cout << "BBBBBBB";
    gotoxy(143, 12);
    cout << "BBBBBBB";
    gotoxy(44, 13);
    cout << "BBBB";
    gotoxy(149, 13);
    cout << "BBBB";
    gotoxy(43, 14);
    cout << "BB";
    gotoxy(152, 14);
    cout << "BB";
    gotoxy(25, 15);
    cout << "BBBBBBBBBBBBBBBBBBB";
    gotoxy(153, 15);
    cout << "BBBBBBBBBBBBBBBBB";
    gotoxy(25, 16);
    cout << "B";
    gotoxy(169, 16);
    cout << "B";
    gotoxy(25, 17);
    cout << "B";
    gotoxy(169, 17);
    cout << "B";
    gotoxy(25, 18);
    cout << "B";
    gotoxy(169, 18);
    cout << "B";
    gotoxy(25, 19);
    cout << "B";
    gotoxy(169, 19);
    cout << "B";
    gotoxy(25, 20);
    cout << "B";
    gotoxy(169, 20);
    cout << "B";
    gotoxy(25, 21);
    cout << "B";
    gotoxy(169, 21);
    cout << "B";
    gotoxy(25, 22);
    cout << "BBBBBBBBBBBBBBBBBB";
    gotoxy(154, 22);
    cout << "BBBBBBBBBBBBBBBB";
    gotoxy(42, 23);
    cout << "B";
    gotoxy(154, 23);
    cout << "B";
    gotoxy(42, 24);
    cout << "B";
    gotoxy(154, 24);
    cout << "B";
    gotoxy(42, 25);
    cout << "B";
    gotoxy(154, 25);
    cout << "B";
    gotoxy(42, 26);
    cout << "B";
    gotoxy(154, 26);
    cout << "B";
    gotoxy(42, 27);
    cout << "B";
    gotoxy(154, 27);
    cout << "B";
    gotoxy(42, 28);
    cout << "B";
    gotoxy(154, 28);
    cout << "B";
    gotoxy(42, 29);
    cout << "B";
    gotoxy(154, 29);
    cout << "B";
    gotoxy(43, 30);
    cout << "B";
    gotoxy(153, 30);
    cout << "B";
    gotoxy(43, 31);
    cout << "B";
    gotoxy(153, 31);
    cout << "B";
    gotoxy(43, 32);
    cout << "BB";
    gotoxy(152, 32);
    cout << "BB";
    gotoxy(44, 33);
    cout << "BBBB";
    gotoxy(149, 33);
    cout << "BBBB";
    gotoxy(47, 34);
    cout << "BBBBBBB";
    gotoxy(143, 34);
    cout << "BBBBBBB";
    gotoxy(53, 35);
    cout << "BBBBBBB";
    gotoxy(137, 35);
    cout << "BBBBBBB";
    gotoxy(59, 36);
    cout << "BBBBBBB";
    gotoxy(131, 36);
    cout << "BBBBBBB";
    gotoxy(65, 37);
    cout << "BBBBBBBBBBB";
    gotoxy(121, 37);
    cout << "BBBBBBBBBBB";
    gotoxy(75, 38);
    cout << "BBBBBBBBBBBBBBBBBB";
    gotoxy(104, 38);
    cout << "BBBBBBBBBBBBBBBBBB";
    gotoxy(92, 39);
    cout << "BBBBBBBBBBBBB";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    gotoxy(93, 12);
    cout << "###########";
    gotoxy(88, 13);
    cout << "######         ######";
    gotoxy(88, 14);
    cout << "#                   #";
    gotoxy(88, 15);
    cout << "#                   #";
    gotoxy(88, 16);
    cout << "#                   #";
    gotoxy(88, 17);
    cout << "#                   #";
    gotoxy(88, 18);
    cout << "######         ######";
    gotoxy(91, 19);
    cout << "#             #";
    gotoxy(91, 20);
    cout << "#             #";
    gotoxy(91, 21);
    cout << "#             #";
    gotoxy(91, 22);
    cout << "###############";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    gotoxy(91, 15);
    cout << "0000       0000";
    gotoxy(90, 16);
    cout << "0    0     0    0";
    gotoxy(90, 17);
    cout << "0    0     0    0";
    gotoxy(92, 18);
    cout << "000       000";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    gotoxy(98, 16);
    cout << "J";
    gotoxy(97, 17);
    cout << "JJJ";
    gotoxy(98, 18);
    cout << "J";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    gotoxy(92, 19);
    cout << "-------------";
    gotoxy(92, 21);
    cout << "-------------";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    gotoxy(96, 14);
    cout << "=====";
    gotoxy(92, 20);
    cout << "=============";

    gotoxy(76, 2);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "COLLECT ALL STARS TO OPEN THE WAY TO THE VOID BOX";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    gotoxy(98, 3);
    cout << "|";
    gotoxy(98, 4);
    cout << "|";
    gotoxy(98, 5);
    cout << "|";
    gotoxy(98, 6);
    cout << "v";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    gotoxy(10, 10);
    cout << "DESTROY THE SKULL TO DEFEAT THE KEEPER";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
}

//

void zliczaniegwiazd() {
    ofstream stars("options/LevelStars.txt");

    if (stars.is_open()) {
        zebranegwiazdy = 0;
        for (int i = 0; i < 4; i++) {
            for (int y = 0; y < 5; y++) {
                if (starslevel[i][y] > starslevelzapis[i][y]) {
                    stars << starslevel[i][y];
                    zebranegwiazdy += starslevel[i][y];
                    stars << endl;
                }
                else {
                    starslevel[i][y] = starslevelzapis[i][y];
                    stars << starslevel[i][y];
                    zebranegwiazdy += starslevel[i][y];
                    stars << endl;
                }
            }
            stars << endl;
        }
        stars.close();
    }
}

void LevelUn() {
    ofstream levels("options/LevelsUnlocked.txt");

    if (levels.is_open()) {
        for (int i = 0; i < 4; i++) {
            for (int z = 0; z < 4; z++) {
                levels << unlockedlevels[i][z];
                levels << endl;
            }
            levels << endl;
        }
        levels.close();
    }
}

void UnlockedLevels() {
    ofstream levels("options/Unlocked.txt");

    if (levels.is_open()) {
        for (int i = 0; i < 3; i++) {
            levels << unlocked[i];
            levels << endl;
        }
        levels.close();
    }
}

void world1tutorial() {
    MusicBoxTutorial();
    tutorial = 1;
    for (int i = 4; i < 21; i++) {
        for (int y = 18; y < 80; y++) {
            if (i == 4 || i == 6 || i == 12 || i == 20) { // y
                mainmenu[i][y] = "#";
            }
            else if (y == 18 || y == 79) { // x
                mainmenu[i][y] = "#";
            }
            else if (i > 6 && i < 13) {
                if (y == 33 || y == 49 || y == 64) {
                    mainmenu[i][y] = "#";
                }
            }
            else {
                mainmenu[i][y] = " ";
            }
        }
    }
    for (int i = 4; i < 21; i++) {
        for (int y = 18; y < 80; y++) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
            cout << mainmenu[i][y];

        }
        cout << endl;
    }

    gotoxy(28, 2);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "TUTORIAL";
    Sleep(2000);
    gotoxy(8, 7);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "UP";
    gotoxy(22, 7);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "RIGHT";
    gotoxy(34, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "DOWN";
    gotoxy(53, 7);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "LEFT";
    gotoxy(66, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "<== IF YOU GET HIT BY ONE OF THESE PROJECTILES YOU WILL LOSE A LIFE";
    gotoxy(70, 2);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "YOU'VE GOT 5 LIVES";
    gotoxy(70, 3);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "YOUR MAIN GOAL IS TO REACH THE FINISH LINE";
    gotoxy(65, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "<=== THAT'S THE FINISH LINE";
    gotoxy(22, 18);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << player << " <=== THAT'S YOU";
    gotoxy(10, 18);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << "CONTROLS: W - UP, S - DOWN, A - LEFT, D - RIGHT";
    gotoxy(17, 20);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "PRESS R TO RESTART THE TUTORIAL";




    grazaczeta = true;
    getCursorChar();
    zycia = 10000000;
    gracz.x = 6;
    gracz.y = 11;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    createEntitiesTutorial1();
    while (ok == false && grazaczeta == true) {
        setCursorInvisible(false);
        updateTutorial1();
        updateEntities();
        poruszanie();
    }
    if (grazaczeta == false && ok == false) {
        czyjesttutorial = false;
        deleteobjects();
        system("CLS");
    }
}

void world1tutorial2() {
    MusicBoxTutorial();
    tutorial = 2;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    ifstream tutorial2("levels/leveltutorial/tutorialBox.txt");
    if (tutorial2.is_open()) {
        while (getline(tutorial2, plansza)) {
            cout << plansza << endl;
        }
    }
    tutorial2.close();

    gotoxy(17, 2);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "TUTORIAL";
    Sleep(2000);

    gotoxy(44, 2);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "BOXES CAN PROTECT YOU FROM INCOMING PROJECTILES";


    gotoxy(20, 12);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "BOX";

    grazaczeta = true;
    getCursorChar();
    zycia = 10000000;
    gracz.x = 5;
    gracz.y = 5;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    createEntitiesTutorial2();
    while (ok == false && grazaczeta == true) {
        setCursorInvisible(false);
        updateTutorial1();
        updateEntities();
        poruszanie();
    }
    if (grazaczeta == false && ok == false) {
        czyjesttutorial = false;
        deleteobjects();
        system("CLS");
    }
}

void world2tutorial1() {
    MusicBoxTutorial();
    tutorial = 3;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    ifstream tutorial3("levels/leveltutorial/tutorialLasers.txt");
    if (tutorial3.is_open()) {
        while (getline(tutorial3, plansza)) {
            cout << plansza << endl;
        }
    }
    tutorial3.close();

    gotoxy(46, 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "TUTORIAL";
    Sleep(2000);

    gotoxy(77, 3);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "WATCH OUT FOR LASERS!";

    grazaczeta = true;
    getCursorChar();
    zycia = 10000000;
    gracz.x = 28;
    gracz.y = 11;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    createEntitiesTutorial3();
    while (ok == false && grazaczeta == true) {
        setCursorInvisible(false);
        updateTutorial1();
        updateEntities();
        poruszanie();
    }
    if (grazaczeta == false && ok == false) {
        czyjesttutorial = false;
        deleteobjects();
        system("CLS");
    }
}

void world2tutorial2() {
    MusicBoxTutorial();
    tutorial = 4;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    ifstream tutorial4("levels/leveltutorial/tutorialDoor.txt");
    if (tutorial4.is_open()) {
        while (getline(tutorial4, plansza)) {
            cout << plansza << endl;
        }
    }
    tutorial4.close();

    gotoxy(51, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "TUTORIAL";
    Sleep(2000);

    gotoxy(94, 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << "YOU NEED A KEY TO UNLOCK THE DOOR";

    gotoxy(94, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << "YOU CAN ONLY HAVE ONE KEY AT A TIME";

    gotoxy(94, 8);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << "AFTER UNLOCKING THE DOOR YOU'LL LOSE THE KEY";


    gotoxy(20, 10);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "DOOR";

    gotoxy(20, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "KEY";

    grazaczeta = true;
    getCursorChar();
    zycia = 10000000;
    gracz.x = 30;
    gracz.y = 13;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    createEntitiesTutorial4();
    while (ok == false && grazaczeta == true) {
        setCursorInvisible(false);
        updateTutorial1();
        updateEntities();
        poruszanie();
    }
    if (grazaczeta == false && ok == false) {
        czyjesttutorial = false;
        deleteobjects();
        system("CLS");
    }
}

void world3tutorial1() {
    MusicBoxTutorial();
    tutorial = 5;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    ifstream tutorial5("levels/leveltutorial/tutorialFiger.txt");
    if (tutorial5.is_open()) {
        while (getline(tutorial5, plansza)) {
            cout << plansza << endl;
        }
    }
    tutorial5.close();
    zapalony = false;
    gotoxy(49, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "TUTORIAL";
    Sleep(2000);

    gotoxy(96, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "PRESS THE BUTTON TO CHANGE THE STATE OF THE FIGERS";


    gotoxy(18, 18);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "BUTTON";

    gotoxy(28, 18);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "FIGER ON";
    gotoxy(31, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "&";




    gotoxy(39, 18);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "FIGER OFF";
    gotoxy(42, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << char(254);

    grazaczeta = true;
    getCursorChar();
    zycia = 10000000;
    gracz.x = 20;
    gracz.y = 11;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    createEntitiesTutorial5();
    while (ok == false && grazaczeta == true) {
        setCursorInvisible(false);
        updateTutorial1();
        updateEntities();
        poruszanie();
    }
    if (grazaczeta == false && ok == false) {
        czyjesttutorial = false;
        deleteobjects();
        system("CLS");
    }
}

void world3tutorial2() {
    MusicBoxTutorial();
    tutorial = 6;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    ifstream tutorial6("levels/leveltutorial/tutorialDoor2.txt");
    if (tutorial6.is_open()) {
        while (getline(tutorial6, plansza)) {
            cout << plansza << endl;
        }
    }
    tutorial6.close();
    zapalony = false;
    gotoxy(52, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "TUTORIAL";
    Sleep(2000);

    gotoxy(93, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "YOU NEED 3 MAGNETIC KEYS TO UNLOCK A MAGNETIC GATE";


    gotoxy(49, 24);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "DOOR";

    gotoxy(59, 24);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "MAGNETIC KEY";

    grazaczeta = true;
    getCursorChar();
    zycia = 10000000;
    gracz.x = 54;
    gracz.y = 14;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    createEntitiesTutorial6();
    while (ok == false && grazaczeta == true) {
        setCursorInvisible(false);
        updateTutorial1();
        updateEntities();
        poruszanie();
    }
    if (grazaczeta == false && ok == false) {
        czyjesttutorial = false;
        deleteobjects();
        system("CLS");
    }
}

void world4tutorial1() {
    MusicBoxTutorial();
    tutorial = 7;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    ifstream tutorial7("levels/leveltutorial/tutorialRollsideup.txt");
    if (tutorial7.is_open()) {
        while (getline(tutorial7, plansza)) {
            cout << plansza << endl;
        }
    }
    tutorial7.close();
    zapalony = false;
    gotoxy(40, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "TUTORIAL";
    Sleep(2000);

    gotoxy(89, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "ROLLUP AND ROLLSIDE SHOOTS FROM THEIR FOUR SIDES";

    gotoxy(93, 7);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "WATCH OUT FOR THEIR PROJECTILES!";

    gotoxy(31, 24);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "ROLLUP";

    gotoxy(49, 24);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "ROLLSIDE";

    grazaczeta = true;
    getCursorChar();
    zycia = 10000000;
    gracz.x = 13;
    gracz.y = 12;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    createEntitiesTutorial7();
    while (ok == false && grazaczeta == true) {
        setCursorInvisible(false);
        updateTutorial1();
        updateEntities();
        poruszanie();
    }
    if (grazaczeta == false && ok == false) {
        czyjesttutorial = false;
        deleteobjects();
        system("CLS");
    }
}

void world4tutorial2() {
    MusicBoxTutorial();
    tutorial = 8;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    ifstream tutorial8("levels/leveltutorial/tutorialTeleport.txt");
    if (tutorial8.is_open()) {
        while (getline(tutorial8, plansza)) {
            cout << plansza << endl;
        }
    }
    tutorial8.close();
    zapalony = false;
    gotoxy(49, 7);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "TUTORIAL";
    Sleep(2000);

    gotoxy(35, 20);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "TELEPORT TELEPORTS YOU FROM ONE POINT TO ANOTHER";

    gotoxy(50, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "TELEPORT";


    grazaczeta = true;
    getCursorChar();
    zycia = 10000000;
    gracz.x = 34;
    gracz.y = 10;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    createEntitiesTutorial8();
    while (ok == false && grazaczeta == true) {
        setCursorInvisible(false);
        updateTutorial1();
        updateEntities();
        poruszanie();
    }
    if (grazaczeta == false && ok == false) {
        czyjesttutorial = false;
        deleteobjects();
        system("CLS");
    }
}


//
void dead() {
    system("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    gotoxy(38, 10);
    cout << "###############################################";
    gotoxy(38, 11);
    cout << "#                                             #";
    gotoxy(38, 12);
    cout << "#                   YOU DIED!                 #";
    gotoxy(38, 13);
    cout << "#                                             #";
    gotoxy(38, 14);
    cout << "###############################################";
    gotoxy(38, 15);
    cout << "#                      #                      #";
    gotoxy(38, 16);
    cout << "#     BACK TO MENU     #       TRY AGAIN      #";
    gotoxy(38, 17);
    cout << "#                      #                      #";
    gotoxy(38, 18);
    cout << "###############################################";

    gracz.x = 41;
    gracz.y = 16;

    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    m = 1;
    ultrastars = 0;
    while (grazaczeta == false) {
        char e = _getch();
        if (e == 'a' || e == toupper('a')) {
            if (m == 2) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";
                gracz.x -= 24;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                m = 1;
            }
        }
        else if (e == 'd' || e == toupper('d')) {
            if (m == 1) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";
                gracz.x += 24;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                m = 2;
            }
        }
        else if (e == ' ') {
            if (m == 1) {
                czyjesttutorial = true;
                grazaczeta = false;
                deleteobjects();
                worldmenu();
            }
            else if (m == 2) {
                deleteobjects();
                restartlevel();
            }
        }
    }
}

void finished() {
    system("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    gotoxy(38, 10);
    cout << "###############################################";
    gotoxy(38, 11);
    cout << "#                                             #";
    gotoxy(38, 12);
    cout << "#                 YOU ESCAPED!                #";
    gotoxy(38, 13);
    cout << "#                                             #";
    gotoxy(38, 14);
    cout << "###############################################";
    gotoxy(38, 15);
    cout << "#                      #                      #";
    gotoxy(38, 16);
    cout << "#     BACK TO MENU     #      NEXT LEVEL      #";
    gotoxy(38, 17);
    cout << "#                      #                      #";
    gotoxy(38, 18);
    cout << "###############################################";
    unlockedlevels[world - 1][level - 1] = true;
    LevelUn();
    gracz.x = 41;
    gracz.y = 16;
    czyjesttutorial = true;
    zapalony = false;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    m = 1;

    while (grazaczeta == false) {
        char e = _getch();
        if (e == 'a' || e == toupper('a')) {
            if (m == 2) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";
                gracz.x -= 24;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                m = 1;
            }
        }
        else if (e == 'd' || e == toupper('d')) {
            if (m == 1) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";
                gracz.x += 24;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                m = 2;
            }
        }
        else if (e == ' ') {
            if (m == 1) {
                zliczaniegwiazd();
                czyjesttutorial = true;
                grazaczeta = false;
                deleteobjects();
                worldmenu();
            }
            else if (m == 2) {
                zliczaniegwiazd();
                deleteobjects();
                nextlevel();
            }
        }
    }
}

void finishedchapter() {
    system("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    gotoxy(38, 10);
    cout << "###############################################";
    gotoxy(38, 11);
    cout << "#                                             #";
    gotoxy(38, 12);
    cout << "#              CHAPTER " << world << " COMPLETED            #";
    gotoxy(38, 13);
    cout << "#                                             #";
    gotoxy(38, 14);
    cout << "###############################################";
    gotoxy(38, 15);
    cout << "#                                             #";
    gotoxy(38, 16);
    cout << "#                 BACK TO MENU                #";
    gotoxy(38, 17);
    cout << "#                                             #";
    gotoxy(38, 18);
    cout << "###############################################";

    unlocked[world - 1] = true;
    gracz.x = 41;
    gracz.y = 16;
    liczbakluczy = 0;
    czyjesttutorial = true;
    zapalony = false;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    while (grazaczeta == false) {
        char e = _getch();
        if (e == ' ') {
            zliczaniegwiazd();
            UnlockedLevels();
            deleteobjects();
            world = 0;
            level = 0;
            MusicBox();
            startmenu();
        }
    }
}

void finishedgame() {
    liczbakluczy = 0;
    czyjesttutorial = true;
    zapalony = false;
    zliczaniegwiazd();
    deleteobjects();
    world = 0;
    level = 0;
    system("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    gotoxy(58, 10);
    cout << "YES!";
    gracz.x = 60;
    gracz.y = 13;
    for (int i = 0; i < 21; i++) {
        gotoxy(gracz.x, gracz.y);
        cout << " ";
        gracz.x += 1;
        gotoxy(gracz.x, gracz.y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
        cout << player;
        Sleep(100);
        if (i == 10) {
            gotoxy(74, 10);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
            cout << "I'M FINALLY FREE!";
        }
    }
    Sleep(1000);
    gotoxy(74, 10);
    cout << "                   ";
    gotoxy(58, 10);
    cout << "     ";
    if (zebranegwiazdy == 60) {
        ThePitfall();
    }
    else {
        if (IsMusicOn == true) {
            if (playing == false) {
                PlaySound(TEXT("The Pitfall.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                playing = true;
            }
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        gotoxy(96, 6);
        cout << "HA";
        Sleep(1000);
        gotoxy(100, 7);
        cout << "HA";
        Sleep(1000);
        gotoxy(104, 8);
        cout << "HA";
        Sleep(1000);
        gotoxy(108, 9);
        cout << "HA";
        gotoxy(96, 6);
        cout << "  ";
        gotoxy(100, 7);
        cout << "  ";
        gotoxy(104, 8);
        cout << "  ";
        gotoxy(108, 9);
        cout << "  ";

        gotoxy(78, 11);
        cout << "#######";
        gotoxy(78, 12);
        cout << "#     #";
        gotoxy(78, 13);
        cout << "#  ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
        cout << player;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "  #";
        gotoxy(78, 14);
        cout << "#     #";
        gotoxy(78, 15);
        cout << "#######";



        gotoxy(95, 13);
        cout << player;
        gotoxy(90, 8);
        cout << "you really thought you can escape?";
        Sleep(2000);
        gotoxy(90, 8);
        cout << "                                     ";
        gotoxy(86, 8);
        cout << "there";
        Sleep(1000);
        gotoxy(86, 8);
        cout << "     ";
        gotoxy(86, 8);
        cout << "is";
        Sleep(1000);
        gotoxy(86, 8);
        cout << "no";
        Sleep(1000);
        gotoxy(86, 8);
        cout << "ESCAPE!";
        Sleep(2000);
        system("CLS");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        gotoxy(73, 10);
        cout << "#################################################";
        for (int i = 0; i + 11 <= 19; i++) {
            gotoxy(73, 11 + i);
            cout << "#                                               #";
        }
        gotoxy(73, 20);
        cout << "#################################################";

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
        gotoxy(88, 12);
        cout << "THANKS FOR PLAYING!";
        gotoxy(87, 15);
        cout << "Collected stars: " << zebranegwiazdy << "/60";
        gotoxy(86, 18);
        cout << "Press space to continue....";
        while (grazaczeta == false) {
            char e = _getch();
            if (e == ' ') {
                MusicBox();
                startmenu();
            }
        }
    }
}

void TheEnd() {
    gotoxy(gracz.x, gracz.y);
    cout << " ";
    gotoxy(76, 2);
    cout << "                                                 ";
    gotoxy(98, 3);
    cout << " ";
    gotoxy(98, 4);
    cout << " ";
    gotoxy(98, 5);
    cout << " ";
    gotoxy(98, 6);
    cout << " ";
    gotoxy(10, 10);
    cout << "                                      ";
    gotoxy(50, 7);
    cout << "          ";
    gotoxy(130, 7);
    cout << "                   ";
    ultrastars = 0;
    liczbakluczy = 0;
    czyjesttutorial = true;
    zapalony = false;
    zliczaniegwiazd();
    deleteobjects();
    world = 0;
    level = 0;
    gracz.x = 100;
    gracz.y = 30;
    gotoxy(98, 30);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;

    if (IsMusicOn == true) {
        if (playing == false) {
            PlaySound(TEXT("laserShoot.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            playing = true;
        }
    }
    for (int i = 0; i < 15; i++) {
        gotoxy(120 - i, 15 - i);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        cout << "&";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    gotoxy(84, 4);
    cout << "WHAT HAVE YOU DONE???";
    for (int i = 0; i < 15; i++) {
        gotoxy(60 + i, 15 - i);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        cout << "&";
    }
    Sleep(2000);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    gotoxy(84, 4);
    cout << "                     ";
    gotoxy(84, 4);
    cout << "OH THIS IS BAD....";
    for (int i = 0; i < 15; i++) {
        gotoxy(87 - i, 27 + i);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
        cout << "&";
    }
    for (int i = 0; i < 15; i++) {
        gotoxy(122 + i, 26 + i);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
        cout << "&";
    }
    Sleep(2000);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    gotoxy(84, 4);
    cout << "                  ";
    gotoxy(84, 4);
    cout << "NO THIS CAN'T BE";
    for (int i = 0; i < 15; i++) {
        gotoxy(80 + i, 16 + i);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cout << "&";
    }
    for (int i = 0; i < 17; i++) {
        gotoxy(54 + i, 18 - i);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cout << "&";
    }
    Sleep(2000);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    gotoxy(84, 4);
    cout << "                 ";
    gotoxy(84, 4);
    cout << "MY CREATION";
    for (int i = 0; i < 15; i++) {
        gotoxy(50 + i, 36 - i);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
        cout << "&";
    }
    Sleep(2000);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    gotoxy(84, 4);
    cout << "            ";
    gotoxy(84, 4);
    cout << "NOOOOOOO";
    Sleep(2000);
    playing = false;
    system("CLS");
    if (IsMusicOn == true) {
        if (playing == false) {
            PlaySound(TEXT("explosion"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            playing = true;
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    gotoxy(93, 12);
    cout << "###########";
    gotoxy(88, 13);
    cout << "######         ######";
    gotoxy(88, 14);
    cout << "#                   #";
    gotoxy(88, 15);
    cout << "#                   #";
    gotoxy(88, 16);
    cout << "#                   #";
    gotoxy(88, 17);
    cout << "#                   #";
    gotoxy(88, 18);
    cout << "######         ######";
    gotoxy(91, 19);
    cout << "#             #";
    gotoxy(91, 20);
    cout << "#             #";
    gotoxy(91, 21);
    cout << "#             #";
    gotoxy(91, 22);
    cout << "###############";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    gotoxy(91, 15);
    cout << "0000       0000";
    gotoxy(90, 16);
    cout << "0    0     0    0";
    gotoxy(90, 17);
    cout << "0    0     0    0";
    gotoxy(92, 18);
    cout << "000       000";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    gotoxy(98, 16);
    cout << "J";
    gotoxy(97, 17);
    cout << "JJJ";
    gotoxy(98, 18);
    cout << "J";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    gotoxy(92, 19);
    cout << "-------------";
    gotoxy(92, 21);
    cout << "-------------";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    gotoxy(96, 14);
    cout << "=====";
    gotoxy(92, 20);
    cout << "=============";

    int liczba = 1;
    for (int i = 0; i < 20; i++) {
        if (i != 0) {
            liczba += 2;
            gotoxy(108 - i, 17 - i);
            for (int z = 0; z < liczba; z++) {
                for (int t = 0; t < liczba; t++) {
                    gotoxy(108 - i, 17 - i + z);
                    if (i % 3 == 0) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    }
                    else if (i % 3 == 1) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                    }
                    else if (i % 3 == 2) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    }
                    cout << "@";
                }
            }
        }
        else {
            gotoxy(98, 17);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << "@";
        }
        Sleep(100);
    }
    PlaySound(NULL, 0, 0);
    playing = false;
    system("CLS");
    Sleep(3000);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    ifstream level24("levels/levelmain/levelThePitfallBoss1.txt");
    if (level24.is_open()) {
        while (getline(level24, plansza)) {
            cout << plansza << endl;
        }
    }
    level24.close();
    for (int i = 18; i < 90; i++) {
        for (int y = 6; y < 28; y++) {
            gotoxy(i, y);
            cout << " ";
        }
    }
    gotoxy(98, 28);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    gotoxy(84, 26);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "There's the exit!";
    Sleep(2000);
    gotoxy(84, 26);
    cout << "Let's finally leave this place for good";
    Sleep(2000);
    gotoxy(84, 26);
    cout << "                                       ";

    if (IsMusicOn == true) {
        if (playing == false) {
            PlaySound(TEXT("SEARCH.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            playing = true;
        }
    }

    gracz.x = 98;
    gracz.y = 28;
    gotoxy(112, 18);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "Game created by ClueSec";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    for (int i = 3; i < 98; i++) {
        gotoxy(gracz.x, gracz.y);
        cout << " ";
        gracz.x -= 1;
        gotoxy(gracz.x, gracz.y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
        cout << player;
        Sleep(40);
        if (i == 45) {
            gotoxy(gracz.x, gracz.y);
            cout << " ";
            gracz.y -= 1;
            gotoxy(gracz.x, gracz.y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
            cout << player;
        }
    }

    system("cls");

    planszaLevel4_5();
    for (int i = 11; i < 151; i++) {
        for (int y = 5; y < 14; y++) {
            gotoxy(i, y);
            cout << " ";
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    gracz.x = 138;
    gracz.y = 9;
    for (int i = 7; i < 138; i++) {
        gotoxy(gracz.x, gracz.y);
        cout << " ";
        gracz.x -= 1;
        gotoxy(gracz.x, gracz.y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
        cout << player;
        Sleep(40);
    }

    system("cls");
    planszaLevel4_2();
    for (int i = 4; i < 104; i++) {
        for (int y = 7; y < 14; y++) {
            gotoxy(i, y);
            cout << " ";
        }
    }

    gotoxy(74, 22);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "Game Director/Programmer: ClueSec";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    gracz.x = 4;
    gracz.y = 8;
    for (int i = 9; i < 102; i++) {
        gotoxy(gracz.x, gracz.y);
        cout << " ";
        gracz.x += 1;
        gotoxy(gracz.x, gracz.y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
        cout << player;
        Sleep(40);
    }

    system("cls");

    planszaLevel3_5();
    for (int i = 16; i < 167; i++) {
        for (int y = 19; y < 27; y++) {
            gotoxy(i, y);
            cout << " ";
        }
    }
    gotoxy(139, 16);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "Additional Support: Kaszmir, Lucy";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    gracz.x = 168;
    gracz.y = 23;
    for (int i = 17; i < 168; i++) {
        gotoxy(gracz.x, gracz.y);
        cout << " ";
        gracz.x -= 1;
        gotoxy(gracz.x, gracz.y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
        cout << player;
        Sleep(45);
    }

    system("cls");

    planszaLevel3_2();
    for (int i = 6; i < 109; i++) {
        for (int y = 5; y < 14; y++) {
            gotoxy(i, y);
            cout << " ";
        }
    }
    gotoxy(78, 19);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "Level Design Director: ClueSec";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    gracz.x = 114;
    gracz.y = 8;
    for (int i = 4; i < 114; i++) {
        gotoxy(gracz.x, gracz.y);
        cout << " ";
        gracz.x -= 1;
        gotoxy(gracz.x, gracz.y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
        cout << player;
        Sleep(45);
    }

    system("cls");

    planszaLevel2_2();
    for (int i = 1; i < 90; i++) {
        for (int y = 13; y < 20; y++) {
            gotoxy(i, y);
            cout << " ";
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    gracz.x = 84;
    gracz.y = 14;
    for (int i = 15; i < 84; i++) {
        gotoxy(gracz.x, gracz.y);
        cout << " ";
        gracz.x -= 1;
        gotoxy(gracz.x, gracz.y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
        cout << player;
        Sleep(45);
    }

    system("cls");

    planszaLevel1_3();
    for (int i = 20; i < 102; i++) {
        for (int y = 13; y < 18; y++) {
            gotoxy(i, y);
            cout << " ";
        }
    }
    gotoxy(39, 9);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "Music/Sounds: ClueSec";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    gracz.x = 100;
    gracz.y = 16;
    for (int i = 17; i < 100; i++) {
        gotoxy(gracz.x, gracz.y);
        cout << " ";
        gracz.x -= 1;
        gotoxy(gracz.x, gracz.y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
        cout << player;
        Sleep(50);
    }

    system("cls");

    planszaLevel1_1();
    for (int i = 1; i < 80; i++) {
        for (int y = 5; y < 12; y++) {
            gotoxy(i, y);
            cout << " ";
        }
    }
    gotoxy(11, 16);
    cout << "                      ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    gracz.x = 80;
    gracz.y = 9;
    for (int i = 1; i < 80; i++) {
        gotoxy(gracz.x, gracz.y);
        cout << " ";
        gracz.x -= 1;
        gotoxy(gracz.x, gracz.y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
        cout << player;
        Sleep(50);
    }

    system("cls");

    gotoxy(14, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    cout << "<==== EXIT (for real now)";
    gotoxy(75, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "@ClueSec 2022";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(1, 9);
    cout << "#####################################################################################################";
    gotoxy(1, 10);
    cout << "#";
    gotoxy(1, 11);
    cout << "#";
    gotoxy(1, 13);
    cout << "#";
    gotoxy(1, 14);
    cout << "#";
    gotoxy(1, 15);
    cout << "#####################################################################################################";
    gracz.x = 100;
    gracz.y = 12;

    for (int i = 2; i < 100; i++) {
        gotoxy(gracz.x, gracz.y);
        cout << " ";
        gracz.x -= 1;
        gotoxy(gracz.x, gracz.y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
        cout << player;
        Sleep(50);
    }

    system("cls");

    PlaySound(NULL, 0, 0);
    playing = false;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    gotoxy(53, 8);
    cout << "###############################################";
    gotoxy(53, 9);
    cout << "#                                             #";
    gotoxy(53, 10);
    cout << "#                                             #";
    gotoxy(53, 11);
    cout << "#                                             #";
    gotoxy(53, 12);
    cout << "###############################################";

    gotoxy(73, 10);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "THE END";

    liczbakluczy = 0;
    czyjesttutorial = true;
    zapalony = false;
    deleteobjects();
    world = 0;
    level = 0;

    while (grazaczeta == false) {
        char e = _getch();
        if (e == ' ') {
            MusicBox();
            system("cls");
            n = 0;
            menu();
        }
    }
}
//

void world1level1() {
    system("cls");
    playing = false;
    grazaczeta = true;
    c = 'h';
    if (czyjesttutorial == true) {
        world1tutorial();
    }
    world = 1;
    level = 1;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel1_1();
    gracz.x = 5;
    gracz.y = 9;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }

    }
    if (grazaczeta == false && playing == false) {
        finished();
    }
}

void world1level2() {
    system("cls");
    c = 'h';
    world = 1;
    level = 2;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel1_2();
    gracz.x = 2;
    gracz.y = 4;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }
    }
    if (grazaczeta == false && playing == false) {
        finished();
    }
}

void world1level3() {
    system("cls");
    playing = false;
    grazaczeta = true;
    c = 'h';
    if (czyjesttutorial == true) {
        world1tutorial2();
    }
    world = 1;
    level = 3;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel1_3();
    gracz.x = 24;
    gracz.y = 14;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }

    }
    if (grazaczeta == false && playing == false) {
        finished();
    }
}

void world1level4() {
    system("cls");
    c = 'h';
    playing = false;
    grazaczeta = true;
    world = 1;
    level = 4;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel1_4();
    gracz.x = 42;
    gracz.y = 7;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }

    }
    if (grazaczeta == false && playing == false) {
        finished();
    }
}

void world1level5() {
    system("cls");
    c = 'h';
    playing = false;
    grazaczeta = true;
    world = 1;
    level = 5;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel1_5();
    gracz.x = 43;
    gracz.y = 47;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }

    }
    if (grazaczeta == false && playing == false) {
        finishedchapter();
    }
}

void world2level1() {
    system("cls");
    playing = false;
    grazaczeta = true;
    c = 'h';
    if (czyjesttutorial == true) {
        world2tutorial1();
    }
    world = 2;
    level = 1;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel2_1();
    gracz.x = 22;
    gracz.y = 7;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }

    }
    if (grazaczeta == false && playing == false) {
        finished();
    }
}

void world2level2() {
    system("cls");
    c = 'h';
    playing = false;
    grazaczeta = true;
    world = 2;
    level = 2;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    gotoxy(2, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "WHICH IS REAL?";
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel2_2();
    gracz.x = 29;
    gracz.y = 11;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }

    }
    if (grazaczeta == false && playing == false) {
        finished();
    }
}

void world2level3() {
    system("cls");
    c = 'h';
    playing = false;
    grazaczeta = true;
    world = 2;
    level = 3;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel2_3();
    gracz.x = 21;
    gracz.y = 13;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }

    }
    if (grazaczeta == false && playing == false) {
        finished();
    }
}

void world2level4() {
    system("cls");
    playing = false;
    grazaczeta = true;
    c = 'h';
    if (czyjesttutorial == true) {
        world2tutorial2();
    }
    world = 2;
    level = 4;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel2_4();
    gracz.x = 27;
    gracz.y = 16;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }

    }
    if (grazaczeta == false && playing == false) {
        finished();
    }
}

void world2level5() {
    system("cls");
    c = 'h';
    playing = false;
    grazaczeta = true;
    world = 2;
    level = 5;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel2_5();
    gracz.x = 67;
    gracz.y = 19;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }

    }
    if (grazaczeta == false && playing == false) {
        finishedchapter();
    }
}

void world3level1() {
    system("cls");
    playing = false;
    grazaczeta = true;
    c = 'h';
    if (czyjesttutorial == true) {
        world3tutorial1();
    }
    world = 3;
    level = 1;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel3_1();
    gracz.x = 32;
    gracz.y = 20;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }

    }
    if (grazaczeta == false && playing == false) {
        finished();
    }
}

void world3level2() {
    system("cls");
    playing = false;
    grazaczeta = true;
    c = 'h';
    world = 3;
    level = 2;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel3_2();
    gracz.x = 91;
    gracz.y = 10;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }

    }
    if (grazaczeta == false && playing == false) {
        finished();
    }
}

void world3level3() {
    system("cls");
    playing = false;
    grazaczeta = true;
    c = 'h';
    if (czyjesttutorial == true) {
        world3tutorial2();
    }
    world = 3;
    level = 3;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel3_3();
    gracz.x = 62;
    gracz.y = 30;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }

    }
    if (grazaczeta == false && playing == false) {
        finished();
    }
}

void world3level4() {
    system("cls");
    playing = false;
    grazaczeta = true;
    c = 'h';
    world = 3;
    level = 4;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel3_4();
    gracz.x = 29;
    gracz.y = 16;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }

    }
    if (grazaczeta == false && playing == false) {
        finished();
    }
}

void world3level5() {
    system("cls");
    c = 'h';
    playing = false;
    grazaczeta = true;
    world = 3;
    level = 5;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel3_5();
    gracz.x = 22;
    gracz.y = 23;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }

    }
    if (grazaczeta == false && playing == false) {
        finishedchapter();
    }
}

void world4level1() {
    system("cls");
    playing = false;
    grazaczeta = true;
    c = 'h';
    if (czyjesttutorial == true) {
        world4tutorial1();
    }
    world = 4;
    level = 1;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel4_1();
    gracz.x = 100;
    gracz.y = 16;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }

    }
    if (grazaczeta == false && playing == false) {
        finished();
    }
}

void world4level2() {
    system("cls");
    playing = false;
    grazaczeta = true;
    c = 'h';
    world = 4;
    level = 2;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel4_2();
    gracz.x = 29;
    gracz.y = 22;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }

    }
    if (grazaczeta == false && playing == false) {
        finished();
    }
}

void world4level3() {
    system("cls");
    playing = false;
    grazaczeta = true;
    c = 'h';
    if (czyjesttutorial == true) {
        world4tutorial2();
    }
    world = 4;
    level = 3;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel4_3();
    gracz.x = 76;
    gracz.y = 32;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }

    }
    if (grazaczeta == false && playing == false) {
        finished();
    }
}

void world4level4() {
    system("cls");
    playing = false;
    grazaczeta = true;
    c = 'h';
    world = 4;
    level = 4;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel4_4();
    gracz.x = 34;
    gracz.y = 16;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }

    }
    if (grazaczeta == false && playing == false) {
        finished();
    }
}

void world4level5() {
    system("cls");
    c = 'h';
    playing = false;
    grazaczeta = true;
    world = 4;
    level = 5;
    starslevelzapis[world - 1][level - 1] = 0;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesLevel4_5();
    gracz.x = 35;
    gracz.y = 38;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }
    }
    if (grazaczeta == false && playing == false) {
        finishedgame();
    }
}

void ThePitfall() {
    if (IsMusicOn == true) {
        if (playing == false) {
            PlaySound(TEXT("The Pitfall.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            playing = true;
        }
    }
    system("cls");
    enter = true;
    gotoxy(78, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    gotoxy(95, 13);
    cout << player;
    gotoxy(90, 8);
    cout << "so....";
    Sleep(2000);
    gotoxy(90, 8);
    cout << "      ";
    gotoxy(86, 8);
    cout << "you finally made it.....";
    Sleep(3000);
    gotoxy(86, 8);
    cout << "                        ";
    gotoxy(86, 8);
    cout << "you have also found all stars....";
    Sleep(4000);
    gotoxy(86, 8);
    cout << "but i won't let you go that easily....";
    Sleep(4000);
    gotoxy(86, 8);
    cout << "let's see if you can escape my most secure prison";
    Sleep(4000);
    gotoxy(86, 8);
    cout << "                                                 ";
    gotoxy(86, 8);
    cout << "one";
    Sleep(2000);
    gotoxy(86, 8);
    cout << "last";
    Sleep(2000);
    gotoxy(86, 8);
    cout << "time";
    Sleep(2000);
    cout << "    ";
    worldThePitfall1();
}

void worldThePitfall1() {
    system("cls");
    c = 'h';
    playing = false;
    grazaczeta = true;
    world = 5;
    intersection = 1;
    LoadLevel();
    if (enter == true) {
        Sleep(5000);
    }
    createEntitiesThePitfall1();
    if (enter == true) {
        Sleep(5000);
    }
    getCursorChar();
    zycia = 5;
    gracz.x = 57;
    gracz.y = 35;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    if (enter == true) {
        Sleep(8000);
        enter = false;
    }
    MusicBox();
    grazaczeta = true;
    playing = true;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }
    }
    if (grazaczeta == false && playing == false) {
        system("CLS");
        liczbakluczy = 0;
        czyjesttutorial = true;
        zapalony = false;
        deleteobjects();
        MusicBox();
        nextlevel();
    }
}

void timer() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    gotoxy(95, 32);
    cout << seconds << "/100%";
    seconds += 1;
    if (seconds == 100) {
        grazaczeta = false;
        playing = false;
    }
}

void worldThePitfall2() {
    system("cls");
    c = 'h';
    playing = false;
    grazaczeta = true;
    world = 5;
    intersection = 2;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesThePitfall2();
    gracz.x = 83;
    gracz.y = 17;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    Sleep(2000);
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            timer();
            updateEntities();
            poruszanie();
        }
    }
    if (grazaczeta == false && playing == false) {
        system("CLS");
        liczbakluczy = 0;
        czyjesttutorial = true;
        zapalony = false;
        deleteobjects();
        MusicBox();
        nextlevel();
    }
}

void worldThePitfall3() {
    system("cls");
    c = 'h';
    playing = false;
    grazaczeta = true;
    world = 5;
    intersection = 3;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesThePitfall3();
    gracz.x = 56;
    gracz.y = 39;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }
    }
    if (grazaczeta == false && playing == false) {
        system("CLS");
        liczbakluczy = 0;
        czyjesttutorial = true;
        zapalony = false;
        deleteobjects();
        MusicBox();
        nextlevel();
    }
}

void worldThePitfallBoss() {
    system("cls");
    c = 'h';
    playing = false;
    grazaczeta = true;
    world = 5;
    intersection = 4;
    LoadLevel();
    MusicBox();
    grazaczeta = true;
    playing = true;
    getCursorChar();
    zycia = 5;
    createEntitiesThePitfallBoss();
    gracz.x = 98;
    gracz.y = 28;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << player;
    spawn.x = gracz.x;
    spawn.y = gracz.y;
    informacjeinfo();
    while (playing == true) {
        while (grazaczeta == true) {
            setCursorInvisible(false);
            update1();
            updateEntities();
            poruszanie();
        }
    }
    if (grazaczeta == false && playing == false) {
        TheEnd();
    }
}

void poruszanie() {
    c = '0';
    if (_kbhit() == 1)
    {
        c = _getch();
    }
}

void startmenu() {
    system("cls");
    for (int i = 0; i < 28; i++) {
        for (int y = 0; y < 130; y++) {
            if (i == 0 || i == 27) { // y
                mainmenu[i][y] = "#";
            }
            else if (y == 0 || y == 129) { // x
                mainmenu[i][y] = "#";
            }
            else {
                mainmenu[i][y] = " ";
            }
        }
    }
    for (int i = 0; i < 28; i++) {
        for (int y = 0; y < 130; y++) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
            cout << mainmenu[i][y];

        }
        cout << endl;
    }


    gotoxy(6, 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "########";
    gotoxy(6, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "#";
    gotoxy(8, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "BACK";
    gotoxy(13, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "#";
    gotoxy(6, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "########";

    gotoxy(58, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    cout << "Select The Chapter";


    gotoxy(117, 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "########";
    gotoxy(117, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "#";
    gotoxy(119, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "SHOP";
    gotoxy(124, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "#";
    gotoxy(117, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "########";


    gotoxy(16, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "#############";
    gotoxy(16, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "#";
    gotoxy(18, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "CHAPTER 1";
    gotoxy(28, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "#";
    gotoxy(16, 16);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "#############";


    gotoxy(46, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "#############";
    gotoxy(46, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "#";
    gotoxy(48, 15);
    if (unlocked[0] == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        cout << "CHAPTER 2";
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "CHAPTER 2";
    }
    gotoxy(58, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "#";
    gotoxy(46, 16);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "#############";

    gotoxy(76, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "#############";
    gotoxy(76, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "#";
    gotoxy(78, 15);
    if (unlocked[1] == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << "CHAPTER 3";
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "CHAPTER 3";
    }
    gotoxy(88, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "#";
    gotoxy(76, 16);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "#############";

    gotoxy(106, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "#############";
    gotoxy(106, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "#";
    gotoxy(108, 15);
    if (unlocked[2] == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        cout << "CHAPTER 4";
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "CHAPTER 4";
    }
    gotoxy(118, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "#";
    gotoxy(106, 16);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "#############";


    gotoxy(61, 21);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "*   " << zebranegwiazdy << "/60   *";


    gotoxy(57, 24);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "####################";
    gotoxy(57, 25);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(59, 25);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "THE      PITFALL";
    gotoxy(76, 25);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(57, 26);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "####################";

    gracz.x = 13;
    gracz.y = 15;

    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    n = 1;
    m = 1;

    while (grazaczeta == false) {
        char e = _getch();
        if (e == 'w' || e == toupper('w')) {
            if (n == 1 && m == 1) {
                gracz.x = 13;
                gracz.y = 15;
                gotoxy(gracz.x, gracz.y);
                cout << " ";

                gracz.x = 3;
                gracz.y = 5;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n = 0;

            }
            else if (n == 2) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";

                gracz.x = 13;
                gracz.y = 15;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n = 1;
                m = 1;
            }
            else if (n == 1 && m == 4) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";

                gracz.x = 114;
                gracz.y = 5;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n = 0;
            }
        }
        if (e == 's' || e == toupper('s')) {
            if (n == 0 && m == 1) {
                gracz.x = 3;
                gracz.y = 5;
                gotoxy(gracz.x, gracz.y);
                cout << " ";

                gracz.x = 13;
                gracz.y = 15;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n += 1;
            }
            else if (n == 0 && m == 4) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";

                gracz.x = 103;
                gracz.y = 15;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n += 1;
            }
            else if (n == 1) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";

                gracz.x = 54;
                gracz.y = 25;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n += 1;

            }
        }
        if (e == 'a' || e == toupper('a')) {
            if (n == 1) {
                if (m == 2) {
                    gracz.x = 43;
                    gracz.y = 15;
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 13;
                    gracz.y = 15;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }
                else if (m == 3) {
                    gracz.x = 73;
                    gracz.y = 15;
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 43;
                    gracz.y = 15;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }
                else if (m == 4) {
                    gracz.x = 103;
                    gracz.y = 15;
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 73;
                    gracz.y = 15;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }

            }
            else if (n == 0) {
                if (m == 4) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 3;
                    gracz.y = 5;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 3;
                }
            }

        }
        if (e == 'd' || e == toupper('d')) {
            if (n == 1) {
                if (m == 1) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 43;
                    gracz.y = 15;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
                else if (m == 2) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 73;
                    gracz.y = 15;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
                else if (m == 3) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 103;
                    gracz.y = 15;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
            }
            if (n == 0) {
                if (m == 1) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 114;
                    gracz.y = 5;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 3;
                }
            }


        }
        else if (e == ' ') {
            if (n == 0) {
                if (m == 1) {
                    system("cls");
                    n = 0;
                    menu();
                }
                else if (m == 4) {
                    system("cls");
                    shop();
                }
            }
            else if (n == 1) {
                if (m == 1) {
                    world1menu();
                }
                else if (m == 2 && unlocked[0] == true) {
                    world2menu();
                }
                else if (m == 3 && unlocked[1] == true) {
                    world3menu();
                }
                else if (m == 4 && unlocked[2] == true) {
                    world4menu();
                }

            }
            else if (n == 2) {
                if (zebranegwiazdy == 60) {
                    ThePitfall();
                }
                else {
                    gotoxy(80, 25);
                    cout << "YOU NEED " << 60 - zebranegwiazdy << " MORE STAR";
                    if (zebranegwiazdy != 59) {
                        cout << "S ";
                    }
                    else {
                        cout << " ";
                    }
                    cout << "TO ENTER....";
                    Sleep(750);
                    gotoxy(80, 25);
                    cout << "                                               ";
                    gotoxy(54, 25);
                }
            }
        }
    }
}

void optionsmenu() {
    system("cls");
    for (int i = 0; i < 28; i++) {
        for (int y = 0; y < 130; y++) {
            if (i == 0 || i == 27) { // y
                mainmenu[i][y] = "#";
            }
            else if (y == 0 || y == 129) { // x
                mainmenu[i][y] = "#";
            }
            else {
                mainmenu[i][y] = " ";
            }
        }
    }
    for (int i = 0; i < 28; i++) {
        for (int y = 0; y < 130; y++) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
            cout << mainmenu[i][y];

        }
        cout << endl;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    gotoxy(62, 7);
    cout << "#########";
    gotoxy(62, 8);
    cout << "# RESET #";
    gotoxy(62, 9);
    cout << "#########";
    gotoxy(62, 13);
    cout << "#########";
    gotoxy(62, 14);
    cout << "# MUSIC #";
    gotoxy(62, 15);
    cout << "#########";
    gotoxy(62, 21);
    cout << "#########";
    gotoxy(62, 20);
    cout << "# BACK  #";
    gotoxy(62, 19);
    cout << "#########";

    gracz.x = 60;
    gracz.y = 8;

    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    n = 0;

    while (grazaczeta == false) {
        char e = _getch();
        if (e == 'w' || e == toupper('w')) {
            if (n <= 0) {
                if (readChar(gracz.x, gracz.y) == player) {

                }
                else {
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                }

            }
            else {
                gotoxy(gracz.x, gracz.y);
                cout << " ";
                gracz.y -= 6;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n -= 1;
            }
        }
        else if (e == 's' || e == toupper('s')) {
            if (n >= 2) {
                if (readChar(gracz.x, gracz.y) == player) {
                    gotoxy(gracz.x - 1, gracz.y);
                    cout << " ";
                }
                else {
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                }
            }
            else {
                gotoxy(gracz.x, gracz.y);
                cout << " ";
                gracz.y += 6;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n += 1;
            }
        }
        else if (e == ' ') {
            if (n == 0) {
                reset();
            }
            else if (n == 1) {
                if (IsMusicOn == true) {
                    PlaySound(NULL, 0, 0);
                    IsMusicOn = false;
                    playingmusic = false;
                    ofstream muzyka("options/MusicMute.txt");

                    if (muzyka.is_open()) {
                        muzyka << IsMusicOn;
                        muzyka.close();
                    }
                }
                else {
                    IsMusicOn = true;
                    playingmusic = true;
                    PlaySound(TEXT("Imprisoned.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                    ofstream muzyka("options/MusicMute.txt");

                    if (muzyka.is_open()) {
                        muzyka << IsMusicOn;
                        muzyka.close();
                    }
                }

            }
            else if (n == 2) {
                system("cls");
                n = 0;
                menu();
            }
        }
    }
}

void opcje() {
    ifstream skin("options/Skin.txt");

    if (skin.is_open()) {
        skin >> wybranapostac;
        skin.close();
    }
    ifstream stars("options/LevelStars.txt");

    if (stars.is_open()) {
        for (int i = 0; i < 4; i++) {
            for (int y = 0; y < 5; y++) {
                stars >> starslevel[i][y];
                starslevelzapis[i][y] = starslevel[i][y];
                if (poczatek == true) {
                    zebranegwiazdy += starslevel[i][y];
                }
            }
        }
        stars.close();
    }

    ifstream odblokowane("options/Unlocked.txt");

    if (odblokowane.is_open()) {
        for (int i = 0; i < 3; i++) {
            odblokowane >> unlocked[i];
        }
        odblokowane.close();
    }

    ifstream muzyka("options/MusicMute.txt");

    if (muzyka.is_open()) {
        muzyka >> IsMusicOn >> playingmusic;
        muzyka.close();
    }

    ifstream kolor("options/Colour.txt");

    if (kolor.is_open()) {
        kolor >> kolorgracza;
        kolor.close();
    }

    ifstream odblokowanepoziomy("options/LevelsUnlocked.txt");

    if (odblokowanepoziomy.is_open()) {
        for (int i = 0; i < 4; i++) {
            for (int z = 0; z < 4; z++) {
                odblokowanepoziomy >> unlockedlevels[i][z];
            }
        }
        odblokowanepoziomy.close();
    }

}

void menu() {
    system("cls");
    world = 0;
    level = 0;
    if (poczatek == true) {
        opcje();
        MusicBox();
        poczatek = false;
    }
    else {

    }
    for (int i = 0; i < 28; i++) {
        for (int y = 0; y < 130; y++) {
            if (i == 0 || i == 27) { // y
                mainmenu[i][y] = "#";
            }
            else if (y == 0 || y == 129) { // x
                mainmenu[i][y] = "#";
            }
            else {
                mainmenu[i][y] = " ";
            }
        }
    }
    for (int i = 0; i < 28; i++) {
        for (int y = 0; y < 130; y++) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
            cout << mainmenu[i][y];

        }
        cout << endl;
    }



    gotoxy(8, 4);
    Sleep(500);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "TTTTTTTTT";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "    H   H   ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "EEEEEEEE            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "PPPPPP      ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "I       ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "TTTTTTTTT    ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "FFFFFFFF     ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << "A         ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "L        L";
    gotoxy(8, 5);
    Sleep(500);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "    T        ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "H   H   ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "E                   ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "P    P      ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "I           ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "T        ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "F           ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << "A A        ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "L        L";
    gotoxy(8, 6);
    Sleep(500);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "    T        ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "HHHHH   ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "EEEE                ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "PPPPPP      ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "I           ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "T        ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "FFFFF      ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << "A   A       ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "L        L";
    gotoxy(8, 7);
    Sleep(500);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "    T        ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "H   H   ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "E                   ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "P           ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "I           ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "T        ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "F         ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << "A AAA A      ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "L        L";
    gotoxy(8, 8);
    Sleep(500);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
    cout << "    T        ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "H   H   ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "EEEEEEEE            ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "P           ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "I           ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "T        ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "F        ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << "A       A     ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "LLLLLLL  LLLLLLL";
    gotoxy(59, 11);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "*   " << zebranegwiazdy << "/60   *";
    gotoxy(62, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "START";
    gotoxy(62, 16);
    cout << "OPTIONS";
    gotoxy(62, 18);
    cout << "EXIT";
    gracz.x = 57;
    gracz.y = 14;

    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    while (grazaczeta == false) {
        char d = _getch();
        if (d == 'w' || d == toupper('w')) {
            if (n <= 0) {
                if (readChar(gracz.x, gracz.y) == player) {

                }
                else {
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                }

            }
            else {
                gotoxy(gracz.x, gracz.y);
                cout << " ";
                gracz.y -= 2;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n -= 1;
            }
        }
        else if (d == 's' || d == toupper('s')) {
            if (n >= 2) {
                if (readChar(gracz.x, gracz.y) == player) {
                    gotoxy(gracz.x - 1, gracz.y);
                    cout << " ";
                }
                else {
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                }
            }
            else {
                gotoxy(gracz.x, gracz.y);
                cout << " ";
                gracz.y += 2;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n += 1;
            }
        }
        else if (d == 'a' || d == toupper('a')) {
            char h = _getch();
            if (h == 'h' || h == toupper('h')) {
                char z = _getch();
                if (z == 'a' || z == toupper('a')) {
                    if (IsMusicOn == true) {
                        if (playing == false) {
                            PlaySound(TEXT("secret.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                            playing = true;
                        }
                    }
                }
            }
        }
        else if (d == ' ') {
            if (n == 0) {
                startmenu();
            }
            else if (n == 1) {
                optionsmenu();
            }
            else if (n == 2) {
                system("cls");
                exit(1);
            }
        }
    }
}

void world1menu() {
    system("cls");
    system("cls");
    for (int i = 0; i < 28; i++) {
        for (int y = 0; y < 130; y++) {
            if (i == 0 || i == 27) { // y
                mainmenu[i][y] = "#";
            }
            else if (y == 0 || y == 129) { // x
                mainmenu[i][y] = "#";
            }
            else {
                mainmenu[i][y] = " ";
            }
        }
    }
    for (int i = 0; i < 28; i++) {
        for (int y = 0; y < 130; y++) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
            cout << mainmenu[i][y];

        }
        cout << endl;
    }


    gotoxy(6, 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "########";
    gotoxy(6, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "#";
    gotoxy(8, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "BACK";
    gotoxy(13, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "#";
    gotoxy(6, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "########";



    gotoxy(14, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(14, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(15, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << 1;
    gotoxy(16, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(14, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(13, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[0][0] << " / 3";


    gotoxy(39, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(39, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(40, 14);
    if (unlockedlevels[0][0] == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << 2;
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << 2;
    }

    gotoxy(41, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(39, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(38, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[0][1] << " / 3";


    gotoxy(64, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(64, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(65, 14);
    if (unlockedlevels[0][1] == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << 3;
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << 3;
    }
    gotoxy(66, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(64, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(63, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[0][2] << " / 3";

    gotoxy(89, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(89, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(90, 14);
    if (unlockedlevels[0][2] == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << 4;
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << 4;
    }
    gotoxy(91, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(89, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(88, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[0][3] << " / 3";

    gotoxy(114, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(114, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(115, 14);
    if (unlockedlevels[0][3] == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << 5;
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << 5;
    }
    gotoxy(116, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(114, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(113, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[0][4] << " / 3";

    gracz.x = 11;
    gracz.y = 14;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    n = 1;
    m = 1;


    while (grazaczeta == false) {
        char e = _getch();
        if (e == 'w' || e == toupper('w')) {
            if (n == 1 && m == 1) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";

                gracz.x = 3;
                gracz.y = 5;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n = 0;

            }
        }
        if (e == 's' || e == toupper('s')) {
            if (n == 0 && m == 1) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";

                gracz.x = 11;
                gracz.y = 14;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n += 1;
            }

        }
        if (e == 'a' || e == toupper('a')) {
            if (n == 1) {
                if (m == 2) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 11;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }
                else if (m == 3) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 36;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }
                else if (m == 4) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 61;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }
                else if (m == 5) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 86;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }

            }


        }
        if (e == 'd' || e == toupper('d')) {
            if (n == 1) {
                if (m == 1) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 36;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
                else if (m == 2) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 61;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
                else if (m == 3) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 86;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
                else if (m == 4) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 111;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
            }
        }
        else if (e == ' ') {
            if (n == 0) {
                if (m == 1) {
                    system("cls");
                    n = 0;
                    startmenu();
                }
            }
            else if (n == 1) {
                if (m == 1) {
                    world1level1();
                }
                else if (m == 2 && unlockedlevels[0][0] == true) {
                    world1level2();
                }
                else if (m == 3 && unlockedlevels[0][1] == true) {
                    world1level3();
                }
                else if (m == 4 && unlockedlevels[0][2] == true) {
                    world1level4();
                }
                else if (m == 5 && unlockedlevels[0][3] == true) {
                    world1level5();
                }
            }
        }
    }
}

void world2menu() {
    system("cls");
    system("cls");
    for (int i = 0; i < 28; i++) {
        for (int y = 0; y < 130; y++) {
            if (i == 0 || i == 27) { // y
                mainmenu[i][y] = "#";
            }
            else if (y == 0 || y == 129) { // x
                mainmenu[i][y] = "#";
            }
            else {
                mainmenu[i][y] = " ";
            }
        }
    }
    for (int i = 0; i < 28; i++) {
        for (int y = 0; y < 130; y++) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
            cout << mainmenu[i][y];

        }
        cout << endl;
    }


    gotoxy(6, 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "########";
    gotoxy(6, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "#";
    gotoxy(8, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "BACK";
    gotoxy(13, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "#";
    gotoxy(6, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "########";



    gotoxy(14, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(14, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(15, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << 1;
    gotoxy(16, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(14, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(13, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[1][0] << " / 3";


    gotoxy(39, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(39, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(40, 14);
    if (unlockedlevels[1][0] == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << 2;
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << 2;
    }
    gotoxy(41, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(39, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(38, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[1][1] << " / 3";


    gotoxy(64, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(64, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(65, 14);
    if (unlockedlevels[1][1] == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << 3;
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << 3;
    }
    gotoxy(66, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(64, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(63, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[1][2] << " / 3";

    gotoxy(89, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(89, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(90, 14);
    if (unlockedlevels[1][2] == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << 4;
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << 4;
    }
    gotoxy(91, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(89, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(88, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[1][3] << " / 3";

    gotoxy(114, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(114, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(115, 14);
    if (unlockedlevels[1][3] == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << 5;
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << 5;
    }
    gotoxy(116, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(114, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(113, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[1][4] << " / 3";

    world = 2;
    gracz.x = 11;
    gracz.y = 14;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    n = 1;
    m = 1;


    while (grazaczeta == false) {
        char e = _getch();
        if (e == 'w' || e == toupper('w')) {
            if (n == 1 && m == 1) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";

                gracz.x = 3;
                gracz.y = 5;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n = 0;

            }
        }
        if (e == 's' || e == toupper('s')) {
            if (n == 0 && m == 1) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";

                gracz.x = 11;
                gracz.y = 14;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n += 1;
            }

        }
        if (e == 'a' || e == toupper('a')) {
            if (n == 1) {
                if (m == 2) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 11;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }
                else if (m == 3) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 36;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }
                else if (m == 4) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 61;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }
                else if (m == 5) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 86;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }

            }


        }
        if (e == 'd' || e == toupper('d')) {
            if (n == 1) {
                if (m == 1) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 36;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
                else if (m == 2) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 61;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
                else if (m == 3) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 86;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
                else if (m == 4) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 111;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
            }
        }
        else if (e == ' ') {
            if (n == 0) {
                if (m == 1) {
                    system("cls");
                    n = 0;
                    startmenu();
                }
            }
            else if (n == 1) {
                if (m == 1) {
                    world2level1();
                }
                else if (m == 2 && unlockedlevels[1][0] == true) {
                    world2level2();
                }
                else if (m == 3 && unlockedlevels[1][1] == true) {
                    world2level3();
                }
                else if (m == 4 && unlockedlevels[1][2] == true) {
                    world2level4();
                }
                else if (m == 5 && unlockedlevels[1][3] == true) {
                    world2level5();
                }
            }
        }
    }
}

void world3menu() {
    system("cls");
    system("cls");
    for (int i = 0; i < 28; i++) {
        for (int y = 0; y < 130; y++) {
            if (i == 0 || i == 27) { // y
                mainmenu[i][y] = "#";
            }
            else if (y == 0 || y == 129) { // x
                mainmenu[i][y] = "#";
            }
            else {
                mainmenu[i][y] = " ";
            }
        }
    }
    for (int i = 0; i < 28; i++) {
        for (int y = 0; y < 130; y++) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
            cout << mainmenu[i][y];

        }
        cout << endl;
    }


    gotoxy(6, 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "########";
    gotoxy(6, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "#";
    gotoxy(8, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "BACK";
    gotoxy(13, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "#";
    gotoxy(6, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "########";



    gotoxy(14, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(14, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(15, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << 1;
    gotoxy(16, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(14, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(13, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[2][0] << " / 3";


    gotoxy(39, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(39, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(40, 14);
    if (unlockedlevels[2][0] == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << 2;
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << 2;
    }
    gotoxy(41, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(39, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(38, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[2][1] << " / 3";


    gotoxy(64, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(64, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(65, 14);
    if (unlockedlevels[2][1] == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << 3;
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << 3;
    }
    gotoxy(66, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(64, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(63, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[2][2] << " / 3";

    gotoxy(89, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(89, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(90, 14);
    if (unlockedlevels[2][2] == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << 4;
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << 4;
    }
    gotoxy(91, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(89, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(88, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[2][3] << " / 3";

    gotoxy(114, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(114, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(115, 14);
    if (unlockedlevels[2][3] == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << 5;
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << 5;
    }
    gotoxy(116, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(114, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(113, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[2][4] << " / 3";

    world = 3;
    gracz.x = 11;
    gracz.y = 14;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    n = 1;
    m = 1;


    while (grazaczeta == false) {
        char e = _getch();
        if (e == 'w' || e == toupper('w')) {
            if (n == 1 && m == 1) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";

                gracz.x = 3;
                gracz.y = 5;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n = 0;

            }
        }
        if (e == 's' || e == toupper('s')) {
            if (n == 0 && m == 1) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";

                gracz.x = 11;
                gracz.y = 14;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n += 1;
            }

        }
        if (e == 'a' || e == toupper('a')) {
            if (n == 1) {
                if (m == 2) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 11;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }
                else if (m == 3) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 36;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }
                else if (m == 4) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 61;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }
                else if (m == 5) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 86;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }

            }


        }
        if (e == 'd' || e == toupper('d')) {
            if (n == 1) {
                if (m == 1) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 36;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
                else if (m == 2) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 61;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
                else if (m == 3) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 86;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
                else if (m == 4) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 111;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
            }
        }
        else if (e == ' ') {
            if (n == 0) {
                if (m == 1) {
                    system("cls");
                    n = 0;
                    startmenu();
                }
            }
            else if (n == 1) {
                if (m == 1) {
                    world3level1();
                }
                else if (m == 2 && unlockedlevels[2][0] == true) {
                    world3level2();
                }
                else if (m == 3 && unlockedlevels[2][1] == true) {
                    world3level3();
                }
                else if (m == 4 && unlockedlevels[2][2] == true) {
                    world3level4();
                }
                else if (m == 5 && unlockedlevels[2][3] == true) {
                    world3level5();
                }
            }
        }
    }
}

void world4menu() {
    system("cls");
    system("cls");
    for (int i = 0; i < 28; i++) {
        for (int y = 0; y < 130; y++) {
            if (i == 0 || i == 27) { // y
                mainmenu[i][y] = "#";
            }
            else if (y == 0 || y == 129) { // x
                mainmenu[i][y] = "#";
            }
            else {
                mainmenu[i][y] = " ";
            }
        }
    }
    for (int i = 0; i < 28; i++) {
        for (int y = 0; y < 130; y++) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
            cout << mainmenu[i][y];

        }
        cout << endl;
    }


    gotoxy(6, 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "########";
    gotoxy(6, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "#";
    gotoxy(8, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "BACK";
    gotoxy(13, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "#";
    gotoxy(6, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "########";



    gotoxy(14, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(14, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(15, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << 1;
    gotoxy(16, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(14, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(13, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[3][0] << " / 3";


    gotoxy(39, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(39, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(40, 14);
    if (unlockedlevels[3][0] == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << 2;
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << 2;
    }
    gotoxy(41, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(39, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(38, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[3][1] << " / 3";


    gotoxy(64, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(64, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(65, 14);
    if (unlockedlevels[3][1] == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << 3;
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << 3;
    }
    gotoxy(66, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(64, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(63, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[3][2] << " / 3";

    gotoxy(89, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(89, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(90, 14);
    if (unlockedlevels[3][2] == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << 4;
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << 4;
    }
    gotoxy(91, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(89, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(88, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[3][3] << " / 3";

    gotoxy(114, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(114, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(115, 14);
    if (unlockedlevels[3][3] == true) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout << 5;
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << 5;
    }
    gotoxy(116, 14);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "#";
    gotoxy(114, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "###";
    gotoxy(113, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << starslevel[3][4] << " / 3";

    world = 4;
    gracz.x = 11;
    gracz.y = 14;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    n = 1;
    m = 1;


    while (grazaczeta == false) {
        char e = _getch();
        if (e == 'w' || e == toupper('w')) {
            if (n == 1 && m == 1) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";

                gracz.x = 3;
                gracz.y = 5;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n = 0;

            }
        }
        if (e == 's' || e == toupper('s')) {
            if (n == 0 && m == 1) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";

                gracz.x = 11;
                gracz.y = 14;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n += 1;
            }

        }
        if (e == 'a' || e == toupper('a')) {
            if (n == 1) {
                if (m == 2) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 11;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }
                else if (m == 3) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 36;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }
                else if (m == 4) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 61;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }
                else if (m == 5) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 86;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }

            }


        }
        if (e == 'd' || e == toupper('d')) {
            if (n == 1) {
                if (m == 1) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 36;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
                else if (m == 2) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 61;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
                else if (m == 3) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 86;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
                else if (m == 4) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 111;
                    gracz.y = 14;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
            }
        }
        else if (e == ' ') {
            if (n == 0) {
                if (m == 1) {
                    system("cls");
                    n = 0;
                    startmenu();
                }
            }
            else if (n == 1) {
                if (m == 1) {
                    world4level1();
                }
                else if (m == 2 && unlockedlevels[3][0] == true) {
                    world4level2();
                }
                else if (m == 3 && unlockedlevels[3][1] == true) {
                    world4level3();
                }
                else if (m == 4 && unlockedlevels[3][2] == true) {
                    world4level4();
                }
                else if (m == 5 && unlockedlevels[3][3] == true) {
                    world4level5();
                }
            }
        }
    }
}

void nextlevel() {
    if (world == 1) {
        if (level == 1) {
            world1level2();
        }
        else if (level == 2) {
            world1level3();
        }
        else if (level == 3) {
            world1level4();
        }
        else if (level == 4) {
            world1level5();
        }
    }
    else if (world == 2) {
        if (level == 1) {
            world2level2();
        }
        else if (level == 2) {
            world2level3();
        }
        else if (level == 3) {
            world2level4();
        }
        else if (level == 4) {
            world2level5();
        }
    }
    else if (world == 3) {
        if (level == 1) {
            world3level2();
        }
        else if (level == 2) {
            world3level3();
        }
        else if (level == 3) {
            world3level4();
        }
        else if (level == 4) {
            world3level5();
        }
    }
    else if (world == 4) {
        if (level == 1) {
            world4level2();
        }
        else if (level == 2) {
            world4level3();
        }
        else if (level == 3) {
            world4level4();
        }
        else if (level == 4) {
            world4level5();
        }
    }
    else if (world == 5) {
        if (intersection == 1) {
            worldThePitfall2();
        }
        else if (intersection == 2) {
            worldThePitfall3();
        }
        else if (intersection == 3) {
            worldThePitfallBoss();
        }
    }
}

void restartlevel() {
    if (world == 1) {
        if (level == 1) {
            world1level1();
        }
        else if (level == 2) {
            world1level2();
        }
        else if (level == 3) {
            world1level3();
        }
        else if (level == 4) {
            world1level4();
        }
        else if (level == 5) {
            world1level5();
        }
    }
    else if (world == 2) {
        if (level == 1) {
            world2level1();
        }
        else if (level == 2) {
            world2level2();
        }
        else if (level == 3) {
            world2level3();
        }
        else if (level == 4) {
            world2level4();
        }
        else if (level == 5) {
            world2level5();
        }
    }
    else if (world == 3) {
        if (level == 1) {
            world3level1();
        }
        else if (level == 2) {
            world3level2();
        }
        else if (level == 3) {
            world3level3();
        }
        else if (level == 4) {
            world3level4();
        }
        else if (level == 5) {
            world3level5();
        }
    }
    else if (world == 4) {
        if (level == 1) {
            world4level1();
        }
        else if (level == 2) {
            world4level2();
        }
        else if (level == 3) {
            world4level3();
        }
        else if (level == 4) {
            world4level4();
        }
        else if (level == 5) {
            world4level5();
        }
    }
    else if (world == 5) {
        if (intersection == 1) {
            worldThePitfall1();
        }
        else if (intersection == 2) {
            worldThePitfall2();
        }
        else if (intersection == 3) {
            worldThePitfall3();
        }
        else if (intersection == 4) {
            worldThePitfallBoss();
        }
    }
}

void worldmenu() {
    if (world == 1) {
        world = 0;
        level = 0;
        MusicBox();
        world1menu();
    }
    else if (world == 2) {
        world = 0;
        level = 0;
        MusicBox();
        world2menu();
    }
    else if (world == 3) {
        world = 0;
        level = 0;
        MusicBox();
        world3menu();
    }
    else if (world == 4) {
        world = 0;
        level = 0;
        MusicBox();
        world4menu();
    }
    else if (world == 5) {
        world = 0;
        level = 0;
        MusicBox();
        startmenu();
    }
}

void shop() {
    system("cls");
    for (int i = 0; i < 28; i++) {
        for (int y = 0; y < 130; y++) {
            if (i == 0 || i == 27) { // y
                mainmenu[i][y] = "#";
            }
            else if (y == 0 || y == 129) { // x
                mainmenu[i][y] = "#";
            }
            else {
                mainmenu[i][y] = " ";
            }
        }
    }
    for (int i = 0; i < 28; i++) {
        for (int y = 0; y < 130; y++) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << mainmenu[i][y];

        }
        cout << endl;
    }
    gotoxy(6, 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "########";
    gotoxy(6, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "#";
    gotoxy(8, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "BACK";
    gotoxy(13, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "#";
    gotoxy(6, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "########";

    gotoxy(65, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    cout << "SHOP";

    gotoxy(34, 11);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << char(111);

    gotoxy(33, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "*0*";

    gotoxy(66, 11);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << char(79);

    gotoxy(65, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "15*";

    gotoxy(101, 11);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << char(142);

    gotoxy(100, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "25*";

    gotoxy(34, 18);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << char(139);

    gotoxy(33, 20);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "40*";

    gotoxy(66, 18);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << char(154);

    gotoxy(65, 20);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "50*";

    gotoxy(101, 18);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << char(153);

    gotoxy(100, 20);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "60*";

    gotoxy(63, 24);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    cout << "COLOUR";
    gotoxy(56, 26);
    cout << "<---";
    gotoxy(73, 26);
    cout << "--->";

    gracz.x = 31;
    gracz.y = 11;
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;
    n = 1;
    m = 1;


    while (grazaczeta == false) {
        char e = _getch();
        if (e == 'w' || e == toupper('w')) {
            if (n == 1) {
                if (m == 1) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";

                    gracz.x = 3;
                    gracz.y = 5;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    n = 0;
                }
            }
            else if (n == 2) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";


                gracz.y -= 7;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n = 1;
            }
            else if (n == 3) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";

                gracz.x = 63;
                gracz.y -= 8;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n = 2;
            }
        }
        if (e == 's' || e == toupper('s')) {
            if (n == 0) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";

                gracz.x = 31;
                gracz.y = 11;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n += 1;
            }
            else if (n == 1) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";

                gracz.y += 7;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n += 1;
            }
            else if (n == 2) {
                gotoxy(gracz.x, gracz.y);
                cout << " ";

                gracz.y += 8;
                gracz.x = 66;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n += 1;
            }

        }
        if (e == 'a' || e == toupper('a')) {
            if (n == 1) {
                if (m == 2) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 31;
                    gracz.y = 11;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }
                else if (m == 3) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 63;
                    gracz.y = 11;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }


            }
            else if (n == 2) {
                if (m == 2) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 31;
                    gracz.y = 18;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }
                else if (m == 3) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 63;
                    gracz.y = 18;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m -= 1;
                }


            }
            else if (n == 3) {
                if (kolorgracza > 1) {
                    kolorgracza -= 1;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    gotoxy(63, 24);
                    cout << "COLOUR";
                    gotoxy(56, 26);
                    cout << "<---";
                    gotoxy(73, 26);
                    cout << "--->";
                }
            }

        }
        if (e == 'd' || e == toupper('d')) {
            if (n == 1) {
                if (m == 1) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 63;
                    gracz.y = 11;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
                else if (m == 2) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 98;
                    gracz.y = 11;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }

            }
            else if (n == 2) {
                if (m == 1) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 63;
                    gracz.y = 18;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }
                else if (m == 2) {
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";


                    gracz.x = 98;
                    gracz.y = 18;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    m += 1;
                }

            }
            else if (n == 3) {
                if (kolorgracza != 14) {
                    kolorgracza += 1;
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                    gotoxy(63, 24);
                    cout << "COLOUR";
                    gotoxy(56, 26);
                    cout << "<---";
                    gotoxy(73, 26);
                    cout << "--->";
                }
            }
        }
        else if (e == ' ') {
            if (n == 0) {
                if (m == 1) {
                    system("cls");
                    n = 0;
                    startmenu();
                }
            }
            else if (n == 1) {
                if (m == 1) {
                    wybranapostac = 1;
                    gotoxy(gracz.x, gracz.y);
                    cout << " ";
                    Postac();
                    gotoxy(gracz.x, gracz.y);
                    cout << player;
                }
                else if (m == 2) {
                    if (zebranegwiazdy >= 15) {
                        wybranapostac = 2;
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        Postac();
                        gotoxy(gracz.x, gracz.y);
                        cout << player;
                    }
                }
                else if (m == 3) {
                    if (zebranegwiazdy >= 25) {
                        wybranapostac = 3;
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        Postac();
                        gotoxy(gracz.x, gracz.y);
                        cout << player;
                    }
                }
            }
            else if (n == 2) {
                if (m == 1) {
                    if (zebranegwiazdy >= 40) {
                        wybranapostac = 4;
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        Postac();
                        gotoxy(gracz.x, gracz.y);
                        cout << player;
                    }
                }
                else if (m == 2) {
                    if (zebranegwiazdy >= 50) {
                        wybranapostac = 5;
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        Postac();
                        gotoxy(gracz.x, gracz.y);
                        cout << player;
                    }
                }
                else if (m == 3) {
                    if (zebranegwiazdy == 60) {
                        wybranapostac = 6;
                        gotoxy(gracz.x, gracz.y);
                        cout << " ";
                        Postac();
                        gotoxy(gracz.x, gracz.y);
                        cout << player;
                    }
                }
            }
        }
        ofstream skin2("options/Colour.txt");
        if (skin2.is_open()) {
            skin2 << wybranapostac;
            skin2.close();
        }
        ofstream kolor("options/Colour.txt");
        if (kolor.is_open()) {
            kolor << kolorgracza;
            kolor.close();
        }
    }
}

void reset() {
    ofstream reset2("options/LevelStars.txt");
    gotoxy(75, 8);
    cout << "ARE YOU SURE? Y/N";
    bool r = false;
    while (!r) {
        char d = _getch();
        if (d == 'y' || d == toupper('y')) {
            if (reset2.is_open()) {
                for (int i = 0; i < 4; i++) {
                    for (int y = 0; y < 5; y++) {
                        starslevel[i][y] = 0;
                        reset2 << starslevel[i][y];
                        reset2 << endl;
                    }
                    reset2 << endl;
                }
                reset2.close();

                ofstream reset3("options/Skin.txt");
                if (reset3.is_open()) {
                    reset3 << 1;
                }
                reset3.close();

                ofstream reset4("options/Unlocked.txt");

                if (reset4.is_open()) {
                    for (int i = 0; i < 3; i++) {
                        unlocked[i] = 0;
                        reset4 << unlocked[i];
                        reset4 << endl;
                    }
                    reset4.close();
                }

                ofstream kolor("options/Colour.txt");
                if (kolor.is_open()) {
                    kolorgracza = 1;
                    kolor << kolorgracza;
                    kolor.close();
                }

                ofstream odblokowanepoziomy("options/LevelsUnlocked.txt");

                if (odblokowanepoziomy.is_open()) {
                    for (int i = 0; i < 4; i++) {
                        for (int z = 0; z < 4; z++) {
                            unlockedlevels[i][z] = 0;
                            odblokowanepoziomy << unlockedlevels[i][z];
                            odblokowanepoziomy << endl;
                        }
                        odblokowanepoziomy << endl;
                    }
                    odblokowanepoziomy.close();
                }

                wybranapostac = 1;
                zebranegwiazdy = 0;
                gotoxy(75, 8);
                cout << "                    ";
                gotoxy(75, 8);
                cout << "RESET SUCCESFUL";
                Sleep(1000);
                gotoxy(75, 8);
                cout << "                    ";
                r = true;
            }
        }
        else if (d == 'n' || d == toupper('n')) {
            gotoxy(75, 8);
            cout << "                    ";
            gotoxy(75, 8);
            cout << "RESET CANCELLED";
            Sleep(1000);
            gotoxy(75, 8);
            cout << "                    ";
            r = true;
        }
    }
}

void poczatekmenu() {
    gotoxy(gracz.x, gracz.y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
    Postac();
    cout << player;


    while (grazaczeta == false) {
        char d = _getch();
        if (d == 'w' || d == toupper('w')) {
            if (n <= 0) {
                if (readChar(gracz.x, gracz.y) == player) {

                }
                else {
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                }

            }
            else {
                gotoxy(gracz.x, gracz.y);
                cout << " ";
                gracz.y -= 2;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n -= 1;
            }
        }
        else if (d == 's' || d == toupper('s')) {
            if (n >= 2) {
                if (readChar(gracz.x, gracz.y) == player) {
                    gotoxy(gracz.x - 1, gracz.y);
                    cout << " ";
                }
                else {
                    gotoxy(gracz.x, gracz.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                    Postac();
                    cout << player;
                }
            }
            else {
                gotoxy(gracz.x, gracz.y);
                cout << " ";
                gracz.y += 2;
                gotoxy(gracz.x, gracz.y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolorgracza);
                Postac();
                cout << player;
                n += 1;
            }
        }
        else if (d == ' ') {
            if (n == 0) {
                startmenu();
            }
            else if (n == 1) {
                optionsmenu();
            }
            else if (n == 2) {
                system("cls");
                exit(1);
            }
        }
    }

}

void start() {
    setCursorInvisible(false);
    menu();
}

int main()
{
    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
    start();
    return 0;
}
