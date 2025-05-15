#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND 256

void create_file(const char *path) {
    FILE *file = fopen(path, "w");
    if (file) {
        printf("Файл %s создан.\n", path);
        fclose(file);
    } else {
        perror("Ошибка при создании файла");
    }
}

void delete_file(const char *path) {
    if (remove(path) == 0) {
        printf("Файл %s удален.\n", path);
    } else {
        perror("Ошибка при удалении файла");
    }
}

void modify_file(const char *path) {
    FILE *file = fopen(path, "a");
    if (!file) {
        perror("Ошибка при открытии файла");
        return;
    }
    printf("Введите текст для добавления: ");
    char buffer[256];
    fgets(buffer, sizeof(buffer), stdin);
    fputs(buffer, file);
    fclose(file);
    printf("Файл %s изменён.\n", path);
}

void view_file(const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) {
        perror("Ошибка при открытии файла");
        return;
    }
    printf("Содержимое файла %s:\n", path);
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
    printf("\n");
}

int main() {
    char input[MAX_COMMAND];
    char command[32], argument[224];

    while (1) {
        printf("> ");
        if (!fgets(input, sizeof(input), stdin)) break;

        if (sscanf(input, "%31s %223[^\n]", command, argument) < 1) continue;

        if (strcmp(command, "создать") == 0) {
            create_file(argument);
        } else if (strcmp(command, "удалить") == 0) {
            delete_file(argument);
        } else if (strcmp(command, "изменить") == 0) {
            modify_file(argument);
        } else if (strcmp(command, "посмотреть") == 0) {
            view_file(argument);
        } else if (strcmp(command, "выйти") == 0) {
            printf("Выход из программы.\n");
            break;
        } else {
            printf("Неизвестная команда: %s\n", command);
        }
    }

    return 0;
}
