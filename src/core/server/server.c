#include <stdio.h>
#include <logger/log.h>
#include <mongoose/mongoose.h>

#include "server.h"
#include "../types.h"
#include "../../router/router.h"

void get_server_addr(addr_t* addr) {
    snprintf(addr->full_url, sizeof(addr->full_url), "http://%s:%d", addr->host, addr->port);
}

errCode_t create_server(server_t* server, addr_t addr) {
    server->mgr = malloc(sizeof(struct mg_mgr));
    errCode_t err = (!server->mgr) ? ERR_ALLOC_FAILED : ERR_OK;

    if (err == ERR_OK) {
        mg_mgr_init(server->mgr);
        get_server_addr(&addr);
        server->addr = addr;
        server->router = malloc(sizeof(router_t));
        if (server->router) {
            server->router->routes = NULL;
            server->router->routes_count = 0;
            server->running = true;
        } else {
            err = ERR_ALLOC_FAILED;
        }
    }

    if (err == ERR_OK) {
        log_info("Server created successfully");
        register_routes(server->router);
    } else {
        log_error("Failed to create server: %d", err);
    }

    return err;
}

errCode_t run_server(server_t* server) {
    errCode_t err = ERR_OK;

    if (!server || !server->mgr) {
        log_error("Invalid server configuration.");
        err = ERR_INVALID_SERVER_CONFIG;
    } else {
        struct mg_connection *conn = mg_http_listen(server->mgr, server->addr.full_url, router_handle_request, server);

        if (!conn) {
            err = ERR_INIT_FAILED;
            log_error("Failed to start server: %d", err);
        } else {
            log_info("Server started successfully at %s", server->addr.full_url);
            for (;server->running;)
                mg_mgr_poll(server->mgr, 1000);
        }
    }

    return err;
}

errCode_t stop_server(server_t* server) {
    log_info("Server stopped.");
    if (server->mgr) {
        mg_mgr_free(server->mgr);
        free(server->mgr);
        server->mgr = NULL;
    }
    if (server->router) {
        free(server->router);
        server->router = NULL;
    }
    return ERR_OK;
}
