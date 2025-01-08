#ifndef LISTA_H
#define LISTA_H

#include "No.h"

class Lista {
private:
    No* cabeca;
    int tamanho;

public:
    Lista();
    ~Lista();

    void adicionar(int idNo, float pesoNo = 0.0);
    void remover(int idNo);
    bool contem(int idNo);
    int getTamanho();
    No* getElemento(int indice);
};

#endif // LISTA_H