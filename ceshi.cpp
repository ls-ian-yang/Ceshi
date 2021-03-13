#include <iostream>
#include <cstring>
#include <string>
//#include <format>
#include <map>
using namespace std;

string getTail(string fileName)
{
    size_t pos = 0;
    string token;
    string delimiter = ".";
    while((pos = fileName.find(delimiter)) != string::npos)
    {
        token = fileName.substr(0, pos);
//        cout << token << endl;
        fileName.erase(0, pos + delimiter.length());
    }
    
    return fileName;
}

string getHead(string fileName)
{
    size_t pos = 0;
    string token;
    string delimiter = ".";
    if((pos = fileName.find(delimiter)) != string::npos)
    {
        token = fileName.substr(0, pos);
        return token;
    }
    return nullptr;
}

class interpreter
{
    public:
    void compile(char **param)
    {
        cout<<"Compiling"<<endl;
        return;
    }
};

class cuda : public interpreter
{
    public:
    void compile(string fileName, char **param = nullptr)
    {
        string head = getHead(fileName);
        string tail = getTail(fileName); 
//        cout<<fileName<<head<<tail<<endl;
        string command;
//       command = format("nvcc {} -o test_{}", fileName, head);
        command = "nvcc " + fileName + " -o test_" + head;
        char finalCommand[100];
        strcpy(finalCommand, command.c_str());
//        cout<<finalCommand<<endl;
        system(finalCommand);
//        cout<<"happy"<<endl;
        return;
    }
};


int main(int argc, char **argv)
{
    string fileName = argv[1];
    string tail = getTail(fileName);
//    cout<< tail <<endl;
    typedef map<string, string> dic;
    typedef map<string, interpreter*> inter;
    dic f2l;
    inter l2c;
    f2l["cu"] = "cuda";
    cuda cudaCompiler;
//    cout << f2l[tail] << endl;
/*
    l2c["cuda"] = cudaCompiler;
    l2c[f2l[tail]].compile(argv);
*/
    if(f2l[tail] == "cuda")
        cudaCompiler.compile(fileName);
}