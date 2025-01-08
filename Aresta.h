#ifndef ARESTA_H
#define ARESTA_H

class Aresta {
private:
    int origem;
    int destino;
    float peso;
    Aresta* proxAresta;

public:
    Aresta(int origem, int destino, float peso = 1.0);
    ~Aresta();

    int getOrigem();
    int getDestino();
    float getPeso();
    Aresta* getProxAresta();
    void setProxAresta(Aresta* prox);
};

#endif // ARESTA_H
