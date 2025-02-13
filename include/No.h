#ifndef NO_H
#define NO_H

#include "Aresta.h"

// Ajuste de nomenclatura e agrupamento de atributos
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

    void adicionaAresta(int destino, float peso = 1.0, bool direcionado);
    void removeAresta(int destino, bool direcionado);

    void incGrauEntrada();
    void incGrauSaida();

    No* obterNoDestino(int destino);
    void setIDNo(int idNo);
};

#endif // NO_H