/**
 * @file Aresta.cpp
 * @brief Implementação das funções da classe Aresta.
 */

#include "../include/Aresta.h"
#include "../include/No.h"

/**
 * @brief Construtor da classe Aresta.
 * 
 * Este construtor inicializa uma aresta com os nós de origem e destino, o peso da aresta e o ponteiro para a próxima aresta.
 * 
 * @param origem Ponteiro para o nó de origem da aresta.
 * @param destino Ponteiro para o nó de destino da aresta.
 * @param peso O peso da aresta.
 */
Aresta::Aresta(No* origem, No* destino, float peso) 
    : origem(origem), destino(destino), peso(peso), proxAresta(nullptr) {}

/**
 * @brief Destrutor da classe Aresta.
 * 
 * O destrutor da classe Aresta é vazio, pois a liberação de memória dos nós (origem e destino) deve ser tratada em outra parte do código.
 */
Aresta::~Aresta() {}

/**
 * @brief Obtém o ID do nó de origem da aresta.
 * 
 * Este método retorna o ID do nó de origem da aresta.
 * 
 * @return O ID do nó de origem.
 */
int Aresta::getIdOrigem() {
    return origem->getIdNo();
}

/**
 * @brief Obtém o ID do nó de destino da aresta.
 * 
 * Este método retorna o ID do nó de destino da aresta.
 * 
 * @return O ID do nó de destino.
 */
int Aresta::getIdDestino() {
    return destino->getIdNo();
}

/**
 * @brief Obtém o peso da aresta.
 * 
 * Este método retorna o peso atribuído à aresta.
 * 
 * @return O peso da aresta.
 */
float Aresta::getPeso() {
    return peso;
}

/**
 * @brief Obtém a próxima aresta.
 * 
 * Este método retorna o ponteiro para a próxima aresta na lista.
 * 
 * @return Ponteiro para a próxima aresta.
 */
Aresta* Aresta::getProxAresta() {
    return proxAresta;
}

/**
 * @brief Define a próxima aresta.
 * 
 * Este método define a próxima aresta na lista de arestas.
 * 
 * @param prox Ponteiro para a próxima aresta a ser associada.
 */
void Aresta::setProxAresta(Aresta* prox) {
    proxAresta = prox;
}

/**
 * @brief Define o nó de destino da aresta.
 * 
 * Este método define o nó de destino da aresta.
 * 
 * @param valor Ponteiro para o nó de destino.
 */
void Aresta::setNoDestino(No *valor) {
    this->destino = valor;
}

/**
 * @brief Define o nó de origem da aresta.
 * 
 * Este método define o nó de origem da aresta.
 * 
 * @param valor Ponteiro para o nó de origem.
 */
void Aresta::setNoOrigem(No *valor) {
    this->origem = valor;
}
