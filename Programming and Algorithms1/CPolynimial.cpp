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

/*
The task is to develop a C++ class CPolynomial representing polynomials of arbitrary degree.

The class will store individual coefficients (floating point numbers - double precision), moreover, public interface will offer overloaded operators and methods to manipulate polynomials:

default constructor
    the constructor will prepare an object representing polynomial 0,
copy constructor
    the constructor will be implemented if your internal representation requires it,
destructor
    destructor will be present if your internal representation requires it,
overloaded operator=
    the operator will copy the contents from one instance to another (if the automatically generated op= cannot be used with your implementation).
operator <<
    will output a textual form of the polynomial into an output stream. The output formatting must follow these rules:

        the polynomial will be displayed in a decreasing order of powers, i.e. from the highest power of x,terms with zero coefficient are not displayed in the output,
        terms with coefficient +1 and -1 are displayed without the coefficient (just a power of x),
        there are not unnecessary - in the output (i.e. x - 9 or - x^2 + 4 is OK, whereas x + (-9) is not),
        zero polynomial will be displayed as 0.

operator +
    adds two polynomials,
operator -
    subtracts two polynomials,
operator *
    multiplies given polynomial either with a double, or with another polynomial,
operators == and !=
    compare two polynomials,
operator []
    is used to access (read / write) individual coefficients, the term is determined by the index (0 = absolute, 1 = x, 2 = x^2, ... ). The read form must be available even on const instances,
operator ()
    evaluates the value of the polynomial for the given value x (x is a double),
Degree()
    the method returns the degree of the polynomial (e.g. x^3+4 has degree of 3, 5 has degree 0, specifically 0 has degree 0).

Submit a source file with your implementation of CPolynomial class. The submitted file shall not contain any #include directives nor main function. If your main function or #include remains in the file, please place them into a conditional compile block.

This task does not provide the required class interface. Instead, you are expected to develop the interface yourself. Use the description above, the attached examples, and your knowledge of overloaded operators.
Advice

    The testing environment uses output operator (<<) and indexing operator [] to examine your instance. If your overloaded operators << and [] do not work properly, the tests will be negative. The testing environment accepts small differences up to 0.1 ‰ when comparing the floating point values.
    Implement the output operator properly -- do not blindly sent the data to cout. Instead, send the data to the output stream passed as the parameter. Do not add any extra whitespace/newline characters.
    If your program does not compile (and especially if it compiles locally, however it does not compile in Progtest), there might be some problem in your interface design. Check your operator overloads, pay special attention to const qualifiers.
    The bonus test requires very fast polynomial multiplication. The test multiplies polynomials of degree approx. 100000. Naive solution cannot pass the test, an efficient algorithms is required.
    CPolynomial class is tested for copying. Your implementation must include copy cons/op= if the implementation cannot use automatically generated copy cons/op=.
    STL classes std::vector and std::string are available. However, the rest of STL is not.

A solution of this problem may be used for code review if it passes all mandatory tests with 100 % results.

*/

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
