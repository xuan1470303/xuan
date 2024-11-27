#include <iostream>
#include <cmath>
#include <string>
#include <cctype>
using namespace std;

class Polynomial;  // 先聲明Polynomial類別 

class Term
{
    friend class Polynomial;  // 使Polynomial類成為Term的友元類，允許訪問Term的私有成員
    friend istream& operator>>(istream& in, Polynomial& poly); // 重載輸入
    friend ostream& operator<<(ostream& out, const Polynomial& poly); // 重載輸出
private:
    float coef;  // 項的係數 
    int exp;     // 項的指數 
};

class Polynomial
{
public:
    Polynomial(); // 構造函數
    ~Polynomial(); // 解構函數
    Polynomial Add(Polynomial poly); // 加法函數 
    Polynomial Mult(Polynomial poly); // 乘法函數 
    float Eval(float x); // 計算多項式在x值下的結果
    void Display() const; // 顯示多項式 
    friend istream& operator>>(istream& in, Polynomial& poly); // 重載輸入
    friend ostream& operator<<(ostream& out, const Polynomial& poly); // 重載輸出

private:
    Term* termArray; // 動態分配的Term數組 
    int capacity;    // 項數組的最大容量 
    int terms;       // 當前多項式中的項 

    void resize();   // 調整項數組的大小 
    int stringToInt(const string& str); // 手動轉換字符串到整數 
    void parseTerm(const string& termStr, Term& term); // 解析單項 
};

// 手動實現字符串到整數的轉換
int Polynomial::stringToInt(const string& str) {
    int result = 0;  // 最終的整數結果
    bool isNegative = false;  // 判斷符號 

    int startIdx = 0;  // 起始索引，跳過正負號 
    if (str[0] == '-') {
        isNegative = true;  // 若字符串以 '-' 開頭，設為負數 
        startIdx = 1;  // 從第二個字符開始處理 
    } else if (str[0] == '+') {
        startIdx = 1;  // 若以 '+' 開頭，跳過符號，從第二個字符開始處理 
    }

    // 遍歷字符串中的每個字符，將其轉換為數字並累加 
    for (int i = startIdx; i < str.length(); ++i) {
        char ch = str[i];

        // 如果字符是數字 
        if (ch >= '0' && ch <= '9') {
            result = result * 10 + (ch - '0');  // 將字符轉換為對應的整數並加到結果中 
        } else {
            // 如果遇到非數字字符，視為無效輸入，跳出處理 
            cout << "無效的字符: " << ch << endl;
            break;  // 停止處理 
        }
    }

    // 如果是負數，返回負的結果
    return isNegative ? -result : result;
}

// 解析單個項 (例如 "2X^1" 或 "3" 或 "-5X^2")
void Polynomial::parseTerm(const string& termStr, Term& term) {
    size_t xPos = termStr.find('X');  // 查找是否有 'X' 字符 

    if (xPos != string::npos) {  // 如果找到了 X
        // 提取係數 
        string coefStr = termStr.substr(0, xPos); 
        if (coefStr.empty() || coefStr == "+" || coefStr == "-") {
            coefStr += "1";  // 如果係數部分為空或只有正負號，則默認為 1 或 -1
        }
        term.coef = stringToInt(coefStr); // 將係數轉換為浮點數 
        // 查找指數 
        size_t expPos = termStr.find('^');
        if (expPos != string::npos) {  // 如果有 '^'，則取其後的數字作為指數 
            term.exp = stringToInt(termStr.substr(expPos + 1));
        } else {  // 否則指數默認為 1
            term.exp = 1;
        }
    } else {  // 沒有 'X'，表示這是一個常數項 
        term.coef = stringToInt(termStr);  // 將該項視為常數項 
        term.exp = 0;  // 常數項的指數為 0
    }
}

// 構造函數，初始化多項式 
Polynomial::Polynomial()
{
    capacity = 5;  // 初始容量為5
    terms = 0;
    termArray = new Term[capacity];  // 動態分配Term數組 
}

// 解構函數，釋放分配的內存 
Polynomial::~Polynomial()
{
    delete[] termArray;  // 釋放內存 
}

// 當數組容量不夠時，調整其大小 
void Polynomial::resize()
{
    capacity *= 2;  // 將容量加倍 
    Term* newArray = new Term[capacity];  // 分配一個新的較大的數組 

    // 將現有項拷貝到新數組 
    for (int i = 0; i < terms; i++)
    {
        newArray[i] = termArray[i];
    }

    // 釋放舊的數組並將指針指向新的數組 
    delete[] termArray;
    termArray = newArray;
}

