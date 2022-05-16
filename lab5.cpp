#include  <iostream>
#include <cmath>
#include <windows.h>

using namespace std;

float func_z(float&);

int main(){

	LPVOID lpvBase;               // Base address of the test memory
    BOOL bSuccess;                // Flag
    DWORD i;                      // Generic counter
    DWORD dwPageSize;               // Page size on this computer
    MEMORY_BASIC_INFORMATION mbi {};

    SYSTEM_INFO sSysInfo;         // Useful information about the system


	GetSystemInfo(&sSysInfo);     // Initialize the structure.
	printf ("This computer has page size %d.\n\n", sSysInfo.dwPageSize);



	lpvBase = VirtualAlloc(
                     NULL,                 // System selects address
                     sSysInfo.dwPageSize*3, 					// 	Size of allocation
                     MEM_COMMIT,          
                     PAGE_READWRITE);      

	if (lpvBase == NULL )
        printf ("VirtualAlloc reserve failed.\n\n");


    printf ("  Calculations and write in allocated memory \n");
    auto lpPtr = (float*)lpvBase;
	for (float alpha = 0.1; alpha < 1.1; alpha+=0.1){
		*lpPtr = func_z(alpha);
		cout << func_z(alpha) << "  -------  " << lpPtr << '\n';
		lpPtr++;
	}

	LPVOID addr;
	cout << "\n\nEnter address to check: ";
	cin >> addr;
	VirtualQuery(addr, &mbi, sizeof(mbi));
	if (mbi.State == MEM_COMMIT){
		cout << "Fist 100 bytes in page: \n";
		for (lpPtr = (float*)mbi.BaseAddress; lpPtr <= (float*)(mbi.BaseAddress + 100); lpPtr++){
			cout << lpPtr << "  ----  " << *lpPtr << "\n";		
		}
	}
	else{
		cout << "Memory is not committed at this address" << "\n";
	}

	system("pause");
	return 0;	
}

float func_z(float &alpha){

	return (cos(alpha) + sin(alpha)) / (cos(alpha) - sin(alpha));
}