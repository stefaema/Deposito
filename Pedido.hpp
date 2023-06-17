
#include <iostream>
#include "Direccion.hpp"
using namespace std;
#ifndef Pedido_HPP
#define Pedido_HPP
class Pedido
{
    public:
    int mercaderia;
    Direccion* lugar;
    Pedido(int mercaderia, Direccion* lugar)
    {
        this->mercaderia = mercaderia;
        this->lugar = lugar;
    }
};
#endif