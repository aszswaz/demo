package com.example.springdatajpademo.entities.po;

import lombok.*;
import lombok.experimental.Accessors;
import org.hibernate.Hibernate;
import org.hibernate.annotations.Comment;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Table;
import java.util.Date;
import java.util.Objects;

/**
 * Jpa 演示
 *
 * @author aszswaz
 * @date 2022-06-27 15:55:24
 */
@SuppressWarnings("JavadocDeclaration")
@Getter
@Setter
@ToString(callSuper = true)
@Accessors(chain = true)
@Table(name = "jpa_demo")
@Entity
public class JpaDemoPO extends BasePO {
    @Comment(value = "文本")
    @Column(name = "text", nullable = false)
    private String text;

    @Comment(value = "时间")
    @Column(name = "time", columnDefinition = "TIMESTAMP(3)", nullable = false)
    private Date time;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || Hibernate.getClass(this) != Hibernate.getClass(o)) return false;
        JpaDemoPO jpaDemoPO = (JpaDemoPO) o;
        return getId() != null && Objects.equals(getId(), jpaDemoPO.getId());
    }
}
