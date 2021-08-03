#include "hdr.h"

void http2_initial(SOCKET sock) {
    http2_stream settings;
    settings.len = 0;
    settings.type = 4;
    settings.flags = 0;
    settings.st_id = 0;

    http2_stream headers;
    headers.len = 36;
    headers.type = 1;
    headers.flags = 0;
    headers.st_id = 0x03000000;

    http2_stream continuation;
    continuation.len = 10;
    continuation.type = 9;
    continuation.flags = 0;
    continuation.st_id = 0x03000000;

    char buf[500];
    send(sock, "GET / HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection: Upgrade, HTTP2-Settings\r\nUpgrade: h2c\r\nHTTP2-Settings: AAMAAABkAARAAAAAAAIAAAAA\r\n\r\n", 128, NULL);
    recv(sock, buf, 500, NULL);

    send(sock, "PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n", 24, NULL);
    send(sock, (char*)&settings, 9, NULL);
    recv(sock, buf, 500, NULL);
    send(sock, (char*)&headers, 9, NULL);
    send(sock, "\x82\x84\x86\x41\x86\xa0\xe4\x1d\x13\x9d\x09\x7a\x88\x25\xb6\x50\xc3\xab\xb6\x15\xc1\x53\x03\x2a\x2f\x2a\x40\x83\x18\xc6\x3f\x04\x76\x76\x76\x76", 36, NULL);
}