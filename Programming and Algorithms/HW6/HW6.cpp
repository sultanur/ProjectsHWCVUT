#ifndef __PROGTEST__
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stdexcept>
#include <algorithm>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

class CDataType {

protected:
    string m_name= "";
    size_t m_size = 0;

public:
    virtual ~CDataType() {  }
    virtual CDataType * create ( ) const  = 0 ;

    virtual size_t getSize ( ) const { return m_size ; }
    const string & name ( ) const { return m_name ; }
    virtual void setName ( const string & name ) { this->m_name = name ;}
    virtual void print ( ostream & out  ) const = 0;
    friend ostream & operator << ( ostream & out , const CDataType & datatype ) {
        datatype.print( out );
        return out;
    }

    bool operator == ( const CDataType & obj ) const {
        return (typeid (*this) == typeid ( obj ) && isEqual( obj ) );
    }
    bool operator != ( const CDataType & obj ) const {
        return (  typeid (*this) != typeid ( obj )  || (! isEqual( obj ) ) ) ;
    }
    virtual bool isEqual (const CDataType & obj ) const = 0;

};
class CDataTypeInt: public CDataType
{
public:
    CDataTypeInt() { }
    virtual size_t getSize ( ) const override { return 4 ; }
    virtual CDataTypeInt * create ( void ) const override { return new CDataTypeInt( *this); }
    virtual void print ( ostream & out  ) const override {
        out << "int" << " ";
    }
    virtual bool isEqual ( const CDataType & obj ) const override {
       return true;
    }
};

class CDataTypeDouble: public CDataType
 {
 public:
     CDataTypeDouble() { }
     virtual size_t getSize ( ) const override { return 8 ; }
     virtual CDataTypeDouble * create ( void ) const override { return new CDataTypeDouble(*this ); }
     virtual void print ( ostream & out  ) const override { out << "double" << " "; }
     virtual  bool isEqual (const CDataType & obj ) const override {
         return true;
     }
};

class CDataTypeEnum: public CDataType
{
public:
    CDataTypeEnum( ) { }
    virtual size_t getSize ( ) const override { return 4 ; }
    virtual CDataTypeEnum * create ( void ) const override { return new CDataTypeEnum(*this ); }
    CDataTypeEnum & add ( const string & str ) {
        auto found = find_if ( m_argsEnum.begin( ), m_argsEnum.end( ),
                               [&str] ( const string & a ) { return a == str ; } ) ;
        if (found != m_argsEnum.end() ) {
            throw invalid_argument("Duplicate enum value: " + str) ;
        } else {
            m_argsEnum.emplace_back( str ) ;
        }
        return *this;
    }
    virtual void print ( ostream & out  ) const override {
        out << "enum" << "\n" << "{" << endl;
        for ( auto elem = m_argsEnum.begin(); elem != prev(m_argsEnum.end()); ++elem )
            out << (*elem) << ", " <<  endl;
        out << m_argsEnum.back() << "\n" << "} " ;

    }
    bool isEqual (const CDataType & obj ) const override {
        const CDataTypeEnum &castObj = static_cast<const CDataTypeEnum &>( obj );
        if ( this->m_argsEnum.size() != castObj.m_argsEnum.size() ) {
            return false;
        } else {
            for (size_t elem = 0; elem < this->m_argsEnum.size(); ++elem) {
                if (m_argsEnum[elem].compare(castObj.m_argsEnum[elem]) != 0) {
                    return false;
                }
            }
        }
        return true;
    }

private:
    vector < string> m_argsEnum;

};

