#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cmath>
#include <cfloat>
#include <cassert>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#if defined ( __cplusplus ) && __cplusplus > 199711L /* C++ 11 */
#include <memory>
#endif /* C++ 11 */
using namespace std;
#endif /* __PROGTEST__ */

class CPolynomial
{
  public:
    // default constructor
    CPolynomial  ( );
    ~CPolynomial( ) ;
    // operator +
    CPolynomial operator + ( const CPolynomial & polynomial ) const;
    // operator -
    CPolynomial operator - ( const CPolynomial & polynomial ) const;
    // operator * (polynomial, double)
    CPolynomial operator * ( const CPolynomial & polynomial ) const;
    
    CPolynomial operator * ( const double      & number ) const;
    // operator ==
    bool operator   ==   ( const CPolynomial & polynomial ) const;
    // operator !=
    bool operator   !=   ( const CPolynomial& polynomial ) const;
    // operator []
    double&   operator [] ( const unsigned int & index );
    double    operator [] ( const unsigned int & number ) const;
    // operator ()
    double  operator ( ) ( const double& number ) const;
    // Degree (), returns unsigned value
    unsigned int  Degree ( ) const;
    
    friend std::ostream & operator << ( std::ostream & out, const CPolynomial & polynomial );
     
  private:
    // todo
    vector <double> m_coeff = { 0 };
};

  CPolynomial:: CPolynomial( )  { }

  CPolynomial:: ~CPolynomial( ) { }

  CPolynomial CPolynomial:: operator + ( const CPolynomial & polynomial ) const {
      CPolynomial result;
      vector<double> higher;
      vector<double> lower; 

      if ( m_coeff.size() < polynomial.m_coeff.size( ) ) {
        higher = polynomial.m_coeff;
      } else {
        higher = m_coeff;
      }

      if ( m_coeff.size() < polynomial.m_coeff.size( ) ) {
        lower = m_coeff;
      } else {
        lower = polynomial.m_coeff;
      }

    result.m_coeff.resize( higher.size( ) );

    for ( unsigned int i = 0; i < lower.size(); i++ ) {
      result.m_coeff [i] = m_coeff [i] + polynomial.m_coeff [i];
    }

    for ( unsigned int j = (unsigned int)lower.size( ); j < higher.size( ); j++ ) {
      result.m_coeff [j] = higher [j];
    }
      return result;
  }
    
     
  CPolynomial CPolynomial:: operator - ( const CPolynomial & polynomial ) const {
    CPolynomial result;
    vector<double> higher;
    vector<double> lower; 

    if ( m_coeff.size() < polynomial.m_coeff.size( ) ) {
        higher = polynomial.m_coeff;
      } else {
        higher = m_coeff;
      }

      if ( m_coeff.size() < polynomial.m_coeff.size( ) ) {
        lower = m_coeff;
      } else {
        lower = polynomial.m_coeff;
      }

    result.m_coeff.resize( higher.size( ) );

    for ( unsigned int i = 0; i < lower.size(); i++ ) {
      result.m_coeff [i] = m_coeff [i] - polynomial.m_coeff [i];
    }

    for ( unsigned int j = (unsigned int)lower.size( ); j < higher.size( ); j++ ) {
      if (higher == m_coeff) {
            result.m_coeff [j] = m_coeff [j];
        } else {
            result.m_coeff [j] = -polynomial.m_coeff [j];
        }
    }

    return result;
  }

CPolynomial CPolynomial::operator * ( const CPolynomial& polynomial ) const {
    CPolynomial result;
    unsigned int newSize = polynomial.m_coeff.size( ) + m_coeff.size( ) - 1;
    result.m_coeff.resize( newSize );

    for ( unsigned int i = 0; i < polynomial.m_coeff.size( ); i++ ) {
        for ( unsigned int j = 0; j < m_coeff.size(); ++j) {
            result.m_coeff [i + j] += polynomial.m_coeff [i] * m_coeff [j];
        }
    }

    return result;
}

