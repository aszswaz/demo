package com.example;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.lang.management.ManagementFactory;
import java.nio.charset.StandardCharsets;

/**
 * JNI demo
 *
 * @author aszswaz
 * @date 2022-08-11 09:29:42
 */
@SuppressWarnings("JavadocDeclaration")
public class JniDemo {
    public static void main(String[] args) throws IOException, InterruptedException {
        Runtime.getRuntime().loadLibrary("JniEntity");
        JniEntity.fork();

        try (RandomAccessFile file = new RandomAccessFile("demo.log", "rw")) {
            file.seek(file.length());
            // Get the pid and hostname of the process.
            String name = ManagementFactory.getRuntimeMXBean().getName();
            String message = name + ": Hello World" + System.lineSeparator();
            file.write(message.getBytes(StandardCharsets.UTF_8));
        }

        Thread.sleep(10000);
    }
}
