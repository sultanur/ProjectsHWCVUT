//
// Created by nuray on 19.5.22.
//

#ifndef CALENDAR_REGISTER_H
#define CALENDAR_REGISTER_H
#include "CDate.hpp"
#include "Time.hpp"
#include "CEventTypes.hpp"
#include <map>
#include <vector>

//! class Register
/*!class Register handles the main container, provides some functionality. All functions works with main database,
 * such as adding into container, searching, deleting, importing.
 * Attribute of this class is vector of shared_ptr ov type CEventTypes
 */
class Register {

private:
    std::vector<std::shared_ptr<CEventTypes> >   m_dataBase;

public:
    //!Default constructor calls when object of Register is created
    Register  ( ) ;

    //!Default destructor
    ~Register ( ) ;

    //!Getter and setter
    /*!getter dataBase() returns m_dataBase (vector)
     *
     * @return  vector of shared_ptr of type CEventTypes
     */
    std::vector <std::shared_ptr<CEventTypes > > dataBase ( ) ;

    /*!Setter setDataBase ( ) takes vector and assigns to attribute  of class Register
     *
     * @param other  vector of shared_ptr of type Event
     */
    void setDataBase    ( const std::vector <std::shared_ptr<CEventTypes > > & other ) ;


    //! Method to find event in main container m_dataBase by date and time
    std::vector<std::shared_ptr<CEventTypes> >::iterator findByTime ( const CDate & date, const CTime & time );

    //! Method to find event in main container m_dataBase by date title
    std::vector<std::shared_ptr<CEventTypes> >::iterator findByTitle  ( const std::string & title ) ;

    bool  findInDB ( std::vector<std::shared_ptr<CEventTypes> >::iterator finding )  ;

    void findByDate ( const CDate & date );
    //! Method compares typeid's of each element and parameter of this method and prints out its  events
    /*!
     *
     * @param evT  shared_ptr of type CEventTypes
     */
    void printByType        ( const std::shared_ptr<CEventTypes> & evT ) const;

    //! Method compares typeid's of each element and parameter of this method and prints out its  events
    bool printOccupiedTime  ( const CDate & date ) const;

    //!tTakes parameter place and searches in m_database event with that title
    /*!
     *
     * @param place  - string value
     * @return returns true if finds in m_database, false otherwise
     */
    bool  searchByPlace     ( const std::string & place   ) const;

    //!tTakes parameter place and searches in m_database event with that title
    /*!
     * @param title - string value
     * @return true if finds in m_database, false otherwise
     */
    bool  searchByTitle     ( const std::string & title   ) ;

    //! Adds objects of type CEventTypes to m_database, before checks if searching date and time are not occupied
    /*!
     *
     * @param evTypes shared_ptr of type CEvenTypes
     * @return true if there is no event with the same date and time and added to m_dataBase.Otherwise returns false
     */
    bool AddEvents ( const std::shared_ptr<CEventTypes> & evTypes ) ;
    //! Method ImportEvents handles work with file, opening it, formatting and writing all values to matched variables
    Event ImportEvents (  Event ev  );

    //!Methd finds event by time and date, then deletes it from m_dataBase
    /*!
     *
     * @param date - objects of type CDate
     * @param time - object of type CTime
     * @return return true if finds event and deletes it, otherwise false
     */
    bool deletingEvent ( const CDate & date, const CTime & time ) ;



//!Helper Method to setup local attributes of created ImportantEvents

    std::shared_ptr <Important_Event> setImportantEvent  ( const std::string & notice,
                                                           const std::shared_ptr<Event> & event );

//!Helper Method to setup local attributes of created MovAbleEvents
    std::shared_ptr <MoveAble_Event>  setMoveAbleEvent   ( const int & movesLimit ,
                                                           const std::shared_ptr<Event> & event   ) ;

//!Helper Method to setup local attributes of created OptionalEvents
    std::shared_ptr <Optional_Event>  setOptionalEvent   ( const std::shared_ptr<Event> & event );




};


#endif //CALENDAR_REGISTER_H
