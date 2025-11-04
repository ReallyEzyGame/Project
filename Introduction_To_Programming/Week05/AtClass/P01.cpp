#include <stdio.h>
#include <string.h>
// STUDENT'S ID: 24120409
// FULLNAME: Le Thanh Phong
// CLASS: 25CTT1B/24CTT3

// Febuary may have 29 days in the leap year
// we will check by using leapYear function
short days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct Date
{
    int day = 1, month = 1, year = 1970;
};

int abs(int val)
{
    return val >= 0 ? val : -val;
}

// Converte between Date <--> Number
bool is_leap_year(const int);
long long date_to_number(const Date);
Date number_to_date(const long long);

int compare_2_date(const Date, const Date);
Date find_tomorrow(const Date);
Date find_yesteday(const Date);
Date increase_by_k(const Date, const int k);
Date decrease_by_k(const Date, const int k);
int distance_with_new_year(const Date);
int distance_with_new_year_1970(const Date);
int distance_between_2_date(const Date, const Date);
void find_date_of_week(const Date);

void list()
{
    printf("--------------------- MENU CHOICE ----------------------\n");
    printf("1. Compare 2 Dates\n");
    printf("2. Find tomorrow: increase a date by 1 day\n");
    printf("3. Find yesterday: decrease a date by 1 day\n");
    printf("4. Increase a date by k day\n");
    printf("5. Decrease a date by k day\n");
    printf("6. Compute the distance between input date vs 1/1/same year\n");
    printf("7. Compute the distance between input date vs 1/1/1970\n");
    printf("8. Compute the distance between 2 Dates\n");
    printf("9. Find the date of week of the input\n");
}
bool choice_list(int choice)
{
    if (choice < 1 || choice > 9)
    {
        printf("Process to Shutdown\nGoodbye\n");
        return false;
    }

    Date date1, date2;
    int k = 0;
    printf("Input Date 1: ");
    scanf_s("%d %d %d", &date1.day, &date1.month, &date1.year);

    switch (choice)
    {
    case 1:
    {
        printf("Input Date 2: ");
        scanf_s("%d %d %d", &date2.day, &date2.month, &date2.year);
        int compare = compare_2_date(date1, date2);

        if (compare < 0)
        {
            printf("Date 1 < Date 2");
        }
        else if (compare == 0)
        {
            printf("Date 1 == Date 2");
        }
        else
        {
            printf("Date 1 > Date 2");
        }
        break;
    }
    case 2:
    {
        date2 = find_tomorrow(date1);
        printf("The Day after is: %d/%d/%d", date2.day, date2.month, date2.year);
        break;
    }
    case 3:
    {
        date2 = find_yesteday(date1);
        printf("The Day Before is: %d/%d/%d", date2.day, date2.month, date2.year);
        break;
    }
    case 4:
    {
        printf("Input K: ");
        scanf_s("%d", &k);

        date2 = increase_by_k(date1, k);
        printf("The Date after %d Day: %d/%d/%d", k, date2.day, date2.month, date2.year);
        break;
    }
    case 5:
    {
        printf("Input K: ");
        scanf_s("%d", &k);

        date2 = decrease_by_k(date1, k);
        printf("The Date before %d Day: %d/%d/%d", k, date2.day, date2.month, date2.year);
        break;
    }
    case 6:
    {
        printf("The Distance from New Year: %d", distance_with_new_year(date1));
        break;
    }
    case 7:
    {
        printf("The Distance from 1/1/1970: %d", distance_with_new_year_1970(date1));
        break;
    }
    case 8:
    {
        printf("Input Date 2: ");
        scanf_s("%d %d %d", &date2.day, &date2.month, &date2.year);

        printf("The Distance between 2 Dates: %d", distance_between_2_date(date1, date2));
        break;
    }
    case 9:
    {
        printf("The Date of the Week is: ");
        find_date_of_week(date1);
        printf(", %d/%d/%d", date1.day, date1.month, date1.year);
        break;
    }
    default:
    {
        printf("Process to Shutdown\nGoodbye\n");
        return false;
    }
    }
    return true;
}
int main()
{
    int choice;
    list();
    do
    {
        printf("\n");
        printf("Input Choice: ");
        scanf_s("%d", &choice);

    } while (choice_list(choice));
}

bool is_leap_year(const int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
long long date_to_number(const Date date)
{
    long long total = date.day;

    // find the total of the day in year field
    for (int y = 1; y < date.year; ++y)
    {
        total += 365 + is_leap_year(y);
    }
    // find total of the day in month field
    for (short m = 1; m < date.month; ++m)
    {
        total += days_in_month[m - 1] + (m == 2 && is_leap_year(date.year));
    }

    return total;
}
Date number_to_date(const long long number)
{
    int day = number, month = 1, year = 1;

    // Find the year
    while (day > 365 + is_leap_year(year))
    {
        day -= 365 + is_leap_year(year);
        year++;
    }
    // Find the Month
    while (day > days_in_month[month - 1] + (month == 2 && is_leap_year(year)))
    {
        day -= days_in_month[month - 1] + (month == 2 && is_leap_year(year));
        month++;
        if (month == 13)
        {
            month = 1;
            year++;
        }
    }

    return Date{day, month, year};
}

void find_date_of_week(const Date date)
{
    long long number_date = date_to_number(date);

    short date_of_week = (number_date + 6) % 7 + 1;

    switch (date_of_week)
    {
    case 1:
        printf("Monday");
        break;
    case 2:
        printf("Tuesday");
        break;
    case 3:
        printf("Wednesday");
        break;
    case 4:
        printf("Thursday");
        break;
    case 5:
        printf("Friday");
        break;
    case 6:
        printf("Saturday");
        break;
    case 7:
        printf("Sunday");
        break;
    }
}

int compare_2_date(const Date date1, const Date date2)
{
    long long number_date_1 = date_to_number(date1);
    long long number_date_2 = date_to_number(date2);

    if (number_date_1 < number_date_2)
    {
        return -1;
    }
    else if (number_date_1 == number_date_2)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int distance_with_new_year(const Date date)
{
    return date_to_number(date) - date_to_number(Date{1, 1, date.year});
}
int distance_with_new_year_1970(const Date date)
{
    return abs(date_to_number(date) - date_to_number(Date{1, 1, 1970}));
}
int distance_between_2_date(const Date date1, const Date date2)
{
    long long number_date_1 = date_to_number(date1);
    long long number_date_2 = date_to_number(date2);

    return abs(number_date_1 - number_date_2);
}

Date find_yesteday(const Date date)
{
    long long number_date = date_to_number(date) - 1;
    return number_to_date(number_date);
}
Date find_tomorrow(const Date date)
{
    long long number_date = date_to_number(date) + 1;
    return number_to_date(number_date);
}
Date increase_by_k(const Date date, const int k)
{
    long long number_date = date_to_number(date) + k;
    return number_to_date(number_date);
}
Date decrease_by_k(const Date date, const int k)
{
    long long number_date = date_to_number(date) - k;
    return number_to_date(number_date);
}