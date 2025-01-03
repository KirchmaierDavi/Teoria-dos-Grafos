#ifndef NO_H
#define NO_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include "Aresta.h"

using namespace std;
class Aresta;

class No {

private:
    int idNo;
    float pesoNo;
    unsigned int grauEntrada;
    unsigned int grauSaida;
    int numArestas;
    No *proxNo;
    Aresta *primeiraAresta;
    Aresta *ultimaAresta;
    bool visitado;

public:
    No(int idNo);
    ~No();

    Aresta* getPrimeiraAresta();
    Aresta* getUltimaAresta();

    int getNumArestas();
    void setPrimeiraAresta(Aresta *novaAresta);


    No* getProxNo();

    int getIdNo();

    int getPeso();

    int getGrauEntrada();

    int getGrauSaida();

    void setProxNo(No *novoNo);
    
    void incGrauEntrada();
    void incGrauSaida();

    void incGrau(bool direcionado);

    
    void setPeso(float valor);
    void setIdNo(int valor);

    bool foiVisitado();
    void desmarcarVisitado();
    void marcarVisitado();

};

#endif // NO_H