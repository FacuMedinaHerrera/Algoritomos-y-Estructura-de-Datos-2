#include "Lista.h"

Lista::Lista():_primero(nullptr),_ultimo(nullptr) {
    // Completar
}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    Nodo* actual=_primero;
    while(_primero != nullptr){
        _primero=_primero->next;
        delete actual;
        actual = _primero;
    }
}

Lista& Lista::operator=(const Lista& aCopiar) {
    // Completar
    if (this->_primero != nullptr) {
        Nodo *actual = this->_primero;
        while (actual != nullptr) {
            this->_primero = _primero->next;
            delete actual;
            actual = this->_primero;
        }
    }
    if (aCopiar._primero!=nullptr) {
        Nodo* actual=new Nodo(*aCopiar._primero);
        Nodo*ultimo=new Nodo(*aCopiar._ultimo);
        this->_primero =actual;

        Nodo* actualACopiar=aCopiar._primero->next;
        Nodo* previo;
        while(actualACopiar->next != nullptr){
            previo=actual;
            actual->next=new Nodo(*actualACopiar);
            actual=actual->next;
            actual->back=previo;
            actualACopiar = actualACopiar->next;
        }
        if (actualACopiar->next== nullptr){
            ultimo->back=actual;
            actual->next=ultimo;
        }
        this->_ultimo =ultimo;
    }else{

        this->_primero= nullptr;
        this->_ultimo= nullptr;

    }

    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    // Completar
    Nodo* nuevo = new Nodo(elem);
    nuevo->next=_primero;
    if(_primero== nullptr){
        _ultimo=nuevo;
    }else{
        _primero->back=nuevo;
    }
    _primero=nuevo;
}

void Lista::agregarAtras(const int& elem) {
    Nodo* nuevo = new Nodo(elem);
    nuevo->back=_ultimo;
    if(_primero== nullptr){
        _primero=nuevo;
    }else{
        _ultimo->next=nuevo;
    }
    _ultimo=nuevo;
}

void Lista::eliminar(Nat i) {
    // Completar
    Nodo* actual = _primero;
    Nodo* previo;

    if (i == 0) {
        previo=_primero;
        _primero=_primero->next;
        if (_primero != nullptr){
            _primero->back = nullptr;
        }
        delete previo;
    }else{
        for (int j = 0; j < i; j++) {
            previo = actual;
            actual = actual->next;
        }
        previo->next=actual->next;
        if (actual->next != nullptr){
            actual->next->back=previo;
        }else{
            _ultimo=actual->back;
        }
        delete actual;
    }
}

int Lista::longitud() const {
    // Completar
    int i=0;
    Nodo* actual= _primero;
    while(actual != nullptr){
        i++;
        actual=actual->next;
    }
    return i;
}

const int& Lista::iesimo(Nat i) const {
    // Completar
    int j=0;
    Nodo* actual= _primero;
    while(j<i){
        actual=actual->next;
        j++;
    }
    return actual->valor;
}

int& Lista::iesimo(Nat i) {
    // Completar (hint: es igual a la anterior...)
    int j=0;
    Nodo* actual= _primero;
    while(j<i){
        actual=actual->next;
        j++;

    }
    return actual->valor;
    //assert(false);
}

void Lista::mostrar(ostream& o) {
    // Completar
    Nodo *actual = _primero;
    o << "[";
    while (actual != _ultimo) {
        o << actual->valor;
        actual=actual->next;
        if (actual == _ultimo){
            o<<"]";
        }else{
            o<<", ";
        }
    }
}