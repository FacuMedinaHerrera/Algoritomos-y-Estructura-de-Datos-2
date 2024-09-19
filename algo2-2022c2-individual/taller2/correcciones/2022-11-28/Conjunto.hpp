#define IZQ false
#define DER true
typedef bool DIR;
template <class T>
Conjunto<T>::Conjunto():_raiz(nullptr) {
    // Completar

}

template <class T>
Conjunto<T>::~Conjunto() { 
    // Completar
    if (_raiz != nullptr) destructorAux(_raiz,_raiz);

}
template <class T>
void Conjunto<T>::destructorAux(Nodo* raiz, Nodo* padre) {
    Nodo* actual = raiz;

    if (actual->izq != nullptr){
        destructorAux(actual->izq,actual);
    }
    if (actual->der != nullptr){
        destructorAux(actual->der,actual);
    }
    if (actual->der == nullptr && actual->izq == nullptr){
        if (actual->valor < padre->valor){
            padre->izq = nullptr;
        }else if (actual->valor > padre->valor){
            padre->der = nullptr;
        }
        delete(actual);
    }
}
template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    if (_raiz == nullptr) return false;
    T raiz= _raiz->valor;
    Nodo* actual = _raiz;
    while(raiz != clave){
        if (clave <raiz){
            actual = actual->izq;
            if (actual == nullptr) return false;
            raiz = actual->valor;
            }
        if (clave > raiz){
            actual=actual->der;
            if (actual == nullptr)return false;
            raiz = actual->valor;
        }
    }
    return raiz == clave;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if (_raiz == nullptr){
       _raiz = new Nodo(clave);
    }else {
        T raiz = _raiz->valor;
        Nodo *actual = _raiz;
        Nodo *padre;
        while (raiz != clave) {
            if (clave < raiz) {
                padre = actual;
                actual = actual->izq;
                if (actual == nullptr) {
                   insertarAux(padre, clave, actual);
                }
                raiz = actual->valor;
            }
            if (clave > raiz) {
                padre = actual;
                actual = actual->der;
                if (actual == nullptr){
                    insertarAux(padre, clave, actual);
                }
                raiz = actual->valor;
            }
        }
    }
}

