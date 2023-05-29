#include <iostream>
#include <fstream>
#include <string>

class FileManeger {
private:

    struct FileManegerRc{
        int ref_count;
        std::fstream file;
        FileManegerRc(const std::string name);
        ~FileManegerRc();
    };
    FileManegerRc *value;
    std::string name;

public:
    FileManeger(); 
    FileManeger(std::string name); 
    FileManeger &operator = (const FileManeger& rhs);
    FileManeger(FileManeger &cpy); 
    ~FileManeger(); 
    char operator[] (std::fstream::pos_type i); 
    const std::string &getName() const;
    void setName(const std::string &name);
    const std::fstream &getFile() const;
    void setFile(const std::fstream &file);
    int getLength();
    bool open_new();
    operator char();
    FileManeger& operator[](int i);
    void operator=(char c);
    friend std::ostream& operator<<(std::ostream& os, const FileManeger& file);
    FileManegerRc *getValue() const;
    void setValue(FileManegerRc *value);

    //  Exceptions:
    class FileNotOpenedException{};
    class EOFReachedException{};

};

