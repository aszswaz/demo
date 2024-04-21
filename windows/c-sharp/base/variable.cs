using System;

class Laucher {
    public static void Main(string[] args) {
        var n1 = 100;
        var n2 = 200;
        Console.WriteLine("n1 + n2: " + (n1 + n2));

        int n3 = 100;
        Console.WriteLine("int: " + n3);
        string n4 = "Hello World";
        Console.WriteLine("string: " + n4);
        long n5 = 100;
        Console.WriteLine("long: " + n5);
        short n6 = 100;
        Console.WriteLine("short: " + n6);
        // 16 位 unicode 字符
        char n7 = 'A';
        Console.WriteLine("char: " + n7);
        float n8 = 100.01f;
        Console.WriteLine("float: " + n8);
        double n9 = 100.05;
        Console.WriteLine("double: " + n9);
        // 8 位有符号整数
        sbyte n10 = 100;
        Console.WriteLine("sbyte: " + n10);

        // 无符号整数
        uint n11 = 100;
        Console.WriteLine("uint: " + n11);
        // 8 位无符号整数
        byte n12 = 100;
        Console.WriteLine("byte: " + n12);
        ulong n13 = 10000;
        Console.WriteLine("ulong: " + n13);
        ushort n14 = 100;
        Console.WriteLine("ushort: " + n14);

        bool n15 = true;
        Console.WriteLine("bool: " + n15);
    }
}