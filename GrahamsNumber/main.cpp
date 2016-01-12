//
//  main.cpp
//  GrahamsNumber
//
//  Created by Jonny Biederstädt on 12/01/16.
//  Copyright © 2016 Jonny Biederstädt. All rights reserved.
//

#include <iostream>
#include <string>
#include <cmath>
#include <regex>

using namespace std;

double calKnuthUpArrow(string p_str_term);

int main(int argc, const char * argv[]) {
    string str_input = "";
    
    // insert code here...
    cout
        << "Hello, this little program will be able to calculate tetration,\n"
        << "the G Numbers and finally Graham's number.\n"
        << "For tetration:\n"
        << "\tlike 4 k 3 = 64\n"
        << "\t(k is used instead of ^, or what your arrow would look like)\n"
        << "\tor 4 [2] 3 = 64 (not yet implemented):\n"
        << "For G1...64: G1...64\n"
        << "\tor for Graham's Number itself simply G\n\n"
        << "Please enter your terms:\n";
    
    getline(cin, str_input);
    
    cout
        << "\n\nThank you! The Result to that would be:\n"
        << calKnuthUpArrow(str_input)
        << "\n\n"
        << "--------------------------------------------------------------------------------"
        << "\n";

    return 0;
}

double calKnuthUpArrow(string p_str_term){
    double d_result = 0;
    int i_arrow_count = 0; //arrow_count
    int i_basis = 0;
    int i_exponent = 0;
    string str_seg_regex = "(\\d*)\\s{0,}k{1,}\\s{0,}(\\d*)";
    string str_tet_regex = "k{1,}";
    string::size_type sz;
    smatch sm;
    
    //cout << "errrrrr " << str_seg_regex << "    " << regex_search(p_str_term, sm, r) << " T " << p_str_term << " T " << endl;

    const regex r_seg(str_seg_regex);
    if(regex_search(p_str_term, sm, r_seg) && sm.size() == 2){
        //have to test if sm[0|1] is a number
        i_basis = stoi(sm[0], &sz);
        i_exponent = stoi(sm[1], &sz);
    }
    
    cout << " 1." << sm[0] << " 2." << sm[1] << " ";
    
    const regex r_tet(str_tet_regex);
    if (regex_search(p_str_term, sm, r_tet))
        i_arrow_count = (int)sm.length();
    
    if(i_arrow_count == 1)
        d_result = pow(i_basis, i_exponent);
    else
        while(i_arrow_count)
            for(int i = 0; i < i_exponent; i++)
                d_result = pow(i_basis, d_result);
    
    cout << " " << d_result << " " << i_basis << " " << i_exponent << " " << i_arrow_count << " ";
    
    return d_result;
}