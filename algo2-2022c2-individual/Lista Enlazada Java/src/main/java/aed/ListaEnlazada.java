package aed;

import java.util.*;

public class ListaEnlazada<T> implements Secuencia<T> {
    // Completar atributos privados
    
    private class Nodo{
        // Completar
        T valor;
        Nodo next;
        Nodo back;
        public Nodo(T elem){
            valor = elem;
            next = null;
            back = null;
        }
        
    }
    private Nodo _primero;
    private Nodo _ultimo;
    public ListaEnlazada() {
        _primero=new Nodo(null);
        _ultimo=new Nodo(null);
        _primero.next=_ultimo;
        _ultimo.back=_primero;
        
    }

    public int longitud() {
        int i=0;
        Nodo actual= _primero.next;
        while(actual!= _ultimo){
        i++;
        actual=actual.next;
    }
    return i;
    }

    public void agregarAdelante(T elem) {
        Nodo nuevo = new Nodo(elem);
        if(_ultimo.back==_primero){
            _ultimo.back=nuevo;
        }else{
            _primero.next.back = nuevo;
        }
        nuevo.next=_primero.next;
        nuevo.back=_primero;
        _primero.next=nuevo;
        
    }

    public void agregarAtras(T elem) {
        Nodo nuevo = new Nodo(elem);
        if(_primero.next==_ultimo){
            _primero.next = nuevo;
        }else{
            _ultimo.back.next = nuevo;
        }
        nuevo.back=_ultimo.back;
        nuevo.next=_ultimo;
        _ultimo.back=nuevo;
    }

    public T obtener(int i) {
        int j=0;
        Nodo actual= _primero.next;
        while(j<i){
            actual=actual.next;
            j++;
        }
        return actual.valor;
    }

    public void eliminar(int i) {
        Nodo actual = _primero.next;
        Nodo previo=null;

        if (i == 0) {
            _primero.next=actual.next;
            if (_primero.next != _ultimo){//caso solo un elemento en la lista, apunto _primero a _ultimo y viceversa.
                _ultimo.back=_primero;
            }else{//caso donde hay mas de un elemento
                actual.next.back=_primero;
            }
        }else{
            for (int j = 0; j < i; j++) {
                previo = actual;
                actual = actual.next;
            }
            previo.next=actual.next;
            if (actual.next != _ultimo){
                actual.next.back=previo;
            }else{
                _ultimo.back=actual.back;
            }
            
        }
    }

    public void modificarPosicion(int indice, T elem) {
        Nodo actual=_primero.next;
        int i=0;
        while(i!=indice){
            actual = actual.next;
            i++;
        }
        actual.valor=elem;
    }

    public ListaEnlazada<T> copiar() {
        ListaEnlazada<T> aCopiar = new ListaEnlazada<>();
        Nodo actual = this._primero.next;//para iterar en la lista que me pasan;
        for(int i = 0;i<this.longitud();i++){
            aCopiar.agregarAtras(actual.valor);
            actual=actual.next;
        }
        return aCopiar;
    }

    public ListaEnlazada(ListaEnlazada<T> lista) {
       ListaEnlazada<T> copia = lista.copiar();
       this._primero=copia._primero;
       this._ultimo=copia._ultimo;
    }
    
    @Override
    public String toString() {
        Nodo actual = this._primero.next;
        StringBuilder res=new StringBuilder();
        if(this.longitud()==0){
            res.append("[]");
        }else{
            res.append("[");
            for(int i =0;i<this.longitud();i++){
                res.append(actual.valor.toString());
                if(actual.next==_ultimo){
                    res.append("]");
                }else{
                    res.append(", ");
                }
                actual=actual.next;
            }
        }

        return res.toString();
    }

    private class ListaIterador implements Iterador<T> {
    	// Completar atributos privados
        private Nodo _actual=_primero.next;
        

        public boolean haySiguiente() {
	        return _actual != _ultimo;
        }
        
        public boolean hayAnterior() {
            return _actual.back != _primero;
        }

        public T siguiente() {
            T valor = _actual.valor;
            _actual=_actual.next;
            return valor; 
        }
        
    
        public T anterior() {
	        T valor = _actual.back.valor;
            _actual=_actual.back;
            return valor;

        }
    }

    public Iterador<T> iterador() {
	    return new ListaIterador();
    }

}
