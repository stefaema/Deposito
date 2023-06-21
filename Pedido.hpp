
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
    Pedido(){};
    Pedido(int mercaderia, int index)
    {
        this->mercaderia = mercaderia;
        lugar = index;
    }
    int getMercaderia(){return mercaderia;}
    bool operator==(const Pedido& otro) const {
        // Comparar los atributos relevantes para determinar si los pedidos son iguales
        return lugar == otro.lugar && mercaderia == otro.mercaderia;
    }
};
#endif