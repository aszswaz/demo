# Introduction

Java JNI demo

# Demo

```bash
$ mkdir out && javac -d out -sourcepath src src/com/example/JniDemo.java
$ cd jni && make
$ java -cp ../out -Djava.library.path="$PWD" com.example.JniDemo
```