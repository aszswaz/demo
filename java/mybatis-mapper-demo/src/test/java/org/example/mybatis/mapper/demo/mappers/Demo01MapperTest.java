package org.example.mybatis.mapper.demo.mappers;

import io.mybatis.mapper.example.Example;
import lombok.extern.slf4j.Slf4j;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;
import org.example.mybatis.mapper.demo.entities.Demo01PO;
import org.junit.jupiter.api.*;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

/**
 * mybatis mapper 测试
 *
 * @author aszswaz
 * @date 2022-06-28 11:54:04
 */
@Slf4j
@SuppressWarnings("JavadocDeclaration")
public class Demo01MapperTest {
    private static SqlSessionFactory sessionFactory;
    private SqlSession session;
    private Demo01Mapper mapper;

    @BeforeAll
    static void beforeAll() {
        try (InputStream is = Resources.getResourceAsStream("mybatis.xml")) {
            sessionFactory = new SqlSessionFactoryBuilder().build(is);
        } catch (Exception e) {
            throw new RuntimeException(e.getMessage(), e);
        }
    }

    @BeforeEach
    void setUp() {
        this.session = sessionFactory.openSession(true);
        this.mapper = this.session.getMapper(Demo01Mapper.class);
        log.info("Form is being created.");
        this.mapper.createTable();
        log.info("Form created successfully.");
    }

    @AfterEach
    void tearDown() {
        this.session.close();
    }

    /**
     * 插入单条数据
     */
    @Test
    void insert01Test() {
        Demo01PO po = new Demo01PO();
        po.setMessage("Hello World");
        Assertions.assertEquals(1, this.mapper.insert(po));
        log.info(String.valueOf(po));
    }

    /**
     * 批量插入数据
     */
    @Test
    void insert02Test() {
        List<Demo01PO> dPos = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            Demo01PO dPo = new Demo01PO();
            dPo.setMessage("Hello World");
            dPos.add(dPo);
        }
        log.info("insert {} data.", this.mapper.insertList(dPos));
        dPos.forEach(item -> log.info(String.valueOf(item)));
    }

    @Test
    void find01Test() {
        this.mapper.wrapper()
                .eq(Demo01PO::getId, 10000)
                .list()
                .forEach(item -> log.info(String.valueOf(item)));
    }
}