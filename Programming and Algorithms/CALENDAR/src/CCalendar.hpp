//
// Created by nuray on 1.5.22.
//


#ifndef CALENDAR_DATE_H
#define CALENDAR_DATE_H
#include <iostream>
#include <vector>
#include <memory>
#include "CDate.hpp"
#include "Time.hpp"

//------------------------------------------------------------------------------------------------------------//
//!Class CCalendar
/*! class is designed for printing 3 types of Calendar: Monthly, Weekly, Daily
 *This class is abstract parent class for 3 derived classes , contains virtual methods and destructor;
 */
class CCalendar  {

protected:
    //! 2 attributes of class CCalendar are 2 shared_ptr to classes CDate and CTime. These attributes are main providers
    /*!  of data related to dates and time in building monthly , weekly and daily calendars. */
    std::shared_ptr<CDate> m_date = std::make_shared<CDate>();
    std::shared_ptr<CTime> m_time = std::make_shared<CTime>();

public:
    //!virtual Destructor
    /*!Destructs objects of  derived classes of CCalendar
    */
    virtual ~CCalendar ( ) { }

//! method setDate
/*! assigns parameters year, month, day to attributes of class CDate and returns  CDate object. All three parameters assigned to 0;
 * @param year -  unsigned int value of year
 * @param month -  unsigned int to value of month
 * @param day -    unsigned int to value of day
 * @return object of CDate
 */
    CDate& setDate ( unsigned int year, unsigned int  month,  unsigned int day );

//! method setTime
/*! assigns parameters hour and minute to attributes of class CTime and returns CTime object
 * @param hour - const ref of type unsigned int to value of hour
 * @param minute - const ref of type unsigned int to value of minute
 * @return object of CTime
 */
    CTime& setTime ( const unsigned int & hour, const unsigned int & minute );
//! virtual method print
 /*!Method is called by operator <<  provides calculations and design of object's parameters and prints out result;
 \param out - an ostream output value.
 */
    virtual void print ( std::ostream & out ) const = 0;
//! virtual method isValidate
/*! provides validation of date which builds from parameters year month and day, calculates days in month with consideration of  leap years
 * @param year - unsigned value of year,
 * @param month - unsigned value of month,
 * @param day - unsigned value of day;
 */
    virtual bool isValidDate ( unsigned int year, unsigned int month, unsigned int day ) ;
//! overloading operator << , cals method print to output object of derived classes of CCalendar
/*!
 * @param out - object of class ostream, outputs object of class CCalendar to console
 * @param d - src object of CCalendar
 */
    friend std::ostream & operator << ( std::ostream & out, const CCalendar & d ) ;
};
//----------------------------------------------------------------------------------------------------------------//
//! derived class MonthlyCalendar of abstract class CCalendar
/*! This class responsible for design and printing out monthly calendar
 */
class MonthlyCalendar : public CCalendar  {
public:
//! default constructor is called when object of MonthlyCalendar is created;
    MonthlyCalendar( ) ;
//! parametrized constructor, which takes 2 parameters and sets them to attributes of CDate class
/*! parameters assigns to attributes of CDate class by calling method setDate which takes these params;
 * @param year - unsigned value of year
 * @param month  - unsigned value of month
 */
    MonthlyCalendar( unsigned int year, unsigned int month ) ;
/*! static overloads method isValidDate, takes 2 parameters,
/*! provides validation of date which builds from parameters year month and day, calculates days in month with consideration of  leap years
 * @param year - unsigned value of year,
 * @param month - unsigned value of month;
 */
    bool isValidDate ( unsigned int year, unsigned int month );

//! override method print
    /*!Method is called by operator <<  provides calculations and design objects of class MonthlyCalendar  and prints out the result;
    \param out - an ostream output value.
    */
    void print ( std::ostream  & out ) const override ;
};
//----------------------------------------------------------------------------------------------------------------//
//! derives class WeeklyCalendar, responsible for printing out weekly calendar
class WeeklyCalendar: public CCalendar {
public:
//!default constructor, is called when object of WeeklyCalendar is created;
    WeeklyCalendar ( );
//! parametrized constructor, which takes 3 parameters and sets them to attributes of CDate class
/*! parameters assigns to attributes of CDate class by calling method setDate which takes these params;
 * @param year - unsigned value of year
 * @param month  - unsigned value of month
 * @param day - unsigned value of day;
 */
    WeeklyCalendar ( unsigned int year, unsigned int month, unsigned int day ) ;

//! override method print
    /*!Method is called by operator <<  provides calculations and design objects of class WeeklyCalendar  and prints out the result;
    \param out - an ostream output value.
    */
    void print ( std::ostream & out ) const override ;

};
//----------------------------------------------------------------------------------------------------------------//
//!derived class DailyCalendar is responsible for calculation , design of DailyCalendar
class DailyCalendar: public CCalendar  {
public:
//!default constructor, is called when object of DailyCalendar is created;
    DailyCalendar();
//! parametrized constructor, which takes 3 parameters and sets them to attributes of CDate class
/*! parameters assigns to attributes of CDate class by calling method setDate which takes these params;
 * @param year -   unsigned value of year
 * @param month  - unsigned value of month
 * @param day -  unsigned value of day;
 */
    DailyCalendar(unsigned int year, unsigned int month, unsigned int day);

//! override method print
    /*!Method is called by operator <<  provides calculations and design objects of class DailyCalendar  and prints out the result;
    \param out - an ostream output value.
    */
    void print ( std::ostream &out ) const override;

};

#endif //CALENDAR_DATE_H