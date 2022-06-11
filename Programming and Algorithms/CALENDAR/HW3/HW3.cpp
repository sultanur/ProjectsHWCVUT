#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

//=================================================================================================
// a dummy exception class, keep this implementation
class InvalidDateException : public invalid_argument
{
  public:
    InvalidDateException ( )
      : invalid_argument ( "invalid date or format" )
    {
    }
};
//=================================================================================================
// date_format manipulator - a dummy implementation. Keep this code unless you implement your
// own working manipulator.
ios_base & ( * date_format ( const char * fmt ) ) ( ios_base & x )
{
  return [] ( ios_base & ios ) -> ios_base & { return ios; };
}
//=================================================================================================


class CDate
{

public:

    CDate ( int year, int month, int day ) {

        if ( !(isValidDate(year, month, day)) )
            throw InvalidDateException();
        else
            calculate(year, month, day);
    }
    CDate ( const CDate & tim ):m_time ( tim.m_time ) { }

    bool isLeapYear  ( int year) {
        if ( year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
            return true;
        else return false;
    }
    void calculate   ( int year, int month, int day) {
        m_time = time( NULL );
        tm *timePtr = localtime( &m_time );

       timePtr->tm_year = year - 1900;
       timePtr->tm_mon  = month - 1;
       timePtr->tm_mday = day;
       timePtr->tm_sec = 1;
       timePtr->tm_min = 1;
       timePtr->tm_hour = 1;

       m_time = mktime( timePtr );
       //cout << m_time << endl;
   }
    bool isValidDate ( int year, int month, int day) {
        static const int DaysInMonth[ 2 ][ 12 ] = {
                { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
                { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
        };

        if ( year < 1 || month < 1 || month > 12 || day < 1 || day > DaysInMonth[isLeapYear(year)][month -1])
            return false;
        else return true;
    }


    CDate & operator + ( int days ) {
        m_time += (days*86400);
        return *this;
    }
    CDate & operator - ( int days ) {
        m_time -= (days*86400);
        return *this;
    }
    int operator - ( const CDate & d ) const { // difference between two dates;
       return  difftime(this->m_time, d.m_time) / 86400;
    }
    CDate & operator =  ( const CDate & d ) {
        if (this == &d)
            return *this;
        this->m_time = d.m_time;
        return *this;
    }
    CDate & operator ++ ( ) {
        this->m_time += 86400;
        return *this;
    }
    CDate   operator ++ ( int d) {  // postfix
        CDate temp = *this;
        this->m_time += 86400; //adding 1 day in seconds
        return temp;
    }
    CDate & operator -- ( ) {
        this->m_time -= 86400;
        return *this;
    }
    CDate   operator -- ( int d) {
        CDate temp = *this;
        this->m_time -= 86400;
        return temp;
    }
    bool operator == ( const CDate & d ) const {
        return this->m_time == d.m_time;
    }
    bool operator != ( const CDate & d ) const {
        return this->m_time != d.m_time;
    }
    bool operator <= ( const CDate & d ) const {
        return this->m_time <= d.m_time;
    }
    bool operator <  ( const CDate & d ) const {
        return this->m_time < d.m_time;
    }
    bool operator >= ( const CDate & d ) const {
        return this->m_time >= d.m_time;
    }
    bool operator >  ( const CDate & d ) {
        return this->m_time > d.m_time;
    }
    friend ostream & operator << ( ostream & out,  CDate & d ) {
        tm *timePtr = localtime( &d.m_time );
        out << timePtr->tm_year + 1900 << '-' << setfill('0') << setw(2)
            << timePtr->tm_mon + 1 << '-' <<  setw(2) << timePtr->tm_mday;
        return out;
    }
    friend istream & operator >> ( istream & in, CDate & d ) {
        //"2015-09-03"
        int year, month, day;
        char ch;
        in >> year >> ch >> month >> ch >> day;
        if ( (!(d.isValidDate(year, month, day))) || ch != '-') {
            in.setstate(ios::failbit);
            return in;
        }
        d.calculate(year, month, day);
        return in;
    }

private:
    time_t m_time;
};

#ifndef __PROGTEST__
int main ( void )
{
  ostringstream oss;
  istringstream iss;

  CDate a ( 2000, 1, 2 );
  CDate b ( 2010, 2, 3 );
  CDate c ( 2004, 2, 10 );
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2000-01-02" );
  oss . str ("");
  oss << b;
  assert ( oss . str () == "2010-02-03" );
  oss . str ("");
  oss << c;
  assert ( oss . str () == "2004-02-10" );
  a = a + 1500;
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2004-02-10" );
  b = b - 2000;
  oss . str ("");
  oss << b;
  assert ( oss . str () == "2004-08-13" );
  assert ( b - a == 185 );
  assert ( ( b == a ) == false );
  assert ( ( b != a ) == true );
  assert ( ( b <= a ) == false );
  assert ( ( b < a ) == false );
  assert ( ( b >= a ) == true );
  assert ( ( b > a ) == true );
  assert ( ( c == a ) == true );
  assert ( ( c != a ) == false );
  assert ( ( c <= a ) == true );
  assert ( ( c < a ) == false );
  assert ( ( c >= a ) == true );
  assert ( ( c > a ) == false );
  a = ++c;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-11 2004-02-11" );
  a = --c;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-10 2004-02-10" );
  a = c++;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-10 2004-02-11" );
  a = c--;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-11 2004-02-10" );
  iss . clear ();
  iss . str ( "2015-09-03" );
  assert ( ( iss >> a ) );
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2015-09-03" );
  a = a + 70;
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2015-11-12" );

  CDate d ( 2000, 1, 1 );
  try
  {
    CDate e ( 2000, 32, 1 );
    assert ( "No exception thrown!" == nullptr );
  }
  catch ( ... )
  {
  }
  iss . clear ();
  iss . str ( "2000-12-33" );
  assert ( ! ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-01-01" );
  iss . clear ();
  iss . str ( "2000-11-31" );
  assert ( ! ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-01-01" );
  iss . clear ();
  iss . str ( "2000-02-29" );
  assert ( ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-02-29" );
  iss . clear ();
  iss . str ( "2001-02-29" );
  assert ( ! ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-02-29" );

//  //-----------------------------------------------------------------------------
//  // bonus test examples
//  //-----------------------------------------------------------------------------
//  CDate f ( 2000, 5, 12 );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2000-05-12" );
//  oss . str ("");
//  oss << date_format ( "%Y/%m/%d" ) << f;
//  assert ( oss . str () == "2000/05/12" );
//  oss . str ("");
//  oss << date_format ( "%d.%m.%Y" ) << f;
//  assert ( oss . str () == "12.05.2000" );
//  oss . str ("");
//  oss << date_format ( "%m/%d/%Y" ) << f;
//  assert ( oss . str () == "05/12/2000" );
//  oss . str ("");
//  oss << date_format ( "%Y%m%d" ) << f;
//  assert ( oss . str () == "20000512" );
//  oss . str ("");
//  oss << date_format ( "hello kitty" ) << f;
//  assert ( oss . str () == "hello kitty" );
//  oss . str ("");
//  oss << date_format ( "%d%d%d%d%d%d%m%m%m%Y%Y%Y%%%%%%%%%%" ) << f;
//  assert ( oss . str () == "121212121212050505200020002000%%%%%" );
//  oss . str ("");
//  oss << date_format ( "%Y-%m-%d" ) << f;
//  assert ( oss . str () == "2000-05-12" );
//  iss . clear ();
//  iss . str ( "2001-01-1" );
//  assert ( ! ( iss >> f ) );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2000-05-12" );
//  iss . clear ();
//  iss . str ( "2001-1-01" );
//  assert ( ! ( iss >> f ) );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2000-05-12" );
//  iss . clear ();
//  iss . str ( "2001-001-01" );
//  assert ( ! ( iss >> f ) );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2000-05-12" );
//  iss . clear ();
//  iss . str ( "2001-01-02" );
//  assert ( ( iss >> date_format ( "%Y-%m-%d" ) >> f ) );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2001-01-02" );
//  iss . clear ();
//  iss . str ( "05.06.2003" );
//  assert ( ( iss >> date_format ( "%d.%m.%Y" ) >> f ) );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2003-06-05" );
//  iss . clear ();
//  iss . str ( "07/08/2004" );
//  assert ( ( iss >> date_format ( "%m/%d/%Y" ) >> f ) );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2004-07-08" );
//  iss . clear ();
//  iss . str ( "2002*03*04" );
//  assert ( ( iss >> date_format ( "%Y*%m*%d" ) >> f ) );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2002-03-04" );
//  iss . clear ();
//  iss . str ( "C++k" );
//  assert ( ( iss >> date_format ( "C++%mformat%dPA2%Yrulez" ) >> f ) );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2006-09-10" );
//  iss . clear ();
//  iss . str ( "%12%13%2010%" );
//  assert ( ( iss >> date_format ( "%%%m%%%d%%%Y%%" ) >> f ) );
//  oss . str ("");
//  oss << f;
//  assert ( oss . str () == "2010-12-13" );
//
//  CDate g ( 2000, 6, 8 );
//  iss . clear ();
//  iss . str ( "2001-11-33" );
//  assert ( ! ( iss >> date_format ( "%Y-%m-%d" ) >> g ) );
//  oss . str ("");
//  oss << g;
//  assert ( oss . str () == "2000-06-08" );
//  iss . clear ();
//  iss . str ( "29.02.2003" );
//  assert ( ! ( iss >> date_format ( "%d.%m.%Y" ) >> g ) );
//  oss . str ("");
//  oss << g;
//  assert ( oss . str () == "2000-06-08" );
//  iss . clear ();
//  iss . str ( "14/02/2004" );
//  assert ( ! ( iss >> date_format ( "%m/%d/%Y" ) >> g ) );
//  oss . str ("");
//  oss << g;
//  assert ( oss . str () == "2000-06-08" );
//  iss . clear ();
//  iss . str ( "2002-03" );
//  assert ( ! ( iss >> date_format ( "%Y-%m" ) >> g ) );
//  oss . str ("");
//  oss << g;
//  assert ( oss . str () == "2000-06-08" );
//  iss . clear ();
//  iss . str ( "hello kitty" );
//  assert ( ! ( iss >> date_format ( "hello kitty" ) >> g ) );
//  oss . str ("");
//  oss << g;
//  assert ( oss . str () == "2000-06-08" );
//  iss . clear ();
//  iss . str ( "2005-07-12-07" );
//  assert ( ! ( iss >> date_format ( "%Y-%m-%d-%m" ) >> g ) );
//  oss . str ("");
//  oss << g;
//  assert ( oss . str () == "2000-06-08" );
//  iss . clear ();
//  iss . str ( "20000101" );
//  assert ( ( iss >> date_format ( "%Y%m%d" ) >> g ) );
//  oss . str ("");
//  oss << g;
//  assert ( oss . str () == "2000-01-01" );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
