//
// Created by nuray on 8.5.22.
//
#include "Time.hpp"
#include <iomanip>
#include <iostream>
//------------------------------------------------------------------------------//

CTime:: CTime ( ) { }
CTime:: CTime ( const CTime & other ) {
    m_tim = other.m_tim;
    m_hour = other.m_hour;
    m_minute = other.m_minute;
}
CTime:: CTime (const unsigned int & hour, const unsigned int & minute ) {
    calculate ( hour, minute );
    m_hour = hour;
    m_minute = minute;

}

//------------------------------------------------------------------------------//
void CTime:: setHour   ( const unsigned int & hour   ) { m_hour = hour;     }
void CTime:: setMinute ( const unsigned int & minute ) { m_minute = minute; }

//------------------------------------------------------------------------------//

unsigned int CTime:: hour   ( ) { return m_hour;    }
unsigned int CTime:: minute ( ) { return m_minute;  }
time_t CTime::timm ( ) { return m_tim; }

//------------------------------------------------------------------------------//

bool CTime:: isValidTime ( const unsigned int & hour, const  unsigned int & min ) {
    if  ( hour > 23 || hour < 0 || min > 59 || min < 0 )
        return false;
    return true;
}
void CTime::calculate ( const int & hour, const int & minute ) {
    struct tm  timePtr;
    m_tim = time (NULL );
    timePtr = *localtime (&m_tim );

    timePtr.tm_hour = hour ;
    timePtr.tm_min = minute ;
    timePtr.tm_sec = 1;

    m_tim = mktime (&timePtr );

}

//------------------------------------------------------------------------------//

CTime & CTime:: operator  +  ( int minutes ) {
    m_tim += (minutes * 60);
    struct tm timePtr = *localtime(&m_tim);
    m_hour = timePtr.tm_hour;
    m_minute = timePtr.tm_min;
    return *this;
}
bool CTime::    operator  == ( const CTime & other )  {
    return ( this->m_hour == other.m_hour &&
    this->m_minute == other.m_minute && m_tim == other.m_tim );
}
bool CTime::    operator  >  ( const CTime & other )  {
    if  ( this->m_hour == other.m_hour )
        return ( this->m_minute > other.m_minute );
    else return ( this->m_hour > other.m_hour );
}
bool CTime::    operator  <  ( const CTime & other )  {
    if  ( this->m_hour == other.m_hour )
        return ( this->m_minute < other.m_minute|| m_tim < other.m_tim  );
    else return ( this->m_hour  <  other.m_hour || m_tim < other.m_tim );
}
bool CTime::    operator  >= ( const CTime & other )  {
    if  ( this->m_hour == other.m_hour )
        return ( this->m_minute >= other.m_minute );
    else return this->m_hour >= other.m_hour ;
}
bool CTime::    operator  <= ( const CTime & other )  {
    if  ( this->m_hour == other.m_hour )
        return ( this->m_minute <= other.m_minute );
    else return this->m_hour <= other.m_hour;
}
CTime& CTime::  operator  =  ( const CTime & other )  {
    if ( this == &other )
        return *this;
    this->m_hour = other.m_hour;
    this->m_minute = other.m_minute;
    this->m_tim = other.m_tim;
    return *this;
}
std::ostream &  operator  << ( std::ostream & out , const CTime & time ) {
    struct tm timePtr = *localtime(&time.m_tim) ;
    out << std::setfill( '0' ) << std::setw( 2 )
        << timePtr.tm_hour  << ":" << std::setfill( '0' )
        << std::setw( 2 ) << timePtr.tm_min ;

    return out;
}

