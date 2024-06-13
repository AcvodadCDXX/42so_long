#include <mlx.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    void *img;
    int width;
    int height;
    int bpp;
    int size_line;
    int endian;
    char *data;
} t_image;

void put_pixel_to_image(t_image *img, int x, int y, int color) {
    if (x >= 0 && x < img->width && y >= 0 && y < img->height) {
        *(uint32_t *)(img->data + (y * img->size_line + x * (img->bpp / 8))) = color;
    }
}

int blend_colors(int bg_color, int fg_color) {
    int alpha = (fg_color >> 24) & 0xFF;
    if (alpha == 0) return bg_color; // fully transparent pixel
    if (alpha == 255) return fg_color; // fully opaque pixel

    int inv_alpha = 255 - alpha;

    int bg_r = (bg_color >> 16) & 0xFF;
    int bg_g = (bg_color >> 8) & 0xFF;
    int bg_b = bg_color & 0xFF;

    int fg_r = (fg_color >> 16) & 0xFF;
    int fg_g = (fg_color >> 8) & 0xFF;
    int fg_b = fg_color & 0xFF;

    int r = (fg_r * alpha + bg_r * inv_alpha) / 255;
    int g = (fg_g * alpha + bg_g * inv_alpha) / 255;
    int b = (fg_b * alpha + bg_b * inv_alpha) / 255;

    return (r << 16) | (g << 8) | b;
}

void blend_images(t_image *bg, t_image *fg, t_image *result) {
    for (int y = 0; y < bg->height; y++) {
        for (int x = 0; x < bg->width; x++) {
            int bg_color = *(uint32_t *)(bg->data + (y * bg->size_line + x * (bg->bpp / 8)));
            int fg_color = *(uint32_t *)(fg->data + (y * fg->size_line + x * (fg->bpp / 8)));
            int blended_color = blend_colors(bg_color, fg_color);
            put_pixel_to_image(result, x, y, blended_color);
        }
    }
}

int main() {
    void *mlx = mlx_init();
    if (!mlx) return EXIT_FAILURE;

    void *win = mlx_new_window(mlx, 128, 128, "Test Transparency");
    if (!win) return EXIT_FAILURE;

    t_image bg, fg, result;

    bg.img = mlx_xpm_file_to_image(mlx, "assets/images/background/background.xpm", &bg.width, &bg.height);
    fg.img = mlx_xpm_file_to_image(mlx, "assets/images/player/player.xpm", &fg.width, &fg.height);

    if (!bg.img || !fg.img) return EXIT_FAILURE;

    bg.data = mlx_get_data_addr(bg.img, &bg.bpp, &bg.size_line, &bg.endian);
    fg.data = mlx_get_data_addr(fg.img, &fg.bpp, &fg.size_line, &fg.endian);

    result.img = mlx_new_image(mlx, bg.width, bg.height);
    result.data = mlx_get_data_addr(result.img, &result.bpp, &result.size_line, &result.endian);

    blend_images(&bg, &fg, &result);

    mlx_put_image_to_window(mlx, win, result.img, 0, 0);
    mlx_loop(mlx);

    return 0;
}
