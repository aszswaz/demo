@Suppress("RedundantSetter", "RedundantGetter")
class ObjectDemo {
    var name01 = "name01"
        // 属性的 get/set 函数，field get/set 函数所对应的属性
        get() = "Hello World"
        set(value) {
            field = value
        }

    var name02 = "name02"
        get() = field
        set(value) {
            field = value
            println("value: $value")
        }
}

fun main() {
    val obj = ObjectDemo()
    // 给属性赋值时自动调用属性的 set 函数
    obj.name01 = "我去"
    obj.name02 = "啦啦"
    // 通过属性的 get 函数取值
    println("obj.name01: ${obj.name01}")
}