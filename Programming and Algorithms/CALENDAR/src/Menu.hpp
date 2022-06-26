//
// Created by nuray on 1.5.22.
//

#ifndef CALENDAR_MENU_H
#define CALENDAR_MENU_H
#include "Register.hpp"
#include "ExportEvents.hpp"
#include "CDate.hpp"
#include "Time.hpp"
#include "Register.hpp"

class Menu {

public:
//!Default constructor
    Menu ( ) ;
//! Menu of commands,
/*!Implementation of interface, including commands
 * Has 1 attribute - shared_ptr of type  Register which provides access to main database in this project
 */

//! prints to the screen word Calendar and welcome message
    void welcome();

    //!Displays all name of commands
    void displayMenu ( void );

    //!Cals all implemented functions
    void MainMenu    ( void ) ;

    //!Method to print out monthly Calendar
    void monthlyCalendar ( );

    //!Method to print out weekly Calendar
    void weeklyCalendar  ( );

    //!Method to print outdayly Calendar
    void dailyCalendar   ( );

    //! This method handles interaction with user and by reading data from user created event with all features and attributes
    void readCreateEvent    ( ) ;

    //! Method searchByPlace  reads user input ( place ) and calls method searchByTitle from class Register

    void searchEventByPlace ( ) const;

    //! Method searchByPlace  reads user input ( title ) and calls method searchByTitle from class Register
    void searchEventByTitle ( ) const;

    /*!Method handles exporting to files. Reads user input related to exporting files and creates objects of class ExportFormat
     * and calls its method to export
   */
    void exportEvents       ( );

    /*!Method importEvent handles file,  user input, assigns all imported date to variables, assigns new rules
     * and restrictions from user and saves the data.
     */
    void importEvent        ( );

    /*!Method handles time changes for events. There are 2 types of changes: to free time slot or occupied time slot.
     * in case of changing time to occupied, method handles movement of event and placing to his/her place intended to change event.
    !*/
    void setTimeChange      ( );

    //!method handles printing out event by type
    void printEventByType   ( );
    //!Method handles finding event by date and time in m_database then handles deletion of that event,
    void deleteEvent        ( );



    //!Method handles user input all parameters of Date and creates CDate object
    CDate readDate  ( ) ;

    //!Method handles user input all parameters of Date and creates CDate object
    CTime readTime  ( ) ;

    //!Method helps to validate created object of CDate from user input
    CTime enterTime (  CTime  enterTime );

    //!Method helps to validate created object of CDate from user input
    CDate enterDate (  CDate  enterDate );

    //!Method to check if string contains integer chars
    bool isNumber   ( const std::string& input ) const ;

    //!Methods handles reading user input and as result to set up  type for  event
    int  choseType      ( int  type  );

    //!Methods handles reading user input and as result to set up  Recurrence Cycle for  event
    int  choseRecCycle  ( int recCycle );

    //!Methods handles reading user input and as result to set up  Recurrence Limit for  event
    std::string  setRecLimit ( std::string recLimit );

    //!Methods handles reading user input and as result to set up  Duration of event  for  event
    std::string  setDuration ( std::string duration );

    //!Methods handles reading user input on participants and adds it to vector of participants
    std::vector <std::string> addingParticipants (  bool & responseExit, std::vector <std::string> & participants );

    //! Method created Important Event and recurrence of it on user provided info
    void  CreateSaveImportantEvent ( const Event & event );

    //! Method created MovAble Event and recurrence of it on user provided info
    void  CreateSaveMovAbleEvent   ( const Event & event );

    //! Method created Optional Event and recurrence of it on user provided info
    void  CreateSaveOptionalEvent  ( const Event & event );

    //!Method to display created Event
    void displayCreatedEvent ( const std::shared_ptr<CEventTypes> & event ) const ;

    //!Method saves created event related on users response
    bool saveCreatedEvent    ( const std::shared_ptr<CEventTypes> & event );


    std::shared_ptr<Register> reg  = std::make_shared<Register>()  ;




};


#endif //CALENDAR_MENU_H