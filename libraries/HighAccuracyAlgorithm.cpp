/*
高精的库，采用c++实现，底层使用vector
*/
#include <cstdio>
#include <vector>

using namespace std;

const int BSYS=10;//Basic

bool max(vector <int> x,vector <int> y){
	if (x.size() > y.size())	
		return true;
	else if (x.size() < y.size())
		return false;
	else
		for (int i = 0;i <= x.size();i++)
			if (x[i] > y[i])
				return true;
	return false;
}

void sub(vector <int> a,vector <int> b,vector <int> &c){
	int len,i;
    len = a.size();
    for (i = 0;i < len;i++)
    	c.push_back(a[i]);
    len = b.size();
   	for (i = 0;i < len;i++)
    	c[i] -= b[i];
    for (i = 0;i < a.size();i++){
    	if (c[i] < 0){
    		c[i] += BSYS;
    		c[i+1] -= 1;
		}
	}
	while (c[c.size()-1] == 0)
		c.pop_back();
}

struct HighAccuracyAlgorithm{
    vector <int> number;//number
    int sign;//Pos or Neg
    void Change_to_HAA(int origin_number){
    	if (origin_number < 0){
    		sign = -1;
    		origin_number=0-origin_number;
		}
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
    	if (sign + addend.sign == 0){
    		if (addend.sign == -1){	
    			if (max(number,addend.number)){
    				sub(number,addend.number,out.number);
					return out;
				}
				else if (max(addend.number,number)){
					out.sign = -1;
					sub(addend.number,number,out.number);
					return out;
				}
				else{
					out.sign = 0;
					return out;
				}
			}
			if (sign == -1){
				if (max(number,addend.number)){
					out.sign = -1;
					sub(number,addend.number,out.number);
					return out;
				}
				else if (max(addend.number,number)){
					sub(addend.number,number,out.number);
					return out;
				}
				else{
					out.sign = 0;
					return out;
				}
			}
		}
    	if (sign == -1 && addend.sign == -1){
    		out.sign = -1;
		}
    	len = addend.number.size()>number.size() ? addend.number.size() : number.size();
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
			out.number.push_back(out.number[number.size()-1] / BSYS);
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
		int i = 0,j = 0,len = 0;
		vector <char> init;
		char in;
		while (1){
			scanf("%c",&in);
			if (in == ' ' || in == '\n' ||((in < '0' || in > '9') && in != '-')){
				if ((in < '0' || in > '9') && in != '-' && in != ' ' && in != '\n'){
					sign = 0;
					return;
				}
				if (!j){
					continue;
				}
				break;
			}
			init.push_back(in);
			j = 1;
		}
		len = init.size() - 1;
		if (len == -1 || (len == 0 && init[0] < '0' || init[0] > '9')){
			sign = 0;
			return;
		}
		j = 0;
		for(int i = len;i >= 0;i--){
			if (init[i] == '-' ){
				sign = -1;
				continue;
			}
			number.push_back(init[i] - '0');
			j = 1;
			sign = 1;
		}
		while (number[number.size()-1] == 0)
			number.pop_back();
	}
};
