
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
 
int main()
{
    struct stat buf;
    int result;
 
    //获得文件状态信息
 
    result =stat( "./ceshi.cpp", &buf );
 
    //显示文件状态信息
 
    if( result != 0 )
       perror( "Error: " );//并提示出错的原因，如No such file or directory（无此文件或索引）
 
    else
    {
 
        printf("Size: %d\n", buf.st_size);
        printf("Creat time: %s", ctime(&buf.st_ctime));
        printf("Access time: %s", ctime(&buf.st_atime));
        printf("Modify time: %s", ctime(&buf.st_mtime));
 
    }
}
