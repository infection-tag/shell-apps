#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

/* texteditor.c: simple text editor that allows you to make a file and edit it.
 * does not have the same functionality as VI, just for quick notes and such.
 * use the -r flag to read it without deleting it.
 * editing a file WILL delete all of its previous contents. */

int main(int argc, char *argv[]) {
    char filename[MAX_LINE_LENGTH];
    char line[MAX_LINE_LENGTH];
    FILE *file;
    int read_mode = 0;
    int edit_mode = 0;

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s [-r filename] <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 3) {
        if (strcmp(argv[1], "-r") == 0) {
            read_mode = 1;
            strcpy(filename, argv[2]);
        } else {
            fprintf(stderr, "Usage: %s [-r filename] <filename>\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        strcpy(filename, argv[1]);
    }

    if (read_mode) {
        file = fopen(filename, "r");

        if (file == NULL) {
            fprintf(stderr, "Error opening file %s\n", filename);
            exit(EXIT_FAILURE);
        }

        printf("File contents:\n");

        while (fgets(line, MAX_LINE_LENGTH, file)) {
            printf("%s", line);
        }

        fclose(file);
        printf("Type 'edit' to edit the file, or press Ctrl+D to exit.\n");

        while (fgets(line, MAX_LINE_LENGTH, stdin)) {
            if (strcmp(line, "edit\n") == 0) {
                edit_mode = 1;
                break;
            } else {
                exit(EXIT_SUCCESS);
            }
        }
    }

    if (edit_mode) {
        file = fopen(filename, "r+");

        if (file == NULL) {
            fprintf(stderr, "Error opening file %s\n", filename);
            exit(EXIT_FAILURE);
        }

        printf("Enter text, press Ctrl+D to save and exit:\n");

        while (fgets(line, MAX_LINE_LENGTH, stdin)) {
            fputs(line, file);
        }

        fclose(file);
        printf("Text saved to %s\n", filename);
    } else {
        file = fopen(filename, "w");

        if (file == NULL) {
            fprintf(stderr, "Error opening file %s\n", filename);
            exit(EXIT_FAILURE);
        }

        printf("Enter text, press Ctrl+D to save and exit:\n");

        while (fgets(line, MAX_LINE_LENGTH, stdin)) {
            fputs(line, file);
        }

        fclose(file);
        printf("Text saved to %s\n", filename);
    }

    return 0;
}

