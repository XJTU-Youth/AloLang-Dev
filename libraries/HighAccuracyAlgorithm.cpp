/*
高精的库，采用c++实现，底层使用vector
*/
#include <vector>

using namespace std;

struct HighAccuracyAlgorithm //高精类
{
    vector<int> number;
    void Change_to_HAA(int origin_number)
    {
        while (origin_number)
        {
            number.push_back(origin_number % 10);
            origin_number /= 10;
        }
    }
};
/* 我傻了你们帮忙封装成类吧*/
vector<int> sampleA;
vector<int> sampleB;
void HHA_Plus()
{
    /* 迭代器 p1 分配给位数较大的 */
    vector<int>::iterator p1;
    vector<int>::iterator p2;
    vector<int>::iterator p3;
    int len_a = sampleA.size();
    int len_b = sampleB.size();
    if (len_a <= len_b)
    {
        sampleA.swap(sampleB);
        swap(len_a, len_b);
    }
    p1 = sampleA.begin();
    p2 = sampleB.begin();
    vector<int> answer; //答案数组
    bool flag = false;
    /* 倒序储存 */
    while (p2 < sampleB.end())
    {
        answer.push_back(*p1 + *p2);
        if (flag)
        {
            *p3 + 1;
            flag = false;
        }
        if (*p3 > 9)
        {
            flag = true;
            *p3 %= 10;
        }
        p1++;
        p2++;
        p3++;
    }
    while (p1 < sampleA.end())
    {
        answer.push_back(*p1);
        if (flag)
        {
            *p3 + 1;
            flag = false;
        }
        if (*p3 > 9)
        {
            flag = true;
            *p3 %= 10;
        }
        p1++;
        p3++;
    }
    if (flag)
    {
        *p3 + 1;
        flag = false;
    }
    if (*p3 > 9)
    {
        answer.push_back(*p3 /10);
        *p3 %= 10;
    }
}

int main() {}