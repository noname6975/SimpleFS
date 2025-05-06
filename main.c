#include <stdio.h>
#include "filesystem.h"

int main() {
    const char *fname = "test.txt";

    FILE *fs = open_fs_file("filesystem.disk");
    add_new_file(fs, "/test.txt", "Привет\nМир");
    // char line[] = view_file_from_fs(fs, "/test.txt");
    printf("%s", view_file_from_fs(fs, "/test.txt"));

    return 0;
}
