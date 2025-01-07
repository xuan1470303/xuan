#include<iostream>
#include <cmath>
using namespace std;
class Node {
public:
    float coef;
    int exp;
    Node* link;//指向下一個位子
};
class Polynomial {
private:
    Node* hand;
public:
    Node* getHand() const { return hand; } // 返回 hand 指針
    Polynomial();//建構值
    ~Polynomial();//解構值
    Polynomial(const Polynomial& a);//複製建構值
    void Added(float coef, int exp);//新增函數
    Polynomial& operator=(const Polynomial& a);//等號
    Polynomial operator+(const Polynomial& b);//加法
    Polynomial operator-(const Polynomial& b);//減法
    Polynomial operator*(const Polynomial& b);//乘法
    float Eval(float x)const;//給值代入
    friend ostream& operator<<(ostream& os, const Polynomial& b);
    friend istream& operator>>(istream& is, Polynomial& b);
};

//建構子初始化指標
Polynomial::Polynomial() : hand(nullptr) {}

//解構子 釋放記憶體
Polynomial::~Polynomial() 
{
    Node* temp;
    while (hand != nullptr)
    {
        temp = hand;
        hand = hand->link;
        delete temp;
    }
}

// 複製建構子  複製另一個多項式
Polynomial::Polynomial(const Polynomial& a) {
    hand = nullptr;
    Node* temp = a.hand;
    while (temp != nullptr) {
        Added(temp->coef, temp->exp);
        temp = temp->link;
    }
}

// 新增節點函數
void Polynomial::Added(float coef, int exp) {
    Node* newNode = new Node;
    newNode->coef = coef;
    newNode->exp = exp;
    newNode->link = nullptr;

    if (hand == nullptr || hand->exp < exp) {
        newNode->link = hand;
        hand = newNode;
    }
    else {
        Node* temp = hand;
        while (temp->link != nullptr && temp->link->exp >= exp) {
            temp = temp->link;
        }
        if (temp->exp == exp) {
            temp->coef += coef;  // 如果指數相同，合併係數
            delete newNode;   // 釋放多餘的節點
        }
        else {
            newNode->link = temp->link;
            temp->link = newNode;
        }
    }
}

//多項式的相加
Polynomial Polynomial::operator+(const Polynomial& b) {
    Polynomial result;
    Node* tempA = hand;
    Node* tempB = b.getHand();

    while (tempA != nullptr && tempB != nullptr) {
        if (tempA->exp > tempB->exp) {
            result.Added(tempA->coef, tempA->exp);
            tempA = tempA->link;
        }
        else if (tempA->exp < tempB->exp) {
            result.Added(tempB->coef, tempB->exp);
            tempB = tempB->link;
        }
        else {
            result.Added(tempA->coef + tempB->coef, tempA->exp);
            tempA = tempA->link;
            tempB = tempB->link;
        }
    }

    while (tempA != nullptr) {
        result.Added(tempA->coef, tempA->exp);
        tempA = tempA->link;
    }

    while (tempB != nullptr) {
        result.Added(tempB->coef, tempB->exp);
        tempB = tempB->link;
    }

    return result;
}

//多項式的相減
Polynomial Polynomial::operator-(const Polynomial& b) {
    Polynomial result;
    Node* tempA = hand;
    Node* tempB = b.getHand();

    while (tempA != nullptr && tempB != nullptr) {
        if (tempA->exp > tempB->exp) {
            result.Added(tempA->coef, tempA->exp);
            tempA = tempA->link;
        }
        else if (tempA->exp < tempB->exp) {
            result.Added(-tempB->coef, tempB->exp);
            tempB = tempB->link;
        }
        else {
            result.Added(tempA->coef - tempB->coef, tempA->exp);
            tempA = tempA->link;
            tempB = tempB->link;
        }
    }

    while (tempA != nullptr) {
        result.Added(tempA->coef, tempA->exp);
        tempA = tempA->link;
    }

    while (tempB != nullptr) {
        result.Added(-tempB->coef, tempB->exp);
        tempB = tempB->link;
    }

    return result;
}

Polynomial Polynomial::operator*(const Polynomial& b) {
    Polynomial result;
    Node* tempA = hand;   // 第一個多項式的指標
    Node* tempB = b.getHand();// 第二個多項式的指標

    while (tempA != nullptr) {
        tempB = b.getHand();  // 重置 tempB 為第二個多項式的頭節點
        while (tempB != nullptr) {
            // 相乘：係數相乘，指數相加
            float newCoef = tempA->coef * tempB->coef;
            int newExp = tempA->exp + tempB->exp;

            // 將結果加入到結果多項式
            result.Added(newCoef, newExp);

            tempB = tempB->link; // 移動到第二個多項式的下一個項目
        }

        tempA = tempA->link; // 移動到第一個多項式的下一個項目
    }

    return result;
}

Polynomial& Polynomial::operator=(const Polynomial& a) {
    if (this == &a) {
        return *this; // 防止自我賦值
    }

    // 清除當前多項式的節點
    Node* temp;
    while (hand != nullptr) {
        temp = hand;
        hand = hand->link;
        delete temp;
    }

    hand = nullptr;

    // 複製 a 的節點
    Node* tempA = a.hand;
    while (tempA != nullptr) {
        Added(tempA->coef, tempA->exp);
        tempA = tempA->link;
    }

    return *this;
}


// Evaluate the polynomial at a given value of x
float Polynomial::Eval(float x) const {
    float result = 0.0f;
    Node* temp = hand;
    while (temp != nullptr) {
        result += temp->coef * pow(x, temp->exp);
        temp = temp->link;
    }
    return result;
}

// Output stream overload to print the polynomial
ostream& operator<<(ostream& os, const Polynomial& b) {
    Node* temp = b.hand;
    bool first = true;
    while (temp != nullptr) {
        if (first) {
            first = false;
        }
        else {
            os << " + ";
        }
        os << temp->coef << "x^" << temp->exp;
        temp = temp->link;
    }
    return os;
}

// Input stream overload to read a polynomial
istream& operator>>(istream& in, Polynomial& b) {
    // 清空原來的多項式資料
        int num;
        cout << "請輸入有幾項指數: ";
        in >> num;
        for (int i = 0; i < num; i++)
        {//一個一個存
            cout << "請輸入系數與指數(EX. 2 2 3 1 1 0) ";
            int exp;
            float coef;
            in >> coef >> exp;
            b.Added(coef, exp);//新增
        }
        return in;
}


int main() {
    Polynomial p1, p2, result;

    cout << "請輸入第一個多項式"<<endl;
    cin >> p1;
    cout << "請輸入第二個多項式"<<endl;
    cin >> p2;
    cout << "Polynomial 1: " << p1 << endl;
    cout << "Polynomial 2: " << p2 << endl;
    result = p1 + p2;
    cout << "Sum of the polynomials: " << result << endl;
    result = p1 - p2;
    cout << "Difference of the polynomials: " << result << endl;
    result = p1 * p2;
    cout << "Product of the polynomials: " << result << endl;
    float x;
    cout << "Enter a value for x to evaluate the polynomials: ";
    cin >> x;
    cout << "Polynomial 1 evaluated at x = " << x << ": " << p1.Eval(x) << endl;
    cout << "Polynomial 2 evaluated at x = " << x << ": " << p2.Eval(x) << endl;

    return 0;
}
