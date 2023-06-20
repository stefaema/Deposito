#include <iostream>
#include <cstdlib>
#include "Direccion.hpp"
#include "Pedido.hpp"
#include <fstream>
#include <iomanip>
using namespace std;
#define Alcance  361
#define NO_MIEMBRO 0
#define MIEMBRO 1
int matrizAdyacente[Alcance][Alcance];
char matrizMapa[Alcance];
const int INFINITO = 1000000;
void verif360()
{
    for(int i = 0; i<361;i++) 
    {
        if(i!=22 && matrizAdyacente[360][i]<INFINITO){cout<<"ojo "<<i<<endl;}
    }
}
void printDireccion(int indice)
{
    if(indice != 360)
    {
    int pasillo;
    int estante;
    int celda;
    pasillo = (indice/45);
    estante = (indice / 15) - pasillo * 3;
    celda = indice - pasillo * 45 - estante * 15;
    pasillo++; celda++; estante++; 
    std::cout<<"Pasillo: "<<pasillo<<" "<<"Estante: "<<estante<<" "<<"Celda: "<<" "<<celda<<endl;
    }
    else std::cout<< "Caja (0,0,0)"<<endl;
}
void printIndice(int pasillo, int estante, int celda)
    {   
        int index = (pasillo-1) * 45 + (estante-1) * 15 + celda - 1;
        if(pasillo,estante,celda != 0) std::cout <<index<<endl;
        //la caja es direccion (0,0,0)
        else std::cout<<360;
    }
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
void printDirecciones(int p,int e,int c)
{
    cout<<"La gondola ";
    printDireccion(getIndice(p,e,c));
    cout<<" esta relacionada con: "<<endl;
    for(int i = 0;i<361;i++)
    {
        if(matrizAdyacente[getIndice(p,e,c)][i]< INFINITO && getIndice(p,e,c) != i)
        {
            printDireccion(i);
            cout<<"con un peso de: "<<matrizAdyacente[getIndice(p,e,c)][i]<<endl;
        }
    }
}
void comprobarSimetria()
{
    bool simetria = true;
    for (int i = 0; i < 361; i++)
    {
        for (int j = 0; j < 361; j++)
        {
            if(matrizAdyacente[i][j] != matrizAdyacente[j][i])
            {
                simetria = false;
                cout<<"ojo con ";
                printDireccion(j);
                cout<<"que no coincide con ";printDireccion(i);
                cout<<endl;
            }
            
            
        }
        
    }
    if(simetria)cout<<"bien ahi"<<endl;
    else cout<<"ojoalpiojo"<<endl;
}
void printSecuenciaCamino(int origen, int meta, int prev[Alcance])
{
     if (meta==origen) cout<< origen<<"  ";
   else{
        printSecuenciaCamino(origen,prev[meta],prev);
        cout<<meta<<"  ";
   }
}
int devuelveCamino(int origen, int meta)
{
    int actual, i, k, continua, menordist, nuevadist;
    int previos[Alcance];
    int costoPorIter[Alcance];
    int visitados[Alcance];
    for (int i = 0; i < Alcance; i++)
    {
        visitados[i]=NO_MIEMBRO;
        previos[i] = -1;
        costoPorIter[i]=INFINITO;
    }
    visitados[origen]= MIEMBRO; costoPorIter[origen]=0; actual = origen; continua=1; k=0;
    while((actual != meta)&&(continua == 1))
    {
        continua = 0;
        menordist = INFINITO;
        for(i=0; i < Alcance; i++)
        {
            if(visitados[i] == NO_MIEMBRO)
            {
                nuevadist = costoPorIter[actual]+matrizAdyacente[actual][i];
                if(nuevadist<costoPorIter[i])
                {
                    costoPorIter[i]=nuevadist;
                    previos[i]=actual; continua=1;
                }
                if(costoPorIter[i]<menordist)
                {
                    menordist = costoPorIter[i];
                    k=i; continua=1;
                }
            }
        }
        actual = k;
        visitados[actual] = MIEMBRO;
    }
    printSecuenciaCamino(origen,meta, previos);
    return costoPorIter[meta];
}




//La caja tiene direccion (0,0,0)

int main()
{
rellenarMatrizAdyacencia();
hacerTxtAdy();

cout<<devuelveCamino(getIndice(1,1,1),getIndice(8,3,15));

}

