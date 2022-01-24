#include "decrypt.h"
#include "GetMTable.h"


void decryptMono(string encrPath, string outputPath, string monoPath, string EmonoPath) {
	//ifstream sEmono(EmonoPath);
	int(*monoPtr), (*EmonoPtr);
	int mono[64], Emono[64];
	monoPtr = &mono[0];
	EmonoPtr = &Emono[0];
	// reading file and sorting it min->max
	monoPtr = read64(monoPath, monoPtr);
	monoPtr = monoSort(monoPtr);
	EmonoPtr = read64(EmonoPath, EmonoPtr);
	EmonoPtr = monoSort(EmonoPtr);
	for (int i = 0; i < 64; i++) {
		cout << monoPtr[i] << " ";
	}
	cout << '\n';
	for (int i = 0; i < 64; i++) {
		cout << EmonoPtr[i] << " ";
	}
	replace(monoPtr, EmonoPtr, outputPath, encrPath);
}


//monogr reading from file
//array looks like {<char>, <number>, etc} sorted by freq
int* read64(string path, int* Ptr) {
	string word;
	ifstream smono(path);
	for (int i = 0; i < 63; i += 2) {
		smono >> word;
		while (word == "" || word == " ") {
			smono >> word;
		}
		Ptr[i] = -64 + (int)i / 2;
		Ptr[i + 1] = stoi(word);
	}
	smono.close();
	return Ptr;
}


//monogr sorting in array
int* monoSort(int* mono) {
	int cnt = 1;
	int buf;
	while (cnt != 0) {
		cnt = 0;
		for (int i = 0; i < 61; i += 2) {
			if (mono[i + 1] > mono[i + 3]) {
				buf = mono[i + 1];
				mono[i + 1] = mono[i + 3];
				mono[i + 3] = buf;
				buf = mono[i];
				mono[i] = mono[i + 2];
				mono[i + 2] = buf;
				cnt++;
			}
		}
	}
	return mono;
}

//final decr func. key { '<ref file letter>', '<encryption>', ... }
void replace(int* Ptr, int* EPtr, string outpath, string Epath) {
	int key[64];
	for (int i = 0; i < 63; i+=2) {
		key[i] = Ptr[i];
		key[i + 1] = EPtr[i];
	}
	string line;
	ifstream encr(Epath);
	ofstream output(outpath, std::ofstream::out);
	cout << "replacing\n";
	while (getline(encr, line, '\n')) {
		for (int i = 0; i < (int)line.length(); i++) {
			if (isCyrillic(line[i])) {
				for (int j = 63; j > 0; j -= 2) {
					if (line[i] == (char)key[j] || line[i] == (char)key[j] + 32) {
						if (line[i] < -32) {
							line[i] = (char)key[j - 1];
						}
						else {
							line[i] = (char)(key[j - 1]+32);
						}
						break;
					}
				}
			}
		}
		output << line << "\n";
	}
	encr.close();
	output.close();
}




//path + "encrypted.txt", path + "bi.txt", path + "mono.txt", path + "biDecr.txt", path + "Emono.txt"

void decryptBi(string encrPath, string biPath, string monoPath, string outputPath, string EmonoPath, string encBiPath)
{
	//ifstream sEmono(EmonoPath);
	int(*monoPtr), (*EmonoPtr), (*bi), (*encrBi);
	int mono[64], Emono[64];
	monoPtr = &mono[0];
	EmonoPtr = &Emono[0];
	// reading file and sorting it min->max
	monoPtr = read64(monoPath, monoPtr);
	monoPtr = monoSort(monoPtr);
	EmonoPtr = read64(EmonoPath, EmonoPtr);
	EmonoPtr = monoSort(EmonoPtr);
	for (int i = 0; i < 64; i++) {
		cout << monoPtr[i] << " ";
	}
	cout << '\n';
	for (int i = 0; i < 64; i++) {
		cout << EmonoPtr[i] << " ";
	}







	replace(monoPtr, EmonoPtr, outputPath, encrPath);
}