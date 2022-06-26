//
// Created by nuray on 17.5.22.
//

#ifndef CALENDAR_CEVENT_H
#define CALENDAR_CEVENT_H
#include "CEventTypes.hpp"


std::shared_ptr<Event>  CEventTypes:: getEvent ( )  const { return m_event; }
void CEventTypes:: setEvent ( const std::shared_ptr<Event> & ev )  { m_event = ev; }


CEventTypes & CEventTypes:: operator = ( const CEventTypes & other )  {
    this->m_event = other.m_event;
    return *this;
}
std::ostream & operator  <<  ( std::ostream & out, const CEventTypes & evTypes )  {
    evTypes.print( out );
    return out;
}
bool CEventTypes:: operator ==  ( CEventTypes & obj ) const  {
    return  ( typeid ( *this )  == typeid ( obj ) );
}

//----------------------------------------------------------------------------------------------------------//

std::string Important_Event:: notice ( )  { return m_notice ; }
void Important_Event:: setNotice ( std::string notice ) { m_notice = notice; }

bool Important_Event::operator == ( const CEventTypes & other ) const {
    return ( typeid ( *this ) == typeid ( other )
             && m_ImportantEvents == dynamic_cast<const Important_Event &> (other).m_ImportantEvents );
}

std::shared_ptr<CEventTypes> Important_Event :: create( ) const {
    return std::make_shared<Important_Event>(*this );
}

Important_Event & Important_Event:: addEvent ( const std::string & notice,
                                               const std::shared_ptr<Event> & evT  )
                                               {
    m_ImportantEvents.push_back ( std::make_pair ( notice, evT ) );
    return *this;
}

void Important_Event:: print ( std::ostream & out ) const  {
    out  << "\n---------------IMPORTANT EVENT---------------\n";

    for ( auto & elem : m_ImportantEvents ) {
        out  << "Notice:                 " << elem.first;
        out <<"\n";
        out << *( elem.second );
    }
}

std::shared_ptr<CEventTypes> Important_Event:: setChanges ( bool & changed, const std::shared_ptr<CEventTypes> & event ,  const CDate & date, const CTime & time  ) const {
    std::cout  << "It is Important Event, cannot make any changes\n" ;
    changed = false;
    return event;

}

//----------------------------------------------------------------------------------------------------------//

void MoveAble_Event :: setNumberMoves ( const int & moves ) { m_numberOFMoves = moves ;}
int MoveAble_Event :: movesNumber () { return m_numberOFMoves; }

bool MoveAble_Event::operator == ( const CEventTypes & other ) const {
    return ( typeid ( *this ) == typeid ( other )
             && m_MoveAbleEvents == dynamic_cast<const MoveAble_Event &> ( other ).m_MoveAbleEvents );
}


std::shared_ptr<CEventTypes> MoveAble_Event:: create ( ) const  {
    return std::make_shared<MoveAble_Event> ( *this );

}

MoveAble_Event & MoveAble_Event :: addEvent ( const int & movesLimit,
                                              const std::shared_ptr<Event> & evT  ) {
    m_MoveAbleEvents.push_back( std::make_pair ( movesLimit,  evT ) );
    return *this;
}

void MoveAble_Event :: print ( std::ostream & out ) const {
    out  << "\n------------------MOVABLE EVENT------------------ \n";

    for ( auto & elem : m_MoveAbleEvents ) {
        out  << "Moves Limit:            " << elem.first;
        out <<"\n";
        out << *( elem.second );
    }
}


std::shared_ptr<CEventTypes> MoveAble_Event:: setChanges (  bool & changed, const std::shared_ptr<CEventTypes> & event ,
                                                            const CDate & date, const CTime & time ) const {
    std::shared_ptr<MoveAble_Event> castEvent = std::dynamic_pointer_cast<MoveAble_Event> ( event );
    std::cout << "MOVEABLE EVENT\n";
    std::string response;

    if ( castEvent->m_numberOFMoves != 0 ) {
        castEvent->m_numberOFMoves--;
        castEvent->getEvent()->setCDate(date);
        castEvent->getEvent()->setCTime(time);
        castEvent->getEvent()->setFinishTime(castEvent->getEvent()->getCTime() + castEvent->getEvent()->duration());
     } else {
        std::cout  << "There is 0 moves for this event \n" ;
        changed = false;
        return event;
    }

    std::cout <<  "Event moved successfully to a new date and time\n" ;
    std::cout <<  "Display event with a new date and time? [Y|N] \n" ;
    getline (std::cin, response );
    if ( response == "N" || response == "n" || !std::cin ) {
        std::cin.clear();
        changed = true;
    } else {
          std::cout  << "\n"  << "Moves limit:            " <<  castEvent->m_numberOFMoves << "\n"  ;
          std::cout  << *( castEvent->getEvent() ) << "\n";
          changed = true;
          }

        return castEvent;
    }

//----------------------------------------------------------------------------------------------------------//


std::shared_ptr<CEventTypes>  Optional_Event:: create (  ) const  {
    return  std::make_shared<Optional_Event> ( *this );
}

Optional_Event &  Optional_Event :: addEvent (  const std::shared_ptr<Event> & evT )    {
    m_OptionalEvents.push_back( evT );
    return *this;
}

void Optional_Event :: print ( std::ostream & out ) const    {
    out   << "\n-------------------OPTIONAL EVENT-------------------\n" ;
    for ( auto & elem : m_OptionalEvents ) {
        out << *elem;
    }
}

std::shared_ptr<CEventTypes> Optional_Event:: setChanges ( bool & changed , const std::shared_ptr<CEventTypes> & event ,
                                                            const CDate & date, const CTime & time ) const  {
    std::string response;
    std::shared_ptr<Optional_Event> castEvent = std::dynamic_pointer_cast<Optional_Event> ( event );
    std:: cout  <<  "Setting changes for Optional EVent \n";
    castEvent->getEvent()->setCDate ( date );
    castEvent->getEvent()->setCTime (time );
    castEvent->getEvent()->setFinishTime(castEvent->getEvent()->getCTime() + castEvent->getEvent()->duration() );

    std::cout  << "Event moved successfully to a new date and time\n" ;
    std::cout  << "Display event with a new date and time? [Y|N] \n" ;
    getline (std::cin, response );
    if ( response == "N" || response == "n" || !std::cin ) {
        std::cin.clear();
        changed = true;
    } else {
        changed = true;
        std::cout  << "\n" << *( castEvent->getEvent() ) << "\n";
    }

    return castEvent;
}


//-----------------------------------------------------------------------------------------------------------//



#endif //CALENDAR_CEVENT_H
