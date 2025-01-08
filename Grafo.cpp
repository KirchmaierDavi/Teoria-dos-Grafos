#include "Grafo.h"

Grafo::Grafo(int ordem, bool direcionado, bool ponderadoVertices, bool ponderadoArestas)
    : ordem(ordem), direcionado(direcionado), ponderadoVertices(ponderadoVertices), ponderadoArestas(ponderadoArestas) {}

Grafo::~Grafo() {}

int Grafo::getOrdem() {
    return ordem;
}

bool Grafo::ehDirecionado() {
    return direcionado;
}

bool Grafo::verticePonderado() {
    return ponderadoVertices;
}

bool Grafo::arestaPonderada() {
    return ponderadoArestas;
}
