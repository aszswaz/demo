package org.example;

import java.io.IOException;
import java.io.InputStream;

/**
 * IPC 无名管道
 *
 * @author aszswaz
 * @date 2022-07-05 15:47:32
 */
@SuppressWarnings("JavadocDeclaration")
public class IPCDemo01 {
    public static void main(String[] args) throws IOException {
        Runtime runtime = Runtime.getRuntime();
        Process process = runtime.exec("ls -fl");
        InputStream stdout = process.getInputStream();
        InputStream stderr = process.getErrorStream();
        System.out.println(new String(stdout.readAllBytes()));
        System.out.println(new String(stderr.readAllBytes()));
    }
}
