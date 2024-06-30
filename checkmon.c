#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <limits.h>

void print_and_save_file_content(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        printf("Failed to open the file: %s\n", filepath);
        return;
    }

    char buffer[1024];
    time_t server_time, my_time;
    // time
    time_t seconds;
    time(&seconds);
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        //fputs(buffer, stdout); // Print to standard output
        // printf("%s\n", buffer);
        // printf("%lu\n", strtol(buffer, NULL, 10));
        server_time = strtol(buffer, NULL, 10);
        if (seconds - server_time > 5) printf("\033[1;91m●\033[0m");
        else printf("\033[1;92m●\033[0m");
        printf("\n");
    }

    fclose(file);
}

int main(void) {
    while (1) {
        // \033 is the escape character in octal
        // [2J clears the entire screen
        // [H moves the cursor to the top-left corner
        printf("\033[2J\033[H"); // Clear the screen using ANSI escape codes and same as system("clear");
        //
        const char *directoryPath = "/dev/shm";
        DIR *dir = opendir(directoryPath);
        if (dir == NULL) {
            perror("Failed to open directory");
            return EXIT_FAILURE;
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_REG) { // Check if it's a regular file
                char filepath[PATH_MAX];
                strcpy(filepath, directoryPath);
                strcat(filepath, "/");
                strcat(filepath, entry->d_name);
                char* name = strtok(entry->d_name, ".");
                printf("%s: ", name);
                print_and_save_file_content(filepath);
            }
        }
        closedir(dir);
        //
        sleep(1);
    }

    return EXIT_SUCCESS;
}

