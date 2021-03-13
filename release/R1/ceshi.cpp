#include <iostream>
#include <iterator>
#include <cstring>
#include <string>
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
    void compile(string fileName, int argc, char **param = nullptr)
    {
        string head = getHead(fileName);
        string tail = getTail(fileName); 
        string command;
        command = "nvcc " + fileName + " -o test_" + head;
        for(int i = 0; i < argc; i++)
        {
            command += " ";
            command += string(param[i]);
        }
        char finalCommand[256];
        strcpy(finalCommand, command.c_str());
        cout << finalCommand << endl;
        system(finalCommand);
        return;
    }
};


    typedef map<string, string> dic;
    typedef map<string, interpreter*> inter;

int main(int argc, char **argv)
{
    dic f2l;
    inter l2c;
    cuda cudaCompiler;
    f2l["cu"] = "cuda";

    string fileName = argv[1];
    string tail = getTail(fileName);

    if(f2l[tail] == "cuda")
        cudaCompiler.compile(fileName, argc - 2, &argv[2]);
}