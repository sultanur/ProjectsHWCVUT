//
// Created by nuray on 1.5.22.
//

#include "Event.hpp"
#include "Time.hpp"
#include <algorithm>
#include <iomanip>


//--------------------------------------------------------------------------------------------------------------------//

Event:: Event ( ) { }
Event:: Event  ( const Event & other )  {

    m_startDate             = other.m_startDate;
    m_startTime             = other.m_startTime;
    m_finishTime            = other.m_finishTime;
    m_title                 = other.m_title;
    m_place                 = other.m_place;
    m_duration              = other.m_duration;
    m_type                  = other.m_type;
    m_recurrence            = other.m_recurrence;
    m_recurrenceLimit       = other.m_recurrenceLimit;
    m_EventStrType          = other.m_EventStrType;
    m_numberOFParticipants  = other.m_numberOFParticipants;
    m_participants          = other.m_participants;
    m_exp                   = other.m_exp;

}
Event:: Event ( CDate startDate, CTime startTime, CTime finishTime,  std::string title , std::string place, int duration ,
                int type, int recurrence, int recurrenceLimit, std::string EventStrType,
                int numberOFParticipants, std::vector <std::string > participants, bool exp )
                {
        this->m_startDate = startDate;
        this->m_startTime = startTime;
        this->m_finishTime = finishTime;
        this->m_title = title;
        this->m_place = place;
        this->m_duration = duration;
        this->m_type = type;
        this->m_recurrence = recurrence;
        this->m_recurrenceLimit = recurrenceLimit;
        this->m_EventStrType = EventStrType;
        this->m_numberOFParticipants = numberOFParticipants;
        this->m_participants = participants;
        this->m_exp = exp;
}

std::shared_ptr<Event> Event::clone () const {
    Event temp ( m_startDate, m_startTime, m_finishTime,  m_title , m_place, m_duration ,
                 m_type,  m_recurrence,  m_recurrenceLimit,  m_EventStrType,
                 m_numberOFParticipants,  m_participants , m_exp );

    return std::make_shared<Event> ( temp );
}


//--------------------------------------------------------------------------------------------------------------------//

CDate Event:: getCDate    ( )  { return m_startDate             ;}
CTime Event:: getCTime    ( )  { return m_startTime             ;}
CTime Event:: finishTime  ( )  { return m_finishTime            ;}
std::string Event:: title ( )  { return m_title                 ;}
std::string Event:: place ( )  { return  m_place                ;}
int Event:: duration      ( )  { return m_duration              ;}
int Event:: type          ( )  { return m_type                  ;}
int Event:: recurrence    ( )  { return m_recurrence            ;}
int Event:: recurrenceLimit      ( ) { return m_recurrenceLimit ;}
std::string Event:: eventStrType ( ) { return  m_EventStrType   ;}
int Event:: numberOfParticipants ( ) { return m_numberOFParticipants  ;}
std::vector <std::string > Event:: participants ( ) { return m_participants ;}
bool Event:: exp ( ) { return m_exp; }

//--------------------------------------------------------------------------------------------------------------------//

void Event:: setCDate           ( const CDate & date        )   { m_startDate =  date               ;}
void Event:: setCTime           ( const CTime & tim         )   { m_startTime =  tim                ;}
void Event:: setFinishTime      ( const CTime & tim         )   { m_finishTime = tim                ;}
void Event:: setTitle           ( const std::string & title )   { m_title = title                   ;}
void Event:: setPlace           ( const std::string & place )   { m_place = place                   ;}
void Event:: setDuration        ( const int & minutes       )   { m_duration = minutes              ;}
void Event:: setType            ( const int & type          )   { m_type = type                     ;}
void Event:: setRecurrence      ( const int & rec           )   { m_recurrence = rec                ;}
void Event:: setRecurrenceLimit ( const int & limit         )   { m_recurrenceLimit = limit         ;}
void Event:: setEventStrType    ( const std::string & strType ) { m_EventStrType = strType          ;}
void Event:: setNumberOfParticipants ( const int & number)      { m_numberOFParticipants = number   ;}
void Event:: setExp ( const bool & exp ) { m_exp = exp; }
void Event:: setParticipants    ( const std::vector <std::string > & participants )
{
    m_participants = participants;
  }



