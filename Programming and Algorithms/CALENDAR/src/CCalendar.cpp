
#include <iomanip>
#include "CCalendar.hpp"
#include "CDate.hpp"
#include <time.h>

#define TIME_SIZE 40


//-------------------------------------------------------------------------------------------------------------------//

std::ostream & operator << ( std::ostream & out, const CCalendar & d ) {
    d.print( out  );
    return out;
}
CDate & CCalendar:: setDate ( unsigned int year = 0, unsigned int month = 0, unsigned int day = 0 ) {
    m_date->setYear  ( year  );
    m_date->setMonth ( month );
    m_date->setDay   ( day   );
    return *m_date;
}
CTime & CCalendar:: setTime ( const unsigned int & hour, const unsigned int & minute ) {
    m_time->setHour( hour );
    m_time->setMinute( minute );
    return *m_time;
}
bool CCalendar:: isValidDate ( unsigned int year, unsigned int month, unsigned int day ) {
    if ( year > 4000 || year < 2000 || day < 1 || day > m_date->getMonthDays( month, year) || month < 1 || month > 12 )
        return false;
    return true;
}

//-------------------------------------------------------------------------------------------------------------------//

MonthlyCalendar :: MonthlyCalendar( ) { }
MonthlyCalendar :: MonthlyCalendar ( unsigned int year, unsigned int month ) {
    auto d = setDate ( year, month );
}

void MonthlyCalendar:: print ( std::ostream  & out ) const {
    size_t i = 0, j = 0;
    int firstDayWeek = m_date->getWeekDay(1, m_date->month(), m_date->year());
    std::cout << firstDayWeek << std::endl;
    unsigned int numberDays = m_date->getMonthDays(m_date->month(), m_date->day());
    out << "                   Monthly Calendar \n" ;

    out << std::setw(20) << "  " << months[m_date->month() - 1] << " " << m_date->year() << std::endl;
    out << "|----------------------------------------------------------------|\n";
    out << std::setw(9)  << "SUN" ;
    out << "     MON     TUE     WED     THU     FRI";
    out << std::setw(10) <<  "SAT\n" ;
    out  <<"|----------------------------------------------------------------|\n" ;

    for (i = 1; i <= firstDayWeek; ++i) {
        out << "        ";
    }
    j = firstDayWeek;

    for (i = 1; i <= numberDays; i++) {
        unsigned int weekday = m_date->getWeekDay(i, m_date->month(), m_date->year());

        if (j++ % 7 == 0 && j != 1) {
            out << "\n";
            out << std::setw(8) << i;
        } else if (i == 1) {
            out << std::setw(8) << i;
        } else {
            out << std::setw(8) << i;
        }
    }
    out <<"\n\n\n";
}
bool MonthlyCalendar:: isValidDate ( unsigned int year, unsigned int month )  {
    if ( year > 4000 || year < 2000 || month > 12 || month < 1 )
        return false;
    return true;
}

//-------------------------------------------------------------------------------------------------------------------//

WeeklyCalendar:: WeeklyCalendar ( ) { }
WeeklyCalendar:: WeeklyCalendar ( unsigned int year , unsigned int month,  unsigned int day ) {
    auto d = setDate ( year, month, day );
}

void WeeklyCalendar:: print ( std::ostream & out ) const {
    out  << "                  Weekly Calendar \n" ;
        if ( m_date->day() > 24)
            out << "                   " << months[m_date->month()-1] << "-"
                <<months[m_date->month()] << m_date->year() << "\n" ;
        else
            out << "                   "  << months[m_date->month()-1]
                <<"  " << m_date->year() << "\n" ;
        unsigned int firstDayWeek = m_date->getWeekDay (m_date->day(), m_date->month(), m_date->year() );
        out << "|----------------------------------------------------------------|\n ";
        out << std::setw(10) << "SUN" ;
        out << std::setw(8)  << "MON" << std::setw(8)  << "TUE" << std::setw(8)
                                << "WED" << std::setw(8)  << "THU" << std::setw(8)  << "FRI";
        out << std::setw(10)  <<"SAT\n";
        out <<"|----------------------------------------------------------------|\n";

        for ( auto i = 0; i < firstDayWeek; ++i) {
            out << "        ";
        }
        auto j = firstDayWeek;
        int daysInMonth = m_date->getMonthDays(m_date->month(), m_date->year() );
        int n = m_date->day() + 7;
        int i = 0;
        if ( n <= daysInMonth ) {
            for (i = m_date->day(); i < n; i++) {
                if (j++ % 7 == 0 && j != 1) {
                    out << "\n";
                    out << std::setw(8) << i;
                } else if (i == 1) {
                    out << std::setw(8) << i;
                } else {
                    out << std::setw(8) << i;
                }
            }
            out << "\n\n\n";
        } else {
            for (i = m_date->day(); i <= daysInMonth; i++) {

                if (j++ % 7 == 0 && j != 1 ) {
                    out << "\n";
                    out << std::setw(8) << i;
                } else {
                    out << std::setw(8) << i;
                }
            }
            n -= daysInMonth;
            for (i = 1; i < n; i++) {
                if (j++ % 7 == 0 && j != 1) {
                    out << "\n";
                    out << std::setw(8) << i;
                } else if (i == 1) {
                    out << std::setw(8) << i;
                } else {
                    out << std::setw(8) << i;
                }
            }
            out << "\n\n\n";

        }
    }

//------------------------------------------------------------------------------------------------------------------//

DailyCalendar:: DailyCalendar( ) { }
DailyCalendar:: DailyCalendar ( unsigned int year,   unsigned int month, unsigned int day ) {
    auto d = setDate (year, month, day );
}

void DailyCalendar:: print ( std::ostream & out  ) const  {

    out <<"               Daily Calendar \n";
        out << "              "  << m_date->day() << "  " << months[m_date->month() - 1] <<"  "  << m_date->year() << "\n" ; //week -> date
    for ( size_t i = 1; i < 12; ++i ) {
        out  << i << ": AM  _______________________________\n";
    }
    for ( size_t i = 12; i < 25; ++i ) {
        out  << i << ": PM  _______________________________\n";
    }
    out <<"\n\n";
}


//-------------------------------------------------------------------------------------------------------------------//