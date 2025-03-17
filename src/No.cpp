/**
 * @file No.cpp
 * @brief Implementação das funções da classe No.
 */
#include "../include/No.h"
#include "../include/Aresta.h"
#include <iostream>

using namespace std;

No::No(int idNo, float pesoNo)
    : idNo(idNo), pesoNo(pesoNo), grauEntrada(0), grauSaida(0),
      primeiraAresta(nullptr), ultimaAresta(nullptr), proxNo(nullptr) {}

No::~No()
{
    Aresta *arestaAtual = primeiraAresta;
    while (arestaAtual != nullptr)
    {
        Aresta *proxAresta = arestaAtual->getProxAresta();
        delete arestaAtual;
        arestaAtual = proxAresta;
    }
}

int No::getIdNo()
{
    return idNo;
}

float No::getPesoNo()
{
    return pesoNo;
}

unsigned int No::getGrauEntrada()
{
    return grauEntrada;
}

unsigned int No::getGrauSaida()
{
    return grauSaida;
}

Aresta *No::getPrimeiraAresta()
{
    return primeiraAresta;
}

No *No::getProxNo()
{
    return proxNo;
}

void No::setProxNo(No *proxNo)
{
    this->proxNo = proxNo;
}

void No::adicionaAresta(int destino, float peso, bool direcionado)
{
    No *destinoNo = obterNoDestino(destino); // Obtém o ponteiro do nó de destino

    // Criação da nova aresta com os ponteiros para os nós
    Aresta *novaAresta = new Aresta(this, destinoNo, peso); // Passa os ponteiros para Aresta

    if (ultimaAresta != nullptr)
    {
        ultimaAresta->setProxAresta(novaAresta);
    }
    else
    {
        primeiraAresta = novaAresta;
    }
    ultimaAresta = novaAresta;

    // Atualiza graus
    this->grauSaida++;
    if (!direcionado)
    {
        this->grauEntrada++;
    }
}

void No::removeAresta(int destino, bool direcionado)
{
    if (this->primeiraAresta == nullptr)
    {
        std::cout << "Nó sem arestas";
        return;
    }

    Aresta *atual = this->primeiraAresta;
    Aresta *anterior = nullptr;

    while (atual != nullptr && atual->getIdDestino() != destino)
    {
        anterior = atual;
        atual = atual->getProxAresta();
    }

    if (atual != nullptr)
    {
        if (anterior == nullptr)
        {
            this->primeiraAresta = atual->getProxAresta();
        }
        else
        {
            anterior->setProxAresta(atual->getProxAresta());
        }

        if (atual == this->ultimaAresta)
        {
            this->ultimaAresta = anterior;
        }

        atual->setProxAresta(nullptr);
        atual->setNoOrigem(nullptr);
        atual->setNoDestino(nullptr);

        delete atual;

        this->grauSaida--;
        if (!direcionado)
        {
            this->grauEntrada--;
        }
    }
}

void No::incGrauEntrada()
{
    this->grauEntrada++;
}

void No::incGrauSaida()
{
    this->grauSaida++;
}

No *No::obterNoDestino(int destino)
{
    // Este método pode ser implementado para buscar o nó de destino a partir do ID
    // Dependendo da sua estrutura de grafo, você pode buscar na lista de nós
    // Exemplo de código fictício:
    // return grafo->getNoById(destino);
    
    return nullptr;  // Substitua conforme a lógica do seu grafo
}

void No::setIDNo(int idNo) {
    this->idNo = idNo;
}