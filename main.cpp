#include <iostream>
#include <cstdlib>
#include "Robot.cpp"
#include <fstream>
#include <iomanip>
#include <windows.h>
using namespace std;

#define Alcance  361
#define NO_MIEMBRO 0
#define MIEMBRO 1

int matrizAdyacente[Alcance][Alcance];
char matrizMapa[Alcance];

int getIndice(int p, int e, int c)
{
    if(p!= 0 && e != 0 && c != 0 )
        return (p-1) * 45 + (e-1) * 15 + c - 1;
    else
        return 360;
}
void rellenarMatrizAdyacencia()
{
//Por defecto todo es infinito
cout<<"Analizando la disposicion estructural del deposito (matriz de Adyacencia)"<<endl;
for(int i = 0; i<361; i++)
{
     for(int j = 0; j<361; j++)
    {
        matrizAdyacente[i][j] = INFINITO;
        if(i==j)
        matrizAdyacente[i][i]= 0;
    }
}
//Primero las celdas del medio
std::cout<<"Rellenando las celdas centrales";
    for(int pasilloAux = 1; pasilloAux <= 8; pasilloAux++)
    {
        for(int estanteAux = 1; estanteAux <= 3; estanteAux++)
        {
            for(int gondolaAux = 2; gondolaAux <= 14;gondolaAux++)
            {   
                int i = getIndice(pasilloAux,estanteAux,gondolaAux);
                matrizAdyacente[i][i+1] = 1;
                matrizAdyacente[i][i-1] = 1;
                
            }
        }
    }
Sleep(500);cout<<dye::green(".");Sleep(500);cout<<dye::green(".");Sleep(500);cout<<dye::green(". ");
std::cout<<dye::green("  \u2713 Listo")<<endl;
std::cout<<"Rellenando las celdas verticales";
//Luego las celdas verticales
for (int i = 1; i <= 8; i++)
{
    for (int j = 1; j <= 8; j++)
    {
     for (int k = 1; k<=3; k++)   
        {   
            if(i!=j)
            {
            matrizAdyacente[getIndice(i,k,1)][getIndice(j,k,1)]= 2*abs(j-i) + 2;
            matrizAdyacente[getIndice(i,k,1)][getIndice(i,k,2)]=1;
            matrizAdyacente[getIndice(i,k,15)][getIndice(i,k,14)]= 1;
            if(k!=3)matrizAdyacente[getIndice(i,k,15)][getIndice(i,k+1,1)] = 3;
            if(k!=1)matrizAdyacente[getIndice(i,k,1)][getIndice(i,k-1,15)] = 3;
            matrizAdyacente[getIndice(i,k,15)][getIndice(j,k,15)]= 2 * abs(j-i) + 2;
            }
        }
    }
    
}
//por ultimo la caja
matrizAdyacente[360][22]=1;matrizAdyacente[22][360]=1;
Sleep(500);cout<<dye::green(".");Sleep(500);cout<<dye::green(".");Sleep(500);cout<<dye::green(". ");std::cout<<dye::green("  \u2713 Listo")<<endl;

std::cout<<"Matriz de Adyacencia completada (ver matrizCompleta.txt)\n\n";
}
void hacerTxtAdy()
{   
    ofstream matrizCompleta("matrizCompleta.txt");
    matrizCompleta<<"i j ";
    for(int k = 0; k<361; k++){matrizCompleta<<setfill('0')<<setw(3)<<k<<" ";}
    matrizCompleta<<endl;
    for(int i = 0; i<361;i++)
    {   
        matrizCompleta <<setfill('0')<<setw(3)<<i<<" ";
        for(int j = 0; j<361; j++)
        {
        if(matrizAdyacente[i][j]<INFINITO)
        {
            if(matrizAdyacente[i][j]>9) matrizCompleta <<" "<< matrizAdyacente[i][j] <<" ";
            else matrizCompleta <<" "<< matrizAdyacente[i][j] <<"  ";
        }
        else
         matrizCompleta << "   " <<" ";  
        }// \u221E = inf
        matrizCompleta<<"\n";
    }
}
Lista<Pedido*>* lista21_6()
{   
    Lista<Pedido*>* lista1 = new Lista<Pedido*>();
    lista1->add(new Pedido(8,275));
    lista1->add(new Pedido(5,358));
    lista1->add(new Pedido(1,10));
    lista1->add(new Pedido(6,150));
    lista1->add(new Pedido(5,328));
    lista1->add(new Pedido(10,20));
    lista1->add(new Pedido(5,162));
    lista1->add(new Pedido(2,216));
    lista1->add(new Pedido(5,148));
    lista1->add(new Pedido(10,20));
    lista1->add(new Pedido(5,1));
    lista1->add(new Pedido(2,87));
    return lista1;
}
Lista<Pedido*>* lista20_6()
{
    Lista<Pedido*>* lista2 = new Lista<Pedido*>();
    lista2->add(new Pedido(2,100));
    lista2->add(new Pedido(1,200));
    lista2->add(new Pedido(5,300));
    lista2->add(new Pedido(3,150));
    lista2->add(new Pedido(3,50));
    lista2->add(new Pedido(8,89));
    lista2->add(new Pedido(7,1));
    lista2->add(new Pedido(2,22));
    lista2->add(new Pedido(1,178));
    lista2->add(new Pedido(5,287));
    lista2->add(new Pedido(1,43));
    lista2->add(new Pedido(9,51));
    return lista2;
}
Lista<Pedido*>* lista22_6()
{
    Lista<Pedido*>* lista3 = new Lista<Pedido*>();
    bool on = true;
    cout<<"\nPanel de confeccion de orden de pedidos"<<endl;
    while(on)
    {
        int cant;
        int p,e,g;
        int indice;
        cout<<"Ingrese cantidad de mercaderia a extraer\n"<<endl;
        cin>>cant;
        if(cant>10 || cant<1){cant=1; cout<<"Dato incorrecto, se asume 1"<<endl;}
        cout<<"Ingrese posicion: Pasillo, Estante, Gondola\n"<<endl;
        cin>>p; 
        if(p>8 || p<1){p=1; cout<<"Dato incorrecto, se asume 1"<<endl;}
        cin>>e;
        if(e>3 || e<1){e=1; cout<<"Dato incorrecto, se asume 1"<<endl;}
        cin>>g;
        if(g>15 || g<1){g=1; cout<<"Dato incorrecto, se asume 1"<<endl;}
        indice = getIndice(p,e,g);
        lista3->add(new Pedido(cant,indice));
        cout<<"Quiere continuar agregando pedidos?[Y]/[N]\n\n";
        char response;cin>>response;
        if(response=='N' || response =='n')
        {
            on = false;
        }
        if(response!='Y' && response !='y' && response!='N' && response != 'n')
        {
            cout<<"Eran dos opciones. Se asume que si se sigue"<<endl;
        }
    }
    return lista3;
}
//La caja tiene direccion (0,0,0)

int main()
{   
    cout<<"Panel de control de Vi100-3 \U0001F916"<<"\n\n";
    Lista<Pedido*>* lista_pedidos;
    rellenarMatrizAdyacencia();
    hacerTxtAdy();
    cout<<dye::purple("Historial de recorridos")<<endl;
    cout<<"A\u2022 20/6/2023"<<endl;
    cout<<"B\u2022 21/6/2023"<<endl;
    cout<<"C\u2022 22/6/2023 (Orden en proceso)"<<endl;
    cout<<"\nSeleccione fecha para acceder al recorrido\n";
    char a;
    cin>>a;
    cout<<"\n\n";
    switch (toupper(a))
    {
    case 'A':
        lista_pedidos = lista20_6();
        break;
    case 'B':
        lista_pedidos=lista21_6();
        break;
    case 'C':
        lista_pedidos=lista22_6();
        break;
    default:
        break;
    }

    Robot* robot1 = new Robot(lista_pedidos, matrizAdyacente);
    robot1->hacerMapa();
    robot1->realizarPedidos();
    robot1->printMapa();
}

