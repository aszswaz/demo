package org.example;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.channels.FileLock;

/**
 * IPC 有名管道
 *
 * @author aszswaz
 * @date 2022-07-05 16:00:19
 */
@SuppressWarnings("JavadocDeclaration")
public class IPCDemo02 {
    public static void main(String[] args) throws IOException, InterruptedException {
        String command = args[0];

        // 利用文件系统实现共享内存
        if ("write".equals(command)) {
            RandomAccessFile file = new RandomAccessFile("/tmp/demo.dat", "rw");
            FileChannel fc = file.getChannel();
            MappedByteBuffer mbb = fc.map(FileChannel.MapMode.READ_WRITE, 0, 1024);

            FileLock lock;
            for (int i = 65; i < 91; i++) {
                lock = fc.lock();
                System.out.println("put: " + (char) i);
                mbb.put((byte) i);
                lock.release();
                Thread.sleep(1000);
            }
        } else if ("read".equals(command)) {
            RandomAccessFile file = new RandomAccessFile("/tmp/demo.dat", "rw");
            FileChannel fc = file.getChannel();
            MappedByteBuffer mbb = fc.map(FileChannel.MapMode.READ_ONLY, 0, 1024);

            FileLock lock;
            for (int i = 0; i < 26; i++) {
                lock = fc.lock();
                System.out.print((char) mbb.get(i));
                lock.release();
                Thread.sleep(1000);
            }
        }
    }
}
