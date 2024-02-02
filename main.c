#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define EXITMSG(msg) do { \
        perror(msg); \
        exit(EXIT_FAILURE); } while(0)

int main(){

    // Открытие файла для записи с режимом создания
    const char filename[] = "myfile.txt";
    int fd = open(filename, O_WRONLY, O_CREAT);
    if (fd == -1)
        // Если файл уже существует
        if (errno == EEXIST)
            remove(filename);
        else{
            perror("Unhandled error opening for write file ");
            exit(EXIT_FAILURE);
        }
    
    // Запись в файл
    const char text[] = "Hello, world!\n";
    int bytes_written=  write(fd, (void*)text, sizeof(text)); 
    if (bytes_written == -1) {
        perror("Unhandled error writing file ");
        exit(EXIT_FAILURE);
    }
    printf("Written to a file: '%.*s'\n", (int)sizeof(text)-1, text); // -1 for exclude '\0'

    // Закрытие файла
    close(fd);
    fd = -1;

    // Открытие файла для чтения
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Unhandled error opening for read file ");
        exit(EXIT_FAILURE);
    }

    // Чтение данных из файла
    char buffer[1024];
    int bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("Unhandled error reading file ");
        exit(EXIT_FAILURE);
    }

    // Вывод прочитанных данных
    printf("\nRead from file: '%.*s'\n", bytes_read, buffer);

    // Закрытие файла
    close(fd);

    return 0;
}