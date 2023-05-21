#include <unistd.h>

#include <stdio.h>
#include <fcntl.h>

#include <errno.h>

int main() {
    char* path = "file_name.txt";
    char link[] = "aaaaaaaaa.txt";
    char prev_link[] = "aaaaaaaaa.txt";

    int fd;
    if ((fd = creat(path, S_IRUSR | S_IWUSR)) < 0) {
        perror("creat() error");
        return 1;
    }

    close(fd);

    int pointer = 0;
    int amount = 1;
    remove(link);
    if (symlink(path, link) != 0) {
        perror("symlink() error");
    }
    link[pointer]++;
    amount++;

    for (int i = 0; i < 100; ++i) {
        remove(link);
        if (symlink(prev_link, link) != 0) {
            perror("symlink() error");
        }

        if (access(link, F_OK) == -1) {
            break;
        }

        if (link[pointer] == 'z') {
            pointer++;
            prev_link[pointer - 1]++;
            prev_link[pointer]--;
        }

        prev_link[pointer]++;
        link[pointer]++;
        amount++;
    }

    printf("%d\n", amount);
}