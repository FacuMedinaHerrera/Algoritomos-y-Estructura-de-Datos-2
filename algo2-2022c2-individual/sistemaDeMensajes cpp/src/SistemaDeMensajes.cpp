#include "SistemaDeMensajes.h"

// Completar...

SistemaDeMensajes::SistemaDeMensajes(){
    for(int i = 0; i<4; i++){
        _conns[i] = nullptr;
    }
}

void SistemaDeMensajes::registrarJugador(int id, std::string ip) {
    if (registrado(id)) {
        desregistrarJugador(id);
        registrarJugador(id,ip);
    }else {
        _conns[id] = new ConexionJugador(ip);

    }
}

void SistemaDeMensajes::enviarMensaje(int id, std::string mensaje) {
    (*_conns[id]).enviarMensaje(mensaje);
}

bool SistemaDeMensajes::registrado(int id) const {
    return _conns[id] != nullptr;
}

string SistemaDeMensajes::ipJugador(int id) const {
    return (*_conns[id]).ip();
}
void SistemaDeMensajes::desregistrarJugador(int id){
   delete _conns[id];
    _conns[id]= nullptr;
}
SistemaDeMensajes::~SistemaDeMensajes(){
    for(int i=0;i<4;i++) {
        delete _conns[i];
    }
    for(Proxy* p:_prox){
        delete p;
    }

}
Proxy* SistemaDeMensajes::obtenerProxy(int id) {
    ConexionJugador** conn = new ConexionJugador* (_conns[id]);
    Proxy* jugador = new Proxy(conn);
    _prox.push_back(jugador);
    return jugador;
}

