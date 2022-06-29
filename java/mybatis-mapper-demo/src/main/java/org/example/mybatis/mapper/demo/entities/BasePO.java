package org.example.mybatis.mapper.demo.entities;

import io.mybatis.provider.Entity.Column;
import lombok.Data;
import lombok.experimental.Accessors;

/**
 * @author aszswaz
 * @date 2022-06-29 10:04:16
 */
@Data
@Accessors(chain = true)
@SuppressWarnings("JavadocDeclaration")
public abstract class BasePO {
    @Column(id = true)
    private Long id;
}
