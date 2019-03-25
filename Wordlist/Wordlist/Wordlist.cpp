// Wordlist.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "pch.h"
#include<stdlib.h>
#include <iostream>
#include<string>
#include<fstream>
using std::string;
string word[100000];
int word_num = 0;
int word_len[28][28];
int len_word[28][28];
string word_long[26][26];
int word_dis[28][28];
int indgree[28] = { 0 };
int outdgree[28] = { 0 };
int stack[28];
int stack_top = -1;
int topo[28];
int topo_top = -1;
int word_line[26];
int path[100] = { -1 };
int path_num = -1;
int type = 0;
int h_tag = 0;
int t_tag = 0;
int r_tag = 0;
int start_word = 'l' - 'a';
int tail_word = 'l' - 'a';

















/////////////////////////////////////////////////////////////////
string wordd[26][1000];
int wordd_num[26] = { 0 };
int words[26][1000][3];  //0:单词尾  1：单词长度  2：单词是否还能作为首单词遍历
int word_go[26][1000] = { 0 };   //一次遍历中已被遍历过的单词 
int longst = 0;
int longdst = 0;
int dlst = 0;
int d_num = 0;
int lst = 0;
string paths[1000];
int paths_num = -1;
string long_path[1000];
string long_dpath[1000];
void dfs(int start)
{
	int tag = 0;
	for (int k = 0; k < wordd_num[start]; k++) {
		if (!word_go[start][k]) {
			tag = 1;
			words[start][k][2] = 1;
			longst++;
			longdst = longdst + words[start][k][1];
			paths_num++;
			paths[paths_num] = wordd[start][k];
			word_go[start][k] = 1;
			//std::cout <<path[path_num];
			//std::cout<<"  ";
			dfs(words[start][k][0]);
			word_go[start][k] = 0;
			longdst = longdst - words[start][k][1];
			longst--;
			paths_num--;
		}
		else if (paths[paths_num] != wordd[start][k] && !r_tag) {
			std::cout << "形成单词环！程序结束！!\n";
			exit(0);
		}
	}
	if (tag == 0) {
		if (lst < longst) {
			lst = longst;
			for (int i = 0; i < lst; i++) {
				long_path[i] = paths[i];
			}
		}
		if (dlst < longdst) {
			dlst = longdst;
			d_num = longst;
			for (int i = 0; i < dlst; i++) {
				long_dpath[i] = paths[i];
			}
		}
	}
}

