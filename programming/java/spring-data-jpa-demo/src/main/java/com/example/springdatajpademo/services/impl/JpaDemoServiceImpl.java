package com.example.springdatajpademo.services.impl;

import com.example.springdatajpademo.entities.po.JpaDemoPO;
import com.example.springdatajpademo.repositories.JpaDemoRepository;
import com.example.springdatajpademo.services.JpaDemoService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Example;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.Assert;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import java.util.List;

/**
 * JPA 演示
 *
 * @author aszswaz
 * @date 2022-06-27 17:42:29
 */
@Service
@Slf4j
@SuppressWarnings("JavadocDeclaration")
public class JpaDemoServiceImpl implements JpaDemoService {
    @PersistenceContext
    private EntityManager em;
    private final JpaDemoRepository repository;

    @Autowired
    public JpaDemoServiceImpl(
            JpaDemoRepository repository
    ) {
        this.repository = repository;
    }

    @Transactional
    @Override
    public void truncate() {
        this.em.createNativeQuery("TRUNCATE jpa_demo").executeUpdate();
    }

    @Override
    public void addBatch01(List<JpaDemoPO> jdPos) {
        this.repository.saveAll(jdPos);
        jdPos.forEach(item -> log.info(String.valueOf(item)));
    }

    @Transactional
    @Override
    public void addBatch02(List<JpaDemoPO> jdPos) {
        Assert.notEmpty(jdPos, "jd pos can not be null.");
        for (JpaDemoPO jdPo : jdPos) {
            this.em.persist(jdPo);
        }
        jdPos.forEach(item -> log.info(String.valueOf(item)));
    }

    @Override
    public JpaDemoPO find01() {
        JpaDemoPO jdPo = new JpaDemoPO();
        jdPo.setText("Hello World-24");
        return this.repository.findOne(Example.of(jdPo)).orElse(null);
    }

    @Override
    public List<JpaDemoPO> find02(List<String> queries) {
        return this.repository.findByText01(queries);
    }
}
