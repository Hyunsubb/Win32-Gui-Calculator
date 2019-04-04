#pragma once

class Convert {
private:
	int expLen, index;
	TCHAR popOp, tok;
	TCHAR* convExp;
public:
	Convert();
	void ConvToRPNExp(TCHAR[]);
	int GetOpPrec(TCHAR);
	int WhoPrecOp(TCHAR, TCHAR);
	int EvalRPNExp(TCHAR[]);
	~Convert();
};