#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <memory.h>
#include <assert.h>

#define REGULAR_FILE_TYPE 8

typedef struct string {
    char* buf;
    size_t lenght;
    size_t capacity;
}* String;

String initString(size_t capacity) {
    char *buf = malloc(capacity);
    assert(buf != NULL);

    String str = malloc(sizeof(struct string));
    assert(str != NULL);
    str->buf = buf;
    str->lenght = 0;
    str->capacity = capacity;
    return str;
}

void copy(String out, String in) {
    if (in->lenght > out->capacity) {
        printf("Error\n");
        return;
    }

    for (int i = 0; i < in->lenght; ++i) {
        out->buf[i] = in->buf[i];
    }

    out->lenght = in->lenght;
}

void destroyString(String *str) {
    assert(str != NULL);
    free(((*str)->buf));
    free(*str);
}


int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Please enter the directory name\n");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        DIR *dir = opendir(argv[i]);
        if (!dir) {
            printf("Please enter the correct directory name\n");
            return EXIT_FAILURE;
        }

        String fullDirname = initString(256);

        String dirname = initString(256);
        int j = 0, k = 0;
        while(argv[i][j] != '\0') {
            if (argv[i][j] == '/') {
                k = 0;
                ++j;
                continue;
            }

            dirname->buf[k] = argv[i][j];
            ++k;
            ++j;
        }
        dirname->buf[k] = '\0';
        dirname->lenght = k;

        fullDirname->lenght = j + 1;
        for (int m = 0; m <= fullDirname->lenght; ++m) {
            fullDirname->buf[m] = argv[i][m];
        }

        String reverseDirname = initString(256);
        reverseDirname->buf[0] = '.';
        reverseDirname->buf[1] = '/';
        for (int m = k - 1, l = 2; m >= 0; --m, ++l) {
            reverseDirname->buf[l] = dirname->buf[m];
        }
        reverseDirname->buf[k + 2] = '\0';
        reverseDirname->lenght = k + 3;
        
        struct stat dirStat;
        stat(dirname->buf, &dirStat);

        mkdir(reverseDirname->buf, dirStat.st_mode);

        struct dirent* entry;
        char reverseFileName[255];
        DIR *newDir = opendir(reverseDirname->buf);
        if (newDir == NULL) {
            closedir(dir);
            printf("Something went wrong!");
            return EXIT_FAILURE;
        }

        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type != REGULAR_FILE_TYPE) {
                continue;
            }

            int len = 0;
            while(entry->d_name[len] != '\0') {
                ++len;
            }

            for (int m = len - 1, l = 0; m >= 0; --m, ++l) {
                reverseFileName[l] = entry->d_name[m];
            }
            reverseFileName[len] = '\0';

            String fullName = initString(256);
            String reverseFullName = initString(256);

            copy(fullName, fullDirname);
            fullName->lenght += len;
            fullName->buf[fullDirname->lenght - 1] = '/';

            copy(reverseFullName, reverseDirname);
            reverseFullName->lenght += len;
            reverseFullName->buf[reverseDirname->lenght - 1] = '/';

            for (int m = fullDirname->lenght, l = 0; m <= fullName->lenght; ++m, ++l) {
                fullName->buf[m] = entry->d_name[l];
            }

            for (int m = reverseDirname->lenght, l = 0; m <= reverseFullName->lenght; ++m, ++l) {
                reverseFullName->buf[m] = reverseFileName[l];
            }

            fullName->buf[fullName->lenght + 1] = '\0';
            reverseFullName->buf[reverseFullName->lenght + 1] = '\0';

            FILE *in = fopen(fullName->buf, "r");
            FILE *out = fopen(reverseFullName->buf, "w");

            if (in == NULL || out == NULL) {
                closedir(dir);
                closedir(newDir);
                int first = fclose(in);
                int second = fclose(out);
                printf("Something went wrong! File in %s: error code - %d, file out %s, error code: %d",
                        entry->d_name, first, reverseFileName, second);
                return EXIT_FAILURE;
            }

            char buf = 0;
            fseek(in, 0, SEEK_END);
            while ((fseek(in, -1L, SEEK_CUR) != EOF)) {
                buf = fgetc(in);
                fputc(buf, out);
                fseek(in, -1L, SEEK_CUR);
            }

            destroyString(&fullName);
            destroyString(&reverseFullName);
            fclose(in);
            fclose(out);
        }

        destroyString(&fullDirname);
        destroyString(&dirname);
        destroyString(&reverseDirname);
        closedir(dir);
        closedir(newDir);
    }
    return EXIT_SUCCESS;
}