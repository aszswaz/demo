import java.util.concurrent.Executors;

@SuppressWarnings({"StatementWithEmptyBody", "LoopConditionNotUpdatedInsideLoop"})
public class Demo02 {
    /**
     * 向虚拟线程的调度器添加一定数量的虚拟线程，并且使用死循环让虚拟线程无法终止
     */
    public static void main(String[] args) throws InterruptedException {
        // 使用自行创建的调度线程运行虚拟线程
        try (var service = Executors.newVirtualThreadPerTaskExecutor()) {
            for (int i = 0; i < 10; i++) {
                int num = i;
                service.submit(() -> {
                    System.out.println("i: " + num);
                    while (args.length == 0){}
                });
            }
        }

        Thread.sleep(500);
    }
}
