#include "lab.h"

#include <iostream>
#include <string>
#include <iomanip>

#define UNIX_TIME_OFFSET        62167132800LL
#define UNIX_TIME_64_MAX_YEAR   584554049253LL
#define UNIX_TIME_MAX           2147483647
#define UNIX_TIME_DAY           86400
#define UNIX_TIME_HOUR          3600
#define UNIX_TIME_MINUTE        60
#define UNIX_TIME_MONTH_31      2678400
#define UNIX_TIME_MONTH_30      2592000
#define UNIX_TIME_MONTH_28      2419200
#define UNIX_TIME_YEAR          31536000LL
#define WINDOWS_TICK            10000000
#define UNIX_EPOCH              11644473600LL
#define WINDOWS_MAX_TIME        9223149887999990000LL
#define REMINDER_M_CONSTANT_15  532
#define REMINDER_M_CONSTANT_28  285
#define REMINDER_M_CONSTANT_19  420
#define REMINDER_M_CONSTANT     7980
#define NOT_FOUND               18446744073709551615ULL
/*
inline int euclidGCD(int num_1, int num_2) 
{
    if (num_1 == num_2) 
    {
        return num_1;
    }
    if (num_1 > num_2) {
        int temp = num_1;
        num_1 = num_2;
        num_2 = temp;
    }
    return euclidGCD(num_1, num_2 - num_1);
} 
*/
/*  
 * 
 */

/*                   Chinese theorem of reminders with predetermend values 
 * y_* are storing values that are nesseesary for acquiring certan reminder
 * rem_* are values, that store reminders, from wich later y_* will be calculted
 * REMINDER_M_CONSTANT* are predetermined values, that can be calculeted by multiplying two other dividers
 */ 

inline int remindersToNum(int rem_1, int rem_2, int rem_3)
{
    int y_1 = 1;
    int y_2 = 1;
    int y_3 = 1;
    while ((REMINDER_M_CONSTANT_15 * y_1 % 15 != 1) and (y_1 < 15))
    {
        ++y_1;
    }
    while ((REMINDER_M_CONSTANT_28 * y_2 % 28 != 1) and (y_2 < 28))
    {
        ++y_2;
    }
    while ((REMINDER_M_CONSTANT_19 * y_3 % 19 != 1) and (y_3 < 19))
    {
        ++y_3;
    }
    return ((REMINDER_M_CONSTANT_15 * y_1 * rem_1)+(REMINDER_M_CONSTANT_28 * y_2 * rem_2)+(REMINDER_M_CONSTANT_19 * y_3 * rem_3)) % REMINDER_M_CONSTANT;
}

/*                   Function that check is string contains only numbers 
 */ 

inline bool isNum(std::string  const& string){
    return string.find_first_not_of("0123456789") == std::string::npos;
}

/*                   String to uint64_t convertion 
 * Simple coversion algorythm, that is based on string to char conversion with further byte wrighting to result;
 */ 

inline uint64_t stringToUint64_t(std::string const& value) 
{
    if (isNum(value))
    {
        uint64_t result = 0;

        char const* char_v = value.c_str();
        char const* char_q = char_v + value.size();
        while (char_v < char_q) 
        {
            result = (result << 1) + (result << 3) + *(char_v++) - '0';
        }
        return result;
    }
    else 
    {
        return 0;
    }
}

/*                   String to unsingned int convertion 
 * String converted to unsigned long, than checked to be in range of unsigned int
 */

inline unsigned int stringToUint( std::string const& string)
{
    if (isNum(string))
    {
        unsigned long lresult = stoul(string, 0, 10);
        unsigned int result = lresult;
        if (result != lresult) 
        {
            std::cerr << result << " is out of range" << std::endl;
        }
        return result;
    }
    else 
    {
        return 0;
    }
}

/*                  This function checks if inputed indicts are coorrect
 * After check, it will get year from remindersToNum function and pass it to setBullshitYear
 */

