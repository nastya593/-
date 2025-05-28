# Гусева Лазарева Петянина 0907-31 
 ## open_or_create_fs
 ### Открытие файла в файловой системе
 ```
 FILE* open_or_create_fs(const char* path) {
    FILE* file = fopen(path, "r+");
    if (!file) {
        file = fopen(path, "w+");
        if (!file) {
            perror("Не удалось открыть или создать файл файловой системы");
            return NULL;
        }
    }
    return file;
}

char* read_full_fs(FILE* file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(size + 1);
    if (!buffer) {
        perror("Ошибка выделения памяти");
        return NULL;
    }

    fread(buffer, 1, size, file);
    buffer[size] = '\0';
    return buffer;
}

void write_full_fs(FILE* file, const char* data) {
    freopen(NULL, "w+", file); // очистить содержимое файла
    fputs(data, file);
    fflush(file);
}
 ```
 ### Параметры, которые принимает функция
 const char* path — строка, указывающая путь к файлу файловой системы.
 ### Параметры, которые возвращает функция
 FILE* — указатель на открытый файл, или NULL, если произошла ошибка.
 ## read_file
 ### Просмотр содержимого файла
 ```
 char* read_file(const char* filename) {
    const char* fs_path = "filesystem.txt";

    FILE* fs = open_or_create_fs(fs_path);
    if (!fs) return NULL;

    char* fs_content = read_full_fs(fs);
    fclose(fs);

    if (!fs_content) return NULL;

    char* line = strtok(fs_content, "\n");
    int found = 0;
    char* result = NULL;

    while (line != NULL) {
        if (strcmp(line, filename) == 0) {
            found = 1;
            line = strtok(NULL, "\n"); 
            if (line != NULL && strcmp(line, "/") != 0) {
                result = strdup(line);
            } else {
                result = strdup("");
            }
            break;
        }
        line = strtok(NULL, "\n");
    }

    free(fs_content);

    if (!found) {
        printf("Файл '%s' не найден.\n", filename);
        return NULL;
    }

    return result; 
}
 ```
 ### Параметры, которые принимает функция
 const char* filename — строка с именем файла, содержимое которого нужно прочитать.
 ### Параметры, которые возвращает функция
 char* — указатель на динамически выделенную строку с содержимым файла, или NULL, если файл не найден или произошла ошибка.
 ## delete_file
 ### Удаление файла
 ```
 int delete_file(const char* filename) {
    const char* fs_path = "filesystem.txt";

    FILE* fs = open_or_create_fs(fs_path);
    if (!fs) return -1;

    char* fs_content = read_full_fs(fs);
    fclose(fs);

    if (!fs_content) return -1;

    char* lines[1024]; // предполагаем максимум 1024 строк
    int count = 0;

    char* temp_str = strdup(fs_content);
    free(fs_content);

    char* token = strtok(temp_str, "\n");
    while (token != NULL && count < 1024) {
        lines[count++] = token;
        token = strtok(NULL, "\n");
    }

    char** new_lines = malloc(sizeof(char*) * (count + 1));
    int new_count = 0;

  while (i < count) {
          if (strcmp(lines[i], filename) == 0) {
              i += 2; 
              continue;
          } else {
              new_lines[new_count++] = lines[i];
              i++;
          }
  }

  if (new_count == 0 || strcmp(new_lines[new_count -1], "/") !=0 ) {
      new_lines[new_count++] = strdup("/");
  }

   FILE* fs_write = fopen(fs_path, "w");
   if (!fs_write) {
       perror("Ошибка открытия файла для записи");
       free(new_lines);
       free(temp_str);
       return -1;
   }

   for (int j=0; j< new_count; j++) {
       fputs(new_lines[j], fs_write);
       fputc('\n', fs_write);
   }

   fclose(fs_write);

   free(new_lines);
   free(temp_str);
 ```
 ### Параметры, которые принимает функция
 const char* filename — строка с именем файла, который нужно удалить.
 ### Параметры, которые возвращает функция
 int — статус выполнения: 0 — успешно удален, -1 — произошла ошибка.
 ## add_file_to_fs
 ### Добавление нового файла
 ```
 int add_file_to_fs(const char* fs_path, const char* filename) {
    FILE *fs = fopen(fs_path, "r+");
    if (!fs) {
        perror("Ошибка открытия файла системы");
        return -1;
    }

    fseek(fs, 0, SEEK_END);
    long size = ftell(fs);
    fseek(fs, 0, SEEK_SET);

    char *content = malloc(size + 1024); 
    if (!content) {
        fclose(fs);
        perror("Ошибка выделения памяти");
        return -1;
    }

    fread(content, 1, size, fs);
    content[size] = '\0';

    strcat(content, "\n");
    strcat(content, filename);

    freopen(fs_path, "w", fs);
    fwrite(content, 1, strlen(content), fs);

    free(content);
    fclose(fs);
    return 0;
}
 ```
 ### Параметры, которые принимает функция
 const char* fs_path — путь к файлу файловой системы.
 const char* filename — имя файла, который нужно добавить.
 ### Параметры, которые возвращает функция
 int — статус выполнения: 0 — успешно добавлен, -1 — произошла ошибка.
 ## modify_file_in_fs
 ### Изменение содержимого файла
 ```
 int modify_file_in_fs(const char* fs_path, const char* filename, const char* new_content) {
    FILE *fs = fopen(fs_path, "r");
    if (!fs) {
        perror("Ошибка открытия файла системы");
        return -1;
    }

    fseek(fs, 0, SEEK_END);
    long size = ftell(fs);
    fseek(fs, 0, SEEK_SET);

    char *content = malloc(size + 1024); 
    if (!content) {
        fclose(fs);
        perror("Ошибка выделения памяти");
        return -1;
    }

    fread(content, 1, size, fs);
    content[size] = '\0';

    fclose(fs);

    char *lines[1024]; 
    int line_count = 0;

    char *ptr = strtok(content, "\n");
    while (ptr != NULL && line_count < 1024) {
        lines[line_count++] = ptr;
        ptr = strtok(NULL, "\n");
    }

    char *new_lines[1024];
    int new_line_count = 0;

    for (int i = 0; i < line_count; i++) {
        if (strcmp(lines[i], filename) != 0) {
            new_lines[new_line_count++] = lines[i];
        }
    }

    new_lines[new_line_count++] = (char*)new_content;

    FILE *write_fs = fopen(fs_path, "w");
    
    if (!write_fs) {
        perror("Ошибка открытия файла для записи");
        return -1;
    }

    for (int i = 0; i < new_line_count; i++) {
        fprintf(write_fs, "%s\n", new_lines[i]);
    }

    fclose(write_fs);
 ```
 ### Параметры, которые принимает функция
 const char* fs_path — путь к файлу файловой системы.
 const char* filename — имя файла, содержимое которого нужно изменить.
 const char* new_content — новое содержимое файла.
 ### Параметры, которые возвращает функция
 int — статус выполнения: 0 — успешно удален, -1 — произошла ошибка.


