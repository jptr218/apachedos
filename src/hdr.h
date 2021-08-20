#pragma once
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#include <thread>

#pragma comment (lib, "Ws2_32.lib")
using namespace std;

#pragma pack(1)
struct http2_stream {
    uint16_t zero = 0;
    uint8_t len;
    uint8_t type;
    uint8_t flags;
    uint32_t st_id;
};

addrinfo* find_host(string ip, string port);
void http2_initial(SOCKET sock);
void worker(addrinfo* addr, char* buf, int blen);
