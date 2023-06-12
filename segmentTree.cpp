#include <bits/stdc++.h>
using namespace std;
class segTree
{
public:
    vector<int> seg;
    segTree(int n)
    {
        seg.resize(4 * n + 1, 0);
    }
    void build(int i, int low, int high, vector<int> &arr)
    {
        if (low == high)
        {
            seg[i] = arr[low];
            return;
        }
        int mid = (low + high) >> 1;
        build(2 * i + 1, low, mid, arr);
        build(2 * i + 2, mid + 1, high, arr);
        seg[i] = min(seg[2 * i + 1], seg[2 * i + 2]);
    }
    int query(int i, int low, int high, int ql, int qh)
    {
        if (low > qh || high < ql)
            return INT_MAX;
        if (ql <= low && high <= qh)
        {
            return seg[i];
        }
        int mid = (low + high) >> 1;
        int left = query(2 * i + 1, low, mid, ql, qh);
        int right = query(2 * i + 2, mid + 1, high, ql, qh);
        return min(left, right);
    }
    void update(int i, int low, int high, int index, int val)
    {
        if (low == high && low == index)
        {
            seg[i] = val;
            return;
        }
        int mid = (low + high) >> 1;
        if (index <= mid)
            update(2 * i + 1, low, mid, index, val);
        else
            update(2 * i + 2, mid + 1, high, index, val);
        seg[i] = min(seg[2 * i + 1], seg[2 * i + 2]);
    }
};

int main()
{
    //    0 1 2 3 4 5   6  7 8
    vector<int> t = {3, 2, 1, 5, 2, 0, 45, 21, 3};
    int n = t.size();
    segTree seg(n);
    seg.build(0, 0, n - 1, t);
    cout << "Segment tree built\n";
    cout << seg.query(0, 0, n - 1, 0, 6);
    cout << "Performing update: ";
    seg.update(0, 0, n - 1, 5, 100);
    cout << "After update min: " << seg.query(0, 0, n - 1, 0, 6);
}