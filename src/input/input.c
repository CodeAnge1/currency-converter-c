#include <logger/log.h>
#include <stdio.h>
#include <stdlib.h>
#include "input.h"

char *read_file(const char *filename) {
    log_trace("Reading file: %s", filename);
    FILE *f = fopen(filename, "rb");
    char *res = NULL;
    if (f) {
        fseek(f, 0, SEEK_END);
        size_t size = ftell(f);
        rewind(f);
        res = (char *)malloc(size + 1);
        if (res) {
            fread(res, 1, size, f);
            res[size] = '\0';
        } else {
            log_error("Memory allocation failed for file: %s", filename);
        }
        fclose(f);
    } else {
        log_warn("Failed to open file: %s", filename);
    }
    return res;
}
