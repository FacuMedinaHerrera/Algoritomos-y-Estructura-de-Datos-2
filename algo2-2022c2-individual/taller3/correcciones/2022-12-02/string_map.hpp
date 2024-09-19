
#include "string_map.h"

template <typename T>
string_map<T>::string_map(): _raiz(nullptr), _size(0){
    // COMPLETAR
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    // COMPLETAR
    _size = d._size;
    this->_raiz = new Nodo();
    if(d._size == 0) {
        return *this;
    }else{
        copiaDeTrie(d._raiz,_raiz);
        return *this;
    }
}
template<typename T>
void string_map<T>::copiaDeTrie(Nodo* original, Nodo* copia) {
    for (int i = 0; i< original->siguientes.size();i++) {

        if (original->siguientes[i] != nullptr){
            copia->siguientes[i] = new Nodo();
            if (original->siguientes[i]->definicion != nullptr){
                copia->siguientes[i]->definicion = new T(*(original->siguientes[i]->definicion));
            }
            copiaDeTrie(original->siguientes[i],copia->siguientes[i]);
        }
    }
}
template <typename T>
string_map<T>::~string_map(){
    // COMPLETAR
    if(_raiz != nullptr) {
        Nodo *actual = _raiz;
        auxDestructor(actual);
    }
}
template<typename T>
void string_map<T>::auxDestructor(Nodo *actual) {
    bool esHoja = false;
    for(int i = 0; i<256; i++){
        if(actual->siguientes[i] != nullptr){
            esHoja = false;
            auxDestructor(actual->siguientes[i]);
            actual->siguientes[i] = nullptr;
        }else{
            esHoja=true;
        }
    }
    if(esHoja){
        if(actual->definicion != nullptr){
            delete actual->definicion;
        }
        delete actual;
    }
}
template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR

}


template <typename T>
int string_map<T>::count(const string& clave) const{
    // COMPLETAR
    if (_raiz == nullptr) return 0;
    Nodo* actual = _raiz;
    int res = 0;
    int i = 0;
    while((actual->siguientes)[int (clave[i])] != nullptr && !res && i < clave.size()){
        actual = actual->siguientes[int (clave[i])];
        if ( i == clave.size()-1 && actual->definicion != nullptr){
            res = 1 ;
        }
        i++;
    }
    return  res;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    // COMPLETAR
    Nodo* actual = _raiz;

    for (int i = 0; i < clave.size(); ++i) {
        actual=actual->siguientes[int (clave[i])];

    }
    return *(actual->definicion);
}

template <typename T>
T& string_map<T>::at(const string& clave) { //modificable
    // COMPLETAR
    Nodo* actual = _raiz;

    for (int i = 0; i < clave.size(); ++i) {
        actual=actual->siguientes[int (clave[i])];

    }
    return *(actual->definicion);
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    // COMPLETAR
    //Armo una lista con los nodos correspondientes a la clave
    Nodo* actual =_raiz;
    vector<Nodo*> aBorrar;
    for (int i = 0; i < clave.size(); ++i) {
        aBorrar.push_back(actual->siguientes[int(clave[i])]);
        actual=actual->siguientes[int(clave[i])];
    }
    //borrado
    for (int i = aBorrar.size()-1; i >= 0; i--) {
        if(aBorrar[i]->definicion != nullptr){
            delete aBorrar[i]->definicion;
            aBorrar[i]->definicion= nullptr;
        }
        if(i<aBorrar.size()-1 && aBorrar[i]->definicion != nullptr ) {
            if(aBorrar[i]->definicion == nullptr) {
                delete (aBorrar[i]);
                aBorrar[i] = nullptr;
                _size--;
            }
        }
    }
}

template <typename T>
int string_map<T>::size() const{
    // COMPLETAR
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    // COMPLETAR
    if (_raiz == nullptr) return true;
    else return false;
}

template<typename T>
void string_map<T>::insert(const pair<string, T> &aInsertar) {
    if (_raiz == nullptr){
        _raiz = new Nodo();
    }
    Nodo* actual=_raiz;
    for (int i = 0; i < aInsertar.first.size() ; ++i) {
        if (actual->siguientes[int (aInsertar.first[i])] != nullptr){// son prefijos
            //si ya existe una letra con definicion:
            if (actual->siguientes[int(aInsertar.first[i])]->definicion != nullptr && i == aInsertar.first.size()-1){
                delete actual->siguientes[int(aInsertar.first[i])]->definicion;
                actual->siguientes[int(aInsertar.first[i])]->definicion = new T(aInsertar.second);
            }
            //avanzar el actual sobre este puntero
            actual=actual->siguientes[int (aInsertar.first[i])];
        }else{
            //apuntar el puntero a un nuevo nodo insertado.
            if (i==aInsertar.first.size() -1){ //al ultimo elemento de la palabra lo inserto con la definicion
                actual->siguientes[int (aInsertar.first[i])] = new Nodo();
                actual = actual->siguientes[int (aInsertar.first[i])];
                actual->definicion = new T(aInsertar.second);
                _size++;
            }else {//mientras no sea la ultima letra de la palabra, inserto nodos inicializados en null
                actual->siguientes[int(aInsertar.first[i])] = new Nodo();
                actual = actual->siguientes[int(aInsertar.first[i])];
            }
        }
    }
}





