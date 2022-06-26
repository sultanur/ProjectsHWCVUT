//
// Created by nuray on 19.5.22.
//
#include <string>
#include <iomanip>
#include "Register.hpp"


Register:: Register  ( )  { }
Register:: ~Register ( )  { }


std::vector <std::shared_ptr<CEventTypes > > Register::  dataBase( ) { return m_dataBase; }
void Register:: setDataBase ( const std::vector <std::shared_ptr<CEventTypes > > & vec ) { m_dataBase = vec; }

std::vector<std::shared_ptr<CEventTypes> >::iterator Register:: findByTime ( const CDate & date, const CTime & time ) {
    auto found = find_if ( m_dataBase.begin(), m_dataBase.end( ),
                          [&] ( const std::shared_ptr <CEventTypes> &evT ) {
                              return  ( ( evT->getEvent()->getCDate() == date  &&  evT->getEvent()->getCTime() == time  ) ||
                                        ( evT->getEvent()->getCDate() == date  &&  evT->getEvent()->finishTime() > time &&
                                         evT->getEvent()->getCTime() < time ) ) ;
                          } );
    return found;
}
std::vector<std::shared_ptr<CEventTypes> >::iterator Register:: findByTitle  ( const std::string & title ) {
    auto found = std::find_if (m_dataBase.begin(), m_dataBase.end(),
                               [&] ( const std::shared_ptr <CEventTypes> &a ){
                                   return ( ( a->getEvent()->title().compare ( title ) ) == 0  );
                               });
    return found;
}

void Register:: findByDate ( const CDate & date ) {
    for ( auto & k : m_dataBase) {
        if ( k->getEvent()->getCDate() == date )
            std::cout << k->getEvent()->title() <<" " << k->getEvent()->getCTime() << " " << k->getEvent()->finishTime() <<"\n";
    }

}
bool Register:: findInDB ( std::vector<std::shared_ptr<CEventTypes> >::iterator finding ) {
   if ( finding != m_dataBase.end() )
        return  true;
    else
        return false;
}

void Register::  printByType       ( const std::shared_ptr<CEventTypes> & evT ) const {
    int counter = 0;
    std::string  typeStr;
    bool exporting = false;
    for ( auto & elem: m_dataBase ) {
        elem->getEvent()->setExp( exporting );
        if ( typeid ( *elem ) == typeid ( *evT ) ) {
            typeStr = ( *elem ).getEvent( )->eventStrType( );
            std::cout << *( elem->getEvent( ) );
            counter++;
        }
    }
    if ( counter != 0 ) {
        std::cout    << "Overall "  << counter << " "
                    << typeStr <<" Event(s) \n" ;
    } else {
        std::cout  << "\nSorry, not found  " << typeid ( *evT).name() << "  in Calendar \n" ;
    }

}
bool Register::  printOccupiedTime ( const CDate & date ) const  {
    std::cout << "\nOccupied time for date " <<  date << ": \n\n";
    int counter = 0;
    for ( auto & elem : m_dataBase ) {
        if (date == elem->getEvent()->getCDate()) {
            counter++;
            std::cout << "Event " << elem->getEvent()->eventStrType() << "  ";
            std::cout << "Title " << elem->getEvent()->title() << "  ";
            std::cout << "from  " << elem->getEvent()->getCTime()
                      << " to " << elem->getEvent()->finishTime() << "\n";;
        }
    }
    if ( counter == 0 ) {
        std::cout  << "There is no Event(s) in your schedule for " << date << "\n" ;
        return false;
    }

    return true;
}

bool Register::  searchByPlace     ( const std::string & place ) const {
    auto foundPlace = std::find_if ( m_dataBase.begin(), m_dataBase.end( ),
                                    [&] ( const std::shared_ptr<CEventTypes > & a ) {
                                    return ( a->getEvent()->place().compare( place ) == 0 ); } );

    if ( foundPlace == m_dataBase.end ( ) ) {
        std::cout  << "Event in " << place << "  not found in Calendar\n"  ;
        return false;
    } else {
        std::cout  << "        Details of found Event: \n" ;
        std::cout << *( (*foundPlace)->getEvent() );

    }

    return true;
}
bool Register::  searchByTitle     ( const std::string & title ) {
    auto foundTitle = findByTitle ( title );

    if ( foundTitle == m_dataBase.end ( ) ) {
        std::cout<< "Event by Title " << title << "  not found in Calendar\n "  ;
        return false;
    } else {
        std::cout  << "        Details of found Event: \n" ;
        std::cout << *( ( *foundTitle )->getEvent() );
    }

    return true;

}


