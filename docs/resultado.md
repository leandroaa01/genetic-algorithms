## Comparaçoes do GenNearestNeighbor:
Segue teste feito com o main.cpp, ele foram gerando no mimino 3 vezes cada, pegando o menos...

VALORES RAROS GERANDO:
distancia: 13.97 (Tmax = 15.00)
caminho: 1 28 18 6 13 32
distancia: 14.94 (Tmax = 15.00)
caminho: 1 28 18 5 6 32

Tmax = 5 , gerou mesma rota/tempo do artigo:
T = 4.14 , rota:  1 28 32 

No Tmax = 10, ele está com bugs, mas gerou uma solução melhor:
T =  7.89 , rota: 1 18 28 32
acredito que foi o swap(não sei como gerou, mas teve entre o 18 e 28 kkkk)

No Tmax = 15 , ele gerou um tempo ruim.
T = 13.97 sendo que o melhor é 14.70
provamente foi pq a rota foi menor:
1 28 18 6 13 32

No Tmax = 20, ele gerou um tempo melhor:
T = 19.66 , rota: 1 28 18 6 7 3 13 32

No Tmax = 25, ele gerou um tempo melhor novamnete:
T = 24.38 , rota: 1 28 18 6 7 3 2 8 9 13 32

No Tmax = 30, ele gerou um rota menor que no artigo 
T = 29.58 , rota: 1 28 18 6 7 3 2 8 10 11 12 19 32

No Tmax = 35, ele gerou um tempo melhor novamnete:
T = 34.80 , rota: 1 6 7 3 2 8 9 10 11 12 21 20 27 28 18 32

No Tmax = 40, ele gerou um tempo melhor novamnete:
T = 39.23 , rota:  1 18 6 7 3 2 8 9 10 11 12 21 20 19 27 31 28 32

No Tmax = 46, ele gerou um tempo melhor novamnete:
T = 45.95 , rota: 1 5 6 7 3 2 8 9 10 11 12 21 20 27 31 26 19 28 18 32

No Tmax = 50, ele gerou um tempo melhor novamnete:
T = 49.61 , rota:  1 28 18 6 7 3 2 8 9 10 11 12 21 20 19 27 31 26 22 23 32

No Tmax = 60, ele gerou um rota menor que no artigo 
T = 59.76, rota: 1 6 7 3 2 8 9 10 11 12 21 20 19 27 31 26 22 23 25 24 28 18 32

No Tmax = 70, ele gerou um tempo melhor novamnete:
T = 69.78 , rota: 1 27 31 26 22 23 25 24 30 29 28 18 6 7 3 2 8 9 10 11 12 21 20 19 32

No Tmax = 80, ele gerou um tempo melhor novamnete:
T = 79.99 , rota:1 27 31 26 22 23 25 24 30 29 17 15 5 18 6 7 3 2 8 9 10 11 12 21 20 19 32

No Tmax = 85, ele gerou um tempo melhor novamnete:
T = 84.66 , rota: 1 6 7 3 2 8 9 10 11 12 21 20 19 27 31 26 22 23 25 24 30 29 17 15 14 5 18 28 32
