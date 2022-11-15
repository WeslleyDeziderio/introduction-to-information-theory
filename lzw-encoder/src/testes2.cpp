#include <bits/stdc++.h>
using namespace std;
vector<int> encoding(string s1)
{
	cout << "Encoding\n";
	unordered_map<string, int> table;
	for (int i = 0; i <= 255; i++) {
		string ch = "";
		ch += char(i);
		table[ch] = i;
	}

	string p = "", c = "";
	p += s1[0];
	int code = 256;
	vector<int> output_code;
	cout << "String\tOutput_Code\tAddition\n";
	for (long unsigned int i = 0; i < s1.length(); i++) {
		if (i != s1.length() - 1)
			c += s1[i + 1];
		if (table.find(p + c) != table.end()) {
			p = p + c;
		}
		else {
			cout << p << "\t" << table[p] << "\t\t"
				<< p + c << "\t" << code << endl;
			output_code.push_back(table[p]);
			table[p + c] = code;
			code++;
			p = c;
		}
		c = "";
	}
	cout << p << "\t" << table[p] << endl;
	output_code.push_back(table[p]);
	return output_code;
}

void decoding(vector<int> op)
{
	cout << "\nDecoding\n";
	unordered_map<int, string> table;
	for (int i = 0; i <= 255; i++) {
		string ch = "";
		ch += char(i);
		table[i] = ch;
	}




	
	int old = op[0];
	int n;
	string s = table[old];
	string c = "";
	c += s[0];
	cout << s;
	int count = 256;
	for (long unsigned int i = 0; i < op.size() - 1; i++) {
		n = op[i + 1];
		if (table.find(n) == table.end()) {
			s = table[old];
			s = s + c;
		}
		else {
			s = table[n];
		}
		cout << s;
		c = "";
		c += s[0];
		table[count] = table[old] + c;
		count++;
		old = n;
	}
}
int main()
{

	string s = "Carlos considerou Ega com espanto. Para que? Para arrastar os passos tristes desde o Gremio at� � Casa Havaneza? N�o! Paris era o unico logar da terra congenere com o typo definitivo em que elle se fix�ra: - �o homem rico que vive bem�. Passeio a cavallo no Bois; alm��o no Bignon; uma volta pelo boulevard; uma hora no club com os jornaes; um bocado de florete na sala d'armas; � noite a Com�die Fran�aise ou uma soir�e; Trouville no ver�o, alguns tiros �s lebres no inverno; e atrav�s do anno as mulheres, as corridas, certo interesse pela sciencia, o bric-�-brac, e uma pouca de blague. Nada mais inoffensivo, mais nullo, e mais agradavel.";

	vector<int> output_code = encoding(s);
	cout << "Output Codes are: ";
	for (long unsigned int i = 0; i < output_code.size(); i++) {
		cout << output_code[i] << " ";
	}
	cout << endl;
	decoding(output_code);
}
