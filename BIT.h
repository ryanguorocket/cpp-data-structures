using ll = long long;

struct BIT {
    int si;
    vector<ll> bit;
    BIT() {}
    BIT(int nsi) {
        si = nsi;
        bit = vector<ll>(nsi + 1);
    }
    void reset() {
        fill(bit.begin(), bit.end(), 0ll);
    }
    void update(int p, ll v) {
        for(p++; p <= si; p += p & -p) bit[p] += v;
    }
    ll query(int p) {
        ll ret = 0;
        for(p++; p > 0; p -= p & -p) ret += bit[p];
        return ret;
    }
    ll query(int a, int b) {
        return query(b) - query(a - 1);
    }
};
