import java.util.concurrent.Executors;

@SuppressWarnings({"StatementWithEmptyBody", "LoopConditionNotUpdatedInsideLoop"})
public class Demo02 {
    /**
     * 测试当虚拟线程进行 BIO 操作或 sleep() 时，是否真的切换到其他的虚拟线程去运行了
     */
    public static void main(String[] args) throws InterruptedException {
        // 使用自行创建的调度线程运行虚拟线程
        try (var service = Executors.newVirtualThreadPerTaskExecutor()) {
            for (int i = 0; i < 10; i++) {
                int num = i;
                service.submit(() -> {
                    try {
                        System.out.println("i: " + num);
                        // BIO 操作有些麻烦，这里用 sleep 代替，暂停当前虚拟线程，执行其他虚拟线程
                        Thread.sleep(5000);
                        // 由于死循环的存在，只有部分虚拟线程可以继续执行，其他虚拟线程会永远的处于 sleep 状态
                        System.out.println("wait, i: " + num);
                        while (args.length == 0) {}
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                });
            }
        }

        Thread.sleep(500);
    }
}
