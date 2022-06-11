#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <chrono>
using namespace std;
#endif /* __PROGTEST__ */

class CDate
{
public:
    CDate ( ) { }
    CDate ( int year, int month, int day ) :m_year ( year ), m_month ( month ), m_day ( day ) { }
    int getYear  ( ) {
        return m_year;
    }
    int getMonth ( ) {
        return m_month;
    }
    int getDay   ( ) {
        return m_day;
    }
    bool operator == ( const CDate & d ) const  {
        return (m_year == d.m_year
                && m_month == d.m_month
                && m_day == d.m_day );
    }
    bool operator != ( const CDate & d ) const  {
        return (! (m_year == d.m_year
                   && m_month == d.m_month
                   && m_day == d.m_day ) );
    }
    bool operator <  ( const CDate & d ) const  {
        if ( m_year != d.m_year )
            return m_year < d.m_year;
        if ( m_month != d.m_month)
            return m_month < d.m_month;
        if ( m_day != d.m_day )
            return m_day < d.m_day ;
        return true;
    }
    bool operator >  ( const CDate & d ) const  {
        if ( m_year != d.m_year )
            return m_year > d.m_year;
        if ( m_month != d.m_month)
            return m_month > d.m_month;
        if ( m_day != d.m_day )
            return m_day > d.m_day ;
        return true;
    }
    bool operator <= ( const CDate & d ) const  {
        if ( m_year != d.m_year )
            return m_year <= d.m_year;
        if ( m_month != d.m_month)
            return m_month <= d.m_month;
        if ( m_day != d.m_day )
            return m_day <= d.m_day ;
        return true;
    }
    friend ostream & operator << ( ostream & out, const CDate & d ) {
        out << d.m_year << "/" << d.m_month << "/" << d.m_day;
        return out;
    }
    bool compare ( const CDate & b ) const {
        if ( m_year != b.m_year )
            return m_year < b.m_year;
        if ( m_month != b.m_month)
            return m_month < b.m_month;
        if ( m_day != b.m_day )
            return m_day < b.m_day ;
        return true;
    }

private:
    int m_year;
    int m_month;
    int m_day;

};

class Product {
public:
    Product( ) { }
    struct Storage {
        Storage( ) { }
        Storage ( const CDate & date, int count ): s_date( date ), s_count( count ) { }

        CDate s_date;
        int s_count;
    };

    vector <shared_ptr<Storage>> & getListByDates ( ) {
        return m_listByDates;
    }
    //getters, setters
    int getSum ( ) {
        return m_sum;
    }
    void takeSum ( int s ) {
        m_sum -= s;
    }
    void setSum ( int s ) {
        m_sum += s;
    }

private:
    vector <shared_ptr<Storage>> m_listByDates;
    int m_sum = 0;

};

class CSupermarket
{
  public:

