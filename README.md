# TP3 Heurísticas para CVRP

## Install
1) Install `cmake`, `make`, `g++` and `gtest` 
2) Clone project: `git clone git@github.com:ngoldenberg/uba-aed3-tp3-2c-2019.git` 
_(or no ssh: `git clone https://github.com/ngoldenberg/uba-aed3-tp3-2c-2019`)_ 
3) Run `cmake -S . -B build`

## Build
- Compile: `make -C build`
- Test: `make -C build test`
- Clean: `make -C build clean`
_(se puede evitar `-C build` estar dentro de `build/`)_

## Run & Usage
### CLI direct usage
Se puede correr directamente el ejectuable: `./bin/cvrp_cws`
Tambien podemos hacer `cat` de un archivo ya procesados por python. 
#### Examples
```
cat test/data/input/set-a-32.txt | ./bin/cvrp_cws
cat test/data/input/X-n502-k39.txt | ./bin/cvrp_cws
```

### Python processing
Para procesar archivos raw de casos de CVRP, puede utilizarse un script de python ubicado en `experimentacion`:
- `cd experimentacion`
- `pip install -r requirements.txt`
- `jupyter notebook`
- Correr el archivo `template_experimentación.ipynb`

## Resolucion del problema
Se resuelve en c++ y se proveen ejecutables que toman la entrada traducida desde python.

Se implementan las Heurísticas: 
- [x] savings-clark-wright: Constructiva de savings mediante el método savings de Clark-Wright.
- [x] greedy-v2: heuŕıstica constructiva golosa adicional.
- clustering-sweep: Heuŕıstica constructiva de cluster-first, route-second. Clusterizando mediante sweep algorithm y luego resolviendo los TSPs restantes de manera heuŕıstica.
- clustering-v2: Heuŕıstica constructiva de cluster-first, route-second con otra alternativa de clus- terizacíon y resolucíon de TSPs posteriores.
- [x] simulated-annealing: Metaheuŕıstica de Simulated Annealing.

## Experimentacion
Se grafica y eligen los ejecutables desde python. Lo manejamos con jupyter notebook y pasamos la entrada a c++.

Usamos instancias de la página http://vrp.atd-lab.inf.puc-rio.br/index.php/en/

```bash
cd experimentacion
jupyter notebook
```

## Informe
El mismo se encuenta en overleaf y su link es: https://www.overleaf.com/read/hnsmmtdhgxyg

## Developer notes

### Agilizar Simulated Annealing
Para correr los tests mas rapidamente, es posible incrementar el valor de `SA_COOLING`. 
Chequear [esta linea](https://github.com/ngoldenberg/uba-aed3-tp3-2c-2019/blob/alg/sa/src/config/defaults.h#L6).


