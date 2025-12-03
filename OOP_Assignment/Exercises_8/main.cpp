#include "String.h"
#include "SmartPointer.h"
#include <iostream>

#define KILO_BYTE 1024

#define READ_AS_BINARY 0
#define READ_AS_OCTAN 8
#define READ_AS_DECIMAL 10
#define READ_AS_HEXAN 16
#define READ_AS_CHAR 128

// The _size of the _object is Measured by Byte(B)
/*
Apply OOP and Design Patterns to implement a computer file system (FS). The (FS) on
a computer is organized into Disks. Each Disk can contain Folders, Files, and
Shortcuts. A Folder can contain Files, Shortcuts, and subfolders. The main attributes of
Disk, Folder, File, and Shortcut include a _name. Additionally:

• Disk has information about its _capacity.
• File has information about its _size and type (binary or text).
• Shortcut has information about the path to the source (the Folder or File that the
shortcut points to).

a. Implement the classes, including the FS, Disk, Folder, File, Shortcut, and any other
necessary classes or interfaces.
b. Implement the getFreeSpace() method to calculate the available space on a disk.
Assume that the _size of a Shortcut is 1KB. The _size of a Folder is the sum of the sizes
of all files, shortcuts, and subfolders it contains.

*/

/*
    15/10/2025, implement class: FileSystem, _object, File, Shortcut
                Since the class Folder share many things with _object so we decided to erease class Folder and implement it as _object instead
    2/12/2025, Continue the project
*/
// We Consider and Handle each drive as the same as Folder

class FileSystem;

class Object; // Can be Consider as a Folder
class File;
class Shortcut;

class Object
{
private:
    Array<SmartPointer<Object>> _objects;

protected:
    String _name;

public:
    Object() : _objects(), _name() {}
    Object(const String str) : _objects(), _name(str) {}
    Object(const Object &other) : _objects(other._objects), _name(other._name) {}
    ~Object() = default;

    virtual void open()
    {
        String str;

        std::cout << "Input Name: ";
        std::cin >> str;

        for (SmartPointer<Object> &obj : _objects)
        {
            // found the _object
            if (str == obj->name())
            {
                obj->display();
                return;
            }
        }

        printf("No _object has the _name: %s was Found\n", str);
    }
    String name() const
    {
        return _name;
    }
    // display information of the _ptr
    // if the _object is folder, it will display all of it child
    virtual void display()
    {
        for (SmartPointer<Object> &obj : _objects)
        {
            obj->display();
            std::cout << std::endl;
        }
    }
    virtual int size() const
    {
        size_t _size = 0;

        for (SmartPointer<Object> &obj : _objects)
            _size += obj->size();

        return _size;
    }
    virtual SmartPointer<Object> clone() const
    {
        return SmartPointer<Object>(new Object(*this));
    }
};

class File : public Object
{
private:
    Array<char> _data;
    int _base; // provides the file reading mode in binary, octan, decimal, hexan and ASCCI char
public:
    File() : Object(), _data(), _base(READ_AS_BINARY) {}
    File(const int reading_mode) : Object(), _data()
    {
        switch (reading_mode)
        {
        case READ_AS_BINARY:
        case READ_AS_OCTAN:
        case READ_AS_DECIMAL:
        case READ_AS_HEXAN:
        case READ_AS_CHAR:
            _base = reading_mode;
        default:
            _base = READ_AS_BINARY;
            break;
        }
    }
    File(const String &name) : Object(name), _data(), _base(READ_AS_BINARY) {}
    File(const File &other) : Object(other), _data(other._data), _base(other._base) {}
    ~File();

    // Display the _ptr of the array
    // base on the file  type, example: binary, dec-10, hex-16....
    void open() final
    {
    }
    // Display the information of the file, including:  _size, type....
    void display() final
    {
    }
    int size() const final
    {
        return _data.size();
    }
    SmartPointer<Object> clone() const final
    {
        return SmartPointer<Object>(new File(*this));
    }
};

class Shortcut : public Object
{
private:
    SmartPointer<Object> _ptr;

public:
    Shortcut() = delete;
    Shortcut(const Object *obj) : Object(), _ptr(obj) {}
    Shortcut(const SmartPointer<Object> &&obj) : Object(*obj)
    {
        _ptr = &obj;
    }
    Shortcut(const Shortcut &other) : Object(other)
    {
        _ptr = &other._ptr;
    }
    ~Shortcut() = default;

    void open() final
    {
        (*_ptr).open();
    }

    int size() const final
    {
        return KILO_BYTE;
    }
    SmartPointer<Object> clone() const final
    {
        return SmartPointer<Object>(new Shortcut(*this));
    }
};

class FileSystem
{
private:
    Array<String> _current_path; // Current Path that user are in

    Array<SmartPointer<Object>> objects;

    FileSystem() : objects() {}
    FileSystem(const FileSystem &) = delete;
    FileSystem &operator=(FileSystem &) = delete;
    ~FileSystem() = default;

public:
    static FileSystem &getInstance()
    {
        static FileSystem instance;
        return instance;
    }

    void addDisk()
    {
        String disk_name;
        std::cout << "Input Disk _name: ";

        // Make Sure each disk has a specific _name
        for (SmartPointer<Object> &obj : objects)
        {
            if (disk_name == obj->name())
            {
                std::cout << "Disk " << disk_name << " have already existed" << std::endl;
            }
        }
        // Add a new Disk
        SmartPointer<Object> new_disk(new Object(disk_name));
        objects.push_back(new_disk);
    }
    // Display all the Disk(s) that are in the File System
    void display()
    {
        for (SmartPointer<Object> &obj : objects)
        {
            String name = obj->name();
            std::cout << name << std::endl;
        }
    }
    int getDiskNumber() const
    {
        return objects.size();
    }
    void open(String disk_name)
    {

        for (SmartPointer<Object> &obj : objects)
        {
            if (disk_name == obj->name())
            {
                obj->open();
                return;
            }
        }

        std::cout << disk_name << " disk was not found" << std::endl;
    }
    Array<String> current_path() const {
        return _current_path;
    }
};

int main()
{
    Array<int> array;
    array.push_back(1);
    array.push_back(1);
    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    for (int i = 0; i < array.size(); ++i)
    {
        std::cout << array[i] << " ";
    }

    String str;
    std::cin >> str;
}