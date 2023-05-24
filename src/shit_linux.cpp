#include <time.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include <string>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

using namespace std;

char name[260];
time_t newTime = 0;

char* getNewestFile( const char* path )
{
    DIR *dir;
    struct stat buf;
    struct dirent *ptr;
    dir = opendir(".");
    
    while((ptr = readdir(dir)) != NULL)
    {
        char name1[260];
        strcpy(name1, ptr->d_name);
        stat(ptr->d_name, &buf);
        if(!S_ISDIR(buf.st_mode))
        {
            if(buf.st_mtime > newTime)
            {
                newTime = buf.st_mtime;
                strcpy(name, name1);
            }
        }
    }

    closedir(dir);
    return 0;
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
