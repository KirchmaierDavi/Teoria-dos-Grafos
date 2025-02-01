#ifndef ARESTA_H
#define ARESTA_H

//#include "No.h"
class No; 

class Aresta {
private:
    No* origem;
    No* destino;
    float peso;
    Aresta* proxAresta;

public:
    Aresta(No* origem, No* destino, float peso = 1.0);
    ~Aresta();

    int getIdDestino();
    int getIdOrigem();
    void setNoOrigem(No* no);
    void setNoDestino(No* no); 
    float getPeso();
    Aresta* getProxAresta();
    void setProxAresta(Aresta* prox);
};

#endif // ARESTA_H