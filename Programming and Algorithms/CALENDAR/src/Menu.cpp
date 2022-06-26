//
// Created by nuray on 1.5.22.
//

#include "Menu.hpp"
#include "ExportEvents.hpp"
#include  <cstdlib>


    Menu:: Menu( ) { }

    void Menu:: welcome     ( )      {
    std::cout << std::endl<<std::endl;
    std::cout<<"             #####         #        #           #######     #     #     ######         #        ######  "<<std::endl;
    std::cout<<"            #     #       # #       #           #           ##    #     #     #       # #       #     # "<<std::endl;
    std::cout<<"            #            #   #      #           #           # #   #     #     #      #   #      #     # "<<std::endl;
    std::cout<<"            #           #     #     #           #####       #  #  #     #     #     #     #     ######  "<<std::endl;
    std::cout<<"            #           #######     #           #           #   # #     #     #     #######     #   #   "<<std::endl;
    std::cout<<"            #     #     #     #     #           #           #    ##     #     #     #     #     #    #  "<<std::endl;
    std::cout<<"             #####      #     #     #######     #######     #     #     ######      #     #     #     # "<< std::endl;

    }
    void Menu:: displayMenu ( void ) {
    std::cout << "\n\nWELCOME, \n";
    std::cout << "Please, enter below number to perform operation on CALENDAR: \n";
    std::cout << "      #------------------------------------------#\n";
    std::cout << "      #    " <<   " 1 "  << "  DISPLAY MONTHLY CALENDAR         #\n" ;
    std::cout << "      #    " <<   " 2 "  << "  DISPLAY WEEKLY CALENDAR          #\n" ;
    std::cout << "      #    " <<   " 3 "  << "  DISPLAY DAILY CALENDAR           #\n" ;
    std::cout << "      #    " <<   " 4 "  << "  ADD EVENT                        #\n" ;
    std::cout << "      #    " <<   " 5 "  << "  SEARCH EVENT BY PLACE            #\n" ;
    std::cout << "      #    " <<   " 6 "  << "  SEARCH EVENT BY TITLE            #\n" ;
    std::cout << "      #    " <<   " 7 "  << "  EXPORT EVENT                     #\n" ;
    std::cout << "      #    " <<   " 8 "  << "  IMPORT EVENT                     #\n" ;
    std::cout << "      #    " <<   " 9 "  << "  CHANGE EVENT TIME                #\n" ;
    std::cout << "      #    " <<   " 10"  << "  PRINT EVENTS BY TYPE             #\n" ;
    std::cout << "      #    " <<   " 11"  << "  DELETE EVENT                     #\n" ;
    std::cout << "      #    " <<   " 12  Exit                                "<< "#\n";
    std::cout << "      #------------------------------------------------------------------#\n" ;

    }
    void Menu:: MainMenu    ( void ) {
        while ( 1 ) {

            displayMenu();

            std::cout  << "\n\nEnter number of operation\n" ;
            unsigned int month, year, day, type;
            int operation;
            std::string response, place;
            std::getline (std::cin, response );
            try {
                operation = std::stoi(response );
            } catch ( const std::invalid_argument  & e ){
                std::cerr <<" Invalid Menu option   " << e.what( ) << std::endl;
                continue;
            }
            switch ( operation ) {
                case ( 1 ):
                    monthlyCalendar( );
                    break;
                case ( 2 ):
                    weeklyCalendar( );
                    break;
                case ( 3 ):
                    dailyCalendar( );
                    break;
                case ( 4 ):
                    readCreateEvent( );
                    break;
                case ( 5 ):
                    searchEventByPlace( );
                    break;
                case ( 6 ):
                    searchEventByTitle( );
                    break;
                case ( 7 ):
                    exportEvents ( );
                    break;
                case ( 8 ):
                    importEvent ( );
                    break;
                case ( 9 ):
                    setTimeChange ( );
                    break;
                case ( 10 ):
                    printEventByType();
                    break;
                case ( 11 ):
                    deleteEvent();
                    break;
                case ( 12 ):
                    return;

        }
    }
}

    void Menu:: monthlyCalendar    ( )       {

        while ( 1 ) {
            std::string response;
            unsigned int year, month;
            std::cout  << "\n\nMonth: ";
            getline(std::cin, response);
            if ( !isNumber(response ) ) {
                std::cout  << "Please, enter number of month\n" ;
                std::cout  << "Continue ? [Y/N]: ";
                getline(std::cin, response);
                if ( response == "N" || response == "n" || !std::cin ) {
                    std::cin.clear();
                    return;
                } else continue;
            }
            month = std::stoi (response );

            std::cout  << "Year: ";
            getline(std::cin, response );
            if ( !isNumber(response ) ) {
                std::cout  << "Please, enter right year \n" ;
                std::cout  << "Continue ? [Y/N]: ";
                getline (std::cin, response );
                if ( response == "N" || response == "n" || !std::cin ) {
                    std::cin.clear();
                    return;
                } else continue;
            }
            year = std::stoi(response);
            MonthlyCalendar *MC = new MonthlyCalendar ( year, month );
            if (! ( MC->isValidDate ( year, month ) ) ) {
                std::cout  << "\nInvalid date. Please try again...\n" ;
                std::cout  << "Continue ? [Y/N]: ";
                getline(std::cin, response);
                if ( response == "N" || response == "n" || !std::cin ) {
                    std::cin.clear();
                    return;
                }
            } else {
                std::cout << *MC;
                std::cout  << "\n\n\nAgain ? [Y/N]: ";
                getline(std::cin, response);
                if ( response == "N" || response == "n" || !std::cin ) {
                    std::cin.clear();
                    return;
                }
            }
            continue;
        }
    }
    void Menu:: weeklyCalendar     ( )       {
        std::string response;
        unsigned int day, month, year;
        while ( 1 ) {
            std::cout  << "\n\nDay \n";
            getline(std::cin, response );
            if ( !isNumber(response ) ) {
                std::cout << "Please, enter correct day \n";
                std::cout << "Continue ? [Y/N]: \n";
                getline(std::cin, response);
                if ( response == "N" || response == "n" || !std::cin ) {
                    std::cin.clear();
                    return;
                } else continue;
            }
            day = std::stoi (response );

            std::cout  << "Month  \n";
            getline (std::cin, response );
            if (!isNumber (response ) ) {
                std::cout  << "Please, enter month in number\n" ;
                std::cout  << "Continue ? [Y/N]: \n";
                getline(std::cin, response);
                if ( response == "N" || response == "n" || !std::cin ) {
                    std::cin.clear();
                    return;
                } else continue;
            }
            month = std::stoi (response );

            std::cout  << "Year \n";
            getline(std::cin, response );
            if ( !isNumber(response ) ) {
                std::cout  << "Please, enter correct year\n" ;
                std::cout  << "Continue ? [Y/N]: \n";
                getline(std::cin, response);
                if ( response == "N" || response == "n" || !std::cin ) {
                    std::cin.clear();
                    return;
                } else continue;
            }
            year = std::stoi(response);

            WeeklyCalendar *WC = new WeeklyCalendar(year, month, day);
            if (! ( WC->isValidDate ( year, month, day ) ) )  {
                std::cout  << "\nInvalid date. Please try again...\n" ;
                std::cout  << "Continue ? [Y/N]: \n";
                getline(std::cin, response );
                if ( response == "N" || response == "n" || !std::cin ) {
                    std::cin.clear();
                    return;
                }
            } else {
                std::cout << *WC;
                std::cout  << "\n\n\nAgain ? [Y/N]: \n";
                getline(std::cin, response );
                if ( response == "N" || response == "n" || !std::cin ) {
                    std::cin.clear();
                    return;
                }
            }
            continue;
        }
    }
    void Menu:: dailyCalendar      ( )       {
        std::string response;
        unsigned int day, month, year;
        while ( 1 ) {
            std::cout  << "\n\nDay: \n";
            getline(std::cin, response );
            if ( !isNumber (response ) ) {
                std::cout  << "Please, enter correct day \n" ;
                std::cout  << "Continue ? [Y/N]: \n";
                getline (std::cin, response );
                if ( response == "N" || response == "n" || !std::cin ) {
                    std::cin.clear();
                    return;
                } else continue;
            }
            day = std::stoi (response );

            std::cout  << "Month: \n";
            getline (std::cin, response );
            if ( !isNumber (response ) ) {
                std::cout  << "Please, enter month in number\n" ;
                std::cout  << "Continue ? [Y/N]: \n";
                getline(std::cin, response );
                if ( response == "N" || response == "n" || !std::cin ) {
                    std::cin.clear();
                    return;
                } else continue;
            }
            month = std::stoi(response );

            std::cout  << "Year \n";
            getline (std::cin, response );
            if (!isNumber(response ) ) {
                std::cout  << "Please, enter correct year\n" ;
                std::cout  << "Continue ? [Y/N]: \n";
                getline (std::cin, response );
                if ( response == "N" || response == "n" || !std::cin ) {
                    std::cin.clear();
                    return;
                } else continue;
            }
            year = std::stoi (response );
            DailyCalendar *DC = new DailyCalendar ( year, month, day );
            if (! ( DC->isValidDate( year, month, day ) ) ) {
                std::cout  << "\nInvalid date. Please try again...\n" ;
                std::cout  << "Continue ? [Y/N]: \n";
                getline (std::cin, response );
                if ( response == "N" || response == "n" || !std::cin ) {
                    std::cin.clear();
                    return;
                }
            } else {
                std::cout << *DC;
                CDate occupied  ( day, month, year );
                reg->findByDate ( occupied ) ;
                std::cout  << "\n\n\nAgain ? [Y/N]: \n";
                getline (std::cin, response );
                if ( response == "N" || response == "n" || !std::cin ) {
                    std::cin.clear();
                    return;
                }
            }
            continue;
        }
    }

    void Menu:: readCreateEvent    ( )       {
        std::vector <std::string> participants;
        CDate zeroDate ( 0 , 0, 0 );
        CTime zeroTime ( 0, 0 );
        std::string response, recLimitStr, durationStr;
        int recLimit;
        bool recurrence, responseExit = false;
        int recCycle, duration;
        int type;

        while ( 1 ) {
            Event tmpNewEvent;

            std::cout  << "\nEnter following info for Event creation \n" << std::endl;

            std::cout << "\n\nTITLE of Event: " ;
            getline (std::cin, response );
            tmpNewEvent.setTitle ( response );

            type = choseType ( type );
            if ( type < 1 )
                return;
            tmpNewEvent.setType ( type );

            switch ( tmpNewEvent.type() ) {
                case ( 1 ):
                    tmpNewEvent.setEventStrType ("Important" );
                    break;
                case ( 2 ):
                    tmpNewEvent.setEventStrType ("MoveAble" );
                    break;
                case ( 3 ):
                    tmpNewEvent.setEventStrType ("Optional" );
                    break;
            }

            tmpNewEvent.setCDate(enterDate ( tmpNewEvent.getCDate() ) );
            if ( tmpNewEvent.getCDate() == zeroDate )
                return;
            tmpNewEvent.setCTime (enterTime( tmpNewEvent.getCTime() ) ) ;
            if ( tmpNewEvent.getCTime() == zeroTime )
                return;

            durationStr = setDuration ( durationStr );
            duration = std::stoi ( durationStr  );
            if ( duration < 1 )
                return ;
            tmpNewEvent.setDuration (duration );

            tmpNewEvent.setFinishTime (tmpNewEvent.getCTime() + tmpNewEvent.duration() );

            std::cout  << "Place:  " ;
            getline (std::cin, response );
            tmpNewEvent.setPlace ( response ) ;

            participants = addingParticipants ( responseExit, participants );
            if ( responseExit )
                return;
            if ( participants.size() == 0  && ( !responseExit ) ) {
                tmpNewEvent.setNumberOfParticipants (0);
            } else {
                tmpNewEvent.setNumberOfParticipants (participants.size() );
                tmpNewEvent.setParticipants ( participants );
            }

            std::cout  << "Set up recurrence for event? [Y|N]: ";
            getline(std::cin, response );
            if ( response == "N" || response == "n" || !std::cin ) {
                std::cin.clear();
                recurrence = false;
            } else {
                recurrence = true;
            }

            if ( recurrence ) {
                recCycle = choseRecCycle ( recCycle );
                if ( recCycle < 1 )
                    return;
                switch ( recCycle ) {
                    case (1):
                        tmpNewEvent.setRecurrence (7 );
                        break;
                    case (2):
                        tmpNewEvent.setRecurrence (14 );
                        break;
                    case (3):
                        tmpNewEvent.setRecurrence (30 );
                        break;
                }

                recLimitStr = setRecLimit ( recLimitStr );
                recLimit = std::stoi ( recLimitStr );
                if ( recLimit < 1 )
                    return ;
                tmpNewEvent.setRecurrenceLimit ( recLimit );
            }

            switch ( tmpNewEvent.type() ) {
                case ( 1 ): {
                    CreateSaveImportantEvent ( tmpNewEvent );
                    break;
                }
                case ( 2 ): {
                    CreateSaveMovAbleEvent ( tmpNewEvent );
                    break;
                }
                case ( 3 ): {
                    CreateSaveOptionalEvent ( tmpNewEvent );
                    break;
                }
            }
            std::cout << "\n\nDo you want to create another Event? [Y|N]: " ;
            getline (std::cin, response );
            if ( response == "N" || response == "n" || !std::cin ) {
                std::cin.clear();
                return;
            } else
                continue;
        }
    }
    void Menu:: searchEventByPlace ( ) const {
        std::string place;
        std::cout  << "Place of Event to find: " ;
        std::getline (std::cin, place);
        reg->searchByPlace ( place );
    }
    void Menu:: searchEventByTitle ( ) const {
        std::string title;
        std::cout  << "Title of Event to find: " ;
        std::getline ( std::cin, title );
        reg->searchByTitle ( title );
    }
    void Menu:: exportEvents       ( )       {
        std::string response;
        int format, way, type;
        while ( 1 ) {
            std::cout << "Which Events to Export: "  << std::endl;
            std::cout << "1. All events            " << std::endl;
            std::cout <<          "2. By Event Type         " << std::endl;
            getline ( std::cin, response );
            if ( isNumber (response) ) {
                way = (std::stoi (response ) );
                if (! ( way == 1 || way == 2 ) ) {
                    std::cout  << "Please, enter one of Number of Formats [1 | 2] \n";
                    std::cout  << "Continue ? [Y/N]: ";
                    getline(std::cin, response);
                    if ( response == "N" || response == "n" || !std::cin ) {
                        std::cin.clear();
                        return;
                    } else continue;
                } else
                    break;
            } else {
                std::cout  << "Please, enter Number of Format\n" ;
                std::cout  << "Continue ? [Y/N]: ";
                getline (std::cin, response );
                if ( response == "N" || response == "n" || !std::cin ) {
                    std::cin.clear();
                    return;
                } else continue;
            }
            break;
        } //way of exporting

        while ( 1 ) {
            std::cout   << "Choose format of File to Export:\n";
            std::cout   << "1. TEXT FILE\n";
            std::cout           << "2. CSV  FILE\n" ;
            getline(std::cin, response );
            if ( isNumber(response ) ) {
                format = ( std::stoi (response ) );
                if (!( format == 1 || format == 2 ) ) {
                    std::cout  << "Please, enter one of Number of Formats [1 | 2]\n" ;
                    std::cout  << "Continue ? [Y/N]: ";
                    getline(std::cin, response);
                    if (response == "N" || response == "n" || !std::cin) {
                        std::cin.clear();
                        return;
                    } else continue;
                } else
                    break;
            } else {
                std::cout  << "Please, enter Number of Format\n" ;
                std::cout << "Continue ? [Y/N]: ";
                getline(std::cin, response);
                if ( response == "N" || response == "n" || !std::cin ) {
                    std::cin.clear();
                    return;
                } else continue;
            }
            break;
        } //format of exporting

        switch ( way )  { //all
            case ( 1 ): {
                switch ( format ) {
                    case ( 1 ): { //text,  all
                        auto FTxt = std::make_shared<CTextFormat>();
                        FTxt->exportAllEvents ( reg->dataBase() );
                        return;
                    }
                    case ( 2 ): { //csv, all
                        auto FCsv = std::make_shared<CSVFileFormat>();
                        FCsv->exportAllEvents ( reg->dataBase() );
                        return;
                    }
                }
                break;
            }
            case ( 2 ): { //by type
                int type;
                type = choseType( type );
                if ( type < 0 )
                    return;

                switch ( type )  {
                    case ( 1 ):  {
                        auto ImportantEvent = std::make_shared<Important_Event>();
                        if ( format == 1 ) {
                            auto FTxt = std::make_shared<CTextFormat>();
                            FTxt->exportEventsByType (reg->dataBase(), ImportantEvent );
                            return;
                        } else {
                            auto FCsv = std::make_shared<CSVFileFormat>();
                            FCsv->exportEventsByType(reg->dataBase(), ImportantEvent );
                            return;
                        }
                        break;
                    }
                    case ( 2 ):  {
                        auto MoveAbleEvent = std::make_shared<MoveAble_Event>();
                        if ( format == 1 ) {
                            auto FTxt = std::make_shared<CTextFormat>();
                            FTxt->exportEventsByType(reg->dataBase(), MoveAbleEvent );
                            return;
                        } else {
                            auto FCsv = std::make_shared<CSVFileFormat>();
                            FCsv->exportEventsByType(reg->dataBase(), MoveAbleEvent );
                            return;
                        }
                        break;
                    }
                    case ( 3 ):  {
                        auto OptionalEvent = std::make_shared<Optional_Event>();
                        if ( format == 1 ) {
                            auto FTxt = std::make_shared<CTextFormat>();
                            FTxt->exportEventsByType(reg->dataBase(), OptionalEvent );
                            return;
                        } else {
                            auto FCsv = std::make_shared<CSVFileFormat>();
                            FCsv->exportEventsByType(reg->dataBase(), OptionalEvent );
                            return;
                        }
                    } break;
                }
            }
        }
    }
    void Menu:: importEvent        ( )       {
        Event event;
        bool recurrence;
        std::string recLimitStr, response;
        event = reg->ImportEvents (event );
        int type, recCycle, recLimit;
        event.setFinishTime (( event.getCTime() + event.duration() ) );

        std::cout  << "\nChose type for Importing Event \n" ;
        type = choseType( type );
        if ( type < 0 )
            return;

        event.setType ( type );
        switch ( event.type() ) {
            case ( 1 ):
                event.setEventStrType ("Important" );
                break;
            case ( 2 ):
                event.setEventStrType ("MoveAble" );
                break;
            case ( 3 ):
                event.setEventStrType ("Optional" );
                break;
        }

        std::cout  << "Set up recurrence for Importing Event? [Y|N]: ";
        getline (std::cin, response);
        if ( response == "N" || response == "n" || !std::cin ) {
            std::cin.clear();
            recurrence = false;
        } else {
            recurrence = true;
        }

        if ( recurrence ) {
            recCycle = choseRecCycle(recCycle );
            if ( recCycle < 1 )
                return;
            switch ( recCycle ) {
                case (1):
                    event.setRecurrence(7);
                    break;
                case (2):
                    event.setRecurrence(14);
                    break;
                case (3):
                    event.setRecurrence(30);
                    break;
            }

            recLimitStr = setRecLimit(recLimitStr );
            recLimit = std::stoi(recLimitStr );
            if ( recLimit < 1 )
                return;
            event.setRecurrenceLimit(recLimit );
        }

        switch ( event.type() ) {
            case ( 1 ): {
                CreateSaveImportantEvent ( event );
                break;
            }
            case ( 2 ): {
                CreateSaveMovAbleEvent ( event );
                break;
            }
            case ( 3 ): {
                CreateSaveOptionalEvent ( event );
                break;
            }
        }
    }
    void Menu:: setTimeChange      ( )       {
        std::string response, title;
        std::vector < std::shared_ptr < CEventTypes > > ::iterator
        foundTitle;
        bool change, moved = false;
        CDate date;
        CTime zeroTime (0, 0);
        CDate zeroDate (0, 0, 0);
        CTime freeTime (0, 0);
        CDate moveDate (0, 0, 0);
        CTime moveTime (0, 0);

        while ( 1 ) {
            std::cout << "Enter Event Title: " ;
            getline(std::cin, title);
            foundTitle = reg->findByTitle(title);
            if (!(reg->findInDB(foundTitle))) {
                std::cout  << "There is no Event with title " << title << "\n" ;
                std::cout  << "Want to try again? [Y|N]: " ;
                getline(std::cin, response);
                if (response == "N" || response == "n" || !std::cin) {
                    std::cin.clear();
                    return;
                } else continue;
            } else break;
        }

        std::cout  << "\nEnter date you want to make changes:  ";
        date = enterDate( date );

        while ( 1 ) {
            std::cout  << "Print all occupied time for "  << date  << " [Y|N]?  ";
            getline(std::cin, response);
            if (response == "N" || response == "n" || !std::cin) {
                std::cin.clear();
                std::cout  << "Change time anyway for event " << title << " ? [Y|N] ";
                getline(std::cin, response);
                if (response == "N" || response == "n" || !std::cin) {
                    std::cin.clear();
                    change = false;
                    return;
                } else
                    change = true;

            } else {
                if ( reg->printOccupiedTime ( date ) ) {
                    std::cout  << "\nChange time for event " << title << "  to free slot in " << date << " ? [Y|N]  " ;
                    getline(std::cin, response);
                    if (response == "N" || response == "n" || !std::cin) {
                        std::cin.clear();
                        std::cout  << "Change to occupied time? [Y|N]  " ;
                        getline(std::cin, response);
                        if (response == "N" || response == "n" || !std::cin) {
                            std::cin.clear();
                            change = false;
                            return;
                        } else
                            change = true;
                    } else {
                        while ( 1 ) {
                            std::cout  << "Enter a new ( free ) time for event " << title << "   " << "\n" ;
                            freeTime = enterTime(freeTime);
                            if (freeTime == zeroTime)
                                return;

                            auto checkTime = reg->findByTime(date, freeTime);

                            if ( reg->findInDB (checkTime ) ) {
                                std::cout  << "You entered occupied time ";
                                std::cout  << "Want to try again? [Y|N]  ";
                                getline(std::cin, response);
                                if (response == "N" || response == "n" || !std::cin) {
                                    std::cin.clear();
                                    return;
                                } else continue;
                            }
                            break;
                        }
                        auto MovedEvent = (*foundTitle)->setChanges(moved, (*foundTitle), date, freeTime); ///////
                        if ( moved ) {
                            reg->AddEvents(MovedEvent);
                            return;
                        } else continue;
                    }
                } else {
                    std::cout  << "You can change to any time for " << title << "  in " << date << "  " ;
                    std::cout  << "Continue ? [Y|N]  " ;
                    getline(std::cin, response);
                    if (response == "N" || response == "n" || !std::cin) {
                        std::cin.clear();
                        return;
                    } else {
                        freeTime = enterTime(freeTime);
                        if (freeTime == zeroTime)
                            return;
                        auto MovedEvent = (*foundTitle)->setChanges(moved, (*foundTitle), date, freeTime); ////
                        if (moved) {
                            reg->AddEvents(MovedEvent);
                            return;
                        } else {
                            std::cout  << "Set up to another time for  Event " << title << "? [Y|N] ";
                            getline(std::cin, response);
                            if (response == "N" || response == "n" || !std::cin) {
                                std::cin.clear();
                                return;
                            } else {
                                continue;
                            }
                        }
                    }
                }
            }
            CTime newTime;
            if ( change ) {
                std::cout  << "\nEnter new desired  time for event  " << title << " in " << date << " ";
                newTime = enterTime(freeTime);
                if (newTime == zeroTime)
                    return;
                auto foundTime = reg->findByTime ( date, newTime );
                if ( !reg->findInDB (foundTime ) ) {
                    std::cout << "Entered date is not occupied. Change to a new date and time? [Y|N]  ";
                    getline(std::cin, response);
                    if (response == "N" || response == "n" || !std::cin) {
                        std::cin.clear();
                        return;
                    } else {
                        auto MovedEvent = (*foundTitle)->setChanges(moved, (*foundTitle), date, newTime); /////
                        if (moved) {
                            reg->AddEvents(MovedEvent);
                            return;
                        } else {
                            std::cout  << "Set up to another time for  Event " << title << "? [Y|N]  ";
                            getline(std::cin, response);
                            if (response == "N" || response == "n" || !std::cin) {
                                std::cin.clear();
                                return;
                            } else {
                                continue;
                            }
                        }
                    }

                } else { // move
                    std::cout  << "Entered date and time is occupied by event: \n" ;
                    std::cout << *(*foundTime)->getEvent() << "\n";
                    std::cout << "Move this event to a new date? [Y|N]  " ;
                    getline(std::cin, response);
                    if (response == "N" || response == "n" || !std::cin) {
                        std::cin.clear();
                        return;
                    } else {
                        std::cout  << "Enter a date and time to move event   ";
                        moveDate = enterDate(moveDate);
                        moveTime = enterTime(moveTime);
                        auto MovedEvent = ((*foundTime)->setChanges(moved, (*foundTime), moveDate, moveTime));  ////
                        if (moved) {
                            reg->AddEvents(MovedEvent);
                            std::cout  << "Set up to freed time for event " << title << "  ? [Y|N]:  " ;
                            getline(std::cin, response);
                            if (response == "N" || response == "n" || !std::cin) {
                                std::cin.clear();
                                return;
                            } else {
                                auto ChangeTime = (*foundTitle)->setChanges(moved, (*foundTitle),
                                                                            date,(*foundTime)->getEvent()->getCTime() ); /////
                                reg->AddEvents (ChangeTime );
                                return;
                            }
                        } else {
                            std::cout  << "Set up to another time for  Event " << title << "? [Y|N]  ";
                            getline(std::cin, response);
                            if (response == "N" || response == "n" || !std::cin) {
                                std::cin.clear();
                                return;
                            } else {
                                continue;
                            }
                        }
                    }
                }
            }
        }
    }
    void Menu:: printEventByType   ( )       {
        std::string response;
        int type;
        type = choseType( type );
        if ( type > 0 ) {
            switch ( type ) {
                case ( 1 ): {
                    auto evT = std::make_shared<Important_Event>();
                    reg->printByType ( evT );
                    break;
                }
                case ( 2 ): {
                    auto evT = std::make_shared<MoveAble_Event>();
                    reg->printByType ( evT );
                    break;
                }
                case ( 3 ): {
                    auto evT = std::make_shared<Optional_Event>();
                    reg->printByType ( evT );
                    break;
                }
            }
        } else return ;

    }
    void Menu:: deleteEvent        ( )       {
        std::string response;
        std::cout<< "Enter Date and Time to find in Calendar in order to delete   ";
        CDate dateToDelete;
        CTime timeToDelete;

        while  ( 1 ) {
            dateToDelete = readDate();
            if (!(dateToDelete.isValidDate(dateToDelete.year(),
                                           dateToDelete.month(),
                                           dateToDelete.day()))) {

                std::cout << "\nInvalid date. Please try again...  \n" ;
                std::cout << "Continue ? [Y/N]:  ";
                getline(std::cin, response);
                if (response == "N" || response == "n" || !std::cin) {
                    std::cin.clear();
                    return;
                } else continue;
            }
            break;
        }
        while ( 1 ) {
            timeToDelete = readTime();
            if (!(timeToDelete.isValidTime(timeToDelete.hour(), timeToDelete.minute()))) {

                std::cout  << "\nInvalid date. Please try again...\n" ;
                std::cout  << "Continue ? [Y/N]:  ";
                getline(std::cin, response);
                if (response == "N" || response == "n" || !std::cin) {
                    std::cin.clear();
                    return;
                } else continue;
            }
            break;
        }

        auto result = reg->deletingEvent(dateToDelete, timeToDelete);
        if (result) {
            std::cout  << "Event for " << dateToDelete << " " << timeToDelete
                      << " is successfully deleted from Calendar\n";
            return;
        } else {
            std::cout  << "There is no Event in  " << dateToDelete << "  at  " << timeToDelete
                      << "  to delete from Calendar\n" << "\n";
            return;
        }


    }

    CDate Menu:: readDate   ( )      {
    unsigned int year, month, day;
    std::string response;
    std::cout  << "\n\nDay: " ;
    getline ( std::cin, response );
    char * ch = ( char* )response.c_str(), *ptrEnd[1];
    day = ( int )( strtol ( ch, ptrEnd, 0 ) );
    if ( *ptrEnd == ch || !std::cin ) {
        std::cin.clear();
        day = -1;
    }
    std::cout  << "Month: " ;
    std::getline(std::cin, response );
    ch = ( char* )response.c_str();
    month = ( int )( strtol ( ch, ptrEnd, 0 ));
    if ( *ptrEnd == ch || !std::cin ) {
        std::cin.clear();
        month = -1;
    }
    std::cout  << "Year: " ;
    std::getline(std::cin, response );
    ch = ( char* )response.c_str();
    year = ( int )( strtol ( ch, ptrEnd, 0 ));
    if ( *ptrEnd == ch || !std::cin ) {
        std::cin.clear();
        year = -1;
    }

    return CDate (day, month, year);
}
    CTime Menu:: readTime   ( )      {
    unsigned int hour, minute;
    std::string response;
    std::cout  << "\n\nHour: " ;
    getline(std::cin, response );
    char * ch = ( char* ) response.c_str(), *ptrEnd[1];
    hour = ( int )( strtol ( ch, ptrEnd, 0 ) );
    if ( *ptrEnd == ch || !std::cin ) {
        std::cin.clear();
        hour = -1;
    }
    std::cout << "Minute: " ;
    getline (std::cin, response );
    ch = ( char* ) response.c_str();
    minute = ( int )( strtol ( ch, ptrEnd, 0 ));
    if ( *ptrEnd == ch || !std::cin ) {
        std::cin.clear();
        minute = -1;
    }

    return CTime ( hour, minute );
}
    CTime Menu:: enterTime  ( CTime enterTime  ) {
        CTime zeroTime(0, 0);
        std::string response;
        while (1) {
            enterTime = readTime();
            if (!(enterTime.isValidTime(enterTime.hour(), enterTime.minute()))) {
                std::cout  << "\nInvalid date. Please try again...\n" ;
                std::cout << "Continue ? [Y/N]: ";
                getline(std::cin, response);
                if (response == "N" || response == "n" || !std::cin) {
                    std::cin.clear();
                    return enterTime = zeroTime;
                } else continue;

            } else break;
        }
        return enterTime;
    }
    CDate Menu:: enterDate  ( CDate  enterDate ) {
        std::string response;
        CDate zeroDate(0, 0, 0);
        while ( 1 ) {
            enterDate = readDate();
            if (!( enterDate.isValidDate(enterDate.year(), enterDate.month(), enterDate.day()))) {
                std::cout  << "\nInvalid date. Please try again...\n" ;
                std::cout  << "Continue ? [Y/N]:  ";
                getline (std::cin, response );
                if ( response == "N" || response == "n" || !std::cin ) {
                    std::cin.clear();
                    enterDate = zeroDate;
                    return enterDate;
                } else continue;
            }
            break;
        }
        return enterDate;
    }
    bool Menu::  isNumber   ( const std::string& input ) const {
        for (char c: input) {
            if (!isdigit(c))
                return false;
        }
        return true;
    }


    int  Menu:: choseType          ( int  type )             {
        std::string response;

        while ( 1 )   {
            std::cout   << "Choose the Event Type :\n";
            std::cout   << "TYPE 1: Important Event\n";
            std::cout   << "TYPE 2: Movable Event\n";
            std::cout   << "TYPE 3: Optional Event\n" ;
            getline(std::cin, response);
            if ( isNumber(response ) ) {
                type = std::stoi(response) ;
                if (!( type == 1 || type == 2 || type == 3 ) ) {
                    std::cout << "Please, enter one of TYPE Numbers [1 | 2 | 3 ]\n" ;
                    std::cout  << "Continue ? [Y/N]: ";
                    getline(std::cin, response);
                    if (response == "N" || response == "n" || !std::cin) {
                        std::cin.clear();
                        type = -1;
                        return type;
                    } else continue;
                } else
                    break;
            } else {
                std::cout << "Please, enter TYPE Number\n" ;
                std::cout << "Continue ? [Y/N]: ";
                getline(std::cin, response);
                if (response == "N" || response == "n" || !std::cin) {
                    std::cin.clear();
                    type = -1;
                    return type;
                } else continue;
            }
        }
        return type;

    }
    int  Menu:: choseRecCycle      ( int  recCycle )         {
        std::string response;
        while ( 1 ) {
            std::cout   << "Choose recurrence cycle: \n";
            std::cout   << "1: EVERY WEEK\n";
            std::cout   << "2: EVERY 14 DAYS\n";
            std::cout   << "3: EVERY MONTH\n" ;
            getline (std::cin, response );
            if ( isNumber (response ) ) {
                recCycle = std::stoi (response );
                if ( ! ( recCycle == 1 || recCycle == 2 || recCycle == 3 ) ) {
                    std::cout  << "Please, enter one of cycle Numbers [1 | 2 | 3 ]\n";
                    std::cout  << "Continue ? [Y/N]: ";
                    getline(std::cin, response);
                    if (response == "N" || response == "n" || !std::cin) {
                        std::cin.clear();
                        recCycle = -1;
                    } else continue;
                } else
                    break;
            } else {
                std::cout  << "Please, enter recurrence's cycles Number\n" ;
                std::cout  << "Continue ? [Y/N]: ";
                getline(std::cin, response);
                if (response == "N" || response == "n" || !std::cin) {
                    std::cin.clear();
                    recCycle = -1;
                } else continue;
            }
        }
        return recCycle;
    }
    std::string Menu:: setRecLimit ( std::string recLimit )  {
        std::string response;
        while ( 1 ) {
            std::cout  << "Set limit to recurrence: " ;
            getline(std::cin, recLimit );
            if (!isNumber (recLimit ) ) {
                std::cout  << "Please, enter limit in number\n" ;
                std::cout  << "Continue ? [Y/N]: ";
                getline(std::cin, response);
                if ( recLimit == "N" || recLimit == "n" || !std::cin) {
                    std::cin.clear();
                    recLimit = "0";
                } else continue;
            }
            break;
        }
        return recLimit;
    }
    std::string Menu:: setDuration ( std::string duration )  {
        while ( 1 ) {
            std::cout  << "Duration  of Event in minutes: " ;
            getline (std::cin, duration );
            if ( !isNumber (duration ) ) {
                std::cout  << "Please, enter duration in minutes \n";
                std::cout  << "Continue ? [Y/N]: ";
                getline(std::cin, duration );
                if ( duration == "N" || duration == "n" || !std::cin ) {
                    std::cin.clear();
                    duration = "0";
                } else continue;
            }
            break;
        }
        return duration;
    }
    std::vector <std::string> Menu:: addingParticipants ( bool & responseExit,
                                                          std::vector <std::string> & participants ) {
        std::string response, participantsNumber;
        int number = 0;
        responseExit = false;
        while  ( 1 ) {
            participants.clear();
            std::cout << "Number of Participants: " ;
            getline(std::cin, participantsNumber );
            if ( ! isNumber(participantsNumber ) ) {
                std::cout << "Please, enter number\n";
                std::cout << "Continue ? [Y/N]: ";
                getline ( std::cin, response );
                if ( response == "N" || response == "n" || !std::cin ) {
                    std::cin.clear();
                    responseExit = true;
                    participantsNumber = "0";
                } else continue;
            }
            break;
        }
        number = std::stoi ( participantsNumber ) ;
        if ( number != 0 ) {
            for ( size_t i = 0; i < number; ++i ) {
                std::cout << "Name of Participant: " ;
                getline(std::cin, response );
                participants.push_back ( response );
            }
        }
        return participants;
    }
    void Menu:: CreateSaveImportantEvent ( const Event & event ) {
        std::string notice;
        std::cout << "Notice of Event Importance: " ;
        getline (std::cin, notice );

        auto newEvent = std::make_shared<Event> ( event );

        auto ImportantEvent = reg->setImportantEvent ( notice, newEvent );

        auto Event = std::shared_ptr<CEventTypes> ( ImportantEvent->create() );
        Event->setEvent ( newEvent );
        displayCreatedEvent (ImportantEvent );

        if ( saveCreatedEvent (Event ) ) {

            if ( ImportantEvent->getEvent()->recurrenceLimit() != 0 ) {
                int counter = 1;

                std::cout  << "Recurrence date(s): " << " \n";

                int recDays = ImportantEvent->getEvent()->recurrence();
                CDate tmpDate = ImportantEvent->getEvent()->getCDate();

                for ( size_t i = 0; i < ImportantEvent->getEvent()->recurrenceLimit(); ++i ) {

                    auto RecurrenceEvClone = newEvent->clone();
                    RecurrenceEvClone->setCDate ( tmpDate + recDays );

                    auto ImportantEventRec = reg->setImportantEvent ( ImportantEvent->notice(),
                                                                      newEvent );


                    auto EventRec = std::shared_ptr<CEventTypes>(ImportantEventRec->create());
                    EventRec->setEvent( RecurrenceEvClone );

                    if ( reg->AddEvents (EventRec ) ) {
                        std::cout  << "                      " << counter << ") "
                                   << RecurrenceEvClone->getCDate() << std::endl;
                        counter++;
                    } else {
                        std::cout  << "EVENT IS NOT SAVED. " <<  "You already have Event "
                                  << RecurrenceEvClone->title() << " in " << RecurrenceEvClone->getCDate()
                                  << " " << RecurrenceEvClone->getCTime() << "\n " ;
                        continue;
                    }
                }
            }
        } else return;
    }
    void Menu:: CreateSaveMovAbleEvent   ( const Event & event ) {

        int movesLimit = 0;
        std::string moveStr, response;
        while ( 1 ) {
            std::cout  << "Set Moves Limit: " ;
            getline(std::cin, moveStr);
            if (!isNumber(moveStr)) {
                std::cout  << "Please, enter limit in number\n" ;
                std::cout  << "Continue ? [Y/N]: ";
                getline(std::cin, response);
                if (response == "N" || response == "n" || !std::cin) {
                    std::cin.clear();
                    return;
                } else
                    continue;
            } else {
                movesLimit = std::stoi(moveStr);
                break;
            }
            break;
        }

        auto newEvent = std::make_shared<Event> ( event );

        auto MoveAbleEvent = reg->setMoveAbleEvent ( movesLimit, newEvent );

        auto Event = std::shared_ptr<CEventTypes> ( MoveAbleEvent->create() );
        Event->setEvent ( newEvent );
        displayCreatedEvent (MoveAbleEvent );

        if ( saveCreatedEvent ( Event ) ) {

            if ( MoveAbleEvent->getEvent()->recurrenceLimit() != 0 ) {
                int counter = 1;

                std::cout  << "Recurrence date(s): " << " \n";

                int recDays = MoveAbleEvent->getEvent()->recurrence();
                CDate tmpDate = MoveAbleEvent->getEvent()->getCDate();

                for ( size_t i = 0; i < MoveAbleEvent->getEvent()->recurrenceLimit(); ++i ) {

                    auto RecurrenceEvClone = newEvent->clone();
                    RecurrenceEvClone->setCDate ( tmpDate + recDays );

                    auto MoveableEventRec = reg->setMoveAbleEvent( MoveAbleEvent->movesNumber(), newEvent );


                    auto EventRec = std::shared_ptr<CEventTypes> ( MoveAbleEvent->create());
                    EventRec->setEvent ( RecurrenceEvClone );

                    if ( reg->AddEvents ( EventRec ) ) {
                        std::cout  << "                      " << counter << ") "
                                   << RecurrenceEvClone->getCDate() << std::endl ;
                        counter++;
                    } else {
                        std::cout << "EVENT IS NOT SAVED. "  << "You already have Event "
                                  << RecurrenceEvClone->title() << " in " << RecurrenceEvClone->getCDate()
                                  << " " << RecurrenceEvClone->getCTime() << "\n " ;
                        continue;
                    }
                }
            }
        } else return;
    }
    void Menu:: CreateSaveOptionalEvent  ( const Event & event ) {

        auto newEvent = std::make_shared<Event> ( event );

        auto OptionalEvent = reg->setOptionalEvent ( newEvent );
        auto Event = std::shared_ptr<CEventTypes> ( OptionalEvent->create() );

        displayCreatedEvent ( OptionalEvent );

        if ( saveCreatedEvent ( Event ) ) {

            if ( OptionalEvent->getEvent()->recurrenceLimit() != 0 ) {
                int counter = 1;

                std::cout  << "Recurrence date(s): " << " \n";

                int recDays = OptionalEvent->getEvent()->recurrence();
                CDate tmpDate = OptionalEvent->getEvent()->getCDate();
                for ( size_t i = 0; i < OptionalEvent->getEvent()->recurrenceLimit(); ++i ) {

                    auto RecurrenceEvClone = newEvent->clone();
                    RecurrenceEvClone->setCDate ( tmpDate + recDays );

                    auto OptionalEventRec = reg->setOptionalEvent ( RecurrenceEvClone );

                    auto EventRec = std::shared_ptr<CEventTypes> ( OptionalEventRec->create());
                    EventRec->setEvent ( RecurrenceEvClone );

                    if ( reg->AddEvents ( OptionalEventRec ) ) {
                        std::cout  << "                      " << counter << ") "
                                   << RecurrenceEvClone->getCDate() << std::endl ;
                        counter++;
                    } else {
                        std::cout  << "EVENT IS NOT SAVED. "
                                  << OptionalEvent->getEvent()->getCDate()
                                  << " " << OptionalEvent->getEvent()->getCTime()
                                  << " is already occupied by "
                                  << RecurrenceEvClone->title() << " event\n" ;
                        continue;
                    }
                }
            }
        } else return;

    }

    void  Menu:: displayCreatedEvent   ( const std::shared_ptr<CEventTypes> & event ) const {
        std::string response;
        std::cout  << "Display entered data? [Y|N]: " ;
        getline(std::cin, response);
        if (response == "N" || response == "n" || !std::cin) {
            std::cin.clear();
        } else {
            std::cout << *event;
        }
    }
    bool  Menu:: saveCreatedEvent      ( const std::shared_ptr<CEventTypes> & event )       {
        std::string response;
        std::cout  << "\nSave created event? [Y|N]: " ;
        getline (std::cin, response );
        if ( response == "N" || response == "n" || !std::cin ) {
            std::cout  << "\nEntered event haven't been saved \n " ;
            std::cin.clear();
            return false;
        } else {
            if ( reg->AddEvents(event ) ) {
                std::cout  << "\n\nYour event successfully added to the Calendar\n" ;
                return true;
            } else {
                std::cout  << "EVENT IS NOT SAVED. "  << "You already have Event in  "
                          << event->getEvent()->getCDate() << "  at " << event->getEvent()->getCTime() << " \n" ;
            }

        }
        return false;
    }


























