#include <iostream>
#include <iomanip>

using namespace std;

#define MAP_SIZE 4000000UL
#define MAP_MASK (MAP_SIZE - 1)

int main()
{
    unsigned long asd = ((0x19C00000+0x00300000)& ~MAP_MASK);
	unsigned long asd2 = 0x19000000/1024/1024;
   cout << "Hello World" << endl; 
   cout << (unsigned)asd2 << endl;
cout << setbase(16) << asd << endl;
   
   return 0;
}


