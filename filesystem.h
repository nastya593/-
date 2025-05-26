#ifndef FILESYSTEM_H
#define FILESYSTEM_H

typedef struct {
    char *name;     // Имя файла
    char *content;  // Содержимое файла
} FileEntry;

typedef struct {
    FileEntry *entries;   // Массив файлов
    size_t     count;     // Количество файлов
} FileSystem;

/* Загрузка / сохранение / освобождение */
int  fs_load(const char *fname, FileSystem *fs);
int  fs_save(const char *fname, const FileSystem *fs);
void fs_free(FileSystem *fs);

/* CRUD операции */
int  read_file(const FileSystem *fs, const char *filename, char **out_content);
int  add_file_to_fs(FileSystem *fs, const char *filename);
int  modify_file_in_fs(FileSystem *fs, const char *filename, const char *new_content);
int  delete_file(FileSystem *fs, const char *filename);

/* Новые функции */
int  fs_count(const FileSystem *fs);
int  fs_rename(FileSystem *fs, const char *old_name, const char *new_name);

#endif /* FILESYSTEM_H */
