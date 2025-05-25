#include <mongoose/mongoose.h>

#include "router/router.h"
#include "core/types.h"
#include "utils/utils.h"
#include "core/server/server.h"

static addr_t local_addr = {.host="127.0.0.1", .port=15000};

int main() {
    init_logger();
    server_t server;

    create_server(&server, local_addr);
    run_server(&server);
    stop_server(&server);

    return 0;
}