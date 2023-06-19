#include <iostream>
#include "Direccion.hpp"
#include "Pedido.hpp"
#include <fstream>
#include <iomanip>
using namespace std;
int matrizAdyacente[361][361];
const int INFINITO = 1000000;
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
    std::cout<<"Pasillo: "<<pasillo<<endl<<"Estante: "<<estante<<endl<<"Celda: "<<celda<<endl;
    }
    else std::cout<< "Caja"<<endl;
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
    if(p,e,c!=0)
        return (p-1) * 45 + (e-1) * 15 + c - 1;
    else
        return 360;
}
void rellenarMatrizAdyacencia()
{
//Por defecto todo es indinito
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
std::cout<<"Rellendndo las celdas centrales...";
    for(int pasilloAux = 1; pasilloAux <= 8; pasilloAux++)
    {
        for(int estanteAux = 1; estanteAux < 4; estanteAux++)
        {
            for(int gondolaAux = 2; gondolaAux < 15;gondolaAux++)
            {   
                int i = getIndice(pasilloAux,estanteAux,gondolaAux);
                matrizAdyacente[i][i+1] = 1;
                matrizAdyacente[i][i-1] = 1;
                
            }
        }
    }
std::cout<<" \u2713 Listo"<<endl;std::cout<<"Rellendndo las celdas veritcales...";
//Luego las celdas verticales
    for(int pasilloAux = 2; pasilloAux <= 7; pasilloAux++)
    {

                int i = getIndice(pasilloAux,1,1);
                int j = getIndice(pasilloAux,3,15);
                int k = getIndice(pasilloAux,1,15);
                int l = getIndice(pasilloAux,2,1);

                matrizAdyacente[i][i+45] = 4;
                matrizAdyacente[i][i+1] = 1;
                matrizAdyacente[i][-45] = 4;

                matrizAdyacente[j][j+45] = 4;
                matrizAdyacente[j][j-1] = 1;
                matrizAdyacente[j][j-45] = 4;

                matrizAdyacente[k][k+1]= 4; matrizAdyacente[k+15][k+1]= 4;
                matrizAdyacente[k][k+45] = 4; matrizAdyacente[k+15][k+45]= 4;
                matrizAdyacente[k][k-45] = 4; matrizAdyacente[k+15][k-45] = 4;
                matrizAdyacente[k][k-1]= 1; matrizAdyacente[k+15][k-1] = 1;

                matrizAdyacente[l][l+1]= 1; matrizAdyacente[l+15][l+1]= 1;
                matrizAdyacente[l][l-1]= 4; matrizAdyacente[l+15][l-1]= 4;
                matrizAdyacente[l][l+45] = 4; matrizAdyacente[l+15][l+45] = 4;
                matrizAdyacente[l][l-45] = 4; matrizAdyacente[l+15][l-45] = 4;
    }
std::cout<<" \u2713 Listo"<<endl;std::cout<<"Rellendndo las esquinas externas...";
//Luego las esquinas externas
    matrizAdyacente[0][1]=1; matrizAdyacente[0][45] = 4;              //Esq. Sup.Izq.
    matrizAdyacente[44][43] = 1; matrizAdyacente[44][89] = 4;         //Esq. Sup. Der.
    matrizAdyacente[315][316]= 1; matrizAdyacente[315][270] = 4;      //Esq. Inf. Izq.
    matrizAdyacente[359][358] = 1; matrizAdyacente[359][314] = 1;     //Esq. Inf. Der.
std::cout<<" \u2713 Listo"<<endl;std::cout<<"Rellendndo las esquinas internas...";
//Por ultimo las esquinas internas y caja
    matrizAdyacente[14][15]=4; matrizAdyacente[14][59] = 4; matrizAdyacente[14][13] = 1;
    matrizAdyacente[15][14]=4; matrizAdyacente[15][60] = 4; matrizAdyacente[15][16] = 1;
    matrizAdyacente[29][30]=4; matrizAdyacente[29][74] = 4; matrizAdyacente[29][28] = 1;
    matrizAdyacente[30][29]=4; matrizAdyacente[30][75] = 4; matrizAdyacente[30][31] = 1;
    matrizAdyacente[329][330]=4; matrizAdyacente[329][284] = 4; matrizAdyacente[329][328] = 1;
    matrizAdyacente[330][329]=4; matrizAdyacente[330][285] = 4; matrizAdyacente[330][331] = 1;
    matrizAdyacente[344][345]=4; matrizAdyacente[344][299] = 4; matrizAdyacente[344][343] = 1;
    matrizAdyacente[345][344]=4; matrizAdyacente[345][300] = 4; matrizAdyacente[345][346] = 1;
    matrizAdyacente[22][360]=4; matrizAdyacente[360][22]=4;
std::cout<<" \u2713 Listo"<<endl;    
std::cout<<"Matriz de Adyacencia completada"<<endl;
}
void hacerTxt()
{   
    ofstream matrizCompleta("matrizCompleta.txt");
    matrizCompleta<<"  j ";
    for(int k = 0; k<361; k++){matrizCompleta<<setfill('0')<<setw(3)<<k<<" ";}
    matrizCompleta<<"\ni  "<<endl;
    for(int i = 0; i<361;i++)
    {   
        matrizCompleta <<setfill('0')<<setw(3)<<i<<" ";
        for(int j = 0; j<361; j++)
        {
        if(matrizAdyacente[i][j]<INFINITO)
         matrizCompleta <<" "<< matrizAdyacente[i][j] <<"  ";
        else
         matrizCompleta << " \u221E " <<" ";  
        }
        matrizCompleta<<"\n";
    }
}
//La caja tiene direccion (0,0,0)

int main()
{
rellenarMatrizAdyacencia();
hacerTxt();

}

