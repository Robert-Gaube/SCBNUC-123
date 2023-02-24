#include "segment_tree.h"
#include <iostream>

const int& min(const int& a, const int& b) {
    return (a < b) ? a : b;
}

const int& max(const int& a, const int& b) {
    return (a < b) ? b : a;
}
segment_tree::segment_tree(const int n) {
    m_nodes = new int[4*n];
    m_n = n;
}
segment_tree::~segment_tree() {
    delete m_nodes;
}

void segment_tree::build(const int *a) {
    segment_tree::rec_built(a, 1, 0, m_n - 1);
}
int segment_tree::query(const int l, const int r) {
    return segment_tree::rec_query(1, 0, m_n - 1, l, r);
}
void segment_tree::update(const int pos, const int new_val) {
    segment_tree::rec_update(1, 0, m_n - 1, pos, new_val);
}

void segment_tree::rec_built(const int a[], int v, int tl, int tr) {
    if(tl == tr) {
        m_nodes[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        rec_built(a, v * 2, tl, tm);
        rec_built(a, v * 2 + 1, tm + 1, tr);
        m_nodes[v] = m_nodes[v * 2] + m_nodes[v * 2 + 1];
    }
}
int x;
int segment_tree::rec_query(int v, int tl, int tr, int l, int r) {
    if(l > r) {
        return 0;
    } else if (tl == l && tr == r) {
        return m_nodes[v];
    } else {
        int tm = (tl + tr) / 2;
        std::cout << v * 2 << " " << tl << " " << tm << " " << l << " " << min(r, tm) << '\n';
        std::cout << v * 2 + 1<< " " << tm << " " << tr << " " << max(tm, l) << " " << r << "\n\n";
        std::cin >> x;
        return rec_query(v * 2, tl, tm, l, min(r, tm)) 
        + rec_query(v * 2 + 1, tm + 1, tr, max(l, tm), r);
    }
}
void segment_tree::rec_update(int v, int tl, int tr, const int &pos, const int &new_val) {
    if(tl == tr) {
        m_nodes[v] = new_val;
    } else {
        int tm = (tr + tl) / 2;
        if(pos < tm) rec_update(v * 2, tl, tm, pos, new_val);
        else rec_update(v * 2 + 1, tm + 1, tr, pos, new_val);
        m_nodes[v] = m_nodes[v * 2] + m_nodes[v * 2 + 1];
    }
}

void segment_tree::print() {
    int i;
    for(i = 1; i <= 4*m_n; ++i) {
        if(m_nodes[i])
            std::cout << m_nodes[i] << "(" << i << ") ";
    }
    std::cout << '\n';
}