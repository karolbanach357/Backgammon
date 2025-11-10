#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include "conio2.h"
#include <time.h>

#define ROLLS 2
#define AREA 24
#define MAX_PONS 6
#define PONS 15

#define POS_BOARD_Y 4 
#define POS_BOARD_X 2 
#define MAX_POS_BOARD_Y 21
#define MAX_POS_BOARD_X 76
#define POLE_1 "/\\"
#define POLE_2 "\\/"
#define POLE_0 ".."
#define BORDER_1 30 //trojkat w gore
#define BORDER_2 31 //trojkat w dol
#define POS_OPCJE_X 80
#define POS_OPCJE_Y 10
#define ERR_Y 23

#define MENU_X 5
#define MENU_Y 5

//deifnicje klawiszy
#define ENTER 13
#define UP 72 //Strzalka w gore
#define DOWN 80 //Strzaka w dol
#define BACK_ 8 //Backspace

#define PON 178

#define TRUE 1
#define FALSE 0

#define PART_13_18 8
#define PART_19_24 42
#define PART_1_6 67
#define PART_7_12 33
#define PART_N_Y 5
#define PART_S_Y 19
#define CO_ILE_POLE 5

typedef enum
{
    none,
    yellow,
    ligthred
} color;
typedef enum
{
    one,
    two
} ply;

typedef struct
{
    int ile_pawns;
    color kolor;
}pole;
typedef struct gra
{
    int home1;
    int home2;
    pole plansza[24];
    ply player;
    int banda1;
    int banda2;
    int rzut1;
    int rzut2;
    int punkty1;
    int punkty2;
} Bakgammon;

// RYSOWANIE INTERFEJSU PLANSZY

void border_board() //wypisuje obramowanie planszy
{
    textcolor(BROWN);
    gotoxy(POS_BOARD_X, POS_BOARD_Y);
    for (int i = POS_BOARD_X; i < MAX_POS_BOARD_X; i++)
    {
        if (i % 2 == 0)
            putch(BORDER_1);
        else
            putch(BORDER_2);
    }
    for (int i = POS_BOARD_Y; i < MAX_POS_BOARD_Y; i++)
    {
        gotoxy(POS_BOARD_X, i);
        putch(BORDER_1);
        putch(BORDER_2);
    }
    for (int i = POS_BOARD_X; i < MAX_POS_BOARD_X; i++)
    {
        if (i % 2 == 1)
            putch(BORDER_2);
        else
            putch(BORDER_1);
    }
    for (int i = POS_BOARD_Y; i < MAX_POS_BOARD_Y; i++)
    {
        gotoxy(MAX_POS_BOARD_X, i);
        putch(BORDER_1);
        putch(BORDER_2);
    }
    textcolor(WHITE);
}
void inside_parts(int position_x, int position_y) //Czesc polnocna planszy
{
    gotoxy(position_x, position_y);

    for (int i = 0; i <= MAX_PONS; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cputs(POLE_0);
            printf("   ");
            cputs(POLE_2);
            printf("   ");
        }
        gotoxy(position_x, position_y + i);
    }
}
void inside_parts_2(int position_x, int position_y) //Czesc poludniowa planszy
{
    gotoxy(position_x, position_y);

    for (int i = 1; i <= MAX_PONS; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cputs(POLE_1);
            printf("   ");
            cputs(POLE_0);
            printf("   ");
        }
        gotoxy(position_x, position_y - i);
    }
}
void inside_board()
{
    inside_parts(PART_13_18, PART_N_Y);
    inside_parts(PART_19_24, PART_N_Y);
    inside_parts_2(PART_19_24, PART_S_Y);
    inside_parts_2(PART_13_18, PART_S_Y);
}
void numbers_board()
{
    int j = 0; //zmienna potrzebna do przesuwania
    for (int i = 13; i <= 18; i++)
    {
        gotoxy(PART_13_18 + (j * CO_ILE_POLE), POS_BOARD_Y - 1);
        printf("%d", i);
        j++;
    }
    j = 0;
    for (int i = 19; i <= 24; i++)
    {
        gotoxy(PART_19_24 + (j * CO_ILE_POLE), POS_BOARD_Y - 1);
        printf("%d", i);
        j++;
    }
    j = 0;
    for (int i = 12; i > 6; i--)
    {
        gotoxy(PART_13_18 + (j * CO_ILE_POLE), MAX_POS_BOARD_Y);
        printf("%d", i);
        j++;
    }
    j = 0;
    for (int i = 6; i > 0; i--)
    {
        gotoxy(PART_19_24 + (j * CO_ILE_POLE), MAX_POS_BOARD_Y);
        printf("%d", i);
        j++;
    }
}
void bar_board()
{
    gotoxy(MAX_POS_BOARD_X / 2 - 1, POS_BOARD_Y + 1);
    for (int i = POS_BOARD_Y + 1; i < MAX_POS_BOARD_Y; i++)
    {
        if (i == MAX_POS_BOARD_Y / 2 + 3)
            cputs("BAR");
        else
            cputs("|||");
        gotoxy(MAX_POS_BOARD_X / 2 - 1, i);
    }
}
void opcje_board()
{
    int i = 0;
    gotoxy(POS_OPCJE_X, POS_BOARD_Y + i++);
    cputs("=========OPCJE=======");
    gotoxy(POS_OPCJE_X, POS_BOARD_Y + i++);
    cputs("| q - wyjscie z gry |");
    gotoxy(POS_OPCJE_X, POS_BOARD_Y + i++);
    cputs("| m - opcja ruchu   |");
    gotoxy(POS_OPCJE_X, POS_BOARD_Y + i++);
    cputs("| s - zapisz gre    |");
    gotoxy(POS_OPCJE_X, POS_BOARD_Y + i++);
    cputs("| w - wczytaj gre   |");
    gotoxy(POS_OPCJE_X, POS_BOARD_Y + i++);
    cputs("=====================");
    gotoxy(POS_OPCJE_X, POS_BOARD_Y + i++);
}

