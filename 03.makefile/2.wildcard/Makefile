#通配符
#$^表示所有依赖
test: a.o b.o c.o
	gcc -o test $^ 

#使用%.o:%.c （增加任意.o，都不用增加 xxx.o:xxx.c）
#$@表示目标文件  #$<表示第一个依赖（即%.c）
%.o : %.c
	gcc -c -o $@ $< 

clean:
	rm *.o
	rm test
