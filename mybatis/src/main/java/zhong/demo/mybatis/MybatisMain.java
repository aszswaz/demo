package zhong.demo.mybatis;

import lombok.extern.log4j.Log4j2;
import org.apache.ibatis.session.SqlSession;

import java.io.IOException;
import java.util.Objects;

/**
 * @author aszswaz
 * @date 2021/3/24 17:34:07
 */
@Log4j2
@SuppressWarnings("JavaDoc")
public class MybatisMain {
    public static void main(String[] args) throws IOException {
        MybatisUtil mybatisUtil = new MybatisUtil();
        SqlSession sqlSession = mybatisUtil.getSession();
        DemoMapper demoMapper = sqlSession.getMapper(DemoMapper.class);

        Integer index = 0;
        long start = System.currentTimeMillis();
        for (int i = 0; i < 9000; i++) {
            index = demoMapper.selectIndex(index);
            index = Objects.isNull(index) ? 0 : index;
            index++;
            demoMapper.insertIndex(index);
            if (System.currentTimeMillis() - start >= 1000) {
                log.info(index);
                start = System.currentTimeMillis();
            }
            sqlSession.commit();
        }
        demoMapper.clear();
        sqlSession.commit();
        sqlSession.close();
    }
}
