#ifndef UTILS_H
#define UTILS_H

const char *get_content_type(const char *path);
bool file_is_exists(const char* path);
void init_logger();

#endif // UTILS_H