import java.util.concurrent.atomic.AtomicReference;

/**
 * 自旋锁演示
 */
@SuppressWarnings("unused")
public class SpinLockDemo {
    private static final AtomicReference<Object> CAS = new AtomicReference<>();
    private final Object lock = new Object();

    @SuppressWarnings("StatementWithEmptyBody")
    public void lock() {
        // 利用 CAS 实现自旋锁
        while (!CAS.compareAndSet(null, this.lock)) ;
    }

    public void unlock() {
        CAS.compareAndSet(this.lock, null);
    }
}
