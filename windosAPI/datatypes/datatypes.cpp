#include <iostream>
#include<Windows.h>
using namespace std;

int main()
{
    CHAR a = 'A'; // size is 8  bits
    WCHAR a1 = 'A';  // size is 16 bits

    cout << "the size of char datatype is " << sizeof(char) << endl;
    cout << "the size of wchar datatype is " << sizeof(WCHAR) << endl;


    CHAR  arr[] = "ansii";
    WCHAR uarr[] = L"unicode";

    /* stackoverflow answer
    'L' means wchar_t, which, as opposed to a normal character, requires 16-bits of storage rather than 8-bits.
    Here's an example:

    "A"    = 41
    "ABC"  = 41 42 43
    L"A"   = 00 41
    L"ABC" = 00 41 00 42 00 43

    A wchar_t is twice big as a simple char. In daily use you don't need to use wchar_t, but if you are using windows.h you are going to need it.
    */


    BOOL res;

    // strlen for normal string
    cout << "length of ascii string is " <<arr<<" = "<< strlen(arr) << endl; //output 4

    // wcslen for unicode string
    wcout << "length of the wide char array " << uarr << " = " << wcslen(uarr) << endl; // output 7

    cout << endl;
    cout << "check if char array is unicode or not" << endl;

    res = IsTextUnicode(arr, strlen(arr), NULL);
    cout << endl;
    if (res == 1)
    {
        cout << "string " << arr << " is unicode" << endl;
    }
    else
    {
        cout << "string " << arr << " not unicode" << endl;

    }

    cout << endl;
    cout << "check if wchar array is unicode or not" << endl;

    res = IsTextUnicode(uarr, strlen(arr), NULL);
    cout << endl;
    if (res == 1)
    {
        wcout << "string " << uarr << " is unicode" << endl;
    }
    else
    {
        wcout << "string " << uarr << " not unicode" << endl;

    }
    cout << endl << endl;


    // multibyte to wide char conversion
    // normal string to wstring

    int WcharSize = 0;
    WcharSize = MultiByteToWideChar(CP_UTF8, //encoding format
        0, //dwflag
        arr, // pointer to the character string to  convert
        -1, // if it null terminated since we are using char array
        NULL, // pointer to buffer
        0  // size of the char of the buffer ,if this is 0 then required buffer size
        );

    cout << "the size of the required buffer for string "<< arr<<"  "<< WcharSize << endl;


    PWCHAR  output= new WCHAR[WcharSize];
    int status = MultiByteToWideChar(CP_UTF8, //encoding format
        0, // dwflags should set to 0 when utf8 is used
        arr, // input ansi array
        -1, // if the string is null terminated
        output, // output to store wchar variable
        WcharSize // size of the buffer in characters
    );

    if (status)
    {
        wcout << "conversion is successfull and the output string is in unicode format " << (output) << endl;
    }
    else
    {
        cout << "conversion is failed" << endl;
    }

    cout << endl << endl;


    // conversion from  wide char to multibyte conversion

    int AnsiSize = WideCharToMultiByte(CP_UTF8, //code page
        0, // dwflags
        uarr, // pointer to unicode
        -1,   // size of the unicode if char array then it is -1
        NULL, // pointer to buffer
        0, // size in bytes of the buffer
        NULL, // null for utf8
        NULL    // null for utf8
    );

    cout << "the size of the ansi string required for the  conversion is :" << AnsiSize << endl;
 


    PCHAR output1 = new CHAR[AnsiSize];
    int status1= WideCharToMultiByte(CP_UTF8, //code page
        0, // dwflags
        uarr, // pointer to unicode
        -1,   // size of the unicode if char array then it is -1
        output1, // pointer to buffer
        AnsiSize, // size in bytes of the buffer
        NULL, // null for utf8
        NULL    // null for utf8
    );


    if (status1)
    {
        cout << "conversion successfull and the ansi string is: " << (output1) << endl;
    }
    else
    {
        cout << "conversion failed" << endl;
    }



    return 0;
}


