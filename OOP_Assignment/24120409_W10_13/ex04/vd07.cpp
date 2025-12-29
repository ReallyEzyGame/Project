#include <iostream>
#include <string>
#include <vector>
#include <exception>
using namespace std;

class CFile;
class CFolder;

class CItem
{
protected:
    string _name;
    bool _read_only;
    bool _hidden;

public:
    CItem(string name)
    {
        _name = name;
        _read_only = false;
        _hidden = false;
    }

    virtual ~CItem() = default;

    virtual void SetHidden(const bool is_hidden, const bool apply_to_children) = 0;
    virtual void Print(const bool print_hidden, const int indent = 0) = 0;
    virtual unsigned long long Size() = 0;
    string Name()
    {
        return _name;
    }
    virtual string Type() = 0;
};

class CFile : public CItem
{
private:
    unsigned long long _size;

public:
    CFile(const string name, const unsigned long long size) : CItem(name)
    {
        _size = size;
    }
    CFile() = default;

    void Print(const bool print_hidden, const int indent = 0) final
    {
        for (int i = 0; i < indent; ++i)
        {
            cout << "   ";
        }

        if (_hidden == false || print_hidden == true)
        {
            cout << "File: " << _name << " <" << _size << ">";
            cout << ", read_only: " << _read_only;
            cout << ", is_hidden" << _hidden;
        }
        else
        {
            cout << "hidden file";
        }
    }
    unsigned long long Size() final
    {
        return _size;
    }
    string Type() final
    {
        return "File";
    }
    void SetHidden(const bool is_hiddent, const bool is_apply_to_children) final
    {
        _hidden = is_hiddent;
    }
};
class CFolder : public CItem
{
private:
    vector<CItem*> _contents;

public:
    CFolder(const string name) : CItem(name) {}
    ~CFolder() = default;

    void Add(CItem*&& item)
    {
        if (item == nullptr)
        {
            throw exception("Access to nullptr");
        }

        _contents.push_back(std::move(item));
    }
    CItem* FindByName(const string name)
    {
        for (int i = 0; i < _contents.size(); ++i)
        {
            if (_contents[i]->Name() == name)
            {
                return _contents[i];
            }
            if (_contents[i]->Type() == "Folder")
            {
                CItem* item = dynamic_cast<CFolder*>(_contents[i])->FindByName(name);

                if (item != nullptr)
                {
                    return item;
                }
            }
        }
        return nullptr;
    }
    CItem* RemoveByName(const string name)
    {
        for (int i = 0; i < _contents.size(); ++i)
        {
            if (_contents[i]->Name() == name)
            {
                CItem* item = _contents[i];

                std::swap(_contents[i], _contents.back());
                _contents.pop_back();

                return item;
            }
        }
        return nullptr;
    }
    unsigned long long Size() final
    {
        unsigned long long total = 0;
        for (int i = 0; i < _contents.size(); ++i)
        {
            total += _contents[i]->Size();
        }
        return total;
    }
    void Print(const bool print_hidden, const int indent = 0) final
    {
        for (int i = 0; i < indent; ++i)
        {
            cout << "   ";
        }

        if (_hidden == false || print_hidden == true)
        {
            cout << "Folder: " << _name << " <" << Size() << ">, is_hidden: " << _hidden << ", read_only: " << _read_only << endl;

            for (int i = 0; i < _contents.size() - 1; ++i)
            {
                _contents[i]->Print(print_hidden, indent + 1);
                cout << endl;
            }
            _contents.back()->Print(print_hidden, indent + 1);
        }
        else
        {
            cout << "hidden folder";
        }
    }
    void SetHidden(const bool hidden, const bool apply_to_children) final
    {
        _hidden = hidden;
        if (apply_to_children)
        {
            for (int i = 0; i < _contents.size(); ++i)
            {
                _contents[i]->SetHidden(hidden, apply_to_children);
            }
        }
    }
    string Type() final
    {
        return "Folder";
    }
};

int main()
{
    CFolder C("C");
    CFolder System("System");
    CFolder Windows("Windows");

    CFile a_txt("a.txt", 123);
    CFile b_doc("b.doc", 456);

    try
    {
        System.Add(&a_txt);
        Windows.Add(&b_doc);
        C.Add(&System);
        C.Add(&Windows);
    }
    catch (const exception& ex)
    {
        cout << "Error: " << ex.what() << endl;
    }
    cout << "Content of folder C ->" << endl;
    bool isPrintHiddenItems = false;
    C.Print(isPrintHiddenItems);
    cout << endl
        << endl;

    CItem* p = C.RemoveByName("System");
    cout << "Content of folder C after removing folder 'System' ->" << endl;
    C.Print(false);
    cout << endl
        << endl;

    p = C.FindByName("b.doc");
    if (p != NULL)
    {
        cout << "b.doc is found in folder C" << endl;
    }
    else
    {
        cout << "b.doc is not found" << endl;
    }

    p = C.FindByName("a.txt");
    if (p != NULL)
    {
        cout << "a.txt is found" << endl;
    }
    else
    {
        cout << "a.txt is not found" << endl;
    }

    p = C.FindByName("Windows");
    bool isHidden;
    bool isAlsoApplyToChildren;

    if (p != NULL)
    {
        cout << "Folder Windows is found. Content of folder Windows ->" << endl;
        isHidden = true;
        isAlsoApplyToChildren = true;

        p->SetHidden(isHidden, isAlsoApplyToChildren);
        p->Print(false);
        cout << endl
            << endl;
    }
    else
    {
        cout << "Folder Windows is not found" << endl;
    }
    return 0;
}