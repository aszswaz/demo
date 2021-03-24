package zhong.demo.mybatis;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;

/**
 * @author aszswaz
 * @date 2021/3/24 18:21:33
 */
@SuppressWarnings("JavaDoc")
public class MybatisUtil {
    private final SqlSessionFactory sessionFactory;

    public MybatisUtil() throws IOException {
        InputStream inputStream = Resources.getResourceAsStream("mybatis.xml");
        this.sessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
        inputStream.close();
    }

    public SqlSession getSession() {
        return sessionFactory.openSession();
    }
}
