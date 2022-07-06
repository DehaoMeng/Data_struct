#include "Data.cpp"
void set_date(Data *A){
    int y,m,d;
    cin >> y >> m >> d;
    A->SetData(y,m,d);
}
void show_date(Data *A){
    if (A->GetYear() && A->GetMonth() && A->GetDay())
        cout << A->GetYear() << "-" << A->GetMonth() << "-" << A->GetDay() << endl;
    else if (A->GetYear() && A->GetMonth())
    {
        cout << A->GetYear() << "-" << A->GetMonth() << endl;
    }
    else if()
}
int main()
{
    Data A;
    set_date(&A);
    show_date(&A);
    return 0;
}