#include <iostream>
#include "lista.hpp"
#include "Pedido.hpp"

#ifndef ROBOT_CPP
#define ROBOT_CPP
class Robot
{
    private:
        int ubicacion;
        int maximo;
        int volumenOcupado = 0;
        Lista<Pedido*>* pedidos;
    
    public:
        
        Robot()
        {
            pedidos = new Lista<Pedido*>();
            ubicacion = 360;
            maximo = 10;
        }
        Robot(Lista<Pedido*>* list)
        {
            pedidos = list;
        }

        bool comprobarVolumen(int volumenNuevo)
        {
            if(volumenOcupado + volumenNuevo > maximo) return false;
            else return true;
        }
        
        void ingresarPedido(Pedido* pedidoNuevo)
        {
            if(comprobarVolumen(pedidoNuevo->getMercaderia())){
                pedidos->add(pedidoNuevo);
                volumenOcupado+=pedidoNuevo->getMercaderia();
                cout << "Pedido ingresado correctamente\n";
            }
            else cout << "No fue posible ingresar el pedido\n" << "Capacidad disponible: "<< maximo-volumenOcupado <<endl;
        }

        void realizarPedidos()
        {

        }







};



#endif