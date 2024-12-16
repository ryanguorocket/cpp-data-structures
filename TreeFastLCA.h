// Construction in O(nlogn), LCA query in O(1)

using pi = pair<int, int>;

struct Fast_LCA {
    int n, s, lgv; // tree size, sparse size, log val
    vector<vector<int>> adj;
    vector<vector<pi>> sparse;
    vector<int> par, dep, etPos;
    vector<pi> et; // dep, index

    Fast_LCA() {}
    Fast_LCA(int nsi, vector<pi>& edges) {
        n = nsi;
        adj.resize(n);
        for(auto [i, j]: edges) {
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
        par.resize(n);
        dep.resize(n);
        etPos.resize(n);
        root(0);
    }

    void root(int r) {
        par[r] = -1;
        etDfs(r);
        initSparse();
    }
    void etDfs(int p) {
        etPos[p] = et.size();
        et.push_back({dep[p], p});
        for(int i: adj[p]) {
            if(i == par[p]) continue;
            par[i] = p;
            dep[i] = dep[p] + 1;
            etDfs(i);
            et.push_back({dep[p], p});
        }
    }
    void initSparse() {
        s = et.size();
        lgv = 32 - __builtin_clz(et.size()); // floor(log_2(et.size())) + 1
        sparse = vector<vector<pi>>(lgv, vector<pi>(s));
        for(int i = 0; i < s; i++) sparse[0][i] = et[i];
        for(int i = 1; i < lgv; i++) {
            for(int j = 0; j < s; j++) {
                if(j + (1 << (i - 1)) < s) {
                    sparse[i][j] = min(sparse[i - 1][j], sparse[i - 1][j + (1 << (i - 1))]);
                }
                else sparse[i][j] = sparse[i - 1][j];
            }
        }
    }
    pi sparseQuery(int a, int b) {
        int l2v = 31 - __builtin_clz(b - a + 1);
        pi av = sparse[l2v][a];
        pi bv = sparse[l2v][b - (1 << l2v) + 1];
        return min(av, bv);
    }

    int lca(int a, int b) {
        int l = etPos[a], r = etPos[b];
        if(l > r) swap(l, r);
        return sparseQuery(l, r).second;
    }
};
