struct DSU {
    int sz, numComp;
    vector<int> par, si;

    DSU() {}
    DSU(int nsz) {
        sz = nsz;
        par.resize(sz);
        si.resize(sz);
        numComp = nsz;
        for(int i = 0; i < sz; i++) {
            par[i] = i;
            si[i] = 1;
        }
    }

    int findPar(int p) {
        if(par[p] == p) return p;
        return par[p] = findPar(par[p]);
    }
    bool connected(int a, int b) {
        return findPar(a) == findPar(b);
    }
    void connect(int a, int b) {
        a = findPar(a);
        b = findPar(b);
        if(a == b) return;
        numComp--;
        if(si[a] < si[b]) swap(a, b);
        par[b] = a;
        si[a] += si[b];
    }

    int getSize(int p) {
        p = findPar(p);
        return si[p];
    }
    int getNum() {
        return numComp;
    }
};
