package org.example.mybatis.mapper.demo.entities;

import lombok.Data;
import lombok.experimental.Accessors;

import static io.mybatis.provider.Entity.Column;
import static io.mybatis.provider.Entity.Table;

/**
 * mybatis mapper 插件演示
 *
 * @author aszswaz
 * @date 2022-06-28 10:50:11
 */
@Data
@Accessors(chain = true)
@Table(value = "mybatis_mapper_demo")
@SuppressWarnings("JavadocDeclaration")
public class Demo01PO {
    @Column(id = true)
    private Long id;
    @Column(value = "message")
    private String message;
}
