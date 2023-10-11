package com.example.springdatajpademo.repositories;

import com.example.springdatajpademo.entities.po.JpaDemoPO;
import com.example.springdatajpademo.services.JpaDemoService;
import lombok.extern.slf4j.Slf4j;
import org.jetbrains.annotations.NotNull;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.stream.Collectors;

/**
 * @author aszswaz
 * @date 2022-06-27 16:03:49
 */
@SuppressWarnings("JavadocDeclaration")
@Slf4j
@SpringBootTest
class JpaDemoRepositoryTest {
    @Autowired
    private JpaDemoService service;

    @BeforeEach
    void setUp() {
        this.service.truncate();
    }

    /**
     * 通过 saveAll 进行批量插入，是一条数据执行一次 SQL
     */
    @Test
    void insertTest01() {
        this.service.addBatch01(this.getData01());
    }

    /**
     * 通过事务执行批量插入
     */
    @Test
    void insertTest02() {
        this.service.addBatch02(this.getData01());
    }

    /**
     * 单条数据查询
     */
    @Test
    void findTest01() {
        this.insertTest02();
        log.info(String.valueOf(this.service.find01()));
    }

    /**
     * 批量数据查询
     */
    @Test
    void findTest02() {
        this.insertTest02();
        List<String> texts = this.getData01(20, 20).stream().map(JpaDemoPO::getText).collect(Collectors.toList());
        this.service.find02(texts).forEach(item -> log.info(String.valueOf(item)));
    }

    /**
     * 生成一批数据
     */
    @NotNull
    private List<JpaDemoPO> getData01() {
        return this.getData01(0, 1000);
    }

    @NotNull
    private List<JpaDemoPO> getData01(int offset, int count) {
        final Date currentTime = new Date();
        List<JpaDemoPO> jdPos = new ArrayList<>();
        for (int i = offset; i < offset + count; i++) {
            JpaDemoPO jdPo = new JpaDemoPO()
                    .setText("Hello World-" + i)
                    .setTime(currentTime);
            jdPos.add(jdPo);
        }
        return jdPos;
    }
}