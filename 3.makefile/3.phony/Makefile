#假想目标
test: a.o b.o c.o
	gcc -o test $^ 

%.o : %.c
	gcc -c -o $@ $< 

clean:
	rm *.o
	rm test

# 有同名clean的文件，必须把clean目标定义为假想目标
.PHONY:clean
