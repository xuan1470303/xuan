#include <iostream>
#include <cmath>
#include <string>
#include <cctype>
using namespace std;

class Polynomial;  // ���n��Polynomial���O 

class Term
{
    friend class Polynomial;  // ��Polynomial������Term���ͤ����A���\�X��Term���p������
    friend istream& operator>>(istream& in, Polynomial& poly); // ������J
    friend ostream& operator<<(ostream& out, const Polynomial& poly); // ������X
private:
    float coef;  // �����Y�� 
    int exp;     // �������� 
};

class Polynomial
{
public:
    Polynomial(); // �c�y���
    ~Polynomial(); // �Ѻc���
    Polynomial Add(Polynomial poly); // �[�k��� 
    Polynomial Mult(Polynomial poly); // ���k��� 
    float Eval(float x); // �p��h�����bx�ȤU�����G
    void Display() const; // ��ܦh���� 
    friend istream& operator>>(istream& in, Polynomial& poly); // ������J
    friend ostream& operator<<(ostream& out, const Polynomial& poly); // ������X

private:
    Term* termArray; // �ʺA���t��Term�Ʋ� 
    int capacity;    // ���Ʋժ��̤j�e�q 
    int terms;       // ��e�h���������� 

    void resize();   // �վ㶵�Ʋժ��j�p 
    int stringToInt(const string& str); // ����ഫ�r�Ŧ���� 
    void parseTerm(const string& termStr, Term& term); // �ѪR�涵 
};

// ��ʹ�{�r�Ŧ���ƪ��ഫ
int Polynomial::stringToInt(const string& str) {
    int result = 0;  // �̲ת���Ƶ��G
    bool isNegative = false;  // �P�_�Ÿ� 

    int startIdx = 0;  // �_�l���ޡA���L���t�� 
    if (str[0] == '-') {
        isNegative = true;  // �Y�r�Ŧ�H '-' �}�Y�A�]���t�� 
        startIdx = 1;  // �q�ĤG�Ӧr�Ŷ}�l�B�z 
    } else if (str[0] == '+') {
        startIdx = 1;  // �Y�H '+' �}�Y�A���L�Ÿ��A�q�ĤG�Ӧr�Ŷ}�l�B�z 
    }

    // �M���r�Ŧꤤ���C�Ӧr�šA�N���ഫ���Ʀr�ò֥[ 
    for (int i = startIdx; i < str.length(); ++i) {
        char ch = str[i];

        // �p�G�r�ŬO�Ʀr 
        if (ch >= '0' && ch <= '9') {
            result = result * 10 + (ch - '0');  // �N�r���ഫ����������ƨå[�쵲�G�� 
        } else {
            // �p�G�J��D�Ʀr�r�šA�����L�Ŀ�J�A���X�B�z 
            cout << "�L�Ī��r��: " << ch << endl;
            break;  // ����B�z 
        }
    }

    // �p�G�O�t�ơA��^�t�����G
    return isNegative ? -result : result;
}

// �ѪR��Ӷ� (�Ҧp "2X^1" �� "3" �� "-5X^2")
void Polynomial::parseTerm(const string& termStr, Term& term) {
    size_t xPos = termStr.find('X');  // �d��O�_�� 'X' �r�� 

    if (xPos != string::npos) {  // �p�G���F X
        // �����Y�� 
        string coefStr = termStr.substr(0, xPos); 
        if (coefStr.empty() || coefStr == "+" || coefStr == "-") {
            coefStr += "1";  // �p�G�Y�Ƴ������ũΥu�����t���A�h�q�{�� 1 �� -1
        }
        term.coef = stringToInt(coefStr); // �N�Y���ഫ���B�I�� 
        // �d����� 
        size_t expPos = termStr.find('^');
        if (expPos != string::npos) {  // �p�G�� '^'�A�h����᪺�Ʀr�@������ 
            term.exp = stringToInt(termStr.substr(expPos + 1));
        } else {  // �_�h�����q�{�� 1
            term.exp = 1;
        }
    } else {  // �S�� 'X'�A��ܳo�O�@�ӱ`�ƶ� 
        term.coef = stringToInt(termStr);  // �N�Ӷ������`�ƶ� 
        term.exp = 0;  // �`�ƶ������Ƭ� 0
    }
}

// �c�y��ơA��l�Ʀh���� 
Polynomial::Polynomial()
{
    capacity = 5;  // ��l�e�q��5
    terms = 0;
    termArray = new Term[capacity];  // �ʺA���tTerm�Ʋ� 
}

// �Ѻc��ơA������t�����s 
Polynomial::~Polynomial()
{
    delete[] termArray;  // ���񤺦s 
}

// ��Ʋծe�q�����ɡA�վ��j�p 
void Polynomial::resize()
{
    capacity *= 2;  // �N�e�q�[�� 
    Term* newArray = new Term[capacity];  // ���t�@�ӷs�����j���Ʋ� 

    // �N�{����������s�Ʋ� 
    for (int i = 0; i < terms; i++)
    {
        newArray[i] = termArray[i];
    }

    // �����ª��ƲըñN���w���V�s���Ʋ� 
    delete[] termArray;
    termArray = newArray;
}