template <class T>
void Conjunto<T>::insertarAux(Nodo* padre, const T& clave, Nodo*&nuevo){
    nuevo= new Nodo(clave);
    if (clave<padre->valor){
        padre->izq=nuevo;
    }
    if (clave>padre->valor)padre->der=nuevo;
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    Nodo *padre = _raiz;
    Nodo *actual = _raiz;
    if (pertenece(clave)) {
        while (actual->valor != clave) {
            if (clave < actual->valor) {
                padre = actual;
                actual = actual->izq;
            }
            else if (clave > actual->valor) {
                padre = actual;
                actual = actual->der;
            }
        }
        // Caso 1, el nodo a borrar es hoja:
        if (actual->der == nullptr && actual->izq == nullptr) {
            if (actual == _raiz) {
                _raiz = nullptr;
            } else if (actual->valor < padre->valor){
                padre->izq = nullptr;
            }else if (actual->valor > padre->valor){
                padre->der = nullptr;
            }
            delete (actual);
        }
            // Caso 2, Solo un hijo.
        else if (actual->der == nullptr && actual->izq != nullptr) {
            if (clave < padre->valor) {
                padre->izq = actual->izq;
                delete (actual);
            } else if (clave > padre->valor) {
                padre->der = actual->izq;
                delete (actual);
            }else{//es la raiz y solo tiene un subarbol izquierdo
                _raiz=actual->izq;
                actual->izq= nullptr;//por seguridad
                delete(actual);
            }
        } else if (actual->der != nullptr && actual->izq == nullptr) {
            if (clave < padre->valor) {
                padre->izq = actual->der;
                delete (actual);
            } else if (clave > padre->valor) {
                padre->der = actual->der;
                delete (actual);
            }else{//es la raiz y tien un subarbol a la derecha
                _raiz=actual->der;
                actual->der= nullptr;
                delete(actual);
            }
        }
            //Caso 3, nodo con dos hijos.
        else if (actual->izq != nullptr && actual->der != nullptr) {
            //apunto el padre a la derecha del que voy a eliminar
            if (clave > padre->valor) {
                padre->der = actual->der;
                Nodo *inmSucesor = actual->der;
                while (inmSucesor->izq != nullptr) {
                    inmSucesor = inmSucesor->izq;
                }
                inmSucesor->izq = actual->izq;
                delete (actual);
            } else if (clave < padre->valor) {
                padre->izq = actual->der;
                Nodo *inmSucesor = actual->der;
                while (inmSucesor->izq != nullptr) {
                    inmSucesor = inmSucesor->izq;
                }
                inmSucesor->izq = actual->izq;
                delete (actual);
            }else{//El que quiero borrar es la raiz
                T inmSucesor= this->siguiente(actual->valor);
                Nodo* aBorrar;
                actual=actual->der;
                if (actual->valor!= inmSucesor) {
                    while (actual->izq->valor != inmSucesor) {
                        actual = actual->izq; //nodo padre del inmediato sucesor, debo desapuntar su izquierda ya que ese sera movido a la raiz
                    }
                    padre->valor=inmSucesor;
                    aBorrar = actual->izq;
                    if (aBorrar->der != nullptr){
                        actual->izq=aBorrar->der;
                    }else{
                        actual->izq= nullptr;
                    }
                    delete(aBorrar);
                }else if (actual->valor == inmSucesor){
                    padre->der=actual->der;
                    padre->valor=inmSucesor;
                    delete(actual);
                }
            }
        }
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo* actual = _raiz;
    Nodo* padre= _raiz;
    vector<pair<Nodo*,DIR>> Nodos;
    T sucesor;//tupla de nodo que se fija si entro por izq o der
    while(actual->valor != clave){
        if (clave < actual->valor){
            padre =actual;
            Nodos.push_back(make_pair(actual,IZQ));
            actual=actual->izq;
        }
        if (clave>actual->valor){
            padre = actual;
            Nodos.push_back(make_pair(actual,DER));
            actual=actual->der;
        }
    } //Si tiene hijo derecho, es el minimo del sub arbol derecho.
    if (actual->der != nullptr){
        actual=actual->der;
        while(actual->izq != nullptr){
            actual = actual->izq;
        }
        return actual->valor;
    }
    //Si no hay hijo derecho y es hijo izquierdo, su padre es el sucesor.
    else if ( actual->der == nullptr && actual->valor < padre->valor){
        return padre->valor;
    }
    //Si no tiene hijo derecho, y es hijo derecho, subir hasta el primer nodo que es hijo izquierdo o la raiz.
    else if (actual->der== nullptr && actual->valor > padre->valor){
        int i=Nodos.size()-1;
        while(Nodos[i].second != IZQ){
            i--;
        }
        i--;
        sucesor=Nodos[i].first->valor;
        if (sucesor==_raiz->valor){
            sucesor = actual->valor;
        }
        return sucesor;
    }

}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* minimo=_raiz;
    if (_raiz->izq == nullptr)return _raiz->valor;
    while (minimo->izq!= nullptr){
        minimo=minimo->izq;
    }
    return minimo->valor;
}
template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* maximo=_raiz;
    if (_raiz->der == nullptr)return _raiz->valor;
    while (maximo->der!= nullptr){
        maximo=maximo->der;
    }
    return maximo->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    unsigned int res=0;
    Nodo* actual = _raiz;
    if (actual != nullptr){
        res++;
       res = cardinalAux(res, actual);
    }
    return res;
}
template <class T>
unsigned int Conjunto<T>::cardinalAux(unsigned int& res, Nodo *actual) const {

    if (actual->der != nullptr){
        cardinalAux(res,actual->der);
    }
    if (actual->izq != nullptr){
        cardinalAux(res,actual->izq);
    }
    return res++;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