void all_dfs() {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < wordd_num[i]; j++) {
			if (!words[i][j][2]) {
				words[i][j][2] = 1;
				longst++;
				paths_num++;
				longdst += words[i][j][1];
				paths[paths_num] = wordd[i][j];
				word_go[i][j] = 1;
				dfs(words[i][j][0]);
				word_go[i][j] = 0;
				longst--;
				longdst -= words[i][j][1];
				paths_num--;
			}
		}
	}
}
void front_dfs(int i) {
	for (int j = 0; j < wordd_num[i]; j++) {
		if (!words[i][j][2]) {
			words[i][j][2] = 1;
			longst++;
			paths_num++;
			longdst += words[i][j][1];
			paths[paths_num] = wordd[i][j];
			word_go[i][j] = 1;
			dfs(words[i][j][0]);
			word_go[i][j] = 0;
			longst--;
			longdst -= words[i][j][1];
			paths_num--;
		}
	}
}
string t_word[26][1000];    //以尾字母为序保存单词 
int tail_word_num[26] = { 0 };  //尾字母的单词数量 
int tail_words[26][1000][3];  //0:单词首  1：单词长度  2：单词是否还能作为尾单词遍历
int tail_word_go[26][1000] = { 0 };   //一次遍历中已被遍历过的单词 
void fill_dictionary() {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < wordd_num[i]; j++) {
			t_word[wordd[i][j][wordd[i][j].length() - 1] - 'a'][tail_word_num[wordd[i][j][wordd[i][j].length() - 1] - 'a']++] = wordd[i][j];
		}
	}
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < tail_word_num[i]; j++) {
			tail_words[i][j][0] = t_word[i][j][0] - 'a';
			tail_words[i][j][1] = t_word[i][j].length();
		}
	}
}
void t_dfs(int start)
{
	int tag = 0;
	for (int k = 0; k < tail_word_num[start]; k++) {
		if (!tail_word_go[start][k]) {
			tag = 1;
			tail_words[start][k][2] = 1;
			longst++;
			longdst = longdst + tail_words[start][k][1];
			paths_num++;
			paths[paths_num] = t_word[start][k];
			tail_word_go[start][k] = 1;
			t_dfs(tail_words[start][k][0]);
			tail_word_go[start][k] = 0;
			longdst = longdst - tail_words[start][k][1];
			longst--;
			paths_num--;
		}
		else if (paths[paths_num] != t_word[start][k] && !r_tag) {
			std::cout << "形成单词环！程序结束！!\n";
			exit(0);
		}
	}
	if (tag == 0) {
		if (lst < longst) {
			lst = longst;
			for (int i = 0; i < lst; i++) {
				long_path[i] = paths[i];
			}
		}
		if (dlst < longdst) {
			dlst = longdst;
			d_num = longst;
			for (int i = 0; i < dlst; i++) {
				long_dpath[i] = paths[i];
			}
		}
	}
}
void tail_dfs(int i) {
	for (int j = 0; j < tail_word_num[i]; j++) {
		if (!tail_words[i][j][2]) {
			tail_words[i][j][2] = 1;
			longst++;
			paths_num++;
			longdst += tail_words[i][j][1];
			paths[paths_num] = t_word[i][j];
			tail_word_go[i][j] = 1;
			t_dfs(tail_words[i][j][0]);
			tail_word_go[i][j] = 0;
			longst--;
			longdst -= tail_words[i][j][1];
			paths_num--;
		}
	}
}
void ftdfs(int start, int tail)
{
	for (int k = 0; k < wordd_num[start]; k++) {
		if (!word_go[start][k]) {
			words[start][k][2] = 1;
			longst++;
			longdst = longdst + words[start][k][1];
			paths_num++;
			paths[paths_num] = wordd[start][k];
			word_go[start][k] = 1;
			if (words[start][k][0] == tail) {
				if (lst < longst) {
					lst = longst;
					for (int i = 0; i < lst; i++) {
						long_path[i] = paths[i];
					}
				}
				if (dlst < longdst) {
					dlst = longdst;
					d_num = longst;
					for (int i = 0; i < dlst; i++) {
						long_dpath[i] = paths[i];
					}
				}
			}
			ftdfs(words[start][k][0], tail);
			word_go[start][k] = 0;
			longdst = longdst - words[start][k][1];
			longst--;
			paths_num--;
		}
		else if (paths[paths_num] != wordd[start][k] && !r_tag) {
			std::cout << "形成单词环！程序结束！!\n";
			exit(0);
		}
	}
}
void ft_dfs(int i, int tail) {
	for (int j = 0; j < wordd_num[i]; j++) {
		if (!words[i][j][2]) {
			words[i][j][2] = 1;
			longst++;
			paths_num++;
			longdst += words[i][j][1];
			paths[paths_num] = wordd[i][j];
			word_go[i][j] = 1;
			ftdfs(words[i][j][0], tail);
			word_go[i][j] = 0;
			longst--;
			longdst -= words[i][j][1];
			paths_num--;
		}
	}
}
void r_run()
{
	int i, j;
	for (i = 0; i < 26; i++) {
		for (j = 0; j < wordd_num[i]; j++) {
			words[i][j][0] = wordd[i][j][wordd[i][j].length() - 1] - 'a';
			words[i][j][1] = wordd[i][j].length();
		}
	}
	fill_dictionary();
	if (h_tag == 0 && t_tag == 0) {
		all_dfs();
	}
	else if (h_tag == 1&& t_tag == 0) {
		front_dfs(start_word);
	}
	else if (t_tag == 1&& h_tag == 0) {
		tail_dfs(tail_word);
	}
	else if (h_tag == 1 && t_tag == 1) {
		ft_dfs(start_word, tail_word);
	}
	std::ofstream out("solution.txt");
	if (type == 0) {
		for (i = 0; i < lst; i++) {
			std::cout << long_path[i] + "\n";
			out << long_path[i] + "\n";
		}
	}
	else if (type == 1) {
		for (i = 0; i < d_num; i++) {
			std::cout << long_dpath[i] + "\n";
			out << long_dpath[i] + "\n";
		}
	}
	out.close();
}
/////////////////////////////////////////////////////////////////






















