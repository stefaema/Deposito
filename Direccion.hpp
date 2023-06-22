
#include <iostream>
using namespace std;
#ifndef Direccion_HPP
#define Direccion_HPP
class Direccion
{
    public:
    int pasillo;
    int estante;
    int celda;
    Direccion()
    {
        pasillo = 1;
        estante = 1;
        celda = 1;
    }
    Direccion(int p, int e, int c)
    {
        pasillo = p;
        estante = e;
        celda = c;
        verificarDireccion();
    }
    int getIndice()
    {
        return (pasillo-1) * 45 + (estante-1) * 15 + celda - 1;
        //la caja es direccion (0,0,0)
        if(pasillo==0 && estante==0 && celda == 0)
        {
            return 360;
        }
    }
    void verificarDireccion()
    {
        if((celda > 15 || estante > 3 || pasillo > 8))
        {
        cout<<"Precaucion: Direccion no permitida. Se configura como la primer celda."<<endl;
        pasillo = 1;
        estante = 1;
        celda = 1;
        }
    }

};
#endif