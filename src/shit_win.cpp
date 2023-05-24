#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

using namespace std;

char name[260];
time_t newTime = 0;

char* getNewestFile( const char* path )
{
    struct stat buf;
    struct _finddata_t data;
    long hnd = _findfirst( path, &data );    // 查找文件名与正则表达式chRE的匹配第一个文件
    if ( hnd < 0 )
    {
        perror( path );
    }
    int  nRet = (hnd <0 ) ? -1 : 1;
    while ( nRet >= 0 )
    {
        
        if ( data.attrib != _A_SUBDIR )  // 如果是目录
        {
            char name1[260];
            strcpy(name1, data.name);
            stat(data.name, &buf);
            if(buf.st_mtime > newTime)
            {
                newTime = buf.st_mtime;
                strcpy(name, name1);
            }
        }
        nRet = _findnext( hnd, &data );
    }
    _findclose( hnd );     // 关闭当前句柄
}

int main(int argc, char **argv)
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
                if (result != 0)
                {
                    getNewestFile("./*.*");
                    result = stat(name, &buf);
                }
                else
                {
                    strcpy(name, "test.cu");
                }
            }
            else
            {
                strcpy(name, "test.py");
            }
        }
        else
        {
            strcpy(name, "test.c");
        }
    }
    else
    {
        strcpy(name, "test.cpp");
    }

    if (result != 0)
    {
        perror("Error");
    }
    else
    {
        string command;
        command = "shi " + string(name);
        char** param = &argv[1];
        for(int i = 0; i < argc - 1; i++)
        {
            command += " ";
            command += string(param[i]);
        } 
        char finalCommand[256];
        strcpy(finalCommand, command.c_str());
        cout << finalCommand << endl;
        system(finalCommand); 
    }
}