bool Register:: AddEvents ( const std::shared_ptr<CEventTypes> & evTypes ) {
    std::vector<std::shared_ptr<CEventTypes> >::iterator found;
    found = findByTime ( evTypes->getEvent()->getCDate(), evTypes->getEvent()->getCTime() );

    if ( found != m_dataBase.end() ) {
        return false;
    } else {
        m_dataBase.push_back ( evTypes );
    }
    return true;
}
Event Register::ImportEvents    ( Event ev ) {

    std::ifstream inFile;
    std::vector <std::string> participants;
    int numberParticipantsInt;
    std::string fileName = "doc/DataToImport.txt";
    std::string title, place, duration, numberParticipants , name ;
    std::string year, month, day, hour, minute;
    inFile.open ( fileName,  std::ios::in ) ;
    if ( !inFile ) {
        std::cout  << "\n\nThere is something went wrong. Couldn't open file. Please try again...  \n";
    }

    getline (inFile, title   );
    ev.setTitle ( title );

    getline (inFile,place    );
    ev.setPlace ( place );

    getline     ( inFile, year,  '-'    )  &&
    getline     ( inFile, month, '-'    )  &&
    getline     ( inFile, day );

    ev.setCDate ( CDate (std::stoi   ( day    ),
                            std::stoi   ( month  ),
                              std::stoi   ( year   ) ) );

    getline     ( inFile, hour,  ':'    )  &&
    getline     ( inFile, minute) ;
    ev.setCTime ( CTime ( std::stoi  ( hour   ),
                             std::stoi  ( minute ) ) );

    getline ( inFile,  duration );
    ev.setDuration ( std::stoi ( duration )  ) ;

    getline ( inFile,  numberParticipants ) ;
    numberParticipantsInt = std::stoi ( numberParticipants );
    ev.setNumberOfParticipants ( numberParticipantsInt );

    if ( numberParticipantsInt != 0 ) {
        for ( size_t i = 0; i < numberParticipantsInt; ++i ) {
            getline (inFile,name) ;
            participants.push_back ( name );
        }
       ev.setParticipants ( participants );
    }

    return ev;

}
bool Register:: deletingEvent   ( const CDate & date, const CTime & time ) {
    auto found = findByTime ( date, time );
    if ( found != m_dataBase.end( ) ) {
        m_dataBase.erase(( found ) );
        return true;
    }

    return false;

}

std::shared_ptr <Important_Event> Register:: setImportantEvent ( const std::string & notice,
                                                                 const std::shared_ptr<Event> & event   )  {
    auto ImportantEvent = std::make_shared<Important_Event>();
    ImportantEvent->setNotice ( notice );
    ImportantEvent->addEvent  ( notice, event );
    ImportantEvent->setEvent  (event );


    return ImportantEvent;
}
std::shared_ptr <MoveAble_Event>  Register:: setMoveAbleEvent  ( const int & movesLimit ,
                                                                 const std::shared_ptr<Event> & event   )  {

    auto MoveAbleEvent = std::make_shared<MoveAble_Event>();

    MoveAbleEvent->setEvent (event );
    MoveAbleEvent->setNumberMoves (movesLimit );
    MoveAbleEvent->addEvent ( movesLimit, event );

    return MoveAbleEvent;

}
std::shared_ptr <Optional_Event>  Register:: setOptionalEvent  ( const std::shared_ptr<Event> & event   )  {

    auto OptionalEvent = std::make_shared<Optional_Event>();
    OptionalEvent->setEvent  (event );
    OptionalEvent->addEvent  ( event );

    return OptionalEvent;
}