CPolynomial CPolynomial:: operator * ( const double & number ) const {
  CPolynomial result;

  for ( unsigned int i = 0; i < m_coeff.size( ); i++ ) {
      result[i] = m_coeff [i] * number;
    }

  return result;
}

bool CPolynomial:: operator == ( const CPolynomial & polynomial ) const {
  vector<double> higher;
  vector<double> lower;
  
  if ( m_coeff.size( ) < polynomial.m_coeff.size( ) ) { 
       higher = polynomial.m_coeff;
  } else  { 
       higher = m_coeff;
  }

  if ( m_coeff.size( ) < polynomial.m_coeff.size( ) ) {
    lower = m_coeff;
  } else {
    lower = polynomial.m_coeff;
  }
  
  for (unsigned int i = 0; i < lower.size(); i++) {
        if ( lower[i] != higher[i]) 
          return false;     
  } 

  for ( unsigned int j = lower.size(); j < higher.size(); j++ ) {
        if ( higher [j] != 0 ) 
          return false;      
  }

    return true;
}


bool CPolynomial:: operator != (const CPolynomial& polynomial) const {
  vector<double> higher;
  vector<double> lower;
  
  if ( m_coeff.size( ) < polynomial.m_coeff.size( ) ) { 
       higher = polynomial.m_coeff;
  } else  { 
       higher = m_coeff;
  }

  if ( m_coeff.size( ) < polynomial.m_coeff.size( ) ) {
    lower = m_coeff;
  } else {
    lower = polynomial.m_coeff;
  }
  
  for (unsigned int i = 0; i < lower.size(); i++) {
    if ( lower[i] != higher[i]) 
        return true;  
  }

  for ( unsigned int j = lower.size(); j < higher.size(); j++ ) { 
    if ( higher [j] == 0 ) 
        return false;  
  }
    return true;

}

double&  CPolynomial:: operator [] (const unsigned int & index ) {
    if ( Degree( ) <= index ) {
        m_coeff.resize( index + 1 );
    }

    return m_coeff [index];
}

double CPolynomial::operator [] (const unsigned int & index) const {
    if ( m_coeff.size() <= index ) {
        return 0;
    }

    return m_coeff [index];
}

double CPolynomial::operator ( ) ( const double& value ) const {
  double result = 0;

    for ( unsigned int i = 0; i < m_coeff.size(); i++ ) {
        result += ( m_coeff [i] * ( std::pow(value, i ) ) );
    }

    return result;
}

unsigned int CPolynomial::Degree ( ) const {
    for ( long int i = m_coeff.size( ) - 1; i >= 0; i-- ) {
        if ( m_coeff [i] != 0 ) {
            return ( unsigned int ) i;
        }
    }

    return 0;
}

// "- x^5"
// "0"

