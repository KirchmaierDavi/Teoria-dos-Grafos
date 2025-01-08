#include "No.h"

No::No(int idNo, float pesoNo) 
    : idNo(idNo), pesoNo(pesoNo), grauEntrada(0), grauSaida(0), 
      primeiraAresta(nullptr), ultimaAresta(nullptr), proxNo(nullptr) {}

No::~No() {
    Aresta* arestaAtual = primeiraAresta;
    while (arestaAtual != nullptr) {
        Aresta* proxAresta = arestaAtual->getProxAresta();
        delete arestaAtual;
        arestaAtual = proxAresta;
    }
}

int No::getIdNo() {
    return idNo;
}

float No::getPesoNo() {
    return pesoNo;
}

unsigned int No::getGrauEntrada() {
    return grauEntrada;
}

unsigned int No::getGrauSaida() {
    return grauSaida;
}

Aresta* No::getPrimeiraAresta() {
    return primeiraAresta;
}

No* No::getProxNo() {
    return proxNo;
}

void No::setProxNo(No* proxNo) {
    this->proxNo = proxNo;
}

void No::adicionaAresta(int destino, float peso, bool direcionado) {
    Aresta* novaAresta = new Aresta(this->idNo, destino, peso);
    if (ultimaAresta != nullptr) {
        ultimaAresta->setProxAresta(novaAresta);
    } else {
        primeiraAresta = novaAresta;
    }
    ultimaAresta = novaAresta;

    // Atualiza graus
    this->grauSaida++;
    if (!direcionado) {
        this->grauEntrada++;
    }
}

void No::incGrauEntrada() {
    this->grauEntrada++;
}

void No::incGrauSaida() {
    this->grauSaida++;
}
