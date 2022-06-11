#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>

using namespace std;
#endif /* __PROGTEST__ */

class CVATRegister {

private:
    struct Company {
        Company ( const string &name, const string &address, const string &taxID ) : m_name ( name ), m_address ( address ), m_taxID ( taxID ) { }
        Company ( const string &name, const string &address ) : m_name ( name ), m_address ( address ) { }

        string m_name;
        string m_address;
        string m_taxID;
        unsigned int m_sumIncomes = 0;
    };

    struct ID {
        ID ( string taxID, shared_ptr <Company> & company ) : m_taxID ( taxID ), m_company( company ) { }
        ID ( string taxID) : m_taxID( taxID ) { }

        string m_taxID;
        shared_ptr <Company> m_company;
    };

    vector <shared_ptr<ID>> m_companyIDs;
    vector <shared_ptr<Company>> m_companyList;

    vector<unsigned int> m_maxHeap;
    vector<unsigned int> m_minHeap;
    bool m_start  = true;
    unsigned int m_median = 0;

public:
    CVATRegister  ( void )  { }
    ~CVATRegister ( void )  { }

    bool newCompany             ( const string & name, const string & addr, const string & taxID );
    bool cancelCompany          ( const string & name, const string & addr );
    bool cancelCompany          ( const string & taxID );
    bool invoice                ( const string & taxID, unsigned int amount );
    bool invoice                ( const string & name, const string & addr, unsigned int amount );
    bool audit                  ( const string & name, const string & addr, unsigned int & sumIncome ) const;
    bool audit                  ( const string & taxID, unsigned int & sumIncome ) const;
    bool firstCompany           ( string & name, string & addr ) const;
    bool nextCompany            ( string & name, string & addr ) const;
    unsigned int medianInvoice  ( void ) const;

    bool isUniqueID         ( const string & taxID ) {
        for ( auto &id: m_companyIDs )
            if ( ( id->m_taxID.compare (taxID ) ) == 0 )
                return false;
        return true;
    }
    static int compare_ints ( const void *a, const void *b ) {
        int arg1 = * ( const int * ) a;
        int arg2 = * ( const int * ) b;

        if ( arg1 < arg2 ) return -1;
        if ( arg1 > arg2 ) return 1;
        return 0;
    }
    void addIncome          ( shared_ptr <Company> & company, const unsigned int & amount ) {
        company->m_sumIncomes += amount;
    }
    void findingNameAddr    ( const string &name, const string & addr, vector <shared_ptr<Company>>::iterator & index, bool & flag )  {
        auto compareFuncNA =
                [] ( const Company & r, const pair <string, string> & l ) {
                    if ( strcasecmp(r.m_name.c_str(), l.first.c_str( ) ) != 0 )
                        return strcasecmp(r.m_name.c_str(), l.first.c_str());
                    else return strcasecmp(r.m_address.c_str(), l.second.c_str());
                };
        index = lower_bound (m_companyList.begin ( ), m_companyList.end ( ), make_pair (name, addr ),
                                 [&] ( const shared_ptr <Company> & r, const pair <string, string> & l ) {
                                     return ( compareFuncNA (*r, l ) < 0 );
                                 } );
        if ( index != m_companyList.end ( ) && compareFuncNA (**index, make_pair (name, addr ) ) == 0 ) {
            flag = true;
        } else flag = false;
    }
    void findingTaxID       ( const string & taxID, vector <shared_ptr<ID>>::iterator & indexID, bool & flag )  {
        auto compareFuncID =
                [] ( const ID & r, const string & l ) {
                    return ( r.m_taxID.compare (l ) );
                };
        indexID = lower_bound (m_companyIDs.begin( ), m_companyIDs.end( ), taxID,
                                   [&] ( const shared_ptr <ID> &r, const string & l ) {
                                       return ( compareFuncID ( *r, l ) < 0 );
                                   } );
        if (indexID != m_companyIDs.end( )  && compareFuncID ( **indexID, taxID ) == 0 ) {
            flag = true;
        }
        else flag = false;
    }

