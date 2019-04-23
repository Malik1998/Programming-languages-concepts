#include <bits/stdc++.h>

using namespace std;






#define VIRTUAL_CLASS(X) struct X { map<string, function<void()> > functionTable;


#define END_CLASS(X) };


#define VIRTUAL_CLASS_DERIVED(D, B) struct D { map<string, function<void()> > functionTable;


#define END_DERIVE(D, B) };


#define METHOD_DECLARATION(X) X() {

#define ENDED(X) }


#define DECLARE_METHOD(X, name, code) functionTable[#name] = [&] () {code};


#define METHOD_DECLARATION_D(D, B) D() { B b = B(); for ( auto it = b.functionTable.begin(); it != b.functionTable.end(); it++ ) { functionTable[it->first] = it->second; }




VIRTUAL_CLASS(Base)


METHOD_DECLARATION(Base)

    DECLARE_METHOD(Base, Both, {cout << "Both Base" << endl;} )


    DECLARE_METHOD(Base, OnlyBase, {cout << "OnlyBase" << endl;} )

ENDED(Base)

END_CLASS(Base)





VIRTUAL_CLASS_DERIVED( Derived, Base )

METHOD_DECLARATION_D(Derived, Base)


    DECLARE_METHOD( Derived, Both,  {cout << "Both Derived" << endl;} )


    DECLARE_METHOD( Derived, OnlyDerived,  {cout << "onlyDerived" << endl;} )

ENDED(Derived)

END_DERIVE( Derived, Base )




#define VIRTUAL_CALL(object, name) object->functionTable[#name]();



struct d{
    static map<string, void (*)()> functionTable;
};

void x() {}

int main() {

    Base *base = new Base();


    Derived derived = Derived();

    Base* reallyDerived = reinterpret_cast<Base*>(&derived);

    VIRTUAL_CALL(base, Both)
    VIRTUAL_CALL(reallyDerived, Both)
    VIRTUAL_CALL(reallyDerived, OnlyBase)
    VIRTUAL_CALL(reallyDerived, OnlyDerived)

}