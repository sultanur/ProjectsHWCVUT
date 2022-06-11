#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <array>
#include <cassert>
using namespace std;
#endif /* __PROGTEST__ */
/*
Since COVID pandemic is not under control yet, the government introduces new and new restrictions to slow down the spread of the virus. It even resurrected the idea of self tracking by means of mobile phones (eRouška). You are asked to prepare the software needed for this project. Unfortunately, the project leader and SW architect is ill at the moment, thus you have to both design the interface and implement the software.

You are expected to develop 3 classes. The interface is mostly up to you, however, some interface is already fixed (see the attached archive, your implementation must be compatible). The required classes are:

    CTimeStamp, the class represents a simple time stamp. The required interface is a constructor to initialize the fields (year/month/day/hour/minute/second). The values passed to the constructor are valid dates/times, your class does not have to validate them.
    CContact is a class to encapsulate a single contact between two people. The people are identified by their respective phone numbers, moreover, there is a timestamp associated with the contact (CTimeStamp).
    CEFaceMask is a class that stores the contacts. The contacts are added via method addContact, searching for contacts is provided via method listContacts. There are two options to call the search method: either with the phone of the infected person, or the phone of the infected person and a time interval. In either case, the method returns a list o phone numbers the person was in contact with (limited to the given time interval in the latter case).

We represent phone numbers as integers in this task (do not do this in practice, leading zeros are important for phone numbers). The return value of listContacts returns a list of phone numbers. The list must not contain duplicates (do not include the second and all further occurrences of the same number). Next, it is important to list the contacts in the order they were added (contacts made earlier will be listed before contacts made later). Finally, there may be some glitches when filling the database. In particular, the hardware sensors report a contact with itself (the same phone number). Such contacts would be confusing, do not include them in the result.

Notes:

    There are example runs and some test data included in the attached archive.
    Do not spend time with optimizations. A reasonable implementation of naive algorithms is enough for this assignment.
    Pay attention to the design of the class interface. Do not declare everything public. Use the seminars to consult the design of your classes.

*/


// TODO (year/month/day/hour/minute/second)
class CTimeStamp
{ 
  public:
    int m_year;
    int m_month;
    int m_day;
    int m_hour;
    int m_minute;
    int m_second;

      public:
            CTimeStamp();
            CTimeStamp (int year, int month, int day, int hour, int minute,int second )
                        :m_year(year), m_month(month), m_day(day), m_hour(hour), m_minute(minute), m_second(second) {}
            CTimeStamp (const CTimeStamp & t) 
                        {
                          m_year = t.m_year;
                          m_month = t.m_month;
                          m_day = t.m_day;
                          m_hour = t.m_hour;
                          m_minute = t.m_minute;
                          m_second = t.m_second;
                        } 
    static bool is_leap_year(int y){
      bool isLeapYear = false;
      if (y % 4 == 0) {
          if (y % 100 == 0) {
            if (y % 400 == 0) {
                isLeapYear = true;
            }
          } 
          else isLeapYear = true;
      }
      return isLeapYear;
    }
  
   static long calculate_seconds_between(
                                        uint Y1, uint M1, uint D1, uint H1, uint m1, uint S1,
                                        uint Y2, uint M2, uint D2, uint H2, uint m2, uint S2)
  {
    bool invert = false;
    if (Y1 > Y2) {
        invert = true;
    } else if (Y1 == Y2) {
        if (M1 > M2) {
            invert = true;
        } else if (M1 == M2) {
            if (D1 > D2) {
                invert = true;
            } else if (D1 == D2) {
                if (H1 > H2) {
                    invert = true;
                } else if (H1 == H2) {
                    if (m1 > m2) {
                        invert = true;
                    } else if (m1 == m2 && S1 > S2) {
                        invert = true;
                    }
                }
            }
        }
    }

    if (invert) {
        std::swap(Y1, Y2);
        std::swap(M1, M2);
        std::swap(D1, D2);
        std::swap(H1, H2);
        std::swap(m1, m2);
        std::swap(S1, S2);
    }

    static const int month_days_sum[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    const uint Y1_days = month_days_sum[M1 - 1];
    const uint Y2_days = month_days_sum[M2 - 1];
    int years_days = (Y2 - Y1) * 365;

    for (uint i = Y1 + 1; i < Y2;) {
        if (is_leap_year(i)) {
            ++years_days;
            i += 4;
        } else {
            ++i;
        }
    }

    const bool lY1 = is_leap_year(Y1) && (M1 < 2 || (M1 == 2 && D1 < 29));
    const bool lY2 = is_leap_year(Y2) && (M2 > 2 || (M2 == 2 && D2 > 28));

    if (Y1 == Y2) {
        if (lY1 && lY2) ++years_days;
    } else {
        if (lY1) ++years_days;
        if (lY2) ++years_days;
    }

    // Convert years to seconds
    const long years_seconds = years_days * 86400;

    // Time difference in seconds
    const long S1s = ((Y1_days + D1) * 86400) + (H1 * 3600) + (m1 * 60) + S1;
    const long S2s = ((Y2_days + D2) * 86400) + (H2 * 3600) + (m2 * 60) + S2;

    const long total = years_seconds + (S2s - S1s);

    if (invert) return -total;
    else return total;
  }
    
};
 // TODO  CContact is a class to encapsulate a single contact between two people. 
//The people are identified by their respective phone numbers, moreover, there is a timestamp associated with the contact (CTimeStamp).
class CContact
{       
         public:
          CTimeStamp m_timestamp;
          int m_phone1;
          int m_phone2;         
               
