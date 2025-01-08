#include "ListaEncad.h"

Lista::Lista(int capacidadeInicial) : capacidade(capacidadeInicial), tamanho(0) {
    data = new int[capacidade];
}

Lista::~Lista() {
    delete[] data;
}

void Lista::adicionar(int valor) {
    if (tamanho == capacidade) {
        capacidade *= 2;
        int* novoData = new int[capacidade];
        for (int i = 0; i < tamanho; ++i) {
            novoData[i] = data[i];
        }
        delete[] data;
        data = novoData;
    }
    data[tamanho++] = valor;
}

void Lista::remover(int valor) {
    for (int i = 0; i < tamanho; ++i) {
        if (data[i] == valor) {
            data[i] = data[--tamanho];
            return;
        }
    }
}

bool Lista::contem(int valor) {
    for (int i = 0; i < tamanho; ++i) {
        if (data[i] == valor) {
            return true;
        }
    }
    return false;
}

int Lista::getTamanho() {
    return tamanho;
}
