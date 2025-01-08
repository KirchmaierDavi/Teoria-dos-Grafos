#include "Aresta.h"
#include "No.h"

Aresta::Aresta(No* origem, No* destino, float peso) 
    : origem(origem), destino(destino), peso(peso), proxAresta(nullptr) {}

Aresta::~Aresta() {}

int Aresta::getIdOrigem() {
    return origem->getIdNo();
}

int Aresta::getIdDestino() {
    return destino->getIdNo();
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

void Aresta::setNoDestino(No *valor) {
    this->destino = valor;
}

void Aresta::setNoOrigem(No *valor) {
    this->origem = valor;
}