//--------------------------------------------------------------------------------------------------------------------//

Event & Event:: operator =   ( const Event & other ) {
    if ( this == & other ) { return *this; }
    this->m_startDate = other.m_startDate;
    this->m_startTime = other.m_startTime;
    this->m_title = other.m_title;
    this->m_place = other.m_place;
    this->m_duration = other.m_duration;
    this->m_type = other.m_type;
    this->m_recurrence = other.m_recurrence;
    this->m_recurrenceLimit = other.m_recurrenceLimit;
    this->m_EventStrType = other.m_EventStrType;
    this->m_numberOFParticipants = other.m_numberOFParticipants;
    this->m_participants = other.m_participants;
    bool m_exp = other.m_exp;
    return *this;
}
std:: ostream & operator <<  ( std::ostream & out , const Event & event ) {
    if ( event.m_exp)
        event.exportEv( out );
    else
        event.print( out );

    return out;
}
void Event:: print ( std::ostream & out ) const      {
    int counter = 1;
    out <<"Title:                  "             << m_title         << "\n";
    out <<"Type:                   "             << m_EventStrType  << "\n";
    out <<"Place:                  "             << m_place         << "\n";
    out <<"Date:                   "             << m_startDate     << "\n";
    out <<"Start Time:             "             << m_startTime     << "\n";
    out <<"Duration:               "             << std::setfill( '0' ) << std::setw( 2 ) << m_duration << " minutes" << "\n";
    out <<"Finish Time:            "             << m_finishTime     << "\n";
    out <<"Number of Participants: "             << m_numberOFParticipants << "\n";
    if ( m_numberOFParticipants != 0 ) {
        out  << "Participant's name:  " << "\n";
        for ( auto & name: m_participants ) {
            out << "                     " << counter << ") " << name << "\n";
            counter++;
        }
    }
    out << "\n";
}
void Event:: exportEv ( std::ostream & out ) const   {
    int counter = 1;
    out << "Title:                  "           <<  m_title         << "\n";
    out << "Type:                   "           <<  m_EventStrType  << "\n";
    out << "Place:                  "           <<  m_place         << "\n";
    out << "Date:                   "           <<  m_startDate     << "\n";
    out << "Start Time:             "           <<  m_startTime     << "\n";
    out << "Duration:               "           <<  std::setfill( '0' ) << std::setw( 2 ) << m_duration << " minutes" << "\n";
    out << "Finish Time:            "           <<  m_finishTime     << "\n";
    out << "Number of Participants: "           <<  m_numberOFParticipants << "\n";
    if ( m_numberOFParticipants != 0 ) {
        out << "Participant's name:  " << "\n";
        for ( auto & name: m_participants ) {
            out << "                     " << counter << ") " <<  name << "\n";
            counter++;
        }
    }
    out << "\n";


}




bool Event:: operator <  ( const Event & other )  {
    if ( this->m_startDate == other.m_startDate)
        return ( this->m_startTime < other.m_startTime );
    else return this->m_startDate < other.m_startDate;
}
bool Event:: operator >  ( const Event & other )  {
    if ( this->m_startDate == other.m_startDate)
        return ( this->m_startTime > other.m_startTime );
    else return this->m_startDate > other.m_startDate;
}
bool Event:: operator >= ( const Event & other )  {
    if ( this->m_startDate == other.m_startDate)
        return ( this->m_startTime >= other.m_startTime );
    else return this->m_startDate >= other.m_startDate;
}
bool Event:: operator <= ( const Event & other )  {
    if ( this->m_startDate == other.m_startDate)
        return ( this->m_startTime <= other.m_startTime );
    else return this->m_startDate <= other.m_startDate;
}
bool Event:: operator == ( const Event & other )  {
return ( this->m_startDate == other.m_startDate
        && this->m_startTime == other.m_startTime );
}


//--------------------------------------------------------------------------------------------------------------------//
