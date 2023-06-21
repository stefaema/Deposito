#include <iostream>
#include <cstdlib>
#include "Robot.cpp"
#include <fstream>
#include <iomanip>

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
cout<<"Procediendo a la completitud de la matriz de Adyacencia"<<endl;
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
std::cout<<"Rellenando las celdas centrales...";
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
std::cout<<"  \u2713 Listo"<<endl;std::cout<<"Rellenando las celdas verticales...";
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

std::cout<<"  \u2713 Listo"<<endl;std::cout<<"Matriz de Adyacencia completada (ver matrizCompleta.txt)"<<endl;
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
void hacerMapa()
{
//cada elemento de la matriz tendrá su propia leyenda. H sera las estanterias. V seran los casilleros disponibles
for (int i = 0; i < 361; i++)
{
    matrizMapa[i] = 'V';
}

}
void printMapa()
{
    //La caja
    cout<<"\t\t\t";
    switch(matrizMapa[360])
    {
        case 'V':
            cout<<"\u25A3"<<endl;
    }
    //El resto
    for(int i = 0; i < 360; i++)
    {
        switch (matrizMapa[i])
        {
        case 'V':
            cout<<"\u25AD ";
            break;
        
        default:
            break;
        }
        if((i+1) % 15 == 0)
            cout<<"  ";
        if((i+1) %45 == 0)
            cout<<"\n";
        
    }
}

//La caja tiene direccion (0,0,0)

int main()
{
    rellenarMatrizAdyacencia();
    hacerTxtAdy();
    Lista<Pedido*>* lista_pedidos = new Lista<Pedido*>();

    lista_pedidos->add(new Pedido(3,0));
    lista_pedidos->add(new Pedido(5,1));
    lista_pedidos->add(new Pedido(10,275));
    lista_pedidos->add(new Pedido(1,10));
    lista_pedidos->add(new Pedido(5,358));
    lista_pedidos->add(new Pedido(1,160));
    Robot* robot1 = new Robot(lista_pedidos, matrizAdyacente);

    cout<<robot1->devuelveCamino(getIndice(1,1,1),getIndice(8,3,15));
}

