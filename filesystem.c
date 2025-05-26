#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int delete_file(const char* filename) {
    const char* fs_path = "filesystem.txt";

    FILE* fs = open_or_create_fs(fs_path);
    if (!fs) return -1;

    char* fs_content = read_full_fs(fs);
    fclose(fs);

    if (!fs_content) return -1;

    char* lines[1024]; 
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

   return 0; 
}
