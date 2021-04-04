package zhong.demo.java.util.random;

import lombok.extern.log4j.Log4j2;

import java.util.Random;

/**
 * 随机数使用
 *
 * @author aszswaz
 * @date 2021/3/25 16:38:56
 */
@Log4j2
public class RandomDemo {
    public static void main(String[] args) {
        randomInt();
    }

    private static void randomInt() {
        Random random = new Random();
        for (int i = 0; i < 10; i++) {
            log.info(random.nextInt(2));
        }
    }
}
