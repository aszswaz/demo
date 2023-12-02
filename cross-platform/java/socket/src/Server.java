import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Objects;

public class Server {
    @SuppressWarnings({"InfiniteLoopStatement"})
    public static void main(String[] args) throws Exception {
        Socket client = null;
        BufferedReader read = null;
        String line;

        try (ServerSocket sock = new ServerSocket(8080)) {
            while (true) {
                try {
                    client = sock.accept();
                    read = new BufferedReader(new InputStreamReader(client.getInputStream()));
                    while (true) {
                        line = read.readLine();
                        if (Objects.isNull(line)) break;
                        System.out.println(line);
                    }
                } finally {
                    if (Objects.nonNull(read)) read.close();
                    if (Objects.nonNull(client)) client.close();
                }
            }
        }
    }
}