// KOSTKI DO GRY
int roll_throw()
{
    return rand() % 6 + 1;
}
void rolls_show(struct gra* Gra) // KOSTKI --> CZEMU NIE DZIALACIE
{
    gotoxy(POS_BOARD_X + CO_ILE_POLE, MAX_POS_BOARD_Y / 2 + 2);
    printf("Rolls: [%d][%d] \n", Gra->rzut1, Gra->rzut2);
}

// RYSOWANIE PIONKOW
void kolor_pionka(struct gra* Gra, int index)
{
    if (Gra->plansza[index].kolor == yellow)
        textcolor(YELLOW);
    else if (Gra->plansza[index].kolor == ligthred)
        textcolor(LIGHTRED);
    else
        textcolor(WHITE);
}
bool rys_gora_dol(int index)
{
    if (index <= 11) // mowi o tym ze do 11 pola planszy sprawdza dany index
        return true; //oznacza ze rysuje w gore
    else
        return false; // oznacza ze rysuje w dol
}
void rys_pionek(int position_x, int position_y, struct gra* Gra, int index)
{
    kolor_pionka(Gra, index);
    for (int i = NULL; i < Gra->plansza[index].ile_pawns; i++)
    {
        if (rys_gora_dol(index) == true)
        {
            gotoxy(position_x, position_y - i);
            putch(PON);
            putch(PON);
        }
        else
        {
            gotoxy(position_x, position_y + i);
            putch(PON);
            putch(PON);
        }
    }
    textcolor(WHITE);
}
void draw_game(struct gra* Gra)
{
    int index = 0;
    for (int i = 0; i < MAX_PONS; i++)
    {
        rys_pionek(PART_1_6 - (CO_ILE_POLE * i), PART_S_Y, Gra, index++);
    }
    for (int i = 0; i < MAX_PONS; i++)
    {
        rys_pionek(PART_7_12 - (CO_ILE_POLE * i), PART_S_Y, Gra, index++);
    }
    for (int i = 0; i < MAX_PONS; i++)
    {
        rys_pionek(PART_13_18 + (CO_ILE_POLE * i), PART_N_Y, Gra, index++);
    }
    for (int i = 0; i < MAX_PONS; i++)
    {
        rys_pionek(PART_19_24 + (CO_ILE_POLE * i), PART_N_Y, Gra, index++);
    }


}

// RYSOWANIE GRACZA
void gracz_dane(struct gra* Gra)
{
    gotoxy(POS_OPCJE_X, MAX_POS_BOARD_Y - 4);
    cputs("Ruch gracza:  ");
    printf("%d", Gra->player + 1);
    gotoxy(POS_OPCJE_X, MAX_POS_BOARD_Y - 2);
    cputs("Pionki gracza 1 w domu: "); printf("%d", Gra->home1);
    gotoxy(POS_OPCJE_X, MAX_POS_BOARD_Y - 1);
    cputs("Pionki gracza 2 w domu: "); printf("%d", Gra->home2);
}

