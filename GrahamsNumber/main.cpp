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

const int iMAXARRLEN = 10;

class InfInt{
    public:
        //range of unsigned long long:
        //0 to 18,446,744,073,709,551,615
        //static unsigned long long s_ull_max;
        static int s_ull_max_log10;
        unsigned long long m_num[iMAXARRLEN] = {0};
        bool m_toolarge = false;
    
        InfInt(){
            s_ull_max_log10 = (int)log10((double)numeric_limits<unsigned long long>::max());

            cout << s_ull_max_log10;
        
            //cout << "create";
        }
    
        ~InfInt(){
            //cout << "destroy";
        }
    
        void setULL(unsigned long long p_num){
            m_num[0] = p_num;
        }
    
        public: string toString(void){
            
            return "";
        }
    
};
//unsigned long long InfInt::s_ull_max = 0ull;
int InfInt::s_ull_max_log10 = 0ull;

int grahams(void);
unsigned long long calKnuthUpArrow(string p_str_term);
InfInt infAdd(InfInt Num1, InfInt Num2);
InfInt &infMul(InfInt &Factor1, InfInt &Factor2);
InfInt &infPow(InfInt &Basis, InfInt &Exp);

//array< int, 5 > &fillarr( array< int, 5 > &arr );

int main(int argc, const char * argv[]) {
    
    //grahams();
    
    cout << infAdd(*new InfInt, *new InfInt).toString();
    
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

    const regex r_seg(str_seg_regex);
    if(regex_search(p_str_term, sm, r_seg) && sm.size() == 3){
        //have to test if sm[0|1] is a number
        i_basis = stoi(sm[1], &sz);
        i_exponent = stoi(sm[2], &sz);
    }
    
    //cout << " 1." << sm[0] << " 2." << sm[1] << " 3." << sm[2] << " size:" << sm.size();
    
    const regex r_tet(str_tet_regex);
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

InfInt infAdd(
    InfInt Num1,
    InfInt Num2
){
    InfInt iiSum;
    
    
    
    return iiSum;
}

InfInt infMul(
    InfInt Factor1,
    InfInt Factor2
){
    InfInt iiSum;
    return iiSum;
}

InfInt infPow(
    InfInt Basis,
    InfInt Expf
){
    InfInt iiSum;
    return iiSum;
}

/*array< int, 5 > &fillarr( array< int, 5 > &arr ) {
    return arr; // "array" being boost::array or std::array
}*/