## Структура проекта
- filesystem.h — заголовочный файл с объявлениями структур и прототипами функций.
- filesystem.c — файл с реализацией всех функций, описанных в filesystem.h.
- main.c — пример использования вашей файловой системы.

## Как подключить и использовать:

1. Включение заголовочного файла
В любом файле вашего проекта, где вы хотите использовать функции файловой системы, добавьте строку: #include "filesystem.h".  
2. Компиляция
При компиляции убедитесь, что компилятор знает о файле реализации filesystem.c.
4. Использование
После подключения (#include "filesystem.h") вы можете создавать объекты типа FileSystem, вызывать функции загрузки, сохранения, добавления/удаления файлов и т.д.

Таким образом, получается библиотека - файл filesystem.c с реализацией всех функций. Данная библиотека подключается через #include "filesystem.h". 
# Использование файловой системы

Команды:

- создать <путь_до_файла> — создать пустой файл
- удалить <путь_до_файла> — удалить файл
- изменить <путь_до_файла> <текст> — записать текст в файл (перезаписать)
- посмотреть <путь_до_файла> — вывести содержимое файла

Примеры:

> создать /filesystem.txt
Файл '/filesystem.txt' создан.

> изменить /filesystem.txt Привет мир
Файл '/filesystem.txt' изменён.

> посмотреть /filesystem.txt
Привет мир

> удалить /filesystem.txt
Файл '/filesystem.txt' удалён.

