
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/*
 * int main(int argc, char **argv) 
 * 参数解读
 * 
 * ./copy 1.txt 2.txt
 * argc    = 3
 * argv[0] = "./copy"
 * argv[1] = "1.txt"
 * argv[2] = "2.txt"
 */
int main(int argc, char **argv)
{
	int fd_old, fd_new;
	
	
	/* 1. 判断参数 */
	if (argc != 3) 
	{
		printf("Usage: %s <old-file> <new-file>\n", argv[0]);
		return -1;
	}

	/* 2. 打开老文件 */
	fd_old = open(argv[1], O_RDONLY);
	if (fd_old == -1)
	{
		printf("can not open file %s\n", argv[1]);
		return -1;
	}

	/* 3. 创建新文件
	int open(const char *pathname, int flags, mode_t mode);

	flag:
	a. O_RDWR表示可读可写方式打开;
	b. O_RDONLY表示只读方式打开;
	c. O_WRONLY表示只写方式打开;
	d. O_APPEND 表示如果这个文件中本来是有内容的，则新写入的内容会接续到原来内容的后面;
	e. O_TRUNC表示如果这个文件中本来是有内容的，则原来的内容会被丢弃，截断；
	f. O_CREAT表示当前打开文件不存在，我们创建它并打开它，通常与O_EXCL结合使用，当没有文件时创建文件，有这个文件时会报错提醒我们；

	mode:
	Mode表示创建文件的权限，只有在flags中使用了O_CREAT时才有效，否则忽略。
	S_IRUSR 文件所属用户 读
	S_IWUSR 文件所属用户 写
	S_IRGRP 与文件所属用户同组 读
	S_IWGRP 与文件所属用户同组 写
	S_IROTH 其他用户 读
	S_IWOTH 其他用户 写

	 */ 
	fd_new = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd_new == -1)
	{
		printf("can not creat file %s\n", argv[2]);
		return -1;
	}

	/* 4. 循环： 读老文件-写新文件 */
	char buf[1024]; //缓冲区
	int len; //读取长度

	//每次从老文件最多读取1024个字节到buf，实际读取为长度len
	while ((len = read(fd_old, buf, 1024)) > 0)
	{
		//若len与写入长度不同，说明出错了
		if (write(fd_new, buf, len) != len)
		{
			printf("can not write %s\n", argv[2]);
			return -1;
		}
	}

	/* 5. 关闭文件 */
	close(fd_old);
	close(fd_new);
	
	return 0;
}

