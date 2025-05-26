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

    return 0;
}
