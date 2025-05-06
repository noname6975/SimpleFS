#ifndef FILESYSTEM_H
#define FILESYSTEM_H

void create_file(const char *filename);
void delete_file(const char *filename);
void write_to_file(const char *filename, const char *content);
void read_file(const char *filename);
int file_exists(const char *filename);

#endif // FILESYSTEM_H
