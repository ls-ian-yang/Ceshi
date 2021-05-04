#include <iostream>
#include <iterator>
#include <cstring>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/program_options/parsers.hpp>
#include <map>
using namespace std;

/*
-----------------------------------------------------------------
    Environments variables
-----------------------------------------------------------------
*/

int defaultMode[10] = {0,0,0,0,0,0,0,0,0,0};

/*
-----------------------------------------------------------------
    Helper functions:
        getTail
        getHead
-----------------------------------------------------------------
*/

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


/*
-----------------------------------------------------------------
    Interpreters:
        Interpreter:
            cuda
            python
            CPP
    Functions:
        compile
            handleParam
            compose*
-----------------------------------------------------------------
*/

class interpreter
{
    public:
    void compile(string fileName, int argc, char **param, int *mode = defaultMode)
    {
        string parameters = handleParam(argc, param, mode);
        compose(fileName, parameters, mode);
        return;
    }

    string handleParam(int argc, char **param = nullptr, int *mode = defaultMode)
    {
        string command;
        for(int i = 0; i < argc; i++)
        {
            command += " ";
            command += string(param[i]);
        }
        return command;
    }
    
    virtual void compose(string fileName, string param, int *mode = defaultMode);
};

class cuda : public interpreter
{
    public:
    void compose(string fileName, string param, int *mode = defaultMode)
    {
        string prefix = "";
        if(mode[0])
        {
            prefix = "test_";
        }

        string head = getHead(fileName);
        string command;
        command = "nvcc " + fileName + " -o " + prefix + head;
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
    void compose(string fileName, string param, int *mode = defaultMode)
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

class CPP : public interpreter
{
    public:
    void compose(string fileName, string param, int *mode = defaultMode)
    {
        string prefix = "";
        if(mode[0])
        {
            prefix = "test_";
        }

        string head = getHead(fileName);
        string command;
        command = "g++ " + fileName + " -o " + prefix + head;
        command += param;
        char finalCommand[256];
        strcpy(finalCommand, command.c_str());
        cout << finalCommand << endl;
        system(finalCommand);
        return;
    }
};


/*
-----------------------------------------------------------------
    Body of function:
        Analyse arguments
        Define the to main lists
        Define compilers *
        Tell the language *
        Get Compiler *
        Run compile
-----------------------------------------------------------------
*/

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
    CPP cppCompiler;

    // Add S.2
    f2l["cu"] = "cuda";
    f2l["py"] = "python";
    f2l["cpp"] = "cpp";
    f2l["c++"] = "cpp";
    f2l["c"] = "cpp";

    // Add S.3
    l2c["cuda"] = &cudaCompiler;
    l2c["python"] = &pythonCompiler;
    l2c["cpp"] = &cppCompiler;

    interpreter* ptr = l2c[f2l[tail]];
    ptr->compile(fileName, argc - 1, &argv[1]);

    return 0;
}

/*
-----------------------------------------------------------------
    Ceshi mode
-----------------------------------------------------------------
*/

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

/*
-----------------------------------------------------------------
    Main:
        Enter ceshi mode OR
        Compile as normal
-----------------------------------------------------------------
*/

int main(int argc, char **argv)
{
    if(argc == 1)
    {
        ceshiMode();
        return 0;
    }
    ceshi(argc - 1, &argv[1]);
    return 0;
}