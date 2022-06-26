//
// Created by nuray on 1.5.22.
//
#include "CDate.hpp"
#include "Time.hpp"
#include <iomanip>
#include <time.h>


//------------------------------------------------------------------------------//

    CDate:: CDate  ( ) { }
    CDate:: CDate  ( const CDate & date ) {
        m_tim = date.m_tim;
        m_day = date.m_day;
        m_month = date.m_month;
        m_year = date.m_year;
    }
    CDate:: CDate  ( const unsigned int & day, const unsigned int & month, const unsigned int & year ) {
            calculate(year, month, day);
            m_day = day;
            m_month = month;
            m_year = year;

    }
//------------------------------------------------------------------------------//

    unsigned int CDate:: day   ( ) { return m_day;   }
    unsigned int CDate:: month ( ) { return m_month; }
    unsigned int CDate:: year  ( ) { return m_year ; }
    time_t CDate:: tim ( ) { return m_tim; }

//------------------------------------------------------------------------------//

    void CDate:: setDay   ( const unsigned int & day   )  { m_day  = day;    }
    void CDate:: setMonth ( const unsigned int & month )  { m_month = month; }
    void CDate:: setYear  ( const unsigned int & year  )  { m_year = year;   }

//------------------------------------------------------------------------------//
    std::ostream & operator  <<  ( std::ostream & out, const CDate & date ) {
    struct tm timePtr = *localtime(&date.m_tim) ;
    out  << timePtr.tm_year + 1900 << '-' << std::setfill( '0' )
         << std::setw( 2 ) << timePtr.tm_mon + 1 << '-' << std::setw( 2 ) << timePtr.tm_mday;
    return out;
}
    CDate& CDate::  operator =   ( const CDate & other )        {
        if ( this == &other ) return *this;
        this->m_tim = other.m_tim;
        this->m_year = other.m_year;
        this->m_month = other.m_month;
        this->m_day = other.m_day;
        return *this;
}
    CDate & CDate:: operator +   ( int days )                   {
        m_tim += days*(24*60*60);
        struct tm timePtr = *localtime(&m_tim) ;
        m_year = timePtr.tm_year + 1900;
        m_month = timePtr.tm_mon + 1;
        m_day = timePtr.tm_mday;
        return *this;
    }
    bool  CDate:: operator   ==  ( const CDate & other ) const  {
        return ( this->m_tim == other.m_tim && this->m_year == other.m_year &&
                    this->m_month == other.m_month && this->m_day == other.m_day ) ;
    }
    bool  CDate:: operator   !=  ( const CDate & other ) const  {
        return  (! ( this->m_tim == other.m_tim && this->m_year == other.m_year &&
                 this->m_month == other.m_month && this->m_day == other.m_day )) ;
    }
    bool  CDate:: operator   <   ( const CDate & other ) const  {
        if ( this->m_year < other.m_year || this->m_tim < other.m_tim ) {
            return true;
        } else if ( this->m_year == other.m_year ) {
            if ( this->m_month < other.m_month ||  this->m_tim < other.m_tim ) {
                return true;
            } else if ( this->m_month == other.m_month ) {
                if ( this->m_day < other.m_day || this->m_tim < other.m_tim ) {
                    return true;
                }
            }
        }
        return false;
    }
    bool  CDate:: operator   <=  ( const CDate & other ) const  {
        if ( this->m_year <= other.m_year || this->m_tim <= other.m_tim  ) {
            return true;
        } else if ( this->m_year == other.m_year ) {
            if ( this->m_month <= other.m_month || this->m_tim <= other.m_tim ) {
                return true;
            } else if ( this->m_month == other.m_month ) {
                if ( this->m_day <= other.m_day || this->m_tim <= other.m_tim ) {
                    return true;
                }
            }
        }
        return false;
    }
    bool  CDate:: operator    >  ( const CDate & other ) const  {
        if ( this->m_year > other.m_year || this->m_tim > other.m_tim ) {
            return true;
        } else if ( this->m_year == other.m_year ) {
            if ( this->m_month > other.m_month || this->m_tim > other.m_tim ) {
                return true;
            } else if ( this->m_month == other.m_month ) {
                if ( this->m_day > other.m_day || this->m_tim > other.m_tim ) {
                    return true;
                }
            }
        }
        return false;
    }
    bool  CDate:: operator   >=  ( const CDate & other ) const  {
        if ( this->m_year >= other.m_year || this->m_tim >= other.m_tim ) {
            return true;
        } else if ( this->m_year == other.m_year ) {
            if ( this->m_month >= other.m_month || this->m_tim >= other.m_tim ) {
                return true;
            } else if ( this->m_month == other.m_month ) {
                if ( this->m_day >= other.m_day || this->m_tim >= other.m_tim ) {
                    return true;
                }
            }
        }
        return false;
    }


//------------------------------------------------------------------------------//
    void CDate::calculate    ( const unsigned int & year,
                               const unsigned int & month,
                               const unsigned int & day  )    {
    struct tm  timePtr;
    m_tim = time(NULL);
    timePtr = *localtime(&m_tim);
    timePtr.tm_year = year - 1900;
    timePtr.tm_mon = month - 1;
    timePtr.tm_mday = day;

    timePtr.tm_hour = 1;
    timePtr.tm_min = 1;
    timePtr.tm_sec = 1;

    m_tim = mktime(&timePtr);

}
    unsigned int CDate:: getMonthDays ( const unsigned int & month,
                                        const unsigned int & year ) const {
    unsigned int monthDays[] ={31,28,31,30,31,30,31,31,30,31,30,31  };

    if ( month == 2 ) {
        monthDays[1] = LeapYear( year ) ? 29 : 28 ;
    }
    return monthDays[month-1];  /* Return number of days in that month */
}
    int CDate:: getWeekDay   ( unsigned int day, unsigned int  month,
                               unsigned int year ) const      {
    // std::string weekday[7] = {"Saturday","Sunday","Monday","Tuesday", "Wednesday","Thursday","Friday"};
    static int t[] = { 0, 3, 2, 5, 0, 3,
                       5, 1, 4, 6, 2, 4 };
    year -= month < 3;
    return ( year + year / 4 - year / 100 +
             year / 400 + t[month - 1] + day) % 7;
}
    bool CDate:: isValidDate ( const unsigned  int & year,
                               const unsigned  int & month,
                               const unsigned  int & day   )   {
        if ( month < 1 || month > 12 || day < 1 || day > getMonthDays( month, year ) || year < 2000 || year > 4000)
            return false;
        return true;
    }




