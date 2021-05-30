#include "lab.h"

#include <iostream>
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


void Time::
    setUnix64Time(uint64_t u64_time)
    {
        this->unixtime = u64_time;
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
void Time::
    setFull(unsigned int day = 1, unsigned int month = 1, uint64_t year = 0, unsigned int hour = 0, unsigned int minute = 0, unsigned int second = 0)
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
        this->setFull(day, month, year);
        return;
    }
void Time::
    setTime(unsigned int hour, unsigned int minute, unsigned int second)
    {
        this->setFull(0, 0, 0, hour, minute, second);
        return;
    }
void Time::
    setYear(uint64_t year)
    {
        this->setFull(0, 0, year);
        return;
    }
void Time::
    setMonth(unsigned int month)
    {
        this->setFull(0, month);
        return;
    }
void Time::
    setDay(unsigned int day)
    {
        this->setFull(day);
        return;
    }
void Time::
    setHour(unsigned int hour)
    {
        this->setFull(0, 0, 0, hour);
        return;
    }
void Time::
    setMinute(unsigned int minute)
    {
        this->setFull(0, 0, 0, 0, minute);
        return;
    }
void Time::
    setSecond(unsigned int second)
    {
        this->setFull(0, 0, 0, 0, 0, second);
        return;
    }
uint64_t Time::
    getUnix64Time() const
    {
        return this->unixtime;
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
	out << std::setw(4) << std::setfill('0') << time[0] << '-' << std::setw(2) << std::setfill('0') << time[1] << '-' << time[2] << "T" << time[3] << ":" << time[4] << ":" << time[5] << "+00:00" << std::endl;
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
    Time(unsigned int day, unsigned int month, uint64_t year, unsigned int hour, unsigned int minute, unsigned int second)
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
    std::cout << time;
}


