//
// Created by 86176 on 2022/3/17 0017.
//

#ifndef LINKLIST_LIANSHI_ONLY01_CPP_BANK_H
#define LINKLIST_LIANSHI_ONLY01_CPP_BANK_H

class BBank;
class GBank;
class CBank {
private:
    int balance;
public:
    friend int total(CBank f1, BBank f2,GBank f3);
    CBank(int x);
};
class BBank{
private:
    int balance;
public:
    BBank(int x);
    friend int total(CBank f1, BBank f2,GBank f3);
};
class GBank{
private:
    int balance;
public:
    GBank(int x);
    friend int total(CBank f1, BBank f2,GBank f3);
};
int total(CBank f1, BBank f2,GBank f3)
{
    int total = f1.balance + f2.balance + f3.balance;
    return total;
}

#endif //LINKLIST_LIANSHI_ONLY01_CPP_BANK_H