void Time::
    setBullshitTime(int indict, int solar_shit, int lunar_shit)
    {
        if ((indict > 15) or (indict < 1) or (solar_shit > 28) or (solar_shit < 1) or (lunar_shit > 19) or (lunar_shit < 1))
        {
            if ((indict > 15) or (indict < 1))
            {
                std::cerr << "Indict is out of range" << std::endl;
            }
            if ((solar_shit > 28) or (solar_shit < 1))
            {
                std::cerr << "Solar circle is out of range" << std::endl;
            }
            if ((lunar_shit > 19) or (lunar_shit < 1))
            {
                std::cerr << "Lunar circle is out of range" << std::endl;
            }
            this->unixtime = 0;
        }
        else 
        {
            this->setBullshitYear(remindersToNum(indict, solar_shit, lunar_shit));
        }
        return;
    }
void Time::
    setUnix64Time(uint64_t u64_time)
    {
        this->unixtime = u64_time;
        return;
    }

/*                  This function parse input string
 * 
 */

void Time::
    setStringTime(std::string str_time)
    {
        std::string delimiter_1 = "T";
        std::string delimiter_2 = "-";
        std::string delimiter_3 = ":";
        std::string delimiter_4 = "+";
        std::string delimiter_5 = "-";
        std::string str_date;
        std::string str_day;
        std::string str_month;
        std::string str_year;
        std::string str_hour;
        std::string str_minute;
        std::string str_second;
        std::string str_g_hour;

        if(str_time.find(delimiter_1) != NOT_FOUND)
        {
            str_date = str_time.substr(0, str_time.find(delimiter_1));
            str_time.erase(0, str_time.find(delimiter_1) + delimiter_1.length());
        }
        else
        {
            std::cerr << "Invalid string format given" << std::endl;
            this->unixtime = 0;
            return;
        }

        if(str_date.find(delimiter_2) != NOT_FOUND)
        {
            str_year = str_date.substr(0, str_date.find(delimiter_2));
            str_date.erase(0, str_date.find(delimiter_2) + delimiter_2.length());
        }
        else
        {
            std::cerr << "Invalid string format given" << std::endl;
            this->unixtime = 0;
            return;
        }

        if(str_date.find(delimiter_2) != NOT_FOUND)
        {
            str_month = str_date.substr(0, str_date.find(delimiter_2));
            str_date.erase(0, str_date.find(delimiter_2) + delimiter_2.length());
            str_day = str_date;
        }
        else
        {
            std::cerr << "Invalid string format given" << std::endl;
            this->unixtime = 0;
            return;
        }

        if(str_time.find(delimiter_3) != NOT_FOUND)
        {
            str_hour = str_time.substr(0, str_time.find(delimiter_3));
            str_time.erase(0, str_time.find(delimiter_3) + delimiter_3.length());
        }
        else
        {
            std::cerr << "Invalid string format given" << std::endl;
            this->unixtime = 0;
            return;
        }

        if(str_time.find(delimiter_3) != NOT_FOUND)
        {
            str_minute = str_time.substr(0, str_time.find(delimiter_3));
            str_time.erase(0, str_time.find(delimiter_3) + delimiter_3.length());
        }
        else
        {
            std::cerr << "Invalid string format given" << std::endl;
            this->unixtime = 0;
            return;
        }

        if(str_time.find(delimiter_4) != NOT_FOUND or str_time.find(delimiter_5) != NOT_FOUND)
        {
            if (str_time[2] == '+')
            {
                str_second = str_time.substr(0, str_time.find(delimiter_4));
                str_time.erase(0, str_time.find(delimiter_4) + delimiter_4.length());
            }
            else
            {
                str_second = str_time.substr(0, str_time.find(delimiter_5));
                str_time.erase(0, str_time.find(delimiter_5) + delimiter_5.length());
            }
            if(str_time.find(delimiter_3) != NOT_FOUND)
            {
                str_g_hour = str_time.substr(0, str_time.find(delimiter_3));
                str_time.erase(0, str_time.find(delimiter_3) + delimiter_3.length());
            }
            else
            {
                std::cerr << "Invalid string format given" << std::endl;
                this->unixtime = 0;
                return;
            }
        }
        else
        {
            std::cerr << "Invalid string format given" << std::endl;
            this->unixtime = 0;
            return;
        }

        /*           TODO
         * • Add GTM time shift 
         * • Fix number length 0 error 
         * • Remove debug output
         * • Clean this part 
         * • Make single error handler
         * • Complete comment
         */

        std::cout << str_g_hour << " " << str_time << std::endl;

        if (isNum(str_day) && isNum(str_month) && isNum(str_year) && isNum(str_hour) && isNum(str_minute) && isNum(str_second))
        {
           this->setFull(stringToUint(str_day), stringToUint(str_month), stringToUint64_t(str_year), stringToUint(str_hour), stringToUint(str_minute), stringToUint(str_second)); 
        }
        else 
        {
            std::cerr << "Invalid string format given" << std::endl;
            this->unixtime = 0;
        }
        return;
    }
