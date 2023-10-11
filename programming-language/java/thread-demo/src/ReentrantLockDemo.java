import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * 公平锁演示
 */
public class ReentrantLockDemo extends Thread {
    private static int num;

    private final Lock lock;

    public ReentrantLockDemo(Lock lock) {
        this.lock = lock;
    }

    public static void main(String[] args) {
        // 公平锁
        Lock lock = new ReentrantLock(true);
        // 非公平锁
        // Lock lock = new ReentrantLock(false);

        for (int i = 0; i < 10; i++) {
            Thread t1 = new ReentrantLockDemo(lock);
            t1.start();
        }
    }

    @Override
    public void run() {
        lock.lock();

        try {
            num++;
            Thread.sleep(100);
            System.out.println("thread id: " + super.getId() + ", " + num);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
        }
    }
}