#ifndef LISTA_H
#define LISTA_H

#include "No.h"

class Lista
{
private:
    No *cabeca;
    int tamanho;

public:
    Lista();
    ~Lista();

    Lista &operator=(const Lista &other)
    {
        if (this != &other)
        {
            // Clear current list
            while (cabeca != nullptr)
            {
                No *temp = cabeca;
                cabeca = cabeca->getProxNo();
                delete temp;
            }

            // Copy from other list
            No *current = other.cabeca;
            while (current != nullptr)
            {
                adicionar(current->getIdNo());
                current = current->getProxNo();
            }
        }
        return *this;
    }

    void adicionar(int id, float peso = 0.0);
    void remover(int id);
    bool contem(int id) const;
    No *getElemento(int posicao) const;
    int getTamanho() const;
};
#endif