#include <bits/stdc++.h>
using namespace std;
class SGT
{
public:
    vector<int> seg, lazy;
    SGT(int n)
    {
        seg.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }
    void buildTree(int i, int l, int r, vector<int> &arr)
    {
        if (l == r)
        {
            seg[i] = arr[l];
            return;
        }
        int mid = (l + r) >> 1;
        buildTree(2 * i + 1, l, mid, arr);
        buildTree(2 * i + 2, mid + 1, r, arr);
        seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
    }
    void updatefromLazy(int &i, int &l, int &r)
    {
        if (lazy[i] == 0)
            return;
        seg[i] += ((r - l + 1) * lazy[i]);
        if (l != r)
        {
            lazy[2 * i + 1] = lazy[i];
            lazy[2 * i + 2] = lazy[i];
        }
        lazy[i] = 0;
    }
    int query(int i, int l, int r, int ql, int qr)
    {
        updatefromLazy(i, l, r);
        if (ql > r || qr < l)
            return 0;
        if (ql <= l && r <= qr)
            return seg[i];
        int mid = (l + r) >> 1;
        int left = query(2 * i + 1, l, mid, ql, qr);
        int right = query(2 * i + 2, mid + 1, r, ql, qr);
        return left + right;
    }
    void updateRange(int i, int l, int r, int ql, int qr, int val)
    {
        updatefromLazy(i, l, r);
        if (l > qr || r < ql)
            return;
        if (ql <= l && qr >= r)
        {
            seg[i] += ((r - l + 1) * val);
            if (l != r)
            {
                lazy[2 * i + 1] = val;
                lazy[2 * i + 2] = val;
            }
            return;
        }
        int mid = (l + r) >> 1;
        updateRange(2 * i + 1, l, mid, ql, qr, val);
        updateRange(2 * i + 2, mid + 1, r, ql, qr, val);
        seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
    }
    void update(int i, int l, int r, int ind, int value)
    {
        updatefromLazy(i, l, r);
        if (l == r)
        {
            seg[i] = value;
            return;
        }
        int mid = (l + r) >> 1;
        if (ind > mid)
            update(2 * i + 2, mid + 1, r, ind, value);
        else
            update(2 * i + 1, mid + 1, r, ind, value);
        seg[i] = (seg[2 * i + 1] + seg[2 * i + 2]);
    }
};
int main()
{
    vector<int> t = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int n = t.size();
    SGT sg(n);
    sg.buildTree(0, 0, n - 1, t);
    sg.updateRange(0, 0, n - 1, 0, 1, 2);
    cout << "Updated: " << sg.query(0, 0, n - 1, 1, 1);
    // sg.update(0, 0, n - 1, 8, -1);
    // cout << "Min value; " << sg.query(0, 0, n - 1, 0, 8);
    //    return 1;
}