#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<ctype.h>
#include"Convert.h"
#include"Stack.h"

Convert::Convert() {
	index = popOp = tok = expLen = 0;
}

void Convert::ConvToRPNExp(TCHAR exp[]) {
	Stack stack;
	expLen = lstrlen(exp);
	convExp = new TCHAR[expLen + 1];
	memset(convExp, 0, expLen);

	for (int i = 0; i < expLen; i++) {
		tok = exp[i];
		if (iswdigit(tok)) {
			convExp[index++] = tok;
		}
		else {
			switch (tok) {
			case '(':
				stack.SPush(tok);
				break;
			case ')':
				while (1) {
					popOp = stack.SPop();
					if (popOp == '(') {
						break;
					}
					convExp[index++] = popOp;
				}
				break;
			case '+':
			case '-':
			case '*':
			case '/':
				while (!stack.SIsEmpty() && WhoPrecOp(stack.SPeek(), tok) >= 0) {
					convExp[index++] = stack.SPop();
				}
				stack.SPush(tok);
				break;
			}
		}
	}
	while (!stack.SIsEmpty()) {
		convExp[index++] = stack.SPop();
	}
	convExp[index] = '\0';
	lstrcpy(exp, convExp);
}

int Convert::GetOpPrec(TCHAR ch) {
	switch (ch) {
	case '*':
	case '/':
		return 5;
	case '+':
	case '-':
		return 3;
	default:
		return 1;
	}
}

int Convert::WhoPrecOp(TCHAR ch1, TCHAR ch2) {
	int op1 = GetOpPrec(ch1);
	int op2 = GetOpPrec(ch2);

	if (op1 > op2) {
		return 1;
	}
	else if (op1 < op2) {
		return -1;
	}
	else {
		return 0;
	}
}

int Convert::EvalRPNExp(TCHAR exp[]) {
	Stack list;
	expLen = lstrlen(exp);
	index = popOp = tok = 0;
	int op1 = 0, op2 = 0;

	for (int i = 0; i < expLen; i++) {
		tok = exp[i];
		if (iswdigit(tok)) {
			list.SPush((tok - '0'));
		}
		else {
			op2 = list.SPop();
			op1 = list.SPop();
			switch (tok) {
			case '+':
				list.SPush(op1 + op2);
				break;
			case '-':
				list.SPush(op1 - op2);
				break;
			case '*':
				list.SPush(op1 * op2);
				break;
			case '/':
				list.SPush(op1 / op2);
				break;
			}
		}
	}
	return list.SPop();
}

Convert::~Convert() {
	delete[] convExp;
}