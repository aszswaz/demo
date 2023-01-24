package example;

/**
 * class 方面的演示
 *
 * @author aszswaz
 * @date 2022-07-04 17:00:33
 */
@SuppressWarnings({"JavadocDeclaration", "ConstantConditions"})
public class ClassDemo {
    public static void main(String[] args) {
        classEquals();
    }

    private static void classEquals() {
        System.out.println("Boolean.class == boolean.class: " + (Boolean.class == boolean.class));
        System.out.println("Byte.class == byte.class: " + (Byte.class == byte.class));
        System.out.println("Short.class == short.class: " + (Short.class == short.class));
        System.out.println("Integer.class == int.class: " + (Integer.class == int.class));
        System.out.println("Long.class == long.class: " + (Long.class == long.class));

        System.out.println("Boolean.class.isInstance(true): " + Boolean.class.isInstance(true));
        System.out.println("boolean.class.isInstance(true)): " + boolean.class.isInstance(true));
    }
}
