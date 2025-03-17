#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include "Grafo.h"
#include "Lista.h"
#include "No.h"
#include <string>

/**
 * @class GrafoLista
 * @brief Classe que representa um grafo utilizando uma lista de adjacência.
 *
 * Esta classe herda de Grafo e implementa funcionalidades específicas para manipulação de grafos
 * representados por listas de adjacência, incluindo operações como verificação de propriedades,
 * manipulação de nós e arestas, e algoritmos de cobertura.
 */
class GrafoLista : public Grafo
{
private:
    Lista *listaAdj; ///< Lista de adjacência que armazena as conexões entre os vértices.
    No **nos;        ///< Array de ponteiros para os nós do grafo.
    int numArestas;  ///< Número total de arestas no grafo.

public:
    /**
     * @brief Construtor da classe GrafoLista.
     * @param ordem Número de vértices do grafo.
     * @param direcionado Indica se o grafo é direcionado (true) ou não (false).
     * @param ponderadoVertices Indica se os vértices possuem pesos (true) ou não (false).
     * @param ponderadoArestas Indica se as arestas possuem pesos (true) ou não (false).
     */
    GrafoLista(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas);

    /**
     * @brief Destrutor da classe GrafoLista.
     * Libera a memória alocada para a lista de adjacência.
     */
    ~GrafoLista();

    /**
     * @brief Verifica se o grafo é completo.
     * Um grafo completo possui todas as combinações possíveis de arestas entre seus vértices.
     * @return true se o grafo é completo; caso contrário, false.
     */
    bool ehCompleto() override;

    /**
     * @brief Determina o número de componentes conexos no grafo.
     * Um componente conexo é um subconjunto de vértices onde existe pelo menos um caminho entre cada par de vértices.
     * @return Número de componentes conexos no grafo.
     */
    int nConexo() override;

    /**
     * @brief Verifica se o grafo é uma árvore.
     * Um grafo é uma árvore se for conexo e não possuir ciclos (nós - 1 = número de arestas).
     * @return true se o grafo é uma árvore; caso contrário, false.
     */
    bool ehArvore() override;

    /**
     * @brief Verifica se o grafo possui pontes.
     * Uma ponte é uma aresta cuja remoção aumenta o número de componentes conexos do grafo.
     * @return true se existe pelo menos uma ponte; caso contrário, false.
     */
    bool possuiPonte() override;

    /**
     * @brief Verifica se o grafo possui vértices de articulação.
     * Um vértice de articulação é aquele cuja remoção aumenta o número de componentes conexos do grafo.
     * @return true se existe pelo menos um vértice de articulação; caso contrário, false.
     */
    bool possuiArticulacao() override;

    /**
     * @brief Carrega o grafo a partir de um arquivo.
     * O arquivo deve conter os dados do grafo, como número de nós, tipo de grafo e arestas.
     * @param arquivo Caminho para o arquivo de entrada.
     */
    void carregaGrafo(const std::string &arquivo) override;

    /**
     * @brief Cria um novo grafo a partir de um arquivo de configuração.
     * O arquivo deve conter as informações do grafo, como tipo de estrutura, número de nós e arestas.
     * @param arquivoConfig Caminho para o arquivo de configuração.
     */
    void novoGrafo(const std::string &arquivoConfig) override;

    /**
     * @brief Remove um nó do grafo representado por lista de adjacência.
     * @param idNo ID do nó a ser removido (ajustado para índice zero-based).
     */
    void deleta_no(int idNo) override;

    /**
     * @brief Adiciona um nó ao grafo representado por lista de adjacência.
     * @param idNo ID do nó a ser adicionado.
     */
    void adicionaNo(int idNo) override;

    /**
     * @brief Adiciona uma nova aresta ao grafo.
     * @param origem ID do nó de origem da aresta.
     * @param destino ID do nó de destino da aresta.
     * @param peso Peso da aresta (caso o grafo seja ponderado por arestas).
     *
     * Se o grafo for não direcionado, a aresta é adicionada nos dois sentidos.
     */
    void novaAresta(int origem, int destino, float peso) override;

    /**
     * @brief Remove uma aresta do grafo.
     * @param idNoOrigem ID do nó de origem da aresta.
     * @param idNoDestino ID do nó de destino da aresta.
     * @param direcionado Indica se o grafo é direcionado (true) ou não (false).
     *
     * Se o grafo for não direcionado, a remoção da aresta ocorre nos dois sentidos.
     */
    void removeAresta(int idNoOrigem, int idNoDestino, bool direcionado) override;