// �Τ��J�h���� 
istream& operator>>(istream& in, Polynomial& poly)
{
    string input;
    cout << "�п�J�h���� (�Ҧp 2X^1+1): ";
    in >> input;

    // �B�z��J���h�����r�Ŧ� 
    size_t start = 0;
    while (start < input.length()) {
        size_t end = input.find_first_of("+-", start + 1);  // �d��U�Ӷ����}�l��m 
        if (end == string::npos) end = input.length();  // �p�G�S�����A�h��r�Ŧ굲�� 
        string termStr = input.substr(start, end - start);  // �����@�� 
        if (termStr != "") {
            Term newTerm;
            poly.parseTerm(termStr, newTerm);  // �ѪR�o���å[�J 
            if (poly.terms == poly.capacity) poly.resize();
            poly.termArray[poly.terms++] = newTerm;
        }

        start = end;  // ���ʨ�U�Ӷ����}�l��m 
    }

    return in;
}

// ��ܦh���� 
/*ostream& operator<<(ostream& out, const Polynomial& poly)
{
    for (int i = 0; i < poly.terms; i++)
    {
        if (i > 0 && poly.termArray[i].coef > 0)  // ��ܥ��� 
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
        if (i > 0 && poly.termArray[i].coef > 0)  // ��ܥ���
            out << "+";
        out << poly.termArray[i].coef << "X^" << poly.termArray[i].exp << " ";
    }
    out << endl;
    return out;
}

// �N��Ӧh�����ۥ[ 
Polynomial Polynomial::Add(Polynomial poly)
{
    Polynomial result;
    int i = 0, j = 0;

    // �X�֨�Ӧh�������� 
    while (i < terms && j < poly.terms)
    {
        if (termArray[i].exp > poly.termArray[j].exp)
        {
            result.termArray[result.terms++] = termArray[i++];  // �N���[�J���G�� 
        }
        else if (termArray[i].exp < poly.termArray[j].exp)
        {
            result.termArray[result.terms++] = poly.termArray[j++];  // �N���[�J���G�� 
        }
        else
        {
            // �p�G���ƬۦP�A�N�Y�Ƭۥ[ 
            result.termArray[result.terms].coef = termArray[i].coef + poly.termArray[j].coef;
            result.termArray[result.terms].exp = termArray[i].exp;
            result.terms++;
            i++;
            j++;
        }

        // �Y�Ʋդw���A�վ�j�p 
        if (result.terms == result.capacity)
            result.resize();
    }

    // �K�[�Ѿl���� 
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

// �N��Ӧh�����ۭ� 
Polynomial Polynomial::Mult(Polynomial poly)
{
    Polynomial result;

    // �N�Ĥ@�Ӧh�������C�@���P�ĤG�Ӧh�������C�@���ۭ� 
    for (int i = 0; i < terms; i++)
    {
        for (int j = 0; j < poly.terms; j++)
        {
            // �Y�Ƭۭ��A���Ƭۥ[ 
            double newCoef = termArray[i].coef * poly.termArray[j].coef;
            int newExp = termArray[i].exp + poly.termArray[j].exp;

            // �N���G���[�J���G�h���� 
            bool termAdded = false;
            for (int k = 0; k < result.terms; k++)
            {
                if (result.termArray[k].exp == newExp)
                {
                    result.termArray[k].coef += newCoef;  // �X�֬ۦP���ƪ��� 
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

            // �Y�Ʋդw���A�վ�j�p
            if (result.terms == result.capacity)
                result.resize();
        }
    }

    return result;
}

// �p��h�����b���wx�ȤU�����G
float Polynomial::Eval(float x)
{
    float result = 0;

    for (int i = 0; i < terms; i++)
    {
        result += termArray[i].coef * pow(x, termArray[i].exp);  // �ϥ�pow(x, exp)�p��x�����Ʀ���
    }

    return result;
}

// �D��ƨӺt�ܦp��ϥ�
int main()
{
    Polynomial p1, p2;
    
    cout << "�п�J�Ĥ@�Ӧh����:" << endl;
    cin >> p1;  // �Τ��J�Ĥ@�Ӧh����
    cout << "�п�J�ĤG�Ӧh����:" << endl;
    cin >> p2;  // �Τ��J�ĤG�Ӧh����

    cout << "�Ĥ@�Ӧh������: " << p1;  // ��ܲĤ@�Ӧh����
    cout << "�ĤG�Ӧh������: " << p2;  // ��ܲĤG�Ӧh����

    // �ܽdAdd�MMult��k
    Polynomial p3 = p1.Add(p2);  // �Np1�Mp2�ۥ[
    cout << "��Ӧh�����ۥ[�����G: " << p3;

    Polynomial p4 = p1.Mult(p2); // �Np1�Mp2�ۭ�
    cout << "��Ӧh�����ۭ������G: " << p4;

    // �p��h����p3�bx=2�ɪ���
    float result = p3.Eval(2.0);
    cout << "�h����p3�bx=2�ɪ���: " << result << endl;

    return 0;
}

