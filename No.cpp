/**
 * @file No.cpp
 * @brief Implementação das funções da classe No.
 */
#include "No.h"
#include "Aresta.h"

/**
 * @brief Construtor da classe No.
 * 
 * Este construtor inicializa um nó com o ID, peso, e valores iniciais para os graus de entrada e saída, além de inicializar os ponteiros para as arestas e o próximo nó.
 * 
 * @param idNo O ID do nó.
 * @param pesoNo O peso do nó.
 */
No::No(int idNo, float pesoNo) 
    : idNo(idNo), pesoNo(pesoNo), grauEntrada(0), grauSaida(0), 
      primeiraAresta(nullptr), ultimaAresta(nullptr), proxNo(nullptr) {}

/**
 * @brief Destrutor da classe No.
 * 
 * O destrutor percorre a lista de arestas associadas ao nó e as libera corretamente.
 */
No::~No() {
    Aresta* arestaAtual = primeiraAresta;
    while (arestaAtual != nullptr) {
        Aresta* proxAresta = arestaAtual->getProxAresta();
        delete arestaAtual;
        arestaAtual = proxAresta;
    }
}

/**
 * @brief Obtém o ID do nó.
 * 
 * Este método retorna o ID do nó.
 * 
 * @return O ID do nó.
 */
int No::getIdNo() {
    return idNo;
}

/**
 * @brief Obtém o peso do nó.
 * 
 * Este método retorna o peso associado ao nó.
 * 
 * @return O peso do nó.
 */
float No::getPesoNo() {
    return pesoNo;
}

/**
 * @brief Obtém o grau de entrada do nó.
 * 
 * Este método retorna o número de arestas que entram no nó.
 * 
 * @return O grau de entrada do nó.
 */
unsigned int No::getGrauEntrada() {
    return grauEntrada;
}

/**
 * @brief Obtém o grau de saída do nó.
 * 
 * Este método retorna o número de arestas que saem do nó.
 * 
 * @return O grau de saída do nó.
 */
unsigned int No::getGrauSaida() {
    return grauSaida;
}

/**
 * @brief Obtém a primeira aresta associada ao nó.
 * 
 * Este método retorna o ponteiro para a primeira aresta do nó.
 * 
 * @return Ponteiro para a primeira aresta do nó.
 */
Aresta* No::getPrimeiraAresta() {
    return primeiraAresta;
}

/**
 * @brief Obtém o próximo nó na lista de nós.
 * 
 * Este método retorna o ponteiro para o próximo nó.
 * 
 * @return Ponteiro para o próximo nó.
 */
No* No::getProxNo() {
    return proxNo;
}

/**
 * @brief Define o próximo nó na lista de nós.
 * 
 * Este método define o próximo nó ao qual o nó atual está apontando.
 * 
 * @param proxNo Ponteiro para o próximo nó.
 */
void No::setProxNo(No* proxNo) {
    this->proxNo = proxNo;
}

/**
 * @brief Adiciona uma aresta ao nó.
 * 
 * Este método cria uma nova aresta com o nó de origem e destino, e o peso atribuído. A aresta é adicionada à lista de arestas do nó.
 * Caso o grafo não seja direcionado, o grau de entrada também é atualizado.
 * 
 * @param destino O ID do nó de destino da aresta.
 * @param peso O peso da aresta.
 * @param direcionado Se a aresta é direcionada ou não.
 */
void No::adicionaAresta(int destino, float peso, bool direcionado) {
    No* destinoNo = obterNoDestino(destino);  // Obtém o ponteiro do nó de destino

    // Criação da nova aresta com os ponteiros para os nós
    Aresta* novaAresta = new Aresta(this, destinoNo, peso);  // Passa os ponteiros para Aresta

    if (ultimaAresta != nullptr) {
        ultimaAresta->setProxAresta(novaAresta);
    } else {
        primeiraAresta = novaAresta;
    }
    ultimaAresta = novaAresta;

    // Atualiza graus
    this->grauSaida++;
    if (!direcionado) {
        this->grauEntrada++;
    }
}

/**
 * @brief Incrementa o grau de entrada do nó.
 * 
 * Este método incrementa o grau de entrada do nó em 1.
 */
void No::incGrauEntrada() {
    this->grauEntrada++;
}

/**
 * @brief Incrementa o grau de saída do nó.
 * 
 * Este método incrementa o grau de saída do nó em 1.
 */
void No::incGrauSaida() {
    this->grauSaida++;
}

/**
 * @brief Obtém o ponteiro para o nó de destino.
 * 
 * Este método deve retornar o ponteiro para o nó de destino a partir do ID fornecido.
 * 
 * @param destino O ID do nó de destino.
 * @return Ponteiro para o nó de destino.
 */
No* No::obterNoDestino(int destino) {
    // Este método pode ser implementado para buscar o nó de destino a partir do ID
    // Dependendo da sua estrutura de grafo, você pode buscar na lista de nós
    // Exemplo de código fictício:
    // return grafo->getNoById(destino);
    
    return nullptr;  // Substitua conforme a lógica do seu grafo
}