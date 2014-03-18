////////////////////////////////////////////////////////////////////////////////
// include section

#include <iostream>
#include <list>
#include <string>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// some additional macro Class

#define SAVE void RegisterAllMBS(list<int *>& aList) {
#define SAVE2(Parent) SAVE Parent::RegisterAllMBS(aList);
#define REG_MEMBER(type, x) RegisterOneMBR(aList, &x)
#define ENDSAVE }

////////////////////////////////////////////////////////////////////////////////
// Base Class

class BaseClass {
public:
    void Load(const char *fileName) {
        init_members();

        for (auto &mbr : members)
            cin >> *mbr;
    }
    void Save(const char *fileName) {
        init_members();

        for (auto &mbr : members)
            cout << *mbr << endl;
        cout << endl;
    }

    BaseClass() : members(0), is_inited(false) {}
    BaseClass(const BaseClass & bc) : members(0), is_inited(false) {}

    BaseClass & operator=(BaseClass & that) {
        if (this == &that)
            return *this;
        
        is_inited = false;
        members.clear();
    }

    virtual void RegisterAllMBS(list<int *>& aList) = 0;

    void RegisterOneMBR(list<int *>& aList, int *mbr) {
        aList.push_back(mbr);
    }

    void RegisterOneMBR(list<int *>& aList, BaseClass *mbr) {
        mbr->RegisterAllMBS(aList);
    }
    
    virtual ~BaseClass();

private:
    list<int *> members;
    bool      is_inited;

    void init_members() {
        if (!is_inited)
            RegisterAllMBS(members);
        is_inited = true;
    }
};

////////////////////////////////////////////////////////////////////////////////
// Point Class

class Point : public BaseClass{
public:
    int x;
    int y;
    int z;

    SAVE
        REG_MEMBER(int, x);
        REG_MEMBER(int, y);
    ENDSAVE;
};

////////////////////////////////////////////////////////////////////////////////
// Point4D Class
class Point4D : public Point
{
public:
    int v;

    SAVE2(Point)
        REG_MEMBER(int, v);
    ENDSAVE;
};

////////////////////////////////////////////////////////////////////////////////
// Point4D Class v2
class Point4D_v2 : public BaseClass
{
public:
    Point p;
    int v;

    SAVE
        REG_MEMBER(Point, p);
        REG_MEMBER(int, v);
    ENDSAVE;
};
////////////////////////////////////////////////////////////////////////////////
// Main

int main()
{
    Point p;
    p.Load("");
    p.Save("");
    
    Point p2 = p;
    p2.x = 2;
    p2.y = 2;
    p2.Save("");

    Point p3;
    p3 = p;
    p3.x = 3;
    p3.Save("");

    Point4D p4;
    p4.Load("");
    p4.Save("");


    Point4D p4_copy = p4;
    p4_copy.x = 2222;
    p4_copy.Save("");

    Point4D_v2 p4_v2;
    p4_v2.Load("");
    p4_v2.Save("");

    return 0;
}

//
//
//
