#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// C2 1.1. Открыть или создать файл
FILE* open_fs_file(const char* filename) {
    FILE* file = fopen(filename, "r+");
    if (!file) file = fopen(filename, "w+");
    return file;
}

// 1.2. Посмотреть файл
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

// 1.3. Удалить файл
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





// C3 1.1. Новый файл
void add_new_file(FILE* fs, const char* filename, const char* content) {
    fseek(fs, 0, SEEK_END); // Перемещаемся в конец файла

    // Записываем имя нового файла в файловую систему
    fprintf(fs, "\n/%s\n", filename);

    // Записываем содержимое файла
    fprintf(fs, "%s\n", content);

    fflush(fs); // Обновляем файл
}

// 1.2. Изменить файл
void modify_file(FILE* fs, const char* filename, const char* new_content) {
    fseek(fs, 0, SEEK_END); // Перемещаемся в конец файла
    long size = ftell(fs);  // Получаем размер файла
    rewind(fs);             // Возвращаем указатель в начало

    char* buffer = malloc(size + 1);
    if (!buffer) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return;
    }

    fread(buffer, 1, size, fs);  // Читаем файл в буфер
    buffer[size] = '\0';          // Завершаем строку

    // Временный файл для записи изменений
    char* temp_filename = "temp_fs.txt";
    FILE* temp_fs = fopen(temp_filename, "w+");
    if (!temp_fs) {
        fprintf(stderr, "Ошибка открытия временного файла\n");
        free(buffer);
        return;
    }

    char* line = strtok(buffer, "\n");
    int found = 0;

    while (line) {
        if (line[0] == '/' && strcmp(line + 1, filename) == 0) {
            found = 1;  // Нашли файл
            fprintf(temp_fs, "/%s\n", filename);  // Записываем название файла
            fprintf(temp_fs, "%s\n", new_content);  // Записываем новое содержимое
        } else if (line[0] == '/' && found) {
            found = 0;  // Пропускаем старое содержимое файла
        } else {
            fprintf(temp_fs, "%s\n", line);  // Записываем остальные строки
        }

        line = strtok(NULL, "\n");
    }

    fclose(temp_fs);  // Закрываем временный файл

    // Удаляем старый файл и переименовываем временный
    remove("filesystem.txt");
    rename(temp_filename, "filesystem.txt");

    free(buffer);
}
