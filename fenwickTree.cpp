#include<bits/stdc++.h>
using namespace std;
// update logn
// sum logn
// each index in fen store sum in particular range
//  for example index i store sum range btw (l-i) where l is number you get turning of right bit of i
class FenwickTree{
    public:
    vector<int>fen;
    FenwickTree(int n){
        fen.resize(n+1,0);
    }
    void buildTree(vector<int>& arr){
        int n=arr.size();
        for(int i=0;i<n;i++){
            update(i,arr[i]);
        }
    }
// update curenct index and go to next index
// next index is= (2's complement of curr index & current index)+index
    void update(int i,int val){
        i++;
        while(i<fen.size()){
            fen[i]+=val;
            i=(i+(i&(-i)));
        }
    }
// sume is sum of indexes of i where i varies from i to 0 by turining of right most bit
    int sum(int i){
        i++;
        int s=0;
        while(i>0){
            s+=fen[i];
            i=(i&(i-1));
        }
        return s;
    }
    int range(int i,int j){
        return sum(j)-sum(i-1);
    }
    void print(){
        for(int i=0;i<fen.size();i++)cout<<fen[i]<<" ";
    }
};

int main(){
    vector<int>arr={1,0,2,1,1,3,0,4,2,5,2,2,3,1,0,2};
    int n=arr.size();
    FenwickTree f(n);
    f.buildTree(arr);
    cout<<"sum: "<<f.sum(4);    
    cout<<"\nsum: "<<f.range(11,12);
}