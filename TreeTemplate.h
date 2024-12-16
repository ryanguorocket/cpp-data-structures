using pi = pair<int, int>;

struct Tree {
    int n, lgv; // size, log val
    vector<vector<int>> adj;
    vector<vector<int>> sparse;
    vector<int> par, dep, si;

    Tree() {}
    Tree(int nsi, vector<pi>& edges) {
        n = nsi;
        lgv = 32 - __builtin_clz(n); // floor(log_2(nsi)) + 1
        adj.resize(n);
        for(auto [i, j]: edges) {
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
        sparse = vector<vector<int>>(lgv, vector<int>(n));
        par.resize(n);
        dep.resize(n);
        si.resize(n);
        root(0);
    }

    void root(int r) {
        par[r] = -1;
        dep[r] = 0;
        dfs(r);
        initSparse();
    }
    void dfs(int p) {
        si[p] = 1;
        for(int i: adj[p]) {
            if(i == par[p]) continue;
            par[i] = p;
            dep[i] = dep[p] + 1;
            dfs(i);
            si[p] += si[i];
        }
    }
    void initSparse() {
        for(int i = 0; i < n; i++) sparse[0][i] = par[i];
        for(int i = 1; i < lgv; i++) {
            for(int j = 0; j < n; j++) {
                int m = sparse[i - 1][j];
                if(m == -1) continue;
                sparse[i][j] = sparse[i - 1][m];
            }
        }
    }

    int kthAncestor(int p, int k) {
        if(dep[p] < k) return -1;
        int ret = p;
        for(int i = 0; i < lgv; i++) if(k & (1 << i)) ret = sparse[i][ret];
        return ret;
    }
    int lca(int a, int b) {
        if (dep[a] < dep[b]) swap(a, b);
        int dd = dep[a] - dep[b];
        for(int i = 0; i < lgv; i++) if(dd & (1 << i)) a = sparse[i][a];
        if(a == b) return a;
        for(int i = lgv - 1; i >= 0; i--) {
            if(sparse[i][a] != sparse[i][b]) {
                a = sparse[i][a];
                b = sparse[i][b];
            }
        }
        return par[a];
    }
    int dist(int a, int b) {
        int lcav = lca(a, b);
        return dep[a] + dep[b] - 2 * dep[lcav];
    }
};
