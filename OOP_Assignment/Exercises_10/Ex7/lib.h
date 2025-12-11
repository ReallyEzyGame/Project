#include "String.h"
#include "SmartPointer.h"
#include <bitset>
#include <utility>
#include <vector>

#define _KILOBYTE_ 1024
#define _MEGABYTE_ 1048576
#define _GIGABYTE_ 1073741824

class Object;
class File;
class BinaryFile;
class TextFile;
class Folder;


class Object
{
protected:
  String _name;
  unsigned long long _current_size;

public:
  Object(const String str);
  Object(const Object &other);
  virtual ~Object();

  String name() const;
  unsigned long long size() const;
  
  virtual UniquePointer<Object> clone() const = 0;
  virtual void infor() const;
  virtual String type() const = 0;
};



class Disk
{
private:
  unsigned long long _capacity;
  unsigned long long _current_size;
  Vector<UniquePointer<Object>> _folders;
  String _name;

public:
  Disk();
  Disk(const String name);
  Disk(const Disk &other);
  Disk(const String name, Vector<UniquePointer<Object>>& objs);
  Disk(Disk&& other);
  ~Disk();

  // Add to a folder of the disk, if nullptr directly add to the disk
  void add(UniquePointer<Object> obj, Folder* folder = nullptr);
  void remove(const int idx);


  unsigned long long size() const;
  unsigned long long capacity() const;
  unsigned long long getFreeSpace() const;
  String name() const;
  
  void heirachy() const;

  Disk& operator=(Disk&& other) noexcept;
  Disk& operator=(const Disk& other);
};



class Folder : public Object
{
  friend void Disk::add(UniquePointer<Object> obj, Folder* folder);
private:
  Vector<UniquePointer<Object>> _objects;

public:
  Folder();
  Folder(const String name);
  Folder(const String name, Vector<UniquePointer<Object>> objects);
  Folder(const Folder &other);
  ~Folder();

  void remove(const int idx);

  UniquePointer<Object> &operator[](const int idx);
  const UniquePointer<Object> &operator[](const int idx) const;
  UniquePointer<Object> clone() const final;
  void infor() const final;
  void heirachy(const int depth) const;
  String type() const final{
    return "folder";
  }
private:
  void insert(UniquePointer<Object> obj);
};



class File : public Object
{
protected:
  Vector<unsigned char> _data;

public:
  File();
  File(const String name);
  File(const String name, Vector<unsigned char> data);
  File(const File &other);
  ~File();


  Vector<unsigned char> data() const;
  unsigned char &operator[](const int idx);
  unsigned char operator[](const int idx) const;

  File &operator=(const File &file);
  virtual void infor() const override = 0;
  virtual String type() const override = 0;
  virtual UniquePointer<Object> clone() const override = 0;
};

class BinaryFile : public File
{
public:
  BinaryFile();
  BinaryFile(const String name);
  BinaryFile(const String name, const Vector<unsigned char> data);
  BinaryFile(const BinaryFile &other);
  ~BinaryFile();

  UniquePointer<Object> clone() const final;
  void infor() const final;
  String type() const final {
    return "binary file";
  }

  friend std::ostream &operator<<(std::ostream &os, const BinaryFile &file);
};

class TextFile : public File
{
public:
  TextFile();
  TextFile(const String name);
  TextFile(const String name, const Vector<unsigned char> data);
  TextFile(const TextFile &other);
  ~TextFile();

  UniquePointer<Object> clone() const final;
  void infor() const final;
  virtual String type() const final {
    return "text file";
  }
  friend std::ostream &operator<<(std::ostream &os, const TextFile &file);
};



class Shortcut : public Object
{
private:
  Object *_ptr;

public:
  Shortcut(Object &obj);
  Shortcut(const String name, Object &obj);
  Shortcut(Object *obj);
  Shortcut(const String name, Object *obj);
  Shortcut(const Shortcut &other);
  ~Shortcut();

  Object *access() const;
  
  UniquePointer<Object> clone() const final;
  void infor() const final;
  String type() const final {
    return "shortcut";
  }
};



class FileSystem
{
private:
  Vector<Disk> disks;
  unsigned long long _total_space;
  unsigned long long _used_space;

  static FileSystem *fs;

  FileSystem();
  FileSystem &operator=(const FileSystem &other) = delete;
  FileSystem(const FileSystem &other) = delete;

public:
  static FileSystem *get_instance();
  void destroy();
  
  void add_disk(Disk &disk);
  
  Disk& find_disk(const String name);
  
  unsigned long long size() const;
  unsigned long long capacity() const;

  const Disk &operator[](const int idx) const;
  Disk &operator[](const int idx);
};

inline FileSystem* FileSystem::fs = nullptr;

