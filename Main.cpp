#include <iostream>
#include "Vector-1.h"
#include <sstream>
#include <stdexcept>

using namespace std;

int main(){
    Vector<int> v;

    for(int i = 0; i < 10; i++){
        v.push_back(i);
    }

    v.push_back(11);
    v.erase(4);
    cout << v.at(3) << endl;

    return 0;
}