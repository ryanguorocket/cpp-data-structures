
constexpr int MOD = 1e9 + 7; // can change this to any value (must be prime if you want inverse)
struct Mint {
    int v;
    Mint() {v = 0;}
    Mint(int nv) {v = nv % MOD;}
    Mint(long long nv) {v = nv % MOD;}
    Mint(const Mint &a) {v = a.v;}
    Mint pow(int a) {
        if(a < 0) return (*this).inv().pow(-a);
        long long ret = 1;
        long long base = v;
        while(a > 0) {
            if(a & 1) ret = (ret * base) % MOD;
            base = (base * base) % MOD;
            a >>= 1;
        }
        return Mint((int)ret);
    }
    Mint inv() {return this->pow(MOD - 2);}
    Mint operator + (int a) const {return Mint((v + a) % MOD);}
    Mint operator + (const Mint &a) const {return Mint((v + a.v) % MOD);}
    Mint& operator += (int a) {
        v = (v + a) % MOD;
        return *this;
    }
    Mint& operator += (const Mint &a) {
        v = (v + a.v) % MOD;
        return *this;
    }
    Mint operator - (int a) const {return Mint((v - a + MOD) % MOD);}
    Mint operator - (const Mint &a) const {return Mint((v - a.v + MOD) % MOD);}
    Mint& operator -= (int a) {
        v = (v - a + MOD) % MOD;
        return *this;
    }
    Mint& operator -= (const Mint &a) {
        v = (v - a.v + MOD) % MOD;
        return *this;
    }
    Mint operator * (int a) const {return Mint(((long long)v * a) % MOD);}
    Mint operator * (const Mint &a) const {return Mint(((long long)v * a.v) % MOD);}
    Mint& operator *= (int a) {
        v = ((long long)v * a) % MOD;
        return *this;
    }
    Mint& operator *= (const Mint &a) {
        v = ((long long)v * a.v) % MOD;
        return *this;
    }
    Mint operator / (int a) const {return Mint(v) * Mint(a).inv();}
    Mint operator / (const Mint a) const {return Mint(v) * Mint(a).inv();}
    Mint& operator /= (int a) {
        v = ((long long)v * Mint(a).inv().v) % MOD;
        return *this;
    }
    Mint& operator /= (const Mint &a) {
        v = ((long long)v * Mint(a).inv().v) % MOD;
        return *this;
    }
    Mint& operator = (int a) {
        v = a;
        return *this;
    }
    bool operator == (int a) const {return v == a;}
    bool operator == (const Mint &a) const {return v == a.v;}
    bool operator != (int a) const {return v != a;}
    bool operator != (const Mint &a) const {return v != a.v;}
    friend ostream& operator << (ostream &os, const Mint &a) {
        os << a.v;
        return os;
    }
};
