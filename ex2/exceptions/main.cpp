#include <iostream>
#include <stdlib.h>     /* exit */
#include <setjmp.h>     /* jmp_buf, setjmp, longjmp */
#include <stack>
#include <utility>
#include <functional>

#define MATH_EXCEPTION 1
#define NULL_POINTER_EXCEPTION 2

jmp_buf env;
bool isInException = false;
std::stack<std::pair<void*, std::function<void(const void* x)>>> to_be_deleted;

struct DumpClassAdded {

    DumpClassAdded() {
        std::cout << "Class created!!!" << std::endl;
    }

    ~DumpClassAdded() {
        std::cout << "explicitly called destructor!" << std::endl;
    }

};

struct DumpClassNotAdded {

    DumpClassNotAdded() {
        std::cout << "Class created!!!" << std::endl;
    }

    ~DumpClassNotAdded() {
        std::cout << "auto called destructor! --- Must not be called" << std::endl;
    }

};



#define TRY(code) int val = setjmp(env); \
                  if (val == 0 ) { \
                    to_be_deleted.push(std::make_pair(nullptr, [](const void* x){})); \
                    code \
                    DELETE_FROM_STACK \
                    } \




#define CATCH(exc, code) else if (val == exc) { \
                        code \
                        }


#define THROW(exc)  \
                    DELETE_FROM_STACK \
                    isInException = false; \
                    longjmp(env, exc);


#define DELETE_FROM_STACK    if (isInException) { \
                            std::cout << "EXCEPTION OCCURED DURING DELETING FROM THE STACK!!!!" << std::endl; \
                            exit(1); \
                            } \
                        while(!to_be_deleted.empty()) { \
                            isInException = true; \
                            std::cout << "Perform deleting" << std::endl; \
                           if (to_be_deleted.top().first == nullptr) {      \
                                std::cout << "Last element" << std::endl; \
                               to_be_deleted.pop(); \
                               break; \
                            } \
                            else { \
                               auto elem = to_be_deleted.top(); \
                               std::cout << "Deleting " << elem.first << std::endl; \
                               to_be_deleted.pop(); \
                               elem.second(elem.first); \
                            } \
                          }

#define SAFE_DELETE(var, NAME) to_be_deleted.push(std::make_pair(&var, [](const void* x) { static_cast<const NAME*>(x)->~NAME(); }));


struct DumpClassAddedWithExcep {

    DumpClassAddedWithExcep() {
        std::cout << "Class created!!!" << std::endl;
    }

    ~DumpClassAddedWithExcep() {

        std::cout << "explicitly called destructor with exception program will stop soon!" << std::endl;

        THROW(NULL_POINTER_EXCEPTION)
    }

};

void throw_exception(int exc) {

    DumpClassAdded dumpClassAdded;

    SAFE_DELETE(dumpClassAdded, DumpClassAdded)


    THROW(exc)
}

void math_exception_executer() {

    DumpClassAddedWithExcep dumpClassAddedWithExcep;
    SAFE_DELETE(dumpClassAddedWithExcep, DumpClassAddedWithExcep)



    DumpClassAdded dumpClassAdded;

    SAFE_DELETE(dumpClassAdded, DumpClassAdded)

    DumpClassAdded dumpClassAdded2;

    SAFE_DELETE(dumpClassAdded2, DumpClassAdded)


    DumpClassAdded dumpClassAdded3;

    SAFE_DELETE(dumpClassAdded3, DumpClassAdded)


    DumpClassAdded dumpClassAdded4;

    SAFE_DELETE(dumpClassAdded4, DumpClassAdded)




    throw_exception(MATH_EXCEPTION);
}


void trying() {

    TRY (
            {
                std:: cout << "Before throwing" << std::endl;

                DumpClassNotAdded dumpClassNotAdded;


                DumpClassAdded dumpClassAdded;

                SAFE_DELETE(dumpClassAdded, DumpClassAdded)


                math_exception_executer();
                std:: cout << "After throw ---- mustn't be here" << std::endl;
            }

    ) CATCH(MATH_EXCEPTION,
            {
                std::cout << "Deal with error" << std::endl;
            }
    ) CATCH(NULL_POINTER_EXCEPTION,
            {
                std::cout << "Another exception, mustn't be here" << std::endl;
            }
    )

}

int main() {
  trying();
}