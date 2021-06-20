#include <io.h>
#include <stdio.h>
 
void printDir( const char* path )
{
    struct _finddata_t data;
    long hnd = _findfirst( path, &data );    // 查找文件名与正则表达式chRE的匹配第一个文件
    if ( hnd < 0 )
    {
        perror( path );
    }
    int  nRet = (hnd <0 ) ? -1 : 1;
    while ( nRet >= 0 )
    {
        if ( data.attrib == _A_SUBDIR )  // 如果是目录
            printf("   [%s]*\n", data.name );
        else
            printf("   [%s]\n", data.name );
        nRet = _findnext( hnd, &data );
    }
    _findclose( hnd );     // 关闭当前句柄
}
void main()
{
    printDir("./*.*");
}