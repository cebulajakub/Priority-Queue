#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>  
#include <string>
#include <ctime>

template<class T>
class Queue
{
public:
Queue(): head(nullptr), tail(nullptr), _size(0) {};
bool isEmpty() const {return head==nullptr;}
void insert(unsigned int priorytet ,const T& element);
const T min() const;
const T removeMin();
unsigned int size() const { return _size; };
void print() const;
 

private:

struct node 
{

T element;
unsigned int priorytet;
node* prev;
node* next;
node(unsigned int p,const T& ele, node*next, node* prev):priorytet(p), element(ele), next(nullptr), prev(nullptr){}
};

node* head;
node* tail;
int _size;



};

template<class T>
void Queue<T>::insert(unsigned int priorytet,const T& element)
{

node* obiekt= new node(priorytet,element, nullptr,nullptr);
node* pomocniczy=nullptr;


if(head==nullptr) //kolejka pusta
{
    head=tail=obiekt;
    _size++;
    return;
}

pomocniczy=head;


while(pomocniczy!=nullptr&&priorytet>pomocniczy->priorytet)
{
    pomocniczy=pomocniczy->prev;
    
}
if(pomocniczy==nullptr)
{
    tail->prev=obiekt;
    obiekt->next=tail;
    obiekt->prev=nullptr;
    tail=obiekt;
}
else
{
    	obiekt->next = pomocniczy->next;
		obiekt->prev = pomocniczy;
		if (obiekt->next != nullptr)
		obiekt->next->prev = obiekt;
		obiekt->prev->next = obiekt;
		if (head == tail || priorytet <= head->priorytet)
			head = obiekt;
}

_size++;

}

template <typename T>
const T Queue<T>::min() const
{
	if (isEmpty())
		throw std::runtime_error("Nie mozna usunac elementu kolejki - kolejka jest pusta.");
	return head->element;
}


void swap(std::string* arr, int i, int j) //funkcja pomocnicza do zmiany dwóch elementów w tablicy
{ 
    std::string temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

template <typename T>
const T Queue<T>::removeMin()
{
	if (isEmpty())
	throw std::runtime_error("Nie mozna usunac elementu kolejki - kolejka jest pusta.");

	node* temp = head;		  // kopia 1 elementu kolejki
	T zapisane = head->element; // zwracany 1 element
	head = head->prev;
	if (head != nullptr)
		head->next = nullptr;

	delete temp;
	_size--;

	return zapisane;
}

template <typename T>
void Queue<T>::print() const
{
	node* pomocniczy; // pomocniczy wezel

	if (isEmpty())
		throw std::runtime_error("Nie mozna wyswietlic elementow kolejki - kolejka jest pusta.");

	// wyswietlanie elementow od najnizszego do najwyzszego priorytetu
	pomocniczy = tail;

	while (pomocniczy != nullptr)
	{
		std::cout << " -> "
			<< "[" << pomocniczy->priorytet << "]" << pomocniczy->element;
		pomocniczy = pomocniczy->next;
	}
	std::cout << "\n";
}



void wczytaj_plik()
{
    const int ROZMIAR_PACZKI = 10; // stała ilość bajtów w paczce
    std::ifstream plik;
    std::string nazwa;
    std::cout<<"Podaj nazwe pliku z wiadomoscia do wyslania:" << std::endl;
    std::cin>>nazwa;
    
    plik.open(nazwa, std::ios::binary); //plik otwieramy w trybie binarnym
    
    if (plik.good())
    {
        // obliczamy liczbę paczek
        plik.seekg(0, std::ios::end); //ustawiamy kursor na koniec pliku
        int rozmiar_pliku = plik.tellg();
        int liczba_paczek = (rozmiar_pliku + ROZMIAR_PACZKI - 1) / ROZMIAR_PACZKI;
        plik.seekg(0, std::ios::beg); //spowrotem ustawiamy na początek

        std::string* paczki = new std::string[liczba_paczek]; //tablica dynamiczna
        for (int i = 0; i < liczba_paczek-1; ++i)
        {
            char buf[ROZMIAR_PACZKI];
            plik.read(buf, ROZMIAR_PACZKI);
            paczki[i] = std::string(buf, plik.gcount());
        }
        //Ostatni pakiet może być krótszy, dlatego trzeba odczytać jego długość i utworzyć odpowiednią string
        int ostatni_rozmiar = rozmiar_pliku % ROZMIAR_PACZKI;
        char buf[ROZMIAR_PACZKI];
        plik.read(buf, ostatni_rozmiar);
        paczki[liczba_paczek-1] = std::string(buf, plik.gcount());

        //dodajemy znak nowej linii po ostatnim pakiecie
        paczki[liczba_paczek-1] += '\n';
        plik.close();

        // przypisujemy priorytet każdej paczce
        for (int i = 0; i < liczba_paczek; ++i)
        {
            paczki[i] = std::to_string(i + 1) +" " +paczki[i]+"\n";
            std::cout<<paczki[i]<<std::endl;
        }

        // losowo zamieniamy kolejność paczek
        std::srand(std::time(nullptr));
        for (int i = 0; i < liczba_paczek - 1; ++i)
        {
            int j = std::rand() % (liczba_paczek - i) + i;
            std::swap(paczki[i], paczki[j]);
        }

        std::string nazwa_wyj;
        std::cout << "Podaj nazwe pliku do zapisu pomieszanej wiadomosci:" << std::endl;
        std::cin >> nazwa_wyj;
        

        std::ofstream zapis(nazwa_wyj, std::ios::binary);
        if (zapis.good())
        {
            for (int i = 0; i < liczba_paczek; ++i)
            {
                zapis.write(paczki[i].data(), paczki[i].size());
            
            }
            zapis.close();
            delete[] paczki;
        }
        else
        {
            std::cout << "Nie mozna otworzyc pliku" << std::endl;
        }
    }
    else
    {
        std::cout << "Plik zostal wczytany nieprawidlowo" << std::endl;
    }
}












#endif