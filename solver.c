#include "bsq.h"

// Devuelve el valor mínimo entre tres enteros.
// Se usa en el algoritmo de programación dinámica para calcular el tamaño del cuadrado más grande.
int min(int a, int b, int c)
{
    // Si 'a' es menor o igual que 'b' y 'c', devuelve 'a'
    if (a <= b && a <= c)
        return (a);

    // Si 'b' es menor o igual que 'a' y 'c', devuelve 'b'
    if (b <= a && b <= c)
        return (b);

    // Si ninguna de las condiciones anteriores se cumple, 'c' es el menor
    return (c);
}


// Aplica el algoritmo de programación dinámica para encontrar el cuadrado más grande sin obstáculos.
// Actualiza la estructura 'sq' con la posición y tamaño del cuadrado encontrado.
void    solve_map(t_map *map, t_square *sq)
{
    int **dp;
    int i;
    int j;

    // Reserva memoria para la matriz auxiliar 'dp' con tantas filas como el mapa
    dp = malloc(sizeof(int *) * map->rows);
    i = 0;
    while (i < map->rows)
    {
        // Reserva memoria para cada fila de 'dp' con tantas columnas como el mapa
        dp[i] = malloc(sizeof(int) * map->cols);
        j = 0;
        while (j < map->cols)
        {
            // Si hay un obstáculo, no se puede formar cuadrado en esta celda
            if (map->grid[i][j] == map->obstacle)
                dp[i][j] = 0;
            // Si está en el borde, solo puede formar un cuadrado de tamaño 1
            else if (i == 0 || j == 0)
                dp[i][j] = 1;
            // Si no hay obstáculo y no está en el borde, calcula el tamaño del cuadrado
            else
                dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);
            // Si el cuadrado actual es más grande que el anterior, actualiza 'sq'
            if (dp[i][j] > sq->size)
            {
                sq->size = dp[i][j];
                sq->x = j;
                sq->y = i;
            }
            j++;
        }
        i++;
    }
    // Libera la memoria de la matriz 'dp'
    while (--i >= 0)
        free(dp[i]);
    free(dp);
}

