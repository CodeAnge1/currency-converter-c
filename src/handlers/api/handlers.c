#include <logger/log.h>

#include "../handlers.h"
#include "../input/input.h"
#include "../core/types.h"
#include "../utils/utils.h"

bool api_handler(struct mg_connection *c, struct mg_http_message *hm) {
    log_debug("Api handler called");
    bool is_found = false;
    struct mg_str currency_name = mg_str("");
    char* base_data_path = "../resources/api_data/currencies";
    char file_path[256];

    if (mg_match(hm->uri, mg_str("/api/currencies"), NULL)) {
        snprintf(file_path, sizeof(file_path), "%s.json", base_data_path);

        struct mg_http_serve_opts opts = {
            .mime_types = get_content_type(file_path)
        };

        mg_http_serve_file(c, hm, file_path, &opts);
        is_found = true;
    } else if (mg_match(hm->uri, mg_str("/api/currencies/*"), &currency_name)) {
        is_found = true;
        char* err_json_data = "{\"error\":\"Currency not found\",\"status\":404}";

        snprintf(file_path, sizeof(file_path), "%s/%.*s.json", base_data_path, (int)currency_name.len, currency_name.buf);

        struct mg_http_serve_opts opts = {
            .mime_types = get_content_type(file_path)
        };

        if (file_is_exists(file_path)) mg_http_serve_file(c, hm, file_path, &opts);
        else mg_http_reply(c, 404, "Content-Type: application/json\r\n", err_json_data);

    }
    return is_found;
}