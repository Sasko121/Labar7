#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void concatenate_files(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Use: %s <file1> <file2> ... <acknowledgment_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE* dest_file = fopen(argv[argc - 1], "wb");
    if (dest_file == NULL) {
        perror("Could not open the acknowledgment file");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc - 1; i++) {
        FILE* src_file = fopen(argv[i], "rb");
        if (src_file == NULL) {
            perror("Could not open the input file");
            fclose(dest_file);
            exit(EXIT_FAILURE);
        }

        char buffer[BUFFER_SIZE];
        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
            fwrite(buffer, 1, bytes_read, dest_file);
        }

        fclose(src_file);
    }

    fclose(dest_file);
    printf("The files have been successfully merged into %s\n", argv[argc - 1]);
}

int main(int argc, char* argv[]) {
    concatenate_files(argc, argv);
    return 0;
}