          CContact (const CTimeStamp timestamp, int phone1, int phone2): m_timestamp(timestamp), m_phone1(phone1), m_phone2(phone2) {}      
         
};
// TODO  CEFaceMask is a class that stores the contacts.
// The contacts are added via method addContact, searching for contacts is provided via method listContacts. 
// There are two options to call the search method: either with the phone of the infected person, or the phone of the infected person and a time interval. 
// In either case, the method returns a list o phone numbers the person was in contact with (limited to the given time interval in the latter case).
class CEFaceMask
{  
  vector <CContact> m_contacts;    
  public:      
    CEFaceMask & addContact (const CContact &person)
    { 
      if (person.m_phone1 != person.m_phone2)
      {
          m_contacts.push_back(person); 
          return *this; 
      } else { 
          return *this;
      }
    }   
    vector<int>  listContacts(const int phoneNumber) const
    {
       vector <int> contacts;        
          for (auto it = m_contacts.begin(); it <= m_contacts.end(); it ++)
          {
              if (((*it).m_phone1 == phoneNumber) && (find(contacts.begin(), contacts.end(), (*it).m_phone2) == contacts.end())) 
              {
                  contacts.push_back((*it).m_phone2);    
              } else if (((*it).m_phone2 == phoneNumber) && (find(contacts.begin(), contacts.end(), (*it).m_phone1) == contacts.end())) 
              {
                  contacts.push_back((*it).m_phone1);
              }                           
          }          
            return contacts; 
    }
         
      vector<int>  listContacts(const int phoneNumber, const CTimeStamp &from, const  CTimeStamp &to) const
      {
        vector <int> contacts {};
        for (auto it = m_contacts.begin(); it < m_contacts.end(); it ++)
        {     
                                  
            if (((*it).m_phone1 == phoneNumber)
                && (CTimeStamp::calculate_seconds_between (from.m_year,from.m_month, from.m_day, from.m_hour, from.m_minute, from.m_second, 
                                                          (*it).m_timestamp.m_year, (*it).m_timestamp.m_month,(*it).m_timestamp.m_day, 
                                                          (*it).m_timestamp.m_hour, (*it).m_timestamp.m_minute,(*it).m_timestamp.m_second) >= 0)
                && (CTimeStamp::calculate_seconds_between ((*it).m_timestamp.m_year,(*it).m_timestamp.m_month, (*it).m_timestamp.m_day, (*it).m_timestamp.m_hour, 
                                                           (*it).m_timestamp.m_minute, (*it).m_timestamp.m_second, 
                                                           to.m_year, to.m_month,to.m_day, to.m_hour, to.m_minute,to.m_second) >= 0)            
                && (find(contacts.begin(), contacts.end(), (*it).m_phone2) == contacts.end()))
            {
                contacts.push_back((*it).m_phone2);
            } 
            else if  (((*it).m_phone2 == phoneNumber) 
                  && (CTimeStamp::calculate_seconds_between (from.m_year,from.m_month, from.m_day, from.m_hour, from.m_minute, from.m_second, 
                                                            (*it).m_timestamp.m_year, (*it).m_timestamp.m_month,(*it).m_timestamp.m_day, 
                                                            (*it).m_timestamp.m_hour, (*it).m_timestamp.m_minute,(*it).m_timestamp.m_second) >= 0)
                  && (CTimeStamp::calculate_seconds_between ((*it).m_timestamp.m_year,(*it).m_timestamp.m_month, (*it).m_timestamp.m_day, (*it).m_timestamp.m_hour, 
                                                            (*it).m_timestamp.m_minute, (*it).m_timestamp.m_second, 
                                                            to.m_year, to.m_month,to.m_day, to.m_hour, to.m_minute,to.m_second) >= 0)
                  && (find(contacts.begin(), contacts.end(), (*it).m_phone2) == contacts.end()))              
              {
                 contacts.push_back((*it).m_phone1); 
              }
        }
       //for (auto &k : contacts)
           //cout << k << endl;
        return contacts;
      }      
  };  
#ifndef __PROGTEST__
int main ()
{
  CEFaceMask test;

  test . addContact ( CContact ( CTimeStamp ( 2021, 1, 10, 12, 40, 10 ), 123456789, 999888777 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 1, 12, 12, 40, 10 ), 123456789, 111222333 ) )
       . addContact ( CContact ( CTimeStamp ( 2021, 2, 5, 15, 30, 28 ), 999888777, 555000222 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 2, 21, 18, 0, 0 ), 123456789, 999888777 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 1, 5, 18, 0, 0 ), 123456789, 456456456 ) );
  test . addContact ( CContact ( CTimeStamp ( 2021, 2, 1, 0, 0, 0 ), 123456789, 123456789 ) );
 // test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 5, 18, 0, 0 ), CTimeStamp ( 2021, 2, 21, 18, 0, 0 ));
  //test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 5, 18, 0, 1 ), CTimeStamp ( 2021, 2, 21, 17, 59, 59 ) );
  //test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 10, 12, 41, 9 ), CTimeStamp ( 2021, 2, 21, 17, 59, 59 ) );
  assert ( test . listContacts ( 123456789 ) == (vector<int> {999888777, 111222333, 456456456}) );
  assert ( test . listContacts ( 999888777 ) == (vector<int> {123456789, 555000222}) );
  assert ( test . listContacts ( 191919191 ) == (vector<int> {}));
  assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 5, 18, 0, 0 ), CTimeStamp ( 2021, 2, 21, 18, 0, 0 ) ) == (vector<int> {999888777, 111222333, 456456456}) );
  assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 5, 18, 0, 1 ), CTimeStamp ( 2021, 2, 21, 17, 59, 59 ) ) == (vector<int> {999888777, 111222333}) );
  assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 10, 12, 41, 9 ), CTimeStamp ( 2021, 2, 21, 17, 59, 59 ) ) == (vector<int> {111222333}) );


  return 0;
}
#endif /* __PROGTEST__ */


