#include<vector>
#include<iostream>
#include "links.h"
using namespace std;
vector<vector<int> > key
    {{0,0,0,1,0,0,1,1},
    {0,0,1,1,0,1,0,0},
    {0,1,0,1,0,1,1,1},
    {0,1,1,1,1,0,0,1},
    {1,0,0,1,1,0,1,1},
    {1,0,1,1,1,1,0,0},
    {1,1,0,1,1,1,1,1},
    {1,1,1,1,0,0,0,1}};

//lok = list of keys for each of the 16 rounds
vector<vector<vector<int> > > lok;

vector<vector<int> > round_key(int round){
    return lok[round-1];
}
void print_2(vector<vector<int> > val){
    cout << "printing the 2-dimensional vector =>" << endl;
    for(int i=0;i<val.size();i++){
        for(int j=0;j<val[i].size();j++) cout << val[i][j] << " ";
        cout << endl;
    }
}
void print_3(vector<vector<vector<int> > > val){
    cout << "printing the 3-d vector" << endl;
    for(int i=0;i<val.size();i++){
        for(int j=0;j<val[i].size();j++){
            for(int k=0;k<val[i][j].size();k++){
                cout << val[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << "*********" << endl;
    }
}
void print_key(){
    for(int i=0;i<key.size();i++){
        for(int j=0;j<key[i].size();j++) cout << key[i][j] <<  " ";
        cout << endl;
    }
}
//generating 56-bit key from 64 bit original keys
vector<vector<int> > first_permutation(){
    vector<vector<int> > pc
    {{57,49,41,33,25,17,9},
    {1,58,50,42,34,26,18},
    {10,2,59,51,43,35,27},
    {19,11,3,60,52,44,36},
    {63,55,47,39,31,23,15},
    {7,62,54,46,38,30,22},
    {14,6,61,53,45,37,29},
    {21,13,5,28,20,12,4}};
    vector<vector<int> > ans;
    vector<int> temp;
    for(int i=0;i<pc.size();i++){
        for(int j=0;j<pc[i].size();j++){
            temp.push_back(key[(pc[i][j]-1)/8][(pc[i][j]-1)%8]);
        }
        ans.push_back(temp);
        temp.clear();
    }
    return ans;
}

//generating 48-bit keys for the roung function
vector<vector<int> > second_permutation(vector<vector<int> > list){
   vector<vector<int> > pc{
       {14,17,11,24,1,5},
       {3,28,15,6,21,10},
       {23,19,12,4,26,8},
       {16,7,27,20,13,2},
       {41,52,31,37,47,55},
       {30,40,51,45,33,48},
       {44,49,39,56,34,53},
       {46,42,50,36,29,32}
   };
   vector<vector<int> > ans;
    vector<int> temp;
    for(int i=0;i<pc.size();i++){
        for(int j=0;j<pc[i].size();j++){
            temp.push_back(list[(pc[i][j]-1)/7][(pc[i][j]-1)%7]);
        }
        ans.push_back(temp);
        temp.clear();
    }
    return ans;

}



//actual shifting operation performed
void shift(vector<vector<int> > &list){
    int seed = list[0][0];
    for(int i=0;i<list.size();i++){
        for(int j=0;j<list[i].size()-1;j++){
            list[i][j]=list[i][j+1];
        }
        list[i][6]=list[(i+1)%4][0];
    }
    list[3][6]=seed;
}

//leftshifting to form the round keys
vector<vector<vector<int> > > left_shift(vector<vector<int> > &check){
    vector<vector<int> > left,right,list,one,two;
    vector<int> temp;
    for(int i=0;i<4;i++){
        temp=check[i];
        left.push_back(temp);
    }
    for(int i=4;i<check.size();i++){
        temp=check[i];
        right.push_back(temp);
    }
    // print_2(left);
    // print_2(right);
    vector<vector<vector<int> > > final;
    string left_shift_string = "1122222212222221";
    for(int i=0;i<left_shift_string.size();i++){
        int len = int(left_shift_string[i])-int('0');
        while(len--){
            shift(left); shift(right);
        }
        list.insert(list.end(),left.begin(),left.end());
        list.insert(list.end(),right.begin(),right.end());
        // print_2(list);
        list=second_permutation(list);
        final.push_back(list);
        list.clear();
    }
    return final;
}

//driver function
int keygen(){
    vector<vector<int> > check;
    
    check = first_permutation();
    //print_2(check);
    lok=left_shift(check);
    // print_3(lok);
    return 0;
}