/*
高精的库，采用c++实现，底层使用vector
*/
#include <vector>

using namespace std;

struct HighAccuracyAlgorithm{
    vector <int> number;
    void Change_to_HAA(int origin_number){
        while (origin_number){
            number.push_back(origin_number%10);
            origin_number /= 10;
        }
    }
    
};