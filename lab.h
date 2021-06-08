#ifndef lab_h
#define lab_h

#include <iostream> 
#include <stdint.h> 
#include <string>

class Time
{
private:

    // Date stored in uint64_t format (second since 0-1-1 0:0:0 up to 584554049253-10-8 7:0:15)

    uint64_t unixtime;
public:

    /*                      Set Functions
     * Function that set date and time in uint64_t format with uint64_t number
     * Function that set date and time in uint64_t format with string value 
     * Function that set year in uint64_t format using indict and 2 other usless and squalid variables
     * Function that set year in uint64_t format with stupid year format 
     * Function that set date and time in uint64_t format using date and time in unixtime format 
     * Function that set date and time in uint64_t format using date and time in filetime format
     * Function that set date and time in uint64_t format with date and time in format: (DAY-MONTH-YEAR HOUR:MINUTE:SECOND)
     * Function that set date in uint64_t format with date in format: (DAY-MONTH-YEAR)
     * Function that set time in uint64_t format with time in format: (HOUR:MINUTE:SECOND)
     * Function that set year in uint64_t format
     * Function that set month in unsigned int format
     * Function that set day in unsigned int format
     * Function that set hour in unsigned int format
     * Function that set minute in unsigned int format
     * Function that set second in unsigned int format
     */

    void setUnix64Time(uint64_t u64_time);
    void setStringTime(std::string str_time);
    void setBullshitTime(int indict, int solar_shit, int lunar_shit);
    void setBullshitYear(uint64_t stupid_year);
    void setUnixTime(uint32_t u_time);
    void setFileTime(uint64_t filetime);
    void setFull(unsigned int day, unsigned int month, uint64_t year, unsigned int hour, unsigned int minute, unsigned int second);
    void setDate(unsigned int day, unsigned int month, uint64_t year);
    void setTime(unsigned int hour, unsigned int minute, unsigned int second);
    void setYear(uint64_t year);
    void setMonth(unsigned int month);
    void setDay(unsigned int day);
    void setHour(unsigned int hour);
    void setMinute(unsigned int minute);
    void setSecond(unsigned int second);
    
    /*                      Get Functions              
     * Function that return date in uint64_t format
     * Function that return date in string format
     * Function that return link to array with indicts of stupid time 
     * Function that return year in shabby year
     * Function that return unixtime
     * Function that return filetime 
     * Function that return link to array with date and time 
     * Function that return year
     * Function that return month 
     * Function that return hour
     * Function that return minute
     * Function that return second
     */

    uint64_t    getUnix64Time()     const;
    std::string getStringTime()     const;
    int *       getBullshitIndict() const;
    uint64_t    getBullshitYear()   const;
    uint64_t    getUnixTime()       const;
    uint64_t    getFileTime()       const;
    uint64_t *  getFull()           const;
    uint64_t    getYear()           const;
    int         getMonth()          const;
    int         getDay()            const;
    int         getHour()           const;
    int         getMinute()         const;
    int         getSecond()         const;
    
    /*                      Constructors
     * Default constructor 
     * Constructor that set date and time in unixtime format 
     * Constructor that set date and time in uint64_t format 
     * Constructor that set date and time in uint64_t format with date and time in format: (DAY-MONTH-YEAR HOUR:MINUTE:SECOND)
     * Destructor 
     * Copy constructor
     */
	Time();
    Time(uint32_t unixtime32);
    Time(uint64_t unixtime64);
    Time(unsigned int day, unsigned int month, uint64_t year, unsigned int hour, unsigned int minute, unsigned int second);
   ~Time();
    Time(const Time &time1);

    /*                      Input/Output operator overload 
     * Formated output overload 
     * Formated input overload
     */ 
    friend std::ostream& operator<< (std::ostream &out, const Time& right);
    friend std::istream& operator>> (std::istream &in, Time& right);
};

/*                      Operator overload 
 * Other operator overload
 */ 

Time operator +(const Time& left, const Time& right);
Time operator -(const Time& left, const Time& right);

bool operator ==(const Time& left, const Time& right);
bool operator <=(const Time& left, const Time& right);
bool operator >=(const Time& left, const Time& right);
bool operator !=(const Time& left, const Time& right);
bool operator <(const Time& left, const Time& right);
bool operator >(const Time& left, const Time& right);

#endif 