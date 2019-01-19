#include <stdio.h> //bilbioteka nagłówkowa dla standard Input Output (wejście, wyjście)
#include <stdlib.h> //zawiera deklaracje funkcji służących do przekształcnia liczb, przydzielenia pamięci
#include <string.h> //definiuje kilka funkcji do manipulowania łańcuchami i tablicami
#include <sys/types.h> //Nagłówek zawiera szereg podstawowych typów pochodnych
#include <netinet/in.h> //rodzina protokołów internetowych: in_port niedopisany całkowity typ dokładnie 16 bitów, in_addr niedopisany całkowity typ dokładnie 32 bitów
#include <arpa/inet.h> //biblioteka udostępnia typ in_port i in_addr
#include <unistd.h> //definiuje różne stałe i typy symboliczne

int main(int argc, char const *argv[]) //argc-liczba argumentów, char const *agrv[]-zawiera ścieżkę wywołania i parametry podane wraz z jego parametrami
{
	int port = 8888; // zmienna numeru portu 
	char *add = "127.0.0.1"; //dodanie do wskaźnika IP
	int i; //zmienna i
	int sockfd, client_sock; //zmienna desktryptora i socket klienta
	struct sockaddr_in addServer, client; // adres serwera,klient
	int addrlen = sizeof(addServer); //zmienna do której wysyłany jest i przyjmowany rozmiar adresu serwera
	char buffer[2048] = {0}; //bufor znaków
	int read_size; // zmienna wczytująca rozmiar
	//przypisanie arg
	if (argv[1] !=  0 && argv[2] != 0) //pierwszy ciąg wynosi zero, drugi ciąg też wynosi zero
	{
		add = argv[1]; //dodajemy wskaźnik do nazwy programu
		port = atoi (argv[2]); //do portu dodajemy wartości liczbowe do drugiego wskaźnika 
	}
	fprintf(stdout,"set: %s:%d\n",add,port); //stdout pobiera funkcje z podanego argumentu z oczekującego strumienia fprintf;zapis %d informuje, że argumentem będzie liczba całkowita, natomiast %s mówi o funkcji, że będzie to łańcuch znaków
	return 0; //zwraca 0
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) //jeśli funkcja socket()zwraca deskryptor AF_INET(IPv4) obsługuje wiele protokołów, a natomiast SOCK_STREAM nawiązuje połączenie to 0 jest równe 0
	{
		perror("socket failed"); //wygenerowane błędów socketa
		exit(EXIT_FAILURE); //kod został niespodziewanie zakończony
	}
	puts("[+] SOCKET"); //zapisuje ciąg znaków socketa

	addServer.sin_family=AF_INET; //serwer określa rodzinę adresów
	addServer.sin_addr.s_addr=inet_addr(add); //serwer dodaje adres lokalny bez przekazywania portu
	addServer.sin_port=htons(port); //serwer podaje numer portu i podłączenia

	//Bind //
	bind(sockfd,(struct sockaddr *)&addServer, sizeof(addServer)); //Funkcja bind () łączy unikalną lokalną nazwę z gniazdem deskryptora. Po wywołaniu funkcji socket () deskryptor nie ma powiązanej nazwy. Jednak należy ona do konkretnej rodziny adresów określonej podczas wywoływania metody socket() i pomaga sprawdzić ile dany typ lub obiekt zawiera bajtów
	puts("[+] BIND"); //zapisuje ciąg znaków binda

	//Listen //słuchanie
	fprintf(stdout,"Czekam na połączenie..."); //stdout pobiera funkcje z podanego argumentu z oczekującego strumienia fprintf i oczekuje na połączenie
	int c = sizeof(struct sockaddr_in); //zmienna c jest równa rozmiarowi bajtów adresu 
	listen(sockfd, 3); //

	//Accept //akceptowanie
	client_sock = accept(sockfd,(struct sockaddr*) &client, &c); //client_sock akceptuje dysktryptora i klienta, odwołanie do c
	puts("[+] CONNECT"); //zapisuje ciąg znaków łączenia
	bzero(buffer, 2048); //kopiuje do łańcucha dane 

	while(1) //pętla while
	{
		bzero(buffer,2048); //kopiuje do łańcucha dane 
		//puts("\t"); 
		recv( client_sock, buffer, 2048, 0); //recv odbiera dane z klient socketa i pobiera dane z buforu
		printf("%s", buffer); //strumień printf dla szerokości wypisuje dane pamięci 
		//send //
		bzero(buffer, 2048); //kopiuje do łańcucha dane 
		//scanf("%s", buffer); //wczytuje dane pamięci; %s łancuch znaków
		i = 0; //zmienna i
		while((buffer[i++] = getchar()) != '\n') //dane pamięci zwiększamy o 1,odczytuje znak bufora do końca I ODRZUCA JE, znak nowej linii
		{

		}
		send(client_sock, buffer, strlen(buffer),0); //wysyłanie deskryptu, pamięci danych, zliczanie bajtów w łańcuchu; pętla(strlen) przechodzi przez ciąg podczas liczenia, aż osiągnie końcowy bajt NULL
	}

	if(read_size == 0) //jeśli wczytaj rozmiar jest równe 0
	{
		puts("klient offline"); //zapisuje ciąg łączenia klienta offline
		fflush(stdout); //opróżnia bufor strumienia
	}
	else if(read_size==-1) //instrukcja lub blok instrukcji, który ma się wykonać jeśli warunek nie zostanie spełniony jest równy -1
	{
		perror("failed..."); //wygenerowanie błędu
	}
	close(client_sock); //zamyka socket klienta
	close(sockfd); //zamyka dysktryptor
	return 0; //zwraca 0
}
