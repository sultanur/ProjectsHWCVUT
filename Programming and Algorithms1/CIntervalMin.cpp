#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <forward_list>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */


/*
The task is to develop class template CIntervalMin. The class will store values similarly to std::vector, moreover, it will provide an interface to quickly search for minimum values in subintervals.

To make the class more flexible, there will be two generic parameters:

    T_ is the data type of the data stored in the instance. T_ may be an ordinary integer, floating point, std::string, or some other data type. Type T_ supports at least the following operations: copying/moving (move/copy constructible, move/copy assignable), comparison by operator <, output to a stream via operator <<, and destruction (destructible). The type may provide some further interface, however, your implementation cannot rely on it. Caution, the type does not have to implement default constructor!
    Cmp_ is an optional generic parameter for the comparator. The comparator is either a function object, a function, a lambda function, or the generic parameter is omitted (in which case the comparator fallbacks to the std::less from the STL library).

The interface of the class:

    Constructor (optionally with a comparator) creates an empty object instance.
    Constructor with a pair of iterators (and with an optional comparator) initializes the instance with the data copied from the range defined by the input iterators.
    Destructor (if needed)
    Method push_back ( val ) appends the value to the end of the internal storage.
    Method pop_back () removes the last value from the internal storage.
    Method size () returns the number of elements stored in the instance.
    Data type const_iterator declares an iterator suitable to access the values stored in a CIntervalMin instance. The iterator must provide random access iterator interface similar to the std::vector iterator. The iterator is a read only iterator (it does not provide an interface to modify the values stored in the CIntervalMin instance).
    Method begin () returns a const_iterator referencing the first element in the store.
    Method end () returns a const_iterator referencing one past the last element in the store.
    Method min (st, en) finds the minimum element in the range defined by the iterators in parameters. The minimum element is then returned to the caller. If defined, the method compares the elements by means of the comparator passed to the constructor. Conversely, the elements will be compared by operator < if the instance does not have a special comparator defined. If there is more than one "minimum" in the range, the method returns the value closest to the iterator st. If the minimum is not defined (e.g., st == en, meaning an empty interval), then the method throws exception std::invalid_argument.

Submit a source file with your CIntervalMin template implementation. Moreover, add any further class (or classes) your implementation requires. The class must follow the public interface above. If there is a mismatch in the interface, the compilation will fail. You may extend the interface and add your own auxiliary methods and member variables (both public and private, although private are preferred). The submitted file must include both declarations as well as implementation of the class (the methods may be implemented inline but do not have to). The submitted file shall not contain anything unnecessary. In particular, if the file contains main, your tests, or any #include definitions, please, keep them in a conditional compile block. Use the template below as a basis for your implementation. If the preprocessor definitions are preserved, the file maybe submitted to Progtest.

Use STL to develop the class. The available headers are listed in the attached source.

There are mandatory and optional tests in this homework. There optional test inputs many values, moreover, it searches for minimum over long intervals. The naive algorithm is too slow to finish the search in time. To pass the bonus, implement some more efficient algorithm, you may adapt some variant of range-minimum-query algorithm.

The basic solution of this homework is very simple, thus it cannot be used for code review. On the other hand, a solution that passes the speed test (i.e., results in 100% points) may be submitted to the code review.
Advice:

    Use some STL container to store the values, e.g., std::vector.
    You do not have to implement const_iterator by yourself. Consider using some existing iterator (hint: using keyword).
    The following may help with the design of the efficient algorithm:
        minimum is computed very often, for long intervals,
        some data preprocessing is needed,
        the preprocessing must be efficient. You cannot preprocess everything from scratch with each invocation of push_back or pop_back,
        the testing mixes calls to push_back, pop_back, and min. The tester may even call min after each call to push_back.
    When searching for the minimum value, there may exist more candidates in the input interval (all equally minimal with respect to the comparison used). In such case, the method must return the minimum closer to the beginning of the interval (to position st). This is an important detail. The comparison may use various criteria, generally, the candidates may be very different. Suppose an example where the values are strings and the input interval contains strings "while", "auto", "void", "const". Next, let the comparator use string length for the comparison. Then there are two candidates (namely "auto" and "void"), but "auto" is the expected result (is closer to the beginning of the interval). Obviously, result "void" would be very different from the expectation.

*/
//#define MIN_PART_SIZE 100
//#define MAGIC_CONST 10

template<typename T_, typename Cmp_ = std::less<T_>>
class CIntervalMin
{
  public:
    using const_iterator = typename std::vector<T_>::const_iterator;
    // default constructor
    // constructor with comparator
    CIntervalMin(Cmp_ cmp = std::less<T_>()) : partSize(minPartSize), cmp(cmp) { };
    // constructor - 2 iterators
    // constructor - 2 iterators + comparator
    template<class Iterator>
    CIntervalMin(Iterator begin, Iterator end,  Cmp_ cmp = Cmp_()) : CIntervalMin(cmp)
    {
        for (auto &a = begin; a != end; ++a) {
            data.push_back(*a);
        }

//        partSize = bestPartSize();

        constructSQRTDec();
    }

