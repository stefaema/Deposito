#include <iostream>
#include "lista.hpp"
#include "Pedido.hpp"

#ifndef ROBOT_CPP
#define ROBOT_CPP
class Robot
{
    public:
    Lista<Pedido*>* pedidos;
    int ubicacion;
    Robot()
    {
        pedidos = new Lista<Pedido*>();
        ubicacion = 360;
    }
    Robot(Lista<Pedido*>* list)
    {
        pedidos = list;
    }
    void realizarPedidos()
    {

    }







};



#endif