libJniEntity.so: com_example_JniEntity.h com_example_JniEntity.c
	gcc -I/usr/lib/jvm/java-8-openjdk/include \
		-I/usr/lib/jvm/java-8-openjdk/include/linux \
		-shared \
		$^ \
		-o $@

clean:
	rm libJniEntity.so
