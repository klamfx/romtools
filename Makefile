all: dump mergerom splitrom

mergerom: mergerom.c
	gcc -o mergerom mergerom.c 

dump: dump.c
	gcc -o dump dump.c

splitrom: splitrom.c
	gcc -o splitrom splitrom.c 

clean:
	rm -f mergerom splitrom dump
