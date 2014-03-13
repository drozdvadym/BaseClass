////////////////////////////////////////////////////////////////////////////////
// include section

#include <iostream>
#include <list>
#include <string>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// some additional macro Class

#define SAVE(Obj) Obj() {
#define REG_MEMBER(type, x) \
    RegisterMBS(new ValueHolderType<type>(&x, #x))
#define ENDSAVE }

////////////////////////////////////////////////////////////////////////////////
// ValueHolder Class

class ValueHolder {
public:
    virtual void loadVal() = 0;
    virtual void saveVal() = 0;
    virtual ~ValueHolder() {}
};

template <typename type>
class ValueHolderType : public ValueHolder {
public:
    ValueHolderType(type* val, const char valN[]) : value(val), valName(valN) {}

    void loadVal() {
        cout << "Please enter " << valName << ": ";
        cin >> *value;
    }

    void saveVal() {
        cout << "<" << valName << "> " << *value;
        cout << " </" << valName << ">" << endl;
        }

private:
    type *value;
    const char *valName;
};


////////////////////////////////////////////////////////////////////////////////
// Base Class

list<ValueHolder *> _G_members;

typedef  list<ValueHolder *>::iterator ListIter;

class BaseClass {
public:
    void Load(const char *fileName)
    {
        auto mmb = members;
        for (auto cnt = members_count; cnt > 0; cnt--, mmb++) {
            (*mmb)->loadVal(); //@todo: implement correct loadVal
        }
    }
    void Save(const char *fileName)
    {
        auto mmb = members;
        for (auto cnt = members_count; cnt > 0; cnt--, mmb++) {
            (*mmb)->saveVal(); //@todo: implement correct saveVal
        }
    }

    BaseClass() : members_count (0) {}

    void RegisterMBS(ValueHolder * mbs)
    {
        if (members_count)
            _G_members.push_back(mbs);
        else
            members = _G_members.insert(_G_members.end(), (mbs));

        members_count++;
    }

    virtual ~BaseClass()
    {
        auto mmb = members;
        for (auto cnt = members_count; cnt > 0; cnt--) {
            delete (*mmb);
            _G_members.erase(mmb++);
        }
    }
private:
    ListIter members;
    int members_count;
};

////////////////////////////////////////////////////////////////////////////////
// Point Class

class Point: public BaseClass{
public:
    int x;
    float y;
    double z;
    string name;

    SAVE(Point)
        REG_MEMBER(int,x);
        REG_MEMBER(float,y);
        REG_MEMBER(double,z);
        REG_MEMBER(string,name);
    ENDSAVE;
};

////////////////////////////////////////////////////////////////////////////////
// Point4D Class
class Point4D : public Point
{
public:
    int v;

    SAVE(Point4D)
        REG_MEMBER(int,v);
    ENDSAVE;
};

////////////////////////////////////////////////////////////////////////////////
// Main



class A {

protected:
    void fooA(){ cout << "LOL" << endl;}
public:
    typedef void (A:: *MMB_FCN)();
    MMB_FCN getFcnAdddr() {return &A::fooA; }
};
class B: public A {public: void fooB() {A::fooA();} };


int main()
{
    A a;

    A::MMB_FCN f = a.getFcnAdddr();
    (a.*f)();

    Point p;
    p.Load("point.xml");
    p.x = 10;
    p.Save("point2.xml");

    {
        Point p2;
    }

    Point4D p2;
    p2.Load("");
    p2.Save("");

    return 0;
}

//
//
//