// WARTOSCI POCZATKOWE
void podstawowe_wartosci(struct gra* Gra)
{
    for (int i = 0; i < AREA; i++)
    {
        Gra->plansza[i].kolor = none;
        Gra->plansza[i].ile_pawns = NULL;
    }
    Gra->home1 = 0;
    Gra->home2 = 0;
    Gra->banda1 = 0;
    Gra->banda2 = 0;
}
void start_pons_player1(struct gra* Gra) //Inicjalizuje pozycje poczatkowe pionkow gracza 1
{
    Gra->plansza[0].kolor = yellow;
    Gra->plansza[0].ile_pawns = 2;

    Gra->plansza[11].kolor = yellow;
    Gra->plansza[11].ile_pawns = 5;

    Gra->plansza[16].kolor = yellow;
    Gra->plansza[16].ile_pawns = 3;

    Gra->plansza[18].kolor = yellow;
    Gra->plansza[18].ile_pawns = 5;
}
void start_pons_player2(struct gra* Gra) //Inicjalizuje pozycje startowe pionkow gracza 2
{
    Gra->plansza[5].kolor = ligthred;
    Gra->plansza[5].ile_pawns = 5;

    Gra->plansza[7].kolor = ligthred;
    Gra->plansza[7].ile_pawns = 3;

    Gra->plansza[12].kolor = ligthred;
    Gra->plansza[12].ile_pawns = 5;

    Gra->plansza[23].kolor = ligthred;
    Gra->plansza[23].ile_pawns = 2;
}
int kto_zaczyna(struct gra* gra)
{
    srand(time(NULL));
    gra->rzut1 = roll_throw();
    gra->rzut2 = roll_throw();
    rolls_show(gra);
    if (gra->rzut1 > gra->rzut2)
    {
        gotoxy(POS_BOARD_X, POS_BOARD_Y);//wypisuje ze zaczyna dany gracz
        cputs("Zaczyna gracz pierwszy");
        getch();
        return gra->player = one;
    }
    else if (gra->rzut1 < gra->rzut2)
    {
        //wypisuje ze zaczyna dany gracz
        gotoxy(POS_BOARD_X, POS_BOARD_Y);
        cputs("Zaczyna gracz drugi");
        getch();
        return gra->player = two;
    }

    else
    {
        gotoxy(POS_BOARD_X, POS_BOARD_Y);
        cputs("Powtorz rzuty"); // wypisuje ze jeszcze raz musi zosta� wykonany rzut
        getch();
        return kto_zaczyna(gra);
    }

}
void inicjalizacja_wstepnych_wartosci(struct gra* Gra)
{
    podstawowe_wartosci(Gra);
    start_pons_player1(Gra);
    start_pons_player2(Gra);
    kto_zaczyna(Gra);
}

// MECHANIKA GRY
void check_player(struct gra* Gra) // sprawdza w ktora strone rusza sie dnay gracz
{
    if (Gra->player == two)
    {
        Gra->rzut1 = Gra->rzut1 * (-1);
    }
}
void change_player(struct gra* Gra) //zmienia runde gracza
{
    if (Gra->player == one)
        Gra->player = two;
    else
        Gra->player = one;
}
bool check_input(struct gra* Gra, int from, int to) // tutaj nagle zmienia sie cos
{
    if (Gra->player == one)
    {
        if (to - from == Gra->rzut1)
        {
            Gra->rzut1 = 0;
            return true;
        }
        else if (to - from == Gra->rzut2)
        {
            Gra->rzut2 = 0;
            return true;
        }
        else
            return false;
    }
    if (Gra->player == two)
    {
        if (from - to == Gra->rzut1)
        {
            Gra->rzut1 = 0;
            return true;
        }
        else if (from - to == Gra->rzut2)
        {
            Gra->rzut2 = 0;
            return true;
        }
        else
            return false;
    }
    return false;
}
void bije_pon(struct gra* Gra, int to)
{
    if (Gra->player == one) // pierwszy player ma zolte
    {
        Gra->plansza[to].ile_pawns = NULL;
        Gra->plansza[to].kolor = none;
        Gra->banda2++;
    }
    if (Gra->player == two)
    {
        Gra->plansza[to].ile_pawns = NULL;
        Gra->plansza[to].kolor = none;
        Gra->banda1++;
    }
}
bool check_move(struct gra* Gra, int from, int to)  // NIE SPRAWDZA POPRAWNOSCI RUCHU PO ZROBIENIU GO
{
    if (from > AREA || to >= AREA || to < 0)
        return false;
    if (Gra->plansza[from].kolor == yellow && Gra->player == two) // sprawdza czy wgl jest pionek
        return false;
    if (Gra->plansza[from].kolor == ligthred && Gra->player == one) // sprawdza czy wgl jest pionek
        return false;
    if (Gra->plansza[from].kolor == none) // sprawdza czy wgl jest pionek
        return false;
    if (Gra->plansza[from].kolor == Gra->plansza[to].kolor) //jesli pionki sa takie same
        return true;
    if (Gra->plansza[to].ile_pawns == NULL) //jesli nic nie ma na polu gdzie chcemy pojsc
    {
        Gra->plansza[to].kolor = Gra->plansza[from].kolor;
        return true;
    }
    if (Gra->plansza[from].kolor != Gra->plansza[to].kolor && Gra->plansza[to].kolor != none && Gra->plansza[to].ile_pawns == 1) //jesli na polu jest 1 pionek przeciwnika
    {
        bije_pon(Gra, to);
        return true;
    }
    return false;
}

