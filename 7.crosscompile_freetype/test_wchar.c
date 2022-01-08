#include <stdio.h>
#include <string.h>
#include <wchar.h>

int main( int argc, char** argv)
{
	//wchar_t保存的一定时unicode值
	wchar_t *chinese_str = L"中gif";
	unsigned int *p = (wchar_t *)chinese_str;
	int i;

	printf("sizeof(wchar_t) = %d, str's Uniocde: \n", (int)sizeof(wchar_t));
	for (i = 0; i < wcslen(chinese_str); i++)
	{
		printf("0x%x ", p[i]);
	}
	printf("\n");

	return 0;
}

