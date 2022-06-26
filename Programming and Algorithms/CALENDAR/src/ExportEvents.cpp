//
// Created by nuray on 1.5.22.
//
#include "ExportEvents.hpp"



ExportFormat::  ~ExportFormat ( ) { }


//-----------------------------------------------------------------------------------------------------//

CTextFormat:: CTextFormat ( ) { }

void CTextFormat:: exportEventsByType ( const std::vector <std::shared_ptr<CEventTypes>> & vecDBS,
                                        const std::shared_ptr<CEventTypes> & evT )  {
    std::fstream outFile;
    std::string type;
    int size = 0;
    outFile.open("ExportByTypeTXT.txt", std::ios::out | std::ios::binary );
    if ( !outFile ) {
        return;
    } else {
        bool uncoloredPrint = true;
        for ( auto &elem: vecDBS ) {
            type = elem->getEvent()->eventStrType();
            elem->getEvent()->setExp( uncoloredPrint );
            if ( typeid( *elem ) == typeid( *evT ) ) {
                outFile << *( elem->getEvent() );
                size = outFile.tellg();
                outFile << "\n";
            }
        }
        outFile.close();
    }

    if ( size == 0 ) {
        std::cout  << "\n\nThere is no " << type << " Event(s) in your Calendar  \n";
        return;
    }
    std::cout  << "\n\nSuccessfully exported your  " << type << "  Event(s) in txt format\n" ;
    return;
}

void CTextFormat:: exportAllEvents    ( const std::vector <std::shared_ptr<CEventTypes>> & vecDBS  ) {
    std::fstream outFile;
    int size = 0;
    outFile.open("AllEventsTXT.txt", std::ios::out | std::ios::binary );
    if ( !outFile ) {
        return;
    } else {
        bool uncoloredPrint = true;
        for ( auto & elem : vecDBS ) {
            elem->getEvent()->setExp( uncoloredPrint );
            outFile << *( elem->getEvent() );
            size = outFile.tellg();
            outFile << "\n";
            }
        outFile.close();
    }

    if ( size == 0 ) {
        std::cout  << "\n\nThere is no Event in your Calendar  \n";
        return;
    }
    std::cout  << "\n\nSuccessfully exported ALL your events in txt format\n" ;
    return;
}


//-----------------------------------------------------------------------------------------------------//

CSVFileFormat::CSVFileFormat ( ) { }

void CSVFileFormat:: exportEventsByType ( const std::vector <std::shared_ptr<CEventTypes>> & vecDBS,
                                          const std::shared_ptr<CEventTypes> & evT ) {
    std::fstream outFile;
    int size = 0;
    std::string type;
    outFile.open("ExportByTypeSCV.csv", std::ios::out| std::ios::binary );
    if ( !outFile ) {
        return;
    } else {
        for ( auto &elem: vecDBS )   {
            if ( typeid ( *elem ) == typeid ( *evT ) )      {
                type = elem->getEvent()->eventStrType();
                outFile << elem->getEvent()->title()        << ",";
                outFile << elem->getEvent()->getCDate()     << ",";
                outFile << elem->getEvent()->getCTime()     << ",";
                outFile << elem->getEvent()->duration()     << ",";
                outFile << elem->getEvent()->finishTime()   << ",";
                outFile << elem->getEvent()->place()        << ",";
                outFile << elem->getEvent()->type()         << ",";
                outFile << elem->getEvent()->eventStrType() << ",";
                outFile << elem->getEvent()->recurrence()   << ",";
                outFile << elem->getEvent()->recurrenceLimit()      << ",";
                outFile << elem->getEvent()->numberOfParticipants() << ",";
                size = outFile.tellg();
                for ( auto &name: elem->getEvent()->participants() ) {
                    outFile << name << ",";
                }
            }
            outFile << "\n";
        }
        outFile.close();
    }
    if ( size == 0 ) {
        std::cout << "\n\nThere is no " << type << " Event(s) in your Calendar  \n";
        return;
    }
    std::cout  << "\n\nSuccessfully exported your " << type << "  Event(s) in csv format\n" ;
    return;
}

void CSVFileFormat:: exportAllEvents    ( const std::vector <std::shared_ptr<CEventTypes>> & vecDBS ) {
    std::fstream outFile;
    int size = 0;
    std::string type;
    outFile.open("AllEventsSCV.csv", std::ios::out | std::ios::binary );
    if ( !outFile ) {
        std::cout  << "\n\nThere is something went wrong. Please try again...  \n";
        return ;
    } else {
        for ( auto &elem: vecDBS ) {
            type = elem->getEvent()->eventStrType();
            outFile << elem->getEvent()->title()                << ",";
            outFile << elem->getEvent()->getCDate()             << ",";
            outFile << elem->getEvent()->getCTime()             << ",";
            outFile << elem->getEvent()->duration()             << ",";
            outFile << elem->getEvent()->finishTime()           << ",";
            outFile << elem->getEvent()->place()                << ",";
            outFile << elem->getEvent()->type()                 << ",";
            outFile << elem->getEvent()->eventStrType()         << ",";
            outFile << elem->getEvent()->recurrence()           << ",";
            outFile << elem->getEvent()->recurrenceLimit()      << ",";
            outFile << elem->getEvent()->numberOfParticipants() << ",";
            size = outFile.tellg();
            for (auto & name: elem->getEvent()->participants() ) {
                outFile << name << ",";
            }
            outFile << "\n";
        }
        outFile.close();
    }
    if ( size == 0 ) {
        std::cout  << "\n\nThere is no " << type << " Event(s) in your Calendar  \n" ;
        return ;
    }

    std::cout  << "\n\nSuccessfully exported ALL your events in csv format\n" ;
    return ;
}

