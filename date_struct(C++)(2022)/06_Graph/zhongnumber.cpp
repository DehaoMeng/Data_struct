//
// Created by 86176 on 2022/6/6 0006.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> a;
    int num;
    while (cin >> num){
        a.push_back(num);
        char ch = getchar();
        if (ch == '\n')
            break;
    }
    sort(a.begin(), a.end());

    int i = 0;
    int MaxCount = 1;
    int index = 0;

    while (i < a.size() - 1){
        int count = 1;
        int j;
        for (j = i; j < a.size() - 1; j++){
            if (a[j] == a[j + 1]){
                count++;
            }
            else{
                break;
            }
        }
        if (MaxCount < count){
            MaxCount = count;
            index = j;
        }
        ++j;
        i = j;
    }
    cout << a[index] << endl;
}