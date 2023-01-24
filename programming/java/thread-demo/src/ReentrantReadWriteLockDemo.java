import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * 读写锁演示
 */
public class ReentrantReadWriteLockDemo extends Thread {
    private static final Lock READ_LOCK;
    private static final Lock WRITE_LOCK;

    static {
        ReadWriteLock lock = new ReentrantReadWriteLock();
        READ_LOCK = lock.readLock();
        WRITE_LOCK = lock.writeLock();
    }

    public static void main(String[] args) {
        for (int i = 0; i < 4; i++) {
            new ReentrantReadWriteLockDemo().start();
        }
    }

    /**将
     * ReadLock 是共享锁，它允许被多个线程同时持有
     * WriteLock 是独占锁，同一时间内只允许单个线程持有
     * ReadLock 和 WriteLock 是互斥的，ReadLock 被获取时，无法获取 WriteLock，反过来说，WriteLock 被获取时，无法获取 ReadLock
     */
    @Override
    public void run() {
        try {
            READ_LOCK.lock();
            System.out.println(System.currentTimeMillis() % 100000 + " thread id: " + this.getId() + ", get ReadLock.");
            READ_LOCK.unlock();

            WRITE_LOCK.lock();
            System.out.println(System.currentTimeMillis() % 100000 + " thread id: " + this.getId() + ", get WriteLock.");
            Thread.sleep(1000);
            WRITE_LOCK.unlock();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
