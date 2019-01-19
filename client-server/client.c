#include <stdio.h> //bilbioteka nag³ówkowa dla standard Input Output (wejœcie, wyjœcie)
#include <stdlib.h> //zawiera deklaracje funkcji s³u¿¹cych do przekszta³cnia liczb, przydzielenia pamiêci 
#include <netdb.h> //biblioteka,która udostêpnia typ in_port, in_addr i hostent(opis hosta internetowego)
#include <arpa/inet.h> //biblioteka udostêpnia typ in_port i in_addr
#include <netinet/in.h> //rodzina protoko³ów internetowych: in_port niedopisany ca³kowity typ dok³adnie 16 bitów, in_addr niedopisany ca³kowity typ dok³adnie 32 bitów
#include <string.h> //definiuje kilka funkcji do manipulowania ³añcuchami i tablicami
#include <unistd.h> //definiuje ró¿ne sta³e i typy symboliczne

int main (int argc, char const *argv[]) //argc-liczba argumentów, char const *agrv[]-zawiera œcie¿kê wywo³ania i parametry podane wraz z jego parametrami
{
	int sockfd, n; //deskryptor gniazda po³¹czenia, które chcemy zamkn¹æ; zmienna n
	struct sockaddr_in serverAddr; //adres serwera
	struct hostent *server; //zwraca adres serwera
	char buffer[2048]; //dane pamiêci , bufor znaków
	char *add = "127.0.0.1"; //dodanie do wskaŸnika IP
	int port = 8888; //zmienna numeru portu
	int i; //zmienna i

	puts("*****Client*****"); //zapisuje strumieñ do klienta

	if (argv[1] != 0 && argv[2] != 0) //pierwszy ci¹g wynosi zero, drugi ci¹g te¿ wynosi zero
	{
		add = argv[1]; //dodajemy wskaŸnik do nazwy programu
		port = atoi(argv[2]); //do portu dodajemy wartoœci liczbowe do drugiego wskaŸnika 
	}
	printf("set: %s:%d\n",add,port); //zapis %d informuje, ¿e argumentem bêdzie liczba ca³kowita, natomiast %s mówi o funkcji, ¿e bêdzie to ³añcuch znaków; printf znaczy formatowanie znaków

	sockfd = socket(AF_INET, SOCK_STREAM, 0); //funkcja socket()zwraca deskryptor gniazda; AF_INET(IPv4) obs³uguje wiele protoko³ów; SOCK_STREAM-po³¹czenie zostaje nawi¹zane, a obie strony maj¹ rozmowê, dopóki po³¹czenie nie zostanie przerwane przez jedn¹ ze stron lub b³¹d sieci.
	serverAddr.sin_family=AF_INET; //serwer okreœla rodzinê adresów
	serverAddr.sin_port=htons(port); //serwer podaje numer portu i pod³¹czenia
	serverAddr.sin_addr.s_addr=inet_addr(add); //serwer dodaje adres lokalny bez przekazywania portu

	//po³¹czenie z serverem
	if(connect(sockfd, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0 ) //connect pobiera desktryptor, informacje o adresie i rozmiar drugiego parametru. które jest mniejsze od 0 
	{
		perror("ERROR CONNECTING"); //wygenerowanie b³êdu
		exit(1); //wywo³anie desktruktorów
	}

	while(1) // pêtla while 
	{
		//send //wysy³anie
		bzero(buffer,2048); //kopiuje do ³añcucha dane 
		//scanf("%s",buffer); //wczytuje dane pamiêci; %s ³ancuch znaków
		i = 0;// int jest równe 0
		while((buffer[i++] = getchar()) != '\n') //dane pamiêci zwiêkszamy o 1,odczytuje znak bufora do koñca I ODRZUCA JE, znak nowej linii
		{

		}
		send(sockfd, buffer, strlen(buffer),0); //wysy³anie deskryptu, pamiêci danych, zliczanie bajtów w ³añcuchu; pêtla(strlen) przechodzi przez ci¹g podczas liczenia, a¿ osi¹gnie koñcowy bajt NULL
		if(buffer[0] == '!' && buffer[1] == 'q') //jeœli dane pamiêci bufora [0] neguj¹ i zwrac¹ wartoœæ true, gdy buffer[1] jest równy q
		{
			send(sockfd, "*****client offline*****", 24,0); //wyœlij desktryptor do klienta offline i wyzeruj
			break; //przerwanie aktualnej pêtli
		}
		//read //czytaj
		bzero(buffer,2048); //skopiuj zero do ci¹gu (kopiuje do ³añcucha s n bajtów, ka¿dy o wartoœci zero)
		read(sockfd, buffer, 2048); // czytaj desktryptor, dane pamiêci
		printf("%s", buffer); //Wypisuje tekst sformatowany na standardowym strumieniu wyjœcia
	}
	close(sockfd); //zamykanie desktryptora
	puts("[+]DONE!"); //zapisuje ³añcuch znaków do standardowego strumienia wyjœcia
	return 0; //zwraca 0
}
