#include "so_long.h"

int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
        handle_error("Usage: ./so_long <map_file>");

    game.map = read_map(argv[1], &game.map_height, &game.map_width);
    validate_map_elements(game.map, game.map_height, game.map_width);
    validate_map_path(game.map, game.map_height, game.map_width);

    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, game.map_width * game.img_width, game.map_height * game.img_height, "so_long");
    game.player_img = mlx_xpm_file_to_image(game.mlx, "player.xpm", &game.img_width, &game.img_height);
    game.collectible_img = mlx_xpm_file_to_image(game.mlx, "collectible.xpm", &game.img_width, &game.img_height);
    game.wall_img = mlx_xpm_file_to_image(game.mlx, "wall.xpm", &game.img_width, &game.img_height);
    game.exit_img = mlx_xpm_file_to_image(game.mlx, "exit.xpm", &game.img_width, &game.img_height);
    game.background_img = mlx_xpm_file_to_image(game.mlx, "background.xpm", &game.img_width, &game.img_height);

    render_map(&game);

    mlx_loop(game.mlx);
    return (0);
}
