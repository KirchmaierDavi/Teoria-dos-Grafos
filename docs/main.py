# Esse foi o script em Python que eu usei para gerar os 10 arquivos de grafo.
# O script gera 10 arquivos de grafo com base em um modelo de grafo aleatório.

import networkx as nx
import numpy as np

# Gerar 10 arquivos
for i in range(10):
    # Número aleatório de nós entre 5000 e 7500
    num_nos = np.random.randint(5000, 7501)
    
    # Probabilidade de aresta ajustada para manter grafo esparso
    probabilidade_aresta = 0.001
    
    # Determinar aleatoriamente se será direcionado, ponderado nós e ponderado arestas
    eh_direcionado = np.random.randint(0, 2)  # 0 ou 1
    eh_ponderado_nos = np.random.randint(0, 2)  # 0 ou 1
    eh_ponderado_arestas = np.random.randint(0, 2)  # 0 ou 1
    
    # Criar grafo com base na direção
    if eh_direcionado:
        grafo = nx.gnp_random_graph(n=num_nos, p=probabilidade_aresta, seed=42+i, directed=True)
    else:
        grafo = nx.gnp_random_graph(n=num_nos, p=probabilidade_aresta, seed=42+i, directed=False)
    
    # Atribuir pesos aos nós se for ponderado
    if eh_ponderado_nos:
        pesos_nos = {no: np.random.randint(1, 11) for no in grafo.nodes()}
        nx.set_node_attributes(grafo, pesos_nos, 'peso')
    
    # Atribuir pesos às arestas se for ponderado
    if eh_ponderado_arestas:
        pesos_arestas = {(u, v): np.random.randint(1, 11) for u, v in grafo.edges()}
        nx.set_edge_attributes(grafo, pesos_arestas, 'peso')
    
    # Nome do arquivo (grafo1.txt, grafo2.txt, etc)
    nome_arquivo = f'grafo{i+1}.txt'
    
    with open(nome_arquivo, 'w') as arquivo:
        # Primeira linha: número de nós, direcionado, ponderado vértices, ponderado arestas
        arquivo.write(f"{grafo.number_of_nodes()} {eh_direcionado} {eh_ponderado_nos} {eh_ponderado_arestas}\n")
        
        # Se ponderado nos vértices, adicionar linha com pesos
        if eh_ponderado_nos:
            pesos_linha = ' '.join(str(grafo.nodes[no]['peso']) for no in grafo.nodes())
            arquivo.write(f"{pesos_linha}\n")
        
        # Linhas das arestas
        for u, v in grafo.edges():
            if eh_ponderado_arestas:
                arquivo.write(f"{u + 1} {v + 1} {grafo[u][v]['peso']}\n")
            else:
                arquivo.write(f"{u + 1} {v + 1}\n")

print("10 arquivos gerados com sucesso!")