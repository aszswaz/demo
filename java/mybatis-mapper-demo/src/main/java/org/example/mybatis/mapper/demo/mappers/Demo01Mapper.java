package org.example.mybatis.mapper.demo.mappers;

import io.mybatis.mapper.Mapper;
import org.apache.ibatis.annotations.Param;
import org.example.mybatis.mapper.demo.entities.Demo01PO;

import java.util.List;

/**
 * mybatis mapper 插件应用演示
 *
 * @author aszswaz
 * @date 2022-06-28 10:48:59
 */
@SuppressWarnings("JavadocDeclaration")
public interface Demo01Mapper extends Mapper<Demo01PO, Long> {
    /**
     * 创建表格
     */
    void createTable();

    /**
     * 清理数据表
     */
    void clear();

    /**
     * 批量插入数据
     */
    int insertAll(@Param(value = "dPos") List<Demo01PO> dPos);
}