    void print              ( std::string text, std::vector <unsigned int> const &v = { } ) const {
        cout << text << ": ";
        for ( const auto &e: v )
            cout << e << ' ';
        cout << '\n';
    }
    void minMaxHeap         ( unsigned int amount ) {
        if ( m_start ) {
            m_median = amount;
            m_maxHeap.push_back ( amount );
            m_start = false;
            return;
        } else if ( !m_start && ( amount >= m_median ) ) {
            m_minHeap.push_back(amount);
            push_heap(m_minHeap.begin(), m_minHeap.end(), greater<>{});
        } else if ( !m_start && ( amount < m_median ) ) {
            m_maxHeap.push_back ( amount ) ;
            push_heap (m_maxHeap.begin ( ), m_maxHeap.end( ) );
        }

        int diffSize = 0;
        ( m_minHeap.size( ) > m_maxHeap.size( ) ) ? diffSize = ( m_minHeap.size( ) - m_maxHeap.size( ) ) : diffSize = ( m_maxHeap.size( ) - m_minHeap.size( ) );

        if ( diffSize == 0 ) {
            /*print(" maxHeap", maxHeap);
            print(" minHeap", minHeap);*/
            m_median = m_minHeap.front( );
        }
        if ( diffSize == 1 ) {
            if ( m_minHeap.size( ) > m_maxHeap.size( ) ) {
                m_median = m_minHeap.front( );
                /*print(" maxHeap", maxHeap);
                print(" minHeap", minHeap);*/
            } else if ( m_minHeap.size( ) < m_maxHeap.size( ) ) {
                /*print(" maxHeap", maxHeap);
                print(" minHeap", minHeap);*/
                m_median = m_maxHeap.front( );
            }
        }
        if ( diffSize > 1 ) {
            if ( m_minHeap.size( ) > m_maxHeap.size( ) ) {
                pop_heap (m_minHeap.begin( ), m_minHeap.end( ), std::greater<>{ } );
                unsigned int tmp = m_minHeap.back( );
                m_minHeap.pop_back( );
                m_maxHeap.push_back( tmp );
                push_heap (m_maxHeap.begin( ), m_maxHeap.end( ) );
                /*print(" maxHeap", maxHeap);
                print(" minHeap", minHeap);*/
                m_median = m_minHeap.front( );
            } else {
                pop_heap (m_maxHeap.begin( ), m_maxHeap.end( ) );
                unsigned int tmp = m_maxHeap.back( );
                m_maxHeap.pop_back( );
                m_minHeap.push_back( tmp );
                push_heap(m_minHeap.begin( ), m_minHeap.end( ), greater<>{ } );
                /*print(" maxHeap", maxHeap);
                print(" minHeap", minHeap);*/
                m_median = m_minHeap.front( );
            }
        }
    }

    };

