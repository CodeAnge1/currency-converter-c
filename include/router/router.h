#ifndef ROUTER_H
#define ROUTER_H

#include "../core/types.h"

errCode_t register_route(router_t *router, const char* url, handler_t handler);
void register_routes(router_t *router);
void router_handle_request(struct mg_connection *c, int ev, void *ev_data);

#endif // ROUTER_H