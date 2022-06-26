//
// Created by nuray on 8.5.22.
//

#ifndef CALENDAR_TIME_H
#define CALENDAR_TIME_H
#define TIME_SIZE 40
#include <ostream>


/*!Handles custom time format ( hours and minutes). Class has methods which\n
* read the time format and decide whether it is valid or invalid. This class is\n
* working with standard time format in integer values and also for addition of time uses library time.h and
* struct tm *localtime(const time_t *__timer)
* class CTime has 3 attributes: m_hour, m_minute and time_t m_tim (holds int value of provided time)
 */

class CTime {
private:
    unsigned int m_hour;
    unsigned int m_minute;
    time_t m_tim;

public:

 //!Default constructor, called when object is created
    CTime ( ) ;

//!Default parametrized constructor, takes as parameter object of CTime and assigns to attributes of class
/*!Reads value of object CTime.
 \param other - an object of CTime.
*/
    CTime ( const CTime & other );

//!Default parametrized constructor, takes as parameter hour and minute
/*!Reads hour, minute, assigns each to attributes of class and calculates parameters with localtime function.
 \param hour - const ref of type unsigned int to hour
 \param minute - const ref of type unsigned int to minute
*/
    CTime ( const unsigned int & hour, const unsigned int & minute );

//!setters of attributes of class CTime
/*!method setHour takes const ref of unsigned int type to hour as parameter and assigns to attribute m_hour
\param hour - const ref of type int to hour
*/
    void setHour   ( const unsigned int & hour   );
/*!method setMinute takes const ref of unsigned int type to minute as parameter and assigns to attribute m_hour
\param minute - const ref of type int to minute
*/
    void setMinute ( const unsigned int & minute );

//!getters of attributes of class CTime
/*!method hour() returns attribute m_hour
\return unsigned int - returns the value of attribute m_hour
*/
    unsigned int hour   ( ) ;

/*!method minute() returns attribute m_minute
\return unsigned int - returns the value of attribute m_minute
*/
    unsigned int minute ( );
/*!method timm() returns attribute m_tim
\return time_t - returns the value of attribute m_tim ( holds absolute value of time calculated by localtime function from library time.h
*/
    time_t timm ( );
//! method isValidTime takes hour and minute and checks them for validation
//! Validation of time checks f.e. hour and minute cannot be negative number , hour <= 23 and minute <= 59

    bool isValidTime  ( const unsigned int & hour, const unsigned int & minute );

//! method calculate( const int & hour, const int & minute )
/*!calculates time in integer by localtime and mktime functions from library time.h. This value is useful in automated calculations
 \param hour  - const ref of type int to hour
 \param minute - const red if type int to minute
 */
    void calculate ( const int & hour, const int & minute );


//!Overloaded operator +
/*! overloaded operator calculates addition of minutes to object of CTime. Calculation is done by using localtime and mktime functions
 \param minutes - int value
 \return object of CTime
 */
    CTime & operator +  ( int minutes ) ;

//!Overloaded operator ==
    /*!Handles comparison between two CTime objects.
      \param other - a CTime object we are comparing with.
      \return true if this == other else false.
    */
    bool operator   ==  ( const CTime & other );

//!Overloaded operator <
/*!Handles comparison between two Time objects.
      \param other - a CTime object we are comparing with.
      \return true if this < other else returns false.
*/
    bool operator   <   ( const CTime & other );

    //!Overloaded operator >
/*!Handles comparison between two Time objects.
      \param other - a CTime object we are comparing with.
      \return true if this > other else returns false.
*/
    bool operator   >   ( const CTime & other );

    //!Overloaded operator >=
/*!Handles comparison between two Time objects.
      \param other - a CTime object we are comparing with.
      \return true if this >= other else returns false.
*/
    bool operator   >=  ( const CTime & other );

    //!Overloaded operator <=
/*!Handles comparison between two Time objects.
      \param other - a CTime object we are comparing with.
      \return true if this <= other else returns false.
*/
    bool operator   <=  ( const CTime & other );


//!Overloaded operator =
 /*!Handles a deep copy of the CTime object.
\param other - a CTime object we are copying from.
\return CTime object
*/
    CTime & operator  =  ( const CTime & other );

//!Overloaded operator <<
/*!Handles calculation with mktime and printing time in format
      \param other - a CTime object we are comparing with.
      \return true if this < other else returns false.
*/
    friend std::ostream & operator << ( std::ostream & out , const CTime & time );


};

#endif //CALENDAR_TIME_H
