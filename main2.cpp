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


    //no tan comunes
    for(int pasilloAux = 2; pasilloAux <= 7; pasilloAux++)
    {

                int i = devuelveIndice(pasilloAux,1,1);
                int j = devuelveIndice(pasilloAux,3,15);
                int k = devuelveIndice(pasilloAux,1,15);
                int l = devuelveIndice(pasilloAux,2,1);

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
    //las esquinas
    matrizAdyacente[0][1]=1; matrizAdyacente[0][0+45]=4;
    matrizAdyacente[44][43] = 1; matrizAdyacente[44][89]= 4;
    matrizAdyacente[314][315]= 1; matrizAdyacente[314][269]=4;
    matrizAdyacente[359][358] = 1; matrizAdyacente[359][314]=1;


        hacerTxt();
}
void hacerTxt()
{   
    ofstream matrizCompleta("matrizCompleta.txt");
    for(int i = 0; i<361;i++)
    {   
        matrizCompleta <<i<<" ";
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
