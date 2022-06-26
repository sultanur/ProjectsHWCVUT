//
// Created by nuray on 1.5.22.
//

#ifndef CDATE_H
#define CDATE_H
#include "Time.hpp"
#include <iostream>
#include <time.h>
#include <cstdlib>

//!Macro definition LeapYear calculates leap year for given parameter (year)
#define LeapYear( year) (( year %400 == 0 ) || ( ( year % 4 == 0 ) && (year %100 != 0 ) ) )

//!static variable array of chars, which consists all 12 months. This static variable is used by classes CCalendar and CDate
static const char *months[] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December",

};

//!static variable array of  chars, which consists short abbreviations of 12 months for printing out in different types of calendar
static const char *monthsAbbreviation[] = {
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sep",
        "Oct",
        "Nov",
        "Dec",

};

//!class CDate is designed to provide date in Gregorian Calendar,  calculations are done by functions mktime and localtime from library time.h
/*!
 *class CDate has 3 attributes (unsigned int m_hour, unsigned int m_month , unsigned int m_day). Takes parameters,
 * validates data taking into account leap years and days in months. For calculation uses
 * mktime and localtime functions from library time.h
 */
class CDate {

private:
    unsigned int m_day;
    unsigned int m_month;
    unsigned int m_year;
    time_t m_tim;

public:
    //! Default constructor is called when object of CDate is created
    CDate( );

    //! Default parametrized constructor is called when object of CDate is created
    /*!Takes day, month, year,  assigns each to attributes of class CDate and calculates parameters with localtime  and mktime function.
     * \param day - const ref of type int to day
     * \param month - const ref of type int to month
     * \param year - const ref of type int to year
     */
    CDate ( const unsigned int & day, const unsigned int & month, const unsigned int& year ) ;

//!Default parametrized constructor, takes as parameter object of CDate
/*!Reads value of object CDate
 \param date - an object of CTime.
*/
    CDate ( const CDate & date );
//------------------------------------------------------------------------------//
//!Getters of attributes of class CDate
/*! method unsigned int day() returns attribute m_day
 * @return  unsigned int  m_day
 */
    unsigned int day   ( );

/*! method unsigned int month() returns attribute m_month
 * @return  unsigned int  m_month
 */
    unsigned int month ( );

    /*! method unsigned int year() returns attribute m_year
 * @return  unsigned int  m_year
 */
    unsigned int year  ( );
    time_t  tim ( ) ;
//------------------------------------------------------------------------------//
//! Setters of attributes
/*! method setDay takes const ref to variable day and assigns to attribute m_day
 * @param day - const ref of  type unsigned int
 */
    void setDay   ( const unsigned int & day   ) ;
    /*! method setMonth takes const ref to variable month and assigns to attribute m_month
 * @param month - const ref of  type unsigned int
 */
    void setMonth ( const unsigned int & month ) ;

    /*! method setMonth takes const ref to variable year and assigns to attribute m_year
* @param month - const ref of  type unsigned int
*/
    void setYear  ( const unsigned int & year  ) ;

//------------------------------------------------------------------------------//
//!Overloaded operator <<
/*!Handles calculation with mktime and localtime functions and printing date in format
 * @param out - object of class ostream
 * @param date - object of CDate to print out
 * @return object of class ostream
 */
    friend std::ostream & operator << ( std::ostream & out, const CDate & date );


    //!Overloaded operator =
    /*!Handles a deep copy of the CDate object.
   \param other - a CDate object we are copying from.
   \return CDate object
   */
    CDate & operator = ( const CDate & other ) ;


    //!Overloaded operator +
/*! overloaded operator calculates addition of days to object of CDate. Calculation is done by using localtime and mktime functions
 \param days - int value
 \return object of CDate
 */
    CDate & operator + ( int days) ;

    //!Overloaded operator !=
/*!Handles comparison between two CDate objects.
      \param other - a CDate object we are comparing with.
      \return true if this != other else returns false.
*/
    bool  operator  != ( const CDate & other ) const ;

    //!Overloaded operator ==
/*!Handles comparison between two CDate objects.
      \param other - a CDate object we are comparing with.
      \return true if this == other else returns false.
*/
    bool  operator  == ( const CDate & other ) const ;

    //!Overloaded operator >=
/*!Handles comparison between two CDate objects.
      \param other - a CDate object we are comparing with.
      \return true if this >= other else returns false.
*/
    bool  operator  >= ( const CDate & other ) const ;
    //!Overloaded operator <=
/*!Handles comparison between two CDate objects.
      \param other - a CDate object we are comparing with.
      \return true if this <= other else returns false.
*/
    bool  operator  <= ( const CDate & other ) const ;
    //!Overloaded operator >
/*!Handles comparison between two CDate objects.
      \param other - a CDate object we are comparing with.
      \return true if this > other else returns false.
*/
    bool  operator  >  ( const CDate & other ) const ;

    //!Overloaded operator <
/*!Handles comparison between two CDate objects.
      \param other - a CDate object we are comparing with.
      \return true if this < other else returns false.
*/
    bool  operator  <  ( const CDate & other ) const ;

//------------------------------------------------------------------------------//

//! method calculate( const unsigned int & year, const unsigned int & month, const unsigned int & day )
/*!calculates date in integer by localtime and mktime functions from library time.h. This value is useful in automated calculations of addition of  days to dates
 \param day  - const ref of type int to hour
 \param month - const red if type int to minute
 \param year - const red if type int to minute
 */
    void calculate ( const unsigned int & year, const unsigned int & month, const unsigned int & day );

    //! method getMonthDays calculates exact number of days in month for given  month with year
    /*!
     * @param month - const ref of type unsigned int
     * @param year - const ref of type unsigned int
     * @return  unsigned int days in month
     */


    unsigned int getMonthDays ( const unsigned int & month, const unsigned int &  year ) const;

    //! method getWeekDay  calculates weekday for given date
    /*!
     * @param day - unsigned int value
     * @param month - unsigned int value
     * @param year - unsigned int value
     * @return  weekday in integer, f.e. Monday = 1, Tuesday = 2 etc.;
     */
    int getWeekDay (  unsigned int day, unsigned int  month, unsigned int year ) const;

    /*! static overloads method isValidDate, takes 2 parameters,
  /*! provides validation of date which builds from parameters year month and day, calculates days in month with consideration of  leap years
   * @param year - const ref of type int
   * @param month - const ref of type int
     * @param day -  const ref of type int
   */
    bool isValidDate( const unsigned int & year, const unsigned  int& month, const  unsigned int &day );

//------------------------------------------------------------------------------//
};


#endif //CDATE_H
