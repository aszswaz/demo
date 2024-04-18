#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>


int bluetooth_socket() {
    struct sockaddr_rc loc_addr = { 0 };
    int s;

    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = *BDADDR_ANY;
    loc_addr.rc_channel = (uint8_t)29;
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

    // put socket into listening mode
    listen(s, 1);
    return s; 
}

/**
 * 通过 socket 的方式进行蓝牙通信
 */
int main(int argc, char **argv) {
    struct sockaddr_rc rem_addr = { 0 };
    int s, client, bytes_len;
    socklen_t slen;
    char buf[1024] = { 0 };

    s = bluetooth_socket();
    // accept one connection
    slen = sizeof(rem_addr);
    client = accept(s, (struct sockaddr *)&rem_addr, &slen);


    ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "accepted connection from %s\n", buf);


    memset(buf, 0, sizeof(buf));
    // read data from the client
    bytes_len = read(client, buf, sizeof(buf));

    if( bytes_len > 0 ) {
        printf("received [%s]\n", buf);
    }

    // close connection
    close(client);
    close(s);
    return 0;
}
