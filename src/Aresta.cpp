/**
 * @file Aresta.cpp
 * @brief Implementação das funções da classe Aresta.
 */

#include "../include/Aresta.h"
#include "../include/No.h"
#include <iostream>
using namespace std;

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
