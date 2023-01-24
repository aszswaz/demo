import java.util.concurrent.Executors;

public class Demo {
    public static void main(String[] args) throws InterruptedException {
        System.out.println("main thread id: " + Thread.currentThread().threadId());
        // 通过三种方式创建并执行虚拟线程
        v1();
        v2();
        v3();
        v4();
        // 防止 main 函数退出时，虚拟线程还没有启动
        Thread.sleep(1000);
    }

    private static void v1() {
        // 创建并执行虚拟线程
        Thread.startVirtualThread(() ->
                System.out.println("v1, thread id: " + Thread.currentThread().threadId()));
    }

    private static void v2() {
        // 创建虚拟线程
        var t = Thread.ofVirtual().unstarted(() ->
                System.out.println("v2, thread id: " + Thread.currentThread().threadId()));
        // 执行虚拟线程
        t.start();
    }

    /**
     * 通过 ThreadFactory 创建虚拟线程
     */
    private static void v3() {
        // 创建 ThreadFactory
        var tf = Thread.ofVirtual().factory();
        // 创建虚拟线程
        var t = tf.newThread(() ->
                System.out.println("v3, thread id: " + Thread.currentThread().threadId()));
        t.start();
    }

    /**
     * 直接调用虚拟线程的 start()，实际上是由 ForkJoinPool 的线程来进行调度的，我们也可以自己创建调度线程，然后运行虚拟线程
     */
    private static void v4() {
        try (var service = Executors.newVirtualThreadPerTaskExecutor()) {
            var tf = Thread.ofVirtual().factory();
            service.submit(() -> System.out.println("v4, thread id: " + Thread.currentThread().threadId()));
        }
    }
}