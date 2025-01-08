#include "Aresta.h"

Aresta::Aresta(int origem, int destino, float peso) 
    : origem(origem), destino(destino), peso(peso), proxAresta(nullptr) {}

Aresta::~Aresta() {}

int Aresta::getOrigem() {
    return origem;
}

int Aresta::getDestino() {
    return destino;
}

float Aresta::getPeso() {
    return peso;
}

Aresta* Aresta::getProxAresta() {
    return proxAresta;
}

void Aresta::setProxAresta(Aresta* prox) {
    proxAresta = prox;
}
