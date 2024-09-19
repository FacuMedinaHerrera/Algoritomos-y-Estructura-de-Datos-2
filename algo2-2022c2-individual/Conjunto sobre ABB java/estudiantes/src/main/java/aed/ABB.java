package aed;
import java.util.*;

// Todos los tipos de datos "Comparables" tienen el método compareTo()
// elem1.compareTo(elem2) devuelve un entero. Si es mayor a 0, entonces elem1 > elem2
public class ABB<T extends Comparable<T>> implements Conjunto<T> {
    // Agregar atributos privados del Conjunto
    private Nodo raiz;
    
    
    private class Nodo {
        // Agregar atributos privados del Nodo
        T valor;
        Nodo izq;
        Nodo der;
        private Nodo minimoNodo(){
            Nodo actual =this;
            while(actual.izq != null){
                actual=actual.izq;
            }
            return actual;
        }
        //Nodo padre;
        // Crear Constructor del nodo
        Nodo(T v){
            valor = v;
            izq =null;
            der=null;
            //padre = null;
        }
    }

    public ABB() {
        raiz =null;
    }
    private int cardinal = 0;
    
    public int cardinal() {
        return cardinal;
    }


    
    public T minimo(){
        Nodo minimo = raiz;
        if(raiz.izq == null){
            return raiz.valor;
        }
        while(minimo.izq != null){
            minimo=minimo.izq;
        }
        return minimo.valor;
    }

    public T maximo(){
        Nodo maximo = raiz;
        if(raiz.der == null){
            return raiz.valor;
        }
        while(maximo.der != null){
            maximo=maximo.der;
        }
        return maximo.valor;
    }

    public void insertar(T clave){
        if(!pertenece(clave)){
            if (raiz == null){
                raiz = new Nodo(clave);
                cardinal++;
            }else {
                Nodo actual = raiz;
                Nodo padre = null;
            while (!clave.equals(actual.valor)) {
                if (clave.compareTo(actual.valor) < 0) {
                    if (actual.izq == null) {
                        actual.izq = new Nodo(clave);
                        cardinal++;
                        break;  // Importante salir del bucle después de insertar
                    } else {//avanzo al siguiente nodo para encontrar la posicion correcta.
                        padre = actual;
                        actual = actual.izq;
                    }
                } else if (clave.compareTo(actual.valor) > 0) {
                    if (actual.der == null) {
                        actual.der = new Nodo(clave);
                        cardinal ++;
                        break;  // Importante salir del bucle después de insertar
                    } else {//avanzo al siguiente nodo para encontrar la posicion correcta.
                        padre = actual;
                        actual = actual.der;
                    }
                }
            }
        }
    }
}

    public boolean pertenece(T elem){
        if(raiz==null){
            return false;
        }
        T _raiz = raiz.valor;
        Nodo actual = raiz;
        while(elem.compareTo(_raiz)!=0){
            if(elem.compareTo(_raiz)<0){
                actual = actual.izq;
                if(actual==null){
                    return false;
                }
                _raiz = actual.valor;
            }
            if(elem.compareTo(_raiz)>0){
                actual=actual.der;
                if(actual==null){
                    return false;
                }
                _raiz=actual.valor;
            }
        }
        return elem.compareTo(_raiz)==0;
    }

