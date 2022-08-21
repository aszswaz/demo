all: pipeline popen

pipeline: pipeline.c
		gcc $^ -o $@ -lpipeline

popen: popen.c
	gcc $^ -o $@

clean:
	rm pipeline
	rm popen
