constexpr int mod1 = 10889991, 
constexpr int mod2 = 12356487;
struct Hash {
    int h1, h2;
    Hash() {h1 = h2 = 0;}
    Hash(int nv) {h1 = h2 = nv;}
    Hash(int nh1, int nh2) {
        h1 = nh1;
        h2 = nh2;
    }
    Hash operator + (int a) const {return Hash((h1 + a) % mod1, (h2 + a) % mod2);}
    Hash operator + (const Hash &a) const {return Hash((h1 + a.h1) % mod1, (h2 + a.h2) % mod2);}
    Hash& operator += (int a) {
        h1 = (h1 + a) % mod1;
        h2 = (h2 + a) % mod2;
        return *this;
    }
    Hash& operator += (const Hash &a) {
        h1 = (h1 + a.h1) % mod1;
        h2 = (h2 + a.h2) % mod2;
        return *this;
    }
    Hash operator - (int a) const {return Hash((h1 - a + mod1) % mod1, (h2 - a + mod2) % mod2);}
    Hash operator - (const Hash &a) const {return Hash((h1 - a.h1 + mod1) % mod1, (h2 - a.h2 + mod2) % mod2);}
    Hash& operator -= (int a) {
        h1 = (h1 - a + mod1) % mod1;
        h2 = (h2 - a + mod2) % mod2;
        return *this;
    }
    Hash& operator -= (const Hash &a) {
        h1 = (h1 - a.h1 + mod1) % mod1;
        h2 = (h2 - a.h2 + mod2) % mod2;
        return *this;
    }
    Hash operator * (int a) const {return Hash(((long long)h1 * a) % mod1, ((long long)h2 * a) % mod2);}
    Hash operator * (const Hash &a) const {return Hash(((long long)h1 * a.h1) % mod1, ((long long)h2 * a.h2) % mod2);}
    Hash& operator *= (int a) {
        h1 = ((long long)h1 * a) % mod1;
        h2 = ((long long)h2 * a) % mod2;
        return *this;
    }
    Hash& operator *= (const Hash &a) {
        h1 = ((long long)h1 * a.h1) % mod1;
        h2 = ((long long)h2 * a.h2) % mod2;
        return *this;
    }
    Hash& operator = (int a) {
        h1 = a % mod1, h2 = a % mod2;
        return *this;
    }
    Hash& operator = (const Hash &a) {
        h1 = a.h1, h2 = a.h2;
        return *this;
    }
    bool operator == (int a) const {return (h1 == a && h2 == a);}
    bool operator == (const Hash &a) const {return (h1 == a.h1 && h2 == a.h2);}
    bool operator != (int a) const {return !(h1 == a && h2 == a);}
    bool operator != (const Hash &a) const {return !(h1 == a.h1 && h2 == a.h2);}
    bool operator < (const Hash &a) const {return make_pair(h1, h2) < make_pair(a.h1, a.h2);}
    friend ostream& operator << (ostream &os, const Hash &a) {
        os << "{" << a.h1 << ", " << a.h2 << "}";
        return os;
    }
};

/*
READ BEFORE USING:
- MAX_HASH should be at least size of largest possible input string
- BASE should be at least 2 more than max element
    - Safe to just set to massive number, a.k.a. GPH (unless an actual string, then use SH)
- BASE should be the same all throughout
*/
bool initialized_pow = false;
const int MAX_HASH = 2e6 + 5;
Hash hash_pow[MAX_HASH];
template <int BASE>
struct String_Hash {
    int sz;
    vector<Hash> prefix_hash;
    String_Hash() {}
    String_Hash(const vector<int>& v) { // elements should be in range [0, BASE - 1) -> [1, BASE)
        assert(!v.empty());
        init(v);
    }
    String_Hash(const string& s, bool str_case = false) { // false -> lowercase, true -> uppercase
        assert(s.length());
        vector<int> to_vec(s.length());
        for(int i = 0; i < s.length(); i++) {
            if(str_case) to_vec[i] = s[i] - 'A';
            else to_vec[i] = s[i] - 'a';
        }
        init(to_vec);
    }
    void init(const vector<int>& v) {
        // Add 1 to everything so that 0 actually means something
        sz = v.size();
        if(!initialized_pow) {
            initialized_pow = true;
            hash_pow[0] = Hash(1);
            for(int i = 1; i < MAX_HASH; i++) hash_pow[i] = hash_pow[i - 1] * BASE;
        }
        prefix_hash.resize(sz);
        prefix_hash[0] = v[0] + 1;
        for(int i = 1; i < sz; i++) {
            prefix_hash[i] = prefix_hash[i - 1] + hash_pow[i] * (v[i] + 1);
        }
    }
    Hash range(int be, int en) {
        Hash ret = prefix_hash[en];
        if(be) ret -= prefix_hash[be - 1];
        ret *= hash_pow[MAX_HASH - 1 - be];
        return ret;
    }
    Hash get_hash() {
        return range(0, sz - 1);
    }
};

typedef String_Hash<27> SH; // For strings
typedef String_Hash<1000000009> GPH; // General purpose

/*
Example use case:

int main() {
    SH s1("hihello");
    SH s2("hellohi");
    cout << s1.range(2, 6) << "\n"; // Hash of "hello"
    cout << s2.range(0, 4) << "\n"; // Hash of "hello"
}

*/
