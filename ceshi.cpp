#include <iostream>
#include <iterator>
#include <cstring>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/program_options/parsers.hpp>
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
    void compile(string fileName, int argc, char **param)
    {
        string parameters = handleParam(argc, param);
        compose(fileName, parameters);
        return;
    }

    string handleParam(int argc, char **param = nullptr)
    {
        string command;
        for(int i = 0; i < argc; i++)
        {
            command += " ";
            command += string(param[i]);
        }
        return command;
    }
    
    virtual void compose(string fileName, string param);
};

class cuda : public interpreter
{
    public:
    void compose(string fileName, string param)
    {
        string head = getHead(fileName);
        string command;
//      command = format("nvcc {} -o test_{}", fileName, head);
        command = "nvcc " + fileName + " -o test_" + head;
        command += param;
        char finalCommand[256];
        strcpy(finalCommand, command.c_str());
        cout << finalCommand << endl;
        system(finalCommand);
        return;
    }
};

class python : public interpreter
{
    public:
    void compose(string fileName, string param)
    {
        string head = getHead(fileName);
        string command;
        command = "python " + fileName;
        command += param;
        char finalCommand[256];
        strcpy(finalCommand, command.c_str());
        cout << finalCommand << endl;
        system(finalCommand);
        return;
    }
};

    typedef map<string, string> dic;
    typedef map<string, interpreter*> inter;

int ceshi(int argc, char **argv)
{
    string fileName = argv[0];
    string tail = getTail(fileName);

    dic f2l;
    inter l2c;
    
    // Add S.1
    cuda cudaCompiler;
    python pythonCompiler;

    // Add S.2
    f2l["cu"] = "cuda";
    f2l["py"] = "python";

//    cout << f2l[tail] << endl;

    // Add S.3
    l2c["cuda"] = &cudaCompiler;
    l2c["python"] = &pythonCompiler;

    interpreter* ptr = l2c[f2l[tail]];
    ptr->compile(fileName, argc - 1, &argv[1]);

    /*if(f2l[tail] == "cuda")
        cudaCompiler.compile(fileName, argc - 2, &argv[2]);
    */
    return 0;
}

int ceshiMode()
{
    string arguments;
    while(cin >> arguments)
    {
        cout << arguments << endl;
        if(arguments == "quit")
            return 0;
    }
    return 0;
}


int main(int argc, char **argv)
{
    string test = "hel asdj qweiq";
    vector<string> args = boost::program_options::split_winmain(test);
    std::cout << args[0] << endl;
    if(argc == 1)
    {
        ceshiMode();
        return 0;
    }
    ceshi(argc - 1, &argv[1]);
    return 0;
}