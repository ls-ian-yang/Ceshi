#include <iostream>
#include <iterator>
#include <cstring>
#include <string>
#include <vector>
//#include <boost/foreach.hpp>
//#include <boost/program_options/parsers.hpp>
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

void executeString(string command)
{
    char finalCommand[256];
    strcpy(finalCommand, command.c_str());
    cout << finalCommand << endl;
    system(finalCommand);
    return;
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
    
    virtual void compose(string fileName, string param, int *mode = defaultMode)
    {
        return;
    };
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
//      command = format("nvcc {} -o test_{}", fileName, head);
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
    //cout << f2l[tail] << endl;

    //Return error if the file is not defined.
    if(f2l[tail] == "")
    {
        cout << "File type ." << tail << " is not supported";
        return 1;
    }

    // Add S.3
    l2c["cuda"] = &cudaCompiler;
    l2c["python"] = &pythonCompiler;
    l2c["cpp"] = &cppCompiler;

    interpreter* ptr = l2c[f2l[tail]];
    ptr->compile(fileName, argc - 1, &argv[1]);

    /*if(f2l[tail] == "cuda")
        cudaCompiler.compile(fileName, argc - 2, &argv[2]);
    */
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
        //Need a real split later
        if(getTail(arguments) != arguments)
        {
            char * argv[1] = {(char*)arguments.c_str()};
            ceshi(1, argv);
        }
        else
            cout << arguments << endl;
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
    //string test = "hel asdj qweiq";
    //vector<string> args = boost::program_options::split_winmain(test);
    if(argc == 1)
    {
        ceshiMode();
        return 0;
    }
    ceshi(argc - 1, &argv[1]);
    return 0;
}