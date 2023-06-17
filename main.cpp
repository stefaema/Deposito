#include <iostream>
#include <fstream>
using namespace std;
int matrizAdyacente[361][361];
const int INFINITO = 1000000;
int devuelveIndice(int, int, int);
void rellenarInfinitos();
void rellenarComunes();
void printBasico();
void hacerTxt();
int main()
{   
    
    rellenarInfinitos();
    rellenarComunes();
    matrizAdyacente[devuelveIndice(1,2,8)][360] = 4;
    matrizAdyacente[360][devuelveIndice(1,2,8)] = 4;
    cout<<"terminó"<<endl;
    printBasico();
    hacerTxt();
}
void hacerTxt()
{   
    ofstream matrizCompleta("matrizCompleta.txt");
    for(int i = 0; i<361;i++)
    {
        for(int j = 0; j<361; j++)
        {
        if(matrizAdyacente[i][j]<INFINITO)
         matrizCompleta << matrizAdyacente[i][j] <<" ";
        else
         matrizCompleta << "\u221E" <<" ";  
        }
        matrizCompleta<<"\n";
    }
}
void rellenarComunes()
{
    for(int pasilloAux = 1; pasilloAux <= 8; pasilloAux++)
    {
        for(int estanteAux = 1; estanteAux < 4; estanteAux++)
        {
            for(int gondolaAux = 2; gondolaAux < 15;gondolaAux++)
            {   
                int i = devuelveIndice(pasilloAux,estanteAux,gondolaAux);
                matrizAdyacente[i][i+1] = 1;
                matrizAdyacente[i][i-1] = 1;
                
            }
        }
    }
}
void printBasico()
{
for(int i = 0; i<15; i++)
{
    for(int j = 0; j<15;j++)
    {   
        if(matrizAdyacente[i][j]<INFINITO)
        cout << matrizAdyacente[i][j] << " ";
        else
        cout<<"\u221E"<<" "; 
    }
    cout<<endl;
}
}

int devuelveIndice(int pasillo,int estante,int gondola)
{
    int indice = 0 + (gondola - 1) + (estante - 1) * 15 + (pasillo - 1)* 45;
    //cout<< indice <<endl;
    return indice;

}
void rellenarInfinitos()
{
    for(int i = 0; i<361; i++)
    {
        for(int j = 0; j<361; j++)
        {
            matrizAdyacente[i][j] = INFINITO;
            if(i==j)
            matrizAdyacente[i][i]= 0;
        }
    }
}