// standardowe ruchy
void make_move(struct gra* Gra, int from, int to)
{

    if (Gra->plansza[from].ile_pawns == 1) // jezeli ostatni pionek to zmienia kolor na zaden
    {
        Gra->plansza[from].kolor = none;
    }
    Gra->plansza[to].ile_pawns++;
    Gra->plansza[from].ile_pawns--;
    if (Gra->player == one)
    {
        Gra->plansza[to].kolor = yellow;
    }
    else
        Gra->plansza[to].kolor = ligthred;

}

// ruchy zwiazane z biciem
bool zbicie_pionka_przez_one(struct gra* Gra)
{
    for (int i = 0; i < AREA; i++)
    {
        if (Gra->plansza[i].kolor == yellow)
        {
            if (Gra->plansza[i + Gra->rzut1].ile_pawns == 1 && Gra->plansza[i + Gra->rzut1].kolor == ligthred && i + Gra->rzut1 < AREA && Gra->rzut1 != 0)
            {
                bije_pon(Gra, i + Gra->rzut1);
                make_move(Gra, i, i + Gra->rzut1);
                Gra->rzut1 = 0;
                return true;
            }
            if (Gra->plansza[i + Gra->rzut2].ile_pawns == 1 && Gra->plansza[i + Gra->rzut2].kolor == ligthred && i + Gra->rzut2 < AREA && Gra->rzut2 != 0)
            {
                bije_pon(Gra, i + Gra->rzut2);
                make_move(Gra, i, i + Gra->rzut2);
                Gra->rzut2 = 0;
                return true;
            }
        }
    }
    return false;
}
bool zbicie_pionka_przez_two(struct gra* Gra)
{
    for (int i = AREA - 1; i >= 0; i--)
    {
        if (Gra->plansza[i].kolor == ligthred)
        {
            if (Gra->plansza[i - Gra->rzut1].ile_pawns == 1 && Gra->plansza[i - Gra->rzut1].kolor == yellow && i - Gra->rzut1 >= 0 && Gra->rzut1 != 0)
            {
                bije_pon(Gra, i - Gra->rzut1);
                make_move(Gra, i, i - Gra->rzut1);
                Gra->rzut1 = 0;
                return true;
            }
            if (Gra->plansza[i - Gra->rzut2].ile_pawns == 1 && Gra->plansza[i - Gra->rzut2].kolor == yellow && i - Gra->rzut2 >= 0 && Gra->rzut2 != 0)
            {
                bije_pon(Gra, i - Gra->rzut2);
                make_move(Gra, i, i - Gra->rzut2);
                Gra->rzut2 = 0;
                return true;
            }
        }
    }
    return false;
}
bool zbicie_pionka(struct gra* Gra)
{
    if (Gra->player == one)
    {
        if (zbicie_pionka_przez_one(Gra) == true)
        {
            return true;
        }
    }
    else
    {
        if (zbicie_pionka_przez_two(Gra) == true)
        {
            return true;
        }
    }
    return false;
}