bool CVATRegister:: newCompany      ( const string & name, const string & addr, const string & taxID ) {
    if ( !isUniqueID ( taxID ) )
        return false;

    vector <shared_ptr<Company>> ::iterator indexNA;
    bool foundNA, foundID;
    findingNameAddr ( name, addr, indexNA, foundNA );
    if ( foundNA )
        return false;
    shared_ptr<Company> newCompany ( nullptr );
    newCompany = make_shared <Company> ( name, addr, taxID );
    m_companyList.insert (indexNA, newCompany );

    vector <shared_ptr<ID>> ::iterator indexID;
    findingTaxID ( taxID, indexID, foundID );
    if ( foundID )
        return false;
    auto companyID = make_shared<ID>(taxID, newCompany );
    m_companyIDs.insert (indexID, companyID );
    return true;
}
bool CVATRegister:: cancelCompany   ( const string & name, const string & addr ) {
    vector <shared_ptr<Company>> ::iterator indexNA;
    bool foundNA, foundID;
    findingNameAddr ( name, addr, indexNA, foundNA );
    if ( foundNA ) {
        string taxID = ( *indexNA )->m_taxID;
        vector < shared_ptr < ID >> ::iterator indexID;
        findingTaxID ( taxID, indexID, foundID );
        if ( foundID ) {
            m_companyIDs.erase (indexID );
        } else return false;
     m_companyList.erase(indexNA );
    } else
        return false;

    return true;
}
bool CVATRegister:: cancelCompany   ( const string & taxID ) {
    bool foundID, foundNA;
    vector <shared_ptr <ID>> ::iterator indexID;
    findingTaxID ( taxID, indexID, foundID );
    if ( foundID ) {
        string name = ( *indexID )->m_company->m_name;
        string addr = ( *indexID )->m_company->m_address;
        vector <shared_ptr<Company>> ::iterator indexNA;
        findingNameAddr(name, addr, indexNA, foundNA );
        if ( foundNA ) {
            m_companyList.erase(indexNA );
        } else
            return false;
        m_companyIDs.erase(indexID );
    } else return false;

    return true;
}
bool CVATRegister:: invoice         ( const string & taxID, unsigned int amount ) {
    bool foundID;
    vector <shared_ptr<ID>>:: iterator indexID;
    findingTaxID ( taxID, indexID, foundID );
    if ( foundID ) {
        addIncome(( ( **indexID ).m_company ), amount );
        if ( amount > 0 )
            minMaxHeap ( amount);
    } else return false;
    return true;
}
bool CVATRegister:: invoice         ( const string & name, const string & addr, unsigned int amount ) {
    vector <shared_ptr<Company>>::iterator indexNA;
    bool foundNA;
    findingNameAddr ( name, addr, indexNA, foundNA );
    if ( foundNA ) {
        auto tmpCompany = make_shared<Company>(name, addr, ( *indexNA )->m_taxID );
        addIncome (*( indexNA ), amount );
        if ( amount > 0 )
            minMaxHeap (amount) ;
    } else
        return false;

    return true;
}
bool CVATRegister:: audit           ( const string & name, const string & addr, unsigned int & sumIncome ) const {
    auto compareFuncNA =
            [] ( const Company & r, const pair<string, string > & l ) {
                if ( strcasecmp (r.m_name.c_str ( ), l.first.c_str ( ) ) != 0 )
                    return strcasecmp (r.m_name.c_str ( ), l.first.c_str ( ) );
                else return strcasecmp (r.m_address.c_str ( ), l.second.c_str ( ) );
            };
    auto index = lower_bound (m_companyList.begin( ), m_companyList.end( ), make_pair (name, addr ),
                             [&]  ( const shared_ptr<Company> & r, const pair <string, string> & l ) {
                                 return ( compareFuncNA (*r, l ) < 0 );
                             } );
    if ( index != m_companyList.end ( ) && compareFuncNA (**index, make_pair (name, addr) ) == 0 ) {
        sumIncome = ( *index )->m_sumIncomes;
    } else
        return false;
    return true;
}
bool CVATRegister:: audit           ( const string & taxID, unsigned int & sumIncome ) const {
    auto compareFuncID =
            [] ( const ID & r, const string & l ){
                return ( r.m_taxID.compare (l ) );
            };
    auto indexID = lower_bound (m_companyIDs.begin( ), m_companyIDs.end( ), taxID,
                               [&] ( const shared_ptr<ID> & r, const string & l ) {
                                   return ( compareFuncID (*r, l ) < 0 );
                               } );
    if ( indexID != m_companyIDs.end( )  && compareFuncID (**indexID, taxID) == 0 ) {
        sumIncome = ( **indexID ).m_company->m_sumIncomes;
    } else
        return false;
    return true;
}
bool CVATRegister:: firstCompany    ( string & name, string & addr ) const {
    if ( m_companyList.empty( ) )
        return false;
    else {
        name = m_companyList.front( )->m_name;
        addr = m_companyList.front( )->m_address;
    }
    return true;
}
bool CVATRegister:: nextCompany     ( string & name, string & addr ) const {
    if ( m_companyList.empty( ) )
        return false;
    auto campFuncCompare =
            [] ( const Company& r, const pair<string, string >  t ) {
                if ( strcasecmp (r.m_name.c_str( ), t.first.c_str( ) ) != 0 )
                    return strcasecmp (r.m_name.c_str( ), t.first.c_str( ) );
                else return strcasecmp (r.m_address.c_str( ), t.second.c_str( ) );
            };
    auto index = lower_bound (m_companyList.begin( ), m_companyList.end( ), make_pair (name, addr ),
                             [&] ( const shared_ptr<Company> &r, const pair <string, string> & t ) {
                                 return ( campFuncCompare(*r, t ) < 0 );
                             } );
    if ( index != m_companyList.end ( ) && campFuncCompare (**index, make_pair (name, addr) ) == 0 ) {
        if ( ( index+1 ) == m_companyList.end( ) )
            return false;
        name = ( **( index + 1 ) ).m_name;
        addr = ( **( index + 1 ) ).m_address;
    }
    else
        return false;

    return true;

}
unsigned int CVATRegister:: medianInvoice  ( void ) const {
    return m_median;
}

