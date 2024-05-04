#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <iomanip>
#include <sstream>
using namespace std;

// ������ʽ��
class Expression {
public:
    // ���ɱ��ʽ
    string generate();
    // ���ɲ�����
    string generateOperand();
    // ���������
    char generate_Operator();
    // ����ѡ��
    int maxNumber;
    vector<char> operators;
    bool allowParentheses;
    bool allowDecimals;
};

string Expression::generate() {
    int numOperands = rand() % 3 + 2;
    string expr;
    int leftParenCount = 0;
    for (int i = 0; i < numOperands; i++) {
        if (i < numOperands - 1 && allowParentheses && rand() % 5 == 0) {
            expr += "(";
            leftParenCount++;
            expr += generateOperand();
            expr += generate_Operator();
            expr += generateOperand();
            i += 2;
        }
        else {
            expr += generateOperand();
        }

        if (leftParenCount > 0 && (i == numOperands - 1 || rand() % 5 == 0)) {
            expr += ")";
            leftParenCount--;
        }
        if (i < numOperands - 1) {
            expr += generate_Operator();
        }
    }

    // ����ȱʧ��������
    while (leftParenCount > 0) {
        expr += ")";
        leftParenCount--;
    }

    return expr;
}

string Expression::generateOperand() {
    // ����[1, maxNumber]��Χ�ڵ�������С��
    double operand = rand() % maxNumber + 1;
    if (allowDecimals && rand() % 2 == 0) {
        operand += (rand() % 100) / 100.0;

        std::ostringstream oss;                     //������λС��
        oss << std::fixed << std::setprecision(2) << operand;
        return oss.str();
    }
    else {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(0) << operand;
        return to_string((int)operand);
    }
}

// �����������������ѡ��һ��
char Expression::generate_Operator() {
    int index = rand() % operators.size();
    return operators[index];
}


int main() {
    // ��ȡ�û�����
    int num_Expressions;
    cout << "������Ҫ���ɵ���Ŀ����: ";
    cin >> num_Expressions;

    int maxNumber;
    cout << "�����������: ";
    cin >> maxNumber;

    string operatorStr;
    cout << "����������������(+-*/): ";
    cin >> operatorStr;

    bool allow_Parentheses;
    cout << "�Ƿ���������(1/0): ";
    cin >> allow_Parentheses;

    bool allow_Decimals;
    cout << "�Ƿ�����С��(1/0): ";
    cin >> allow_Decimals;

    string outFile;
    cout << "����������ļ���: ";
    cin >> outFile;

    // ��ʼ�����ʽ������
    Expression exp;
    exp.maxNumber = maxNumber;
    for (char c : operatorStr) {
        exp.operators.push_back(c);
    }
    exp.allowParentheses = allow_Parentheses;
    exp.allowDecimals = allow_Decimals;

    // ���ɱ��ʽ��������ļ�
    ofstream fout(outFile);
    for (int i = 0; i < num_Expressions; i++) {
        fout << exp.generate() << " = " << endl;
    }
    fout.close();

    cout << "�������,��Ŀ�������" << outFile << endl;

    return 0;
}
