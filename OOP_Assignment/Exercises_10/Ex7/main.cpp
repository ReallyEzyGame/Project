#include "lib.h"

int main()
{
  FileSystem *fs = FileSystem::get_instance();
  Disk disk1("C");
  Disk disk2("D");

  Vector<unsigned char> text = std::initializer_list<unsigned char>({'C', 'o', 'd', 'i', 'n', 'g'});

  UniquePointer<Object> obj1(new Folder("My Folder"));
  UniquePointer<Object> obj2(new BinaryFile("binary file"));
  UniquePointer<Object> obj3(new TextFile("Text File", text));
  UniquePointer<Object> obj4(new Shortcut(obj2.get()));
  UniquePointer<Object> obj5(new Folder("Subfolder"));
  UniquePointer<Object> obj6(new BinaryFile("File subfolder"));

  fs->add_disk(disk1);
  fs->add_disk(disk2);

  std::cout << "Space before: " << fs->size() << std::endl;

  Disk& disk3 = fs->find_disk("D");
  Disk& disk4 = fs->find_disk("C");
  Folder* folder = dynamic_cast<Folder*>(obj1.get());
  Folder* folder2 = dynamic_cast<Folder*>(obj5.get());

  disk3.add(std::move(obj1));
  disk3.add(std::move(obj2));
  disk3.add(std::move(obj3), folder);
  disk3.add(std::move(obj5), folder);
  disk3.add(std::move(obj6), folder2);
  disk4.add(std::move(obj4));

  std::cout << "Size of the Disk C: " << fs->find_disk("C").size() << std::endl;
  std::cout << "Size of the Disk D: " << fs->find_disk("D").size() << std::endl;
  std::cout << "After Adding: " << fs->size() << std::endl;

  std::cout << "Remeaning Space of D disk: " << fs->find_disk("D").getFreeSpace() << std::endl;

  std::cout << "D disk heirachy\n";
  disk3.heirachy();

  fs->destroy();
  
  return 0;
}