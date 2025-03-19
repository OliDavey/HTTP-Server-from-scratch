#include <winsock2.h>
#include <Windows.h>
#include <stdio.h>

int main(){
    // create socket
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    // setting up socket
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0); // IPV4, TCP Socket, Default Protocol
    
    // binding socket to address and creating address
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = 0;
    addr.sin_port = htons(8080);
    bind(s, &addr, sizeof(addr));
   

    // socket listens to address, bind address to socket
    listen(s, 10);

    // accepts client connection
    SOCKET client = accept(s, 0, 0);
    
    // recieve data from socket
    char request[256] = {0};
    recv(client, request, 256, 0);

    // GET /[file] ...
    if (memcmp(request, "GET / ", 6) == 0){
        FILE *f = fopen("index.html", "r");
        char buffer[256] = {0};
        fread(buffer, 1, 256, f);
        send(client, buffer, 256, 0);
        closesocket(s);
        WSACleanup();
    }

}