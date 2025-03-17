#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include "Grafo.h"
#include "No.h"

/**
 * @class GrafoMatriz
 * @brief Classe que representa um grafo utilizando uma matriz de adjacência.
 * 
 * Esta classe herda de Grafo e implementa funcionalidades específicas para manipulação de grafos
 * representados por matrizes de adjacência, incluindo operações como verificação de propriedades,
 * manipulação de nós e arestas, e algoritmos de cobertura.
 */
class GrafoMatriz : public Grafo
{
private:
    int **matrizAdj;        ///< Matriz de adjacência que armazena as conexões entre os vértices.
    No **nos;               ///< Array de ponteiros para os nós do grafo.
    int capacidade;         ///< Capacidade máxima da matriz de adjacência.

    /**
     * @brief Implementa uma construção gulosa randomizada para encontrar uma cobertura de vértices.
     * @param alpha Fator de aleatoriedade que controla a escolha de candidatos (entre 0 e 1).
     * @param tamanhoCobertura Ponteiro para armazenar o tamanho da cobertura encontrada.
     * @return Um array contendo os vértices que fazem parte da cobertura construída.
     */
    int *construcaoGulosaRandomizada(float alpha, int *tamanhoCobertura) override;

    /**
     * @brief Realiza uma busca local para melhorar uma solução inicial de cobertura de vértices.
     * @param solucao Solução inicial a ser melhorada.
     * @param tamanhoSolucao Tamanho da solução inicial.
     * @param tamanhoMelhorSolucao Ponteiro para armazenar o tamanho da solução melhorada.
     * @return Um array contendo os vértices da solução melhorada após a busca local.
     */
    int *buscaLocal(int *solucao, int tamanhoSolucao, int *tamanhoMelhorSolucao) override;

    /**
     * @brief Verifica se uma dada cobertura de vértices é válida, ou seja, se cobre todas as arestas do grafo.
     * @param cobertura Array contendo os índices dos vértices que compõem a cobertura.
     * @param tamanhoCobertura Tamanho do array de cobertura (número de vértices na cobertura).
     * @return true se a cobertura for válida (todas as arestas têm pelo menos uma extremidade na cobertura), false caso contrário.
     */
    bool verificarCobertura(int *cobertura, int tamanhoCobertura) override;

    /**
     * @brief Implementa um algoritmo guloso para encontrar uma cobertura de vértices.
     * @param tamanhoCobertura Ponteiro para armazenar o tamanho da cobertura encontrada.
     * @return Um array contendo os vértices que fazem parte da cobertura.
     */
    int *construcaoGulosa(int *tamanhoCobertura) override;

    /**
     * @brief Atualiza as probabilidades de escolha dos valores de alpha no algoritmo GRASP reativo.
     * @param alphas Array com os valores de alpha disponíveis.
     * @param probabilidades Array com as probabilidades associadas a cada alpha (atualizado pela função).
     * @param valores Array com os valores acumulados de qualidade para cada alpha.
     * @param contadores Array com o número de vezes que cada alpha foi utilizado.
     * @param tamanhoLista Tamanho da lista de alphas.
     * @param melhorValor Melhor valor encontrado para normalização das probabilidades.
     */
    void atualizaProbabilidades(float *alphas, float *probabilidades,
                                float *valores, int *contadores,
                                int tamanhoLista, float melhorValor) override;

public:
    /**
     * @brief Construtor da classe GrafoMatriz.
     * @param ordem Número de vértices do grafo.
     * @param direcionado Indica se o grafo é direcionado (true) ou não (false).
     * @param ponderadoVertices Indica se os vértices possuem pesos (true) ou não (false).
     * @param ponderadoArestas Indica se as arestas possuem pesos (true) ou não (false).
     */
    GrafoMatriz(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas);

    /**
     * @brief Destrutor da classe GrafoMatriz.
     * Libera a memória alocada para o grafo de matriz de adjacência.
     */
    virtual ~GrafoMatriz();

    /**
     * @brief Remove um nó do grafo representado por matriz de adjacência.
     * @param idNo ID do nó a ser removido.
     */
    void deleta_no(int idNo) override;

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
     * Uma árvore é um grafo conexo sem ciclos.
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
     * @brief Remove uma aresta do grafo.
     * @param idNoOrigem ID do nó de origem da aresta.
     * @param idNoDestino ID do nó de destino da aresta.
     * @param direcionado Indica se o grafo é direcionado (true) ou não (false).
     * 
     * Se o grafo for não direcionado, a remoção da aresta ocorre nos dois sentidos.
     * @note Se a aresta não existir, uma mensagem informativa será exibida.
     */
    void removeAresta(int idNoOrigem, int idNoDestino, bool direcionado) override;

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
     * @brief Adiciona um nó ao grafo representado por matriz de adjacência.
     * @param idNo ID do nó a ser adicionado.
     */
    void adicionaNo(int idNo) override;

    /**
     * @brief Adiciona uma nova aresta ao grafo.
     * @param origem ID do nó de origem.
     * @param destino ID do nó de destino.
     * @param peso Peso da aresta (usado apenas se o grafo for ponderado).
     * 
     * Se o grafo for não direcionado, a aresta é adicionada em ambos os sentidos.
     * @note A função verifica se os índices dos nós são válidos e impede a criação de laços.
     */
    void novaAresta(int origem, int destino, float peso) override;

    /**
     * @brief Implementa um algoritmo GRASP (Greedy Randomized Adaptive Search Procedure) para encontrar uma cobertura de arestas.
     * @param alpha Fator de aleatoriedade para a construção gulosa randomizada (entre 0 e 1).
     * @param maxIteracoes Número máximo de iterações do algoritmo.
     * @param tamanhoCobertura Ponteiro para armazenar o tamanho da cobertura encontrada.
     * @return Um array contendo os vértices que fazem parte da melhor cobertura encontrada.
     */
    int *coberturaArestas(float alpha, int maxIteracoes, int *tamanhoCobertura) override;

    /**
     * @brief Implementa um algoritmo GRASP reativo para encontrar uma cobertura de arestas, ajustando dinamicamente os valores de alpha.
     * @param maxIteracoes Número máximo de iterações do algoritmo.
     * @param tamanhoListaAlpha Tamanho da lista de valores de alpha a serem testados.
     * @param tamanhoCobertura Ponteiro para armazenar o tamanho da cobertura encontrada.
     * @return Um array contendo os vértices que fazem parte da melhor cobertura encontrada.
     */
    int *coberturaArestasReativa(int maxIteracoes, int tamanhoListaAlpha, int *tamanhoCobertura) override;
};

#endif // GRAFOMATRIZ_H