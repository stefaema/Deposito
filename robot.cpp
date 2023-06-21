#include <iostream>
#include "lista.hpp"
#include "Pedido.hpp"

#ifndef ROBOT_CPP
#define ROBOT_CPP
#define Alcance  361
#define NO_MIEMBRO 0
#define MIEMBRO 1

const int INFINITO = 1000000;

class Robot
{
    private:
        int ubicacion;
        int maximo;
        int volumenOcupado = 0;
        Lista<Pedido*>* pedidos;
        int (*matrizAdyacente)[Alcance];

    public:
        
        Robot(int matriz[Alcance][Alcance])
        {
            pedidos = new Lista<Pedido*>();
            ubicacion = 360;
            maximo = 10;
            matrizAdyacente = matriz;
        }
        Robot(Lista<Pedido*>* list, int matriz[Alcance][Alcance])
        {
            pedidos = list;
            maximo = 10;
            matrizAdyacente = matriz;
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

        int devuelveCamino(int origen, int meta);
        void printSecuenciaCamino(int origen, int meta, int prev[Alcance]);
        void realizarPedidos()
        {
            //1ro comparar caja con todos los pedidos
            //2do coparar pedido elegido con el resto
            //repetir 2 hasta hacer todos
            //volver a la caja

            int* costo = 0;
            Lista<*Pedido> ordenRealizado;
            Lista<Pedido> pedidosPendientes = pedidos;

            pedidoMasCercano(361, pedidos, costo);

            for (int i = 0; i < pedidos->size(); i++)
            {
            }
            
        }

        //Devuelve el pedido que se encuentra mas cerca y actualiza el costo global
        Pedido pedidoMasCercano(int primerPedido, Lista<Pedido> pedidosPendientes,int* costoGlobal){
            
            Pedido masCercano;
            int costo = INFINITO;

            for (int i = 0; i < pedidosPendientes->size(); i++)
            {
                Pedido pedidoAux = pedidosPendientes->elemento(i);
                int costoAux = devuelveCamino(primerPedido.lugar, pedidoAux.lugar);
                if(costoAux < costo){
                    masCercano = pedidoAux;
                    costo = costoAux;
                }
            }
            costoGlobal += costo;
            return masCercano;
        }

};

void Robot::printSecuenciaCamino(int origen, int meta, int prev[Alcance])
{
    if (meta==origen) cout<< origen<<"  ";
    else{
        printSecuenciaCamino(origen,prev[meta],prev);
        cout<<meta<<"  ";
    }
}

int Robot::devuelveCamino(int origen, int meta)
{
    int actual, i, k, continua, menordist, nuevadist;
    int previos[Alcance];
    int costoPorIter[Alcance];
    int visitados[Alcance];
    for (int i = 0; i < Alcance; i++)
    {
        visitados[i]=NO_MIEMBRO;
        previos[i] = -1;
        costoPorIter[i]=INFINITO;
    }
    visitados[origen]= MIEMBRO; costoPorIter[origen]=0; actual = origen; continua=1; k=0;
    while((actual != meta)&&(continua == 1))
    {
        continua = 0;
        menordist = INFINITO;
        for(i=0; i < Alcance; i++)
        {
            if(visitados[i] == NO_MIEMBRO)
            {
                nuevadist = costoPorIter[actual]+matrizAdyacente[actual][i];
                if(nuevadist<costoPorIter[i])
                {
                    costoPorIter[i]=nuevadist;
                    previos[i]=actual; continua=1;
                }
                if(costoPorIter[i]<menordist)
                {
                    menordist = costoPorIter[i];
                    k=i; continua=1;
                }
            }
        }
        actual = k;
        visitados[actual] = MIEMBRO;
    }
    printSecuenciaCamino(origen, meta, previos);
    return costoPorIter[meta];
}

#endif