    CSupermarket ( ) { }
    bool oneDiffChar ( const string & str1, const string & str2 );
    int  calculateShortage ( const map < string, shared_ptr<Product>>:: iterator & iterMap ,
                             int & count, vector <string> & zeros );
    bool calculateOneDiffChar ( const string & name, map < string,
                                shared_ptr<Product>>:: iterator & iter ) ;
    void print( );
    void printList ( list < pair < string, int > > & d );
    struct comparison {
        bool operator ( ) (const pair < string, int> & a, const pair < string, int > & b ) const {
            return a.second > b.second;
        }
    };
    CSupermarket & store ( const string & name,
                           const CDate & expireDate, const int & count ) ;
    void  sell ( list < pair < string, int >> & shoppingList ) ;
    list <pair < string, int>>  expired  ( const CDate & date ) const;

private:
    map < string, shared_ptr<Product>>  m_articles;

    };

    //helper method to calculate char difference in string
    bool CSupermarket:: oneDiffChar ( const string & str1, const string & str2 )
    {
        if ( ( str1.length( ) - str2.length( ) )  != 0 )
            return false;

        unsigned long int index1 = 0;
        unsigned long int index2 = 0;
        int foundDifference = 0;

        while (index2 < str2.length() && index1 < str1.length()) {
            if (str1.at(index1) != str2.at(index2)) {
               foundDifference++;
               if ( foundDifference > 1)
                    return false;
            }
            index1++;
            index2++;
        }
        return true;
    }

    //method to calculate request in shopping list and update all data in containers;
    int  CSupermarket:: calculateShortage ( const map < string, shared_ptr<Product>>:: iterator & iterMap ,
                                            int & count, vector <string> & zeros )
    {
        int restAmount = 0;

        if ( iterMap->second->getSum( ) > count ) {
            for ( auto indexVec = iterMap->second->getListByDates ( ).begin ( );
                                             indexVec != iterMap->second->getListByDates( ).end ( ) ; )
            {
                if ( (*indexVec )->s_count > count && count != 0 )
                {
                    (*indexVec )->s_count -= count;
                    iterMap->second->takeSum ( count );
                    count = 0;
                } else if ( (*indexVec )->s_count == count && count != 0 )
                {
                    (*indexVec )->s_count -= count;
                    iterMap->second->takeSum( count );
                    count = 0;
                } else if ( (*indexVec )->s_count < count && count != 0 )
                {
                    restAmount = count - (*indexVec )->s_count;
                    iterMap->second->takeSum ( (*indexVec )->s_count );
                    (*indexVec )->s_count = 0;
                    count = restAmount;
                }
                if ( iterMap->second->getSum( ) == 0 )
                    zeros.push_back( iterMap->first  );
                if ( (*indexVec )->s_count == 0 ) {
                    indexVec = iterMap->second->getListByDates( ).erase( indexVec );
                } else ++indexVec;
            }
        } else {
            for ( auto indexVec = iterMap->second->getListByDates( ).begin( );
                                             indexVec != iterMap->second->getListByDates( ).end( ) ; )
            {
                restAmount = count - (*indexVec )->s_count;
                (*indexVec )->s_count -= ( count - restAmount );
                iterMap->second->takeSum(( count - restAmount ) );
                count = restAmount;
                if ( iterMap->second->getSum( ) == 0 )
                    zeros.push_back(iterMap->first );
                if ( (*indexVec )->s_count == 0 ) {
                    indexVec = iterMap->second->getListByDates( ).erase (indexVec );
                } else ++indexVec;
            }
        }
        return count;
    }

    //method  to calculate mismatch by one char in strings;
    bool CSupermarket:: calculateOneDiffChar ( const string & name,
                                               map < string, shared_ptr<Product>>:: iterator & iterMap )
    {
        int numberFounds = 0;
        for ( auto found = m_articles.begin( ); found != m_articles.end(); ++found )
        {
            if ( oneDiffChar(found->first, name ) ) {
                numberFounds++;
                if ( numberFounds > 1 )
                    break;
                iterMap = found;
            }
        }
        if ( numberFounds == 1 )
        {
            return true;
        } else return false;
    }
    //to print the main map with stored articles
    void CSupermarket:: print( )
    {
        for ( auto article = m_articles.begin( ); article != m_articles.end( ); ++article )
        {
            cout << "name: " << article->first <<  " sum: " << article->second->getSum( ) << "  ";
            for ( auto & listDate : article->second->getListByDates( ) )
            {
                cout <<" date: " << listDate->s_date << " count: "<< listDate->s_count ;
            }
            cout << endl;
        }
    }

    //to print list of results ( shortage and expired articles )
    void CSupermarket:: printList ( list < pair < string, int > > & result ) {
        for ( auto iter = result.begin( ); iter != result.end( ); ++iter ) {
            cout <<"name: " << iter->first <<" count: " << iter->second << endl;
        }
    }

    // method to store articles in containers;
    CSupermarket & CSupermarket:: store ( const string & name, const CDate & expireDate, const int & count )
    {
        auto found = m_articles.lower_bound (name );
        auto newStorage = make_shared<Product::Storage> (expireDate, count );

        //if article not found, create a new object for storing;
        if ( found == m_articles.end ( ) || found->first != name )
        {
            auto newProduct = make_shared<Product>( );
            auto newStorage = make_shared<Product::Storage> (expireDate, count );
            newProduct->setSum (count );
            newProduct->getListByDates( ).push_back( newStorage );
            m_articles.emplace_hint ( found, move (name ), newProduct );
        } else {
            // helper function for lower_bound to find in vector of dates and counts input date
            auto compareFunction = [] ( const shared_ptr <Product::Storage> &product, const CDate &p ) {
                return ( product->s_date < p );
            };
            auto foundDate = lower_bound(found->second->getListByDates( ).begin( ), found->second->getListByDates( ).end( ),
                                         expireDate,[&] ( const shared_ptr <Product::Storage> &a, const CDate &b )
                                         {  return ( compareFunction(a, b ) > 0 ); } );

            //if date found, updates all data in containers and overall sum
            if  ( foundDate != found->second->getListByDates( ).end( ) && ( *foundDate )->s_date == expireDate )
            {
                ( *foundDate )->s_count += count;
                ( *found ).second->setSum( count );
            } else {
                // if not found date insert in position article, which improves performance (by no need in sorting)
                newStorage->s_date = expireDate;
                newStorage->s_count = count;
                ( *found ).second->setSum( count );
                ( *found ).second->getListByDates( ).insert(foundDate,  newStorage );
            }
        }
            return *this;
    }

    //method to  update containers and result of shopping list and shortage after selling article
    void  CSupermarket:: sell ( list < pair < string, int >> & shoppingList )
    {
        map < string, shared_ptr<Product>>:: iterator tmpIter;
        vector <string> zeroSum;
        for ( auto  request = shoppingList.begin ( ); request  != shoppingList.end ( ); )
        {
            auto found = m_articles.find (request->first );
            //finding exact matched names from shopping list
            if ( found != m_articles.end() && found->first == request->first ) {
                request->second = calculateShortage ( found, request->second, zeroSum );
            } else {
                //finding articles from shopping list,  mismatch by one char
                if ( calculateOneDiffChar ( request->first, tmpIter ) ) {
                    request->second = calculateShortage ( tmpIter, request->second, zeroSum );
                } else {
                    //not found article, update shortage list with this data
                    request->second = request->second;
                }
            }
            //removing sold article from shortage list by date
            if ( request->second == 0 )
            {
                auto tmpReq = request;
                request++;
                shoppingList.erase(tmpReq );
                continue;
            } else
                ++request;
        }

        //removing sold articles from main map
        for ( size_t i = 0; i < zeroSum.size ( ); ++i ) {
                m_articles.erase( zeroSum[i] );
        }
    }
    //method to get list of expires articles for given date
    list <pair < string, int>>  CSupermarket:: expired  ( const CDate & expireDate ) const
    {
        list <pair < string, int> > listExpiredArticles;
        int sum = 0;
        //traverse vector (inside  main map) of articles bty date, compare with expireDate ,
        for ( auto iterMap = m_articles.begin ( ); iterMap!= m_articles.end ( ); ++iterMap )
        {
            for ( auto storedArticle : iterMap->second->getListByDates() ) {
                if ( storedArticle->s_date > expireDate ){
                    break;
                }
                sum += storedArticle->s_count;
            }
            if ( sum != 0 ) {
                listExpiredArticles.emplace_back ( make_pair ( iterMap->first, sum ) ) ;
                sum = 0;
            }
        }
        //sorting by number of articles in ascending order
        listExpiredArticles.sort ( comparison ( ) );
        return listExpiredArticles;
    }



