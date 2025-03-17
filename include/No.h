#ifndef NO_H
#define NO_H

#include "Aresta.h"

/**
 * @class No
 * @brief Classe que representa um nó (vértice) em um grafo.
 * 
 * Esta classe armazena informações sobre um nó, incluindo seu ID, peso, graus de entrada e saída,
 * além de uma lista de arestas associadas e um ponteiro para o próximo nó na estrutura do grafo.
 */
class No
{
private:
    int idNo;               ///< Identificador único do nó.
    float pesoNo;           ///< Peso associado ao nó.
    unsigned int grauEntrada; ///< Número de arestas que entram no nó.
    unsigned int grauSaida;   ///< Número de arestas que saem do nó.
    Aresta *primeiraAresta; ///< Ponteiro para a primeira aresta associada ao nó.
    Aresta *ultimaAresta;   ///< Ponteiro para a última aresta associada ao nó.
    No *proxNo;             ///< Ponteiro para o próximo nó na lista de nós.

public:
    /**
     * @brief Construtor da classe No.
     * 
     * Inicializa um nó com o ID, peso, e valores iniciais para os graus de entrada e saída,
     * além de inicializar os ponteiros para as arestas e o próximo nó.
     * @param idNo O ID do nó.
     * @param pesoNo O peso do nó (padrão 0.0).
     */
    No(int idNo, float pesoNo = 0.0);

    /**
     * @brief Destrutor da classe No.
     * 
     * Percorre a lista de arestas associadas ao nó e as libera corretamente.
     */
    ~No();

    /**
     * @brief Obtém o ID do nó.
     * @return O ID do nó.
     */
    int getIdNo();

    /**
     * @brief Obtém o peso do nó.
     * @return O peso do nó.
     */
    float getPesoNo();

    /**
     * @brief Obtém o grau de entrada do nó.
     * @return O grau de entrada do nó.
     */
    unsigned int getGrauEntrada();

    /**
     * @brief Obtém o grau de saída do nó.
     * @return O grau de saída do nó.
     */
    unsigned int getGrauSaida();

    /**
     * @brief Obtém a primeira aresta associada ao nó.
     * @return Ponteiro para a primeira aresta do nó.
     */
    Aresta *getPrimeiraAresta();

    /**
     * @brief Obtém o próximo nó na lista de nós.
     * @return Ponteiro para o próximo nó.
     */
    No *getProxNo();

    /**
     * @brief Define o próximo nó na lista de nós.
     * @param proxNo Ponteiro para o próximo nó.
     */
    void setProxNo(No *proxNo);

    /**
     * @brief Adiciona uma aresta ao nó.
     * 
     * Cria uma nova aresta com o nó de origem e destino, e o peso atribuído.
     * A aresta é adicionada à lista de arestas do nó.
     * @param destino O ID do nó de destino da aresta.
     * @param peso O peso da aresta (padrão 1.0).
     * @param direcionado Indica se a aresta é direcionada (true) ou não (false).
     */
    void adicionaAresta(int destino, float peso = 1.0, bool direcionado = false);

    /**
     * @brief Remove uma aresta do nó.
     * 
     * Remove a aresta que aponta para o nó de destino especificado.
     * @param destino O ID do nó de destino da aresta a ser removida.
     * @param direcionado Indica se o grafo é direcionado (true) ou não (false).
     */
    void removeAresta(int destino, bool direcionado);

    /**
     * @brief Incrementa o grau de entrada do nó.
     */
    void incGrauEntrada();

    /**
     * @brief Incrementa o grau de saída do nó.
     */
    void incGrauSaida();

    /**
     * @brief Obtém o ponteiro para o nó de destino.
     * @param destino O ID do nó de destino.
     * @return Ponteiro para o nó de destino.
     */
    No *obterNoDestino(int destino);

    /**
     * @brief Define o ID do nó.
     * @param idNo Novo ID a ser atribuído ao nó.
     */
    void setIDNo(int idNo);
};

#endif // NO_H