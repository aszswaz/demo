package org.example.jdbc.demo;

import lombok.extern.slf4j.Slf4j;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.sql.*;

import static java.sql.Types.*;

/**
 * mysql jdbc 测试
 *
 * @author aszswaz
 * @date 2022-06-28 14:36:50
 */
@Slf4j
@SuppressWarnings("JavadocDeclaration")
public class MysqlTest {
    private static Connection connection;

    @BeforeAll
    static void beforeAll() {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost/demo?useSSL=false&serverTimezone=Asia/Shanghai", "root", "root");
        } catch (Exception e) {
            throw new RuntimeException(e.getMessage(), e);
        }
    }

    @BeforeEach
    void setUp() {
        String sql = "CREATE TABLE IF NOT EXISTS jdbc_demo (" +
                "id BIGINT UNSIGNED PRIMARY KEY AUTO_INCREMENT," +
                "message VARCHAR(255) NOT NULL COMMENT '信息'" +
                ")";
        this.runSql(sql);
    }

    @Test
    void insert01Test() {
        String sql = "INSERT INTO jdbc_demo (message) VALUES" +
                "('Hello World')," +
                "('Hello World')," +
                "('Hello World')," +
                "('Hello World')," +
                "('Hello World')," +
                "('Hello World')," +
                "('Hello World')," +
                "('Hello World')," +
                "('Hello World')";
        this.runSql(sql);
    }

    @Test
    void find01Test() {
        String sql = "SELECT * FROM jdbc_demo";
        this.runSql(sql);
    }

    private void runSql(String sql) {
        try {
            Statement statement = connection.createStatement();
            ResultSet result;
            // Statement.RETURN_GENERATED_KEYS 表示在插入数据的时候，返回数据的 ID
            if (statement.execute(sql, Statement.RETURN_GENERATED_KEYS)) {
                // 执行的是查询数据的操作，mysql 返回了数据
                result = statement.getResultSet();
            } else {
                // 执行的是新增、更新、删除数据或其他操作，mysql 返回了影响的数据条数
                log.info("update count: {}", statement.getUpdateCount());
                result = statement.getGeneratedKeys();
            }

            // 打印列信息
            final ResultSetMetaData metaData = result.getMetaData();
            StringBuilder sb = new StringBuilder();
            for (int i = 1; i <= metaData.getColumnCount(); i++) {
                sb.append(String.format("%-20s", metaData.getColumnName(i)));
            }
            log.info(sb.toString());

            // 打印 mysql 的返回结果
            while (result.next()) {
                sb = new StringBuilder();
                for (int i = 1; i <= metaData.getColumnCount(); i++) {
                    switch (metaData.getColumnType(i)) {
                        case VARCHAR:
                            sb.append(String.format("%-20s", result.getString(i)));
                            break;
                        case BIGINT:
                            sb.append(String.format("%-20d", result.getLong(i)));
                            break;
                        default:
                            sb.append(String.format("%-20s", result.getObject(i)));
                    }
                }
                log.info(sb.toString());
            }
        } catch (Exception e) {
            throw new RuntimeException(e.getMessage(), e);
        }
    }
}
