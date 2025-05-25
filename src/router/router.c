#include <stdbool.h>
#include <logger/log.h>
#include <mongoose/mongoose.h>

#include "../handlers/handlers.h"
#include "../core/types.h"
#include "../input/input.h"

errCode_t register_route(router_t *router, const char* url, handler_t handler) {
    errCode_t err = ERR_OK;
    router->routes = realloc(router->routes, sizeof(route_t) * (router->routes_count + 1));
    
    if (router->routes) {
        router->routes[router->routes_count].path = url;
        router->routes[router->routes_count].handler = handler;
        router->routes_count++;
        log_debug("Route registered successfully: %s", url);
    } else {
        err = ERR_ALLOC_FAILED;
        log_error("Failed to register route: %s, error code: %d", url, err);
    }

    return err;
}

void register_routes(router_t *router) {
    register_route(router, "/", home_handler);
    register_route(router, "/converter", converter_handler);

    register_route(router, "/css/*", static_files_handler);
    register_route(router, "/js/*", static_files_handler);
    register_route(router, "/images/*", static_files_handler);

    register_route(router, "/api/currencies", api_handler);
    register_route(router, "/api/currencies/*", api_handler);
}

void router_handle_request(struct mg_connection *c, int ev, void *ev_data) {
    server_t *server = (server_t*)c->fn_data;

    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        bool route_is_found = false;

        log_trace("Requested resource: %.*s", (int)hm->uri.len, hm->uri.buf);
        
        for (size_t route = 0; route < server->router->routes_count && !route_is_found; route++) {
            if (mg_match(hm->uri, mg_str(server->router->routes[route].path), NULL)) {
                route_is_found = server->router->routes[route].handler(c, hm);
            }
        }

        if (!route_is_found) {
            log_warn("Route not found: %.*s", (int)hm->uri.len, hm->uri.buf);
            err_handler(c, hm, 404);
        }
    }
}