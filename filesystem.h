#ifndef FILESYSTEM_H
#define FILESYSTEM_H

FILE* open_fs_file(const char* filename);
char* view_file_from_fs(FILE* fs, const char* target_filename);
void delete_file_from_fs(FILE* fs, const char* target_filename);
void add_new_file(FILE* fs, const char* filename, const char* content);
void modify_file(FILE* fs, const char* filename, const char* new_content);

#endif // FILESYSTEM_H
