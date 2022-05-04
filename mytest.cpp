#include "bigint.h"
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;


int main() {
    //Add your own code
    //You may comment out the example code snippets below
  
    //First example
//      BigInt mytest("DADCAFE", 16);
//      cout<<mytest.to_string()<<endl;//should print DADCAFE
//      BigInt mytest2("1010",2);
//      cout<<mytest2.to_int()<<endl;//should print 10
//     BigInt mytest3("1010",2);
//     cout<<mytest3.to_int()<<endl;//should print 10
//     BigInt mytest4("AB",36);
//     cout<<mytest4.to_int()<<endl;//should print 371
//     BigInt mytest5("-11000",2);
//     cout<<mytest5.to_int()<<endl;//should print -24
    BigInt t6("-6142969059479558963139678442444433",10);
    BigInt t7("-1",10);
    BigInt t8;
    //Expected: 60756039819049999195671749402734900429517710104992780817801060003690
    t8 = t6*t7;
    cout<<t8.to_string()<<endl;
    cout<<t8.to_int()<<endl;
    
//     cout<<t6.to_string()<<endl;
//     cout<<t6.to_int()<<endl;
//     BigInt t8("-10",10);
    //BigInt t10(t9);
    //cout<<t8.compare(t9);
    //Second example
//     BigInt first("DADCAFE", 16);
//     BigInt second("BEEF", 16);
//     BigInt sum = first + second;
//     first += second;
//     cout<<boolalpha<<(first >= second)<<endl;//should print true
//     cout<<sum.to_string()<<endl;//should print DAE89ED
//     cout<<first.to_string()<<endl;//should print DAE89ED
    
    //Third example
//     BigInt var1(496,10);
//     BigInt var2(249,10);
//     BigInt var3(1189,10);
//     BigInt var4 = modPow(var1,var2,var3);
//     cout<<var4.to_int()<<endl;//should print 72
//     cout<<(char)var4.to_int()<<endl;//should print "H"
    
    
	return 0;
}
