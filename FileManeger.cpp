#include "FileManeger.h"

FileManeger::FileManeger() {}


FileManeger::FileManeger(std::string name):name(name),value(new FileManegerRc(name)){}


FileManeger::FileManeger(FileManeger &cpy):value(cpy.value) {
    this->name=cpy.name;
    ++value->ref_count;

}


FileManeger::~FileManeger() {
    if (--value->ref_count==0){
        std::remove(name.c_str());
        delete value;
    }
}

FileManeger::FileManegerRc::FileManegerRc(const std::string name):ref_count(1),file(name.c_str()){}

FileManeger::FileManegerRc::~FileManegerRc()
{
    if(file.is_open())
        file.close();
}

char FileManeger::operator[] (std::fstream::pos_type i)  {
    value->file.open(this->name.c_str());
    value->file.seekg(i);
    return char(value->file.get());
}



bool FileManeger::open_new() {
    value->file.open(name.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
    if (!value->file.is_open()){
        throw FileNotOpenedException();
    }
    return true;

}

FileManeger::operator char() {
    char c;
    value->file>>c;
    return c;
}

FileManeger &FileManeger::operator[](int i) {
    value->file.seekg(i);
    return *this;
}

void FileManeger::operator=(char c) {
    int pos;
    std::fstream stream;
    pos =value->file.tellg();
    stream.open(name.c_str());
    stream.seekg(pos);
    stream<<(c);
    stream.close();
}

const std::string &FileManeger::getName() const {
    return name;
}

void FileManeger::setName(const std::string &name) {
    FileManeger::name = name;
}

const std::fstream &FileManeger::getFile() const {
    return value->file;
}


std::ostream& operator<<(std::ostream& out, const FileManeger& file)
{
    char c;
    std::fstream stream;
    stream.open(file.getName().c_str());
    while ((c = stream.get()) != EOF)
        out << c;
    stream.close();
    return out;
}

int FileManeger::getLength() {
    int length;
    this->value->file.seekg(0,value->file.end);
    length = value->file.tellg();
    value->file.seekg(0,value->file.beg);
    return length;

}

FileManeger &FileManeger::operator=(const FileManeger &rhs) {
    if (value==rhs.value){
        return *this;
    }
    if (--(value->ref_count)==0){
        delete value;
    }
    value=rhs.value;
    ++(value->ref_count);
    return *this;
}

FileManeger::FileManegerRc *FileManeger::getValue() const {
    return value;
}

void FileManeger::setValue(FileManeger::FileManegerRc *value) {
    FileManeger::value = value;
}

