//
// MIT License
// Copyright (c) 2019 Snekoff. All rights reserved.
//

#include "Unicode_Console_Output.h"

/*     char in circles
     * 0x024b6	-  0x024ff
     * different stuff
     * 0x02500  -  0x025ef
     * */
void printwc(wchar_t wc)
{
    char buf[2 * MB_CUR_MAX];

    mbstate_t state;
    memset(&state,0,sizeof(state));

    size_t offset1 = wcrtomb(buf, wc, &state);

    if(offset1 == size_t(-1))
    {
        std::cerr << "wcrtomb failed (1)" << std::endl;
        return;
    }

    size_t offset2 = wcrtomb(buf + offset1, L'\0', &state);

    if(offset2 == size_t(-1))
    {
        std::cerr << "wcrtomb failed (2)" << std::endl;
        return;
    }

    std::cout << buf;
}

//Example
/*
 * int main()
{
    setlocale(LC_ALL, "");

    printwc(0x1f0a1);
    cout << endl;

    for(auto i = 0x024b6; i <= 0x024ff; i++){
        printwc(i);
        cout << endl;
    }
    for(auto i = 0x02500; i <= 0x025ef; i++){
        printwc(i);
        cout << endl;
    }

return 0;
}
*/