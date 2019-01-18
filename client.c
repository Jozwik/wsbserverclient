#include <stdio.h> //bilbioteka nag��wkowa dla standard Input Output (wej�cie, wyj�cie)
#include <stdlib.h> //zawiera deklaracje funkcji s�u��cych do przekszta�cnia liczb, przydzielenia pami�ci 
#include <netdb.h> //biblioteka,kt�ra udost�pnia typ in_port, in_addr i hostent(opis hosta internetowego)
#include <arpa/inet.h> //biblioteka udost�pnia typ in_port i in_addr
#include <netinet/in.h> //rodzina protoko��w internetowych: in_port niedopisany ca�kowity typ dok�adnie 16 bit�w, in_addr niedopisany ca�kowity typ dok�adnie 32 bit�w
#include <string.h> //definiuje kilka funkcji do manipulowania �a�cuchami i tablicami
#include <unistd.h> //definiuje r�ne sta�e i typy symboliczne

int main (int argc, char const *argv[]) //argc-liczba argument�w, char const *agrv[]-zawiera �cie�k� wywo�ania i parametry podane wraz z jego parametrami
{
	int sockfd, n; //deskryptor gniazda po��czenia, kt�re chcemy zamkn��; zmienna n
	struct sockaddr_in serverAddr; //adres serwera
	struct hostent *server; //zwraca adres serwera
	char buffer[2048]; //dane pami�ci , bufor znak�w
	char *add = "127.0.0.1"; //dodanie do wska�nika IP
	int port = 8888; //zmienna numeru portu
	int i; //zmienna i

	puts("*****Client*****"); //zapisuje strumie� do klienta

	if (argv[1] != 0 && argv[2] != 0) //pierwszy ci�g wynosi zero, drugi ci�g te� wynosi zero
	{
		add = argv[1]; //dodajemy wska�nik do nazwy programu
		port = atoi(argv[2]); //do portu dodajemy warto�ci liczbowe do drugiego wska�nika 
	}
	printf("set: %s:%d\n",add,port); //zapis %d informuje, �e argumentem b�dzie liczba ca�kowita, natomiast %s m�wi o funkcji, �e b�dzie to �a�cuch znak�w; printf znaczy formatowanie znak�w

	sockfd = socket(AF_INET, SOCK_STREAM, 0); //funkcja socket()zwraca deskryptor gniazda; AF_INET(IPv4) obs�uguje wiele protoko��w; SOCK_STREAM-po��czenie zostaje nawi�zane, a obie strony maj� rozmow�, dop�ki po��czenie nie zostanie przerwane przez jedn� ze stron lub b��d sieci.
	serverAddr.sin_family=AF_INET; //serwer okre�la rodzin� adres�w
	serverAddr.sin_port=htons(port); //serwer podaje numer portu i pod��czenia
	serverAddr.sin_addr.s_addr=inet_addr(add); //serwer dodaje adres lokalny bez przekazywania portu

	//po��czenie z serverem
	if(connect(sockfd, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0 ) //connect pobiera desktryptor, informacje o adresie i rozmiar drugiego parametru. kt�re jest mniejsze od 0 
	{
		perror("ERROR CONNECTING"); //wygenerowanie b��du
		exit(1); //wywo�anie desktruktor�w
	}

	while(1) // p�tla while 
	{
		//send //wysy�anie
		bzero(buffer,2048); //kopiuje do �a�cucha dane 
		//scanf("%s",buffer); //wczytuje dane pami�ci; %s �ancuch znak�w
		i = 0;// int jest r�wne 0
		while((buffer[i++] = getchar()) != '\n') //dane pami�ci zwi�kszamy o 1,odczytuje znak bufora do ko�ca I ODRZUCA JE, znak nowej linii
		{

		}
		send(sockfd, buffer, strlen(buffer),0); //wysy�anie deskryptu, pami�ci danych, zliczanie bajt�w w �a�cuchu; p�tla(strlen) przechodzi przez ci�g podczas liczenia, a� osi�gnie ko�cowy bajt NULL
		if(buffer[0] == '!' && buffer[1] == 'q') //je�li dane pami�ci bufora [0] neguj� i zwrac� warto�� true, gdy buffer[1] jest r�wny q
		{
			send(sockfd, "*****client offline*****", 24,0); //wy�lij desktryptor do klienta offline i wyzeruj
			break; //przerwanie aktualnej p�tli
		}
		//read //czytaj
		bzero(buffer,2048); //skopiuj zero do ci�gu (kopiuje do �a�cucha s n bajt�w, ka�dy o warto�ci zero)
		read(sockfd, buffer, 2048); // czytaj desktryptor, dane pami�ci
		printf("%s", buffer); //Wypisuje tekst sformatowany na standardowym strumieniu wyj�cia
	}
	close(sockfd); //zamykanie desktryptora
	puts("[+]DONE!"); //zapisuje �a�cuch znak�w do standardowego strumienia wyj�cia
	return 0; //zwraca 0
}
