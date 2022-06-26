obj/CCalendar.o: src/CCalendar.cpp src/CCalendar.hpp src/CDate.hpp \
obj/ src/Time.hpp
obj/CDate.o: src/CDate.cpp src/CDate.hpp src/Time.hpp
obj/CEventTypes.o: src/CEventTypes.cpp src/CEventTypes.hpp src/Event.hpp \
obj/ src/CCalendar.hpp src/CDate.hpp src/Time.hpp
obj/Event.o: src/Event.cpp src/Event.hpp src/CCalendar.hpp src/CDate.hpp \
obj/ src/Time.hpp
obj/ExportEvents.o: src/ExportEvents.cpp src/ExportEvents.hpp \
obj/ src/Register.hpp src/CDate.hpp src/Time.hpp src/CEventTypes.hpp \
obj/ src/Event.hpp src/CCalendar.hpp
obj/Menu.o: src/Menu.cpp src/Menu.hpp src/Register.hpp src/CDate.hpp \
obj/ src/Time.hpp src/CEventTypes.hpp src/Event.hpp src/CCalendar.hpp \
obj/ src/ExportEvents.hpp
obj/Register.o: src/Register.cpp src/Register.hpp src/CDate.hpp src/Time.hpp \
obj/ src/CEventTypes.hpp src/Event.hpp src/CCalendar.hpp
obj/Time.o: src/Time.cpp src/Time.hpp
obj/main.o: src/main.cpp src/Menu.hpp src/Register.hpp src/CDate.hpp \
obj/ src/Time.hpp src/CEventTypes.hpp src/Event.hpp src/CCalendar.hpp \
obj/ src/ExportEvents.hpp
