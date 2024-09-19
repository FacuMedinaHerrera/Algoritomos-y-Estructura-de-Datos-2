#ifndef ALGO2_LABO_CLASE5_ALGORITMOS_H
#define ALGO2_LABO_CLASE5_ALGORITMOS_H

#include <utility>
#include <iterator>
#include <vector>

// Completar con las funciones del enunciado
template <class Contenedor>
typename Contenedor::value_type minimo(const Contenedor& c){
    auto it = c.begin();
    auto min=*it ;
    while(it!=c.end()){
        if(min>*it)min=*it;
        it++;
    }
    return min;
}
template <class Contenedor>
typename Contenedor::value_type promedio(const Contenedor& c){
    auto iterador=c.begin();
    double valor=0;
    double contador=0;
    while(iterador!=c.end()){
        valor+=*iterador;
        contador++;
        iterador++;
    }
    return valor/contador;
}
template <class Iterator>
typename Iterator::value_type minimoIter(const Iterator& desde, const Iterator& hasta){
    auto min=*desde;
    auto it=desde;
    while(it!=hasta){
        if(min>*it)min=*it;
        it++;
    }
    return min;
}
template<class Iterator>
typename Iterator::value_type promedioIter(const Iterator& desde,const Iterator& hasta){
    double contador=0;
    double suma=0;
    auto it=desde;
    while ( it != hasta){
        suma+=*it;
        contador++;
        it++;
    }
    return suma/contador;
}
template <class Contenedor>
void filtrar(Contenedor &c,const typename Contenedor::value_type& elem){
    auto it=c.begin();
    auto aBorrar=it;
    while(it!=c.end()){
        it++;
        if(*aBorrar==elem){
            c.erase(aBorrar);
        }
        aBorrar=it;
    }
}
template <class Contenedor>
bool ordenado(Contenedor &c){
    auto it=c.begin();
    auto it2=++c.begin();
    bool res=true;
    for(it;it2!=c.end()&&res;it++,it2++){
        if(*it > *it2){
            res=false;
        }
    }
    return res;
}
template <class Contenedor>
std::pair<Contenedor,Contenedor> split(const Contenedor& c,const typename Contenedor::value_type& elem){
    auto it=c.begin();
    Contenedor primero;

    Contenedor segundo;
    auto itPrimero=primero.begin();
    auto itSegundo=segundo.begin();
    for(it;it!=c.end();it++){
        if(*it<elem){
            itPrimero = primero.insert(itPrimero,*it);
            itPrimero++;
        }else{
            itSegundo = segundo.insert(itSegundo,*it);
            itSegundo++;
        }
    }
    return std::make_pair(primero,segundo);
}
template <class Contenedor>
void merge(const Contenedor& c1, const Contenedor& c2, Contenedor& res){
    auto it1 = c1.begin();
    auto it2= c2.begin();
    auto it3=res.begin();
    while(it1 != c1.end() || it2 != c2.end()){
        if(*it1 < *it2){
            it3=res.insert(it3,*it1);
            it3++;
            it1++;
        }else{
            it3=res.insert(it3,*it2);
            it3++;
            it2++;
        }
    }
}
#endif //ALGO2_LABO_CLASE5_ALGORITMOS_H
