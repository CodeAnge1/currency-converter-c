#include <logger/log.h>
#include <sys/stat.h>
#include <stdbool.h>

#include "core/types.h"
#include "input/input.h"

static const content_type_t content_types[] = {
    {".html", "text/html; charset=utf-8"},
    {".css", "text/css"},
    {".js", "application/javascript"},
    {".jpg", "image/jpeg"},
    {".png", "image/png"},
    {".gif", "image/gif"},
    {".ico", "image/x-icon"},
    {".svg", "image/svg+xml"},
    {NULL, NULL}
};

const char *get_content_type(const char *path) {
    const char *ext = strrchr(path, '.');
    const char *current_mime = "application/octet-stream";

    if (ext != NULL)
        for (int i = 0; content_types[i].extension != NULL; i++)
            if (strcmp(ext, content_types[i].extension) == 0)
                current_mime = content_types[i].mime;

    return current_mime;
}

bool file_is_exists(const char* path) {
    struct stat st;
    return stat(path, &st) == 0;
}

void init_logger() {
    log_set_level(LOG_INFO);
}