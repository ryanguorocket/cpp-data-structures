using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

void e_euclidean(ll a, ll b, __int128& x, __int128& y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return;
    }
    __int128 x1, y1;
    e_euclidean(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
}
ll get_inv(ll a, ll b) { // get inverse of a in ring of b
    assert(a >= 0 && b > 0);
    assert(__gcd(a, b) == 1ll);
    __int128 x, y;
    e_euclidean(a, b, x, y);
    return (x % b + b) % b;
}
pll CRT(pll c1, pll c2) {
    assert(c1.first > 0 && c2.first > 0);
    /*
    {i, j} means all values of form ix + j, or x % i == j
    */
    ll n1 = c1.first, n2 = c2.first, a1 = c1.second, a2 = c2.second;
    // n1(-k1) + n2k2 = a1 - a2
    ll gv = __gcd(n1, n2);
    if((a1 - a2) % gv != 0) return {-1ll, -1ll};
    __int128 x, y;
    e_euclidean(n1, n2, x, y);
    __int128 cv = a1 + __int128((a2 - a1) / gv) * x * n1;
    ll lcmv = (__int128(n1) * n2) / gv;
    cv = (cv % lcmv + lcmv) % lcmv;
    return make_pair(lcmv, ll(cv));
}
ll ceil_div(ll num, ll den) {
    assert(den != 0);
    if(den < 0) {
        num *= -1;
        den *= -1;
    }
    if(num >= 0) return (num + den - 1) / den;
    else return num / den;
}
ll floor_div(ll num, ll den) {
    assert(den != 0);
    if(den < 0) {
        num *= -1;
        den *= -1;
    }
    if(num >= 0) return num / den;
    else return (num - den + 1) / den;
}
ll get_num_sols(pll sol, ll a, ll b) { // Number of solutions in [a, b]
    auto [i, j] = sol;
    /*
    a <= ix + j <= b
    a - j <= ix <= b - j
    (a - j) / i <= x <= (b - j) / i
    */
    ll lb = ceil_div(a - j, i);
    ll rb = floor_div(b - j, i);
    return rb - lb + 1;
}

struct LIN_CONG {
    ll a, b, c;
    // ax % b == c
    LIN_CONG(): a{0ll}, b{1ll}, c{0ll} {}
    LIN_CONG(ll na, ll nb, ll nc): a{na}, b{nb}, c{nc} {
        assert(b > 0);
        if(a < 0) {
            a *= -1;
            c *= -1;
        }
        a %= b;
        c = (c % b + b) % b;
        // NOTE: a, b, c >= 0 after this point
    }
    pll get_sols() {
        // {-1, -1} if no sol
        /*
        All answers in form of ix + j, where i, j >= 0
        ax % b = c
        x \cong ca^-1
        */
        ll gv = __gcd(a, b);
        if(c % gv != 0) return {-1ll, -1ll};
        ll na = a / gv, nb = b / gv, nc = c / gv;
        nc = (__int128(nc) * get_inv(na, nb)) % nb;
        return {nb, nc};
    }
};
