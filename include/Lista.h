#ifndef LISTA_H
#define LISTA_H

#include "No.h"

/**
 * @class Lista
 * @brief Classe que representa uma lista encadeada simples.
 * 
 * Esta classe implementa uma lista encadeada para armazenar nós, com operações básicas como adição,
 * remoção, busca e acesso a elementos. É utilizada como estrutura auxiliar em representações de grafos.
 */
class Lista
{
private:
    No *cabeca;     ///< Ponteiro para o primeiro nó da lista.
    int tamanho;    ///< Número de elementos na lista.

public:
    /**
     * @brief Construtor da classe Lista.
     * 
     * Inicializa a lista encadeada, configurando a cabeça como nullptr e o tamanho como 0.
     */
    Lista();

    /**
     * @brief Destrutor da classe Lista.
     * 
     * Percorre a lista encadeada e deleta todos os nós, liberando a memória alocada.
     */
    ~Lista();

    /**
     * @brief Operador de atribuição para copiar uma lista.
     * 
     * Limpa a lista atual e copia os elementos da outra lista fornecida.
     * @param other Lista a ser copiada.
     * @return Referência para a lista atual após a cópia.
     */
    Lista &operator=(const Lista &other)
    {
        if (this != &other)
        {
            // Clear current list
            while (cabeca != nullptr)
            {
                No *temp = cabeca;
                cabeca = cabeca->getProxNo();
                delete temp;
            }

            // Copy from other list
            No *current = other.cabeca;
            while (current != nullptr)
            {
                adicionar(current->getIdNo());
                current = current->getProxNo();
            }
        }
        return *this;
    }

    /**
     * @brief Adiciona um novo nó na lista.
     * 
     * Adiciona um novo nó no início da lista, com o ID e peso fornecidos.
     * @param idNo O ID do nó a ser adicionado.
     * @param pesoNo O peso do nó a ser adicionado (padrão 0.0).
     */
    void adicionar(int idNo, float pesoNo = 0.0);

    /**
     * @brief Remove um nó da lista pelo seu ID.
     * 
     * Remove o nó com o ID especificado da lista, liberando a memória alocada.
     * @param idNo O ID do nó a ser removido.
     */
    void remover(int idNo);

    /**
     * @brief Verifica se a lista contém um nó com o ID fornecido.
     * 
     * Percorre a lista para verificar se há um nó com o ID especificado.
     * @param idNo O ID do nó a ser buscado.
     * @return true se o nó com o ID fornecido for encontrado, false caso contrário.
     */
    bool contem(int idNo) const;

    /**
     * @brief Obtém o elemento na posição especificada da lista.
     * 
     * Retorna o nó na posição indicada pelo índice.
     * @param posicao O índice do elemento desejado.
     * @return Ponteiro para o nó na posição especificada, ou nullptr se o índice estiver fora dos limites.
     */
    No *getElemento(int posicao) const;

    /**
     * @brief Obtém o tamanho da lista.
     * 
     * Retorna o número de nós presentes na lista.
     * @return O número de elementos (tamanho) na lista.
     */
    int getTamanho() const;
};

#endif