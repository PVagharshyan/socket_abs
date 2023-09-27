#include "Socket.h"

#include <iostream>

int main() {
    Socket_server s(8080, 1);
    s.crate_client("client_1");
    return 0;
}
