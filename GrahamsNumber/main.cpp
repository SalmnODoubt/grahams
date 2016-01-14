//
//  main.cpp
//  GrahamsNumber
//
//  Created by Jonny Biederstädt on 12/01/16.
//  Copyright © 2016 Jonny Biederstädt. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <regex>
#include <stdarg.h>

using namespace std;

const int iMAXARRLEN = 10;

class InfInt{
    public:
        //range of unsigned long long:
        //0 to 18,446,744,073,709,551,615
        static unsigned long long s_ull_max;
        static int s_ull_max_digit;
        unsigned long long m_num[iMAXARRLEN] = {0};
        bool m_toolarge = false;
    
        InfInt(){
            s_ull_max = numeric_limits<unsigned long long>::max();
            s_ull_max_digit = (int)log10((double)s_ull_max) + 1;

            //cout << "create";
        }
    
        InfInt(unsigned long long p_num){
            InfInt();
            
            m_num[0] = p_num;
        }
    
        InfInt(InfInt &p_num){
            InfInt();
        
            for(int i = 0; i < iMAXARRLEN; i++)
                m_num[i] = p_num.m_num[i];
        }

        InfInt(int p_count, ...){
            InfInt();
            
            va_list num_fragments;
            int i_index_placement = 0;
            
            va_start(num_fragments, p_count);
            
            i_index_placement = (p_count > iMAXARRLEN ? iMAXARRLEN : p_count) -1;
            
            for(int i = i_index_placement; i >= 0; i--)
                m_num[i] = va_arg(num_fragments, unsigned long long);
        }
    
    
        ~InfInt(){
            //cout << "destroy";
        }
    
        void setULL(unsigned long long p_num){
            m_num[0] = p_num;
        }
    
        string toString(void){
            stringstream r_number;
            bool num_start = false;
            
            int i_arr_len = iMAXARRLEN;
            
            while(--i_arr_len >= 0)
                if(num_start && m_num[i_arr_len])
                    r_number << fillZero(m_num[i_arr_len]) << m_num[i_arr_len];
                else if(num_start && !m_num[i_arr_len])
                    r_number << fillZero(0);
                else if(!num_start && m_num[i_arr_len] && i_arr_len++ )
                    num_start = true;
            
            if(!num_start)
                r_number << '0';
            
            
            regex leading_cero_regex ("(^0{1,})([1-9]{1,})");

            return regex_replace(r_number.str(), leading_cero_regex, "$2");
        }
    
    private:
        string fillZero(unsigned long long p_num){
            stringstream r_zeros;
            int zero_len = s_ull_max_digit - (p_num ? (int)log10((double)p_num) +1 : 0);
            
            while(zero_len--)
                r_zeros << '0';
            
            return r_zeros.str();
        }
    
};
unsigned long long InfInt::s_ull_max = 0ull;
int InfInt::s_ull_max_digit = 0ull;

int grahams(void);
unsigned long long calKnuthUpArrow(string p_str_term);
InfInt infAdd(InfInt p_num1, InfInt p_num2);
InfInt infMul(InfInt p_factor1, InfInt p_factor2);
InfInt infPow(InfInt p_basis, InfInt p_exp);

//array< int, 5 > &fillarr( array< int, 5 > &arr );

int main(int argc, const char * argv[]) {
    
    //grahams();
    
    InfInt test_num = *new InfInt(6, 123456789ull, 23456789ull, 3456789ull, 0, 456789ull, 0);
    
    cout << "test1 " << test_num.toString() << endl;
    cout << "test2 " << infAdd(*new InfInt(1234567890ull), *new InfInt(9876543210ull)).toString() << endl;
    
    return 0;
}

int grahams(void){
    string str_input = "";
    
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
        << "--------------------------------------------------------------"
        << "\n";
    
    return 0;
}

unsigned long long calKnuthUpArrow(string p_str_term){
    unsigned long long d_result = 0;
    int i_arrow_count = 0; //arrow_count
    int i_basis = 0;
    int i_exponent = 0;
    string str_seg_regex = "^\\s{0,}(\\d*)\\s{0,}k{1,}\\s{0,}(\\d*)\\s{0,}$";
    string str_tet_regex = "k{1,}";
    string::size_type sz;
    smatch sm;
    
    //cout << "errrrrr " << str_seg_regex << "    " << regex_search(p_str_term, sm, r) << " T " << p_str_term << " T " << endl;

    regex r_seg(str_seg_regex);
    if(regex_search(p_str_term, sm, r_seg) && sm.size() == 3){
        //have to test if sm[0|1] is a number
        i_basis = stoi(sm[1], &sz);
        i_exponent = stoi(sm[2], &sz);
    }
    
    //cout << " 1." << sm[0] << " 2." << sm[1] << " 3." << sm[2] << " size:" << sm.size();
    
    regex r_tet(str_tet_regex);
    if (regex_search(p_str_term, sm, r_tet))
        i_arrow_count = (int)sm.length();
    
    //cout << " HHH" << sm.length() << "ZZZ ";
    
    d_result = i_basis;
    
    if(i_basis > 2 && i_arrow_count > 1 && i_exponent == 2){
        i_exponent++;
        i_arrow_count--;
    }
    
    if(i_arrow_count == 1 || i_exponent <= 2)
        d_result = pow(i_basis, i_exponent);
    else
        for(int i = 1; i < i_arrow_count; i++)
            for(int ii = 1; ii < i_exponent; ii++)
                d_result = pow(i_basis, d_result);
    
    //cout << " " << d_result << " " << i_basis << " " << i_exponent << " " << i_arrow_count << " ";
    
    return d_result;
}

InfInt infAdd(InfInt p_num1, InfInt p_num2){
    InfInt r_sum;
    return r_sum;
}

InfInt infMul(InfInt p_factor1, InfInt p_factor2){
    InfInt r_prod;
    return r_prod;
}

InfInt infPow(InfInt p_basis, InfInt p_exp){
    InfInt r_prod;
    return r_prod;
}

/*array< int, 5 > &fillarr( array< int, 5 > &arr ) {
    return arr; // "array" being boost::array or std::array
}*/