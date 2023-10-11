package com.example.springdatajpademo.entities.po;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;
import lombok.experimental.Accessors;
import org.hibernate.Hibernate;

import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.MappedSuperclass;
import java.util.Objects;

/**
 * PO 类的基类
 *
 * @author aszswaz
 * @date 2022-06-27 15:56:00
 */
@SuppressWarnings("JavadocDeclaration")
@Getter
@Setter
@ToString
@Accessors(chain = true)
@MappedSuperclass
public abstract class BasePO {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || Hibernate.getClass(this) != Hibernate.getClass(o)) return false;
        BasePO basePO = (BasePO) o;
        return id != null && Objects.equals(id, basePO.id);
    }
}
