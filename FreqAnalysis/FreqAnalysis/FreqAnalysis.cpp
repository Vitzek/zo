/*bigram decryption requires mono statistics. Use decryptBi function only after GetMono();

logic: 
getting char and bigram stats from encrypted text and some book. 
write down stats in mono.txt for book
encrBi.txt, Emono.txt for encrypted file. 
mono data is sorted by alphabet position.
decrypt functions read data files and replace chars according to them. 
in bigram decryption just replace all bigrams according to bigram tables. If word length is odd the last char replaces according to mono stats.
*/

#include "GetMTable.h"
#include "decrypt.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	string path = "C:\\Users\\vitze\\Desktop\\Защита\\FreqAnalysis\\FreqAnalysis\\";
    GetMono(path + "book.txt", path + "mono.txt");
	GetMono(path + "encrypted.txt", path + "Emono.txt");
	decryptMono(path + "encrypted.txt", path+ "monoDecr.txt", path + "mono.txt", path + "Emono.txt");
	//биграммы не работают, файл с рашифрованным текстом прикреплен. Кодировка windows 1251.
	//GetBi(path + "encrypted.txt", path + "encrBi.txt");
	//GetBi(path + "book.txt", path + "bi.txt");
	//decryptBi(path + "encrypted.txt", path + "bi.txt", path + "mono.txt", path + "biDecr.txt", path + "Emono.txt", path + "encrBi.txt");
	return 0;
}

