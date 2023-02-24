// U is the type of the elements of the array that is passed
// T is the type of the elements stored in the tree
class segment_tree {

    public:
        segment_tree(const int n);
        ~segment_tree();
        
        void build(const int a[]);
        int query(const int l, const int r);
        void update(const int pos, const int new_val);
    
        void print();
    private:
        void rec_built(const int a[], int v, int tl, int tr);
        int rec_query(int v, int tl, int tr, int l, int r);
        void rec_update(int v, int tl, int tr, const int &pos, const int &new_val);

        int *m_nodes;
        int m_n;
};