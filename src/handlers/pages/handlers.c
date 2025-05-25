#include <logger/log.h>
#include "../handlers.h"
#include "../input/input.h"
#include "../core/types.h"


bool home_handler(struct mg_connection *c, struct mg_http_message *hm) {
    log_debug("Home handler called");
    bool is_found = false;

    if (mg_match(hm->uri, mg_str("/"), NULL)) {
        mg_http_reply(c, 302, "Location: /converter\r\n", "");
        is_found = true;
    }
    return is_found;
}

bool converter_handler(struct mg_connection *c, struct mg_http_message *hm) {
    bool is_found = false;
    log_debug("Converter handler called");
    if (mg_match(hm->uri, mg_str("/converter"), NULL)) {
        char *data = read_file("../static/templates/converter.html");
        if (data) {
            mg_http_reply(c, 200, "Content-Type: text/html; charset=utf-8\r\n", data);
            free(data);
            is_found = true;
        } else {
            log_error("Failed to read converter template");
            is_found = err_handler(c, hm, 503);
        }
    }

    return is_found;
}

bool err_handler(struct mg_connection *c, struct mg_http_message *hm, size_t status_code) {
    log_debug("Error handler called");
    char *template_path = NULL;
    char *data = NULL;

    if (status_code == 404) {
        log_debug("Not found error handler called");
        template_path = "../static/templates/not-found.html";
        data = read_file(template_path);
    }
    if (status_code == 503 || !data) {
        log_debug("Service unavailable error handler called");
        template_path = "../static/templates/service-unavailable.html";
        data = read_file(template_path);
    }
    else {
        log_warn("Unknown error handler called, status code: %zu", status_code);
        template_path = "../static/templates/service-unavailable.html";
    }

    if (data) {
        mg_http_reply(c, status_code, "Content-Type: text/html; charset=utf-8\r\n", data);
        free(data);
    } else {
        log_error("Failed to read error template, status code: %zu", status_code);
        mg_http_reply(c, status_code, "Content-Type: text/plain\r\n", "Internal Server Error");
    }

    return true;
}
