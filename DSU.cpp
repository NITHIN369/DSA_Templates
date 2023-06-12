#include <vector>
#include <iostream>
using namespace std;
class DSU
{
public:
    vector<int> sz, par;
    DSU(int n)
    {
        sz.resize(n, 1);
        par.resize(n);
        for (int i = 0; i < n; i++)
        {
            par[i] = i;
        }
    }
    int parent(int node)
    {
        if (par[node] == node)
            return node;
        return par[node] = parent(par[node]);
    }
    void unionBySize(int u, int v)
    {
        int up = parent(u);
        int vp = parent(v);
        if (up == vp)
            return;
        if (sz[up] > sz[vp])
        {
            sz[up] += sz[vp];
            par[vp] = up;
        }
        else
        {
            sz[vp] += sz[up];
            par[up] = vp;
        }
    }
};