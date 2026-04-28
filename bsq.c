/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:02:10 by gortiz-j          #+#    #+#             */
/*   Updated: 2025/09/03 11:16:34 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// Función principal del programa BSQ.
// Recorre los archivos pasados por argumento, resuelve cada mapa y lo imprime.
int main(int argc, char **argv)
{
    int         i;      // Índice para recorrer los argumentos
    t_map       map;    // Estructura que contiene el mapa
    t_square    sq;     // Estructura que guarda el cuadrado más grande

    // Verifica que se haya pasado al menos un archivo como argumento
    if (argc < 2)
        return (1); // Si no hay archivos, termina con error

    i = 1;
    while (i < argc)
    {
        // Intenta leer y validar el mapa desde el archivo actual
        if (!read_map(argv[i], &map) || !validate_map(&map))
            // Si falla, imprime mensaje de error
            write(1, "map error\n", 10);
        else
        {
            // Inicializa el cuadrado más grande
            sq.size = 0;

            // Aplica el algoritmo para encontrar el cuadrado más grande
            solve_map(&map, &sq);

            // Imprime el mapa con el cuadrado marcado
            print_map(&map, sq);
        }

        // Libera la memoria del mapa antes de pasar al siguiente archivo
        free_map(&map);
        i++;
    }

    // Termina el programa correctamente
    return (0);
}
