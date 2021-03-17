//  run command => g++ -std=c++11 *.cpp -o t && ./t
#include<vector>
#include<iostream>
#include<string>
#include<bitset>
#include "links.h"
using namespace std;
vector<vector<int> > initial_permutation(vector<vector<int> > &list){
    vector<vector<int> > ip
    {{58,50,42,34,26,18,10,2},
    {60,52,44,36,28,20,12,4},
    {62,54,46,38,30,22,14,6},
    {64,56,48,40,32,24,16,8},
    {57,49,41,33,25,17,9,1},
    {59,51,43,35,27,19,11,3},
    {61,53,45,37,29,21,13,5},
    {63,55,47,39,31,23,15,7}};
    vector<vector<int> > res(8,vector<int>(8,0));
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            res[i][j]=list[(ip[i][j]-1)/8][(ip[i][j]-1)%8];
        }
    }
    return res;
}
//ebit-selection i.e conversion of 32 bit input to 48 bit input for xoring with 48 bit round key
vector<vector<int > > ebit_select(vector<vector<int> > val){
    vector<vector<int> > ebit
    {
        {32,1,2,3,4,5},
        {4,5,6,7,8,9},
        {8,9,10,11,12,13},
        {12,13,14,15,16,17},
        {16,17,18,19,20,21},
        {20,21,22,23,24,25},
        {24,25,26,27,28,29},
        {28,29,30,31,32,1}
    };
    vector<vector<int> > res;
    vector<int> temp;
    for(int i=0;i<8;i++){
        for(int j=0;j<6;j++){
            temp.push_back(val[(ebit[i][j]-1)/8][(ebit[i][j]-1)%8]);
        }
        res.push_back(temp);
        temp.clear();
    }
    return res;
}
//xoring
vector<vector<int> > xoring(vector<vector<int> > &val,vector<vector<int > > &key){
    vector<vector<int> > res;
    vector<int> temp;
    for(int i=0;i<val.size();i++){
        for(int j=0;j<val[i].size();j++){
            temp.push_back((val[i][j]==key[i][j])?0:1);
        }
        res.push_back(temp);
        temp.clear();
    }
    return res;
}
int binary_to_int(int a,int b){
    return (2*(a)+1*(b));
}
int binary_to_int(int a,int b,int c,int d){
    return (8*a+4*b+2*c+1*d);
}

