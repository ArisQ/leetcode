#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    const string RN="IVXLCDM"; //IV XL CD M
    string intToRoman(int num) {
        string reversed_result(32,'a');
        int digit;
        int index=0;
        string::iterator iter=reversed_result.begin();
        // result.resize(32);
        while(num!=0) {
            digit=num%10;
            num=num/10;
            if(digit==4) {
                *(iter++)=RN[index+1]; //IV反向的，故为VI
                *(iter++)=RN[index];
            } else if (digit==9) {
                *(iter++)=RN[index+2];
                *(iter++)=RN[index];
            } else {
                for(int i=0;i<digit%5;++i)
                    *(iter++)=RN[index];
                if (digit>4)
                    *(iter++)=RN[index+1];
            }
            index+=2;
        }
        return string(string::reverse_iterator(iter),reversed_result.rend());
    }
};

int main()
{
    Solution solution;
    cout<<"Hello World!"<<endl;
    cout << solution.intToRoman(3) << endl; //III
    cout << solution.intToRoman(4) << endl; //IV
    cout << solution.intToRoman(9) << endl; //IX
    cout << solution.intToRoman(58) << endl; //LVIII
    cout << solution.intToRoman(1994) << endl; //MCMXCIV
    return 0;
}
