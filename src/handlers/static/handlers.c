#include <logger/log.h>

#include "handlers/handlers.h"
#include "core/types.h"
#include "input/input.h"
#include "utils/utils.h"

bool static_files_handler(struct mg_connection *c, struct mg_http_message *hm) {
    bool is_found = false;

    if (mg_match(hm->uri, mg_str("/*/*"), NULL)) {
        log_debug("Static file requested: %.*s", (int)hm->uri.len, hm->uri.buf);

        char file_path[256];
        snprintf(file_path, sizeof(file_path), "static%.*s", (int)hm->uri.len, hm->uri.buf);

        struct mg_http_serve_opts opts = {
            .mime_types = get_content_type(file_path)
        };
        
        mg_http_serve_file(c, hm, file_path, &opts);
        is_found = true;
    }
    return is_found;
}