// 用戶輸入多項式 
istream& operator>>(istream& in, Polynomial& poly)
{
    string input;
    cout << "請輸入多項式 (例如 2X^1+1): ";
    in >> input;

    // 處理輸入的多項式字符串 
    size_t start = 0;
    while (start < input.length()) {
        size_t end = input.find_first_of("+-", start + 1);  // 查找下個項的開始位置 
        if (end == string::npos) end = input.length();  // 如果沒有找到，則到字符串結束 
        string termStr = input.substr(start, end - start);  // 提取一項 
        if (termStr != "") {
            Term newTerm;
            poly.parseTerm(termStr, newTerm);  // 解析這項並加入 
            if (poly.terms == poly.capacity) poly.resize();
            poly.termArray[poly.terms++] = newTerm;
        }

        start = end;  // 移動到下個項的開始位置 
    }

    return in;
}

// 顯示多項式 
/*ostream& operator<<(ostream& out, const Polynomial& poly)
{
    for (int i = 0; i < poly.terms; i++)
    {
        if (i > 0 && poly.termArray[i].coef > 0)  // 顯示正號 
            out << "+";

        out << poly.termArray[i].coef << "X^" << poly.termArray[i].exp << " ";
    }
    out << endl;
    return out;
}*/
ostream& operator<<(ostream& out, const Polynomial& poly)
{
    for (int i = 0; i < poly.terms; i++)
    {
        if (i > 0 && poly.termArray[i].coef > 0)  // 顯示正號
            out << "+";
        out << poly.termArray[i].coef << "X^" << poly.termArray[i].exp << " ";
    }
    out << endl;
    return out;
}

// 將兩個多項式相加 
Polynomial Polynomial::Add(Polynomial poly)
{
    Polynomial result;
    int i = 0, j = 0;

    // 合併兩個多項式的項 
    while (i < terms && j < poly.terms)
    {
        if (termArray[i].exp > poly.termArray[j].exp)
        {
            result.termArray[result.terms++] = termArray[i++];  // 將項加入結果中 
        }
        else if (termArray[i].exp < poly.termArray[j].exp)
        {
            result.termArray[result.terms++] = poly.termArray[j++];  // 將項加入結果中 
        }
        else
        {
            // 如果指數相同，將係數相加 
            result.termArray[result.terms].coef = termArray[i].coef + poly.termArray[j].coef;
            result.termArray[result.terms].exp = termArray[i].exp;
            result.terms++;
            i++;
            j++;
        }

        // 若數組已滿，調整大小 
        if (result.terms == result.capacity)
            result.resize();
    }

    // 添加剩餘的項 
    while (i < terms)
    {
        result.termArray[result.terms++] = termArray[i++];
    }
    while (j < poly.terms)
    {
        result.termArray[result.terms++] = poly.termArray[j++];
    }

    return result;
}

// 將兩個多項式相乘 
Polynomial Polynomial::Mult(Polynomial poly)
{
    Polynomial result;

    // 將第一個多項式的每一項與第二個多項式的每一項相乘 
    for (int i = 0; i < terms; i++)
    {
        for (int j = 0; j < poly.terms; j++)
        {
            // 係數相乘，指數相加 
            double newCoef = termArray[i].coef * poly.termArray[j].coef;
            int newExp = termArray[i].exp + poly.termArray[j].exp;

            // 將結果項加入結果多項式 
            bool termAdded = false;
            for (int k = 0; k < result.terms; k++)
            {
                if (result.termArray[k].exp == newExp)
                {
                    result.termArray[k].coef += newCoef;  // 合併相同指數的項 
                    termAdded = true;
                    break;
                }
            }

            if (!termAdded)
            {
                result.termArray[result.terms].coef = newCoef;
                result.termArray[result.terms].exp = newExp;
                result.terms++;
            }

            // 若數組已滿，調整大小
            if (result.terms == result.capacity)
                result.resize();
        }
    }

    return result;
}

// 計算多項式在給定x值下的結果
float Polynomial::Eval(float x)
{
    float result = 0;

    for (int i = 0; i < terms; i++)
    {
        result += termArray[i].coef * pow(x, termArray[i].exp);  // 使用pow(x, exp)計算x的指數次方
    }

    return result;
}

// 主函數來演示如何使用
int main()
{
    Polynomial p1, p2;
    
    cout << "請輸入第一個多項式:" << endl;
    cin >> p1;  // 用戶輸入第一個多項式
    cout << "請輸入第二個多項式:" << endl;
    cin >> p2;  // 用戶輸入第二個多項式

    cout << "第一個多項式為: " << p1;  // 顯示第一個多項式
    cout << "第二個多項式為: " << p2;  // 顯示第二個多項式

    // 示範Add和Mult方法
    Polynomial p3 = p1.Add(p2);  // 將p1和p2相加
    cout << "兩個多項式相加的結果: " << p3;

    Polynomial p4 = p1.Mult(p2); // 將p1和p2相乘
    cout << "兩個多項式相乘的結果: " << p4;

    // 計算多項式p3在x=2時的值
    float result = p3.Eval(2.0);
    cout << "多項式p3在x=2時的值: " << result << endl;

    return 0;
}

