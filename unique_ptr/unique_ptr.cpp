/*
https://en.cppreference.com/w/cpp/utility/move
https://docs.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=vs-2019
*/

#include <memory>
#include <iostream>

using namespace std;

class Foo {
public:
    Foo(int v) {
        cout << "reg constructor" << endl;
    }

    Foo(Foo &other) {
        cout << "copy" << endl;
    }

    Foo(Foo &&other) {
        cout << "move" << endl;
    }

    Foo&& operator=(Foo &&other) {
        cout << "move operator =" << endl;
    }
};

std::unique_ptr<Foo> NewFoo() {
    return std::unique_ptr<Foo>(new Foo(1));
}

void AcceptFoo(std::unique_ptr<Foo> f) {

}

void Bar() {
    std::unique_ptr<Foo> g = NewFoo();
    // AcceptFoo(g); // issue is here , AcceptRoo do copy constructor , violate unique_ptr property
    // refer to https://docs.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=vs-2019#robust-programming
    // below basically invoke g's move assignment operator
    AcceptFoo(std::move(g));
}

void Baz() {
    // this one just invoke one regular constructor
    AcceptFoo(NewFoo());
}

void test1(Foo f) {

}

int main() {
    //
    // Foo f(1);

    /*
        some key points below:
        regular below code will invoke reg constructor followed by move constructor
        but since some compiler optimization: https://stackoverflow.com/questions/33126236/why-constructor-is-not-called-when-passed-by-value
        you might just see reg constructor get called , if you try to compile with :
        g++ -std=c++11 unique_ptr.cpp -o unique_ptr.cpp.o -fno-elide-constructors
        Then you would see reg constructor get called followed move constructor
        test1(Foo(1));
    */
    test1(Foo(1));
    // Baz();
    return 0;
}