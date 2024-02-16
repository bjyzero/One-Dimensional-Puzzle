// �����ѧ���ģ��
// �����������Ҫ��ʶ����ƴͼ1 �� ƴͼ2 ������Ҫ�ģ���Ϊ 3 �� 4 �޷��ı� ͹ �� ��
// �������Ǽ��� 0 ���� ���ݣ� 1 ���� ͹��
// ��ƴͼ1 ��ʾΪ 11��ƴͼ2 ��ʾΪ 00��ƴͼ3 ��ʾΪ 01��ƴͼ4 ��ʾΪ 10

// ��巨����˼�룺
//  n ���򣬷ŵ� m �����ӣ�ÿ���������ٷ�һ�������� C(n - 1, m - 1) ��

// ��ô n ���򣬷ŵ� m �����ӣ�ÿ���������ٷ� x ��
// ���������� C(n + m * (1 - x) - 1,   m - 1)
// �Ƶ���n - m * (x - 1) - 1,���� m - 1 ����
// ���ڱ���ÿ�������ٷ� 0 �����򷽰���Ϊ C(n + m - 1, m - 1)

#include <bits/stdc++.h>
using namespace std;

using LL = long long;

const LL mod = 998244353;
const int N = 2000005;

// ����� C(n,m) ���ģ��
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
    // ע�⣺�������ݷ�Χ����������
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

    // ���ų�һ����ζ�� abs(���� - ͻ��) <= 2
    // �������Ƿֳ� c1 > c2 , c1 < c2, c1 = c2�������

    // ���� c1 = c2 ��Ϊ c1 �� c2 ��Ϊ 0 �Ͷ���Ϊ 0 �����
    // ���У���һ����������ʾ�޷����
    // �ڶ��������c1 �� c2 ����˳��ͬ�����ֲ�ͬ������֣�Ҫ�ֱ��������

    if (abs(cnt0 - cnt1) > 2)
    {
        cout << 0 << '\n';
        return;
    }

    // ����� c1 > c2���������ʾ������
    //   11  00  11  00  11
    // 10  01  10  01  10  01
    // ���� n = c3 ���� c4, m = c2 + 1
    
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

        // ����� c1 = c2 > 0 ���˵��
        //   11  00  11  00                          00  11  00  11
        // 10  01  10  01  10                      01  10  01  10  01
        // �� c3(01)                               �� c3(01)
        // m = c1                                  m = c1 + 1
        // n = c3                                  n = c3
        // �� c4(10)                               �� c4(10)
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

    // ע��������ǰ��ʼ������Ҫ�õ�������
    // ���� 0 <= ci <= 1e6
    C_init(2e6);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        solve(i);
    }
    return 0;
}