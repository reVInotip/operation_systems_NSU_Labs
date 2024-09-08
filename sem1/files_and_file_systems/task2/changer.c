#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <linux/stat.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Please enter the name\n");
        return 1;
    }

    char funcName[256];
    int lenght = 0;
    for (int i = 0; argv[0][i] != '\0'; ++i) {
        if (argv[0][i] == '/') {
            lenght = 0;
            continue;
        }
        funcName[lenght] = argv[0][i];
        ++lenght;
    }

    funcName[lenght] = '\0';
    
    if (!strcmp(funcName, "create_dir")) {
        if (mkdir(argv[1], S_IROTH) == -1) {
            fprintf(stderr, "%d\n", errno);
            return 1;
        }
    } else if (!strcmp(funcName, "ls_dir")) {
        DIR *dir = opendir(argv[1]);
        if (dir == NULL) {
            fprintf(stderr, "%d\n", errno);
            return 1;
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            printf("File name: %s, file type: %d\n", entry->d_name, entry->d_type);
        }

        if (closedir(dir) == -1) {
            fprintf(stderr, "%d\n", errno);
            return 1;
        }
    } else if (!strcmp(funcName, "del_dir")) {
        if (remove(argv[1]) == -1) {
            fprintf(stderr, "%d\n", errno);
            return 1;
        }
    } else if (!strcmp(funcName, "create_file")) {
        if(mknod(argv[1], S_IROTH, S_IFREG) == -1) {
            fprintf(stderr, "%d\n", errno);
            return 1;
        }
    } else if (!strcmp(funcName, "cat_file")) {
        FILE *file = fopen(argv[1], "r");
        if (file == NULL) {
            fprintf(stderr, "%d\n", errno);
            return 1;
        }

        char character;
        while ((character = fgetc(file)) != EOF) {
            printf("%c", character);
        }

        if (fclose(file) == EOF) {
            fprintf(stderr, "%d\n", errno);
            return 1;
        }
    } else if (!strcmp(funcName, "del_file")) {
        if (remove(argv[1]) == -1) {
            fprintf(stderr, "%d\n", errno);
            return 1;
        }
    } else if (!strcmp(funcName, "symlink")) {
        if (symlink(argv[1], "symbolic_link") == -1) {
            fprintf(stderr, "%d\n", errno);
            return 1;
        }
    } else if (!strcmp(funcName, "read_link")) { // to do
        char buf[1024];
        if (readlink(argv[1], buf, 1024) == -1) {
            fprintf(stderr, "%d\n", errno);
            return 1;
        }

        printf("%s\n", buf);
    } else if (!strcmp(funcName, "read_link_content")) {
        FILE *file = fopen(argv[1], "r");
        if (file == NULL) {
            fprintf(stderr, "%d\n", errno);
            return 1;
        }

        char character;
        while ((character = fgetc(file)) != EOF) {
            printf("%c", character);
        }

        if (fclose(file) == EOF) {
            fprintf(stderr, "%d\n", errno);
            return 1;
        }
    } else if (!strcmp(funcName, "delete_symlink")) {
        if (remove(argv[1]) == -1) {
            fprintf(stderr, "%d\n", errno);
            return 1;
        }
    } else if (!strcmp(funcName, "link")) {
        if (link(argv[1], "hard_link") == -1) {
            fprintf(stderr, "%d\n", errno);
            return 1;
        }
    } else if (!strcmp(funcName, "remove_link")) {
        if (remove(argv[1]) == -1) {
            fprintf(stderr, "%d\n", errno);
            return 1;
        }
    } else if (!strcmp(funcName, "ls_mod")) {
        struct stat fileInfo;
        if (stat(argv[1], &fileInfo) == -1) {
            fprintf(stderr, "%d\n", errno);
            return 1;
        }
        
        printf("Mode %o, count link %ld\n", fileInfo.st_mode & 07777, fileInfo.st_nlink);
    } else if (!strcmp(funcName, "change_mod")) {
        if(chmod(argv[1], S_IRWXO)) {
            fprintf(stderr, "%d\n", errno);
            return 1;
        }
    } else {
        printf("Incorrect operation: %s\n", funcName);
    }
    return 0;
}