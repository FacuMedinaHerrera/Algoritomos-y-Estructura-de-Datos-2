//
// Created by facu on 09/11/22.
//
#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP
template <class T>
T cuadrado(T x){
    return x*x;
}
template<class Contenedor, class Elem>
bool contiene(Contenedor s, Elem c) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            return true;
        }
    }
    return false;
}
template <class Contenedor>
bool esPrefijo (Contenedor a, Contenedor b){
    bool res = true;
    auto it = b.begin();
    auto it2 = a.begin();
    if (a.size()>b.size())return false;
    while (it != b.end() && res && it2 != a.end()){
        if (*it2 != *it)res= false;
        it++;
        it2++;
    }
    return res;
}

#endif
