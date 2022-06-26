//
// Created by nuray on 1.5.22.
//

#ifndef CALENDAR_EVENT_H
#define CALENDAR_EVENT_H
#include "CCalendar.hpp"
#include "Time.hpp"
#include "CDate.hpp"
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <fstream>


//!class Event
/*! class Event contains quite big number of attributes which helps in dealing with events and scheduling them
 *
 *\param title - string value
 *\param startDate - object of CDate
 * \param startTime - object of CTime
 * \paran finishTime - result af addition to object of CDate and duration of event
 * \param place - string value
 * \param duration - int value
 * \param type - int value ( represents the main 3 types of Event)
 * \param recurrence - int value ( weekly - 1, every 14 days - 2 and monthly - 3)
 * \param recurrenceLimit -int value
 * \param eventStrType - string value name of event Type
 * \param numberOfParticipants - int
 * \param participants - vector of string, contains name of participants
 * \param exp - boolean value,It is used for uncoloring values in importing event data to file

 * */
class Event {

private:
    CDate m_startDate =  CDate  ( 0, 0 , 0 );
    CTime m_startTime =  CTime  ( 0 , 0 );
    CTime m_finishTime = CTime  (0,0 ) ;
    std::string m_title = "";
    std::string m_place = "";
    int m_duration;
    int m_type;
    int m_recurrence = 0;
    int m_recurrenceLimit = 0;
    std::string m_EventStrType = "";
    int m_numberOFParticipants = 0;
    std::vector <std::string >  m_participants;
    bool m_exp = false;


//--------------------------------------------------------------------------------------------------------------------//
public:

    //! Default constructor

    Event ( );

    //!Parametrized default constructor.
    /*!Takes object of Event and assigns it to all attributes (copies)
     *
     * @param other - object of Event
     */
    Event ( const Event & other ) ;
    Event ( CDate startDate, CTime startTime, CTime finishTime, std::string title , std::string place, int duration ,
            int type, int recurrence, int recurrenceLimit, std::string EventStrType,
            int numberOFParticipants, std::vector <std::string > participants , bool exp ) ;

    //!Method clone
    /*!This method creates exact clone of the shared_ptr<Event> object with all of the members.
      \return shared_ptr<Event> object of the clone.
    */
    std::shared_ptr<Event> clone () const;



//--------------------------------------------------------------------------------------------------------------------//
//! Getters of all attributes of class Event
/*!
 *
 * @return depends on types of attributes;
 */

    CDate getCDate      ( ) ;
    CTime getCTime      ( ) ;
    int   duration      ( ) ;
    int   type          ( ) ;
    int   recurrence    ( ) ;
    CTime finishTime    ( ) ;
    std::string title   ( ) ;
    std::string place   ( ) ;
    int recurrenceLimit ( ) ;
    std::string eventStrType ( ) ;
    int numberOfParticipants ( ) ;
    std::vector <std::string >  participants ( ) ;
    bool exp ();

//--------------------------------------------------------------------------------------------------------------------//
//!Setters of all Event attributes
/*! sets inputs  to attributes of Event
 *
 */
    void  setCDate          ( const CDate & date        ) ;
    void  setCTime          ( const CTime & tim         ) ;
    void  setFinishTime     ( const CTime & minutes     ) ;
    void  setTitle          ( const std::string & title ) ;
    void  setPlace          ( const std::string & place ) ;
    void  setDuration       ( const int & minutes       ) ;
    void  setType           ( const int & type          ) ;
    void  setRecurrence     ( const int & rec           ) ;
    void  setRecurrenceLimit( const int & limit         ) ;
    void  setEventStrType ( const std::string & strType ) ;
    void  setNumberOfParticipants ( const int & number  ) ;
    void  setParticipants ( const std::vector <std::string > & participants ) ;
    void setExp ( const bool & exp );

//--------------------------------------------------------------------------------------------------------------------//

    //!Overloaded operator =
    /*!Handles a deep copy of the CEvent object.
   \param other - Event object we are copying from.
   \return Event  object
   */
    Event & operator = ( const Event & other ) ;

    //!operator overloading <<
    /*!overloaded operator calls method print to print all attributes and
     * with consideration boolean attribute exp
     \param out - ostream value
      \param event - object of Event
     \return  objects value
     */
    friend std:: ostream & operator << ( std::ostream & out, const Event & event  );

    /*!Method print() is called by operator << and print out events with each attributes
* @param out  - ostream value
*/
    void print ( std::ostream & out ) const;

    //! Method exportEv( std::ostream  & out )
    /*! This method just copy of method print, where each elements are prepared for printing out, but uncolored,for importing to file
     * @param out
     */
    void exportEv ( std::ostream  & out ) const;

    /*!Overloaded operator <
*Method compares two object by its Date and Time
* @param other  - object of CEvent
* @return  true if this < object of Event Type
*/
    bool operator <  ( const Event & other ) ;


    /*!Overloaded operator >
*Method compares two object by its Date and Time
* @param other  - object of CEvent
* @return  true if this > object of Event Type
*/
    bool operator >  ( const Event & other ) ;


    /*!Overloaded operator <=
*Method compares two object by its Date and Time
* @param other  - object of CEvent
* @return  true if this <= object of Event Type
*/
    bool operator <= ( const Event & other ) ;


    /*!Overloaded operator >=
*Method compares two object by its Date and Time
* @param other  - object of CEvent
* @return  true if this >= object of Event Type
*/
    bool operator >= ( const Event & other ) ;



    /*!Overloaded operator ==
*Method compares two object by its Date and Time
* @param other  - object of CEvent
* @return  true if this == object of Event Type
*/
    bool operator == ( const Event & other ) ;

};

//--------------------------------------------------------------------------------------------------------------------//

#endif //CALENDAR_EVENT_H
