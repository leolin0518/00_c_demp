#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fpm = NULL;
    char buff[255];
    int value = 1;
    //以只读模式 r 打开文件 返回文件指针
    fpm = fopen("/etc/.multi_touch", "r");
    if(fpm != NULL)
    {

         fscanf(fpm, "%s", buff); //使用fscanf读入一个字符串 遇到空格结束
         value = atoi(buff);
         printf("buff:%s\n", buff );
         printf("value:%d\n", value );
         fclose(fpm);
    }
    else
    {
         printf("fopen error\n");
         value = 1;
    }

   return 0;
}

//---------------------------------------
kylin@kylin-badindex:~$ gcc a.c -o a
kylin@kylin-badindex:~$ ./a
buff:0
value:0
kylin@kylin-badindex:~$ cat /etc/.multi_touch
0  //0 is disable, 1 is enbale mutil touch
kylin@kylin-badindex:~$ vim /etc/.multi_touch
kylin@kylin-badindex:~$ sudo vim /etc/.multi_touch
输入密码
kylin@kylin-badindex:~$ ./a
buff:1
value:1
kylin@kylin-badindex:~$

