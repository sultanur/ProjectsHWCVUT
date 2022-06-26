//
// Created by nuray on 17.5.22.
//
#include "Event.hpp"
#include <string>
#include <exception>
#include <vector>
#include <iomanip>
#include <algorithm>


//!class CEvenTypes is abstract parent class
/*! class CEvenTypes is designed to present 3 different types of events: Important, MoveAble and Optional
 * Each types has own variables, methods plus to inherited from parent class.
 * The main attribute of basic class is shared pointer to class Event, through which  all three types of event are formed
 *
 */
class CEventTypes {

protected:
    std::shared_ptr<Event> m_event;

public:

    //! virtual destructor
    virtual ~CEventTypes( ) { }

    /*! Getter of attribute m_event getEvent(),
    \return shared_ptr of type Event
    */
    std::shared_ptr<Event>  getEvent  ( ) const ;

    /*!Setter setEvent
     * Takes shared_ptr ev and assigns to attribute m_event
     * @param ev -shared_ptr of type Event
     */
    void  setEvent  ( const std::shared_ptr<Event> & ev ) ;

    /*!Overloaded operator <<
     * operator << calls method print and provides objects of ostream class
     * @param out  - object of class ostream
     * @param evTypes  - object of class CEvenTypes
     * @return  ostream output with the information about the eventTypes.
     */
    friend std::ostream & operator << ( std::ostream & out, const CEventTypes & evTypes );

    //!Overloaded operator =
    /*!Handles a copy of the CEvenTypes object.
   \param other - a CEvenTypes object we are copying from.
   \return CEvenTypes object
   */
    CEventTypes & operator = ( const CEventTypes & other ) ;

    /*!Overloaded operator ==
     *Method compares two object typeid's
     * @param evType  - object of CEventTypes
     * @return  true if this and CEventTypes object's typeid's are  equal
     */
    bool  operator == (  CEventTypes & evType ) const;

/*!Pure virtual method print
 * @param out - value of ostream
 */
    virtual void print ( std::ostream & out ) const  = 0;

    /*!Pure virtual method create. Creates clone of  CEventTypes' object
   * \return  shared pointer to CEventTypes
   */
    virtual std::shared_ptr<CEventTypes> create ( ) const = 0;

    /*!Pure virtual method setChanges.
     * calculates changes in event dates
     * @param changed - boolean value, marks the changes done or not to parameter Event
     * @param event  - shared pointer of type Event, which will be changed ( its time and date)
     * @param date - object of type CDate, is a new date for event to be changed
     * @param time - object of type CTime is a new time for event to be changed
     * @return  returns shared_ptr of type CEventType to add the result to main database
     */
    virtual std::shared_ptr<CEventTypes> setChanges ( bool & changed ,
                                                      const std::shared_ptr<CEventTypes> & event ,
                                                      const CDate & date, const CTime & time  ) const   = 0;


};
//-----------------------------------------------------------------------------------------------------------//

/*!Derived class Important_Event
 * This type of Event has own attribute notice of Importance, the main difference from other types is that cannot be
 * changed or moved
 * Has 2 attributes: string notice, vector of pair ( notice and shared pointer of type Event)
 */
class Important_Event : public CEventTypes {

protected:
    std::string m_notice;
    std::vector <std::pair<std::string, std::shared_ptr<Event>>> m_ImportantEvents;

public:
    /*!Default destructor
     */
    Important_Event( ) = default;

    /*! Getter notice()
     * @return value of attribute m_notice
     */
    std::string notice ( ) ;

    /*!Setter SetNotice()
     * Takes parameter string and assigns to attribute m_notice
     * @param notice
     */
    void setNotice ( std::string notice );


    /*!Overloaded operator ==
     *Method compares two object typeid's and compares after dynamic casting  parameter of CEventTypes  to Important_Event typd
     * @param other  - object of CEventTypes
     * @return  true if this and Important_Event object's typeid's are  equal
     */
    bool operator == ( const CEventTypes & other ) const;


   /*!Method print() is called by operator << and print out events of type Important in designed format with also own attributes
    * @param out  - ostream value
    */
    void print ( std::ostream & out ) const override;

    //!Method create
    /*!This method creates exact clone of the shared_ptr<CEventTypes> object with all of the members.
      \return shared_ptr<CEventTypes> object of the clone.
    */
    std::shared_ptr<CEventTypes> create (  ) const override;

    //! Method addEvent()
    /*! Takes 2 parameters : notice of Importance and shared pointer of type Event and adds to own container m_ImportantEvents
     * @param notice - string value
     * @param evT  - shared_ptr of type Event
     * @return  returns object of Important_Event
     */
    Important_Event & addEvent ( const std::string & notice,
                                 const std::shared_ptr<Event> & evT  );

    /*! Override  method setChanges.
 * calculates changes in event dates. Important events are forbidden from changes
 * @param changed - boolean value, marks the changes done or not to parameter Event
 * @param event  - shared pointer of type Event, which will be changed ( its time and date)
 * @param date - object of type CDate, is a new date for event to be changed
 * @param time - object of type CTime is a new time for event to be changed
 * @return  returns shared_ptr of type CEventType to add the result to main database
 */
    std::shared_ptr<CEventTypes> setChanges (   bool & changed,
                                                const std::shared_ptr<CEventTypes> & event ,
                                                const CDate & date, const CTime & time ) const override;

};

