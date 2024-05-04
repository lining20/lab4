#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <iomanip>
#include <sstream>
using namespace std;

// 定义表达式类
class Expression {
public:
    // 生成表达式
    string generate();
    // 生成操作数
    string generateOperand();
    // 生成运算符
    char generate_Operator();
    // 配置选项
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

    // 补齐缺失的右括号
    while (leftParenCount > 0) {
        expr += ")";
        leftParenCount--;
    }

    return expr;
}

string Expression::generateOperand() {
    // 生成[1, maxNumber]范围内的整数或小数
    double operand = rand() % maxNumber + 1;
    if (allowDecimals && rand() % 2 == 0) {
        operand += (rand() % 100) / 100.0;

        std::ostringstream oss;                     //保留两位小数
        oss << std::fixed << std::setprecision(2) << operand;
        return oss.str();
    }
    else {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(0) << operand;
        return to_string((int)operand);
    }
}

// 从允许的运算符中随机选择一个
char Expression::generate_Operator() {
    int index = rand() % operators.size();
    return operators[index];
}


int main() {
    // 读取用户配置
    int num_Expressions;
    cout << "请输入要生成的题目数量: ";
    cin >> num_Expressions;

    int maxNumber;
    cout << "请输入最大数: ";
    cin >> maxNumber;

    string operatorStr;
    cout << "请输入允许的运算符(+-*/): ";
    cin >> operatorStr;

    bool allow_Parentheses;
    cout << "是否允许括号(1/0): ";
    cin >> allow_Parentheses;

    bool allow_Decimals;
    cout << "是否允许小数(1/0): ";
    cin >> allow_Decimals;

    string outFile;
    cout << "请输入输出文件名: ";
    cin >> outFile;

    // 初始化表达式生成器
    Expression exp;
    exp.maxNumber = maxNumber;
    for (char c : operatorStr) {
        exp.operators.push_back(c);
    }
    exp.allowParentheses = allow_Parentheses;
    exp.allowDecimals = allow_Decimals;

    // 生成表达式并输出到文件
    ofstream fout(outFile);
    for (int i = 0; i < num_Expressions; i++) {
        fout << exp.generate() << " = " << endl;
    }
    fout.close();

    cout << "生成完毕,题目已输出到" << outFile << endl;

    return 0;
}
