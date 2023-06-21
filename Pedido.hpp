
#include <iostream>
#include "Direccion.hpp"
using namespace std;
#ifndef Pedido_HPP
#define Pedido_HPP
class Pedido
{
    public:
    int mercaderia;
    int lugar;
    Pedido(int mercaderia, int index)
    {
        this->mercaderia = mercaderia;
        lugar = index;
    }
    int getMercaderia(){return mercaderia;}

};
#endif