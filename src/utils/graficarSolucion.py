import networkx as nx
from matplotlib import pyplot as plt

INSTANCE_FILENAME = 'X-n502-k39'
INSTANCE_FILEPATH = 'experimentacion/instancias/%s.txt' % INSTANCE_FILENAME
def ruta_instancia(instancia):
    return INSTANCE_FILEPATH

def main():
    instancia = INSTANCE_FILENAME
    input_file = open('/home/andisici/Documents/algo3/uba-aed3-tp3-2c-2019/test/data/input/A-n33-k5.txt', 'r')
    lines = input_file.readlines()
    n = int(lines[0])
    G = nx.Graph()
    for i in range(n):
        (x,y) = (int(lines[i+2].split()[0]), int(lines[i+2].split()[1]))
        print(x,y)
        G.add_node(i+1,pos=(x,y))

    input_file.close()
    sol_file = open('/home/andisici/Documents/algo3/uba-aed3-tp3-2c-2019/experimentacion/instancias/corridas/A-n33-k5.txt', 'r')
    lines = sol_file.readlines()
    c = int(lines[0])
    print(c)
    for i in range(c):
        anterior = 1 #nodo 1 es el deposito
        for nodo in (lines[i+1]).split():
            # G.add_edge(anterior, int(nodo))
            anterior = int(nodo)

    pos=nx.get_node_attributes(G,'pos')

    nx.draw(G,pos)
    plt.show()
    return 0

main()