void Time::
    setUnixTime(uint32_t u_time)
    {
        this->setUnix64Time((uint64_t)(u_time + UNIX_TIME_OFFSET));
        return;
    }
void Time::
    setFileTime(uint64_t filetime)
    {
        this->setUnixTime(filetime / WINDOWS_TICK - UNIX_EPOCH);
        return;
    }

/*                  This function convert date and time into seconds
 * After simple user input validation, function determinies if year is a leap year 
 * Then goes calculation of days in month with correction for leap years and amount of leap years since start of an epoch
 */

void Time::
    setFull(unsigned int day , unsigned int month , uint64_t year = 0, unsigned int hour = 0, unsigned int minute = 0, unsigned int second = 0)
    {
        if ((year >= 0 && year < (UNIX_TIME_64_MAX_YEAR + 1)) && (month > 0 && month <= 12) && (day > 0 && day <= 31) && (hour >= 0 && hour <= 24) && (minute >= 0 && minute <= 60) && (second >= 0 && second <= 60))
        {
            if ((year == UNIX_TIME_64_MAX_YEAR) && (month > 10) && (day > 8) && (hour > 7) && (second > 15) && (minute > 0))
            {
                std::cerr << "Date is out of range, date must be smaller than 584554049253-10-8T07:00:15+00:00" << std::endl;
                this->unixtime = 0;
                return;
            }
            else
            {
                bool leap = 0;
                if (year % 4 == 0)
                {
                    if (year % 100 == 0)
                    {
                        leap = 0;
                        if (year % 400 == 0)
                        {
                            leap = 1;
                        }
                    }
                    
                }
                if (month <= 12){
                    if (month == 2)
                    {
                        if (leap)
                        {
                            if (day > 29)
                            {
                                std::cerr << "The month you entered: " << month << " doesn't have " << day << " days in it." << std::endl;
                                this->unixtime = 0;
                                return; 
                            }
                        }
                        else 
                        {
                            if (day > 28)
                            {
                                std::cerr << "The month you entered: " << month << " doesn't have " << day << " days in it." << std::endl;
                                this->unixtime = 0;
                                return; 
                            }
                        }
                    }
                    else if (month < 8)
                    {
                        if (month % 2 != 0)
                        {
                            if (day > 31)
                            {
                                std::cerr << "The month you entered: " << month << " doesn't have " << day << " days in it." << std::endl;
                                this->unixtime = 0;
                                return;                        
                            }
                        }
                        else 
                        {
                            if (day > 30)
                            {
                                std::cerr << "The month you entered: " << month << " doesn't have " << day << " days in it." << std::endl;
                                this->unixtime = 0;
                                return;                        
                            }
                        }
                    }
                    else 
                    {
                        if (month % 2 == 0)
                        {
                            if (day > 31)
                            {
                                std::cerr << "The month you entered: " << month << " doesn't have " << day << " days in it." << std::endl;
                                this->unixtime = 0;
                                return;                        
                            }
                        }
                        else 
                        {
                            if (day > 30)
                            {
                                std::cerr << "The month you entered: " << month << " doesn't have " << day << " days in it." << std::endl;
                                this->unixtime = 0;
                                return;                        
                            }
                        }
                    }
                }
                else 
                {
                    std::cerr << "The month you entered: " << month << " doesn't exist " << std::endl;
                    this->unixtime = 0;
                    return;   
                }

                uint64_t leap_years = (year / 4) - (year / 100) + (year / 400);
                this->unixtime = ((leap_years * (UNIX_TIME_YEAR + UNIX_TIME_DAY)) + ((year - leap_years) * UNIX_TIME_YEAR));

                for (int loop = (month - 1); loop > 0; --loop)
                {
                    if (loop == 2)
                    {
                        if (leap)
                        {
                            this->unixtime += UNIX_TIME_MONTH_28 + UNIX_TIME_DAY;
                        }
                        else 
                        {
                            this->unixtime += UNIX_TIME_MONTH_28;
                        }
                    }
                    else if (loop < 8)
                    {
                        if (loop % 2 != 0)
                        {
                            this->unixtime += UNIX_TIME_MONTH_31;
                        }
                        else 
                        {
                            this->unixtime += UNIX_TIME_MONTH_30;
                        }
                    }
                    else 
                    {
                        if (loop % 2 == 0)
                        {
                            this->unixtime += UNIX_TIME_MONTH_31;
                        }
                        else 
                        {
                            this->unixtime += UNIX_TIME_MONTH_30;
                        }
                    }
                }
                --day;
                this->unixtime += (second + (minute * UNIX_TIME_MINUTE) + (hour * UNIX_TIME_HOUR) + (day * UNIX_TIME_DAY));
                return;
            }
        }
        std::cerr << "Date is out of range, you have entered unexisting date" << std::endl;
        this->unixtime = 0;
    }