bool koniec_gry(struct gra* Gra) //sprawdza czy gdzies jest 15 pionkow w poszczegolnych domach graczy
{

    if (Gra->home1 == PONS)
    {
        clrscr();
        Gra->punkty1++;

        printf("\nWygral gracz 1\n");
        printf("Punkty 1: %d\n", Gra->punkty1);
        printf("Punkty 2: %d", Gra->punkty2);
        return true;
    }
    else if (Gra->home2 == PONS)
    {
        clrscr();
        Gra->punkty2++;
        printf("\nWygral gracz 2\n");
        printf("Punkty 1: %d\n", Gra->punkty1);
        printf("Punkty 2: %d", Gra->punkty2);
        return true;
    }
    else
    {
        return false;
    }
}

// ruchy zwiazane z wejsciem do domu
bool check_move_dwor_to_home_one(struct gra* Gra)
{
    for (int i = AREA - 1; i >= 18; i--)
    {
        if (Gra->plansza[i].kolor == yellow)
        {
            if (i + Gra->rzut1 >= AREA || i + Gra->rzut2 >= AREA)
            {
                return true;
            }
            else
                return false;
        }
    }

}
int ruch_do_dom_one(struct gra* Gra)
{
    int home = AREA;
    for (int i = 17; i < AREA; i++) //i: AREA - 6 = 18 - 1 = 17
    {
        if (Gra->plansza[i].kolor == yellow)
        {
            if (i + Gra->rzut1 >= home)
            {
                Gra->home1++;
                Gra->plansza[i].ile_pawns--;
                if (Gra->plansza[i].ile_pawns == 0)
                {
                    Gra->plansza[i].kolor = none;
                }
                Gra->rzut1 = 0;
                return 1;
            }
            else if (i + Gra->rzut2 >= home)
            {
                Gra->home1++;
                Gra->plansza[i].ile_pawns--;
                if (Gra->plansza[i].ile_pawns == 0)
                {
                    Gra->plansza[i].kolor = none;
                }
                Gra->rzut2 = 0;
                return 1;
            }

        }
    }
    return 0;
}
bool check_dwor_one(struct gra* Gra)
{
    int ilosc_dwor = 0;
    for (int i = AREA - 1; i >= 18; i--)
    {
        if (Gra->plansza[i].kolor == yellow)
            ilosc_dwor += Gra->plansza[i].ile_pawns;
    }
    if (check_move_dwor_to_home_one(Gra) == false)
    {
        return false;
    }
    if (ilosc_dwor + Gra->home1 == PONS)
    {
        return true;
    }
    return false;
}

bool check_move_dwor_to_home_two(struct gra* Gra)
{
    for (int i = 0; i < 6; i++)
    {
        if (Gra->plansza[i].kolor == ligthred)
        {
            if (i - Gra->rzut1 <= -1 || i - Gra->rzut2 <= -1)
            {
                return true;
            }
            else
                return false;
        }
    }
}
int ruch_do_dom_two(struct gra* Gra)
{
    int home = -1;
    for (int i = 5; i >= NULL; i--)
    {
        if (Gra->plansza[i].kolor == ligthred)
        {
            if (i - Gra->rzut1 <= home)
            {
                Gra->home2++;
                Gra->plansza[i].ile_pawns--;
                if (Gra->plansza[i].ile_pawns == 0)
                {
                    Gra->plansza[i].kolor = none;
                }
                Gra->rzut1 = 0;
                return 1;
            }
            if (i - Gra->rzut2 <= home)
            {
                Gra->home2++;
                Gra->plansza[i].ile_pawns--;
                if (Gra->plansza[i].ile_pawns == 0)
                {
                    Gra->plansza[i].kolor = none;
                }
                Gra->rzut2 = 0;
                return 1;
            }
        }
    }
}
bool check_dwor_two(struct gra* Gra)
{
    int ilosc_dwor = 0;
    for (int i = NULL; i < 6; i++)
    {
        if (Gra->plansza[i].kolor == ligthred)
            ilosc_dwor += Gra->plansza[i].ile_pawns;
    }
    if (check_move_dwor_to_home_two(Gra) == false)
    {
        return false;
    }
    if (ilosc_dwor + Gra->home2 == PONS)
    {
        return true;
    }
    return false;
}

bool czy_pelny_dwor(struct gra* Gra)
{
    if (Gra->player == one)
    {
        if (check_dwor_one(Gra) == true)
        {
            ruch_do_dom_one(Gra);
            return true;
        }
        else
            return false;
    }
    else
    {
        if (check_dwor_two(Gra) == true)
        {
            ruch_do_dom_two(Gra);
            return true;
        }
        else
            return false;
    }
    return false;
}


