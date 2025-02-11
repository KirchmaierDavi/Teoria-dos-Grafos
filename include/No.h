#ifndef NO_H
#define NO_H

#include "Aresta.h"

class No {
private:
    int idNo;
    float pesoNo;
    unsigned int grauEntrada;
    unsigned int grauSaida;
    Aresta* primeiraAresta;
    Aresta* ultimaAresta;
    No* proxNo;

public:
    No(int idNo, float pesoNo = 0.0);
    ~No();

    int getIdNo();
    float getPesoNo();
    unsigned int getGrauEntrada();
    unsigned int getGrauSaida();
    Aresta* getPrimeiraAresta();
    No* getProxNo();
    void setProxNo(No* proxNo);

    void adicionaAresta(int destino, float peso = 1.0, bool direcionado = false);
    void removeAresta(int destino);

    void incGrauEntrada();
    void incGrauSaida();

    No* obterNoDestino(int destino);
};

#endif // NO_H