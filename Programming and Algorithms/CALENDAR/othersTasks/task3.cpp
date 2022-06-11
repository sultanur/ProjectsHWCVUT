#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>
using namespace std;

enum class ERel
{
    REL_NONE,
    REL_FATHER,
    REL_MOTHER,
    REL_SON,
    REL_DAUGHTER
};
#endif /* __PROGTEST__ */

class CBase {
protected:
    virtual void print(std::ostringstream& out) const {
    }
public:
    //    CBase (int & id, string & name ) {
    //        m_ID = id;
    //        m_Name = name;
    //    }
    ~CBase( ) {
//        for (auto &e : m_parents) {
//            e.
//        }

        cout << "Des BASE" << endl;
    }
    string GetName () const { return  m_Name;}  int  GetID( ) const { return m_ID ;}
    int  GetMale( ) const { return m_male;}
    const vector<shared_ptr<CBase>> & GetChilds() const { return m_childs;}
    const vector<shared_ptr<CBase>> & GetParents() const { return m_parents;}
    void PrintDescendants (std::ostringstream &os) const {
        string pref;
        PrintDescendants(os, 0, true, pref);
    }
    friend std::ostringstream& operator<< (std::ostringstream& out, const CBase& mc) {
        mc.print(out);
        return out;
    }
    void PrintDescendants (std::ostringstream &os, size_t level, bool lastFlag, string &preffix) const {
        string newPref;
        if (level == 0) {
            //os << *this << endl;
            print(os);
            os << endl;
            newPref = " ";
        } else {

            string tmp = preffix;
            newPref = preffix;
            if (lastFlag) {
                tmp += "\\- ";
                newPref += "   ";
            } else {
                tmp += "+- ";
                newPref += "|  ";
            }

            os << tmp;
            print ( os );
            os << endl;
        }

        if (!m_childs.empty()) {
            for (size_t i = 0; i < m_childs.size() - 1; ++i) {
                m_childs[i]->PrintDescendants(os, level + 1, false, newPref);
            }
            m_childs[m_childs.size() - 1]->PrintDescendants(os, level + 1, true, newPref);
        }
    }
    void AddParents(shared_ptr<CBase> father, shared_ptr<CBase> mother) {
//        m_parents.clear();
        m_parents.push_back(father);
        m_parents.push_back(mother);
    }

    void AddChild(shared_ptr<CBase> child) {
        m_childs.push_back(child);
    }
    void clear() {
        m_parents.clear();
        m_childs.clear();
    }

protected:
    int m_ID;
    string m_Name;
    int m_male;
    vector<shared_ptr<CBase>> m_parents;
    vector<shared_ptr<CBase>> m_childs;
};

// class CMan
// {
//   public:
//     // constructor
//     // GetID ()
//     // operator <<
//     // void PrintDescendants ( os )
//   private:
//     // todo
// };

class CMan : public CBase
{
protected:
    void print(std::ostringstream& out) const {
        out << m_ID << ": " << m_Name << " (man)";
        return;
    }
public:
    CMan (int id, const string & name )  {
        m_ID = id;
        m_Name =  name;
        m_male = 1;

        cout << "COS Man" << endl;
    }
    ~CMan() {

//        int m_ID;
//        m_Name.clear();
//        m_parents.clear();
//        m_childs.clear();

        cout << "Des Man" << endl;
    }


    // friend  std::ostringstream & operator << ( std::ostringstream & out , const CMan & man ) override {
    //     man.print(out);
    //     return out;
    // }

    // void PrintDescendants ( std::ostringstream & os );
};



class CWoman : public CBase
{
protected:
    void print(std::ostringstream& out) const {
        out << m_ID   << ": " << m_Name;
        if (m_previousNames.size() != 0) {
            out << " [" << m_previousNames[0];
            for (size_t i = 1; i < m_previousNames.size(); ++i) {
                out << ", " << m_previousNames[i];
            }
            out << "]";
        }
        out << " (woman)";
        return;
    }
public:
    // constructor
    CWoman (int id, const string & name ){
        m_ID = id;
        m_Name = name;
        m_male = 2;
        cout << "CON Woman" << endl;
    }  // GetID ()
    // operator <<

    ~CWoman() {
//        m_Name.clear();
//        m_parents.clear();
//        m_childs.clear();
//        m_previousNames.clear();


        cout << "Des Woman" << endl;
    }

