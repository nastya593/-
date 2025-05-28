#include <stdio.h>
#include <stdlib.h>
#include "filesystem.h"

int main() {
    const char *fs_filename = "filesystem.txt";
    FileSystem fs = {NULL, 0};

    if (fs_load(fs_filename, &fs) != 0) {
        printf("Не удалось загрузить файловую систему. Создаю новую.\n");
        fs.entries = NULL;
        fs.count = 0;
    } else {
        printf("Файловая система успешно загружена.\n");
    }

    const char *new_file_name = "example.txt";
    if (add_file_to_fs(&fs, new_file_name) == 0) {
        printf("Файл '%s' добавлен.\n", new_file_name);
    } else {
        printf("Ошибка при добавлении файла '%s'.\n", new_file_name);
    }

    const char *content = "Это пример содержимого файла.";
    if (modify_file_in_fs(&fs, new_file_name, content) == 0) {
        printf("Содержимое файла '%s' обновлено.\n", new_file_name);
    } else {
        printf("Ошибка при обновлении содержимого файла '%s'.\n", new_file_name);
    }

    char *read_content = NULL;
    if (read_file(&fs, new_file_name, &read_content) == 0 && read_content != NULL) {
        printf("Содержимое файла '%s': %s\n", new_file_name, read_content);
        free(read_content);
    } else {
        printf("Не удалось прочитать файл '%s'.\n", new_file_name);
    }

    if (delete_file(&fs, new_file_name) == 0) {
        printf("Файл '%s' удален.\n", new_file_name);
    } else {
        printf("Ошибка при удалении файла '%s'.\n", new_file_name);
    }

    if (fs_save(fs_filename, &fs) != 0) {
        printf("Ошибка при сохранении файловой системы.\n");
    } else {
        printf("Файловая система успешно сохранена.\n");
    }

    fs_free(&fs);

 {
    FILE *file = fopen("example.txt", "w"); 
    if (file == NULL) {
        printf("Ошибка при создании файла\n");
        return 1;
    }
    fprintf(file, "Привет, файл!\n"); 
    fclose(file);
    {
    const char *filename = "example.txt";
    if (remove(filename) == 0) {
        printf("Файл успешно удалён\n");
    } else {
        printf("Ошибка при удалении файла\n");
    }

void modify_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Ошибка при открытии файла: %s\n", filename);
        return;
    }
    fprintf(file, "%s\n", content); 
    printf("Содержимое добавлено в файл: %s\n", filename);

    fclose(file); 
}
#include <stdio.h>

void view_file(const char *filename) {
    FILE *file = fopen(filename, "r"); 
    if (file == NULL) {
        printf("Ошибка при открытии файла: %s\n", filename);
        return;
    }
    char line[256]; 

    printf("Содержимое файла %s:\n", filename);
    while (fgets(line, sizeof(line), file)) { 
        printf("%s", line); 
    }
    fclose(file); 
}
    return 0;
}


void create_file(const char *path) {
    FILE *file = fopen(path, "w");
    if (file) {
        fprintf(file, ""); 
        fclose(file);
        printf("Файл %s создан.\n", path);
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
void modify_file(const char *path, const char *text) {
    FILE *file = fopen(path, "a");
    if (file) {
        fprintf(file, "%s\n", text);
        fclose(file);
        printf("Файл %s изменен.\n", path);
    } else {
        perror("Ошибка при изменении файла");
    }
}
void view_file(const char *path) {
    char ch;
    FILE *file = fopen(path, "r");
    if (file) {
        while ((ch = fgetc(file)) != EOF) {
            putchar(ch);
        }
        fclose(file);
    } else {
        perror("Ошибка при просмотре файла");
    }
}
int main() {
    char command[256];
    while (1) {
        printf("> ");
        scanf(" %[^\n]", command); 

        char *token = strtok(command, " ");
        if (token) {
            if (strcmp(token, "создать") == 0) {
                token = strtok(NULL, " ");
                create_file(token);
            } else if (strcmp(token, "удалить") == 0) {
                token = strtok(NULL, " ");
                delete_file(token);
            } else if (strcmp(token, "изменить") == 0) {
                token = strtok(NULL, " ");
                char *text = strtok(NULL, "\0"); 
                modify_file(token, text);
            } else if (strcmp(token, "посмотреть") == 0) {
                token = strtok(NULL, " ");
                view_file(token);
            } else {
                printf("Неизвестная команда.\n");
            }
        }
    }
    return 0;
}


