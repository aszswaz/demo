#include <iostream>

#include <windows.h>
#include <ws2bth.h>
#include <bluetoothapis.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "bthprops.lib")

// 目标蓝牙设备地址
#define ADDRESS 0xD83ADD56AF08
// 要想目标设备发送的数据
#define MSG "Hello World!"
// RFCOMM 端口，取值范围：1 - 30
#define PORT 29

/*
 通过蓝牙的 RFCOMM 协议进行可靠的数据传输
*/
int main() {
    int code = {};
    WORD socketVersion = {};
    WSADATA sock_data = {};
    SOCKET sock = {};
    SOCKADDR_BTH addr = {};

    // 初始化 win socket
    socketVersion = MAKEWORD(2, 2);
    code = WSAStartup(socketVersion, &sock_data);
    if (code) {
        std::cerr << "WSAStartup error: " << WSAGetLastError() << std::endl;
        goto finish;
    }

    // 创建蓝牙 RFCOMM socket
    sock = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    if (sock == INVALID_SOCKET) {
        std::cerr << "create socket error: " << WSAGetLastError() << std::endl;
        goto finish;
    }

    // 建立蓝牙 RFCOMM 连接
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
