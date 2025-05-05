#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Открыть или создать файл
FILE* open_fs_file(const char* filename) {
    FILE* file = fopen(filename, "r+");
    if (!file) file = fopen(filename, "w+");
    return file;
}

// 2. Посмотреть файл
char* view_file_from_fs(FILE* fs, const char* target_filename) {
    fseek(fs, 0, SEEK_END);
    long size = ftell(fs);
    rewind(fs);

    char* buffer = malloc(size + 1);
    fread(buffer, 1, size, fs);
    buffer[size] = '\0';

    char* line = strtok(buffer, "\n");
    int found = 0;
    char* result = malloc(size + 1);
    result[0] = '\0';

    while (line) {
        if (line[0] == '/' && strcmp(line + 1, target_filename) == 0) {
            found = 1;
        } else if (line[0] == '/' && found) {
            break;
        } else if (found) {
            strcat(result, line);
            strcat(result, "\n");
        }
        line = strtok(NULL, "\n");
    }

    free(buffer);
    return found ? result : NULL;
}

// 3. Удалить файл
void delete_file_from_fs(FILE* fs, const char* target_filename) {
    fseek(fs, 0, SEEK_END);
    long size = ftell(fs);
    rewind(fs);

    char* buffer = malloc(size + 1);
    fread(buffer, 1, size, fs);
    buffer[size] = '\0';

    char* new_buffer = malloc(size + 1);
    new_buffer[0] = '\0';

    char* line = strtok(buffer, "\n");
    int skip = 0;

    while (line) {
        if (line[0] == '/' && strcmp(line + 1, target_filename) == 0) {
            skip = 1;
        } else if (line[0] == '/' && skip) {
            skip = 0;
        }

        if (!skip) {
            strcat(new_buffer, line);
            strcat(new_buffer, "\n");
        }

        line = strtok(NULL, "\n");
    }

    freopen(NULL, "w+", fs);
    fputs(new_buffer, fs);

    free(buffer);
    free(new_buffer);
}
