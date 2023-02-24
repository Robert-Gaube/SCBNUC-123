#include <iostream>
#include "segment_tree.h"
using namespace std;
int main() {
    segment_tree st{10};

    int v[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    st.build(v);
    st.print();
    cout << st.query(0, 4) << endl;
    //cout << st.query(3, 7) << endl;
    //cout << st.query(0, 9) << endl;

    return 0;
}