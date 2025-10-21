#include "Array.hpp"
#include <SmartPointer.hpp>


#define KILO_BYTE  1024


// The size of the Object is Measured by Byte(B)
/*
Apply OOP and Design Patterns to implement a computer file system (FS). The (FS) on
a computer is organized into Disks. Each Disk can contain Folders, Files, and
Shortcuts. A Folder can contain Files, Shortcuts, and subfolders. The main attributes of
Disk, Folder, File, and Shortcut include a name. Additionally:

• Disk has information about its capacity.
• File has information about its size and type (binary or text).
• Shortcut has information about the path to the source (the Folder or File that the
shortcut points to).

a. Implement the classes, including the FS, Disk, Folder, File, Shortcut, and any other
necessary classes or interfaces.
b. Implement the getFreeSpace() method to calculate the available space on a disk.
Assume that the size of a Shortcut is 1KB. The size of a Folder is the sum of the sizes
of all files, shortcuts, and subfolders it contains.

*/

/*
    15/10/2025, implement class: FileSystem, Object, File, Shortcut
                Since the class Folder share many things with Object so we decided to erease class Folder and implement it as Object instead
*/
// We Consider and Handle each drive as the same as Folder


class FileSystem;


class Object;                   // Can be Consider as a Folder
template <class T> class File;
class Shortcut;

class FileSystem {
private:
    Array<SmartPtr<Object>> objects;

    FileSystem();
    FileSystem(const FileSystem&) = delete;
    FileSystem& operator=(FileSystem&) = delete;
    ~FileSystem() = default;
public:
    static FileSystem& getInstance();

};

FileSystem::FileSystem() {}

FileSystem& FileSystem::getInstance() {
    static FileSystem instance;
    return instance;
}





class Object {
private:
    Array<SmartPtr<Object>> objects;
protected:
    Array<char> name;
public:
    Object();
    Object(const Array<char>);
    Object(const Object&);
    ~Object();


    virtual void access();
    virtual size_t getSize();
    virtual Object* clone();
};

void Object::access() {

}
size_t Object::getSize() {
    size_t size = 0;

    for (SmartPtr<Object> obj : objects)
        size += obj.getData().getSize();

    return size;
}
Object* Object::clone() {
    return new Object(*this);
}



template <class T>
class File : public Object {
private:
    Array<T> data;
public:
    File();
    File(const Array<T>&);
    File(const File&);
    ~File();


    void access() final;
    size_t getSize() final;
    File* clone() final;
};

template<typename T>
void File<T>::access() {

}
template<typename T>
size_t File<T>::getSize() {
    return data.size();
}
template<typename T>
File<T>* File<T>::clone() {
    return new File(*this);
}




class Shortcut :  public Object {
private:
    SmartPtr<Object> ptr;
public:
    Shortcut();
    Shortcut(const Object*);
    Shortcut(const SmartPtr<Object>);
    Shortcut(const Shortcut&);
    ~Shortcut();


    void access() final;
    size_t getSize() final;
    Shortcut* clone() final;
};


void Shortcut::access() {

}
size_t Shortcut::getSize() {
    return KILO_BYTE;
}
Shortcut* Shortcut::clone() {
    return new Shortcut(*this);
}