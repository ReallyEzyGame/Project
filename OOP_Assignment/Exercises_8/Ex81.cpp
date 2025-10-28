#include "Array.hpp"
#include "SmartPointer.hpp"


#define KILO_BYTE           1024

#define READ_AS_BINARY      0
#define READ_AS_OCTAN       8
#define READ_AS_DECIMAL     10
#define READ_AS_HEXAN       16
#define READ_AS_CHAR        128

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
class File;
class Shortcut;





class Object {
private:
    Array<SmartPtr<Object>> objects;
protected:
    Array<char> name;
public:
    Object();
    Object(Array<char>);
    Object(const Object&);
    ~Object() = default;


    virtual void open();
    // display information of the data
    // if the object is folder, it will display all of it child
    virtual void display();

    virtual size_t getSize();
    virtual Array<char> getName();
    virtual Object* clone();
};

Object::Object():  objects(), name() {}
Object::Object(Array<char> str): objects(), name(str) {}
Object::Object(const Object& other) : objects(other.objects), name(other.name) {}


void Object::open() {
    Array<char> str;

    printf("Input File/Folder name open: ");
    scanf("%s", str);

    for (SmartPtr<Object>& obj : objects) {
        // found the Object
        if (str == obj.getData().name)
        {
            obj.getData().open();
            return;
        }
    }

    printf("No Object has the name: %s was Found\n", str);
    return;
}


void Object::display() {
    for (SmartPtr<Object> obj : objects) {
        obj.getData().display();
        printf("\n");
    }
}
size_t Object::getSize() {
    size_t size = 0;

    for (SmartPtr<Object> obj : objects)
        size += obj.getData().getSize();

    return size;
}
Array<char> Object::getName() {
    return name;
}
Object* Object::clone() {
    return new Object(*this);
}





class File : public Object {
private:
    Array<char> data;
    int base;           // provides the file reading mode in binary, octan, decimal, hexan and ASCCI char 
public:
    File();
    File(const int);
    File(const Array<char>&);
    File(const File&);
    ~File();


    // Display the data of the array
    // base on the file  type, example: binary, dec-10, hex-16....
    void open() final;
    // Display the information of the file, including:  size, type....
    void display() final;

    size_t getSize() final;
    Array<char> getName() final;
    File* clone() final;
};

File::File() : Object(), data(), base(READ_AS_BINARY) {}
File::File(const int reading_mode) : Object(), data() {
    switch (reading_mode)
    {
    case READ_AS_BINARY:
    case READ_AS_OCTAN:
    case READ_AS_DECIMAL:
    case READ_AS_HEXAN:
    case READ_AS_CHAR:
        base = reading_mode;
    default:
        base = reading_mode;
        break;
    }
}
File::File(const Array<char>& file_name) : Object(file_name), data(), base(READ_AS_BINARY) {}
File::File(const File& other): Object(other), data(other.data), base(other.base) {}

// this function need to make the output has the formate of 8 char( any base) to a group
void File::open() {
    for (char& ch : data) {
        printf("%c ", ch);
    }
}

void File::display() {
    
}
size_t File::getSize() {
    return data.getSize();
}
Array<char> File::getName() {
    return name;
}
File* File::clone() {
    return new File(*this);
}





class Shortcut :  public Object {
private:
    SmartPtr<Object> ptr;
public:
    Shortcut() = delete;
    Shortcut(const Object*);
    Shortcut(const SmartPtr<Object>);
    Shortcut(const Shortcut&);
    ~Shortcut() = default;


    void open() final;

    

    size_t getSize() final;
    Shortcut* clone() final;
};

Shortcut::Shortcut(const Object* obj) : Object(), ptr(obj) {}
Shortcut::Shortcut(const SmartPtr<Object> obj) : Object(), ptr(obj) {}
Shortcut::Shortcut(const Shortcut& other) : Object(), ptr(other) {}


void Shortcut::open() {
    ptr.getData().open();
}


size_t Shortcut::getSize() {
    return KILO_BYTE;
}
Shortcut* Shortcut::clone() {
    return new Shortcut(*this);
}




class FileSystem {
private:
    Array<Array<char>> current_path;        // Current Path that user are in

    Array<SmartPtr<Object>> objects;

    FileSystem();
    FileSystem(const FileSystem&) = delete;
    FileSystem& operator=(FileSystem&) = delete;
    ~FileSystem() = default;
public:
    static FileSystem& getInstance();


    bool addDisk();
    // Display all the Disk(s) that are in the File System
    void display();
    int getDiskNumber() const;
    void open(const Array<char>);

    Array<Array<char>> getCurrentPath() const;
};

FileSystem::FileSystem(): objects() {}


FileSystem& FileSystem::getInstance() {
    static FileSystem instance;
    return instance;
}
void FileSystem::open(Array<char> disk_name) {

    for (SmartPtr<Object>& obj : objects) {
        if (disk_name == obj.getData().getName()) {
            obj.getData().open();
            return;
        }
    }

    printf("%s disk was not found\n", disk_name);
    return;
}



bool FileSystem::addDisk() {
    char name[256];
    Array<char> disk_name;

    printf("Input Disk Name: ");
    scanf("%s", name);

    disk_name = name;

    // Make Sure each disk has a specific name
    for (SmartPtr<Object>& obj : objects) {
        if (disk_name == obj.getData().getName()) {
            printf("Disk %s already exist\n", disk_name);
            return false;
        }
    }
    // Add a new Disk
    Object disk(disk_name);
    SmartPtr<Object> new_obj(disk_name);
    objects.push_back(new_obj);
    return true;
}
void FileSystem::display() {
    for (SmartPtr<Object>& obj : objects) {
        printf("Object pointer: %llu\n", &obj);

        Array <char> name = obj.getData().getName();
        for (int i =  0; i < name.getSize(); ++i)
            printf("%c", name[i]);

        printf("\n");
    }
}
int FileSystem::getDiskNumber() const {
    return objects.getSize();
}




int main() {
    FileSystem::getInstance().addDisk();
    FileSystem::getInstance().display();

    printf("number of Disk: %d\n", FileSystem::getInstance().getDiskNumber());
}