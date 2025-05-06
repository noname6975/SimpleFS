#include <stdio.h>
#include "filesystem.h"

int main() {
    const char *fname = "test.txt";

    create_file(fname);
    write_to_file(fname, "Привет, мир!\n");
    printf("Содержимое файла:\n");
    read_file(fname);

    return 0;
}