void Time::
    setDate(unsigned int day, unsigned int month, uint64_t year)
    {
        this->setFull(day, month, year, this->getHour(), this->getMinute(), this->getSecond());
        return;
    }
void Time::
    setTime(unsigned int hour, unsigned int minute, unsigned int second)
    {
        this->setFull(this->getDay(), this->getMonth(), this->getYear(), hour, minute, second);
        return;
    }
void Time::
    setBullshitYear(uint64_t stupid_year)
    {
        if (stupid_year - 5508 <= 2470){
            std::cerr << (stupid_year - 5508) << std::endl;
            this->setFull(this->getDay(), this->getMonth(), (stupid_year - 5508), this->getHour(), this->getMinute(), this->getSecond());
        }
        else
        {
            std::cerr << "Year is out of range" << std::endl;
            this->unixtime = 0;
        }
    }
void Time::
    setYear(uint64_t year)
    {
        this->setFull(this->getDay(), this->getMonth(), year, this->getHour(), this->getMinute(), this->getSecond());
        return;
    }
void Time::
    setMonth(unsigned int month)
    {
        this->setFull(this->getDay(), month, this->getYear(), this->getHour(), this->getMinute(), this->getSecond());
        return;
    }
void Time::
    setDay(unsigned int day)
    {
        this->setFull(day, this->getMonth(), this->getYear(), this->getHour(), this->getMinute(), this->getSecond());
        return;
    }
void Time::
    setHour(unsigned int hour)
    {
        this->setFull(this->getDay(), this->getMonth(), this->getYear(), hour, this->getMinute(), this->getSecond());
        return;
    }
void Time::
    setMinute(unsigned int minute)
    {
        this->setFull(this->getDay(), this->getMonth(), this->getYear(), this->getHour(), minute, this->getSecond());
        return;
    }
void Time::
    setSecond(unsigned int second)
    {
        this->setFull(this->getDay(), this->getMonth(), this->getYear(), this->getHour(), this->getMinute(), second);
        return;
    }

uint64_t Time::
    getUnix64Time() const
    {
        return this->unixtime;
    }
std::string Time::
    getStringTime() const
    {
        uint64_t *time = this->getFull();
        std::string out = std::to_string(time[0]);
        out.append("-");
        out.append(std::to_string(time[1]));
        out.append("-");
        out.append(std::to_string(time[2]));
        out.append("T");
        out.append(std::to_string(time[3]));
        out.append(":");
        out.append(std::to_string(time[4]));
        out.append(":");
        out.append(std::to_string(time[5]));
        out.append("+00:00");
        return out;
    }
int * Time::
    getBullshitIndict() const
    {
        static int indicts[3];
        indicts[0] = this->getBullshitYear() % 15;
        indicts[1] = this->getBullshitYear() % 28;
        indicts[2] = this->getBullshitYear() % 19;
        return indicts;
    }
uint64_t Time::
    getBullshitYear() const
    {
        if (584554049253LL - this->getYear() > 5508)
        {
            return (this->getYear() + 5508);
        }
        else 
        {
            std::cerr << "Year is out of range" << std::endl;
            return 0;
        }
    }
uint64_t Time::
    getUnixTime() const
    {
        if ((this->unixtime - UNIX_TIME_OFFSET) > UNIX_TIME_MAX)
        {
            return UNIX_TIME_MAX;
        }
        else 
        {
            return (this->unixtime - UNIX_TIME_OFFSET);
        }
    }
