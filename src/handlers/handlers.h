#ifndef HANDLERS_H
#define HANDLERS_H

#include <mongoose/mongoose.h>
#include <stdbool.h>

bool static_files_handler(struct mg_connection *c, struct mg_http_message *hm);
bool converter_handler(struct mg_connection *c, struct mg_http_message *hm);
bool api_handler(struct mg_connection *c, struct mg_http_message *hm);
bool err_handler(struct mg_connection *c, struct mg_http_message *hm, size_t status_code);

#endif // HANDLERS_H