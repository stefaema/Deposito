
#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace std;
#ifndef LISTA_HPP
#define LISTA_HPP


template <class T> class Nodo {
private:
    T dato;
    Nodo* next;
public:
    Nodo() { next = NULL; };
    Nodo(T a) { dato = a; next = NULL; };
    void set_dato(T a) { dato = a; };
    void set_next(Nodo* n) { next = n; };
    T get_dato() { return dato; };
    Nodo* get_next() { return next; };
    bool es_vacio() { return next == NULL; }
};

template <class T> class Lista {
private: Nodo<T>* czo;
public:
    Lista() { czo = new Nodo<T>(); };
    Lista(Nodo<T>* n) { czo = n; };
    //~Lista(void);
    void add(T d);
    bool esvacia(void);
    T cabeza(void);
    Lista* resto(void);
    string toPrint(string p);
    T suma(T i);
    int size();
    T elemento(int indice);
    void borrar(T elemento);
    void borrarCabeza(void);
    Lista<T>* copy(void);
    void concat(Lista<T>* l1);
};
template <class T>
void Lista<T>::add(T d)
{
    Nodo<T>* nuevo = new Nodo<T>(d);
    nuevo->set_next(czo);
    czo = nuevo;
}
template <class T>
bool Lista<T>::esvacia(void)
{
    return czo->es_vacio();
}
template <class T>
T Lista<T>::cabeza(void)
{
    if (esvacia()) {
        cout << " Error, Cabeza de lista vacia";
        return NULL;
    }
    return czo->get_dato();
}
template <class T>
Lista<T>* Lista<T>::resto(void)
{
    Lista* l = new Lista(czo->get_next());
    return (l);
}
template <class T>
string Lista<T>::toPrint(string p)
{
    if (this->esvacia()) {
        return p;
    }
    else {
        //std::ostringstream stm;
        ostringstream stm;
        stm << this->cabeza() << "-" << this->resto()->toPrint(p) << endl;
        //cout<<endl<<" stm.str()= "<<stm.str()<<endl;
        return stm.str();
    }
}
template <class T>
T Lista<T>::suma(T i)
{    //cout<<" i al entrar= "<<i<<endl;
    if (this->esvacia()) {
        return i;
    }
    else {

        //cout<<"this->cabeza()= "<<this->cabeza()<<endl;   
        return this->resto()->suma(i + this->cabeza());
    }
};
template <class T> 
int Lista<T>::size()
{
    if (this->esvacia()) return 0;
    return 1 + this->resto()->size();
};

template <class T> 
T Lista<T>::elemento(int indice)
{
    if(indice==0){return cabeza();}
    else return resto()->elemento(indice-1);
};

template <class T>
void Lista<T>::borrar(T elemento)
{
    if (!esvacia()) {
        if (*cabeza() == *elemento) {
            borrarCabeza();
        }
        else {
            Lista<T>* restoLista = resto();
            restoLista->borrar(elemento);
            czo->set_next(restoLista->czo);
            delete restoLista;
        }
    }
}

template <class T> void Lista<T>::borrarCabeza(void)
{ //borra el nodo cabeza
    if (!this->esvacia()) {
        Nodo<T>* tmp = czo;
        czo = czo->get_next();
        delete tmp;
    }
}
template <class T> void Lista<T>::concat(Lista<T>* l1)
{// le transfiere los datos de l1 a this
    if (!(l1->esvacia())) {
        this->concat(l1->resto());
        this->add(l1->cabeza());
    }
}
template <class T> Lista<T>* Lista<T>::copy(void)
{
    Lista<T>* aux = new Lista();
    aux->concat(this);
    return aux;
}
#endif