class CDataTypeStruct: public CDataType
{
public:
    CDataTypeStruct() { }
    virtual size_t getSize ( ) const override { return m_StructSize ; }
    virtual CDataTypeStruct * create ( void ) const override { return new CDataTypeStruct(*this ); }
    CDataTypeStruct & addField ( const string & name, const CDataType & datatype ) {
        auto found = find_if ( m_fieldList.begin( ), m_fieldList.end( ),
                               [&name] ( const pair < string , shared_ptr<CDataType> > & a )
                               { return a.first == name ; } ) ;
        if (found == m_fieldList.end() ) {
            auto value = shared_ptr<CDataType>(datatype.create() );
            value->setName(name);
            m_StructSize += value->getSize();
            m_fieldList.push_back(make_pair(name, value) );
        }  else {
            throw invalid_argument( "Duplicate field: " + name );
        }
        return *this;

    }
    CDataType & field ( const string & name ) const {
        auto found = find_if ( m_fieldList.begin( ), m_fieldList.end( ),
                               [&name] ( const pair < string , shared_ptr<CDataType> > & a )
                               { return a.first == name ; } ) ;
        if (found != m_fieldList.end() ) {
            return  *found->second;
        } else {
            throw invalid_argument ("Unknown field: " + name);
        }
    }
    virtual void print ( ostream & out  ) const override {
        out << "struct \n" << "{ " << endl;
        auto last = m_fieldList.end()[-1];
        for ( auto & a : m_fieldList ) {
            a.second->print( out );
            out << a.first << ";" << endl;
            if (a.first == last.first ) {
                out << "}" << endl;
            }
        }
    }