uint64_t Time::
    getFileTime() const
    {
        if ((this->unixtime * WINDOWS_TICK + UNIX_EPOCH) > WINDOWS_MAX_TIME)
        {
            return WINDOWS_MAX_TIME;
        }
        else 
        {
            return (this->unixtime * WINDOWS_TICK + UNIX_EPOCH);
        }
    }

/*                  This function returns date and time in array
 * Function determines if current year is leap, than goes prediction of unixtime and leap years after what
 * Predicted unixtime being compared with original one, then years being adjusted so they are not bigger than 
 * Original year, at the end goes month, days, hours and minutes calculation
 */

uint64_t * Time:: 
    getFull() const
    {
        static uint64_t time_arr[6];
        uint64_t seconds = this->unixtime;
        bool leap = 0;
        int loop = 0;
        int month = 1; 
        int day = 1;
        int hour = 0;
        int minutes = 0;

        if (seconds % 4 == 0)
        {
            if (seconds % 100 == 0)
            {
                leap = 0;
                if (seconds % 400 == 0)
                {
                   leap = 1;
                }
            }
            
        }

        uint64_t pre_years = this->unixtime / 365.251 / UNIX_TIME_DAY;

        uint64_t leap_years = (pre_years / 4) - (pre_years / 100) + (pre_years / 400); 

        uint64_t true_year = (((this->unixtime - (leap_years * (UNIX_TIME_YEAR + UNIX_TIME_DAY))) / (UNIX_TIME_YEAR)) + leap_years);

        uint64_t leap_years_pre = (true_year / 4) - (true_year / 100) + (true_year / 400);

        uint64_t unixtime_pre = ((leap_years_pre * (UNIX_TIME_YEAR + UNIX_TIME_DAY)) + ((true_year - leap_years_pre) * UNIX_TIME_YEAR));

        while (unixtime_pre > this->unixtime)
        {
            true_year-=1;
            leap_years_pre = (true_year / 4) - (true_year / 100) + (true_year / 400);
            unixtime_pre = ((leap_years_pre * (UNIX_TIME_YEAR + UNIX_TIME_DAY)) + ((true_year - leap_years_pre) * UNIX_TIME_YEAR));
        }

        time_arr[0] = true_year;
        leap_years_pre = (true_year / 4) - (true_year / 100) + (true_year / 400);
        seconds -= ((leap_years_pre * (UNIX_TIME_YEAR + UNIX_TIME_DAY)) + ((true_year - leap_years_pre) * UNIX_TIME_YEAR));

        while (loop <= 12)
        {
            ++loop;
            if (loop == 2)
            {
                if (leap)
                {
                    if(seconds < (UNIX_TIME_MONTH_28 + UNIX_TIME_DAY))
                    {
                        month = loop;
                        break;
                    }
                    seconds -= (UNIX_TIME_MONTH_28 + UNIX_TIME_DAY);
                }
                else 
                {
                    if(seconds < UNIX_TIME_MONTH_28)
                    {
                        month = loop;
                        break;
                    }
                    seconds -= UNIX_TIME_MONTH_28;
                }
            }
            else if (loop < 8)
            {
                if (loop % 2 != 0)
                {
                    if(seconds < UNIX_TIME_MONTH_31)
                    {
                        month = loop;
                        break;
                    }
                    seconds -= UNIX_TIME_MONTH_31;
                }
                else 
                {
                    if(seconds < UNIX_TIME_MONTH_30)
                    {
                        month = loop;
                        break;
                    }
                    seconds -= UNIX_TIME_MONTH_30;
                }
            }
            else
            {
                if (loop % 2 == 0)
                {
                    if(seconds < UNIX_TIME_MONTH_31)
                    {
                        month = loop;
                        break;
                    }
                    seconds -= UNIX_TIME_MONTH_31;
                }
                else 
                {
                    if(seconds < UNIX_TIME_MONTH_30)
                    {
                        month = loop;
                        break;
                    }
                    seconds -= UNIX_TIME_MONTH_30;
                }
            }
            month = loop;
        }

        while (seconds >= UNIX_TIME_DAY)
        {
            ++day;
            seconds -= UNIX_TIME_DAY;
        }
        while (seconds >= UNIX_TIME_HOUR)
        {
            ++hour;
            seconds -= UNIX_TIME_HOUR;
        }
        while (seconds >= 60)
        {
            ++minutes;
            seconds -= 60;
        }
        time_arr[1] = month;
        time_arr[2] = day;
        time_arr[3] = hour;
        time_arr[4] = minutes;
        time_arr[5] = seconds;
        return time_arr;
    }