//compression from 48bits to 32 bits for last xoring 
vector<vector<int > > compression(vector<vector<int > > &list){
    vector<vector<int> > s1{
    {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
    {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
    {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
    {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    };
    vector<vector<int> > s2{
    {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
    {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
    {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
    {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    };
    vector<vector<int> > s3{
    {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
    {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
    {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
    {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    };
    vector<vector<int> > s4{
    {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
    {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
    {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
    {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    };
    vector<vector<int> > s5{
    {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
    {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
    {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
    {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    };
    vector<vector<int> > s6{
    {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
    {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
    {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
    {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    };
    vector<vector<int> > s7{
    {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
    {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
    {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
    {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    };
    vector<vector<int> > s8{
    {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
    {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
    {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
    {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    };
    vector<vector<int> > ans;
    vector<int> temp,lol;
    int row,col;
    for(int i=0;i<8;i++){
        lol=list[i];
        row=binary_to_int(lol[0],lol[5]);
        col=binary_to_int(lol[1],lol[2],lol[3],lol[4]);
        // cout << row << " " << col << endl;
        string s ;
        if(i==0) s=bitset<4>(s1[row][col]).to_string();
        else if(i==1) s=bitset<4>(s2[row][col]).to_string();
        else if(i==2) s=bitset<4>(s3[row][col]).to_string();
        else if(i==3) s=bitset<4>(s4[row][col]).to_string();
        else if(i==4) s=bitset<4>(s5[row][col]).to_string();
        else if(i==5) s=bitset<4>(s6[row][col]).to_string();
        else if(i==6) s=bitset<4>(s7[row][col]).to_string();
        else s=bitset<4>(s8[row][col]).to_string();
        // cout << "s=>" << s << endl;
        for(int j=0;j<s.size();j++){
            temp.push_back(int(s[j])-int('0'));
        }
        ans.push_back(temp);
        temp.clear();
    }
    // print_2(ans);
    return ans;
}
vector<vector<int> > last_permutation(vector<vector<int> > list){
    vector<vector<int> > p{
        {16,7,20,21},
        {29,12,28,17},
        {1,15,23,26},
        {5,18,31,10},
        {2,8,24,14},
        {32,27,3,9},
        {19,13,30,6},
        {22,11,4,25}
    };
    vector<vector<int> > ans;
    vector<int> temp;
    for(int i=0;i<8;i++){
        for(int j=0;j<4;j++){
            temp.push_back(list[(p[i][j]-1)/4][(p[i][j]-1)%4]);
        }
        if(i%2!=0){
            ans.push_back(temp);
            temp.clear();}
    }
    return ans;
}

//round function
vector<vector<int> > round(vector<vector<int> > val,vector<vector<int> > key){
    // cout << key.size() << " " << key[0].size() << endl;
    val = ebit_select(val);
    val = xoring(val,key);
    // cout << val.size() << " " << val[0].size() << endl;
    // return val;
    // print_2(val);
    val = compression(val);
    // cout << val.size() << " " << val[0].size() << endl;
    val = last_permutation(val);
    // print_2(val);
    return val;
}

vector<vector<int> > inverse_permutation(vector<vector<int> > list){
    vector<vector<int > > ip{
        {40,8,48,16,56,24,64,32},
        {39,7,47,15,55,23,63,31},
        {38,6,46,14,54,22,62,30},
        {37,5,45,13,53,21,61,29},
        {36,4,44,12,52,20,60,28},
        {35,3,43,11,51,19,59,27},
        {34,2,42,10,50,18,58,26},
        {33,1,41,9,49,17,57,25}
    };
    vector<vector<int > > ans;
    vector<int> temp;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            temp.push_back(list[(ip[i][j]-1)/8][(ip[i][j]-1)%8]);
        }
        ans.push_back(temp);
        temp.clear();
    }
    return ans;
}
char int_to_hex(int x){
    switch(x){
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        case 10:
            return 'A';
        case 11:
            return 'B';
        case 12:
            return 'C';
        case 13:
            return 'D';
        case 14:
            return 'E';
        case 15:
            return 'F';
    }
    return '!';
}
int main(){
    keygen();
    // print_2(round_key(1));
    // assuming the plaintext only contain hexadecimal characters
    // plain-text= "0123456789ABCDEF";
    //from the assumed plain-text the 64 bit matrix for the above plain-text would be
    string m="";
    vector<vector<int> > plain;
    vector<int> temp;
    for(int i=0;i<16;i++){
        m=bitset<4>(i).to_string();
        for(int j=0;j<4;j++){
            temp.push_back(int(m[j])-int('0'));
        }
        if(temp.size()==8){
            plain.push_back(temp);
            temp.clear();
        }
    }
    // print_2(plain);
    plain = initial_permutation(plain);
    // print_2(plain);
    vector<vector<int> > left,right,check;
    for(int i=0;i<4;i++) left.push_back(plain[i]);
    for(int i=4;i<8;i++) right.push_back(plain[i]);

    // check=left;
    // left=right;
    // // print_2(round_key(1));
    // right=round(right,round_key(1));
    // right=xoring(check,right);
    // print_2(right);
    for(int i=1;i<=16;i++){
        check=left;
        left=right;
        right=round(right,round_key(i));
        right=xoring(check,right);
        
    }
    // print_2(left);
    // print_2(right);
    check.clear();
    for(int i=0;i<4;i++){
        check.push_back(right[i]);
    }
    for(int i=0;i<4;i++) check.push_back(left[i]);

    check = inverse_permutation(check);
    string result="";
    for(int i=0;i<8;i++){
        temp=check[i];
        int one=binary_to_int(temp[0],temp[1],temp[2],temp[3]);
        int two=binary_to_int(temp[4],temp[5],temp[6],temp[7]);
        result+=int_to_hex(one);
        result+=int_to_hex(two);
    }
    cout << result << endl;
    


    return 0;
}