    bool isEqual (const CDataType & obj ) const override {
        const CDataTypeStruct &castObj = static_cast< const CDataTypeStruct &>(obj);
        if (this->m_fieldList.size() != castObj.m_fieldList.size())
            return false;
        for (size_t elem = 0; elem < this->m_fieldList.size(); ++elem) {
            if (!(*(m_fieldList[elem].second) ==(*(castObj.m_fieldList[elem].second) ) ) )
                return false;
            }
            return true;
        }



private:
    size_t m_StructSize = 0;
    vector <pair < string, shared_ptr<CDataType> >> m_fieldList;

};
#ifndef __PROGTEST__
static bool        whitespaceMatch                         ( const string    & a,
                                                             const string    & b )
{
    string noWSpaceA = a;
    string noWSpaceB = b;
    noWSpaceA.erase (remove_if ( noWSpaceA.begin(), noWSpaceA.end(), ::isspace), noWSpaceA.end() );
    noWSpaceB.erase (remove_if ( noWSpaceB.begin(), noWSpaceB.end(), ::isspace), noWSpaceB.end() );
    if ( noWSpaceA.compare( noWSpaceB ) == 0 )
        return true;
    return false;
}
template <typename T_>
static bool        whitespaceMatch                         ( const T_        & x,
                                                             const string    & ref )
{
  ostringstream oss;
  oss << x;
  return whitespaceMatch ( oss . str (), ref );
}
int main ( void )
{
    using namespace std::string_literals;
    CDataTypeStruct  a = CDataTypeStruct () .
            addField ( "m_Length", CDataTypeInt () ) .
            addField ( "m_Status", CDataTypeEnum () .
            add ( "NEW" ) .
            add ( "FIXED" ) .
            add ( "BROKEN" ) .
            add ( "DEAD" ) ).
            addField ( "m_Ratio", CDataTypeDouble () );

    CDataTypeStruct b = CDataTypeStruct () .
            addField ( "m_Length", CDataTypeInt () ) .
            addField ( "m_Status", CDataTypeEnum () .
            add ( "NEW" ) .
            add ( "FIXED" ) .
            add ( "BROKEN" ) .
            add ( "READY" ) ).
            addField ( "m_Ratio", CDataTypeDouble () );

    CDataTypeStruct c =  CDataTypeStruct () .
            addField ( "m_First", CDataTypeInt () ) .
            addField ( "m_Second", CDataTypeEnum () .
            add ( "NEW" ) .
            add ( "FIXED" ) .
            add ( "BROKEN" ) .
            add ( "DEAD" ) ).
            addField ( "m_Third", CDataTypeDouble () );

    CDataTypeStruct  d = CDataTypeStruct () .
            addField ( "m_Length", CDataTypeInt () ) .
            addField ( "m_Status", CDataTypeEnum () .
            add ( "NEW" ) .
            add ( "FIXED" ) .
            add ( "BROKEN" ) .
            add ( "DEAD" ) ).
            addField ( "m_Ratio", CDataTypeInt () );

    assert ( whitespaceMatch ( a, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Status;\n"
                                  "  double m_Ratio;\n"
                                  "}") );

    assert ( whitespaceMatch ( b, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    READY\n"
                                  "  } m_Status;\n"
                                  "  double m_Ratio;\n"
                                  "}") );

    assert ( whitespaceMatch ( c, "struct\n"
                                  "{\n"
                                  "  int m_First;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Second;\n"
                                  "  double m_Third;\n"
                                  "}") );

    assert ( whitespaceMatch ( d, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Status;\n"
                                  "  int m_Ratio;\n"
                                  "}") );



    assert ( a == c );
    assert ( a != b );
    assert ( a != d );

    assert ( a . field ( "m_Status" ) == CDataTypeEnum () . add ( "NEW" ) . add ( "FIXED" ) . add ( "BROKEN" ) . add ( "DEAD" ) );
    assert ( a . field ( "m_Status" ) != CDataTypeEnum () . add ( "NEW" ) . add ( "BROKEN" ) . add ( "FIXED" ) . add ( "DEAD" ) );
    assert ( a != CDataTypeInt() );

    assert ( whitespaceMatch ( a . field ( "m_Status" ), "enum\n"
                                                         "{\n"
                                                         "  NEW,\n"
                                                         "  FIXED,\n"
                                                         "  BROKEN,\n"
                                                         "  DEAD\n"
                                                         "}") );


    CDataTypeStruct aOld = a;
    b . addField ( "m_Other", CDataTypeDouble ());
    a . addField ( "m_Sum", CDataTypeInt ());

    assert ( a != aOld );
    assert ( a != c );
    assert ( aOld == c );

    assert ( whitespaceMatch ( a, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Status;\n"
                                  "  double m_Ratio;\n"
                                  "  int m_Sum;\n"
                                  "}") );

    assert ( whitespaceMatch ( b, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    READY\n"
                                  "  } m_Status;\n"
                                  "  double m_Ratio;\n"
                                  "  double m_Other;\n"
                                  "}") );

    c . addField ( "m_Another", a . field ( "m_Status" ));

    assert ( whitespaceMatch ( c, "struct\n"
                                  "{\n"
                                  "  int m_First;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Second;\n"
                                  "  double m_Third;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Another;\n"
                                  "}") );

    d . addField ( "m_Another", a . field ( "m_Ratio" ));

    assert ( whitespaceMatch ( d, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Status;\n"
                                  "  int m_Ratio;\n"
                                  "  double m_Another;\n"
                                  "}") );


    assert ( a . getSize () == 20 );
    assert ( b . getSize () == 24 );


    try
    {
        a . addField ( "m_Status", CDataTypeInt () );
        assert ( "addField: missing exception!" == nullptr );
    }
    catch ( const invalid_argument & e )
    {
        assert ( e . what () == string("Duplicate field: m_Status"));
    }

    try
    {
        cout << a . field ( "m_Fail" ) << endl;
        assert ( "field: missing exception!" == nullptr );
    }
    catch ( const invalid_argument & e )
    {
        assert ( e . what () == string("Unknown field: m_Fail"));
    }

    try
    {
        CDataTypeEnum en;
        en . add ( "FIRST" ) .
                add ( "SECOND" ) .
                add ( "FIRST" );
        assert ( "add: missing exception!" == nullptr );
    }
    catch ( const invalid_argument & e )
    {
        assert ( e . what () == string("Duplicate enum value: FIRST") );
    }


  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
