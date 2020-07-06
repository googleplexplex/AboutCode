#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

void outputFile(string path)
{
    string line;
    ifstream myfile(path);
    if (myfile.is_open())
    {
        while (!myfile.eof())
        {
            getline(myfile, line);
            cout << line << endl;
        }
        myfile.close();
    }
}

string copyFileInHeap(string path)
{
    string result;
    string line;
    ifstream myfile(path);

    if (myfile.is_open())
    {
        while (!myfile.eof())
        {
            getline(myfile, line);
            result += line;

            if (!myfile.eof())
                result += '\n';
        }
        myfile.close();
    }

    return result;
}

string getStructsNames(string searchIn)
{
    smatch m;
    regex structNamesRegex("struct[\n ]+([a-zA-Z][a-zA-Z0-9]*)");
    string result;

    while (regex_search(searchIn, m, structNamesRegex)) {
        result += m[1].str() + ' ';
        searchIn = m.suffix().str();
    }

    return result;
}
string getClassesNames(string searchIn)
{
    smatch m;
    regex structNamesRegex("class[\n ]+([a-zA-Z][a-zA-Z0-9]*)");
    string result;

    while (regex_search(searchIn, m, structNamesRegex)) {
        result += m[1].str() + ' ';
        searchIn = m.suffix().str();
    }

    return result;
}
string getNamespaces(string searchIn)
{
    smatch m;
    regex structNamesRegex("namespace[\n ]+([a-zA-Z][a-zA-Z0-9]*)[\n ]*\\{");
    string result;

    while (regex_search(searchIn, m, structNamesRegex)) {
        result += m[1].str() + ' ';
        searchIn = m.suffix().str();
    }

    return result;
}

string getStructContent(string searchIn, string structName)
{
    smatch m;
    string regexStr("struct " + structName + "[\s\S]*?(\\{\n?([\s\S]*?)\\})\;");
    regex structNamesRegex(regexStr);
    string result;

    while (regex_search(searchIn, m, structNamesRegex)) {
        result += m[1].str() + ' ';
        searchIn = m.suffix().str();
    }

    return result;
}
string getClassContent(string searchIn, string className)
{
    smatch m;
    regex structNamesRegex("class " + className + "[\s\S]*?\\{[ \n]*([\s\S]*?)\\};");
    string result;

    while (regex_search(searchIn, m, structNamesRegex)) {
        result += m[1].str() + ' ';
        searchIn = m.suffix().str();
    }

    return result;
}
string getNamespaceContent(string searchIn, string namespaceName)
{
    smatch m;
    regex structNamesRegex("namespace " + namespaceName + "[\s\S]*?\\{[ \n]*([\s\S]*?)\\};");
    string result;

    while (regex_search(searchIn, m, structNamesRegex)) {
        result += m[1].str() + ' ';
        searchIn = m.suffix().str();
    }

    return result;
}



struct A
{
    void a_method()
    {
        cout << "Thats A struct method!";
    }
};

class
    B
{

};

namespace C {}


int main(void)
{
    string fileContent = copyFileInHeap(__FILE__);
    cout << "Detected structeres: " << getStructsNames(fileContent) << endl;
    cout << "Detected classes: " << getClassesNames(fileContent) << endl;
    cout << "Detected namespaces: " << getNamespaces(fileContent) << endl;

    cout << "Content of A struct: " << getStructContent(fileContent, "A") << endl;
    cout << "Content of B class: " << getClassContent(fileContent, "B") << endl;
    cout << "Content of C namespace: " << getNamespaceContent(fileContent, "C") << endl;

    return 0;
}