// czyszczenie opcji
void wyczysc() // czysci wszystkie polecenia wyswietlane wczesniej
{
    for (int i = POS_OPCJE_Y; i < MAX_POS_BOARD_Y - 4; i++)
    {
        gotoxy(POS_OPCJE_X, i);
        clreol();
    }
}
void wyczysc_input()
{
    for (int i = MAX_POS_BOARD_Y + 3; i <= MAX_POS_BOARD_Y + 4; i++)
    {
        gotoxy(POS_BOARD_X, i);
        clreol();
    }
}


// ruchy zwiazane z BANDA 
void banda_show(struct gra* Gra)
{
    if (Gra->player == one && Gra->banda1 != 0)
    {
        gotoxy(MAX_POS_BOARD_X / 2 + 5, MAX_POS_BOARD_Y / 2 + 2);
        cputs("banda 1: ");
        printf("%d", Gra->banda1);
    }
    if (Gra->player == two && Gra->banda2 != 0)
    {
        gotoxy(MAX_POS_BOARD_X / 2 + 5, MAX_POS_BOARD_Y / 2 + 2);
        cputs("banda 2: ");
        printf("%d", Gra->banda2);
    }
}
bool check_banda(struct gra* Gra)//sprawdza czy nie ma pionka danego gracza na bandzie
{
    if (Gra->player == one && Gra->banda1 != NULL)
    {
        return true;
    }
    if (Gra->player == two && Gra->banda2 != NULL)
    {
        return true;
    }
    return false;
}
bool check_m_banda(struct gra* Gra, int to)
{
    to--;
    if (Gra->player == one)
    {
        if (Gra->plansza[to].kolor != ligthred)
            return true;
        else if (Gra->plansza[to].ile_pawns == 1)
        {
            bije_pon(Gra, to);
            return true;
        }
        return false;
    }
    else
    {
        if (Gra->plansza[to].kolor != yellow)
            return true;
        else if (Gra->plansza[to].ile_pawns == 1)
        {
            bije_pon(Gra, to);
            return true;
        }
        return false;
    }
}
void make_m_banda(struct gra* Gra, int to)
{
    to--; // odejmuje aby zgadzaly sie pola licozne w tablicy od 0
    Gra->plansza[to].ile_pawns++;
    if (Gra->player == one)
    {
        Gra->banda1--;
        Gra->plansza[to].kolor = yellow;
    }
    else
    {
        Gra->banda2--;
        Gra->plansza[to].kolor = ligthred;
    }

}

// DO WYPISYWANIA KOMENDY
int wypisz(int x, int y)
{
    int i = NULL;
    bool koniec = false;
    int tab[3] = {-1,-1,-1};
    gotoxy(x, y);
    while (!koniec)
    {
        int key = getche();
        if (key == BACK_ && i > 0)
        {
            cputs(" ");
            gotoxy(wherex() - 2, wherey());
            tab[i - 1] = -1;
            i--;
        }
        else if (key == ENTER)
        {
            koniec = true;
        }
        else if (key != ENTER && key != BACK_)
        {
            char znak = key;
            tab[i] = znak - '0';
            i++;
        }
    }
    if (tab[1] != -1) // Sprawdza czy liczba jest dwucyfrowa
    {
        return (tab[1] + 10 * tab[0]);
    }
    else
    {
        return (tab[0]);
    }

}

