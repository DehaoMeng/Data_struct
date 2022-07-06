

#include "Data.h"

void Data::SetData(int y, int m, int d) {
    day = d;
    month = m;
    year = y;
}

int Data::GetYear() {
    if (year != 0 && month != 0 && day != 0)
    {
        return year;
    }
    return 0;
}

int Data::GetMonth() {
    if (year != 0 && month != 0 && day != 0)
    {
        return month;
    }
    return 0;
}

int Data::GetDay() {
    if (year != 0 && month != 0 && day != 0)
    {
        return day;
    }
    return 0;
}
