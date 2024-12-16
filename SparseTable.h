template <typename T, typename Func>
struct Sparse_Table {
    int si, lgv;
    vector<vector<T>> st;
    Func func;
    Sparse_Table() {}
    Sparse_Table(const vector<T>& arr, Func f) : func(f) {
        si = arr.size();
        int lgv = 32 - __builtin_clz(si); // floor(log_2(et.size())) + 1
        st = vector<vector<T>>(lgv, vector<T>(si));
        for(int i = 0; i < si; i++) st[0][i] = arr[i];
        for(int i = 1; i < lgv; i++) {
            for(int j = 0; j < si; j++) {
                if(j + (1 << (i - 1)) < si) {
                    st[i][j] = func(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
                }
                else st[i][j] = st[i - 1][j];
            }
        }
    }
    T query(int a, int b) { // range query [a, b]
        int l2v = 31 - __builtin_clz(b - a + 1);
        T av = st[l2v][a];
        T bv = st[l2v][b - (1 << l2v) + 1];
        return func(av, bv);
    };
};

// Common ones
template <typename T>
struct Min_Sparse_Table : public Sparse_Table<T, function<T(T, T)>> {
    Min_Sparse_Table() {
        this->func = [](T a, T b) { return min(a, b); };
    }
    Min_Sparse_Table(const vector<T>& arr)
        : Sparse_Table<T, function<T(T, T)>>(arr, [](T a, T b) { return min(a, b); }) {}
};
template <typename T>
struct Max_Sparse_Table : public Sparse_Table<T, function<T(T, T)>> {
    Max_Sparse_Table() {
        this->func = [](T a, T b) { return max(a, b); };
    }
    Max_Sparse_Table(const vector<T>& arr)
        : Sparse_Table<T, function<T(T, T)>>(arr, [](T a, T b) { return max(a, b); }) {}
};
template <typename T>
struct GCD_Sparse_Table : public Sparse_Table<T, function<T(T, T)>> {
    GCD_Sparse_Table() {
        this->func = [](T a, T b) { return __gcd(a, b); };
    }
    GCD_Sparse_Table(const vector<T>& arr)
        : Sparse_Table<T, function<T(T, T)>>(arr, [](T a, T b) { return __gcd(a, b); }) {}
};
