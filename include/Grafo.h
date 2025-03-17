#ifndef GRAFO_H
#define GRAFO_H

#include "No.h"
#include "Aresta.h"
#include <string>
#include <vector>

/**
 * @class Grafo
 * @brief Classe abstrata que representa um grafo genérico.
 *
 * Esta classe define a interface básica para manipulação de grafos, incluindo operações como verificação de propriedades,
 * manipulação de nós e arestas, e algoritmos de cobertura. É uma base para implementações específicas como GrafoMatriz e GrafoLista.
 */
class Grafo
{
protected:
    int ordem;              ///< Número de vértices do grafo.
    int numNos;             ///< Número total de nós no grafo.
    bool direcionado;       ///< Indica se o grafo é direcionado (true) ou não (false).
    bool ponderadoVertices; ///< Indica se os vértices possuem pesos (true) ou não (false).
    bool ponderadoArestas;  ///< Indica se as arestas possuem pesos (true) ou não (false).
    No *primeiroNo;         ///< Ponteiro para o primeiro nó da lista de nós.
    No *ultimoNo;           ///< Ponteiro para o último nó da lista de nós.

    /**
     * @brief Constrói uma solução inicial para o problema de cobertura de arestas usando um método guloso randomizado.
     * @param alpha Parâmetro que controla a aleatoriedade da escolha dos vértices.
     * @param tamanhoCobertura Ponteiro para armazenar o tamanho da cobertura encontrada.
     * @return Um array contendo os vértices da cobertura inicial.
     */
    virtual int *construcaoGulosaRandomizada(float alpha, int *tamanhoCobertura) = 0;

    /**
     * @brief Realiza uma busca local para melhorar uma solução de cobertura de arestas.
     * @param solucao Array contendo a solução inicial.
     * @param tamanhoSolucao Tamanho da solução inicial.
     * @param tamanhoMelhorSolucao Ponteiro para armazenar o tamanho da solução melhorada.
     * @return Um array contendo a solução melhorada após a busca local.
     */
    virtual int *buscaLocal(int *solucao, int tamanhoSolucao, int *tamanhoMelhorSolucao) = 0;

    /**
     * @brief Verifica se uma dada cobertura de vértices é válida, ou seja, se cobre todas as arestas do grafo.
     * @param cobertura Array contendo os índices dos vértices que compõem a cobertura.
     * @param tamanhoCobertura Tamanho do array de cobertura (número de vértices na cobertura).
     * @return true se a cobertura for válida (todas as arestas têm pelo menos uma extremidade na cobertura), false caso contrário.
     */
    virtual bool verificarCobertura(int *cobertura, int tamanhoCobertura) = 0;

    /**
     * @brief Atualiza as probabilidades de escolha dos valores de alpha no algoritmo GRASP reativo.
     * @param alphas Array com os valores de alpha disponíveis.
     * @param probabilidades Array com as probabilidades associadas a cada alpha (atualizado pela função).
     * @param valores Array com os valores acumulados de qualidade para cada alpha.
     * @param contadores Array com o número de vezes que cada alpha foi utilizado.
     * @param tamanhoLista Tamanho da lista de alphas.
     * @param melhorValor Melhor valor encontrado para normalização das probabilidades.
     */
    virtual void atualizaProbabilidades(float *alphas, float *probabilidades,
                                        float *valores, int *contadores,
                                        int tamanhoLista, float melhorValor) = 0;

public:
    /**
     * @brief Construtor da classe Grafo.
     *
     * Inicializa um grafo com base na ordem (número de vértices), se é direcionado ou não,
     * se os vértices são ponderados e se as arestas são ponderadas.
     * @param ordem Número de vértices do grafo.
     * @param direcionado Indica se o grafo é direcionado (true) ou não (false).
     * @param ponderadoVertices Indica se os vértices são ponderados (true) ou não (false).
     * @param ponderadoArestas Indica se as arestas são ponderadas (true) ou não (false).
     */
    Grafo(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas);

    /**
     * @brief Construtor padrão da classe Grafo.
     *
     * Inicializa um grafo vazio com valores padrão (ordem = 0, não direcionado, sem pesos).
     */
    Grafo() : ordem(0), numNos(0), direcionado(false), ponderadoVertices(false), ponderadoArestas(false) {}

    /**
     * @brief Destrutor virtual da classe Grafo.
     *
     * Responsável por liberar os recursos alocados pelo grafo.
     */
    virtual ~Grafo();

    /**
     * @brief Implementa um algoritmo guloso para encontrar uma cobertura de vértices.
     * @param tamanhoCobertura Ponteiro para armazenar o tamanho da cobertura encontrada.
     * @return Um array contendo os vértices que fazem parte da cobertura.
     */
    virtual int *construcaoGulosa(int *tamanhoCobertura) = 0;

    /**
     * @brief Remove um nó do grafo.
     * @param idNo ID do nó a ser removido.
     */
    virtual void deleta_no(int idNo) = 0;

    /**
     * @brief Obtém o grau de um vértice.
     * @param vertice Índice do vértice.
     * @return Número de arestas conectadas ao vértice especificado.
     */
    virtual int getGrau(int vertice);

    /**
     * @brief Obtém a ordem do grafo.
     * @return A ordem (número de vértices) do grafo.
     */
    virtual int getOrdem();

    /**
     * @brief Obtém o número de nós do grafo.
     * @return O número de nós do grafo.
     */
    virtual int getNumNos();

    /**
     * @brief Verifica se o grafo é direcionado.
     * @return true se o grafo for direcionado, false caso contrário.
     */
    virtual bool ehDirecionado();

