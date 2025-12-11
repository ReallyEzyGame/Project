#include "lib.h"

class Disk;

Object::Object(const String str) : _name(str), _current_size(0) {}
Object::Object(const Object &other) : _name(other._name), _current_size(other._current_size) {}
Object::~Object() {};

String Object::name() const
{
    return _name;
}
unsigned long long Object::size() const
{
    return _current_size;
}
void Object::infor() const
{
    std::cout << "[" << _name << "]" << " <" << _current_size << ">";
}

Folder::Folder() : Object("New Folder") { _current_size = 0; }
Folder::Folder(const String name) : Object(name) { _current_size = 0; }
Folder::Folder(const String name, Vector<UniquePointer<Object>> objects) : Object(name), _objects(std::move(objects))
{
    _current_size = 0;
    for (int i = 0; i < _objects.size(); ++i)
    {
        _current_size += _objects[i]->size();
    }
}
Folder::Folder(const Folder &other) : Object(other)
{
    int size = other._objects.size();

    for (int i = 0; i < size; ++i)
    {
        UniquePointer<Object> copy = other._objects[i]->clone();
        _objects.push_back(std::move(copy));
    }
}
Folder::~Folder() {}

void Folder::insert(UniquePointer<Object> obj)
{
    _objects.push_back(std::move(obj));
}
void Folder::remove(const int idx)
{
    int size = _objects.size();

    _current_size -= _objects[idx]->size();
    _objects[idx] = std::move(_objects[size - 1]);
    _objects.pop_back();
}

UniquePointer<Object> &Folder::operator[](const int idx)
{
    return _objects[idx];
}
const UniquePointer<Object> &Folder::operator[](const int idx) const
{
    return _objects[idx];
}
UniquePointer<Object> Folder::clone() const
{
    Vector<UniquePointer<Object>> objects;
    int size = _objects.size();

    for (int i = 0; i < size; ++i)
    {
        UniquePointer<Object> obj = _objects[i]->clone();
        objects.push_back(std::move(obj));
    }

    Folder *folder = new Folder(this->name(), std::move(objects));
    return UniquePointer<Object>(folder);
}
void Folder::infor() const
{
    Object::infor();
    std::cout << " 'folder'";
}
void Folder::heirachy(const int depth) const
{
    for (int i = 0; i < _objects.size(); ++i)
    {
        for (int j = 1; j <= depth; ++j)
        {
            std::cout << "   ";
        }
        _objects[i]->infor();

        if (_objects[i]->type() == "folder")
        {
            std::cout << std::endl;
            dynamic_cast<Folder*>(_objects[i].get())->heirachy(depth + 1);
        }
        
        if (i < _objects.size() - 1) {
            std::cout << std::endl;
        }
    }
}

File::File() : Object("New File") { _current_size = 0; }
File::File(const String name) : Object(name) { _current_size = 0; }
File::File(const String name, Vector<unsigned char> data) : Object(name), _data(data)
{
    _current_size = _data.size();
};
File::File(const File &other) : Object(other), _data(other._data) {}
File::~File() {}

Vector<unsigned char> File::data() const
{
    return _data;
}
unsigned char &File::operator[](const int idx)
{
    return _data[idx];
}
unsigned char File::operator[](const int idx) const
{
    return _data[idx];
}
File &File::operator=(const File &file)
{
    _data = file._data;
    _current_size = _data.size();
    return *this;
}

BinaryFile::BinaryFile() : File("New Binary Folder") {}
BinaryFile::BinaryFile(const String name) : File(name) {}
BinaryFile::BinaryFile(const String name, const Vector<unsigned char> data) : File(name, data) {};
BinaryFile::BinaryFile(const BinaryFile &other) : File(other) {};
BinaryFile::~BinaryFile() {}

UniquePointer<Object> BinaryFile::clone() const
{
    Object *file = new BinaryFile(_name, _data);
    return UniquePointer<Object>(file);
}

std::ostream &operator<<(std::ostream &os, const BinaryFile &file)
{
    for (unsigned char ch : file._data)
    {
        os << std::bitset<8>(ch);
    }
    return os;
}
void BinaryFile::infor() const
{
    Object::infor();
    std::cout << " 'binary file'";
}
TextFile::TextFile() : File("New Text File") {}
TextFile::TextFile(const String name) : File(name) {}
TextFile::TextFile(const String name, const Vector<unsigned char> data) : File(name, data) {}
TextFile::TextFile(const TextFile &other) : File(other) {}
TextFile::~TextFile() {}

UniquePointer<Object> TextFile::clone() const
{
    Object *file = new TextFile(_name, _data);
    return UniquePointer<Object>(file);
}
void TextFile::infor() const
{
    Object::infor();
    std::cout << " 'text file'";
}
std::ostream &operator<<(std::ostream &os, const TextFile &file)
{
    for (unsigned char ch : file._data)
    {
        os << ch;
    }
    return os;
}

