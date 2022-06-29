package org.example.mybatis.mapper.demo.mappers;

import io.mybatis.mapper.example.Example;
import lombok.extern.slf4j.Slf4j;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;
import org.example.mybatis.mapper.demo.entities.Demo01PO;
import org.jetbrains.annotations.NotNull;
import org.junit.jupiter.api.*;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;
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
        this.mapper.clear();
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
        this.insertTestData(10).forEach(item -> log.info(String.valueOf(item)));
    }

    /**
     * 查询单条数据测试
     */
    @Test
    void find01Test() {
        this.insertTestData(1);
        this.mapper.wrapper()
                .eq(Demo01PO::getId, 10000)
                .list()
                .forEach(item -> log.info(String.valueOf(item)));
    }

    /**
     * 查询所有数据测试
     */
    @Test
    void find02Test() {
        this.insertTestData(100);
        List<Demo01PO> list = this.mapper.wrapper().list();
        log.info("data size: {}", list.size());
        list.subList(0, 10).forEach(item -> log.info(String.valueOf(item)));
        log.info("...");
    }

    /**
     * 查询指定的数据量
     */
    @Test
    void find03Test() {
        final int limit = 10;

        this.insertTestData(100);
        /*
        top 函数使用的是 mybatis 的 RowBounds，分页原理是先把符合条件的所有数据都拿到，然后才进行分页。
        要想防止出现过大的数据量导致的内存浪费，使用 top 函数是不行的，得通过 endSql 自定义分页限制
         */
        // List<Demo01PO> list = this.mapper.wrapper().top(limit);
        List<Demo01PO> list = this.mapper.wrapper()
                .orderBy(Demo01PO::getId, Example.Order.DESC)
                .endSql("limit " + limit)
                .list();
        log.info("data size: {}", list.size());
        list.forEach(item -> log.info(String.valueOf(item)));
    }

    /**
     * in 的用法
     */
    @Test
    void find04Test() {
        this.insertTestData(100);

        List<Long> ids = Arrays.asList(
                10L, 11L, 12L, 13L, 14L
        );
        List<Demo01PO> list = this.mapper.wrapper()
                .in(Demo01PO::getId, ids)
                .orderBy(Demo01PO::getId, Example.Order.DESC)
                .list();
        log.info("data size: {}", list.size());
        list.forEach(item -> log.info(String.valueOf(item)));
    }

    /**
     * 批量插入数据
     */
    @NotNull
    private List<Demo01PO> insertTestData(int size) {
        Assertions.assertTrue(size > 0, "'size' cannot be negative.");
        List<Demo01PO> dPos = new ArrayList<>();
        for (int i = 0; i < size; i++) {
            Demo01PO dPo = new Demo01PO();
            dPo.setMessage("Hello World");
            dPos.add(dPo);
        }
        log.info("insert {} data.", this.mapper.insertAll(dPos));
        return dPos;
    }
}