void dis()
{
	int k, i, j, s, b, t ;
	s = 26;
	b = 1;
	t = 27;

	if (h_tag == 1) {
		for (i = 1; i < 28; i++) {
			if (start_word == topo[i]) {
				b = i;
				s = topo[i];
			}
		}
	}
	if (t_tag == 1) {
		for (i = 1; i < 28; i++) {
			if (tail_word == topo[i]) {
				t = i;
				//std::cout <<t;
			}
		}
	}
	for (k = b; k <= t; k++) {
		for (j = 0; j < k; j++) {
			if (topo[j] != topo[k]) {
				if (type == 0) {
					if (word_len[s][topo[k]] > word_len[topo[j]][topo[k]] + word_len[s][topo[j]] + word_len[topo[k]][topo[k]]) {
						//	std::cout << (char)(s+'a');
					//		std::cout << "  ";
					//		std::cout << (char)(topo[k]+'a');
					//		std::cout << "鐨勮窛绂?  ";
						word_len[s][topo[k]] = word_len[topo[j]][topo[k]] + word_len[s][topo[j]] + word_len[topo[k]][topo[k]];
					//		std::cout << word_len[s][topo[k]];
					//		std::cout << "  ";
						path[topo[k]] = topo[j];
					//	std::cout << "???????????  ";
					//	std::cout << topo[k];
					//	std::cout << ":::::::::::::;;";
					//	std::cout << path[topo[k]];
					//	std::cout << "\n";
					}
				}
				else {
					if (len_word[s][topo[k]] > len_word[topo[j]][topo[k]] + len_word[s][topo[j]] + len_word[topo[k]][topo[k]]) {
						len_word[s][topo[k]] = len_word[topo[j]][topo[k]] + len_word[s][topo[j]] + len_word[topo[k]][topo[k]];
						path[topo[k]] = topo[j];
					}
				}
			}
			else {
				if (type == 0) {
					if (word_len[s][k] > word_len[topo[j]][topo[k]] + word_len[s][topo[j]]) {
						word_len[s][k] = word_len[topo[j]][topo[k]] + word_len[s][topo[j]];
					}
				}
				else {
					if (len_word[s][topo[k]] > len_word[topo[j]][topo[k]] + len_word[s][topo[j]]) {
						len_word[s][topo[k]] = len_word[topo[j]][topo[k]] + len_word[s][topo[j]];
					}
				}
			}
		}
	}
}
void topological_sort()
{
	int i, j, num = 0;
	for (i = 0; i < 26; i++) {
		for (j = 0; j < 26; j++) {
			if (word_len[i][j] < 1000000 && i != j) {
				indgree[j] += 1;
				outdgree[i] += 1;
			}
		}
	}

	for (i = 0; i < 26; i++) {
		if (indgree[i] == 0) {
			indgree[i] += 1;
			outdgree[26]++;
			word_len[26][i] = 0;
		}
		if (outdgree[i] == 0) {
			outdgree[i] += 1;
			indgree[27]++;
			word_len[i][27] = 0;
		}
	}

	stack[++stack_top] = 26;
	while (stack_top >= 0) {
		topo[++topo_top] = stack[stack_top--];
		for (i = 0; i < 28; i++) {
			if (word_len[topo[topo_top]][i] < 1000000 && topo[topo_top] != i) {
				indgree[i] -= 1;
				if (indgree[i] == 0) {
					stack[++stack_top] = i;
				}
			}
		}
	}
	for (i = 0; i < 28; i++) {
		if (indgree[i] != 0) {
			std::cout << "Existence ring！\n";
			exit(0);
		}
	}
}
int main(int argc, char *argv[])
{
	int tag = 0, head_num, i, j, tail_num, len,num;
	char txt[100];
	//const char *v = ".txt";
	strcpy_s(txt, sizeof(txt) / sizeof(txt[0]), argv[argc-1]);
	//strcat_s(txt, sizeof(txt) / sizeof(txt[0]), v);
	if (!strcmp(argv[argc - 2], "-w")) {
		type = 0;
	}
	else if(!strcmp(argv[argc - 2], "-c")){
		type = 1;
	}
	else {
		std::cout << "Wrong format!\n";
		exit(0);
	}
	switch (argc)
	{
	case 4: {
		if (!strcmp(argv[1], "-r")) {
			r_tag = 1;
		}
		break;
	}
	case 5: {
		if (!strcmp(argv[1], "-t")) {
			t_tag = 1;
			tail_word = argv[2][0];
			if (tail_word > 'A'&&tail_word < 'Z') {
				tail_word = tail_word - 'A' + 'a';
			}
			if (tail_word > 'a'&&tail_word < 'z') {
				tail_word = tail_word -'a';

			}
			else {
				std::cout << "尾字母范围错误！";
			}
		}
		else if (!strcmp(argv[1], "-h")) {
			h_tag = 1;
			start_word = argv[2][0];
			if (start_word > 'A'&&start_word < 'Z') {
				start_word = start_word - 'A' + 'a';
			}
			if (start_word > 'a'&&start_word < 'z') {
				start_word = start_word - 'a';

			}
			else {
				std::cout << "首字母范围错误！";
			}
		}
		break;
	}
	case 6: {
		for (i = 1; i < 4; i++) {
			if (!strcmp(argv[i], "-t")) {
				t_tag = 1;
				tail_word = argv[i+1][0];
				if (tail_word > 'A'&&tail_word < 'Z') {
					tail_word = tail_word - 'A' + 'a';
				}
				if (tail_word > 'a'&&tail_word < 'z') {
					tail_word = tail_word - 'a';

				}
				else {
					std::cout << "尾字母范围错误！";
				}
			}
			else if (!strcmp(argv[i], "-h")) {
				h_tag = 1;
				start_word = argv[i+1][0];
				if (start_word > 'A'&&start_word < 'Z') {
					start_word = start_word - 'A' + 'a';
				}
				if (start_word > 'a'&&start_word < 'z') {
					start_word = start_word - 'a';

				}
				else {
					std::cout << "首字母范围错误！";
				}
			}
			else if (!strcmp(argv[i], "-r")) {
				r_tag = 1;
			}
		}
	}
	case 7: {
		for (i = 1; i < 5; i++) {
			if (!strcmp(argv[i], "-t")) {
				t_tag = 1;
				tail_word = argv[i + 1][0];
				if (tail_word > 'A'&&tail_word < 'Z') {
					tail_word = tail_word - 'A' + 'a';
				}
				if (tail_word > 'a'&&tail_word < 'z') {
					tail_word = tail_word - 'a';

				}
				else {
					std::cout << "尾字母范围错误！";
				}
			}
			else if (!strcmp(argv[i], "-h")) {
				h_tag = 1;
				start_word = argv[i + 1][0];
				if (start_word > 'A'&&start_word < 'Z') {
					start_word = start_word - 'A' + 'a';
				}
				if (start_word > 'a'&&start_word < 'z') {
					start_word = start_word - 'a';

				}
				else {
					std::cout << "首字母范围错误！";
				}
			}
		}
		break;
	}
	case 8: {
		for (i = 1; i < 6; i++) {
			if (!strcmp(argv[i], "-t")) {
				t_tag = 1;
				tail_word = argv[i + 1][0];
				if (tail_word > 'A'&&tail_word < 'Z') {
					tail_word = tail_word - 'A' + 'a';
				}
				if (tail_word > 'a'&&tail_word < 'z') {
					tail_word = tail_word - 'a';

				}
				else {
					std::cout << "尾字母范围错误！";
				}
			}
			else if (!strcmp(argv[i], "-h")) {
				h_tag = 1;
				start_word = argv[i + 1][0];
				if (start_word > 'A'&&start_word < 'Z') {
					start_word = start_word - 'A' + 'a';
				}
				if (start_word > 'a'&&start_word < 'z') {
					start_word = start_word - 'a';

				}
				else {
					std::cout << "首字母范围错误！";
				}
			}
			else if (!strcmp(argv[1], "-r")) {
				r_tag = 1;
			}
		}
	}
	}
	FILE *fp;
	errno_t err;
	if ((err = fopen_s(&fp, txt, "r")) != 0) {
		std::cout << "The file was not exist!\n";
		exit(0);
	}
	char c = ' ';
	char d = ' ';
	for (i = 0; i < 28; i++) {
		for (j = 0; j < 28; j++) {
			if (i != j)
				word_len[i][j] = 1000000;
		}
	}
	while (c != EOF) {
		d = c;
		c = fgetc(fp);
		if (c >= 'A'&&c <= 'Z') {
			c = c + 'a' - 'A';
		}
		if (c >= 'a'&&c <= 'z') {
			if (tag == 0) {
				head_num = c - 'a';
				num = c - 'a';
				len = 0;
				word_num++;
				wordd_num[num]++;
			}
			tag = 1;
			wordd[num][wordd_num[num] - 1] = wordd[num][wordd_num[num] - 1] + c;
			word[word_num - 1] = word[word_num - 1] + c;
			len++;
		}
		else {
			if (tag == 1) {
				tail_num = d - 'a';
				if (word_len[head_num][tail_num] > -len) {
					word_len[head_num][tail_num] = -len;
					word_long[head_num][tail_num] = word[word_num - 1];
				}
			}
			tag = 0;
		}
	}
	if (r_tag == 1) {
		r_run();
		exit(0);
	}
	for (i = 0; i < 100; i++) {
		path[i] = -1;
	}
	topological_sort();
	for (i = 0; i < 28; i++) {
		for (j = 0; j < 28; j++) {
			if (word_len[i][j] < 0) {
				len_word[i][j] = -1;
			}
			else {
				len_word[i][j] = word_len[i][j];
			}
		}
	}
	dis();
	//std::cout << -word_len[26][27];           //鍗曡瘝閾炬€诲瓧姣嶆暟 
	int _path[28];
	for (i = 0; i < 28; i++) {
		_path[i] = -1;
	}
	j = 0;
	i = 27;
	if (t_tag == 1) {
		i = tail_word;
		_path[j++] = tail_word;
	}
	while (i >= 0 && path[i] >= 0) {
		_path[j++] = path[i];
		i = path[i];
	}
	
	//if (h_tag == 1) {
	//	_path[j++] = start_word;
	//}
	std::ofstream out("solution.txt");
	for (i = j-1; i >= 0; i--) {
		if (word_len[_path[i]][_path[i]] < 0) {
			std::cout << word_long[_path[i]][_path[i]];
			out << word_long[_path[i]][_path[i]];
			std::cout << "\n";
			out << "\n";
		}
		if (i > 0) {
			std::cout << word_long[_path[i]][_path[i - 1]];
			out << word_long[_path[i]][_path[i - 1]];
			std::cout << "\n";
			out << "\n";
		}
	}
	out.close();
	/*
	char o;
	for(i=0;i<28;i++){
		o=topo[i]+'a';
		std::cout << o;
	}
	std::cout << "\n";
	for(i=0;i<28;i++){
		for(j=0;j<28;j++){
			if(word_len[i][j]>=100000){
				std::cout << "1";
				std::cout << "  ";
			}
			else{
			std::cout << word_len[i][j];
			std::cout << "  ";
			}
		}
		std::cout << "\n";
	}*/
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
