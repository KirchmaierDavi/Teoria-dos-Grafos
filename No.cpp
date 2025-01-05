#include "No.h"

No::No(int idNo) : idNo(idNo), primeiraAresta(nullptr), ultimaAresta(nullptr), proxNo(nullptr) {}

No::~No()
{
    Aresta *aresta = primeiraAresta;
    while (aresta != nullptr)
    {
        Aresta *proxAresta = aresta->getProxAresta();
        delete aresta;
        aresta = proxAresta;
    }
}

void No::incGrau(bool direcionado)
{
    if (direcionado)
    {
        this->grauSaida++;
    }
    else
    {
        this->grauEntrada++;
        this->grauSaida++;
    }
}

int No::getIdNo()
{
    return idNo;
}

No *No::getProxNo()
{
    return proxNo;
}

void No::setProxNo(No *proxNo)
{
    this->proxNo = proxNo;
}

Aresta *No::getPrimeiraAresta()
{
    return primeiraAresta;
}