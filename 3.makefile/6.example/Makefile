#把前面几节的运用起来

#当依赖中包含.h头文件时，只关心.c的变化就不够了，还需要关心头文件的变化

objs = main.o

dep_files := $(patsubst %,.%.d,$(objs)) #依赖文件名为 a.o -> .a.o.d
dep_files := $(wildcard $(dep_files)) #过滤出真实存在的文件

#使用cflag
CFLAGS = -Werror # 把所有警告当成错误
CFLAGS += -Iinclude # 指定头文件搜索路径


test: $(objs)
	gcc -o test $^ 

#注意ifneq后要加空格
ifneq ($(dep_files),)
include $(dep_files) #include包含别的makefile，这里即依赖文件
endif

%.o : %.c
	gcc $(CFLAGS) -c -o $@ $< -MD -MF .$@.d  #-MD表示输出依赖makefile文件xxx.dep  -MF .$@.d表示把xxx.dep 改名为.$@.d

clean:
	rm *.o
	rm test

distclean:
	rm $(dep_files)

# 有同名clean的文件，必须把clean目标定义为假想目标
.PHONY:clean
