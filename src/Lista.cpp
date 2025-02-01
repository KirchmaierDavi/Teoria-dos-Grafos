/**
 * @file ListaEncad.cpp
 * @brief Implementação das funções da classe Lista.
 */

#include "../include/Lista.h"
#include <iostream>

/**
 * @brief Construtor da classe Lista.
 *
 * Este construtor inicializa a lista encadeada, configurando a cabeça como nullptr e o tamanho como 0.
 */
Lista::Lista() : cabeca(nullptr), tamanho(0) {}

/**
 * @brief Destrutor da classe Lista.
 *
 * O destrutor percorre a lista encadeada e deleta todos os nós da lista, liberando a memória alocada.
 */
Lista::~Lista()
{
    No *atual = cabeca;
    while (atual != nullptr)
    {
        No *prox = atual->getProxNo();
        delete atual;
        atual = prox;
    }
}

/**
 * @brief Adiciona um novo nó na lista.
 *
 * Este método adiciona um novo nó no início da lista, com o ID e peso fornecidos.
 *
 * @param idNo O ID do nó a ser adicionado.
 * @param pesoNo O peso do nó a ser adicionado.
 */
void Lista::adicionar(int idNo, float pesoNo)
{
    No *novoNo = new No(idNo, pesoNo);
    novoNo->setProxNo(cabeca);
    cabeca = novoNo;
    tamanho++;
}

/**
 * @brief Remove um nó da lista pelo seu ID.
 *
 * Este método remove o nó com o ID especificado da lista. Se o nó for encontrado, ele será removido e a memória alocada será liberada.
 *
 * @param idNo O ID do nó a ser removido.
 */
void Lista::remover(int idNo)
{
    No *atual = cabeca;
    No *anterior = nullptr;

    while (atual != nullptr && atual->getIdNo() != idNo)
    {
        anterior = atual;
        atual = atual->getProxNo();
    }

    if (atual != nullptr)
    {
        if (anterior == nullptr)
        {
            cabeca = atual->getProxNo();
        }
        else
        {
            anterior->setProxNo(atual->getProxNo());
        }
        delete atual;
        tamanho--;
    }
}

/**
 * @brief Verifica se a lista contém um nó com o ID fornecido.
 *
 * Este método percorre a lista para verificar se há um nó com o ID especificado.
 *
 * @param idNo O ID do nó a ser buscado.
 * @return true Se o nó com o ID fornecido for encontrado, false caso contrário.
 */
bool Lista::contem(int idNo)
{
    No *atual = cabeca;
    while (atual != nullptr)
    {
        if (atual->getIdNo() == idNo)
        {
            return true;
        }
        atual = atual->getProxNo();
    }
    return false;
}

/**
 * @brief Obtém o tamanho da lista.
 *
 * Este método retorna o número de nós presentes na lista.
 *
 * @return O número de elementos (tamanho) na lista.
 */
int Lista::getTamanho()
{
    return tamanho;
}

/**
 * @brief Obtém o elemento na posição especificada da lista.
 *
 * Este método retorna o nó na posição indicada pelo índice. Se o índice for inválido (fora dos limites), retorna nullptr.
 *
 * @param indice O índice do elemento desejado.
 * @return O ponteiro para o nó na posição especificada, ou nullptr caso o índice esteja fora dos limites.
 */
No *Lista::getElemento(int indice)
{
    if (indice < 0 || indice >= tamanho)
    {
        std::cout << "Indice fora dos limites da lista";
        return nullptr;
    }

    No *atual = cabeca;
    for (int i = 0; i < indice; ++i)
    {
        atual = atual->getProxNo();
    }
    return atual;
}