//------------------------------------------------------------------------------------------------------------------------------------------------------//
/*!Derived class MoveAble_Event
 * This type of Event has own attribute number of Moves of Importance, the main difference from other types is that changes are restricted by parameter
 * Has 2 attributes: int numberOfMoves, vector of pair ( numberOfMoves and shared pointer of type Event)
 */

class MoveAble_Event : public CEventTypes {

protected:
    int m_numberOFMoves = 0;
    std::vector <std::pair < int, std::shared_ptr<Event> >> m_MoveAbleEvents;

public:

    /*!Default destructor
  */
    MoveAble_Event ( ) = default;

    //! Setter
    /*!Method setNumberMoves takes int and assigns to local attribute m_numberOfMoves
     *
     * @param moves  - number of Moves
     */
    void setNumberMoves ( const int & moves );

    //! Setter
    /*!movesNumber ()
     *
     * @return local variable m_numberOFMoves
     */
    int movesNumber ( );


    /*!Overloaded operator ==
 *Method compares two object typeid's and compares after dynamic casting  parameter of CEventTypes  to MoveAble_Event type
 * @param other  - object of CEventTypes
 * @return  true if this and MoveAble_Event object's typeid's are  equal
 */
    bool operator == ( const CEventTypes & other ) const;

    /*!Method print() is called by operator << and print out events of type MoveAble_Event in designed format additionally with own attributes
    * @param out  - ostream value
    */
    void print ( std::ostream & out ) const override ;


    //!Method create
    /*!This method creates exact clone of the shared_ptr<CEventTypes> object with all of the members.
      \return shared_ptr<CEventTypes> object of the clone.
    */
    std::shared_ptr<CEventTypes>  create ( ) const override ;

    //! Method addEvent()
    /*! Takes 2 parameters : numberOfMoves and shared pointer of type Event and adds to own container m_MoveAbleEvents
     * @param notice - string value
     * @param evT  - shared_ptr of type Event
     * @return  returns object of Important_Event
     */
    MoveAble_Event & addEvent ( const int & movesLimit,
                                const std::shared_ptr<Event> & evT  ) ;


    /*! Override  method setChanges.
* calculates changes in event dates. MoveAble events are restricted from changes and moves by attribute NumberOfMoves
* @param changed - boolean value, marks the changes done or not to parameter Event
* @param event  - shared pointer of type Event, which will be changed ( its time and date)
* @param date - object of type CDate, is a new date for event to be changed
* @param time - object of type CTime is a new time for event to be changed
* @return  returns shared_ptr of type CEventType to add the result to main database
*/
    std::shared_ptr<CEventTypes> setChanges (   bool & changed ,
                                                const std::shared_ptr<CEventTypes> & event ,
                                                const CDate & date, const CTime & time  ) const override;

};

//---------------------------------------------------------------------------//

//!derived class Optional_Event holds events without any restrictions and rules
/*!class Optional_Event has own container m_Optional_Events.
 * All methods are inherited from base class additionally has static override method ( differs in returns type)
 */

class Optional_Event : public CEventTypes {

protected:
    std::vector <std::shared_ptr<Event> > m_OptionalEvents;

public:

    /*!Default destructor
*/
    Optional_Event( ) = default;

    /*!Overloaded operator ==
*Method compares two object typeid's and compares after dynamic casting  parameter of CEventTypes  to Optional type
* @param other  - object of CEventTypes
* @return  true if this and Optional_Event object's typeid's are  equal
*/
    bool operator == ( const CEventTypes & other ) const;


    /*!Method print() is called by operator << and print out events of type Optional_Event in designed format additionally with own attributes
 * @param out  - ostream value
 */
    void print ( std::ostream & out ) const override ;

    //!Method create
    /*!This method creates exact clone of the shared_ptr<CEventTypes> object with all of the members.
      \return shared_ptr<CEventTypes> object of the clone.
    */
    std::shared_ptr<CEventTypes>  create (  ) const override;


    //! Method addEvent()
    /*! Takes 1 parameter - shared pointer of type Event and adds to own container m_OptionalEvents
     * @param notice - string value
     * @param evT  - shared_ptr of type Event
     * @return  returns object of Important_Event
     */
    Optional_Event & addEvent ( const std::shared_ptr<Event> & evT  ) ;


    /*! Override  method setChanges.
* calculates changes in event dates.
* @param changed - boolean value, marks the changes done or not to parameter Event
* @param event  - shared pointer of type Event, which will be changed ( its time and date)
* @param date - object of type CDate, is a new date for event to be changed
* @param time - object of type CTime is a new time for event to be changed
* @return  returns shared_ptr of type CEventType to add the result to main database
*/
    std::shared_ptr<CEventTypes> setChanges (   bool & changed ,
                                                const std::shared_ptr<CEventTypes> & event ,
                                                const CDate & date, const CTime & time ) const override;


};