// WYSWIETLA CALA PLANSZA
void board_game(struct gra* Gra)
{
    clrscr();
    textbackground(BLACK);
    numbers_board();
    inside_board();
    border_board();
    bar_board();
    opcje_board();
    gracz_dane(Gra);
    rolls_show(Gra);
    draw_game(Gra);
    banda_show(Gra);

}
// WAZNE FUNKCJE
int ruch_banda(struct gra* Gra)
{
    wyczysc_input();
    gotoxy(POS_BOARD_X, ERR_Y + 1);
    cputs("Z bandy na ");
    int to = wypisz(POS_BOARD_X + 11, ERR_Y + 1);
    if (to == 0)
    {
        return 0;
    }
    if (Gra->player == one)
    {
        int from = 0;
        if (check_input(Gra, from, to) == true && check_m_banda(Gra, to) == true)
        {
            make_m_banda(Gra, to);
            return 0;
        }
        else
        {
            gotoxy(POS_OPCJE_X, ERR_Y);
            cputs("BLAD!");
            ruch_banda(Gra);
        }
    }
    else if (Gra->player == two)
    {
        int from = 25;
        if (check_input(Gra, from, to) == true && check_m_banda(Gra, to) == true)
        {
            make_m_banda(Gra, to);
            return 0;
        }
        else
        {
            gotoxy(POS_OPCJE_X, ERR_Y);
            cputs("BLAD!");
            ruch_banda(Gra);
        }
    }
}
int ruszanie(struct gra* Gra)
{
    wyczysc_input();
    gotoxy(POS_BOARD_X, ERR_Y + 1);
    if (zbicie_pionka(Gra) == true)
    {
        cputs("Musisz zbic pionka");
        getch();
        return 0;
    }
    cputs("Skad ruch: ");
    int from = wypisz(POS_BOARD_X + 11, ERR_Y + 1);
    gotoxy(POS_BOARD_X, ERR_Y + 2);
    cputs("Dokad ruch: ");
    int to = wypisz(POS_BOARD_X + 12, ERR_Y + 2);
    ;
    if (from == 0 && to == 0) // Jezeli wprowadzona wartosc 0 0 to oznacza ze ruchow nie ma
    {
        return 0;
    }
    from--;
    to--;

    if (check_move(Gra, from, to) == true && check_input(Gra, from, to) == true)
    {
        make_move(Gra, from, to);
        return 0;
    }
    else
    {
        gotoxy(POS_OPCJE_X, ERR_Y);
        cputs("BLAD!");
        ruszanie(Gra);
    }
    return 0;
}
void mozliwe_ruchy(struct gra* Gra)
{
    Gra->rzut1 = roll_throw();
    Gra->rzut2 = roll_throw();
    int dublet = 1;
    if (Gra->rzut1 == Gra->rzut2) // Sprawdzamy dublet
    {
        dublet = 2;
    }
    int pom_roll = Gra->rzut1; // ZMIENNE SA POTRZEBNE ABY ZAINICJALIZOWAC EWENTUALNY DUBLET
    int pom_roll_2 = Gra->rzut2;
    for (int j = 0; j < dublet; j++)
    {
        Gra->rzut1 = pom_roll;
        Gra->rzut2 = pom_roll_2;
        for (int i = NULL; i < ROLLS; i++)
        {
            rolls_show(Gra);
            if (check_banda(Gra) == false)
            {
                if (czy_pelny_dwor(Gra) == true)
                {
                    gotoxy(POS_BOARD_X, ERR_Y);
                    cputs("Pion do domu");
                    getch();
                    wyczysc();
                    board_game(Gra);
                }
                else
                {
                    ruszanie(Gra);
                    wyczysc();
                    board_game(Gra);
                }
            }
            else
            {
                ruch_banda(Gra);
                wyczysc();
                board_game(Gra);
            }
        }

    }

}
void wykonaj_ruchy(struct gra* Gra)
{
    mozliwe_ruchy(Gra);
    change_player(Gra);
    gracz_dane(Gra);
}

// DO ZAPISU I ODCZYTU

int zapisz_gre(struct gra* Gra)
{
    FILE* pik;

    pik = fopen("zapis_gry.txt", "w+");

    if (pik == NULL)
    {
        cputs("Nie znaleziono pliku :(");
        getch();
        return 1;
    }

    fprintf(pik, "PION W DOMU 1: %d\n", Gra->home1);
    fprintf(pik, "PION W DOMU 2: %d\n", Gra->home2);
    fprintf(pik, "BANDA 1: %d\n", Gra->banda1);
    fprintf(pik, "BANDA 2: %d\n", Gra->banda2);
    fprintf(pik, "ZACZYNA GRACZ: %d\n", Gra->player);
    for (int i = 0; i < AREA; i++)
    {
        fprintf(pik, "POLE %d PON: %d GRACZ %d\n", i + 1, Gra->plansza[i].ile_pawns, Gra->plansza[i].kolor);
    }
    cputs("Zapisano stan gry pomyslnie");
    getch();
    fclose(pik);
    return 1;
}
int wczytaj_gre(struct gra* Gra) // NIE DZIALA -> SPYTAC NATALII
{
    FILE* pik;

    pik = fopen("zapis_gry.txt", "r+");
    if (pik == NULL)
    {
        cputs("Nie znaleziono pliku :(");
        getch();
        return 1;
    }
    int pol;
    fscanf(pik, "PION W DOMU 1: %d\n", &Gra->home1);
    fscanf(pik, "PION W DOMU 2: %d\n", &Gra->home2);
    fscanf(pik, "BANDA 1: %d\n", &Gra->banda1);
    fscanf(pik, "BANDA 2: %d\n", &Gra->banda2);
    fscanf(pik, "ZACZYNA GRACZ: %d\n", &Gra->player);
    for (int i = 0; i < AREA; i++)
    {
        fscanf(pik, "POLE %d PON: %d GRACZ %d\n", &pol, &Gra->plansza[i].ile_pawns, &Gra->plansza[i].kolor);
    }
    cputs("Wczytano stan gry pomyslnie");
    getch();

    fclose(pik);
    return 1;
}

