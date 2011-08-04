#include<iostream>
#include<stdio.h>
#include<string>
#include<utility>
#include<ctype.h>
using namespace std;

#define NUMBER 1	// Se for um número qualquer.
#define DOUBLE 3	// Se o número for um double.
#define ID 4		// Se for um ID.
#define OTHER 8		// Se for outra coisa (+,=,etc).

struct Token{
	string token;
	char type;

	void setType(int t){ type = t; };
	int getType(){ return type; };
	int isID(){ return type == ID; };
	int isOther(){ return type == OTHER; };
	int isNumber(){ return type & 1; };
	int isDouble(){ return type == 3; };
};

// Ignora brancos, monta um token e retorna a posição do buffer
// de onde a função deve ser chamada novamente.
//
// Retorna -1 caso encontre o fim do buffer.
int getNextToken(Token &t, int start_pos, char buffer[]){
	int i = start_pos;
	while(isspace(buffer[i]))
		i++;

	if(buffer[i] == '\0')
		return -1;

	// Monta id's.
	if(isalpha(buffer[i])){
		while(isalpha(buffer[i]))
			t.token.push_back(buffer[i++]);
		t.setType(ID);
		return i;
	}

	// Monta números.
	if(isdigit(buffer[i]) || buffer[i] == '.'){
		t.setType(NUMBER);
		bool decimalFlag = false;
		if(buffer[i] == '.'){
			t.token.append("0.");
			i++;
			decimalFlag = true;
			t.setType(DOUBLE);
		}

more:
		while(isdigit(buffer[i]))
			t.token.push_back(buffer[i++]);

		if(buffer[i] == '.' && !decimalFlag){
			t.setType(DOUBLE);
			decimalFlag = true;
			t.token.push_back(buffer[i++]);
			goto more;
		}
		return i;
	}

	// Monta outros tokens.
	if(ispunct(buffer[i])){
		t.token.push_back(buffer[i++]);
		t.setType(OTHER);
		return i;
	}
}

// Exemplo de uso:
/*
int main(){
	char str[101];
	Token t;
	int i = 0;

	fgets(str, 100, stdin);
	while(1){
		t.token.clear();
		i = getNextToken(t, i, str);
		if(i == -1)
			break;
		cout << t.token << endl;
	}
	return 0;
}
*/
