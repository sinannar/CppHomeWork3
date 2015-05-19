/**
    091044005HW03.cpp
    Implementatiton of the lfind from search.h
    and implementation of the function that get an array of any type and print it
    Also this file include test for some type as int,char,double,bool,CDAccountV1
    To see test result of them,just define them in lines 14 or 17 or 20 or 23 or 26 or 29

**/

#include <iostream>

using namespace std;

/**     define to test integers     **/
//#define TESTFORINTEGER

/**     define to test chars        **/
//#define TESTFORCHAR

/**     define to test doublkes     **/
//#define TESTFORDOUBLE

/**     define to test booliens     **/
//#define TESTFORBOOL

/**     define to test CDAccountV1     **/
//#define TESTFORCDACCOUNTV1

/**     DEBUGGING     **/
//#define DEBUGMODE

/** CDAccountV1 struct type **/
struct CDAccountV1
{
   double balance;
   double interestRate;
   int term;
};

///  Find Functions  ///
/**
pre:  get the key,base amd sizeof array and the width of eache element and tha function pointer that is used for compare
post: return the adress of key if found,return null if not found
**/
void* sinanFind(const void *key, const void *base, size_t *sizeOfArray, size_t width, int (*compar)(const void *, const void *));

///  Compare Functions///
/**
pre:  get the key and iterator
post: return 1 if key and iterators are same,return 0 if they not
**/
int cmpInt(const void *key, const void *iterator);
int cmpChar(const void *key, const void *iterator);
int cmpDouble(const void *key, const void *iterator);
int cmpBool(const void *key, const void *iterator);
int cmpCDAccountV1(const void *key, const void *iterator);

///  Print Functions  ///
/**
pre:  get the base and size of array and each element width and functıonpointer to print elements
post: return NULL
**/
void* sinanPrint( const void *base, size_t *sizeOfArray, size_t width, void (*prt)(const void *));
/**
pre:  get the iterator
post: print iterator
**/
void prntInt( const void *iterator);
void prntChar(const void *iterator);
void prntDouble(const void *iterator);
void prntBool(const void *iterator);
void prntCDAccountV1(const void *iterator);

///  İnitialize CDAccountV1  ///
/**
pre:  get the adress of acc and values of balance interest and term
post: set the value of them
**/
void setCDAccountV1(CDAccountV1 *acc,double balance,double interestRate,int term);

/**  Main  **/
int main()
{

/******    TESTING WITH INTEGERS    ******/
#ifdef TESTFORINTEGER
    {
        int sinan[100]={0};
        size_t size=100;
        int key=58,*a;

        for(int i=0;i<100;++i)
        sinan[i]=i;
        sinan[53]=58;

        a=static_cast<int*>(sinanFind(&key, sinan, &size, sizeof(key) ,cmpInt));
#ifdef DEBUGMODE
        cout<<*a;
#endif
        sinanPrint( sinan, &size, sizeof(key) ,prntInt);
    }
#endif


/******    TESTING WITH CHARS    ******/
#ifdef TESTFORCHAR
    {
        char sinan[100];
        size_t size=100;
        char key='a',*a;

        for(int i=0;i<100;++i)
        sinan[i]=static_cast<char>(i);
        sinan[53]='a';

        a=static_cast<char*>(sinanFind(&key, sinan, &size, sizeof(key) ,cmpChar));
#ifdef DEBUGMODE
        cout<<*a;
#endif
        sinanPrint( sinan, &size, sizeof(key) ,prntChar);
    }
#endif


/******    TESTING WITH DOUBLES    ******/
#ifdef TESTFORDOUBLE
    {
        double sinan[100],j=11.00;
        size_t size=100;
        double key=11.11,*a;

        for(int i=0;i<100;++i,j=j+0.01)
        sinan[i]=j;

        a=static_cast<double*>(sinanFind(&key, sinan, &size, sizeof(key) ,cmpDouble));
#ifdef DEBUGMODE
        cout<<*a;
#endif
        sinanPrint( sinan, &size, sizeof(key) ,prntDouble);
    }
#endif

/******    TESTING WITH BOOLSS    ******/
#ifdef TESTFORBOOL
    {
        bool sinan[100]={0};
        size_t size=100;
        bool key=true,*a;

        for(int i=0;i<100;++i)
        sinan[i]=false;
        sinan[53]=true;

        a=static_cast<bool*>(sinanFind(&key, sinan, &size, sizeof(key) ,cmpBool));
#ifdef DEBUGMODE
        cout<<*a;
#endif
        sinanPrint( sinan, &size, sizeof(key) ,prntBool);
    }
#endif


/******    TESTING WITH struct CDACCOUNTV1    ******/
#ifdef TESTFORCDACCOUNTV1
    {

        CDAccountV1 sinan[100];
        size_t size=100;
        CDAccountV1 key={1.1,1.1,1},*a;

        for(int i=0;i<100;++i)
        setCDAccountV1(&sinan[i],0.0,0.0,0);
        sinan[53]={1.1,1.1,1};

        a=static_cast<CDAccountV1*>(sinanFind(&key, sinan, &size, sizeof(key) ,cmpCDAccountV1));
#ifdef DEBUGMODE
        cout<<"balance:"<<a->balance<<" interestrate"<<a->interestRate<<" term:"<<a->term;
#endif
        sinanPrint( sinan, &size, sizeof(key) ,prntCDAccountV1);
    }
#endif

	return 1;
}

