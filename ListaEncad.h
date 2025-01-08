#ifndef LISTA_H
#define LISTA_H

class Lista {
private:
    int* data;
    int capacidade;
    int tamanho;

public:
    Lista(int capacidadeInicial = 10);
    ~Lista();

    void adicionar(int valor);
    void remover(int valor);
    bool contem(int valor);
    int getTamanho();
};

#endif // LISTA_H