#include "Aresta.h";

Aresta::Aresta(No* noDestino, No* noOrigem, float pesoAresta) : noDestino(noDestino), noOrigem(noOrigem), pesoAresta(pesoAresta), proxAresta(nullptr), direcionado(false) {}

Aresta::~Aresta(){}

int Aresta::getIdDestino() {
    return noDestino->getIdNo();
}

int Aresta::getIdOrigem() {
    return noOrigem->getIdNo();
}

float Aresta::getPesoAresta() {
    return pesoAresta;
}

void Aresta::setPesoAresta(float pesoAresta) {
    this->pesoAresta = pesoAresta;
}

void Aresta::setNoDestino(No *valor) {
    this->noDestino = valor;
}

void Aresta::setProxAresta(Aresta *proxAresta) {
    this->proxAresta = proxAresta;
}