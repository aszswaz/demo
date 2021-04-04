package zhong.http.server;

import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Objects;

/**
 * http server
 *
 * @author aszswaz
 * @date 2021/4/4 18:24:18
 */
public class ServerStart {
    public static void main(String[] args) throws IOException {
        System.out.println("开始运行程序");
        ServerSocket serverSocket = new ServerSocket(8080);
        Socket socket = serverSocket.accept();
        try {
            //noinspection InfiniteLoopStatement
            while (true) {
                InputStream inputStream = socket.getInputStream();
                System.out.print((char) inputStream.read());
            }
        } finally {
            if (Objects.nonNull(socket)) socket.close();
            serverSocket.close();
        }
    }
}
