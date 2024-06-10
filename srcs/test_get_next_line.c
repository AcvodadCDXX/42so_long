#include "so_long.h"

int main(void)
{
    int fd = open("example1.ber", O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    char *line;
    while (get_next_line(fd, &line) > 0)
    {
        printf("Read line: %s\n", line);
        free(line);
    }
    close(fd);
    return 0;
}
