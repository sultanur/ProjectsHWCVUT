#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
/*
The task is to implement a set of functions to handle linked lists. An office is implemented as a structure with two linked lists. The first linked list stores the employees, the second list represents the cars. Each employee is represented by name and a link to his/her assigned car. A car is represented by its model name. Given that structures, the functions are used to initialize a new office, add a new employee, add a new car, copy the office, and dispose the office.

TEMPLOYEE
    is a data structure defined in the testing environment. Your implementation must use the structure, however, it must not modify it in any way. The structure represents one employee. The employees are organized in a single linked list. The structure has the following fields:

        m_Next - a link to the next employee in the list. The last employee in the list must set m_Next to the NULL value.
        m_Car - is a link to the assigned car. The link is either NULL (meaning the employee does not have any car assigned), or it references some element in the car linked list.
        m_Name - an ASCIIZ (zero terminated) employee name.

TCAR
    is a data structure defined in the testing environment. Your implementation must use the structure, however, it must not modify it in any way. The structure represents one car. The car are organized in a single linked list. The structure has the following fields:

        m_Next - a link to the next car in the list. The last car in the list must set m_Next to the NULL value.
        m_Model - an ASCIIZ (zero terminated) car model name.

TOFFICE
    is a data structure defined in the testing environment. Your implementation must use the structure, however, it must not modify it in any way. The structure represents one office, the structure contains two fields:

        m_Emp - a pointer to the first employee in the linked list of employees,
        m_Car - a pointer to the first car in the linked list of cars.

initOffice ()
    the function creates a new office. The structure is to be dynamically allocated and a pointer to that structure is to be returned. Both lists in the newly created office must be initialized as empty.
addEmployee ( office, name )
    the function creates a new employee and places the new employee at the first position of the employee list. The parameters are name - name of the new employee and office - the office to place the employee to. The function is responsible for the allocation of the employee structure, moreover it must initialize the fields. The newly listed employee does not have any car assigned, i.e. m_Car must be set to NULL.
addCar ( office, model )
    the function creates a new car and places the new car at the first position of the car list. The parameters are model - the model name of the car and office - the office to place the car to. The function is responsible for the allocation of the car structure, moreover it must initialize the fields.
freeOffice ( office )
    the function frees all resources allocated by the given office (i.e. both employee and car linked lists plus the structure that represents the office),
cloneOffice ( office )
    the function creates an independent copy of the given office. The newly created office must preserve the employees, the cars, the order of employees, the order of the cars, and the assigned cars. Caution: the newly created list must be independent, thus the links to the cars must be updated to refer to the corresponding elements in the newly created office. Return value is a pointer that points to the newly allocated (and filled) office structure.

Submit a source file with the implementation of the above functions. Further, the source file must include your auxiliary functions which are called from the required functions. Your functions will be called from the testing environment, thus, it is important to adhere to the required interface. Use the attached sample code as a basis for your development, complete the required functions and add your required auxiliary functions. There is an example main with some tests in the attached code. These test cases will be used in the basic test. Please note the header files as well as main is nested in a conditional compile block (#ifdef/#endif). Please keep these conditional compile block in place. They are present to simplify the development. When compiling on your computer, the headers and main will be present as usual. On the other hand, the header and main will "disappear" when compiled by Progtest. Thus, your testing main will not interfere with the testing environment's main.

Your function will be executed in a limited environment. There are limits on both time and memory. The exact limits are shown in the test log of the reference. A reasonable implementation of the naive algorithm shall pass both limits without any problems. There is a bonus test, the bonus test requires an efficient algorithm to copy the lists.
Advice:

    Download the attached sample code and use it as a base for your development.
    The main function in your program may be modified (e.g. a new test may be included). The conditional compile block must remain, however.
    There is macro assert used in the example main function. If the value passed to assert is nonzero (true), the macro does nothing. On the other hand, if the parameter is zero, the macro stops the execution and reports the line, where the test did not match (and shall be fixed). Thus, the program ends silently when your implementation passes all the tests correctly.
    There are not any known limitations on the employee names. In particular, employee names may be unique, but they do not have to be.

*/
typedef struct TCar
{
    struct TCar              * m_Next;
    char                     * m_Model;
} TCAR;

typedef struct TEmployee
{
    struct TEmployee         * m_Next;
    struct TCar              * m_Car;
    char                     * m_Name;
} TEMPLOYEE;

typedef struct TOffice
{
    TEMPLOYEE                * m_Emp;
    TCAR                     * m_Car;
} TOFFICE;

