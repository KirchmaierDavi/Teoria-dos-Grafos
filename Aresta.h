#ifndef ARESTA_H
#define ARESTA_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include "No.h"

using namespace std;

class No;

class Aresta {

private:
    float pesoAresta;
    int noDestino;
    int noOrigem;
    Aresta *proxAresta;
    bool direcionado;


public:
   
    Aresta(int noDestino, int noOrigem, float pesoAresta);
     ~Aresta();

    float getPesoAresta();
    int getIdDestino();
    int getIdOrigem();

    void setPesoAresta(float pesoAresta);
    void setNoDestino(No *valor);

    Aresta* getProxAresta();
    void setProxAresta(Aresta *proxAresta);
    
    bool ehDirecionado();
    void setDirecionado(bool direcionado);

};

#endif // ARESTA_H