__asm__(".code16gcc\n");
__asm__("jmp $0x0000, $main\n");


#include "../../Kernel/utils/iodisp.h"


#define CARRIAGE_RETURN_ASCII 0x0D

void main() 
{
	char odpowiedz;
	
	poczatek:

		putchar(CARRIAGE_RETURN_ASCII);
		print_string("1. Ocena z tego projektu to: \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("A. 2 \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("B. 3 \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("C. 4 \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("D. 5 \n");
		putchar(CARRIAGE_RETURN_ASCII);
		odpowiedz = getchar();
		
		if (odpowiedz != 'D') {print_string("Niestety! Przegrales :( Prawidlowa odpowiedz to D \n"); goto poczatek;}
		else if (odpowiedz == 'D') print_string ("Wygrales 100zl, oto nastepne pytanie. \n");

		putchar(CARRIAGE_RETURN_ASCII);
		print_string("2. Ile miesiecy liczy kwartal? \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("A. 2 \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("B. 3 \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("C. 4 \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("D. 5 \n");
		putchar(CARRIAGE_RETURN_ASCII);
		odpowiedz = getchar();

		if (odpowiedz != 'B') { print_string("Niestety! Przegrales :( Prawidlowa odpowiedz to B \n"); goto poczatek; }
		else if (odpowiedz == 'B') print_string("Wygrales 200zl, oto nastepne pytanie. \n");

		putchar(CARRIAGE_RETURN_ASCII);
		print_string("3. 11 listopada to rocznica: \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("A. Odzyskania niepodleglosci \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("B. Wybuchu I wojny swiatowej \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("C. Uchwalenia konstytucji \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("D. Powstania listopadowego \n");
		putchar(CARRIAGE_RETURN_ASCII);
		odpowiedz = getchar();

		if (odpowiedz != 'A') { print_string("Niestety! Przegrales :( Prawidlowa odpowiedz to A \n"); goto poczatek; }
		else if (odpowiedz == 'A') print_string("Wygrales 300zl, oto nastepne pytanie. \n");

		putchar(CARRIAGE_RETURN_ASCII);
		print_string("4. Woda to tlenek:\n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("A. Wegla \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("B. Srebra \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("C. Zelaza \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("D. Wodoru \n");
		putchar(CARRIAGE_RETURN_ASCII);
		odpowiedz = getchar();

		if (odpowiedz != 'D') { print_string("Niestety! Przegrales :( Prawidlowa odpowiedz to D\n"); goto poczatek; }
		else if (odpowiedz == 'D') print_string("Wygrales 500zl, oto nastepne pytanie.\n");

		putchar(CARRIAGE_RETURN_ASCII);
		print_string("5. Miedzynarodowa organizacja policyjna scigajaca przestepstwa kryminalne to: \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("A. Mosad \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("B. Czeka \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("C. Interpol \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("D. Secret Service \n");
		putchar(CARRIAGE_RETURN_ASCII);
		odpowiedz = getchar();

		if (odpowiedz != 'C') { print_string("Niestety! Przegrales :( Prawidlowa odpowiedz to C\n"); goto poczatek; }
		else if (odpowiedz == 'C') print_string("Wygrales 1000zl, oto nastepne pytanie.\n");

		putchar(CARRIAGE_RETURN_ASCII);
		print_string("6. Ktore z okreslen nie oznacza wyslannika? \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("A. Emisariusz \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("B. Kurier \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("C. Posel \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("D. Ordynat \n");
		putchar(CARRIAGE_RETURN_ASCII);
		odpowiedz = getchar();

		if (odpowiedz != 'D') { print_string("Niestety! Przegrales :( Prawidlowa odpowiedz to D\n"); goto poczatek; }
		else if (odpowiedz == 'D') print_string("Wygrales 2000zl, oto nastepne pytanie.\n");

		putchar(CARRIAGE_RETURN_ASCII);
		print_string("7. Jakie wloskie miasto bylo tlem burzliwego i tragicznego w skutkach romansu Romea i Julii? \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("A. Werona \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("B. Wenecja \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("C. Florencja \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("D. Palermo \n");
		putchar(CARRIAGE_RETURN_ASCII);
		odpowiedz = getchar();

		if (odpowiedz != 'A') { print_string("Niestety! Przegrales :( Prawidlowa odpowiedz to A\n"); goto poczatek; }
		else if (odpowiedz == 'A') print_string("Wygrales 4000zl, oto nastepne pytanie.\n");

		putchar(CARRIAGE_RETURN_ASCII);
		print_string("8. Kto wypowiedzial slynne slowa: 'to maly krok dla czlowieka, ale wielki skok dla ludzkosci'? \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("A. Kosmonauta na ksiezycu \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("B. Laureat Nagrody Nobla \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("C. Genetyk, ktory sklonowal owce \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("D. Konstruktor pierwszego komputera \n");
		putchar(CARRIAGE_RETURN_ASCII);
		odpowiedz = getchar();

		if (odpowiedz != 'A') { print_string("Niestety! Przegrales :( Prawidlowa odpowiedz to A\n"); goto poczatek; }
		else if (odpowiedz == 'A') print_string("Wygrales 8000zl, oto nastepne pytanie.\n");

		putchar(CARRIAGE_RETURN_ASCII);
		print_string("9. Kto wypowiedzial slowa: 'Ja nie z soli ani z roli, ale z tego, co mnie boli'? \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("A. Jan III Sobieski \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("B. Bartosz Glowacki \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("C. Stefan Czarniecki \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("D. Jozef Pilsudski \n");
		putchar(CARRIAGE_RETURN_ASCII);
		odpowiedz = getchar();

		if (odpowiedz != 'C') { print_string("Niestety! Przegrales :( Prawidlowa odpowiedz to C\n"); goto poczatek; }
		else if (odpowiedz == 'C') print_string("Wygrales 16000zl, oto nastepne pytanie.\n");

		putchar(CARRIAGE_RETURN_ASCII);
		print_string("10. Wafel pieczony z delikatnego ciasta w specjalnych foremkach to: \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("A. Bajgiel \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("B. Andrut \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("C. Baklawa \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("D. Beza \n");
		putchar(CARRIAGE_RETURN_ASCII);
		odpowiedz = getchar();

		if (odpowiedz != 'B') { print_string("Niestety! Przegrales :( Prawidlowa odpowiedz to B\n"); goto poczatek; }
		else if (odpowiedz == 'B') print_string("Wygrales 32000zl, oto nastepne pytanie.\n");

		putchar(CARRIAGE_RETURN_ASCII);
		print_string("11. Wysoka czapka futrzana noszona w Wielkiej Brytanii przez reprezentacyjne oddzialy gwardii to: \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("A. Kolpak \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("B. Tiara \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("C. Papacha \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("D. Bermyca \n");
		putchar(CARRIAGE_RETURN_ASCII);
		odpowiedz = getchar();

		if (odpowiedz != 'D') { print_string("Niestety! Przegrales :( Prawidlowa odpowiedz to D\n"); goto poczatek; }
		else if (odpowiedz == 'D') print_string("Wygrales 64000zl, oto nastepne pytanie.\n");

		putchar(CARRIAGE_RETURN_ASCII);
		print_string("12.  Gdzie produkowany jest od 1835 roku wloski wermut Cinzano (rodzaj wina)? \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("A. W Turynie \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("B. W Wenecji \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("C. W Mediolanie \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("D. We Florencji \n");
		putchar(CARRIAGE_RETURN_ASCII);
		odpowiedz = getchar();

		if (odpowiedz != 'A') { print_string("Niestety! Przegrales :( Prawidlowa odpowiedz to A\n"); goto poczatek; }
		else if (odpowiedz == 'A') print_string("Wygrales 125000zl, oto nastepne pytanie.\n");


		putchar(CARRIAGE_RETURN_ASCII);
		print_string("13. Ktory z podanych instrumentow nie nalezy do grupy aerofonow? \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("A. Oboj \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("B. Tuba \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("C. Dudy \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("D. Zele \n");
		putchar(CARRIAGE_RETURN_ASCII);
		odpowiedz = getchar();

		if (odpowiedz != 'D') { print_string("Niestety! Przegrales :( Prawidlowa odpowiedz to D\n"); goto poczatek; }
		else if (odpowiedz == 'D') print_string("Wygrales 250000zl, oto nastepne pytanie.\n");

		putchar(CARRIAGE_RETURN_ASCII);
		print_string("14. Jak nazywa siê amerykanska baza wojskowa na Kubie? \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("A. Santa Clara \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("B. Bayamo \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("C. Guantanamo \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("D. Matanzas \n");
		putchar(CARRIAGE_RETURN_ASCII);
		odpowiedz = getchar();

		if (odpowiedz != 'C') { print_string("Niestety! Przegrales :( Prawidlowa odpowiedz to C\n"); goto poczatek; }
		else if (odpowiedz == 'C') print_string("Wygrales 500000zl, oto nastepne pytanie.\n");

		putchar(CARRIAGE_RETURN_ASCII);
		print_string("15.  Z jakimi plemionami Indian walczyl general Custer nad Little Big Horn ? \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("A. Czirokezami i Seminolami \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("B. Sjuksami i Szejenami \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("C. Szoszonami i Wronami \n");
		putchar(CARRIAGE_RETURN_ASCII);
		print_string("D. Huronami i Mohikanami \n");
		putchar(CARRIAGE_RETURN_ASCII);
		odpowiedz = getchar();

		if (odpowiedz != 'B') { print_string("Niestety! Przegrales :( Prawidlowa odpowiedz to B\n"); goto poczatek; }
		else if (odpowiedz == 'B') print_string("Wygrales MILION ZL, oto nastepne pytanie.\n");


}






