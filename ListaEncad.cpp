#include "ListaEncad.h"
#include <iostream>

Lista::Lista() : cabeca(nullptr), tamanho(0) {}

Lista::~Lista() {
    No* atual = cabeca;
    while (atual != nullptr) {
        No* prox = atual->getProxNo();
        delete atual;
        atual = prox;
    }
}

void Lista::adicionar(int idNo, float pesoNo) {
    No* novoNo = new No(idNo, pesoNo);
    novoNo->setProxNo(cabeca);
    cabeca = novoNo;
    tamanho++;
}

void Lista::remover(int idNo) {
    No* atual = cabeca;
    No* anterior = nullptr;

    while (atual != nullptr && atual->getIdNo() != idNo) {
        anterior = atual;
        atual = atual->getProxNo();
    }

    if (atual != nullptr) {
        if (anterior == nullptr) {
            cabeca = atual->getProxNo();
        } else {
            anterior->setProxNo(atual->getProxNo());
        }
        delete atual;
        tamanho--;
    }
}

bool Lista::contem(int idNo) {
    No* atual = cabeca;
    while (atual != nullptr) {
        if (atual->getIdNo() == idNo) {
            return true;
        }
        atual = atual->getProxNo();
    }
    return false;
}

int Lista::getTamanho() {
    return tamanho;
}

No* Lista::getElemento(int indice) {
    if (indice < 0 || indice >= tamanho) {
        std::cout<< "Indice fora dos limites da lista";
        return nullptr;
    }

    No* atual = cabeca;
    for (int i = 0; i < indice; ++i) {
        atual = atual->getProxNo();
    }
    return atual;
}