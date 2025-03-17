#ifndef ARESTA_H
#define ARESTA_H

class No; // Declaração antecipada para evitar dependência circular

/**
 * @class Aresta
 * @brief Classe que representa uma aresta em um grafo.
 * 
 * Esta classe armazena informações sobre uma aresta, incluindo os nós de origem e destino,
 * o peso da aresta e um ponteiro para a próxima aresta em uma lista encadeada.
 */
class Aresta {
private:
    No* origem;         ///< Ponteiro para o nó de origem da aresta.
    No* destino;        ///< Ponteiro para o nó de destino da aresta.
    float peso;         ///< Peso da aresta.
    Aresta* proxAresta; ///< Ponteiro para a próxima aresta na lista.

public:
    /**
     * @brief Construtor da classe Aresta.
     * 
     * Inicializa uma aresta com os nós de origem e destino, o peso da aresta e o ponteiro para a próxima aresta.
     * @param origem Ponteiro para o nó de origem da aresta.
     * @param destino Ponteiro para o nó de destino da aresta.
     * @param peso O peso da aresta (padrão 1.0).
     */
    Aresta(No* origem, No* destino, float peso = 1.0);

    /**
     * @brief Destrutor da classe Aresta.
     * 
     * O destrutor é vazio, pois a liberação de memória dos nós (origem e destino) deve ser tratada em outra parte do código.
     */
    ~Aresta();

    /**
     * @brief Obtém o ID do nó de origem da aresta.
     * @return O ID do nó de origem.
     */
    int getIdOrigem();

    /**
     * @brief Obtém o ID do nó de destino da aresta.
     * @return O ID do nó de destino.
     */
    int getIdDestino();

    /**
     * @brief Define o nó de origem da aresta.
     * @param no Ponteiro para o nó de origem.
     */
    void setNoOrigem(No* no);

    /**
     * @brief Define o nó de destino da aresta.
     * @param no Ponteiro para o nó de destino.
     */
    void setNoDestino(No* no);

    /**
     * @brief Obtém o peso da aresta.
     * @return O peso da aresta.
     */
    float getPeso();

    /**
     * @brief Obtém a próxima aresta.
     * @return Ponteiro para a próxima aresta na lista.
     */
    Aresta* getProxAresta();

    /**
     * @brief Define a próxima aresta.
     * @param prox Ponteiro para a próxima aresta a ser associada.
     */
    void setProxAresta(Aresta* prox);
};

#endif // ARESTA_H