/**********
Problem Statement:  https://www.hackerrank.com/challenges/extra-long-factorials/problem
Difficulty:         Medium
Problem Author:     vatsalchanana (https://www.hackerrank.com/profile/vatsalchanana)
Soluion Author:     menisorfeas  (https://www.hackerrank.com/profile/menisorfeas)
**********/

#include <bits/stdc++.h>

using namespace std;

class BigInt{
    public:
    vector<int> number;

    BigInt(int n){
        int i=0;
        while (n>0){
            if (i < number.size()) number[i] = n%10;
            else number.push_back(n%10);
            n = n/10;
            i++;
        }
    }

    BigInt(){    
    }

    BigInt operator+(const BigInt& b) {
        BigInt result;
        int maximum = max(b.number.size(), this->number.size());
        int plus=0;
        int sum=0;
        int i;
        for(i=0; i<maximum; i++){
            if (i<b.number.size() && i<this->number.size()) sum = b.number[i] + this->number[i] + plus;
            else if(i<b.number.size()) sum = b.number[i] + plus;
            else sum = this->number[i] + plus;
            plus = sum/10;
            if (i < result.number.size()) result.number[i] = sum%10;
            else result.number.push_back(sum%10);      
        }
        if (i < result.number.size()) result.number[i] = plus;
        else result.number.push_back(plus); 
        return result;
    }

    BigInt operator*(const int& times) {
        BigInt result;
        for (int i=0; i<times; i++){
            result = result + *this;
        }
        return result;
    }
    
};

ostream& operator<<(ostream& os, const BigInt& x){
    bool flag = true;
    for(int i=x.number.size()-1; i >=0; i--){
        if(flag && x.number[i] == 0) continue;
        else{
            os << x.number[i];
            flag = false;
        }
    }
    return os;
};

void extraLongFactorials(int n) {
    BigInt x(1);
    for (int i=n; i > 0; i--){
        x = x * i;
    }
    cout << x;
}

int main()
{
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    extraLongFactorials(n);

    return 0;
}
