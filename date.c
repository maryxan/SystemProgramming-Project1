#include "date.h"

time_t to_seconds(char *date)
{

    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));

    time_t t;
    strptime(date,"%d-%m-%Y",&tm);
    t = mktime(&tm);

    return t;
}

int check_dates(char*date1, char* date2){

    time_t d1 , d2;

    d1 = to_seconds(date1);
    d2 = to_seconds(date2);

    if (d1 < d2 || d1 == d2){

        return 0;

        } else
        {
            if(d2 < 0){

                return 0;

            }
            else return 1;
        }

}