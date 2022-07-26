package org.example;

import java.io.File;
import java.io.IOException;
import java.net.StandardProtocolFamily;
import java.net.UnixDomainSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.nio.charset.StandardCharsets;

import static java.util.Objects.nonNull;

/**
 * Unix Domain Socket 演示
 *
 * @author aszswaz
 * @date 2022-07-05 17:14:12
 */
@SuppressWarnings("JavadocDeclaration")
public class UnixDomainSocketDemo {
    public static void main(String[] args) throws IOException, InterruptedException {
        String command = args[0];
        if ("server".equals(command))
            startServer();
        else if ("client".equals(command))
            startClient();
    }

    @SuppressWarnings({"InfiniteLoopStatement"})
    public static void startServer() throws IOException {
        UnixDomainSocketAddress address = UnixDomainSocketAddress.of("demo.sock");
        new File("demo.sock").deleteOnExit();
        ServerSocketChannel server = null;

        try {
            // 开启 UNIX Domain Socket
            server = ServerSocketChannel.open(StandardProtocolFamily.UNIX);
            server.bind(address);

            while (true) {
                // 等待连接
                System.out.println("Waiting for client to connect...");
                final SocketChannel client = server.accept();
                System.out.println("A client connected successfully, remote address: " + client);
                // 创建线程读取 socket
                Runnable run = () -> {
                    try {
                        ByteBuffer buffer = ByteBuffer.allocate(8192);
                        int len;
                        while ((len = client.read(buffer)) != -1) {
                            byte[] bytes = buffer.array();
                            System.out.println("client: " + new String(bytes, 0, len));
                            client.write(ByteBuffer.wrap(bytes, 0, len));
                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                    } finally {
                        try {
                            System.out.println("A client connection was closed.");
                            client.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                };
                new Thread(run).start();
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        } finally {
            if (nonNull(server)) server.close();
        }
    }

    @SuppressWarnings({"InfiniteLoopStatement", "BusyWait"})
    public static void startClient() throws IOException, InterruptedException {
        UnixDomainSocketAddress address = UnixDomainSocketAddress.of("demo.sock");
        try (SocketChannel server = SocketChannel.open(address)) {
            ByteBuffer buffer = ByteBuffer.allocate(8192);
            byte[] message = "Hello World".getBytes(StandardCharsets.UTF_8);
            while (true) {
                server.write(ByteBuffer.wrap(message));
                int len = server.read(buffer);
                buffer.flip();
                System.out.println("server: " + new String(buffer.array(), 0, len));
                Thread.sleep(5000);
            }
        }
    }
}
