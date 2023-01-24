package com.example.springdatajpademo.services;

import com.example.springdatajpademo.entities.po.JpaDemoPO;

import java.util.List;

/**
 * JPA 演示
 *
 * @author aszswaz
 * @date 2022-06-27 17:41:58
 */
@SuppressWarnings("JavadocDeclaration")
public interface JpaDemoService {
    /**
     * 清理数据表
     */
    void truncate();

    /**
     * 通过 JPA 的 saveAll 保存数据
     */
    void addBatch01(List<JpaDemoPO> jdPos);

    /**
     * 通过事务批量插入数据
     */
    void addBatch02(List<JpaDemoPO> jdPos);

    /**
     * 单条数据查询
     */
    JpaDemoPO find01();

    /**
     * 批量数据查询
     */
    List<JpaDemoPO> find02(List<String> queries);
}
