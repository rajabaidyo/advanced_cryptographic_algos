#ifndef KEY_GENERATOR_H
#define KEY_GENERATOR_H
#include<vector>
using namespace std;
int keygen();
vector<vector<int> > round_key(int round);
void print_2(vector<vector<int> > val);

#endif