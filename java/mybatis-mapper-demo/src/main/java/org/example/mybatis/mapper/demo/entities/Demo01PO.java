package org.example.mybatis.mapper.demo.entities;

import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.ToString;
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
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
@Accessors(chain = true)
@Table(value = "mybatis_mapper_demo")
@SuppressWarnings("JavadocDeclaration")
public class Demo01PO extends BasePO {
    @Column(value = "message")
    private String message;
}
