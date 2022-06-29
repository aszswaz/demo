package org.example.jdbc.demo;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import java.sql.*;

/**
 * mysql jdbc 演示
 *
 * @author aszswaz
 * @date 2022-06-29 19:18:48
 */
@SuppressWarnings("JavadocDeclaration")
public class Mysql02Test {
    private static Connection connection;

    @BeforeAll
    static void beforeAll() {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://192.168.24.1/demo?useSSL=false&serverTimezone=Asia/Shanghai", "root", "root");
        } catch (Exception e) {
            throw new RuntimeException(e.getMessage(), e);
        }
    }

    @Test
    void insertTest() throws SQLException {
        Statement statement = connection.createStatement();
        int update = statement.executeUpdate("INSERT INTO mysql_jdbc_demo(message) VALUES ('Hello World'), ('Hello World')");
        System.out.println("update: " + update);
        if (update != 2) {
            System.out.println("update != 2");
        }
    }
}