// OPCJE DO WPISANIA

int graj(struct gra* Gra)
{
    wyczysc();
    gotoxy(POS_OPCJE_X, POS_OPCJE_Y);
    _setcursortype(_NORMALCURSOR);
    char option = getch();
    switch (option)
    {
    case 'q': //wyjscie z gry
    {
        clrscr();
        koniec_gry(Gra);
        return 0;
        break;
    }
    case 'm': // Opcja ruszania pionka
    {
        if (koniec_gry(Gra) == true)
        {
            getch();
            return 0;
        }
        wykonaj_ruchy(Gra);
        break;
    }
    case 's': // Opcja zapisania stanu gry
    {
        zapisz_gre(Gra);
        break;
    }
    case 'w':
    {
        wczytaj_gre(Gra);
        break;
    }
    default:
    {
        gotoxy(POS_OPCJE_X, POS_OPCJE_Y);
        cputs("zla komenda.");
        getch();
        graj(Gra);
    }
    }
}

// MENU - WYSWIETLA

void clear_arrow_option(int pos_x, int pos_y) {
    gotoxy(pos_x, pos_y);
    printf(" ");
}
void layout_menu()
{
    _setcursortype(_NOCURSOR);
    gotoxy(MENU_X, MENU_Y);
    cputs("GRAJ");
    gotoxy(MENU_X, MENU_Y + 1);
    printf("WCZYTAJ GRE");
    gotoxy(MENU_X, MENU_Y + 2);
    printf("WYJSCIE");
}
int options_menu(int* opcja, bool* pom, struct gra* Gra)
{
    if (*opcja == 1) //ROZPOCZYNA GRE
    {
        *pom = FALSE;
        clrscr();
        inicjalizacja_wstepnych_wartosci(Gra);
        do
        {
            board_game(Gra);
        } while (graj(Gra));
        *pom = TRUE;

    }
    if (*opcja == 2) //WCZYTYWANIE GRY Z PLIKU
    {
        clrscr();
        Gra->rzut1 = roll_throw();
        Gra->rzut2 = roll_throw();
        wczytaj_gre(Gra);
        do
        {
            board_game(Gra);
        } while (graj(Gra));
    }
    if (*opcja == 3) //Konczy gre
    {
        *pom = FALSE;
        clrscr();
        cputs("DO ZOBACZENIA!");
        return 0;
    }
}
void menu_show(struct gra* Gra)
{
    clrscr();
    int opcja = 1;  // Zmienna do sledzenia wybranego elementu
    bool pom = TRUE;
    while (pom) {
        layout_menu();
        clear_arrow_option(MENU_X - 1, MENU_Y + opcja - 1);
        gotoxy(MENU_X - 1, MENU_Y + opcja - 1); // Wyswietlenie kursora obok wybranej opcji
        printf("@");

        char key = getch();
        switch (key) {// Obsluga klawiszy
        case ENTER:
            clrscr();
            options_menu(&opcja, &pom, Gra);
            break;
        case UP:
            if (opcja > 1) {
                clear_arrow_option(MENU_X - 1, MENU_Y + opcja - 1);
                opcja--;
            }
            break;
        case DOWN:
            if (opcja < 3) { //MAKS 3 OPCJE      
                clear_arrow_option(MENU_X - 1, MENU_Y + opcja - 1);
                opcja++;
            }
            break;
        }
    }
}


int main()
{
    Conio2_Init();
    settitle("Karol Banach 197912");
    _setcursortype(_NOCURSOR);
    srand(time(NULL));
    Bakgammon Gra;
    Gra.punkty1 = 0;
    Gra.punkty2 = 0;
    menu_show(&Gra);
    _setcursortype(_NORMALCURSOR);
    return 0;
}
