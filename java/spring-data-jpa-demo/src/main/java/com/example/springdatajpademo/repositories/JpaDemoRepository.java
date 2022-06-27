package com.example.springdatajpademo.repositories;

import com.example.springdatajpademo.entities.po.JpaDemoPO;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

import java.util.List;

/**
 * JPA 演示
 *
 * @author aszswaz
 * @date 2022-06-27 16:03:11
 */
@SuppressWarnings("JavadocDeclaration")
public interface JpaDemoRepository extends JpaRepository<JpaDemoPO, Long> {
    /**
     * 批量查询
     */
    @Query(value = "FROM JpaDemoPO WHERE text IN (:queries)")
    List<JpaDemoPO> findByText01(@Param(value = "queries") List<String> queries);
}
