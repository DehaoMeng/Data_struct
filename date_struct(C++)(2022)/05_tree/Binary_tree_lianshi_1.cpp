/*
 * ��������������ʽ�洢
 * ɾ������㼴ɾ������������
 */
#include <iostream>
#include <string>
using namespace std;

typedef int keytype;//��������������
#define MaxSize 15
//����������ʽ�洢�ṹ
typedef struct BiTNode {
    keytype data;
    struct BiTNode *left, *right;
} Bitree;
Bitree* F = NULL;
//�������ĵݹ�����㷨
Bitree* find(Bitree* T, keytype x)
{
    if (T == NULL)
        return NULL;
    if (T->data == x)
        return T;
    else
    {
        F = T;
        if (T->data > x)
            find(T->left, x);
        else
            find(T->right, x);
    }
}
//����find��������ڵ�
Bitree* insertbst(Bitree* T, keytype key) {
    Bitree* C, * s;
    C = find(T, key);
    if (C == NULL)
    {
        s = (Bitree*)new Bitree;
        s->data = key;
        s->left = s->right = NULL;
        if (F == NULL)
            T = s;
        else if (key < F->data)
            F->left = s;
        else
            F->right = s;
    }
    return T;
}
//���ú���insertbst���ж������Ĵ���
Bitree* creatbst() {
    keytype key;
    Bitree* T = NULL;
    cin >> key;
    while (key != -1) {
        T = insertbst(T, key);
        cin >> key;
    }
    return T;
}
//������������� ���Ƿ�����
void InOrder(Bitree* bt) {
    if (bt != NULL)
    {
        InOrder(bt->left);
        cout << bt->data << " ";
        InOrder(bt->right);
    }
}
//���ú���findɾ�����
int deletebst(Bitree* T, keytype key) {
    Bitree* p, * s, * q;
    s = NULL;
    p = find(T, key);
    if (!p) {
        cout << "������" << endl;
        return 0;
    }
    if (p->left == NULL) {
        q = p;
        p = p->right;
    }
    else if (p->right == NULL) {
        q = p;
        p = p->left;
    }
    else
    {
        q = p;
        s = p->left;
        while (s->right != NULL) {
            q = s;
            s = s->right;
        }
        if (q != p)
            q->right = s->left;
        else
            q->left = s->left;
        q = s;
        p->data = s->data;
    }
    if (F == NULL) T = p;
    else if (q != s) {
        if (key < F->data)
            F->left = p;
        else F->right = p;
    }
    delete q;
    return 1;
}
int main() {
    Bitree* T;
    int x;
    T = (Bitree*) new Bitree ;
    cout << "�������У�";
    T = creatbst();
    cout << "����������������ӦΪ��";
    InOrder(T);
    cout << endl << "����Ҫɾ����������";
    cin >> x;
    while (x != T->data) {
        if (x == -1) break;
        if (T == NULL)
        {
            cout << "������Ϊ��";
            break;
        }
        deletebst(T, x);
        cout << "���ɾ����������������Ϊ��";
        InOrder(T);
        cout << endl << "����Ҫɾ����������";
        cin >> x;
    }
    return 1;
}