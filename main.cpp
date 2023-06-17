#include <iostream>
#include "Direccion.hpp"
#include "Pedido.hpp"
using namespace std;
int main()
{
    Direccion* dir = new Direccion(2,1,7);
    cout<<dir->getIndice();
    Pedido* pedido1 = new Pedido(3,dir);
    cout<<pedido1->lugar->getIndice();
}