#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
        int maxArea(vector<int>& height) {
            int result=0;
            int cij=0;
            for(size_t i=0;i<height.size();++i)
                for(size_t j=i+1;j<height.size();++j) {
                    cij=(j-i)*(height[i]<=height[j]?height[i]:height[j]);
                    if(cij>result)
                        result=cij;
                }
            return result;
        }
};

int main()
{
    vector<int> input={1,8,6,2,5,4,8,3,7};
    cout<<Solution().maxArea(input)<<endl;
    return 0;
}
