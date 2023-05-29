#include <iostream>
#include "FileManeger.h"
#include <sstream>
#include <string>
#include <iterator>
#include <vector>


using namespace std;



class System {

private:

	
    vector<FileManeger*> Files;
    vector<System*> Folders;

    string name;
    int numOfFiles;
    int numOfFolders;
    System* location;


public:

    enum Commands{read,write,touch,copy,remove,move,cat,wc,ln,mkdir,chdir,rmdir,ls,lproot,pwd,exit}; 
    enum {FILE_NAME=100};
    System();
    System(string name);
    ~System();
    void start();

    Commands getCmd(string const& inString) const;

    //Files
    void Read(string fileName,int n);
    void Write(string fileName,int n, char c);
    void Touch(string fileName);
    void cpyFile(string source_file, string target_file);
    void removeFile(string fileName);
    void moveFile(string from, string to);
    void catFile(string fileName);
    void Wc(string file_name);
    void hardLink(string file,string link_Name);


    //Folders
    void makeFolder(string folder_name);
    void changeFolder(string target_folder);
    int fileExists(string file_name);
    int folderExists(string folder_name);
    void printCurrentLoc();
    void printFolder(string target_folder);
    void lpRoot();
    void removeFolder(string folder_to_delete);

    //exceptions:
    class WrongInputException{};
    class FileNotOpenedException{};
    class EOFReachedException{};
    class BadNumException{};
    class FileNotFoundException{};

};



