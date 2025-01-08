#include "GrafoLista.h"
#include <fstream>
#include <iostream>


using namespace std;

GrafoLista::GrafoLista(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas)
    : Grafo(ordem, direcionado, ponderadoVertices, ponderadoArestas) {
    listaAdj = new Lista[ordem];
}

GrafoLista::~GrafoLista() {
    delete[] listaAdj;
}

int GrafoLista::getGrau(int vertice) {
    return listaAdj[vertice].getTamanho();
}

bool GrafoLista::ehCompleto() {
    for (int i = 0; i < ordem; i++) {
        if (listaAdj[i].getTamanho() != ordem - 1) {
            return false;
        }
    }
    return true;
}

bool GrafoLista::ehBipartido() {
    int* cores = new int[ordem];
    for (int i = 0; i < ordem; ++i) {
        cores[i] = -1; // -1 significa não colorido
    }

    int* fila = new int[ordem];
    int inicio = 0, fim = 0;

    cores[0] = 1; // Começa colorindo o primeiro vértice
    fila[fim++] = 0;

    while (inicio != fim) {
        int u = fila[inicio++];
        for (int i = 0; i < listaAdj[u].getTamanho(); ++i) {
            int v = listaAdj[u].getElemento(i)->getIdNo();
            if (cores[v] == -1) {
                cores[v] = 1 - cores[u];
                fila[fim++] = v;
            } else if (cores[v] == cores[u]) {
                delete[] cores;
                delete[] fila;
                return false;
            }
        }
    }

    delete[] cores;
    delete[] fila;
    return true;
}

int GrafoLista::nConexo() {
    bool* visitado = new bool[ordem];
    for (int i = 0; i < ordem; ++i) {
        visitado[i] = false;
    }

    int componentes = 0;

    auto dfs = [&](int v, auto& dfsRef) -> void {
        visitado[v] = true;
        for (int i = 0; i < listaAdj[v].getTamanho(); ++i) {
            int adj = listaAdj[v].getElemento(i)->getIdNo();
            if (!visitado[adj]) {
                dfsRef(adj, dfsRef);
            }
        }
    };

    for (int i = 0; i < ordem; ++i) {
        if (!visitado[i]) {
            componentes++;
            dfs(i, dfs);
        }
    }

    delete[] visitado;
    return componentes;
}

bool GrafoLista::ehArvore() {
    return (nConexo() == 1 && (ordem - 1) == numVertices);
}

bool GrafoLista::possuiPonte() {
    for (int u = 0; u < ordem; u++) {
        for (int i = 0; i < listaAdj[u].getTamanho(); ++i) {
            int v = listaAdj[u].getElemento(i)->getIdNo();

            listaAdj[u].remover(v);
            if (!direcionado) {
                listaAdj[v].remover(u);
            }
            bool* visitado = new bool[ordem];
            for (int j = 0; j < ordem; ++j) {
                visitado[j] = false;
            }

            auto dfs = [&](int vertice, auto& dfsRef) -> void {
                visitado[vertice] = true;
                for (int k = 0; k < listaAdj[vertice].getTamanho(); ++k) {
                    int adj = listaAdj[vertice].getElemento(k)->getIdNo();
                    if (!visitado[adj]) {
                        dfsRef(adj, dfsRef);
                    }
                }
            };

            int componentes = 0;
            for (int j = 0; j < ordem; j++) {
                if (!visitado[j]) {
                    componentes++;
                    dfs(j, dfs);
                }
            }

            delete[] visitado;
            listaAdj[u].adicionar(v);
            if (!direcionado) {
                listaAdj[v].adicionar(u);
            }

            if (componentes > 1) {
                return true;
            }
        }
    }

    return false;
}

bool GrafoLista::possuiArticulacao() {
    bool* visitado = new bool[ordem];
    int componentesOriginais = nConexo();

    for (int v = 0; v < ordem; v++) {
        for (int i = 0; i < ordem; ++i) {
            visitado[i] = false;
        }
        visitado[v] = true; 

        int componentes = 0;
        for (int u = 0; u < ordem; u++) {
            if (!visitado[u]) {
                componentes++;
                auto dfs = [&](int x, auto& dfsRef) -> void {
                    visitado[x] = true;
                    for (int i = 0; i < listaAdj[x].getTamanho(); ++i) {
                        int adj = listaAdj[x].getElemento(i)->getIdNo();
                        if (!visitado[adj]) {
                            dfsRef(adj, dfsRef);
                        }
                    }
                };
                dfs(u, dfs);
            }
        }

        if (componentes > componentesOriginais) {
            delete[] visitado;
            return true;
        }
    }

    delete[] visitado;
    return false;
}

void GrafoLista::carregaGrafo(const std::string& arquivo) {
    std::ifstream file(arquivo);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << arquivo << std::endl;
        return;
    }

    int numNos, direcionado, ponderadoVertices, ponderadoArestas;
    file >> numNos >> direcionado >> ponderadoVertices >> ponderadoArestas;

    this->ordem = numNos;
    this->direcionado = direcionado;
    this->ponderadoVertices = ponderadoVertices;
    this->ponderadoArestas = ponderadoArestas;

    if (ponderadoVertices) {
        std::cout << "Pesos dos vértices:" << std::endl;
        for (int i = 0; i < numNos; i++) {
            int pesoVertice;
            file >> pesoVertice;
            std::cout << "Vértice " << i + 1 << ": Peso " << pesoVertice << std::endl;
        }
    }

    delete[] listaAdj;
    listaAdj = new Lista[numNos];

    int origem, destino, peso;
    while (file >> origem >> destino >> peso) {
        origem--; 
        destino--;
        listaAdj[origem].adicionar(destino);
        if (!direcionado) {
            listaAdj[destino].adicionar(origem);
        }
        std::cout << "Aresta adicionada: " << origem + 1 << " -> " << destino + 1 << " com peso " << peso << std::endl;
    }

    file.close();
    std::cout << "Lista de Adjacência carregada com sucesso." << std::endl;
}

void GrafoLista::novoGrafo(const std::string& arquivoConfig) {
    std::ifstream file(arquivoConfig);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de configuração!" << std::endl;
        return;
    }

    std::string tipo;
    file >> tipo;  // Ignora "matriz" ou "lista"
    file >> ordem >> direcionado >> ponderadoVertices >> ponderadoArestas;
    delete[] listaAdj;
    listaAdj = new Lista[ordem];

    int origem, destino, peso;
    while (file >> origem >> destino >> peso) {
        listaAdj[origem].adicionar(destino);
        if (!direcionado) {
            listaAdj[destino].adicionar(origem);
        }
    }

    file.close();
}
