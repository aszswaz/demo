libJniEntity.so: com_example_JniEntity.h com_example_JniEntity.c
	gcc -I/usr/lib/jvm/java-8-openjdk/include \
		-I/usr/lib/jvm/java-8-openjdk/include/linux \
		-o libJniEntity.so -shared com_example_JniEntity.c

clean:
	rm libJniEntity.so
