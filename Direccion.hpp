
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
    }
    int getIndice()
    {
        return (pasillo-1) * 45 + (estante-1) * 15 + celda - 1;
    }

};
#endif