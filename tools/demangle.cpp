#include <bits/stdc++.h>

using namespace std;

char syntax[] = { '!', '%', '^', '&', '*', '(', ')', '-', '+', '=', '{', '}',
		'|', '~', '[', ']', '\\', ';', '\'', ':', '"', ',', '<', '>', '?', '.',
		'/', '#', ' ' };

bool isSyntax(char c) {
	for (char tmp : syntax) {
		if (c == tmp) {
			return true;
		}
	}
	return false;
}
//从pos查找到下一个非空格字段
void skipSpace(const std::vector<std::string> &words, long unsigned int& i) {
	while (true) {
		i++;
		if (i >= words.size()) {
			//TODO:异常处理（未期待的结尾）
		}
		if (words[i] != " ") {
			break;
		}
	}
}

/*
 * 修饰规则：
 * 加上_alolang_前缀
 * 每个段前面加上长度
 * 比如fun foobar(long a, int b)修饰为_alolang_6foobar4long3int
 */
std::string demangle(const std::string &line) {
	std::vector<std::string> words;
	bool flag = false; //判断栈顶元素状态，如果为false则代表栈顶元素为符号
	for (long unsigned int i = 0; i < line.length(); i++) {
		if (isSyntax(line[i])) {
			words.push_back(std::string(1, line[i]));
			flag = false;
		} else {
			if (!flag) {
				words.push_back(std::string(1, line[i]));
				flag = true;
			} else {
				words[words.size() - 1] += std::string(1, line[i]);
			}
		}
	}
	std::stringstream ss;
	ss << "_alolang_";
	long unsigned int i = -1; //处理指针
	skipSpace(words, i);
	if (words[i] != "fun") {
		//TODO:异常处理
	}
	skipSpace(words, i);
	ss << words[i].length() << words[i];
	skipSpace(words, i);
	if (words[i] != "(") {
		//TODO:异常处理
	}
	skipSpace(words, i);
	if (words[i] != ")") {
		//有参数
		while (true) {
			skipSpace(words, i);
			ss << words[i].length() << words[i]; //得到类型
			skipSpace(words, i); //得到变量名，但在这个阶段没用
			skipSpace(words, i);
			if (words[i] == ")") {
				break;
			}
			if (words[i] != ",") {
				//TODO:异常处理（逗号）
			}
		}
	}
	return ss.str();
}

int main(int argc, char *argv[])
{
	cout << demangle(argv[1]) << endl;
	return 0;
}
