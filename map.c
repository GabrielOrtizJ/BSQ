/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gortiz-j <gortiz-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:10:20 by gortiz-j          #+#    #+#             */
/*   Updated: 2025/09/03 11:15:52 by gortiz-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// Lee el archivo del mapa, lo divide en líneas, interpreta el encabezado
// y llena la estructura t_map con los datos necesarios para resolver el mapa.
int read_map(char *filename, t_map *map)
{
    char    buf[10000];     // Buffer donde se carga el contenido del archivo
    char    **lines;         // Array de líneas separadas del mapa
    int     line_count;     // Número total de líneas encontradas

    // Intenta leer el archivo completo en el buffer
    if (!read_file_to_buffer(filename, buf))
        return (0); // Error al abrir o leer el archivo

    // Divide el contenido del buffer en líneas usando '\n' como separador
    lines = split_lines_custom(buf, &line_count);
    if (!lines || !parse_header(lines[0], map))
        return (0); // Error al dividir líneas o al interpretar el encabezado

    // Copia las líneas del mapa (excluyendo el encabezado) en map->grid
    if (!fill_grid(lines + 1, map))
        return (0); // Error al construir la matriz del mapa

    // Si todo salió bien, devuelve 1
    return (1);
}

// Verifica que el mapa sea válido:
// - Que tenga dimensiones correctas
// - Que todas las líneas tengan la misma longitud
// - Que solo contenga caracteres válidos
// - Que los símbolos del encabezado sean distintos entre sí
int validate_map(t_map *map)
{
    int i;
    int j;

    // Verifica que el mapa esté inicializado correctamente
    if (!map->grid || map->rows <= 0 || map->cols <= 0)
        return (0);

    i = 0;
    while (i < map->rows)
    {
        // Verifica que cada línea tenga la misma cantidad de columnas
        if (ft_strlen(map->grid[i]) != map->cols)
            return (0);

        j = 0;
        while (j < map->cols)
        {
            // Verifica que cada carácter sea 'empty' o 'obstacle'
            if (map->grid[i][j] != map->empty &&
                map->grid[i][j] != map->obstacle)
                return (0);
            j++;
        }
        i++;
    }

    // Verifica que los tres símbolos del encabezado sean distintos
    if (map->empty == map->obstacle || map->empty == map->full
        || map->obstacle == map->full)
        return (0);

    // Si todo está correcto, devuelve 1
    return (1);
}


// Copia una porción del buffer 'buf' desde la posición 'start' hasta 'end - 1'.
// Devuelve una nueva cadena con esa porción, terminada en '\0'.
char    *copy_line(char *buf, int start, int end)
{
    char    *line;
    int     i;

    // Reserva memoria para la nueva línea (incluye espacio para el '\0')
    line = malloc(end - start + 1);
    if (!line)
        return (NULL);

    // Copia carácter por carácter desde 'buf' a 'line'
    i = 0;
    while (start < end)
        line[i++] = buf[start++];

    // Añade el carácter nulo al final para cerrar la cadena
    line[i] = '\0';

    // Devuelve el puntero a la nueva línea copiada
    return (line);
}

// Divide el contenido del buffer 'buf' en líneas separadas usando el carácter '\n'.
// Guarda cada línea en memoria dinámica dentro del array 'lines'.
// Actualiza '*line_count' con el número total de líneas encontradas.
char    **split_lines_custom(char *buf, int *line_count)
{
    char    **lines;   // Array de punteros a cada línea separada
    int     i;         // Índice para recorrer el buffer
    int     start;     // Posición inicial de la línea actual
    int     index;     // Índice para insertar en 'lines'
    int     j;         // Índice para copiar caracteres en cada línea

    // Reserva espacio para hasta 1000 líneas (puedes ajustar este número si lo necesitas)
    lines = malloc(sizeof(char *) * 1000);
    if (!lines)
        return (NULL);

    i = 0;
    start = 0;
    index = 0;

    // Recorre el buffer carácter por carácter
    while (buf[i])
    {
        // Si encuentra un salto de línea, extrae la línea
        if (buf[i] == '\n')
        {
            // Reserva memoria para la línea actual
            lines[index] = malloc(i - start + 1);
            if (!lines[index])
                return (NULL);

            // Copia los caracteres desde 'start' hasta 'i - 1' en la nueva línea
            j = 0;
            while (start < i)
                lines[index][j++] = buf[start++];

            // Termina la línea con '\0' y avanza al siguiente índice
            lines[index++][j] = '\0';

            // Salta el '\n' para comenzar la siguiente línea
            start = i + 1;
        }
        i++;
    }

    // Marca el final del array con NULL
    lines[index] = NULL;

    // Actualiza el contador de líneas
    *line_count = index;

    // Devuelve el array de líneas
    return (lines);
}


// Lee el contenido de un archivo y lo guarda en el buffer 'buf'.
// Se usa para cargar el mapa desde un archivo antes de procesarlo.
int read_file_to_buffer(char *filename, char *buf)
{
    int     fd;     // Descriptor de archivo
    int     bytes;  // Número de bytes leídos

    // Abre el archivo en modo solo lectura
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        // Si no se pudo abrir, devuelve error
        return (0);

    // Lee hasta n bytes del archivo y los guarda en 'buf'
    bytes = read(fd, buf, 999999);

    // Cierra el archivo después de leer
    close(fd);

    // Si no se leyó nada o hubo error, devuelve error
    if (bytes <= 0)
        return (0);

    // Añade el carácter nulo al final del buffer para convertirlo en cadena válida
    buf[bytes] = '\0';

    // Devuelve 1 si la lectura fue exitosa
    return (1);
}

// Copia las líneas del mapa en memoria dinámica dentro de la estructura t_map.
// Construye la matriz 'grid' y calcula el número de columnas.
int fill_grid(char **lines, t_map *map)
{
    int i;

    // Reserva memoria para el array de punteros a cada fila del mapa
    map->grid = malloc(sizeof(char *) * map->rows);
    if (!map->grid)
        return (0);

    // Copia cada línea del mapa usando ft_strdup
    i = 0;
    while (i < map->rows && lines[i])
    {
        map->grid[i] = ft_strdup(lines[i]);
        i++;
    }

    // Calcula el número de columnas usando la primera fila
    map->cols = ft_strlen(map->grid[0]);

    // Devuelve 1 si todo se ha copiado correctamente
    return (1);
}