    // friend  std::ostringstream & operator << ( std::ostringstream & out , const CWoman & women ) {
    //     women.print(out);
    //     return out;
    // }
    // void PrintDescendants ( os )
    // void Wedding ( newName )
    void Wedding(const string &newName) {
        m_previousNames.push_back(m_Name);
        m_Name = newName;
        return;
    }
    const vector<string> &GetPreviousNames() const { return m_previousNames; }
private:
    vector<string> m_previousNames;
};

struct QData {
    shared_ptr<CBase> cur;
    size_t pred;
};

ERel relation(shared_ptr<CBase> a, shared_ptr<CBase> b) {
    if (a->GetParents().size() >= 1 && a->GetParents()[0] != nullptr && a->GetParents()[0]->GetID() == b->GetID()) {
        return ERel::REL_FATHER;
    }
    if (a->GetParents().size() >= 2 && a->GetParents()[1] != nullptr && a->GetParents()[1]->GetID() == b->GetID()) {
        return ERel::REL_MOTHER;
    }
    if (b->GetParents().size() >= 1 && b->GetParents()[0] != nullptr && b->GetParents()[0]->GetID() == a->GetID()) {
        return (b->GetMale() == 1 ? ERel::REL_SON : ERel::REL_DAUGHTER);
    }
    if (a->GetParents().size() >= 2 && a->GetParents()[1] != nullptr && b->GetParents()[1]->GetID() == a->GetID()) {
        return (b->GetMale() == 1 ? ERel::REL_SON : ERel::REL_DAUGHTER);
    }
    return ERel::REL_NONE;
}

class CRegister
{
public:
    ~CRegister() {
//        m_persons.clear();
        for (auto &e : m_persons) {
//            cout << e.second->GetName() << " " << e.second.use_count() << endl;
            e.second->clear();
//            cout << e.second->GetName() << " " << e.second.use_count() << endl;
        }
        cout << "DES CRegister" << endl;
    }
    // default constructor
    bool                 Add           (shared_ptr<CBase> person,
                                        shared_ptr<CBase> father,
                                        shared_ptr<CBase> mother)
    {
        // cout << person->GetID() << endl;
        // cout << (m_persons.find(person->GetID()) != m_persons.end()) << endl;
        if (person == nullptr || m_persons.find(person->GetID()) != m_persons.end()) {
            return false;
        }
        person->AddParents(father, mother);
        if (father != nullptr) {
            father->AddChild(person);
        }
        if (mother != nullptr) {
            mother->AddChild(person);
        }
        m_persons[person->GetID()] = person;
        return true;
    }
    shared_ptr<CBase> FindByID(int id) const {
        const auto &res = m_persons.find(id);
        if (res == m_persons.end()) {
            return nullptr;
        }
        return (*res).second;
        //       return nullptr;
    }
    vector<shared_ptr<CBase>> FindByName (const string &prefix) const {
        vector<shared_ptr<CBase>> res;
        for (auto &p : m_persons) {
            if (p.second->GetMale() == 1) {
                CMan & tmp = dynamic_cast<CMan &> (*(p.second));
                if (tmp.GetName().find(prefix) != string::npos) {
                    res.push_back(p.second);
                }
            } else {
                CWoman & tmp = dynamic_cast<CWoman &> (*(p.second));
                if (tmp.GetName().find(prefix) != string::npos) {
                    res.push_back(p.second);
                } else {
                    for (const auto &s : tmp.GetPreviousNames()) {
                        if (s.find(prefix) != string::npos) {
                            res.push_back(p.second);
                            break;
                        }
                    }
                }
            }
        }
        return res;
    }
    list<pair<shared_ptr<CBase>, ERel> > FindRelatives (int id1, int id2 ) const {
        auto f = m_persons.find(id1);
        auto s = m_persons.find(id2);
        if (f == m_persons.end() || s == m_persons.end() || id1 == id2 ) {
            throw invalid_argument("");
        }
        set<int> used;
        vector<QData> queue;
        queue.push_back({f->second, 0});
        size_t tail = 0;
//        cout<< "START" << endl;
        while (queue.size() != tail) {
            QData tmp = queue[tail];
//            cout << "CH "<< tail << endl;
            for (size_t i = 0; i < tmp.cur->GetChilds().size(); ++i) {
                int id = tmp.cur->GetChilds()[i]->GetID();
                if (used.find(id) == used.end()) {
                    queue.push_back({tmp.cur->GetChilds()[i], tail });
                    used.insert(id);
                    if (id == id2) {
                        list<pair<shared_ptr<CBase>, ERel>> res;
                        int idx = queue.size() - 1;
//                        cout << "CHILD" << endl;
                        while (idx != 0) {
                            int next_idx = queue[idx].pred;
                            res.push_front(make_pair(queue[idx].cur, relation(queue[next_idx].cur, queue[idx].cur)));
                            idx = next_idx;
                        }
                        return res;
                    }
                }
            }

//            cout << "PAR "<< tail<< endl;
            for (size_t i = 0; i < tmp.cur->GetParents().size(); ++i) {
                if (tmp.cur->GetParents()[i] != nullptr) {
                    int id = tmp.cur->GetParents()[i]->GetID();
                    if (used.find(id) == used.end()) {
                        queue.push_back({tmp.cur->GetParents()[i], tail });
                        used.insert(id);
                        if (id == id2) {
                            list<pair<shared_ptr<CBase>, ERel>> res;
                            int idx = queue.size() - 1;
//                            cout << "PARENT" << endl;
                            while (idx != 0) {
                                int next_idx = queue[idx].pred;
                                res.push_front(make_pair(queue[idx].cur, relation(queue[next_idx].cur, queue[idx].cur)));
                                idx = next_idx;
                            }
                            return res;
                        }
                    }
                }
            }
            tail++;
        }
//        cout << "END" << endl;
        return list<pair<shared_ptr<CBase>, ERel>>();
    }
private:
    map<int, shared_ptr<CBase>> m_persons;
};

