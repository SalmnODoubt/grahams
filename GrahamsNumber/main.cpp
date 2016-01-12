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

int calKnuthUpArrow(string p_str_term);

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

int calKnuthUpArrow(string p_str_term){
    int i_result = 0;
    int i_tetration = 0; //arrow_count
    int i_basis = 0;
    int i_exponent = 0;
    string str_seg_regex = "(\\d*)\\s{0,}k{1,}\\s{0,}(\\d*)";
    string::size_type sz;
    
    const regex r(str_seg_regex);
    smatch sm;
    
    //cout << "errrrrr " << str_seg_regex << "    " << regex_search(p_str_term, sm, r) << " T " << p_str_term << " T " << endl;
    
    if(regex_search(p_str_term, sm, r) && sm.size() == 2){
        //have to test if sm[0|1] is a number
        i_basis = stoi(sm[0], &sz);
        i_exponent = stoi(sm[1]);
    }
        /*for(int i = 1; i < sm.size(); i++){
            cout << sm[i] << "X";
        }*/
    
    //@TODO next time i use a regex here
    for(string::iterator it = p_str_term.begin(); it != p_str_term.end(); ++it)
        if(*it == 'k')
            i_tetration++;

    
    
    //result = pow(
    
    i_result = i_tetration;
    
    return i_result;
}