/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:10:30 by gortiz-j          #+#    #+#             */
/*   Updated: 2025/09/03 10:54:59 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
// Convierte una cadena numérica (como "42") en un entero.
// Se usa para leer el número de filas del mapa desde la primera línea del archivo.
int ft_atoi(char *str)
{
    int n;

    n = 0;
    // Mientras el carácter actual sea un dígito ('0' a '9')
    while (*str >= '0' && *str <= '9')
    {
        // Multiplica el número actual por 10 y suma el valor del nuevo dígito
        // Ejemplo: si n = 4 y *str = '2', entonces n = 4 * 10 + 2 = 42
        n = n * 10 + (*str - '0');
        // Avanza al siguiente carácter
        str++;
    }
    // Devuelve el número convertido
    return (n);
}

// Extrae la información del encabezado del mapa y la guarda en la estructura t_map.
// El encabezado tiene el formato: "<num_filas><empty><obstacle><full>", por ejemplo "10.ox".
int parse_header(char *line, t_map *map)
{
    int len;

    // Calcula la longitud de la línea del encabezado
    len = ft_strlen(line);

    // Verifica que la línea tenga al menos 4 caracteres (mínimo válido)
    if (len < 4)
        return (0);

    // Convierte la parte numérica inicial en entero: número de filas del mapa
    map->rows = ft_atoi(line);

    // Extrae los tres últimos caracteres:
    // - El carácter que representa una celda vacía
    map->empty = line[len - 3];
    // - El carácter que representa un obstáculo
    map->obstacle = line[len - 2];
    // - El carácter que se usará para marcar el cuadrado más grande
    map->full = line[len - 1];

    // Devuelve 1 si el encabezado fue procesado correctamente
    return (1);
}
// Calcula la longitud de una cadena de caracteres (sin contar el '\0').
// Se usa para saber cuántos caracteres tiene una línea del mapa o el encabezado.
int ft_strlen(char *str)
{
    int i;

    // Inicializa el contador en 0
    i = 0;

    // Recorre la cadena hasta encontrar el carácter nulo '\0'
    while (str[i])
        i++;

    // Devuelve la cantidad de caracteres recorridos
    return (i);
}

// Crea una copia exacta de la cadena 'src' en memoria dinámica.
// Se usa para duplicar líneas del mapa al construir la matriz 'grid'.
char    *ft_strdup(char *src)
{
    int     i;
    char    *dup;

    // Calcula la longitud de la cadena original
    i = ft_strlen(src);

    // Reserva memoria suficiente para la copia (incluye espacio para '\0')
    dup = malloc(i + 1);
    if (!dup)
        return (NULL);

    // Copia cada carácter de 'src' a 'dup'
    i = 0;
    while (src[i])
    {
        dup[i] = src[i];
        i++;
    }

    // Añade el carácter nulo al final para cerrar la cadena
    dup[i] = '\0';

    // Devuelve el puntero a la nueva cadena duplicada
    return (dup);
}


// Imprime el mapa en pantalla, reemplazando el cuadrado más grande con el carácter 'full'.
void    print_map(t_map *map, t_square sq)
{
    int i;
    int j;

    // Recorre cada fila del mapa
    i = 0;
    while (i < map->rows)
    {
        // Recorre cada columna de la fila actual
        j = 0;
        while (j < map->cols)
        {
            // Verifica si la celda actual está dentro del cuadrado más grande
            if (i >= sq.y - sq.size + 1 && i <= sq.y
                && j >= sq.x - sq.size + 1 && j <= sq.x)
                // Si está dentro del cuadrado, imprime el carácter 'full'
                write(1, &map->full, 1);
            else
                // Si no, imprime el carácter original del mapa
                write(1, &map->grid[i][j], 1);
            j++;
        }
        // Imprime salto de línea al final de cada fila
        write(1, "\n", 1);
        i++;
    }
}


// Libera toda la memoria dinámica asociada al mapa.
// Se llama al final del programa para evitar fugas de memoria.
void    free_map(t_map *map)
{
    int i;

    // Recorre cada fila del mapa
    i = 0;
    while (i < map->rows)
    {
        // Libera la memoria de cada línea del mapa
        free(map->grid[i]);
        i++;
    }
    // Libera el array principal que contiene los punteros a cada fila
    free(map->grid);
}