    /**
     * @brief Verifica se o grafo possui vértices ponderados.
     * @return true se ao menos um vértice for ponderado, false caso contrário.
     */
    virtual bool verticePonderado();

    /**
     * @brief Verifica se o grafo possui arestas ponderadas.
     * @return true se ao menos uma aresta for ponderada, false caso contrário.
     */
    virtual bool arestaPonderada();

    /**
     * @brief Verifica se o grafo é completo.
     * Um grafo completo possui todas as combinações possíveis de arestas entre seus vértices.
     * @return true se o grafo é completo; caso contrário, false.
     */
    virtual bool ehCompleto();

    /**
     * @brief Verifica se o grafo é bipartido.
     * Um grafo bipartido pode ser dividido em dois subconjuntos, onde não existem arestas entre vértices do mesmo subconjunto.
     * @return true se o grafo é bipartido; caso contrário, false.
     */
    virtual bool ehBipartido();

    /**
     * @brief Obtém o nó pelo seu ID.
     * @param id O ID do nó a ser buscado.
     * @return O ponteiro para o nó com o ID especificado ou nullptr caso o nó não seja encontrado.
     */
    No *getNoPeloId(int id);

    /**
     * @brief Determina o número de componentes conexos no grafo.
     * Um componente conexo é um subconjunto de vértices onde existe pelo menos um caminho entre cada par de vértices.
     * @return Número de componentes conexos no grafo.
     */
    virtual int nConexo();

    /**
     * @brief Verifica se o grafo é uma árvore.
     * Uma árvore é um grafo conexo sem ciclos.
     * @return true se o grafo é uma árvore; caso contrário, false.
     */
    virtual bool ehArvore();

    /**
     * @brief Verifica se o grafo possui pontes.
     * Uma ponte é uma aresta cuja remoção aumenta o número de componentes conexos do grafo.
     * @return true se existe pelo menos uma ponte; caso contrário, false.
     */
    virtual bool possuiPonte();

    /**
     * @brief Verifica se o grafo possui vértices de articulação.
     * Um vértice de articulação é aquele cuja remoção aumenta o número de componentes conexos do grafo.
     * @return true se existe pelo menos um vértice de articulação; caso contrário, false.
     */
    virtual bool possuiArticulacao();

    /**
     * @brief Carrega o grafo a partir de um arquivo.
     * O arquivo deve conter os dados do grafo, como número de nós, tipo de grafo e arestas.
     * @param arquivo Caminho para o arquivo de entrada.
     */
    virtual void carregaGrafo(const std::string &arquivo) = 0;

    /**
     * @brief Cria um novo grafo a partir de um arquivo de configuração.
     * O arquivo deve conter as informações do grafo, como tipo de estrutura, número de nós e arestas.
     * @param arquivoConfig Caminho para o arquivo de configuração.
     */
    virtual void novoGrafo(const std::string &arquivoConfig) = 0;

    /**
     * @brief Adiciona um nó ao grafo.
     * @param idNo ID do nó a ser adicionado.
     */
    virtual void adicionaNo(int idNo) = 0;

    /**
     * @brief Obtém o peso de uma aresta entre dois vértices.
     * @param origem O ID do vértice de origem.
     * @param destino O ID do vértice de destino.
     * @return O peso da aresta entre os vértices ou -1 se a aresta não existir.
     */
    virtual float getPesoAresta(int origem, int destino);

    /**
     * @brief Calcula a menor distância entre dois vértices no grafo.
     * @param origem O ID do vértice de origem.
     * @param destino O ID do vértice de destino.
     * @return A menor distância entre os vértices de origem e destino, ou -1 se não houver caminho.
     */
    virtual int menorDistancia(int origem, int destino);

    /**
     * @brief Adiciona uma nova aresta ao grafo.
     * @param origem ID do nó de origem da aresta.
     * @param destino ID do nó de destino da aresta.
     * @param peso Peso da aresta (caso o grafo seja ponderado por arestas).
     */
    virtual void novaAresta(int origem, int destino, float peso);

    /**
     * @brief Encontra uma cobertura mínima de arestas usando uma abordagem GRASP.
     * @param alpha Parâmetro de controle para a aleatoriedade na fase de construção.
     * @param maxIteracoes Número máximo de iterações do algoritmo.
     * @param tamanhoCobertura Ponteiro para armazenar o tamanho da cobertura encontrada.
     * @return Um array contendo os vértices que fazem parte da cobertura mínima de arestas.
     */
    virtual int *coberturaArestas(float alpha, int maxIteracoes, int *tamanhoCobertura) = 0;

    /**
     * @brief Remove uma aresta do grafo.
     * @param idNoOrigem ID do nó de origem da aresta.
     * @param idNoDestino ID do nó de destino da aresta.
     * @param direcionado Indica se o grafo é direcionado (true) ou não (false).
     */
    virtual void removeAresta(int idNoOrigem, int idNoDestino, bool direcionado) = 0;

    /**
     * @brief Implementa uma variação reativa do algoritmo GRASP para cobertura de arestas.
     * @param maxIteracoes Número máximo de iterações do algoritmo.
     * @param tamanhoListaAlpha Número de valores de alpha testados durante a execução.
     * @param tamanhoCobertura Ponteiro para armazenar o tamanho da melhor cobertura encontrada.
     * @return Um array contendo os vértices da melhor cobertura de arestas encontrada.
     */
    virtual int *coberturaArestasReativa(int maxIteracoes, int tamanhoListaAlpha, int *tamanhoCobertura) = 0;
};

#endif // GRAFO_H