    // push_back
    void push_back(T_ x) {
        data.push_back(x);
//        size_t best = bestPartSize();
//        if (std::abs((long long)(partSize - best)) > MAGIC_CONST) {
//            partSize = best;
//            constructSQRTDec();
//        } else {
            size_t partIdx = (data.size() - 1) / partSize;
            if (partIdx >= sqrtDeq.size()) {
                sqrtDeq.push_back(x);
            } else {
                if (cmp(x, sqrtDeq[partIdx])) {
                    sqrtDeq[partIdx] = x;
                }
            }
//        }
    }
    // pop_back
    void pop_back() {
        data.pop_back();
//        size_t best = bestPartSize();
//        if (std::abs((long long)(partSize - best)) > MAGIC_CONST) {
//            partSize = best;
//            constructSQRTDec();
//        } else {
            if ((data.size()) % partSize == 0) {
                sqrtDeq.pop_back();
            } else {
                size_t partIdx = (data.size() - 1) / partSize;
                size_t i = partIdx * partSize;
                sqrtDeq[partIdx] = data[i];
                i++;
                for (; i < data.size(); ++i) {
                    if (cmp(data[i], sqrtDeq[partIdx])) {
                        sqrtDeq[partIdx] = data[i];
                    }
                }
            }
//        }
    }
    // min
    T_ min(const_iterator st, const_iterator en) const {
        if (st >= en || st < begin() || en > end()) {
            throw invalid_argument("");
        }
        size_t start = st - begin();
        size_t end = en - begin();

        T_ res = data[start];
        size_t i = start + 1;
        while (i < end && i % partSize != 0) {
            if (cmp(data[i], res)) {
                res = data[i];
            }
            ++i;
        }

        if (i == end) {
            return res;
        }

        size_t stPart = i / partSize;
        size_t enPart = (end - 1) / partSize;

        for (size_t j = stPart; j < enPart; ++j) {
            if (cmp(sqrtDeq[j], res)) {
                res = sqrtDeq[j];
            }
        }

        i = enPart * partSize;
        while (i < end) {
            if (cmp(data[i], res)) {
                res = data[i];
            }
            ++i;
        }

        return res;
    }
    const_iterator begin() const { return data.cbegin(); }
    const_iterator end() const { return data.cend(); }
    size_t size() const { return data.size(); }

private:
    void constructSQRTDec() {
        size_t lastSQRTIdx = 0;
        for (size_t i = 0; i < data.size(); ++i) {
            if (i % partSize == 0) {
                if (sqrtDeq.size() == lastSQRTIdx) {
                    sqrtDeq.push_back(data[i]);
                } else {
                    sqrtDeq[lastSQRTIdx] = data[i];
                }
                lastSQRTIdx++;
            } else if (cmp(data[i], sqrtDeq[lastSQRTIdx - 1])) {
                sqrtDeq[lastSQRTIdx - 1] = data[i];
            }
        }
    }

    size_t bestPartSize() const {
        return max((size_t)sqrt(data.size()), (size_t)minPartSize);
    }

private:
    std::vector<T_> data;
    std::vector<T_> sqrtDeq;
    size_t partSize;
    Cmp_ cmp;

    static const size_t minPartSize = 100;
};


#ifndef __PROGTEST__
//-------------------------------------------------------------------------------------------------
class CStrComparator
{
  public:
               CStrComparator ( bool byLength = true )
      : m_ByLength ( byLength )
    {
    }
    bool       operator () ( const string & a, const string & b ) const
    {
      return m_ByLength ? a . length () < b . length () : a < b;
    }
  private:
    bool       m_ByLength;
};
//-------------------------------------------------------------------------------------------------
bool strCaseCmpFn ( const string & a, const string & b )
{
  return strcasecmp ( a . c_str (), b . c_str () ) < 0;
}
//-------------------------------------------------------------------------------------------------
class TMP {

public:
    TMP() = delete;
    int _asd;

};
//#ifndef __PROGTEST__
int main ( void )
{
  CIntervalMin <int> a1;
  for ( auto x : initializer_list<int> { 5, 15, 79, 62, -3, 0, 92, 16, 2, -4 } )
    a1 . push_back ( x );

  assert ( a1 . size () == 10 );

  ostringstream oss;
  for ( auto x : a1 )
    oss << x << ' ';

  assert ( oss . str () == "5 15 79 62 -3 0 92 16 2 -4 " );
  assert ( a1 . min ( a1 . begin (), a1 . end () ) == -4 );
  assert ( a1 . min ( a1 . begin () + 2, a1 . begin () + 3 ) == 79 );
  assert ( a1 . min ( a1 . begin () + 2, a1 . begin () + 9 ) == -3 );

  try
  {
    a1 . min ( a1 . begin (), a1 . begin () );
    assert ( "Missing an exception" == nullptr );
  }
  catch ( const invalid_argument & e )
  {
  }
  catch ( ... )
  {
    assert ( "Invalid exception" == nullptr );
  }

  a1 . pop_back ();
  assert ( a1 . size () == 9 );
  a1 . push_back ( 42 );

  assert ( a1 . min ( a1 . begin (), a1 . end () ) == -3 );

  vector<string> words{ "auto", "if", "void", "NULL" };
  CIntervalMin <string> a2 ( words . begin (), words . end () );
  assert ( a2 . min ( a2 . begin (), a2 . end () ) ==  "NULL" );

  CIntervalMin <string, bool(*)(const string &, const string &)> a3 ( words . begin (), words . end (), strCaseCmpFn );
  assert ( a3 . min ( a3 . begin (), a3 . end () ) == "auto" );

  CIntervalMin <string, CStrComparator> a4 ( words . begin (), words . end () );
  assert ( a4 . min ( a4 . begin (), a4 . end () ) == "if" );

  CIntervalMin <string, CStrComparator> a5 ( words . begin (), words . end (), CStrComparator ( false ) );
  assert ( a5 . min ( a5 . begin (), a5 . end () ) == "NULL" );

  CIntervalMin <string, function<bool(const string &, const string &)> > a6 ( [] ( const string & a, const string & b )
  {
    return a > b;
  } );
  for ( const auto & w : words )
    a6 . push_back ( w );
  assert ( a6 . min ( a6 . begin (), a6 . end () ) == "void" );
  return 0;
}
#endif /* __PROGTEST__ */
