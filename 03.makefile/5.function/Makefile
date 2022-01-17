A = a b c

#$(foreach x, set, cmd)
#遍历A里的item，每个item赋值给f，再执行$f.o
B = $(foreach f, $A, $f.o)



#$(filter pattern, set)
# 找出set内符合pattern的元素
C = a b c d/
D = $(filter %/, $C) #找到以"/"结尾的元素
E = $(filter-out %/, $C) #找到不以"/"结尾的元素

#$(wildcard pattern)
files = $(wildcard *.c) #找到符合*.c的文件

file_list = a.c b.c c.c e.c f.c g.c abc
files_exists = $(wildcard $(file_list)) #找出真实存在的文件

#$(patsubst pattern,replacement,$(var))
#从var中把每个元素符合pattern的部分改成replacement
replaced_file_list = $(patsubst %.c, %.d,$(file_list))


all:
	@echo B=$B
	@echo D=$D
	@echo E=$E
	@echo files=$(files)
	@echo files_exists=$(files_exists)
	@echo replaced_file_list=$(replaced_file_list)