#ifndef __PROGTEST__
int               main           ( void )
{
    string name, addr;
    unsigned int sumIncome;
    CVATRegister b1;
    assert ( b1 . newCompany ( "ACME", "Thakurova", "666/666" ) );
    assert ( b1 . newCompany ( "ACME", "Kolejni", "666/666/666" ) );
    assert ( b1 . newCompany ( "Dummy", "Thakurova", "123456" ) );
    assert ( b1 . invoice ( "666/666", 2000 ) );
    assert ( b1 . medianInvoice () == 2000 );
    assert ( b1 . invoice ( "666/666/666", 3000 ) );
    assert ( b1 . medianInvoice () == 3000 );
    assert ( b1 . invoice ( "123456", 4000 ) );
    assert ( b1 . medianInvoice () == 3000 );
    assert ( b1 . invoice ( "aCmE", "Kolejni", 5000 ) );
    assert ( b1 . medianInvoice () == 4000 );
    assert ( b1 . audit ( "ACME", "Kolejni", sumIncome ) && sumIncome == 8000 );
    assert ( b1 . audit ( "123456", sumIncome ) && sumIncome == 4000 );
    assert ( b1 . firstCompany ( name, addr ) && name == "ACME" && addr == "Kolejni" );
    assert ( b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova" );
    assert ( b1 . nextCompany ( name, addr ) && name == "Dummy" && addr == "Thakurova" );
    assert ( ! b1 . nextCompany ( name, addr ) );
    assert ( b1 . cancelCompany ( "ACME", "KoLeJnI" ) );
    assert ( b1 . medianInvoice () == 4000 );
    assert ( b1 . cancelCompany ( "666/666" ) );
    assert ( b1 . medianInvoice () == 4000 );
    assert ( b1 . invoice ( "123456", 100 ) );
    assert ( b1 . medianInvoice () == 3000 );
    assert ( b1 . invoice ( "123456", 300 ) );
    assert ( b1 . medianInvoice () == 3000 );
    assert ( b1 . invoice ( "123456", 200 ) );
    assert ( b1 . medianInvoice () == 2000 );
    assert ( b1 . invoice ( "123456", 230 ) );
    assert ( b1 . medianInvoice () == 2000 );
    assert ( b1 . invoice ( "123456", 830 ) );
    assert ( b1 . medianInvoice () == 830 );
    assert ( b1 . invoice ( "123456", 1830 ) );
    assert ( b1 . medianInvoice () == 1830 );
    assert ( b1 . invoice ( "123456", 2830 ) );
    assert ( b1 . medianInvoice () == 1830 );
    assert ( b1 . invoice ( "123456", 2830 ) );
    assert ( b1 . medianInvoice () == 2000 );
    assert ( b1 . invoice ( "123456", 3200 ) );
    assert ( b1 . medianInvoice () == 2000 );
    assert ( b1 . firstCompany ( name, addr ) && name == "Dummy" && addr == "Thakurova" );
    assert ( ! b1 . nextCompany ( name, addr ) );
    assert ( b1 . cancelCompany ( "123456" ) );
    assert ( ! b1 . firstCompany ( name, addr ) );

    CVATRegister b2;
    assert ( b2 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
    assert ( b2 . newCompany ( "Dummy", "Kolejni", "123456" ) );
    assert ( ! b2 . newCompany ( "AcMe", "kOlEjNi", "1234" ) );
    assert ( b2 . newCompany ( "Dummy", "Thakurova", "ABCDEF" ) );
    assert ( b2 . medianInvoice () == 0 );
    assert ( b2 . invoice ( "ABCDEF", 1000 ) );
    assert ( b2 . medianInvoice () == 1000 );
    assert ( b2 . invoice ( "abcdef", 2000 ) );
    assert ( b2 . medianInvoice () == 2000 );
    assert ( b2 . invoice ( "aCMe", "kOlEjNi", 3000 ) );
    assert ( b2 . medianInvoice () == 2000 );
    assert ( ! b2 . invoice ( "1234567", 100 ) );
    assert ( ! b2 . invoice ( "ACE", "Kolejni", 100 ) );
    assert ( ! b2 . invoice ( "ACME", "Thakurova", 100 ) );
    assert ( ! b2 . audit ( "1234567", sumIncome ) );
    assert ( ! b2 . audit ( "ACE", "Kolejni", sumIncome ) );
    assert ( ! b2 . audit ( "ACME", "Thakurova", sumIncome ) );
    assert ( ! b2 . cancelCompany ( "1234567" ) );
    assert ( ! b2 . cancelCompany ( "ACE", "Kolejni" ) );
    assert ( ! b2 . cancelCompany ( "ACME", "Thakurova" ) );
    assert ( b2 . cancelCompany ( "abcdef" ) );
    assert ( b2 . medianInvoice () == 2000 );
    assert ( ! b2 . cancelCompany ( "abcdef" ) );
    assert ( b2 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
    assert ( b2 . cancelCompany ( "ACME", "Kolejni" ) );
    assert ( ! b2 . cancelCompany ( "ACME", "Kolejni" ) );

    return EXIT_SUCCESS;}
#endif /* __PROGTEST__ */