#include "move_semantic.hpp"

#include <iostream>
#include <cstdint>

int exampleData{14};

class Object
{
public:
    Object() = default;

    Object(int* _ptr) : ptr(_ptr) {
        ++ref_cnt;
    };   //Constructor with pointer assignment
    Object(int* _ptr, int _data) : ptr(_ptr), data(_data) {
        ++ref_cnt;
    };

    virtual ~Object() {
        --ref_cnt;
    }   //Decrement reference counter on each object destruction

    Object(Object& _obj) {
        data = _obj.getData();
        ptr = _obj.ptr;
        ref_cnt++;
    } //Copy constructor - shallow copy by default

    Object& operator=(Object& _obj) = default;  //And default copy assignemnt operator - shallow copy by default 


    Object(Object&& _obj) = default;              //Default move constructro and move assignemnt operator - shallow copies
    Object& operator=(Object&&) = default;


    int getRefCnt() const
    {
        return ref_cnt;
    }

    int getData() const
    {
        return data;
    }

    int getPointee() const
    {
        return *ptr;
    }
    int* ptr;
    int data{0};  
private:
    static uint32_t ref_cnt; //Reference counter  
};

class NonMovableObject : public Object
{
public:
    NonMovableObject() = default;
    NonMovableObject(int* _ptr, int _data) : Object(_ptr, _data) {}
    virtual ~NonMovableObject() {}

    NonMovableObject(Object&& _obj) = delete;             //Remove move constructor and move assignemnt operator - to be sore move semantic cannot be used by Object
    NonMovableObject& operator=(Object&&) = delete;
};


uint32_t Object::ref_cnt = 0;

void move_main()
{
    std::cout << "-------- Move semantic -------- \n";

    Object oA(&exampleData, 125);    //Create class instance with pointer and data
    std::cout << "Movable object oA created, data: " << oA.getData() << ", pointed: " << oA.getPointee() << ", refCnt: " << oA.getRefCnt() << "\n";

    Object oB = oA;                 //Create class instance by copy
    std::cout << "Movable object oB created by copy assignemnt of oA, data: " << oA.getData() << ", pointed: " << oA.getPointee() << ", refCnt: " << oA.getRefCnt() << "\n";

    Object oC(oA);                 //Create class instance by copy
    std::cout << "Movable object oC created by copy constructor of oA, data: " << oA.getData() << ", pointed: " << oA.getPointee() << ", refCnt: " << oA.getRefCnt() << "\n\n";

    Object oMA(&exampleData, 251);    //Create class instance with pointer and data
    std::cout << "Movable base object oMA created, data: " << oMA.getData() << ", pointed: " << oMA.getPointee() << ", refCnt: " << oMA.getRefCnt() << "\n";
    
    Object oMB = std::move(oMA);                 //Create class instance by copy
    std::cout << "Movable object oMB created by move assignemnt on oA, data: " << oMB.getData() << ", pointed: " << oMB.getPointee() << ", refCnt: " << oMB.getRefCnt() << "\n";

    Object oMC(std::move(oMB));                 //Create class instance by copy
    std::cout << "Movable object oMC created by move constructor on oB, data: " << oMC.getData() << ", pointed: " << oMC.getPointee() << ", refCnt: " << oMC.getRefCnt() << "\n\n";

    NonMovableObject oNMA(&exampleData, 31);
    std::cout << "Non Movable object oNMA created, data: " << oNMA.getData() << ", pointed: " << oNMA.getPointee() << ", refCnt: " << oNMA.getRefCnt() << "\n";

    NonMovableObject oNMB = oNMA;                 //Create class instance by copy
    std::cout << "Non Movable object oNMB created by copy assignemnt of oNMA, move not possible, data: " << oNMB.getData() << ", pointed: " << oNMB.getPointee() << ", refCnt: " << oNMB.getRefCnt() << "\n";

    NonMovableObject oNMC(oNMA);                 //Create class instance by copy
    std::cout << "Non  Movable object oNMC created by copy constructor of oNMA, move not possible, data: " << oNMC.getData() << ", pointed: " << oNMC.getPointee() << ", refCnt: " << oNMC.getRefCnt() << "\n\n";
}