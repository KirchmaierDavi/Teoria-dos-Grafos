#ifndef LISTAENCADEADA_H
#define LISTAENCADEADA_H

#include "No.h"

class ListaEncadeada {
public:
    struct NoLista {
        No* no;
        NoLista* proximo;
        NoLista(No* no) : no(no), proximo(nullptr) {}
    };

    NoLista* cabeca;

    ListaEncadeada() : cabeca(nullptr) {}

    void adicionar(No* no) {
        NoLista* novoNo = new NoLista(no);
        novoNo->proximo = cabeca;
        cabeca = novoNo;
    }

    ~ListaEncadeada() {
        while (cabeca) {
            NoLista* temp = cabeca;
            cabeca = cabeca->proximo;
            delete temp;
        }
    }
};

#endif // LISTAENCADEADA_H