    public void eliminar(T clave){
        Nodo padre = raiz;
        Nodo actual = raiz;
        if (pertenece(clave)) {
            while (clave.compareTo(actual.valor)!=0) {
                if (clave.compareTo(actual.valor)<0) {
                    padre = actual;
                    actual = actual.izq;
                }
                else if (clave.compareTo(actual.valor)>0) {
                    padre = actual;
                    actual = actual.der;
                }
            }
            // Caso 1, el nodo a borrar es hoja:
            if (actual.der == null && actual.izq == null) {
                if (actual == raiz) {
                    raiz = null;
                } else if (actual.valor.compareTo(padre.valor)<0){
                    padre.izq = null;
                }else if (actual.valor.compareTo(padre.valor) > 0){
                    padre.der = null;
                }
                cardinal--;
            }
                // Caso 2, Solo un hijo.
            else if (actual.der == null && actual.izq != null) {//el hijo esta a la izquierda
                if (clave.compareTo(padre.valor)<0) {
                    padre.izq = actual.izq;
                    
                } else if (clave.compareTo(padre.valor)>0) {
                    padre.der = actual.izq;
                    
                }else{//es la raiz y solo tiene un subarbol izquierdo
                    raiz=actual.izq;
                    actual.izq= null;//por seguridad 
                    
                }
                cardinal--;
            } else if (actual.der != null && actual.izq == null) {//el hijo esta a la derecha
                if (clave.compareTo(padre.valor)<0) {
                    padre.izq = actual.der;
                    
                } else if (clave.compareTo(padre.valor)>0) {
                    padre.der = actual.der;
                    
                }else{//es la raiz y tien un subarbol a la derecha
                    raiz=actual.der;
                    actual.der= null;
                    
                }
                cardinal--;
            }
                //Caso 3, nodo con dos hijos.
            else if (actual.izq != null && actual.der != null) {
                //apunto el padre a la derecha del que voy a eliminar
                if (clave.compareTo(padre.valor)>0) {
                    padre.der = actual.der;
                    Nodo inmSucesor = actual.der;
                    while (inmSucesor.izq != null) {
                        inmSucesor = inmSucesor.izq;
                    }
                    inmSucesor.izq = actual.izq; //reinserto el sub-arbol a la izquierda del valor a eliminar en un lugar que respete la estructura del arbol.
                    
                } else if (clave.compareTo(padre.valor)<0) {
                    padre.izq = actual.der;
                    Nodo inmSucesor = actual.der;
                    while (inmSucesor.izq != null) {
                        inmSucesor = inmSucesor.izq;
                    }
                    inmSucesor.izq = actual.izq;
                   
                }else{//El que quiero borrar es la raiz
                     if(raiz.der != null){
                        actual = actual.der;
                        while(actual.izq!=null){
                            padre = actual;
                            actual=actual.izq;
                        }
                     }
                     //obtuve el valor del inmediato sucesor. Si existe el sucesor sera ese y sino, seguira valiendo la raiz.
                     //En caso de que no haya sucesor, debo eliminar la raiz actual y decir que la raiz ahora es el siguiente a la izquierda, total el abb seguira valiendo
                     //En caso de que si haya sucesor, debere reacomodar los nodos para decir que la raiz es el sucesor y que sus viejos padres no apunten hacia la nueva raiz
                     if(actual.valor.equals(raiz.valor)){
                        raiz=raiz.izq;
                     }else{//ojo si el padre del sucesor es la raiz.
                        if(padre.valor.equals(raiz.valor)){
                            actual.izq = raiz.izq;
                        }else{
                            actual.izq = raiz.izq;
                            padre.izq = actual.der;
                            actual.der=raiz.der;
                        }
                        raiz=actual;
                     }
                     
                }
                cardinal--;
            }
        }
    }
    
    public String toString(){
        StringBuilder aImprimir=new StringBuilder();
        Iterador <T> it = iterador();
        aImprimir.append("{");
        while(it.haySiguiente()){
            aImprimir.append(it.siguiente());
            if(it.haySiguiente()){
                aImprimir.append(",");
            }else{
                aImprimir.append("}");
            }
        }
        return aImprimir.toString();
    } 
    private class ABB_Iterador implements Iterador<T> {
        private class Pair<A, B> {
            private A first;
            private B second;
             
            public Pair(A first, B second){
                this.first = first;
                this.second = second;
            } 

            public A getFirst() {
                return first;
            }
            public B getSecond() {
                return second;
            }
        }
        private Nodo iterator = new Nodo(minimo());
        
         public boolean haySiguiente() {            
            return iterator != null;
         }
          
        public T siguiente(){
            T result = iterator.valor;
            
            siguienteAux(iterator.valor);
            
            return result;
        }
        private void siguienteAux(T clave) { //PRIMERO ES ENCONTRAR EL VALOR, LUEGO ACTUALIZAR EL ITERADOR.
             Nodo  actual = raiz;
             Nodo  padre= raiz;
             ArrayList<Pair<Nodo ,String>> nodos=new ArrayList<>();//array de tuplas de nodo que se fija si entro por izq o der
             while(!clave.equals(actual.valor)){ //asi encuentro el valor actual y me guardo el camino realizado para llegar.
                if (clave.compareTo(actual.valor)<0){
                    padre =actual;
                    Pair<Nodo,String> par=new Pair<>(actual,"izq");
                    nodos.add(par);
                    actual=actual.izq;
                }
                if (clave.compareTo(actual.valor)>0){
                    padre = actual;
                    Pair <Nodo,String> par=new Pair<>(actual,"der");
                    nodos.add(par);
                    actual=actual.der;
                }
                 //AHORA TENGO QUE ENCONTRAR HACIA DONDE AVANZAR EL ITERADOR. Es decir, que valor toma iterator
             } //Si tiene hijo derecho, es el minimo del sub arbol derecho.
             if (actual.der != null){
                iterator=actual.der.minimoNodo();
             }
             //Si no hay hijo derecho y es hijo izquierdo, su padre es el sucesor.
             else if ( actual.der == null && actual.valor.compareTo(padre.valor) < 0){
                iterator=padre;
             }
         //Si no tiene hijo derecho, y es hijo derecho, subir hasta uno mas del primer nodo que es hijo izquierdo o a la raiz.
             else if (actual.der== null && actual.valor.compareTo(padre.valor) > 0){
                 int i=nodos.size()-1;
                 while(i >= 0 && nodos.get(i).getSecond() != "izq"){
                     i--;
                 }
                 
                 if(i < 0){//el arbol es degenerado a la derecha por lo que no hay sucesor ya que no tiene mas hijos a la derecha.
                    //por decision personal dire que el siguiente al ultimo sera null.
                    iterator = null;
                 }else{
                    iterator=nodos.get(i).getFirst();
                
                }
              
             }
         }
     }
     public Iterador<T> iterador() {
        return new ABB_Iterador();
    }
}   

        


