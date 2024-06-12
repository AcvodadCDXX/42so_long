#include "so_long.h"

void load_images(t_game *game)
{
    int width, height;

    game->player_img = mlx_xpm_file_to_image(game->mlx, "assets/images/player/player.xpm", &width, &height);
    if (!game->player_img)
        ft_putendl_fd("Error: Failed to load player.xpm", 2);
    
    game->collectible_img = mlx_xpm_file_to_image(game->mlx, "assets/images/collectibles/collectible.xpm", &width, &height);
    if (!game->collectible_img)
        ft_putendl_fd("Error: Failed to load collectible.xpm", 2);
    
    game->wall_img = mlx_xpm_file_to_image(game->mlx, "assets/images/wall/wall.xpm", &width, &height);
    if (!game->wall_img)
        ft_putendl_fd("Error: Failed to load wall.xpm", 2);
    
    game->exit_img = mlx_xpm_file_to_image(game->mlx, "assets/images/exit/exit.xpm", &width, &height);
    if (!game->exit_img)
        ft_putendl_fd("Error: Failed to load exit.xpm", 2);
    
    game->background_img = mlx_xpm_file_to_image(game->mlx, "assets/images/background/background.xpm", &width, &height);
    if (!game->background_img)
        ft_putendl_fd("Error: Failed to load background.xpm", 2);
    
    if (!game->player_img || !game->collectible_img || !game->wall_img || !game->exit_img || !game->background_img)
        handle_error("Error: Failed to load images");
}

// Function to initialize game and create window
int init_game(t_game *game, char *map_file)
{
    size_t rows, cols;

    game->mlx = mlx_init();
    if (!game->mlx)
        handle_error("Error: MLX initialization failed");

    game->map = read_map(map_file, &rows, &cols);
    game->map_height = rows;
    game->map_width = cols;
    game->img_width = 64; // Assuming 64x64 images
    game->img_height = 64;

    game->win = mlx_new_window(game->mlx, game->map_width * game->img_width, game->map_height * game->img_height, "so_long");
    if (!game->win)
        handle_error("Error: Window creation failed");

    load_images(game);
    return (0);
}

// Function to render the map
void render_map(t_game *game)
{
    size_t i, j;

    for (i = 0; i < game->map_height; i++)
    {
        for (j = 0; j < game->map_width; j++)
        {
            char tile = game->map[i][j];
            if (tile == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->wall_img, j * game->img_width, i * game->img_height);
            else if (tile == '0')
                mlx_put_image_to_window(game->mlx, game->win, game->background_img, j * game->img_width, i * game->img_height);
            else if (tile == 'P')
                mlx_put_image_to_window(game->mlx, game->win, game->player_img, j * game->img_width, i * game->img_height);
            else if (tile == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->collectible_img, j * game->img_width, i * game->img_height);
            else if (tile == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->exit_img, j * game->img_width, i * game->img_height);
        }
    }
}

int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
        handle_error("Usage: ./so_long <map_file>");
    
    init_game(&game, argv[1]);
    render_map(&game);

    mlx_loop(game.mlx);
    return (0);
}
