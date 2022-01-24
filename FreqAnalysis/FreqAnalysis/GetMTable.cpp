#include "GetMTable.h"
#include <math.h>
#include <cmath>

//getting char stats and writing to file
void GetMono(string filename, string outputPath) {
	setlocale(LC_ALL, "Russian");
	int table[32];
	int total = 0;
	string line;
	for (int i = 0; i < 32; i++) {
		table[i] = 0;
	}
	ifstream ref(filename);
	while (getline(ref, line, '\n')) {
		for (int i = 0; i < (int)line.size(); i++) {
			//cout << line[i];
			if (isCyrillic(line[i])) {
				total++;
				if (line[i] < -32 && line[i] > -65) {
					table[line[i] + 64]++;
				}
				else {
					if ((int)line[i] == -88 || (int)line[i] == -72) {
						table[5]++;
					}
					else {
						table[line[i] + 32]++;
					}
				}
			}
		}
	}
	ref.close();
	ofstream out(outputPath);
	cout << "total cyr symbols: " << total << endl;
	for (int i = 0; i < 32; i++) {
		cout <<char(-64+i) << " " << table[i] << " ";
		out << table[i] << " ";
	}
	out.close();
}



/*
a_		b_		c_		d_
n	a	n	a	n	a	n	a
n	b	n	b	n	b	n	b
n	c	n	c	n	c	n	c

table[32][63] = total bigramms
then sorting every column
*/
/*void GetBi(string filename, string outputPath) {
	int table[33][64];
	for (int i = 0; i < 32; i++) {
		table[0][i * 2] = -64 + i;
		table[0][i * 2 + 1] = 0;
		for (int j = 0; j < 32; j++) {
			table[j+1][i * 2 + 1] = -64+j;
			table[j+1][i * 2] = 0;
		}
	}
	string line;
	ifstream ref(filename);
	int l, k, total; //vars for table index
	total = 0;
	while (getline(ref, line, '\n')) {
		for (int i = 0; i < (int)line.size(); i++) {
			if (isCyrillic(line[i]) && line.size() > i + 1 && isCyrillic(line[i + 1])) {
				//cout << line[i];
				if (line[i] < -32) {
					k = ((int)line[i] + 64) * 2;
				}
				else {
					k = ((int)line[i] + 32) * 2;
				}
				if (line[i+1] < -32){
					l = (int)line[i + 1] + 65;
				}
				else {
					l = (int)line[i + 1] + 33;
				}
				/*if (line[i] < -32 && line[i] > -65) {
					table[(int)line[i+1] + 65][((int)line[i] + 64) * 2]++;
					//line[i+1] -> -64|-33 => 1-32 row
					//line[i] ->  -64|-33 => 0-64 column %2
				}
				else {
					table[(int)line[i + 1] + 33][((int)line[i] + 32) * 2]++;
				}
				table[l][k]++;
				total++;
			}
		}
	}
	cout << total;
	ref.close();
	int (*ptr)[64] = table;
	biSort(ptr);
	int tmp, cnt;
	ofstream out(outputPath);
	for (int i = 0; i < 33; i++) {
		for (int j = 0; j < 64; j++) {
			out << table[i][j] << "";
			line = to_string(table[i][j]);
			for (int i = 0; i < 13 - line.length(); i++) {
				out << " ";
			}
		}
		out << "\n";
	}
	out.close();
}*/


void GetBi(string filename, string outputPath) {
	int table[1024][3];
	for (int i = 0; i < 1024; i++) {
		table[i][0] = i / 32 - 32;
		table[i][1] = -(i % 32)-1;
		table[i][2] = 0;
		//cout << table[i][0] << " " << table[i][1] << " " << table[i][2] << endl;
	}
	string line;
	ifstream ref(filename);
	int pos, total;
	total = 0;

	while (getline(ref, line, '\n')) {
		if(line.size()>1){
			for (int i = 0; i < (int)line.size() - 1; i++) {
				if (isCyrillic(line[i]) && isCyrillic(line[i + 1])) {
					pos = -(int(line[i]) % 32)*32 - (int(line[i + 1] + 1)); //line{-32 -1 num ; -32 -2 num ..... -1 -32 num}
					//cout << int(line[i]) << " " << int(line[i + 1]) << " " << -int(line[i]) % 32 << "  " << -int(line[i + 1] + 1) << '\t' << pos << endl;
					//int(cyrillic) {-64 -1} need values 0-31.
					table[pos][2] ++;
					total++;
				}
			}
		}
	}

	//cout << total;
	ref.close();
	int (*ptr)[3] = table;
	biSort1024(ptr);
	int tmp, cnt;
	ofstream out(outputPath);
	for (int i = 0; i < 1024; i++) { //1024 is max but no reasn to write down all bigrams, about half not used. 
		out << char(table[i][0]) << char(table[i][1]) << " " << to_string(table[i][2]) << endl;
	}
	out.close();
	}
//just bubble sorting function
//table[1024][3]
void biSort1024(int(*ptr)[3]) {
	int cnt =1 ;
	int buf;
		while (cnt != 0) {
			cnt = 0;
			for (int j = 0; j < 1023; j++) {
				if (ptr[j][2] < ptr[j + 1][2]) {
					for (int i = 0; i < 3; i++) {
						buf = ptr[j][i];
						ptr[j][i] = ptr[j + 1][i];
						ptr[j + 1][i] = buf;
					}
					cnt++;
				}
			}
			//cout << cnt << endl;

	}
}
//table[32][63]
/*void biSort(int(*ptr)[64]) {
	int cnt;
	int buf;
	for (int i = 0; i < 64; i+=2) {
		cnt = 1;
		while (cnt != 0) {
			cnt = 0;
			for (int j = 1; j < 32; j++) {
				if (ptr[j][i] < ptr[j+1][i]) {
					buf = ptr[j][i];
					ptr[j][i] = ptr[j+1][i];
					ptr[j+1][i] = buf;
					cnt++;
					buf = ptr[j][i+1];
					ptr[j][i+1] = ptr[j + 1][i+1];
					ptr[j + 1][i+1] = buf;
					cnt++;
				}
			}
		}
	}
}*/


bool isCyrillic(char sym) {
	if (((int)sym < 0 && (int)sym > -65) || ((int)sym == -72) || ((int)sym == -88)) {
		return 1;
	}
	else {
		return 0;
	}
}