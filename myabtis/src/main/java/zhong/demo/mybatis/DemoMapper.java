package zhong.demo.mybatis;

import org.apache.ibatis.annotations.Param;

import javax.annotation.PostConstruct;

/**
 * @author aszswaz
 * @date 2021/3/24 17:47:01
 */
@SuppressWarnings("JavaDoc")
public interface DemoMapper {
    Integer selectIndex(
            @Param(value = "more") int more
    );

    int insertIndex(
            @Param(value = "index") int index
    );

    /**
     * 清理表格
     */
    void clear();
}
