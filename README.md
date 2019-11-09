# TP3 Herísticas para CVRP

## Resolución del problema
Se resuelve en c++ y se proveen ejecutables que toman la entrada traducida desde python.

Se implementan las Heurísticas: 
- greedy-savings-clark: Constructiva de savings mediante el método savings de Clark-Wrigh.
- greedy-v2: heur ́ıstica constructiva golosa adicional.
- clustering-sweep: Heuŕıstica constructiva de cluster-first, route-second. Clusterizando mediante sweep algorithm y luego resolviendo los TSPs restantes de manera heuŕıstica.
- clustering-v2: Heuŕıstica constructiva de cluster-first, route-second con otra alternativa de clus- terizacíon y resolucíon de TSPs posteriores.
- simulated-annealing: Metaheuŕıstica de Simulated Annealing.

```bash

```

## Experimentación
Se grafica y eligen los ejecutables desde python. Lo manejamos con jupyter notebook y pasamos la entrada a c++.

Usamos instancias de la página http://vrp.atd-lab.inf.puc-rio.br/index.php/en/

```bash
cd experimentacion
jupyter notebook
```

## Informe
El mismo se encuenta en overleaf y su link es: https://www.overleaf.com/read/hnsmmtdhgxyg