Shortcut::Shortcut(Object &obj) : Object("New Shortcut"), _ptr(&obj)
{
    _current_size = _KILOBYTE_;
}
Shortcut::Shortcut(const String name, Object &obj) : Object(name), _ptr(&obj)
{
    _current_size = _KILOBYTE_;
};
Shortcut::Shortcut(Object *obj) : Object("New Shortcut"), _ptr(obj) { _current_size = _KILOBYTE_; }
Shortcut::Shortcut(const String name, Object *obj) : Object(name), _ptr(obj) { _current_size = _KILOBYTE_; }
Shortcut::Shortcut(const Shortcut &other) : Object(other), _ptr(other._ptr) { _current_size = _KILOBYTE_; }
Shortcut::~Shortcut() {}

Object *Shortcut::access() const
{
    return _ptr;
}

UniquePointer<Object> Shortcut::clone() const
{
    Object *shortcut = new Shortcut(_name, _ptr);
    return UniquePointer<Object>(shortcut);
}
void Shortcut::infor() const
{
    Object::infor();
    std::cout << " 'shortcut'";
}
Disk::Disk() : _name("New Disk"), _capacity(_MEGABYTE_), _current_size(0) {}
Disk::Disk(const String name) : _name(name), _capacity(_MEGABYTE_), _current_size(0) {}
Disk::Disk(const String name, Vector<UniquePointer<Object>> &folders) : _name(name), _capacity(_MEGABYTE_)
{
    unsigned long long total = 0;
    for (int i = 0; i < folders.size(); ++i)
    {
        total += folders[i]->size();
    }

    if (total <= _capacity)
    {
        _folders = std::move(folders);
        _current_size = total;
    }
    else
    {
        _current_size = 0;
    }
};
Disk::Disk(const Disk &other) : _name(other._name), _capacity(other._capacity), _current_size(other._current_size)
{
    int n = other._folders.size();
    for (int i = 0; i < n; ++i)
    {
        UniquePointer<Object> copy = other._folders[i]->clone();
        _folders.push_back(std::move(copy));
    }
}
Disk::Disk(Disk &&other) : _name(std::move(other._name)), _folders(std::move(other._folders)),
                           _capacity(other._capacity), _current_size(other._current_size)
{
    other._current_size = 0;
    other._capacity = 0;
}
Disk::~Disk() {}

void Disk::add(UniquePointer<Object> obj, Folder *folder)
{
    if (obj->size() + _current_size <= _capacity)
    {
        _current_size += obj->size();
        if (folder == nullptr)
        {
            _folders.push_back(std::move(obj));
        }
        else
        {
            folder->insert(std::move(obj));
        }
    }
}
void Disk::remove(const int idx)
{
    int size = _folders.size();
    unsigned long long folder_size = _folders[idx]->size();

    _folders[idx] = std::move(_folders[size - 1]);
    _folders.pop_back();
    _current_size -= folder_size;
}

unsigned long long Disk::size() const
{
    return _current_size;
}
unsigned long long Disk::capacity() const
{
    return _capacity;
}
unsigned long long Disk::getFreeSpace() const
{
    return _capacity - _current_size;
}
String Disk::name() const
{
    return _name;
}

Disk &Disk::operator=(Disk &&other) noexcept
{
    if (this != &other)
    {
        _name = std::move(other._name);
        _folders = std::move(other._folders);
        _capacity = other._capacity;
        _current_size = other._current_size;

        other._capacity = 0;
        other._current_size = 0;
    }
    return *this;
}

Disk &Disk::operator=(const Disk &other)
{
    if (this != &other)
    {
        _name = other._name;
        _current_size = other._current_size;
        _capacity = other._capacity;

        int n = other._folders.size();

        _folders = Vector<UniquePointer<Object>>();

        for (int i = 0; i < n; ++i)
        {
            _folders.push_back(other._folders[i]->clone());
        }
    }

    return *this;
}
void Disk::heirachy() const
{
    for (int i = 0; i < _folders.size(); ++i)
    {
        std::cout << "   ";
        _folders[i]->infor();
        // folder heirachy
        if(_folders[i]->type() == "folder") {
            std::cout << std::endl;
            dynamic_cast<Folder*>(_folders[i].get())->heirachy(2);
        }

        if (i < _folders.size() - 1) {
            std::cout << std::endl;
        }
    }
}
FileSystem::FileSystem()
{
    _total_space = 16 * _MEGABYTE_;
    _used_space = 0;
}

FileSystem *FileSystem::get_instance()
{
    if (fs == nullptr)
    {
        fs = new FileSystem();
    }
    return fs;
}
void FileSystem::destroy()
{
    delete fs;
    fs = nullptr;
}

void FileSystem::add_disk(Disk &disk)
{
    if (disk.size() + _used_space <= _total_space)
    {
        disks.push_back(std::move(disk));
        _used_space += disks[disks.size() - 1].size();
    }
}

Disk &FileSystem::find_disk(const String name)
{
    for (int i = 0; i < disks.size(); ++i)
    {
        if (disks[i].name() == name)
        {
            return disks[i];
        }
    }
    throw std::runtime_error("Disk not found");
}

unsigned long long FileSystem::size() const
{
    unsigned long long sum = 0;
    for (int i = 0; i < disks.size(); ++i)
    {
        sum += disks[i].size();
    }
    return sum;
}

unsigned long long FileSystem::capacity() const
{
    return _total_space;
}

const Disk &FileSystem::operator[](const int idx) const
{
    return disks[idx];
}
Disk &FileSystem::operator[](const int idx)
{
    return disks[idx];
}
