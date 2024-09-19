#ifndef SISTEMADEMENSAJES_H
#define SISTEMADEMENSAJES_H

#include "ConexionJugador.h"
#include <string>
#include <vector>

#if EJ >= 3 && EJ <= 5
#include "Proxy.h"
#elif EJ == 6
#include "Proxy2.h"
#endif

using namespace std;

class SistemaDeMensajes {
  public:
    SistemaDeMensajes();
    ~SistemaDeMensajes();
    // Pre: 0 <= id < 4
    void registrarJugador(int id, string ip);
    // Pre: 0 <= id < 4
    bool registrado(int id) const;
    // Pre: registrado(id)
    void enviarMensaje(int id, string mensaje);
    // Pre: registrado(id)
    string ipJugador(int id) const;
    void desregistrarJugador(int id);
    Proxy* obtenerProxy(int id);


  private:
    ConexionJugador* _conns[4];
    vector<Proxy*> _prox;
    // _conns es un arreglo de punteros a ConexionJugador de long 4
};

#endif