#ifndef __PROGTEST__
int main ( void )

{

    CSupermarket s;
    s.store ( "bread", CDate ( 2016, 4, 30 ), 100 )
            . store ( "butter", CDate ( 2016, 5, 10 ), 10 )
            . store ( "beer", CDate ( 2016, 8, 10 ), 50 )
            . store ( "bread", CDate ( 2016, 4, 25 ), 100 )
            . store ( "okey", CDate ( 2016, 7, 18 ), 5 );
    /*cout <<"-----------Before ----------------" << endl;
    s.print();*/
    list<pair<string,int> > l1 { { "bread", 2 }, { "Coke", 5 }, { "butter", 20 } };
    s . sell ( l1 );
    assert ( l1 . size () == 2 );
    assert ( ( l1 == list<pair<string,int> > { { "Coke", 5 }, { "butter", 10 } } ) );

    list<pair<string,int> > l2 = s . expired ( CDate ( 2016, 4, 30 ) );
    assert ( l2 . size () == 1 );
    assert ( ( l2 == list<pair<string,int> > { { "bread", 98 } } ) );
      /*cout << "-------------Expired -----------------" << endl;
      s.printList(l2);*/
    list<pair<string,int> > l3 = s . expired ( CDate ( 2016, 5, 20 ) );
    assert ( l3 . size () == 1 );
    assert ( ( l3 == list<pair<string,int> > { { "bread", 198 } } ) );

    list<pair<string,int> > l4 { { "bread", 105 } };
    s . sell ( l4 );
    assert ( l4 . size () == 0 );
    assert ( ( l4 == list<pair<string,int> > {  } ) );
    list<pair<string,int> > l5 = s . expired ( CDate ( 2017, 1, 1 ) );
    assert ( l5 . size () == 3 );
    assert ( ( l5 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "okey", 5 } } ) );
    s . store ( "Coke", CDate ( 2016, 12, 31 ), 10 );
    list<pair<string,int> > l6 { { "Cake", 1 }, { "Coke", 1 }, { "cake", 1 }, { "coke", 1 }, { "cuke", 1 }, { "Cokes", 1 } };
    s . sell ( l6 );
    //s.print();
    assert ( l6 . size () == 3 );
    assert ( ( l6 == list<pair<string,int> > { { "cake", 1 }, { "cuke", 1 }, { "Cokes", 1 } } ) );
    list<pair<string,int> > l7 = s . expired ( CDate ( 2017, 1, 1 ) );
    assert ( l7 . size () == 4 );
    assert ( ( l7 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "Coke", 7 }, { "okey", 5 } } ) );
    s . store ( "cake", CDate ( 2016, 11, 1 ), 5 );
    list<pair<string,int> > l8 { { "Cake", 1 }, { "Coke", 1 }, { "cake", 1 }, { "coke", 1 }, { "cuke", 1 } };
    s . sell ( l8 );
    assert ( l8 . size () == 2 );
    assert ( ( l8 == list<pair<string,int> > { { "Cake", 1 }, { "coke", 1 } } ) );

    list<pair<string,int> > l9 = s . expired ( CDate ( 2017, 1, 1 ) );
    assert ( l9 . size () == 5 );
    assert ( ( l9 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "Coke", 6 }, { "okey", 5 }, { "cake", 3 } } ) );
    list<pair<string,int> > l10 { { "cake", 15 }, { "Cake", 2 } };
    s . sell ( l10 );
    assert ( l10 . size () == 2 );
    assert ( ( l10 == list<pair<string,int> > { { "cake", 12 }, { "Cake", 2 } } ) );
    list<pair<string,int> > l11 = s . expired ( CDate ( 2017, 1, 1 ) );
    assert ( l11 . size () == 4 );
    assert ( ( l11 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "Coke", 6 }, { "okey", 5 } } ) );
    list<pair<string,int> > l12 { { "Cake", 4 } };
    s . sell ( l12 );
    assert ( l12 . size () == 0 );
    assert ( ( l12 == list<pair<string,int> > {  } ) );
    list<pair<string,int> > l13 = s . expired ( CDate ( 2017, 1, 1 ) );
    assert ( l13 . size () == 4 );
    assert ( ( l13 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "okey", 5 }, { "Coke", 2 } } ) );
    list<pair<string,int> > l14 { { "Beer", 20 }, { "Coke", 1 }, { "bear", 25 }, { "beer", 10 } };
    s . sell ( l14 );
    assert ( l14 . size () == 1 );
    assert ( ( l14 == list<pair<string,int> > { { "beer", 5 } } ) );
    s . store ( "ccccb", CDate ( 2019, 3, 11 ), 100 )
            . store ( "ccccd", CDate ( 2019, 6, 9 ), 100 )
            . store ( "dcccc", CDate ( 2019, 2, 14 ), 100 );

    list<pair<string,int> > l15 { { "ccccc", 10 } };
    s . sell ( l15 );
    assert ( l15 . size () == 1 );
    assert ( ( l15 == list<pair<string,int> > { { "ccccc", 10 } } ) );



  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
