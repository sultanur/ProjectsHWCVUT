//
// Created by nuray on 1.5.22.
//

#ifndef CALENDAR_EXPORT_EVENTS_H
#define CALENDAR_EXPORT_EVENTS_H
#include <cstddef>
#include <memory>
#include <iostream>
#include <fstream>
#include "Register.hpp"



//!Abstract Parent Class ExportFormat responsible for exporting to files  schedules from Calendar depending on type or all events
class ExportFormat {

public:
    //!Default Destructor
    virtual ~ExportFormat ( );

    //! Method to export events by type to file
    virtual void  exportEventsByType ( const std::vector <std::shared_ptr<CEventTypes>> & vecDBS,
                                       const std::shared_ptr<CEventTypes> & evT )  = 0;
    //! Method to export all events to file
    virtual void  exportAllEvents    ( const std::vector <std::shared_ptr<CEventTypes>> & vecDBS )  = 0;

};

//!Derived class CSVFileFormat, handles both inherited methods.
class CSVFileFormat: public ExportFormat {

public:
    //!Default constructor
    CSVFileFormat ( ) ;

    //! Method to export events by type to file in csv format
    void   exportEventsByType ( const std::vector <std::shared_ptr<CEventTypes>> & vecDBS,
                                const std::shared_ptr<CEventTypes> & evT  ) override;

    //! Method to export all events to file in csv format
    void   exportAllEvents    ( const std::vector <std::shared_ptr<CEventTypes>> & vecDBS ) override ;

};

class CTextFormat : public ExportFormat {

public:
    CTextFormat( );


//! Method to export events by type to file in txt format
    void  exportEventsByType (  const std::vector <std::shared_ptr<CEventTypes>> & vecDBS,
                                const std::shared_ptr<CEventTypes> & evT  ) override;

    //! Method to export all events to file in txt format
    void  exportAllEvents    (  const std::vector <std::shared_ptr<CEventTypes>> & vecDBS ) override;

};

#endif //CALENDAR_EXPORT_EVENTS_H
