#pragma once

#include "Macros.h"
#include <string>
#include <array>

namespace minirisk {

struct Date
{
public:
    static const unsigned first_year = 1900;
    static const unsigned last_year = 2200;
    static const unsigned n_years = last_year - first_year;

private:
    static std::string padding_dates(unsigned);

    // number of days elapsed from beginning of the year
    unsigned day_of_year() const;

    friend long operator-(const Date& d1, const Date& d2);



public:
    static const std::array<unsigned, 12> days_in_month;  // num of days in month M in a normal year
    static const std::array<unsigned, 12> leap_days_in_month;  // num of days in month M in a leap year
    static const std::array<unsigned, 12> days_ytd;      // num of days since 1-jan to 1-M in a normal year
    static const std::array<unsigned, 12> leap_days_ytd;      // num of days since 1-jan to 1-M in a leap year
    static const std::array<unsigned, n_years> days_epoch;   // num of days since 1-jan-1900 to 1-jan-yyyy (until 2200)

    // Default constructor
    Date() : m_serial(0) {}
    //*input serial
    Date(unsigned serial) : m_serial(serial) {}
   
    // Constructor where the input value is checked.
    //*��������ʱ�Զ���ֵm_serial
    //*�����ַ���ʱ��ֵm_serial
    //stoul��stringתΪunsigned
    Date(const std::string& yyyymmdd): Date
        (std::stoul(yyyymmdd.substr(0, 4)), 
        std::stoul(yyyymmdd.substr(4, 2)),
        std::stoul(yyyymmdd.substr(6))) 
    {}
    //*��������ʱ��Ҫ����ת��Ϊ������ͨ��init������
    Date(unsigned year, unsigned month, unsigned day)
    {
        init(year, month, day);
    }

    //*������yearmonthday��init��ת��Ϊm_serial(���������ھ����ʼ���ڵ�����)
    void init(unsigned year, unsigned month, unsigned day)
    {
        check_valid(year, month, day);
        unsigned month_days;
        month_days = (is_leap_year(year)) ? leap_days_ytd[month -1] : days_ytd[month - 1];
        //*serial=num days of former years+num days of former months in current year+num of days in current month
        m_serial = days_epoch[year - first_year] + month_days + day - 1;
    }

    //*������������init��ת��Ϊm_serial
    void init(unsigned serial)
    {
        //if (valid_test(serial))
            m_serial = serial;
    }


    /*Date(const std::string& yyyymmdd) :
        Date(std::stoul(yyyymmdd.substr(0, 4))��std::stoul(yyyymmdd.substr(4, 2))��std::stoul(yyyymmdd.substr(6)))
    {}*/
    //*�ж������Ƿ���Ч
    static void check_valid(unsigned y, unsigned m, unsigned d);
    static bool valid_test(unsigned y, unsigned m, unsigned d);
    //*�ж��Ƿ�Ϊ����
    static bool is_leap_year(unsigned year);
    //*��������ʼ���ڵ�����serialת��Ϊ�����յ�����
    void year_month_day(unsigned* y, unsigned* m, unsigned* d) const;

    
    //*number of days since 1-Jan-1900
    unsigned getserial() const
    {
        return m_serial;
    }

    //*�����-��С��ϵ
    bool operator<(const Date& d) const
    {
        return m_serial < d.getserial();
    }

    bool operator==(const Date& d) const
    {
        return m_serial <= d.getserial();
    }

    bool operator>(const Date& d) const
    {
        return m_serial > d.getserial();
    }


    //*�����-�Ӽ�
    Date operator+(unsigned n) const
    {
        return Date(getserial() + n);
    }

    Date operator-(unsigned n) const
    {
        return Date(getserial() - n);
    }

    // In YYYYMMDD format
    std::string to_string(bool pretty = true) const
    {
        unsigned m_y, m_m, m_d;
        year_month_day(&m_y, &m_m, &m_d);
        return pretty
            ? std::to_string((int)m_d) + "-" + std::to_string((int)m_m) + "-"
            + std::to_string(m_y)
            : std::to_string(m_serial);
    }
    
private:
    //*change yr,mth,day->serial
    unsigned m_serial;
};

long operator-(const Date& d1, const Date& d2);

inline double time_frac(const Date& d1, const Date& d2)
{
    return static_cast<double>(d2 - d1) / 365.0;
}

} // namespace minirisk