/** sinanFind FUNCTION **/
void* sinanFind(const void *key, const void *base, size_t *sizeOfArray, size_t width, int (*compar)(const void *, const void *))
{
	char* iterator= (char*)base;    //error occured when i try to use static_cast,so idecide to use this way because of constant

	for(size_t i=0 ; i<*sizeOfArray; ++i, iterator+=width ) //look all element
	{
		if(compar(key, iterator))   //compare them
			return static_cast<void*>(iterator);    //return if found
	}
    return NULL;    //if not found return NULL
}

/** COMPARE FUNCTIONS **/
/**
pre:  get the key and iterator
post: return 1 if key and iterators are same,return 0 if they not
**/
int cmpInt(const void *key, const void *iterator)
{
	if( *(int*)iterator == *(int*)key ) //error occured when i try to use static_cast,so idecide to use this way because of constant
			return 1;
	return 0;
}

int cmpChar(const void *key, const void *iterator)
{
	if( *(char*)iterator == *(char*)key ) //error occured when i try to use static_cast,so idecide to use this way because of constant
			return 1;
	return 0;
}

int cmpDouble(const void *key, const void *iterator)
{
	if( *(double*)iterator == *(double*)key ) //error occured when i try to use static_cast,so idecide to use this way because of constant
			return 1;
	return 0;
}

int cmpBool(const void *key, const void *iterator)
{
	if( *(bool*)iterator == *(bool*)key ) //error occured when i try to use static_cast,so idecide to use this way because of constant
			return 1;
	return 0;
}

int cmpCDAccountV1(const void *key, const void *iterator)
{
    CDAccountV1 *acc1,*acc2;
    acc1=(CDAccountV1*)key;     //error occured when i try to use static_cast,so idecide to use this way because of constant
    acc2=(CDAccountV1*)iterator;//error occured when i try to use static_cast,so idecide to use this way because of constant
    if(acc1->balance == acc2->balance && acc1->interestRate == acc2->interestRate &&acc1->term == acc2->term )
        return 1;
	return 0;
}

/** sinanPrint FUNCTION **/
void* sinanPrint( const void *base, size_t *sizeOfArray, size_t width, void (*prt)(const void *))
{
	char* iterator= (char*)base;    //error occured when i try to use static_cast,so idecide to use this way because of constant

	for(size_t i=0 ; i<*sizeOfArray; ++i, iterator+=width ) //look all elements
	{
		prt(iterator);  //print each of them
	}
    return NULL;    //return NULL
}

/** PRINT FUNCTIONS **/
/**
pre:  get the iterator
post: print iterator
**/
void prntInt(const void *iterator)
{
    cout<<" "<<*(int*)iterator; //error occured when i try to use static_cast,so idecide to use this way because of constant
}

void prntChar(const void *iterator)
{
    cout<<" "<<*(char*)iterator;    //error occured when i try to use static_cast,so idecide to use this way because of constant
}

void prntDouble(const void *iterator)
{
    cout<<" "<<*(double*)iterator;  //error occured when i try to use static_cast,so idecide to use this way because of constant
}

void prntBool(const void *iterator)
{
    cout<<" "<<*(bool*)iterator;    //error occured when i try to use static_cast,so idecide to use this way because of constant
}

void prntCDAccountV1(const void *iterator)
{
    CDAccountV1 *acc;
    acc=(CDAccountV1*)iterator; //error occured when i try to use static_cast,so idecide to use this way because of constant
    cout<<" balance:"<<acc->balance
        <<" interestRate:"<<acc->interestRate
        <<" term:"<<acc->term<<endl<<endl;
}

/**   İnitializing CDAccountV1 objects **/
void setCDAccountV1(CDAccountV1 *acc,double balance,double interestRate,int term)
{
    acc->balance=balance;
    acc->interestRate=interestRate;
    acc->term=term;
}
