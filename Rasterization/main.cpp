#include <iostream>

using namespace std;

class Text
{
public:
    int a = 0;
    string b = "haha";
};

int main() {
    Text t;
    cout << t.a << endl;
    cout << t.b << endl;
    return 0;
}