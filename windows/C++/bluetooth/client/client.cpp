#include <iostream>

#include <windows.h>
#include <ws2bth.h>
#include <bluetoothapis.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "bthprops.lib")

// Ŀ�������豸��ַ
#define ADDRESS 0xD83ADD56AF08
// Ҫ��Ŀ���豸���͵�����
#define MSG "Hello World!"
// RFCOMM �˿ڣ�ȡֵ��Χ��1 - 30
#define PORT 29

/*
 ͨ�������� RFCOMM Э����пɿ������ݴ���
*/
int main() {
    int code = {};
    WORD socketVersion = {};
    WSADATA sock_data = {};
    SOCKET sock = {};
    SOCKADDR_BTH addr = {};

    // ��ʼ�� win socket
    socketVersion = MAKEWORD(2, 2);
    code = WSAStartup(socketVersion, &sock_data);
    if (code) {
        std::cerr << "WSAStartup error: " << WSAGetLastError() << std::endl;
        goto finish;
    }

    // �������� RFCOMM socket
    sock = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    if (sock == INVALID_SOCKET) {
        std::cerr << "create socket error: " << WSAGetLastError() << std::endl;
        goto finish;
    }

    // �������� RFCOMM ����
    addr.addressFamily = AF_BTH;
    addr.btAddr = ADDRESS;
    addr.port = PORT;
    code = connect(sock, (SOCKADDR *)&addr, sizeof(addr));
    if (code == SOCKET_ERROR) {
        std::cerr << "socket connect error: " << WSAGetLastError()<< std::endl;
        goto finish;
    }

    code = send(sock, MSG, sizeof(MSG), 0);
    if (code == SOCKET_ERROR) {
        std::cerr << "send error: " << WSAGetLastError() << std::endl;
        goto finish;
    }

finish:
    if (sock) closesocket(sock);
    WSACleanup();
    return code;
}
