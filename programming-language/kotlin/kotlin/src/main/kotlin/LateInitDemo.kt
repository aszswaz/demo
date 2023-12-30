/**
 * 在 kotlin 中，类的属性在声明时必须被初始化，lateinit 关键字的作用就是让属性在需要初始化的时候才进行赋值
 */
class LateInitDemo {
    private lateinit var demo01: String

    fun printDemo01() {
        // 判断属性是否已经初始化
        if (::demo01.isInitialized)
            println("demo01: $demo01")
        else
            println("demo01 is not initialized")
    }
}

fun main() {
    val obj = LateInitDemo()
    obj.printDemo01()
}