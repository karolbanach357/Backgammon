🎯 Cel projektu

Celem projektu było stworzenie w pełni działającej gry Backgammon (Tryktrak) w środowisku terminalowym, z wykorzystaniem biblioteki conio2 do obsługi kolorów, kursora i interfejsu tekstowego.
Program został napisany w jednym pliku, bez użycia klas ani programowania obiektowego — w stylu czysto proceduralnym.

🧩 Opis gry

Gra pozwala na rozgrywkę dwóch graczy lokalnie w konsoli.
Zaimplementowano:

rysowanie planszy ASCII w terminalu,  
pełną mechanikę ruchów pionków (w tym bicie, powrót z bandy, wprowadzenie do domu),  
losowanie kostek i obsługę dubletów,  
zapis i wczytywanie stanu gry z pliku (zapis_gry.txt),  
system punktów i detekcję końca gry,  
menu nawigowane strzałkami (GRAJ / WCZYTAJ / WYJŚCIE).

⚙️ Uruchomienie

Skopiuj plik źródłowy (backgammon.cpp) i upewnij się, że masz zainstalowaną bibliotekę conio2.h (np. w folderze include MinGW).

Skompiluj:  
`g++ backgammon.cpp -o backgammon -lconio2`  
Uruchom grę:  
`backgammon.exe`

Sterowanie:  
Strzałki ↑ / ↓ — poruszanie po menu,  
Enter — wybór opcji,  
m — wykonaj ruch,  
q — zakończ grę,  
s / w — zapisz / wczytaj grę.

💡 Informacje techniczne

Język: C++ (C-style proceduralny)  
Biblioteka: conio2  
Wykorzystane mechanizmy: gotoxy(), textcolor(), putch(), cputs(), getch(), clrscr()
