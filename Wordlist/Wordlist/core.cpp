#include "pch.h"
#include "interface.h"
#include<stdlib.h>
#include <iostream>
#include<string>
#include<fstream>
using std::string;
int gen_chain(char * words[], int len, char * result[])
{
	return 0;
}
void dis(char start_word,char tail_word,int topo[],int type,int word_len[][28],int len_word[][28],int path[])
{
	int k, i, j, s, b, t,h_tag=0,t_tag=0;
	s = 26;
	b = 1;
	t = 27;
	if (start_word != 0) {
		h_tag = 1;
	}
	if (tail_word != 0) {
		t_tag = 1;
	}
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
					//		std::cout << "çš„è·ç¦?  ";
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
void topological_sort(int word_len[][28],int topo[])
{
	int i, j, num = 0,indgree[28],outdgree[28],stack[28],stack_top=-1,topo_top=-1;
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
			std::cout << "Existence ring£¡\n";
			exit(0);
		}
	}
}
int gen_chain_word(char * words[], int len, char * result[], char head, char tail, bool enable_loop)
{
	int word_len[28][28],i,j,topo[28],path[28];
	string word_long[28][28];
	for (i = 0; i < 28; i++) {
		for (j = 0; j < 28; j++) {
			if (i != j)
				word_len[i][j] = 1000000;
		}
	}
	if (enable_loop == 0) {
		for (i = 0; i < len; i++) {
			if (word_len[words[i][0] - 'a'][ words[i][strlen(words[i]) - 1] - 'a']>-(int)(strlen(words[i]))) {
				word_len[words[i][0] - 'a'][words[i][strlen(words[i]) - 1] - 'a'] = -(int)(strlen(words[i]));
				word_long[words[i][0] - 'a'][words[i][strlen(words[i]) - 1] - 'a'] = words[i];
			}
		}
		topological_sort(word_len,topo);
		dis(head,tail,topo,0, word_len, word_len,path);
	}
	return 0;
}

int gen_chain_char(char * words[], int len, char * result[], char head, char tail, bool enable_loop)
{
	return 0;
}
