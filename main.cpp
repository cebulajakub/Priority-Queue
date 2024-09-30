#include <iostream>
#include <sstream>
#include "queuee.h"
#include <fstream>
#include <cstring>
#include <string>





int main()
{

Queue<std::string> kolejka_pakietowa;
std::fstream plik_wys;
std::fstream plik_odb;



wczytaj_plik();

    std::string wiadomosc, nazwa_pliku_do_wsylania, nazwa_pliku_odb_wiadomosci;
    int a;
    char c;


    std::cout << "Prosze wpisac nazwe pliku do wyslania"<<std::endl;
    std::cin>>nazwa_pliku_do_wsylania;

    plik_wys.open(nazwa_pliku_do_wsylania); //otwieranie pliku
    if(plik_wys.good()) //sprawdzenie czy plik działa poprawnie
        {
            
            if (plik_wys.is_open()) 
            {
            std::string slowo;
            while ((plik_wys>>a)) //zczytujemy liczbę
            {
            slowo=""; //zmienna string przechowująca słowa
            plik_wys.get(c); //bierzemy sapcje po priorytecie
            for(int i=0;i<10;i++)//wczytujemy w pętli 10  bajtów
            {
                plik_wys.get(c); //ponownie bierzemy jeden znak
                if(c!='\n') //sprawdzamy czy jest spacją
                slowo+=c; //jeśli nie to dodajemy do zmiennej slowo
                else
                {
                    slowo+=c; // w przciwnym wypadku też dodajemy
                    plik_wys.get(c); // i znowu sprawdzamy
                    if(c!='\n') //jeśli nie jest to sapcja 
                    plik_wys.unget(); // to umieszczamy ostatni odczytany znak w strumieniu wejściowym
                    else
                    break; //w przeciwnym wypadku wychodzimy z pętli
                }

            }
            
            kolejka_pakietowa.insert(a, slowo);
            kolejka_pakietowa.print();
            }
            }   

                plik_wys.close();      
                
                 
            }    
        
            else
            {
                std::cout<<"BLAD!!!"<<std::endl;
            }


            // pętla składania wiadomości w całość
            for (unsigned int i = 1; kolejka_pakietowa.size(); ++i)
            wiadomosc = wiadomosc + kolejka_pakietowa.removeMin();
            std::cout << "\nOdebrana wiadomosc: " <<std::endl<<wiadomosc<<'\n'<<std::endl;


            std::cout<<"Podaj nazwe pliku do którego zapisać wiadomosc"<<std::endl;
            std::cin>>nazwa_pliku_odb_wiadomosci;
            std::ofstream file(nazwa_pliku_odb_wiadomosci);
            plik_odb.open(nazwa_pliku_odb_wiadomosci);
            if(plik_odb.good())
            {
                plik_odb<<wiadomosc;
            }
            else
            {       
            std::cout<<"Nie można otworzyć pliku"<<std::endl;

            }
            plik_odb.close();


        return 0;

}