#include "so_long.h"

void handle_error(const char *message)
{
    ft_putendl_fd("Error", 2);
    ft_putendl_fd((char *)message, 2);
    exit(EXIT_FAILURE);
}

char **read_map(const char *filename, size_t *rows, size_t *cols)
{
    int     fd;
    char    *line;
    char    **map;
    size_t  row_count;
    size_t  col_count;
    ssize_t gnl_result;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        handle_error("Error: Unable to open file");

    map = malloc(sizeof(char *) * 100); // Assume a max of 100 lines for simplicity
    if (!map)
        handle_error("Error: Memory allocation failed");

    row_count = 0;
    col_count = 0;
    while ((gnl_result = get_next_line(fd, &line)) > 0)
    {
        if (row_count == 0)
            col_count = ft_strlen(line);
        else if (ft_strlen(line) != col_count)
            handle_error("Error: Map is not rectangular");

        map[row_count++] = line;
    }

    // Handle the last line if it was not followed by a newline character
    if (gnl_result == 0 && line && *line)
    {
        if (row_count == 0)
            col_count = ft_strlen(line);
        else if (ft_strlen(line) != col_count)
            handle_error("Error: Map is not rectangular");

        map[row_count++] = line;
    }

    map[row_count] = NULL;
    close(fd);
    *rows = row_count;
    *cols = col_count;

    // Debug: Print map dimensions and content
    ft_putstr_fd("Map dimensions: ", 1);
    ft_putnbr_fd(*rows, 1);
    ft_putstr_fd(" x ", 1);
    ft_putnbr_fd(*cols, 1);
    ft_putendl_fd("", 1);

    for (size_t i = 0; i < *rows; i++)
    {
        ft_putendl_fd(map[i], 1);
    }

    return (map);
}

void validate_map_elements(char **map, size_t rows, size_t cols)
{
    size_t i, j;
    int start_count = 0, exit_count = 0, collect_count = 0;

    // Check the first and last rows for walls
    for (j = 0; j < cols; j++)
    {
        if (map[0][j] != '1')
        {
            ft_putstr_fd("Error: Map is not enclosed by walls at (0, ", 2);
            ft_putnbr_fd(j, 2);
            ft_putendl_fd(")", 2);
            handle_error("Error: Map is not enclosed by walls");
        }
        if (map[rows - 1][j] != '1')
        {
            ft_putstr_fd("Error: Map is not enclosed by walls at (", 2);
            ft_putnbr_fd(rows - 1, 2);
            ft_putstr_fd(", ", 2);
            ft_putnbr_fd(j, 2);
            ft_putendl_fd(")", 2);
            handle_error("Error: Map is not enclosed by walls");
        }
    }

    // Check the first and last columns for walls
    for (i = 0; i < rows; i++)
    {
        if (map[i][0] != '1')
        {
            ft_putstr_fd("Error: Map is not enclosed by walls at (", 2);
            ft_putnbr_fd(i, 2);
            ft_putstr_fd(", 0)", 2);
            handle_error("Error: Map is not enclosed by walls");
        }
        if (map[i][cols - 1] != '1')
        {
            ft_putstr_fd("Error: Map is not enclosed by walls at (", 2);
            ft_putnbr_fd(i, 2);
            ft_putstr_fd(", ", 2);
            ft_putnbr_fd(cols - 1, 2);
            ft_putendl_fd(")", 2);
            handle_error("Error: Map is not enclosed by walls");
        }
    }

    // Count elements and check for invalid characters
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (map[i][j] == 'P')
                start_count++;
            else if (map[i][j] == 'E')
                exit_count++;
            else if (map[i][j] == 'C')
                collect_count++;
            else if (map[i][j] != '0' && map[i][j] != '1')
            {
                ft_putstr_fd("Invalid character '", 2);
                write(2, &map[i][j], 1);
                ft_putstr_fd("' at position (", 2);
                ft_putnbr_fd(i, 2);
                ft_putstr_fd(", ", 2);
                ft_putnbr_fd(j, 2);
                ft_putendl_fd(")", 2);
                handle_error("Error: Invalid character in map");
            }
        }
    }
    
    if (start_count != 1 || exit_count != 1 || collect_count < 1)
        handle_error("Error: Invalid map elements count");
}

void flood_fill(char **map, int x, int y, int *collectibles, int *exit)
{
    if (x < 0 || y < 0 || !map[y] || map[y][x] == '\0' || map[y][x] == '1')
        return;

    if (map[y][x] == 'C')
        (*collectibles)--;
    else if (map[y][x] == 'E')
        (*exit)--;

    map[y][x] = '1'; // Mark as visited

    flood_fill(map, x + 1, y, collectibles, exit);
    flood_fill(map, x - 1, y, collectibles, exit);
    flood_fill(map, x, y + 1, collectibles, exit);
    flood_fill(map, x, y - 1, collectibles, exit);
}

void validate_map_path(char **map, size_t rows, size_t cols)
{
    int collectibles = 0, exit = 0;
    size_t i, j;
    int start_x = -1, start_y = -1;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (map[i][j] == 'C')
                collectibles++;
            else if (map[i][j] == 'E')
                exit++;
            else if (map[i][j] == 'P')
            {
                start_x = j;
                start_y = i;
            }
        }
    }
    if (start_x == -1 || start_y == -1)
        handle_error("Error: Start position not found");

    flood_fill(map, start_x, start_y, &collectibles, &exit);

    if (collectibles != 0 || exit != 0)
        handle_error("Error: No valid path in the map");
}

void render_map(t_game *game)
{
    size_t i, j;
    for (i = 0; i < game->map_height; i++)
    {
        for (j = 0; j < game->map_width; j++)
        {
            if (game->map[i][j] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->wall_img, j * game->img_width, i * game->img_height);
            else if (game->map[i][j] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->collectible_img, j * game->img_width, i * game->img_height);
            else if (game->map[i][j] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->exit_img, j * game->img_width, i * game->img_height);
            else if (game->map[i][j] == 'P')
                mlx_put_image_to_window(game->mlx, game->win, game->player_img, j * game->img_width, i * game->img_height);
            else
                mlx_put_image_to_window(game->mlx, game->win, game->background_img, j * game->img_width, i * game->img_height);
        }
    }
}
