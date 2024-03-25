#include <stdio.h>
#include <ctype.h>

#define MAX_FILENAME_LENGTH 100

int main() {
    FILE *file;
    char filename[MAX_FILENAME_LENGTH];
    char ch;
    int words = 0, lines = 0, characters = 0;
    int inWord = 0;
    int isNewLine = 1; // Flag to track if we are at the beginning of a new line

    printf("Enter the filename: ");
    scanf("%s", filename);

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    while ((ch = fgetc(file)) != EOF) {
        characters++;

        // Check for newline character
        if (ch == '\n') {
            lines++;
            isNewLine = 1; // Set flag for new line
        } else if (isNewLine && !isspace(ch)) {
            isNewLine = 0; // Reset flag if non-space character follows a newline
        }

        // Check for word boundary
        if (isspace(ch)) {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            words++;
        }
    }

    fclose(file);

    // Adjust word count for last word without space after it
    if (characters > 0 && !isspace(ch)) {
        words++;
    }

    // Adjust line count for the last line without a newline character
    if (!isNewLine && characters > 0) {
        lines++;
    }

    printf("Word count: %d\n", words);
    printf("Line count: %d\n", lines);
    printf("Character count: %d\n", characters);

    return 0;
}
