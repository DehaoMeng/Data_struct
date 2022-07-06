//
// Created by 86176 on 2022/6/6 0006.
//
#include <iostream>
#include <vector>
using namespace std;
const int MAXSIZE = 100;
void print(vector<int> a){
    for (int i = 0; i < a.size(); ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
}
void group_sort(vector<int> a,int gap){
        for (int i = 0; i < gap; i++) {
            for (int j =i+gap; j < a.size(); j += gap) {
                if(a[j] < a[j-gap]){
                    int temp = a[j];
                    int k = j - gap;
                    while (k >= 0 && a[k] >temp){
                        a[k+gap] = a[k];
                        k-=gap;
                    }
                    a[k+gap] = temp;
                }
            }
        }
    print(a);
}



int main(){
    vector<int> a;
    int num;
    while (cin >> num){
        a.push_back(num);
        char ch = getchar();
        if (ch == '\n')
            break;
    }
    int gap[3];
    for (int i = 0; i < 3; ++i) {
        cin >> gap[i];
        if (char ch =getchar() == '\n')
            break;
    }
    for (int i = 0; i < 3; ++i) {
        group_sort(a,gap[i]);
    }
    return 0;
}