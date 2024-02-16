// 组合数学插板模型
// 这个题我们需要认识到，拼图1 和 拼图2 是最重要的，因为 3 和 4 无法改变 凸 和 凹
// 这里我们假设 0 代表 凹陷， 1 代表 凸出
// 则拼图1 表示为 11，拼图2 表示为 00，拼图3 表示为 01，拼图4 表示为 10

// 插板法基础思想：
//  n 个球，放到 m 个盒子，每个盒子至少放一个，则共有 C(n - 1, m - 1) 种

// 那么 n 个球，放到 m 个盒子，每个盒子至少放 x 个
// 方案数就是 C(n + m * (1 - x) - 1,   m - 1)
// 推导：n - m * (x - 1) - 1,其中 m - 1 不变
// 由于本题每个空至少放 0 个球，则方案数为 C(n + m - 1, m - 1)

#include <bits/stdc++.h>
using namespace std;

using LL = long long;

const LL mod = 998244353;
const int N = 2000005;

// 组合数 C(n,m) 求解模型
LL fac[N], jv[N], inv[N];
void C_init(int n)
{
    jv[0] = fac[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        inv[i] = (i == 1) ? 1 : (mod - mod / i) * inv[mod % i] % mod;
        fac[i] = fac[i - 1] * i % mod;
        jv[i] = jv[i - 1] * inv[i] % mod;
    }
}

inline LL C(int n, int m)
{
    // 注意：基于数据范围给出的特判
    if (n < m || m < 0)
        return 0;

    // C(n,m) = n! / ( m! * (n - m)! )
    return fac[n] * jv[n - m] % mod * jv[m] % mod;
}

void solve(const int &Case)
{
    int c1, c2, c3, c4;
    cin >> c1 >> c2 >> c3 >> c4;

    int cnt0 = 2 * c2 + c3 + c4;
    int cnt1 = 2 * c1 + c3 + c4;

    // 能排成一排意味着 abs(凹陷 - 突出) <= 2
    // 所以我们分成 c1 > c2 , c1 < c2, c1 = c2三种情况

    // 其中 c1 = c2 分为 c1 和 c2 都为 0 和都不为 0 的情况
    // 其中，第一种情况特殊表示无法插板
    // 第二种情况，c1 和 c2 排列顺序不同有两种不同情况出现，要分别讨论相加

    if (abs(cnt0 - cnt1) > 2)
    {
        cout << 0 << '\n';
        return;
    }

    // 这里对 c1 > c2这种情况做示例分析
    //   11  00  11  00  11
    // 10  01  10  01  10  01
    // 这里 n = c3 或者 c4, m = c2 + 1
    
    if (c1 > c2)
    {
        cout << 1LL * C(c2 + c3, c2) * C(c2 + c4, c2) % mod << '\n';
        return;
    }
    else if (c1 < c2)
    {
        cout << 1LL * C(c1 + c3, c1) * C(c1 + c4, c1) % mod << '\n';
        return;
    }
    else
    {
        if (c1 == 0 && c2 == 0)
        {
            if (c3 == 0 || c4 == 0)
                cout << 1 << '\n';

            else
                cout << 0 << '\n';
            return;
        }

        // 这里对 c1 = c2 > 0 情况说明
        //   11  00  11  00                          00  11  00  11
        // 10  01  10  01  10                      01  10  01  10  01
        // 放 c3(01)                               放 c3(01)
        // m = c1                                  m = c1 + 1
        // n = c3                                  n = c3
        // 放 c4(10)                               放 c4(10)
        // m = c2 + 1                              m = c2
        // n = c4                                  n = c4

        int ans1 = 1LL * C(c1 + c3 - 1, c1 - 1) * C(c2 + c4, c2) % mod;
        int ans2 = 1LL * C(c2 + c4 - 1, c2 - 1) * C(c1 + c3, c1) % mod;
        cout << (ans1 + ans2) % mod << '\n';
        return;
    }
}

int main(void)
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    // 注意这里提前初始化好需要用到的数组
    // 这里 0 <= ci <= 1e6
    C_init(2e6);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        solve(i);
    }
    return 0;
}