#endif /* __PROGTEST__ */

TOFFICE * initOffice   ()
{
    TOFFICE * noffice = (TOFFICE *) malloc (sizeof (TOFFICE));
    noffice->m_Emp = NULL;
    noffice->m_Car = NULL;
    return noffice;

}
void addEmployee  ( TOFFICE * office,
                    const char * name )
{
    TEMPLOYEE * newEmp = (TEMPLOYEE *)malloc(sizeof (TEMPLOYEE));
    newEmp->m_Next = office->m_Emp;
    office->m_Emp = newEmp;
    newEmp->m_Car = NULL;

    newEmp->m_Name = strdup(name);

}
void addCar ( TOFFICE  * office,
              const char * model )
{
    TCAR *newCar = (TCAR *)malloc(sizeof (TCAR));

    newCar->m_Next = office->m_Car;
    office->m_Car = newCar;

    newCar->m_Model = strdup(model);

}

TOFFICE * cloneOffice  ( TOFFICE * office )
{
    TOFFICE * B = initOffice();

    TCAR * originalC = office->m_Car;
    TCAR * copyC;

    TEMPLOYEE * originalE = office->m_Emp;
    TEMPLOYEE * copyE;


    while (originalC)
    {
        //copying cars
        copyC = originalC->m_Next;
        originalC->m_Next = (TCAR *)malloc (sizeof(TCAR));
        originalC->m_Next->m_Model = strdup(originalC->m_Model);
        originalC->m_Next->m_Next = copyC;
        originalC = copyC;
    }
    originalC = office->m_Car;

    // copying employees
    while (originalE)
    {
        copyE = originalE->m_Next;
        originalE->m_Next = (TEMPLOYEE *) malloc (sizeof(TEMPLOYEE));
        originalE->m_Next->m_Name = strdup(originalE->m_Name);
        originalE->m_Next->m_Car = NULL;
        originalE->m_Next->m_Next = copyE;
        originalE = copyE;
    }
    originalE = office->m_Emp;

    // separating copies and originals

    if ( office->m_Emp != NULL)
        B->m_Emp = office->m_Emp->m_Next;

    if ( office->m_Car != NULL)
        B->m_Car = office->m_Car->m_Next;

    while (originalE != NULL)
    {
        copyE = originalE->m_Next;
        if (originalE->m_Car != NULL) {
            originalE->m_Next->m_Car = originalE->m_Car->m_Next;
        }
        originalE->m_Next = copyE->m_Next;
        if (copyE->m_Next == NULL) {
            break;
        }

        copyE->m_Next = originalE->m_Next->m_Next;
        originalE = originalE->m_Next;

    }
    while (originalC)
    {
        copyC = originalC->m_Next;
        originalC->m_Next = copyC->m_Next;
        if (copyC->m_Next == NULL) {
            break;
        }
        copyC->m_Next = originalC->m_Next->m_Next;
        originalC = originalC->m_Next;

    }

    return B;
}
/*void print_emp (TOFFICE * office) {
   TEMPLOYEE * tmp = office->m_Emp;
   int i =0;
   while (tmp != NULL) {
      printf ("%d name: %s\n", i++, tmp->m_Name);
      if (tmp->m_Car !=NULL) {
         printf ("%s\n", tmp->m_Car->m_Model);
    } else {
         printf ("\n");
         }
         tmp = tmp->m_Next;
        }
} */
void freeOffice ( TOFFICE * office )
{
    TEMPLOYEE * tmp;
    while (office->m_Emp != NULL)
    {
        tmp = office->m_Emp;
        office->m_Emp = office->m_Emp->m_Next;
        free(tmp->m_Name);
        free(tmp);
    }

    TCAR * tmp1;
    while (office->m_Car != NULL)
    {
        tmp1 = office->m_Car;
        office->m_Car = office->m_Car->m_Next;
        free(tmp1->m_Model);
        free(tmp1);
    }

    free(office);
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    TOFFICE * a, *b;
    char tmp[100];


    a = initOffice();
    addEmployee (a,"Peter");
    b = cloneOffice(a);
    freeOffice(a);
    freeOffice(b);
    // print_emp(b);
   // return 0;



    assert ( sizeof ( TOFFICE ) == 2 * sizeof ( void * ) );
    assert ( sizeof ( TEMPLOYEE ) == 3 * sizeof ( void * ) );
    assert ( sizeof ( TCAR ) == 2 * sizeof ( void * ) );
    a = initOffice ();

    addEmployee ( a, "Peter" );
    addEmployee ( a, "John" );
    addEmployee ( a, "Joe" );
    addEmployee ( a, "Maria" );
    addCar ( a, "Skoda Octavia" );
    addCar ( a, "VW Golf" );
    a -> m_Emp -> m_Car = a -> m_Car;
    a -> m_Emp -> m_Next -> m_Next -> m_Car = a -> m_Car -> m_Next;
    a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car = a -> m_Car;
    assert ( a -> m_Emp
             && ! strcmp ( a -> m_Emp -> m_Name, "Maria" )
             && a -> m_Emp -> m_Car == a -> m_Car );
    assert ( a -> m_Emp -> m_Next
             && ! strcmp ( a -> m_Emp -> m_Next -> m_Name, "Joe" )
             && a -> m_Emp -> m_Next -> m_Car == NULL );
    assert ( a -> m_Emp -> m_Next -> m_Next
             && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Name, "John" )
             && a -> m_Emp -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    assert ( a -> m_Car
             && ! strcmp ( a -> m_Car -> m_Model, "VW Golf" ) );
    assert ( a -> m_Car -> m_Next
             && ! strcmp ( a -> m_Car -> m_Next -> m_Model, "Skoda Octavia" ) );
    assert ( a -> m_Car -> m_Next -> m_Next == NULL );
    b = cloneOffice ( a );
    strncpy ( tmp, "Moe", sizeof ( tmp ) );
    addEmployee ( a, tmp );
    strncpy ( tmp, "Victoria", sizeof ( tmp ) );
    addEmployee ( a, tmp );
    strncpy ( tmp, "Peter", sizeof ( tmp ) );
    addEmployee ( a, tmp );
    strncpy ( tmp, "Citroen C4", sizeof ( tmp ) );
    addCar ( a, tmp );
    b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car = b -> m_Car -> m_Next -> m_Next;
    assert ( a -> m_Emp
             && ! strcmp ( a -> m_Emp -> m_Name, "Peter" )
             && a -> m_Emp -> m_Car == NULL );
    assert ( a -> m_Emp -> m_Next
             && ! strcmp ( a -> m_Emp -> m_Next -> m_Name, "Victoria" )
             && a -> m_Emp -> m_Next -> m_Car == NULL );
    assert ( a -> m_Emp -> m_Next -> m_Next
             && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Name, "Moe" )
             && a -> m_Emp -> m_Next -> m_Next -> m_Car == NULL );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Name, "Maria" )
             && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Joe" )
             && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Car == NULL );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "John" )
             && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next -> m_Next );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    assert ( a -> m_Car
             && ! strcmp ( a -> m_Car -> m_Model, "Citroen C4" ) );
    assert ( a -> m_Car -> m_Next
             && ! strcmp ( a -> m_Car -> m_Next -> m_Model, "VW Golf" ) );
    assert ( a -> m_Car -> m_Next -> m_Next
             && ! strcmp ( a -> m_Car -> m_Next -> m_Next -> m_Model, "Skoda Octavia" ) );
    assert ( a -> m_Car -> m_Next -> m_Next -> m_Next == NULL );
    assert ( b -> m_Emp
             && ! strcmp ( b -> m_Emp -> m_Name, "Maria" )
             && b -> m_Emp -> m_Car == b -> m_Car );
    assert ( b -> m_Emp -> m_Next
             && ! strcmp ( b -> m_Emp -> m_Next -> m_Name, "Joe" )
             && b -> m_Emp -> m_Next -> m_Car == NULL );
    assert ( b -> m_Emp -> m_Next -> m_Next
             && ! strcmp ( b -> m_Emp -> m_Next -> m_Next -> m_Name, "John" )
             && b -> m_Emp -> m_Next -> m_Next -> m_Car == b -> m_Car -> m_Next );
    assert ( b -> m_Emp -> m_Next -> m_Next -> m_Next
             && ! strcmp ( b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car == NULL );
    assert ( b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    assert ( b -> m_Car
             && ! strcmp ( b -> m_Car -> m_Model, "VW Golf" ) );
    assert ( b -> m_Car -> m_Next
             && ! strcmp ( b -> m_Car -> m_Next -> m_Model, "Skoda Octavia" ) );
    assert ( b -> m_Car -> m_Next -> m_Next == NULL );
    freeOffice ( a );
    freeOffice ( b );
    return 0;
}
#endif /* __PROGTEST__ */