// "2*x^8 + 7*x^6 - 20*x^5"
// "x^3 + 3.5*x^1 - 10"
// "- 2*x^3 - 7*x^1 + 20"
// "- x^5 - 2*x^3 - 7*x^1 + 20"
// "x^5 - 2*x^3 - 7*x^1 + 20"
std::ostream & operator << (std::ostream & out, const CPolynomial& polynomial) 
{
  
  bool isFirstElement = true;

  if (polynomial.m_coeff.size() <= 1) {
      out << "0";
      return out;
  }

  for ( long int i = polynomial.m_coeff.size() - 1; i >= 0; i-- ) {
      if (polynomial.m_coeff [i] == 0 && i != 0 ) {
            continue;
      } else if (polynomial.m_coeff [i] == 0 && i == 0 && isFirstElement  == false) {
            break;
      }
  
      if ( i == 0 ) {
          if ( polynomial.m_coeff [i] < 0 && isFirstElement == true )         {
              out << "- "  << -polynomial.m_coeff [i];
          }else if ( polynomial.m_coeff [i] < 0 && isFirstElement == false  ) {
              out <<  " - "  << -polynomial.m_coeff [i];
          } else if ( polynomial.m_coeff [i] > 0 && isFirstElement == true  ) {
              out << ""  << polynomial.m_coeff[i];
          } else if ( polynomial.m_coeff [i] > 0 && isFirstElement == false ) {
              out << " + "  << polynomial.m_coeff[i]; 
        }   
          isFirstElement = false;
          continue;        
      }
    
      if ( polynomial.m_coeff [i] == 1 && isFirstElement == true ) {
          out << "x^"  << i;
      } else if ( polynomial.m_coeff [i] == 1 && isFirstElement == false ) {            
          out << " + x^" << i;
      } else if ( polynomial.m_coeff [i] == -1 && isFirstElement == true )  {
          out << "- x^" << i;
      } else if ( polynomial.m_coeff [i] == -1 && isFirstElement == false )  {
          out << " - x^" << i;
      } else if ( polynomial.m_coeff [i] < 0   && isFirstElement == true )   {
          out << "- " << -polynomial.m_coeff [i] << "*x^" << i;
      } else if ( polynomial.m_coeff [i] < 0   && isFirstElement == false )  {
          out << " - " << -polynomial.m_coeff [i] << "*x^" << i;
      } else if ( polynomial.m_coeff [i] > 0   &&  isFirstElement == true )  {
          out << "" << polynomial.m_coeff [i] << "*x^"<< i;  
      } else if ( polynomial.m_coeff [i] > 0   &&  isFirstElement == false )  {
          out << " + " << polynomial.m_coeff [i] << "*x^" << i;
          }
      // "2*x^8 + 7*x^6 - 20*x^5"
      // "x^3 + 3.5*x^1 - 10"
    
      isFirstElement = false;
  }

    return out;
}


#ifndef __PROGTEST__
bool  smallDiff  ( double  a,
                   double  b )
{

  return true; 
}

bool  dumpMatch ( const CPolynomial & x,
                  const vector<double> & ref )
{

  return true; 

}

int  main  ( void )
{
  CPolynomial a, b, c;
  ostringstream out;
  a[0] = -10;
  a[1] = 3.5;
  a[3] = 1;
  assert ( smallDiff ( a ( 2 ), 5 ) );
  out . str ("");
  out << a;
  out.str();
  assert ( out . str () == "x^3 + 3.5*x^1 - 10" );
  a = a * -2;
  assert ( a . Degree () == 3
           && dumpMatch ( a, vector<double>{ 20.0, -7.0, -0.0, -2.0 } ) );

  out . str ("");
  out << a;
  assert ( out . str () == "- 2*x^3 - 7*x^1 + 20" ); 
  out . str ("");
  out << b;
  assert ( out . str () == "0" );
  b[5] = -1;
  out . str ("");
  out << b;
  assert ( out . str () == "- x^5" );
  c = a + b;
  assert ( c . Degree () == 5
           && dumpMatch ( c, vector<double>{ 20.0, -7.0, 0.0, -2.0, 0.0, -1.0 } ) );

  out . str ("");
  out << c;
  assert ( out . str () == "- x^5 - 2*x^3 - 7*x^1 + 20" );
  c = a - b;
  assert ( c . Degree () == 5
           && dumpMatch ( c, vector<double>{ 20.0, -7.0, -0.0, -2.0, -0.0, 1.0 } ) );

  out . str ("");
  out << c;
  assert ( out . str () == "x^5 - 2*x^3 - 7*x^1 + 20" );
  c = a * b;
  assert ( c . Degree () == 8
           && dumpMatch ( c, vector<double>{ -0.0, -0.0, 0.0, -0.0, 0.0, -20.0, 7.0, -0.0, 2.0 } ) );

  out . str ("");
  out << c;
  assert ( out . str () == "2*x^8 + 7*x^6 - 20*x^5" );
  assert ( a != b );
  b[5] = 0;
  assert ( !(a == b) );
  a = a * 0;
  assert ( a . Degree () == 0
           && dumpMatch ( a, vector<double>{ 0.0 } ) );

  assert ( a == b ); 
  return 0;
}
#endif /* __PROGTEST__ */
