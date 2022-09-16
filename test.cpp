#include <iostream>
#include "general.h"
using namespace std;
int main()
{
    GovernmentID id(Passport, "1020a01", "XD", "00431", "SPCLEB Brad", Date(11, 10, 2011));
    cout << id << '\n';

    return 0;
}