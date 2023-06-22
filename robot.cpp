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
        Lista<Pedido*>* ordenTotal = new Lista<Pedido*>;

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
        

        int devuelveCamino(int origen, int meta, bool imprimir);
        void printSecuenciaCamino(int origen, int meta, int prev[Alcance]);

        int realizarPedidos()
        {
            int *costo = new int();
            *costo = 0;
            int n =1;
            while(!pedidos->esvacia()){
                cout << "Viaje numero " << n << endl;
                int costoDelViaje = realizarRecorrido(pedidos);
                *costo += costoDelViaje;
                volumenOcupado=0;
                n++;
                cout << "Costo del viaje: " << costoDelViaje << endl << endl;
            }
            return *costo;
        }

        int realizarRecorrido(Lista<Pedido*>* pedidosARealizar)
        {
            int *costo = new int();
            *costo = 0;

            //lista que almacena el camino realizado comenzando por el ultimo punto recorrido
            Lista<Pedido*>* ordenRealizado = new Lista<Pedido*>;

            //pedido en el que se encuentra actualmente el robot
            Pedido *pedidoActual = new Pedido();
            Pedido *pedidoAnterior = new Pedido();
        
            for (int i = 0; i < pedidosARealizar->size(); i++)
            {
                if(pedidoActual!=NULL){
                    //1ro comparar caja con todos los pedidos 
                    if(i == 0 ) pedidoActual = pedidoMasCercano(360, pedidos, costo);

                    //2do comparar pedido elegido con el resto 
                    else pedidoActual = pedidoMasCercano(pedidoActual->lugar, pedidos, costo);
                } 
                if(pedidoActual!=NULL){
                    //borrar de pendientes, agregar a realizados, actualizar ubicacion del robot
                    pedidos->borrar(pedidoActual);
                    ordenRealizado->add(pedidoActual);
                    ubicacion = pedidoActual->lugar;
                    pedidoAnterior = pedidoActual;             
                }
                
            }
            //volver a la caja 
            *costo += devuelveCamino(pedidoAnterior->lugar, 360, true);
            ubicacion = pedidoAnterior->lugar;
            return *costo; 
        }

        //Devuelve el pedido que se encuentra mas cerca y actualiza el costo global
        Pedido* pedidoMasCercano(int primerPedido, Lista<Pedido*>* pedidosPendientes,int *costoGlobal){
            
            Pedido* masCercano;
            int costo = INFINITO;
            bool flag = false;

            for (int i = 0; i < pedidosPendientes->size(); i++)
            {
                Pedido* pedidoAux = pedidosPendientes->elemento(i);
                int costoAux = devuelveCamino(primerPedido, pedidoAux->lugar,false);
                if(costoAux < costo && comprobarVolumen(pedidoAux->mercaderia)){
                    masCercano = new Pedido(*pedidoAux);
                    costo = costoAux;
                    flag = true;
                }
                //delete pedidoAux;
            }

            if(flag){
                if(costoGlobal == nullptr) *costoGlobal = costo;
                else *costoGlobal += costo;
                volumenOcupado += masCercano->getMercaderia();
                devuelveCamino(primerPedido, masCercano->lugar,true);
                return masCercano;
            }
            return NULL;
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

int Robot::devuelveCamino(int origen, int meta, bool imprimir)
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
    if(imprimir) {
        printSecuenciaCamino(origen, meta, previos);
        cout << endl << endl;
    }
    return costoPorIter[meta];
}

#endif