    /**
     * @brief Verifica se uma dada cobertura de vértices é válida, ou seja, se cobre todas as arestas do grafo.
     * @param cobertura Array contendo os índices dos vértices que compõem a cobertura.
     * @param tamanhoCobertura Tamanho do array de cobertura (número de vértices na cobertura).
     * @return true se a cobertura for válida (todas as arestas têm pelo menos uma extremidade na cobertura), false caso contrário.
     */
    bool verificarCobertura(int *cobertura, int tamanhoCobertura) override;

    /**
     * @brief Encontra uma cobertura mínima de arestas usando uma abordagem GRASP.
     * @param alpha Parâmetro de controle para a aleatoriedade na fase de construção.
     * @param maxIteracoes Número máximo de iterações do algoritmo.
     * @param tamanhoCobertura Ponteiro para armazenar o tamanho da cobertura encontrada.
     * @return Um array contendo os vértices que fazem parte da cobertura mínima de arestas.
     */
    int *coberturaArestas(float alpha, int maxIteracoes, int *tamanhoCobertura) override;

    /**
     * @brief Implementa um algoritmo guloso para encontrar uma cobertura de vértices.
     * @param tamanhoCobertura Ponteiro para armazenar o tamanho da cobertura encontrada.
     * @return Um array contendo os vértices que fazem parte da cobertura.
     */
    int *construcaoGulosa(int *tamanhoCobertura) override;

    /**
     * @brief Implementa uma variação reativa do algoritmo GRASP para cobertura de arestas.
     * @param maxIteracoes Número máximo de iterações do algoritmo.
     * @param tamanhoListaAlpha Número de valores de alpha testados durante a execução.
     * @param tamanhoCobertura Ponteiro para armazenar o tamanho da melhor cobertura encontrada.
     * @return Um array contendo os vértices da melhor cobertura de arestas encontrada.
     */
    int *coberturaArestasReativa(int maxIteracoes, int tamanhoListaAlpha, int *tamanhoCobertura) override;

private:
    /**
     * @brief Constrói uma solução inicial para o problema de cobertura de arestas usando um método guloso randomizado.
     * @param alpha Parâmetro que controla a aleatoriedade da escolha dos vértices.
     * @param tamanhoCobertura Ponteiro para armazenar o tamanho da cobertura encontrada.
     * @return Um array contendo os vértices da cobertura inicial.
     */
    int *construcaoGulosaRandomizada(float alpha, int *tamanhoCobertura) override;

    /**
     * @brief Realiza uma busca local para melhorar uma solução de cobertura de arestas.
     * @param solucao Array contendo a solução inicial.
     * @param tamanhoSolucao Tamanho da solução inicial.
     * @param tamanhoMelhorSolucao Ponteiro para armazenar o tamanho da solução melhorada.
     * @return Um array contendo a solução melhorada após a busca local.
     */
    int *buscaLocal(int *solucao, int tamanhoSolucao, int *tamanhoMelhorSolucao) override;

    /**
     * @brief Obtém o nó correspondente a um dado ID.
     * @param id ID do nó a ser retornado.
     * @return Ponteiro para o nó correspondente ao ID fornecido.
     */
    No *getNoPeloId(int id) { return nos[id]; }

    /**
     * @brief Implementa um algoritmo guloso para encontrar uma cobertura de vértices.
     * @param tamanhoCobertura Ponteiro para armazenar o tamanho da cobertura encontrada.
     * @return Um array contendo os vértices que fazem parte da cobertura.
     */
    int *algoritmoGuloso(int *tamanhoCobertura);

    /**
     * @brief Calcula e atualiza as probabilidades associadas a uma lista de elementos com base nos valores fornecidos.
     * @param alphas Array contendo os valores de alpha.
     * @param probabilidades Array contendo as probabilidades associadas a cada alpha.
     * @param valores Array contendo os valores obtidos para cada alpha.
     * @param contadores Array contendo o número de vezes que cada alpha foi escolhido.
     * @param tamanhoLista Tamanho das listas de alphas, probabilidades, valores e contadores.
     * @param melhorValor Melhor valor obtido até o momento.
     */
    void atualizaProbabilidades(float *alphas, float *probabilidades,
                                float *valores, int *contadores,
                                int tamanhoLista, float melhorValor) override;
};

#endif