uint64_t Time::
    getYear() const 
    {
        uint64_t *time = this->getFull();
        return time[0];
    }
int Time::
    getMonth() const 
    {
        uint64_t *time = this->getFull();
        return time[1];
    }
int Time::
    getDay() const 
    {
        uint64_t *time = this->getFull();
        return time[2];
    }
int Time::
    getHour() const 
    {
        uint64_t *time = this->getFull();
        return time[3];
    }
int Time::
    getMinute() const 
    {
        uint64_t *time = this->getFull();
        return time[4];
    }
int Time::
    getSecond() const 
    {
        uint64_t *time = this->getFull();
        return time[5];
    }

std::ostream& operator<< (std::ostream &out, const Time& right)
{
    uint64_t *time = right.getFull();
    out << std::setw(4) << std::setfill('0') << time[0] << '-' << std::setw(2) << std::setfill('0') << time[1] << '-' << time[2] << "T" << time[3] << ":" << time[4] << ":" << time[5] << "+00:00";
    return out;
}
std::istream& operator>> (std::istream &in, Time& right)
{
    unsigned int day = 0;
    unsigned int month = 0; 
    uint64_t year = 0;
    unsigned int hour = 0;
    unsigned int minute = 0;
    unsigned int second = 0;

    in >> day;
    in >> month;
    in >> year;
    in >> hour;
    in >> minute;
    in >> second;

    return in;
}
Time operator +(const Time& left, const Time& right) 
{
    try 
    {
        return(left.getUnix64Time() + right.getUnix64Time());
    }
    catch (...)
    {
        std::cerr << "UnixDate is out of range, UnixDate must be smaller than 18446744073709551615" << std::endl;
        return left.getUnix64Time();
    }
}
Time operator -(const Time& left, const Time& right) 
{
    try 
    {
        return (left.getUnix64Time() - right.getUnix64Time());
    }
    catch (...)
    {
        std::cerr << "UnixDate is out of range, UnixDate must be bigger than 0" << std::endl;
        return left.getUnix64Time();
    }
}
bool operator ==(const Time& left, const Time& right)
{
    return (left.getUnix64Time() == right.getUnix64Time());
}
bool operator !=(const Time& left, const Time& right)
{
    return (left.getUnix64Time() != right.getUnix64Time());
}
bool operator <=(const Time& left, const Time& right)
{
    return (left.getUnix64Time() <= right.getUnix64Time());
}
bool operator >=(const Time& left, const Time& right)
{
    return (left.getUnix64Time() >= right.getUnix64Time());
}
bool operator >(const Time& left, const Time& right)
{
    return (left.getUnix64Time() > right.getUnix64Time());
}
bool operator <(const Time& left, const Time& right)
{
    return (left.getUnix64Time() < right.getUnix64Time());
}
Time::
    Time()
    {
        this->unixtime = 0;
    }
Time::
    Time(uint32_t unixtime32)
    {
        this->setUnixTime(unixtime32);
    }
Time::
    Time(uint64_t unixtime64)
    {
        this->unixtime = unixtime64;
    }
Time::
    Time(unsigned int day , unsigned int month , uint64_t year = 0, unsigned int hour = 0, unsigned int minute = 0, unsigned int second = 0)
    {
        this->setFull(day, month, year, hour, minute, second);
    }
Time::
    ~Time()
    {

    }
Time::
    Time(const Time &time)
    {
        this->unixtime = time.unixtime;
    }

int main()
{
    std::cout << "Some Tests:" << std::endl;
    std::cout << "Input time: 2002-10-23 22:13:55" << std::endl;

    Time time(23, 10, 2002, 22, 13, 55);
    time.setStringTime("2033-10-23T22:13:55+00:00");
    std::cout << time << std::endl;
    std::cout << time.getBullshitIndict()[0] << " "<< time.getBullshitIndict()[1] << " "<< time.getBullshitIndict()[2];
}