#include <cstring>
#include "System.h"




System::System():numOfFiles(0),name("V/"),numOfFolders(0),location(this){}


System::System(string name):numOfFiles(0),name(name),numOfFolders(0),location(this){}


System::~System() {
    for (auto it = Files.begin(); it != Files.end(); it++){
      delete *it;
    }
        
    vector<System *>::iterator tmp_iter = Folders.begin();
    for (auto it = Folders.begin(); it != Folders.end(); it++)
        delete *it;
}

void System::start() {
    string input;
    string command;
    char fileOne[FILE_NAME];
	  char fileTwo[FILE_NAME];
	  char usable_char;
    unsigned int n;
    istringstream s_stream;

    // main loop  
    while (1)
    {
      std::cout << "enter a commend,type exit to quit:" << std::endl; 
        if (cin.fail())
            cin.clear();
;
        getline(cin, input);
        istringstream s_stream(input);
        s_stream >> command;
        try
        {
            getCmd(command);
        }
        catch (WrongInputException &e)
        {
            cout << "Error: command is not supported." << endl;
            continue;
        }

        switch (getCmd(command))
        {
            case read:
                if (s_stream.peek() == EOF || s_stream.peek() == '\n' )
                {
                    cout << "Error: USAGE read FILENAME POSITION." << endl;
                    cin.setstate(ios::failbit);
                    continue;
                }
                s_stream >> fileOne;
                if (s_stream.peek() == EOF || s_stream.peek() == '\n')
                {
                    cout << "Error: USAGE read FILENAME POSITION." << endl;
                    cin.setstate(ios::failbit);
                    continue;
                }
                s_stream >> n;
                if (s_stream.fail())
                {
                    cout << "Error: USAGE read FILENAME POSITION." << endl;
                    continue;
                }
                try
                {
                    Read(fileOne, n);
                }
                catch (EOFReachedException &e)
                {
                    cout << "Error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                catch (FileNotFoundException &e)
                {
                    cout << "Error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                catch (BadNumException &e)
                {
                    cout << "Wrong index provided." << endl;
                }
                break;

            case write:
                if (s_stream.peek() == EOF || s_stream.peek() == '\n')
                {
                    cout << "error: USAGE write FILENAME POSITION CHARACTER." << endl;
                    cin.setstate(ios::failbit);
                    continue;
                }
                s_stream >> fileOne;
                if (s_stream.peek() == EOF || s_stream.peek() == '\n')
                {
                    cout << "Error: USAGE write FILENAME POSITION CHARACTER." << endl;
                    cin.setstate(ios::failbit);
                    continue;
                }
                s_stream >> n >> usable_char;
                if (s_stream.fail())
                {
                    cout << "Error: USAGE write FILENAME POSITION CHARACTER." << endl;
                    continue;
                }
                try
                {
                    Write(fileOne, n, usable_char);
                }
                catch (EOFReachedException &e)
                {
                    cout << "Error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                catch (FileNotFoundException &e)
                {
                    cout << "Error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                catch (BadNumException &e)
                {
                    cout << "Wrong index provided." << endl;
                }
                break;

            case touch:
                if (s_stream.peek() == EOF || s_stream.peek() == '\n')
                {
                    cout << "error: USAGE touch FILENAME." << endl;
                    cin.setstate(ios::failbit);
                    continue;
                }
                s_stream >> fileOne;
                if (s_stream.fail())
                {
                    cout << "Error: USAGE touch FILENAME." << endl;
                    continue;
                }
                try
                {
                    Touch(fileOne);
                }
                catch (FileNotOpenedException &e)
                {
                    cout << "Error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                catch (bad_alloc &e)
                {
                    cout << "Error: " << fileOne << " Cannot be allocated." << endl;
                }
                break;

            case copy:
                if (s_stream.peek() == EOF || s_stream.peek() == '\n')
                {
                    cout << "Error: USAGE copy SOURCE_FILENAME TARGET_FILENAME." << endl;
                    cin.setstate(ios::failbit);
                    continue;
                }
                s_stream >> fileOne;
                if (s_stream.peek() == EOF || s_stream.peek() == '\n')
                {
                    cout << "Error: USAGE copy SOURCE_FILENAME TARGET_FILENAME." << endl;
                    cin.setstate(ios::failbit);
                    continue;
                }
                s_stream >> fileTwo;
                if (s_stream.fail())
                {
                    cout << "Error: USAGE copy SOURCE_FILENAME TARGET_FILENAME." << endl;
                    continue;
                }
                try
                {
                    cpyFile(fileOne, fileTwo);
                }
                catch (FileNotFoundException &e)
                {
                    cout << "Error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                catch (bad_alloc &e)
                {
                    cout << "error: " << fileTwo << " Cannot be allocated." << endl;
                }
                break;

            case remove:
                if (s_stream.peek() == EOF || s_stream.peek() == '\n' || s_stream.peek() == '\n')
                {
                    cout << "error: USAGE remove FILENAME." << endl;
                    cin.setstate(ios::failbit);
                    continue;
                }
                s_stream >> fileOne;
                if (s_stream.fail())
                {
                    cout << "error: USAGE remove FILENAME." << endl;
                    continue;
                }
                try
                {
                    removeFile(fileOne);
                }
                catch (FileNotFoundException &e)
                {
                    cout << "error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                break;

            case move:
                if (s_stream.peek() == EOF || s_stream.peek() == '\n')
                {
                    cout << "error: USAGE move SOURCE_FILENAME TARGET_FILENAME." << endl;
                    cin.setstate(ios::failbit);
                    continue;
                }
                s_stream >> fileOne;

                if (s_stream.peek() == EOF || s_stream.peek() == '\n')
                {
                    cout << "error: USAGE move SOURCE_FILENAME TARGET_FILENAME." << endl;
                    cin.setstate(ios::failbit);
                    continue;
                }
                s_stream >> fileTwo;
                if (s_stream.fail())
                {
                    cout << "error: USAGE move SOURCE_FILENAME TARGET_FILENAME." << endl;
                    continue;
                }
                try
                {
                    moveFile(fileOne, fileTwo);
                }
                catch (FileNotFoundException &e)
                {
                    cout << "error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                catch (bad_alloc &e)
                {
                    cout << "error: " << fileTwo << " Cannot be allocated." << endl;
                }
                break;

            case cat:
                if (s_stream.peek() == EOF || s_stream.peek() == '\n')
                {
                    cout << "error: USAGE cat FILENAME." << endl;
                    cin.setstate(ios::failbit);
                    continue;
                }
                s_stream >> fileOne;
                if (s_stream.fail())
                {
                    cout << "error: USAGE cat FILENAME." << endl;
                    continue;
                }
                try
                {
                    catFile(fileOne);
                }
                catch (FileNotFoundException &e)
                {
                    cout << "error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                break;

            case wc:
                if (s_stream.peek() == EOF || s_stream.peek() == '\n')
                {
                    cout << "error: USAGE wc FILENAME [n]." << endl;
                    cin.setstate(ios::failbit);
                    continue;
                }
                s_stream >> fileOne;
                s_stream >> n;
                if (s_stream.fail())
                {
                    try
                    {
                        Wc(fileOne);
                    }
                    catch (FileNotFoundException &)
                    {
                        cout << "error: " << fileOne << " does not exist or cannot be processed." << endl;
                    }
                    continue;
                }
                try
                {
                    Wc(fileOne);
                }
                catch (FileNotFoundException &)
                {
                    cout << "error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                catch (BadNumException &e)
                {
                    cout << "wrong index provided." << endl;
                }
                break;

            case ln:
                if (s_stream.peek() == EOF || s_stream.peek() == '\n')
                {
                    cout << "Error: USAGE ln SOURCE_FILENAME TARGET_FILENAME." << endl;
                    cin.setstate(ios::failbit);
                    continue;
                }
                s_stream >> fileOne;
                if (s_stream.peek() == EOF || s_stream.peek() == '\n')
                {
                    cout << "Error: USAGE ln SOURCE_FILENAME TARGET_FILENAME." << endl;
                    cin.setstate(ios::failbit);
                    continue;
                }
                s_stream >> fileTwo;

                if (s_stream.fail())
                {
                    cout << "Error: USAGE ln SOURCE_FILENAME TARGET_FILENAME." << endl;
                    continue;
                }
                try
                {
                    hardLink(fileOne, fileTwo);
                }
                catch (FileNotFoundException &e)
                {
                    cout << "error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                catch (bad_alloc &e)
                {
                    cout << "error: " << fileTwo << " Cannot be allocated." << endl;
                }
                break;
            case mkdir:
                if (s_stream.peek() == EOF || s_stream.peek() == '\n')
                {
                    cout << "error: USAGE mkdir FILENAME." << endl;
                    cin.setstate(ios::failbit);
                    continue;
                }
                s_stream >> fileOne;
                if (s_stream.fail())
                {
                    cout << "error: USAGE mkdir FILENAME." << endl;
                    continue;
                }
                try
                {
                    makeFolder(fileOne);
                }
                catch (FileNotOpenedException &e)
                {
                    cout << "Error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                catch (FileNotFoundException &e)
                {
                    cout << "Error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                catch (bad_alloc &e)
                {
                    cout << "Error: " << fileOne << " Cannot be allocated." << endl;
                }
                break;

            case chdir:
                if (s_stream.peek() == EOF || s_stream.peek() == '\n')
                {
                    cout << "Error: USAGE chdir FILENAME." << endl;
                    cin.setstate(ios::failbit);
                    continue;
                }
                s_stream >> fileOne;
                if (s_stream.fail())
                {
                    cout << "eEror: USAGE chdir FILENAME." << endl;
                    continue;
                }
                try
                {
                    changeFolder(fileOne);
                }
                catch (FileNotOpenedException &e)
                {
                    cout << "Error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                catch (FileNotFoundException &e)
                {
                    cout << "Error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                catch (bad_alloc &e)
                {
                    cout << "Error: " << fileOne << " cannot be allocated." << endl;
                }
                break;

            case rmdir:
                if (s_stream.peek() == EOF || s_stream.peek() == '\n')
                {
                    cout << "Error: USAGE chdir FILENAME." << endl;
                    cin.setstate(ios::failbit);
                    continue;
                }
                s_stream >> fileOne;
                if (s_stream.fail())
                {
                    cout << "Error: USAGE chdir FILENAME." << endl;
                    continue;
                }
                try
                {
                    removeFolder(fileOne);
                }
                catch (FileNotOpenedException &e)
                {
                    cout << "Error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                catch (FileNotFoundException &e)
                {
                    cout << "Error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                catch (bad_alloc &e)
                {
                    cout << "Error: " << fileOne << " Cannot be allocated." << endl;
                }
                break;

            case ls:
                if (s_stream.peek() == EOF || s_stream.peek() == '\n')
                {
                    cout << "error: USAGE ls FILENAME." << endl;
                    cin.setstate(ios::failbit);
                    continue;
                }
                s_stream >> fileOne;
                if (s_stream.fail())
                {
                    cout << "error: USAGE ls FILENAME." << endl;
                    continue;
                }
                try
                {
                    printFolder(fileOne);
                }
                catch (FileNotOpenedException &e)
                {
                    cout << "error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                catch (FileNotFoundException &e)
                {
                    cout << "error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                catch (bad_alloc &e)
                {
                    cout << "error: " << fileOne << " Cannot be allocated." << endl;
                }
                break;

            case pwd:
                try
                {
                    printCurrentLoc();
                }
                catch (FileNotFoundException &e)
                {
                    cout << "error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                catch (bad_alloc &e)
                {
                    cout << "error: " << fileOne << " Cannot be allocated." << endl;
                }
                break;

            case lproot:
                try
                {
                    lpRoot();
                }
                catch (FileNotFoundException &e)
                {
                    cout << "error: " << fileOne << " does not exist or cannot be processed." << endl;
                }
                catch (bad_alloc &e)
                {
                    cout << "error: " << fileOne << " Cannot be allocated." << endl;
                }
                break;

            case exit:
                return;
        }
    }
}



System::Commands System::getCmd(string const &inString) const {

    if(inString == "read")
        return read;
    else if (inString == "write")
        return write;
    else if (inString == "touch")
        return touch;
    else if (inString == "copy")
        return copy;
    else if (inString == "remove")
        return remove;
    else if (inString == "move")
        return move;
    else if (inString == "cat")
        return cat;
    else if (inString == "wc")
        return wc;
    else if (inString == "ln")
        return ln;

    else if (inString == "mkdir")
        return mkdir;
    else if (inString == "chdir")
        return chdir;
    else if (inString == "rmdir")
        return rmdir;
    else if (inString == "ls")
        return ls;
    else if (inString == "lproot")
        return lproot;
    else if (inString == "pwd")
        return pwd;
    else if (inString == "exit")
        return exit;

    throw WrongInputException();
}

void System::Read(string fileName, int n) {
    int i;
    if (n < 0) throw BadNumException();
    if ((i = fileExists(fileName)) == -1) throw FileNotFoundException();

    FileManeger read(*Files[i]);
    if (read.getLength()==0 && n==0) return;
    if (read.getLength() <= n) throw EOFReachedException();
    cout << char(read[n]) << endl;
}

void System::Write(string fileName, int n, char c) {
    int i;
    if (n < 0) throw BadNumException();
    if ((i = fileExists(fileName)) == -1)
    	throw FileNotFoundException();
    FileManeger write = *Files[i];
    if (write.getLength() < n)
    	throw EOFReachedException();
    write[n] = c;

}

void System::Touch(string fileName) {
    if (fileExists(fileName)!=-1)
        return;
    FileManeger *newFile = new FileManeger(fileName);
    newFile->open_new();
    (*location).Files.push_back(newFile);
    numOfFiles++;
}

void System::cpyFile(string source_file, string target_file) {
    int length;
    int index1;
    int index2;
    fstream destFile;
    fstream copyFile;

    if ((index1=fileExists(source_file))==-1){
        throw FileNotFoundException();
    }
    Touch(target_file);
    index2=fileExists(target_file);

    FileManeger read=*Files[index1];
    FileManeger write=*Files[index2];

    destFile.open(write.getName().c_str(), std::fstream::out);
    copyFile.open(read.getName().c_str(), std::fstream::in);

    copyFile.seekg(0, copyFile.end);
    length = copyFile.tellg();
    copyFile.seekg(0, copyFile.beg);

    if (length == 0)
        return;

    char *buffer = new char[length];
    copyFile.read(buffer, length);   // read file into the buffer.
    destFile.write(buffer, length );

    destFile.close();
    copyFile.close();

    delete[] buffer;
}

void System::removeFile(string fileName) {
    int i;
    if ((i=fileExists(fileName))==-1)
        throw FileNotFoundException();

    vector<FileManeger*>::iterator iter = Files.begin()+i;
    Files.erase(iter);
    numOfFiles--;

    std::remove(fileName.c_str());
}

void System::moveFile(string from, string to) {
    int length;
    int index;
    ofstream to_file ;
    ifstream from_file;

    if (fileExists(from)==-1)
        throw FileNotFoundException();
    if ((index=fileExists(to))==-1)// if a file doesn't exist create a new file
        Touch(to);

    to_file.open( to.c_str(), std::fstream::out);
    from_file.open(from.c_str(), std::fstream::in);

    from_file.seekg(0, from_file.end);
    length = from_file.tellg();
    from_file.seekg(0, from_file.beg);

    char *buffer = new char[length];
    from_file.read(buffer, length);
    to_file.write(buffer, length);

    to_file.close();
    from_file.close();

    delete[] buffer;
    std::remove(from.c_str());

    vector<FileManeger*>::iterator iter = Files.begin()+index;
    Files.erase(iter);
    numOfFiles--;
}

void System::catFile(string fileName) {
    int index;
    int i=0;
    if ((index = fileExists(fileName)) == -1)
    	throw FileNotFoundException();
    if (Files[index]->getLength()==0)
    	return;
    FileManeger read(*Files[index]);
    while (i<read.getLength()) {
        cout << char(read[i]);
        if (read.getLength() <= i) throw EOFReachedException();
        i++;
    }cout<<endl;
}


int System::fileExists(string file_name) {
	int i=0;
    vector<FileManeger*>::iterator iter = Files.begin();

    for (; iter != Files.end(); iter++,i++){
        if ((*iter)->getName()==file_name)
            return i;
    }
    return -1;
}

int System::folderExists(string folder_name) {
	int i=0;
    vector<System*>::iterator iter = Folders.begin();

    for (; iter != Folders.end(); iter++,i++){
        if ((*iter)->name ==folder_name)
            return i;
    }
    return -1;
}

void System::Wc(string file_name) {
    int index;
    int i;
    int chars=0;
    int words=0;
    int lines=0;

    fstream file;

    if ((index = fileExists(file_name)) == -1)
    	throw FileNotFoundException();
    FileManeger read(*Files[index]);

    read.getValue()->file.seekg(0,file.end);
    chars=read.getValue()->file.tellg();
    read.getValue()->file.seekg(0,file.beg);

    char *buffer = new char[chars];
    read.getValue()->file.read(buffer,chars);
    for (i = 0; i <chars ; ++i) {
        if(buffer[i]==' '||buffer[i]=='\n'){
            words++;
            if (buffer[i]=='\n' ){
                lines++;
            }
        }
    }
    cout<<"lines: "<<lines<<", "<<"Words: "<<words<<", "<<"Charcters: "<<chars<<"\n";

    delete[] buffer;
}

void System:: hardLink(string file,string link_name){
    int index1;
    int index2;

    // find the files:
    if ((index1 = fileExists(file)) == -1)
    	throw FileNotFoundException();

    if ((index2 = fileExists(link_name)) == -1)
    	throw FileNotFoundException();

    // make the connection
    *Files[index2] = *Files[index1];

}

void System::makeFolder(string folder_name) {

    if (folderExists(folder_name)!=-1)
    	throw FileNotOpenedException();
    System *new_folder = new System(folder_name);
    location->Folders.push_back(new_folder);
    numOfFolders++;
}

void System::changeFolder(string target_folder) {
    int i;
    if (target_folder=="V/")
    	location=this;
    else if ((i=folderExists(target_folder))!=-1)
        location = Folders[i];
    else
        throw FileNotFoundException();

}

void System::printCurrentLoc() {
    cout<<location->name<<endl;
}

void System::printFolder(string target_folder) {
    int i;
    if (target_folder=="V/"){
        cout << this->name << ":" << endl;
        vector<FileManeger *>::iterator iter = Files.begin();
        for (; iter != Files.end(); iter++)
            if((*iter)->getName().find(target_folder))
            		{cout<<(*iter)->getName()<<endl;}
        vector<System *>::iterator tmp_iter = Folders.begin();
        for (; tmp_iter != Folders.end(); tmp_iter++)
            if (strstr((*tmp_iter)->name.c_str(),target_folder.c_str())!=NULL)
                cout<<(*tmp_iter)->name<<endl;
    }
    else if ((i=folderExists(target_folder))==-1)
    	throw FileNotFoundException();
    else {
        System tmpFolder = *Folders[i];
        cout << location->name << ":" << endl;
        vector<FileManeger *>::iterator iter = tmpFolder.Files.begin();
        for (; iter != tmpFolder.Files.end(); iter++)
            cout << (*iter)->getName() << endl;
        vector<System *>::iterator tmp_iter = tmpFolder.Folders.begin();
        for (; tmp_iter != tmpFolder.Folders.end(); tmp_iter++)
            cout << (*tmp_iter)->name << endl;
    }
}

void System::lpRoot() {
    vector<FileManeger *>::iterator it = Files.begin();

    for (; it != Files.end(); it++){
        cout<<(*it)->getName()<<" "<<(*it)->getValue()->ref_count<<endl;
    }

    vector<System *>::iterator tmp_iter = Folders.begin();
    for (; tmp_iter != Folders.end(); tmp_iter++){
        cout<<(*tmp_iter)->name<<endl;
        location=(*tmp_iter);
        location->lpRoot();
    }
}

void System::removeFolder(string folder_to_delete) {
    int i;
    if ((i=folderExists(folder_to_delete))==-1) {
        throw FileNotOpenedException();
    }
    vector<System *>::iterator tmp_iter = Folders.begin()+i;
    Folders.erase(tmp_iter);
}