#ifndef __PROGTEST__
template <typename T_>
static bool        vectorMatch ( const vector<T_>     & res,
                                const vector<string> & ref )
{
    vector<string> tmp;
    for ( const auto & x : res )
    {
        std::ostringstream oss;
        oss << *x;
        tmp . push_back ( oss . str () );
    }
    return tmp == ref;
}
template <typename T_>
static bool        listMatch ( const list<pair<T_, ERel> >     & res,
                              const list<pair<string, ERel> > & ref )
{
    list<pair<string, ERel> > tmp;
    for ( const auto & x : res )
    {
        std::ostringstream oss;
        oss << *x . first;
        tmp . emplace_back ( oss . str (), x . second );
//        string tmp;
//        switch (x.second) {
//            case ERel::REL_MOTHER:
//                tmp = "REL_MOTHER";
//                break;
//            case ERel::REL_FATHER:
//                tmp = "REL_FATHER";
//                break;
//            case ERel::REL_SON:
//                tmp = "REL_SON";
//                break;
//            case ERel::REL_DAUGHTER:
//                tmp = "REL_DAUGHTER";
//                break;
//
//            default:
//                break;
//        }
//        cout << oss.str() << " " << tmp << endl;
    }
    return tmp == ref;
}
int main ( void )
{
    std::ostringstream oss;
    CRegister r;
    assert ( r . Add ( make_shared<CMan> ( 1, "Peterson George" ),
                      nullptr, nullptr ) == true );
//    assert ( r . Add ( make_shared<CMan> ( 2, "Watson Paul" ),
//                      nullptr, nullptr ) == true );
//    assert ( r . Add ( make_shared<CMan> ( 10, "Smith Samuel" ),
//                      nullptr, nullptr ) == true );
    assert ( r . Add ( make_shared<CWoman> ( 11, "Peterson Jane" ),
                      r . FindByID ( 1 ), nullptr ) == true );
//    assert ( r . Add ( make_shared<CWoman> ( 12, "Peterson Sue" ),
//                      r . FindByID ( 1 ), nullptr ) == true );
//    assert ( r . Add ( make_shared<CMan> ( 13, "Pershing John" ),nullptr, nullptr ) == true );
//    assert ( r . Add ( make_shared<CMan> ( 14, "Pearce Joe" ),nullptr, nullptr ) == true );
//    assert ( r . Add ( make_shared<CMan> ( 15, "Peant Thomas" ),
//                      nullptr, nullptr ) == true );
//    assert ( r . Add ( make_shared<CMan> ( 100, "Smith John" ),
//                      r . FindByID ( 10 ), r . FindByID ( 11 ) ) == true );
//    assert ( r . Add ( make_shared<CMan> ( 101, "Smith Roger" ),
//                      r . FindByID ( 10 ), r . FindByID ( 11 ) ) == true );
//    assert ( r . Add ( make_shared<CMan> ( 102, "Smith Daniel" ),
//                      r . FindByID ( 10 ), r . FindByID ( 11 ) ) == true );
//    assert ( r . Add ( make_shared<CWoman> ( 103, "Smith Eve" ),
//                      r . FindByID ( 10 ), r . FindByID ( 11 ) ) == true );
//    assert ( r . Add ( make_shared<CWoman> ( 103, "Smith Jane" ),
//                      r . FindByID ( 10 ), r . FindByID ( 11 ) ) == false );
//    dynamic_cast<CWoman &> ( *r . FindByID ( 12 ) ) . Wedding ( "Smith Sue" );
//    assert ( r . Add ( make_shared<CMan> ( 150, "Pershing Joe" ),
//                      r . FindByID ( 13 ), r . FindByID ( 12 ) ) == true );
//    dynamic_cast<CWoman &> ( *r . FindByID ( 12 ) ) . Wedding ( "Pearce Sue" );
//    assert ( r . Add ( make_shared<CMan> ( 151, "Pearce Phillip" ),
//                      r . FindByID ( 14 ), r . FindByID ( 12 ) ) == true );
//    dynamic_cast<CWoman &> ( *r . FindByID ( 12 ) ) . Wedding ( "Peant Sue" );
//    assert ( r . Add ( make_shared<CMan> ( 152, "Peant Harry" ),
//                      r . FindByID ( 15 ), r . FindByID ( 12 ) ) == true );
//    assert ( r . Add ( make_shared<CMan> ( 200, "Pershing Peter" ),
//                      r . FindByID ( 150 ), r . FindByID ( 103 ) ) == true );
//    assert ( r . Add ( make_shared<CWoman> ( 201, "Pershing Julia" ),
//                      r . FindByID ( 150 ), r . FindByID ( 103 ) ) == true );
//    assert ( r . Add ( make_shared<CWoman> ( 202, "Pershing Anne" ),
//                      r . FindByID ( 150 ), r . FindByID ( 103 ) ) == true );
//        assert ( vectorMatch ( r . FindByName ( "Peterson" ), vector<string>
//                              {
//            "1: Peterson George (man)",
//            "11: Peterson Jane (woman)",
//            "12: Peant Sue [Peterson Sue, Smith Sue, Pearce Sue] (woman)"
//        } ) );
//        assert ( vectorMatch ( r . FindByName ( "Pe" ), vector<string>
//                              {
//            "1: Peterson George (man)",
//            "11: Peterson Jane (woman)",
//            "12: Peant Sue [Peterson Sue, Smith Sue, Pearce Sue] (woman)",
//            "13: Pershing John (man)",
//            "14: Pearce Joe (man)",
//            "15: Peant Thomas (man)",
//            "150: Pershing Joe (man)",
//            "151: Pearce Phillip (man)",
//            "152: Peant Harry (man)",
//            "200: Pershing Peter (man)",
//            "201: Pershing Julia (woman)",
//            "202: Pershing Anne (woman)"
//        } ) );
//        assert ( vectorMatch ( r . FindByName ( "Smith" ), vector<string>
//                              {
//            "10: Smith Samuel (man)",
//            "12: Peant Sue [Peterson Sue, Smith Sue, Pearce Sue] (woman)",
//            "100: Smith John (man)",
//            "101: Smith Roger (man)",
//            "102: Smith Daniel (man)",
//            "103: Smith Eve (woman)"
//       } ) );
//    assert ( r . FindByID ( 1 ) -> GetID () == 1 );
//    oss . str ( "" );
//    oss << * r . FindByID ( 1 );
//    assert ( oss . str () == "1: Peterson George (man)" );
//    oss . str ( "" );
//    r . FindByID ( 1 ) -> PrintDescendants ( oss );
////        cout << oss.str() << endl;
////        string tmp1 = oss.str();
////        string tmp2 = "1: Peterson George (man)\n"
////        " +- 11: Peterson Jane (woman)\n"
////        " |  +- 100: Smith John (man)\n"
////        " |  +- 101: Smith Roger (man)\n"
////        " |  +- 102: Smith Daniel (man)\n"
////        " |  \\- 103: Smith Eve (woman)\n"
////        " |     +- 200: Pershing Peter (man)\n"
////        " |     +- 201: Pershing Julia (woman)\n"
////        " |     \\- 202: Pershing Anne (woman)\n"
////        " \\- 12: Peant Sue [Peterson Sue, Smith Sue, Pearce Sue] (woman)\n"
////        "    +- 150: Pershing Joe (man)\n"
////        "    |  +- 200: Pershing Peter (man)\n"
////        "    |  +- 201: Pershing Julia (woman)\n"
////        "    |  \\- 202: Pershing Anne (woman)\n"
////        "    +- 151: Pearce Phillip (man)\n"
////        "    \\- 152: Peant Harry (man)\n";
////
////        cout << tmp1.size() << ' ' << tmp2.size() << endl;
////        if (tmp1.size() != tmp2.size()) {
////            int i = 0;
////            while (tmp1[i] == tmp2[i]) {
////                i++;
////            }
////            cout << "I: " << i<<endl;
////            cout << tmp1.substr(i)<<endl;
////            cout << tmp2.substr(i)<<endl;
////        }
//
//    assert ( oss . str () ==
//            "1: Peterson George (man)\n"
//            " +- 11: Peterson Jane (woman)\n"
//            " |  +- 100: Smith John (man)\n"
//            " |  +- 101: Smith Roger (man)\n"
//            " |  +- 102: Smith Daniel (man)\n"
//            " |  \\- 103: Smith Eve (woman)\n"
//            " |     +- 200: Pershing Peter (man)\n"
//            " |     +- 201: Pershing Julia (woman)\n"
//            " |     \\- 202: Pershing Anne (woman)\n"
//            " \\- 12: Peant Sue [Peterson Sue, Smith Sue, Pearce Sue] (woman)\n"
//            "    +- 150: Pershing Joe (man)\n"
//            "    |  +- 200: Pershing Peter (man)\n"
//            "    |  +- 201: Pershing Julia (woman)\n"
//            "    |  \\- 202: Pershing Anne (woman)\n"
//            "    +- 151: Pearce Phillip (man)\n"
//            "    \\- 152: Peant Harry (man)\n" );
//
//    assert ( r . FindByID ( 2 ) -> GetID () == 2 );
//    oss . str ( "" );
//    oss << * r . FindByID ( 2 );
//    assert ( oss . str () == "2: Watson Paul (man)" );
//    oss . str ( "" );
//    r . FindByID ( 2 ) -> PrintDescendants ( oss );
//    assert ( oss . str () ==
//            "2: Watson Paul (man)\n" );
//    assert ( listMatch ( r . FindRelatives ( 100, 1 ), list<pair<string, ERel> >
//                        {
//        { "11: Peterson Jane (woman)", ERel::REL_MOTHER },
//        { "1: Peterson George (man)", ERel::REL_FATHER }
//    } ) );
//
//    assert ( listMatch ( r . FindRelatives ( 100, 13 ), list<pair<string, ERel> >
//                        {
//        { "10: Smith Samuel (man)", ERel::REL_FATHER },
//        { "103: Smith Eve (woman)", ERel::REL_DAUGHTER },
//        { "200: Pershing Peter (man)", ERel::REL_SON },
//        { "150: Pershing Joe (man)", ERel::REL_FATHER },
//        { "13: Pershing John (man)", ERel::REL_FATHER }
//    } ) );
//    assert ( listMatch ( r . FindRelatives ( 100, 2 ), list<pair<string, ERel> >
//                        {
//    } ) );
//    try
//    {
//        r . FindRelatives ( 100, 3 );
//        assert ( "Missing an exception" == nullptr );
//    }
//    catch ( const invalid_argument & e )
//    {
//    }
//    catch ( ... )
//    {
//        assert ( "An unexpected exception thrown" );
//    }
//    try
//    {
//        r . FindRelatives ( 100, 100 );
//        assert ( "Missing an exception" == nullptr );
//    }
//    catch ( const invalid_argument & e )
//    {
//    }
//    catch ( ... )
//    {
//        assert ( "An unexpected exception thrown" );
//    }
    return 0;
}
#endif /* __PROGTEST__ */
