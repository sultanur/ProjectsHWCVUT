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
