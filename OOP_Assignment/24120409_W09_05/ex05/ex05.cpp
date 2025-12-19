#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Object {
private:
    string _name;
public:
    Object(const string name) {
        _name = name;
    }

    string name() const {
        return _name;
    }


    virtual string type() const = 0;
    virtual int size() const = 0;
    virtual void output(ostream& os, const int depth = 0) const {
        for (int i = 0; i  < depth; ++i) {
            os << "   ";
        }
    }


    friend ostream& operator<< (ostream& os, const Object &obj) {
        obj.output(os);
        return os;
    } 
};



class Folder : public Object {
private:
    vector<Object*> sub_object;
public:
    Folder(const string name) : Object(name) {}
    
    int size() const final {
        int total = 0;
        
        for (int i = 0; i  < sub_object.size(); ++i) {
            total += sub_object[i]->size();
        }

        return total;
    }
    int number_of_object() const {
        int cnt = 0;
        
        for (int i = 0; i < sub_object.size(); ++i) {
            if (sub_object[i]->type() == "folder") {
                Folder* folder = dynamic_cast<Folder*>(sub_object[i]);
                cnt += folder->number_of_object();
            }
            cnt++;
        }

        return cnt;
    }
    string type() const final {
        return "folder";
    }
    void output(ostream& os, const int depth = 0) const final {
        Object::output(os, depth);
        os << "[" << name() << "]" << endl; 

        for (int i = 0; i < sub_object.size(); ++i) {
            if (sub_object[i]->type() == "folder") {
                dynamic_cast<Folder*>(sub_object[i])->output(os, depth + 1);
            }
            else {
                sub_object[i]->output(os, depth + 1);
                os << endl;
            }
        }
    }


    void add(Object* obj) {
        sub_object.push_back(obj);
    }

    int cnt_obj_in_folder(const string& name) {
        int cnt = 0;

        for (int i = 0; i < sub_object.size(); ++i) {

            if (sub_object[i]->name() == name) {
                Folder *folder = dynamic_cast<Folder*>(sub_object[i]);
                return folder->number_of_object();
            }
            if (sub_object[i]->type() == "folder") {
                Folder *folder = dynamic_cast<Folder*>(sub_object[i]);
                cnt += folder->cnt_obj_in_folder(name); 
            }
        }

        return cnt;
    }
    int size_of_folder(const string& name) {
        int cnt = 0;

        for (int i = 0; i < sub_object.size(); ++i) {

            if (sub_object[i]->name() == name) {
                Folder *folder = dynamic_cast<Folder*>(sub_object[i]);
                return folder->size();
            }
            if (sub_object[i]->type() == "folder") {
                Folder *folder = dynamic_cast<Folder*>(sub_object[i]);
                cnt += folder->size_of_folder(name); 
            }
        }

        return cnt;
    }
};
class File : public Object {
private:
    int _size;
public:
    File(const string name, const int size) : Object(name) {
        _size = std::abs(size);
    }

    int size() const final {
        return _size;
    }
    string type() const final {
        return "file";
    }
    void output(ostream& os, const int depth = 0) const final {
        Object::output(os, depth);
        os << name() << "(" << size() << " B)";
    }
};



int main() {
    File* f1 = new File("BT1.doc", 123456);
    File* f2 = new File("BT2.cpp", 1280);
    File* f3 = new File("BT2.xls", 23456);
    File* f4 = new File("Ch1.ppt", 34567);

    Folder* C = new Folder("C:");
    Folder* C_work = new Folder("Bai tap C");
    Folder* home_work = new Folder("Bai tap");
    Folder* theory = new Folder("Ly thuyet");


    C_work->add(f2);
    theory->add(f4);
    home_work->add(f1);
    home_work->add(f3);
    home_work->add(C_work);
    C->add(home_work);
    C->add(theory);

    cout << *C << endl;
    cout << "So vat trong thu muc 'Bai tap': " << C->cnt_obj_in_folder("Bai tap") << endl;
    cout << "Kich thuoc cua thu muc 'Bai tap C': " << C->size_of_folder("Bai tap C") << endl;

    system("pause");
    return 0;
}