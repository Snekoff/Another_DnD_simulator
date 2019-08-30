//
// MIT License
// Copyright (c) 2019 Snekoff. All rights reserved.
//

#include "unicode_console_output.h"
//
// MIT License
// Copyright (c) 2019 Snekoff. All rights reserved.
//

/*     char in circles
     * 0x024b6	-  0x024ff
     * different stuff
     * 0x02500  -  0x025ef
     * */
/* Fine stuff: 0x02500 +=
 * 2, 3, 5, 7, 15, 19, 23, 27, 32, 40, 48, 56, 66, 81  - 108, 136, 137, 167, 169, 178, 179.
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
    cout << "  ";
    for(int i = 0; i < 10; i++){
        cout << "  ";
        cout << i;
    }
    int j = 0, p = 0;
    cout <<"\n" << p << "   ";
    for(auto i = 0x02500; i <= 0x025ef; i++){
        //cout << "i = " << i;
        if(j == 10) {
            j = 0;
            cout << "\n";
            p++;
            if(p < 10) cout << p << "   ";
            else cout << p << "  ";
        }
        printwc(i);
        cout << "  ";
        j++;
    }
    cout << "\n";

return 0;
}
*/