#ifndef SERVER_TYPES_H
#define SERVER_TYPES_H

#include <mongoose/mongoose.h>

typedef bool (*handler_t)(struct mg_connection *c, struct mg_http_message *hm);

typedef enum {
    ERR_OK=0,
    ERR_ALLOC_FAILED,
    ERR_ROUTE_ADD_FAILED,
    ERR_INIT_FAILED,
    ERR_INVALID_SERVER_CONFIG,
    ERR_NUM
} errCode_t;

typedef struct {
    const char* host;
    int port;
    char full_url[512];
} addr_t;

typedef struct {
    const char* path;
    handler_t handler;
} route_t;

typedef struct {
    route_t* routes;
    size_t routes_count;
} router_t;

typedef struct {
    struct mg_mgr* mgr;
    bool running;
    addr_t addr;
    router_t* router;
} server_t;

typedef struct {
    const char *extension;
    const char *mime;
} content_type_t;

#endif