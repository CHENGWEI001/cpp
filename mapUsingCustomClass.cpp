// Example program
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

class MyTuple;

typedef set<MyTuple>::iterator myIt;

class MyTuple {
public:
  string word;
  unsigned int cnt;
  bool isInQ;
  myIt it;
  MyTuple(string &word, unsigned int cnt) {
      this->word = word;
      this->cnt = cnt;
      this->isInQ = false;
  }
  MyTuple() {
      cout << "empty construtor called" << endl;
      this->word = "";
      this->cnt = 0;
      this->isInQ = false;
  }
  MyTuple(const MyTuple &other) {
      this->word = other.word;
      this->cnt = other.cnt;
      this->isInQ = other.isInQ;
  }
  MyTuple& operator=(const MyTuple &other) {
      cout << "copy assignment operator called" << endl;
      return *this;
  }
  bool operator< (const MyTuple &other) const {
      return cnt < other.cnt || (cnt == other.cnt && word > other.word);
  }
};

int main()
{

    map<int, MyTuple> myMap;
    string str("test");
    MyTuple foo = MyTuple(str, 5); // constructor called with two params
    // myMap.insert(make_pair(5, foo));
    myMap[5] = foo; // since myMap doesn't have key in myMap, myMap[5] first do constructor with 0 params constructor, then call copy assignment operator to copy the obj
    // myMap[5] = foo;
}
