#ifndef SERVER_H
#define SERVER_H

#include "../types.h"

void get_server_addr(addr_t *server);
errCode_t create_server(server_t* server, addr_t addr);
errCode_t run_server(server_t* server);
errCode_t stop_server(server_t* server);

#endif //SERVER_H
