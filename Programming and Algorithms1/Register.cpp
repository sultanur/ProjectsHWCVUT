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
/*
The task is to develop classes that implement a register of birth and death. The classes provide an interface to modify the register, search for people and search for relatives.

The register stores objects that represents men (CMan) and women (CWoman). Additional genders are not supported in this implementation, however, the class design is open for further extensions. Technically, the classes will be polymorphic, i.e., classes CMan and CWoman will be subclasses of some superclass. Therefore, when researchers in the field of gender studies invent another gender, the register just needs to implement a new class for that new gender. The exact class design is left on you, nevertheless, there is a certain public interface that must be supported:
CMan

The class represents a man. A man is described by his name (any string, not unique) and personal ID (an integer, unique). Next, the class may need to store some other information (a reference to father/mother/children, or some other information you find useful). The public interface must contain:

    constructor with parameters (id, name) to initialize the instance,
    method GetID() to return the personal ID,
    operator << to print the man into an output stream, the output format is ID: name (man), see example runs,
    method PrintDescendants ( os ). The method prints all descendants of the man, in a tree-like form (see the attached source). The order of the children in the output is determined by the order the persons were added to the register.
    other methods you add in your implementation.

CWoman

The class represents a woman. A woman is described by her name (any string, not unique), personal ID (an integer, unique), and all previously used names (maiden name, names from the previous marriages). Next, the class may need to store some other information (a reference to father/mother/children, or some other information you find useful). The public interface must contain:

    constructor with parameters (id, name) to initialize the instance,
    method GetID() to return the personal ID,
    operator << to print the woman into an output stream. There are two output formats for a woman: ID: name (woman) or ID: name [maidenName, name #1, name#2, ..., name#N] (woman) if the woman is married, see example runs,
    method PrintDescendants. The method prints all descendants of the man, in a tree-like form (see the attached source). The order of the children in the output is determined by the order the persons were added to the register.
    method Wedding (newName) changes the name of the woman after a wedding. The method behavior is as follows:
        the existing name is moved to the end of the list of previously used names,
        the woman's name is changed to the name in parameter,
        if Wedding method has not been called on an instance of CWoman, then the instance prints itself without the list of previously used names (i.e., without the square braces and the list)). Once the Wedding method is called, the instance outputs itself with the previously used names (i.e., with the square braces and the list). There may be a situation where the current name and the name after the wedding is literally the same. Anyway, this is still considered a change, thus the list of previously used names changes. For example, the output may even look like this: 666: Novakova [Novakova, Novakova] (woman) (maiden name Novakova, two weddings with name change to Novakova).
    other methods you add in your implementation.

CRegister

The class represents a register of birth and death. There are methods to add people and search for them. The public interface must contain the following methods:

    a default constructor to initialize an empty register,
    a destructor to release the resources,
    method Add (person, father, mother) to add an new person to the register. Parameter person references the CMan/CWoman instance to add to the register. The instance is dynamically allocated and passed as a shared_ptr. The two following arguments are optional. The parameters refer to the father and mother of the person (if the parents are known), or are set to nullptr (if the parents are not known or are not present in the register). The method may be called even with one parent set and the other unknown. The method returns true to indicate success, or false for an error. An error is reported if the ID of the newly added person is already in use. Your implementation does not have to do other validation. In particular, you do not have to test whether the father is a reference to CMan (and mother is a reference to CWoman). The testing environment too reactionary to do that sort of things.
    method FindByID (ID) to find the person with that given ID. The method returns a reference to the person object, or an invalid reference if the ID is unknown. The return value is a type supporting a dereference to access the instance of CMan/CWoman. In other words, the return value may be a raw pointer, a shared_ptr, or your own implementation of a smart pointer.
    method FindByName(prefix) to search for persons whose names start with the given string prefix. Return value is an array of references to persons matching the prefix filter. The persons in the resulting vector must be sorted according to their IDs in an ascending order. If no person in the register matches the prefix, the resulting vector will be empty. The searching must match the prefix with the name of the person, moreover, it must test maiden names and previously used names for married women. The resulting vector must not contain duplicates. For instance, the method may be invoked with parameter "Novakova". Suppose, there is a CWoman with both name and maiden name set to "Novakova". However, the person will be listed only once in the result. The comparison is case-sensitive.
    method FindRelatives ( id1, id2 ) to test whether two persons are relative, or not. Moreover, the method must find the relationship of the two persons if they are actually relatives. The result may be:
        an empty list if the two persons are not relative,
        a list of pairs where each pair references a person and a relationship. The first element in the list will refer to first relative of the person with id1 (i.e., the person with id1 is not included in the returned list). Following it, there are references to the intermediate relatives, ending with a reference to the person with id2. Any pair of persons in the list must be direct relatives, i.e., son/daughter/father/mother. Any more complex relationship must be decomposed, e.g., a brother must be defined by means of a father/mother. Moreover, the relationship must be explicitly present in the resulting pair, i.e., the second field in the pair denotes the relationship between the person and its predecessor in the list.

        Generally, there may exist many such lists defining the relationship of the persons id1 and id2. The method must find the shortest list possible. Even if the lists are as short as possible, there still may exist many such lists. However, any such list is accepted by the testing environment (the testing environment checks the relationship of the adjacent persons in the returned list),
        std::invalid_argument exception is thrown if id1 or id2 is not known in the register, or when id1 == id2.

ERel

Is an enumeration type defining relationship constants (son/daughter/father/mother). The type is defined in the testing environment, your implementation must use it without any changes (keep the declaration in the conditional compile block).

Submit a source file with the implementation of the required classes. Moreover, add any further classes your implementation requires. The classes must follow the public interface above. If there is a mismatch in the interface, the compilation will fail. You may extend the interface and add your own auxiliary methods and member variables (both public and private, although private are preferred). The submitted file must include both declarations as well as implementation of the class (the methods may be implemented inline but do not have to). The submitted file shall not contain anything unnecessary. In particular, if the file contains main, your tests, or any #include definitions, please, keep them in a conditional compile block. Use the template below as a basis for your implementation. If the preprocessor definitions are preserved, the file may be submitted to Progtest.

Use STL to develop the class. The available headers are listed in the attached source.

The task is evaluated in four tests. The first test is mandatory, while the following tests are only optional (your program will be awarded more points if it passes them). If you decide to submit only a partial implementation (you skip the implementation of methods tested in some latter tests), you still have to declare all required methods and provide at least some "dummy" implementation (e.g., return 0 or an empty list). The tests check the following methods:

    The design of the polymorphic classes, methods CMan::GetID, CWoman::GetID, CWoman::Wedding, output of CMan, output of CWoman, CRegister::Add, CRegister::FindByID, and CRegister::FindByName. This test is a mandatory test, your solution will be awarded 0 points if it fails.
    CMan::PrintDescendants and CWoman::PrintDescendants (and all from the previous test).
    CRegister::FindRelatives (and all from the previous test).
    Time efficiency of CRegister::FindByName (and all from the previous test).

Advice:

    Start with the design of your class hierarchy. Your implementation must use polymorphic classes, otherwise, it will fail the mandatory test..
    Use algorithms and containers from the standard library, see the list of available header files.
    The attached example lists only one possible result of CRegister::FindRelatives. Your implementation may return a different list; such list may be rejected by the tests in the attached source. However, Progtest accepts all correct lists (the testing in the attached source is just too simplistic).
    CRegister::Add method parameters father and mother, the return type of CRegister::FindByID and other methods need to pass a reference to stored instances of CMan / CWoman. You are free to choose (raw) pointers, smart pointers from the standard library, or your own encapsulation class (with the properties of a smart pointer). The type, however, must support a dereference, must be usable in a condition (is valid/is invalid), and must support initialization from nullptr. Next, your interface should be consistent (i.e., either always use raw pointers, or always use smart pointers). CRegister::Add parameter person is an exception, you have to use smart pointer from the standard library here.


*/
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
