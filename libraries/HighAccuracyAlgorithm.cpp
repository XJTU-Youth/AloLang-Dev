/*
高精的库，采用c++实现，底层使用vector
*/
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

const int BSYS=10;//Basic

struct HighAccuracyAlgorithm{
    vector <int> number;//number
    int sign;//Pos or Neg
    void Change_to_HAA(int origin_number){
    	if (origin_number < 0)
    		sign = -1;
		else if (origin_number == 0)
			sign = 0;
		else
			sign = 1;
        while (origin_number){
            number.push_back(origin_number%10);
            origin_number /= BSYS;
        }
    }
    HighAccuracyAlgorithm operator +(HighAccuracyAlgorithm addend){//add
    	int i,j,len;
    	HighAccuracyAlgorithm out;
    	if (sign == -1 && addend.sign == -1){
    		out.sign == -1;
		}
    	len=addend.number.size()>number.size() ? addend.number.size() : number.size();
    	for (i = 0;i < len;i++)
    		out.number.push_back(number[i]);
    	for (i = 0;i < len;i++)
    		out.number[i] += addend.number[i];
    	for (i = 1;i < number.size();i++){
    		if (out.number[i-1]/BSYS > 0){
    			out.number[i] += out.number[i-1] / BSYS;
    			out.number[i-1] %= BSYS;
			}
		}
		if (out.number[number.size()-1] / BSYS > 0){
			out.number[number.size()] = out.number[number.size()-1] / BSYS;
			out.number[number.size()-1] %= BSYS;
		}
		return out;
	}
	void print(){//out
		int i,flag=0;
		if (sign == -1){
			printf("-");
		}
		else if (sign == 0){
			printf("0");
			return;
		}
		for (i = number.size()-1;i >= 0;i--){
			if (flag){
				printf("%d",number[i]);
			}
			else if (number[i]){
				printf("%d",number[i]);
				flag = 1;
			}
		}
	}
	void scan(){//in
		int i=0,j,len;
		char in[100001];
		scanf("%s",in);
		if (in[0] == '-'){
			sign = -1;
			i++;
		}
		else if (in[0] == '0'){
			sign = 0;
		}
		else{
			sign = 1;
		}
		len = strlen(in) - 1;
		for (j = len;j >= i;j--){
			number.push_back(in[j]-'0');
		}
	}
};
