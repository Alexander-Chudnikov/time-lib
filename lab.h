#ifndef lab_h
#define lab_h

class Time
{
private:
    uint64_t unixtime;
    uint64_t leap_years;
public:
    
    void setUnix64Time(uint64_t u64_time);
    void setUnixTime(uint64_t u_time);
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
    
    uint64_t getUnix64Time() const;
    uint64_t getUnixTime()   const;
    uint64_t getFileTime()   const;
    uint64_t getFull()       const;
    uint64_t getYear()       const;
    int      getMonth()      const;
    int      getDay()        const;
    int      getHour()       const;
    int      getMinute()     const;
    int      getSecond()     const;
    
	Time();
    Time(uint64_t unixtime);
   ~Time();
    Time(const Time &time1);

    friend std::ostream& operator<< (std::ostream &out, const Time& right);
    friend std::istream& operator>> (std::istream &in, Time& right);

    friend Time operator +(const Time& left, const Time& right);
    friend Time operator -(const Time& left, const Time& right);
    friend Time& operator +=(const Time& left, const Time& right);
    friend Time& operator -=(const Time& left, const Time& right);

    friend bool operator ==(const Time& left, const Time& right);
    friend bool operator <=(const Time& left, const Time& right);
    friend bool operator >=(const Time& left, const Time& right);
    friend bool operator !=(const Time& left, const Time& right);
    friend bool operator <(const Time& left, const Time& right);
    friend bool operator >(const Time& left, const Time& right);

};

#endif 

// tar -cJvf cw-[n].txz Matrix.h Matrix.cpp
