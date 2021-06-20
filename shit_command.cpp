
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
 
int main()
{
    struct stat buf;
    int result;
 
    //假设当前文件夹只有一种语言的test文件    
    result = stat("./test.cpp", &buf);
    if (result != 0)
    { 
        result =stat("./test.c", &buf);
        if (result != 0)
        {
            result =stat("./test.py", &buf);
            if (result != 0)
            { 
                result =stat("./test.cu", &buf);
            }
        }
    }
    if (result != 0)
    {
        perror("Error");
    }
    else
    {
        printf("Size: %d\n", buf.st_size);
        printf("Creat time: %s", ctime(&buf.st_ctime));
        printf("Access time: %s", ctime(&buf.st_atime));
        printf("Modify time: %s", ctime(&buf.st_mtime));
    }
}
