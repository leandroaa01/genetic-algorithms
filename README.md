# Memetic Algorithm Hequetor Leander 

## Authors
This project was developed by Heitor Fernandes Paes Leme Campo (<heitor.campos.711@ufrn.edu.br>) and Leandro Andrade de Araujo (<leandro.andrade.401@ufrn.edu.br>) as part of the *Graphs* course at UFRN.

## Compilling and Running
> [!note]
> This method requires CMake (>= 3.31.6) to be installed on your system. 
> CMake is a cross-platform build system generator used to configure and compile the project. If it's not already installed, 
> you can install it using your system’s package manager (e.g., `sudo apt install cmake` on Debian/Ubuntu or `brew install cmake` on macOS).

Once CMake is set up, follow the steps:


1 Clone this repository:

```bash
git clone https://gitlab.com/leandroaa01/mahl-unit-3.git
```


2. Navigate to the project directory:

```bash
cd mahl-unit-3
```

3. Compile and build the program using `cmake`:

```bash
cmake -S . -B build 
cmake --build build
```
or

```bash
install.sh
```

4. Run:

```bash
./bin/Mahl
```

> [!note]
> Run **./bin/Mahl [ --help or -h ]** to view all available options and usage instructions.


```bash
Usage: Mahl [<options>] 

Rendering simulation options:
  -h, --help                           Show this help message and exit
  -p <value>, --population <value>     Set the population size (default: 50)
  -g <value>, --generations <value>    Set the number of generations (default: 600)
  -tx <value>, --tmax <value>          Set the Tmax value (default: 85.0)
  -c <value>, --children <value>       Set the children goal (default: 50)
  -b <value>, --breed <value>          Set the breed quantity (default: 6)
  -s <value>, --selection <value>      Set the population selection quantity (default: 10)
  -m <value>, --mutation <value>       Set the mutation rate (default: 0.40)
  -i <value>, --immigration <value>    Set the immigration quantity (default: 0)
  -ps, --print-score                   Print the best score every 25% generations
  -allHeuristic                        Use all heuristic methods for initial population generation (default: true)
  -gni, --useGenNearestInsertion       Use the nearest insertion heuristic for initial population generation
  -gnn, --useGenNearestNeighbor        Use the nearest neighbor heuristic for initial population generation
  -gm, --useMahl                       Use the MAHL algorithm for evolution 
  -ama, --activeMA                     Activate the Memetic Algorithm for local search
  -t, -test                            Run the program in test mode, executing multiple runs with different Tmax values

   Obs: The program will run 20 executions with the specified parameters and print the best solution found, along with the average execution time.
   When activating a heuristic, the last result will always be considered.
   
```

