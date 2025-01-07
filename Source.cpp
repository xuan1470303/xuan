#include<iostream>
#include <cmath>
using namespace std;
class Node {
public:
    float coef;
    int exp;
    Node* link;//���V�U�@�Ӧ�l
};
class Polynomial {
private:
    Node* hand;
public:
    Node* getHand() const { return hand; } // ��^ hand ���w
    Polynomial();//�غc��
    ~Polynomial();//�Ѻc��
    Polynomial(const Polynomial& a);//�ƻs�غc��
    void Added(float coef, int exp);//�s�W���
    Polynomial& operator=(const Polynomial& a);//����
    Polynomial operator+(const Polynomial& b);//�[�k
    Polynomial operator-(const Polynomial& b);//��k
    Polynomial operator*(const Polynomial& b);//���k
    float Eval(float x)const;//���ȥN�J
    friend ostream& operator<<(ostream& os, const Polynomial& b);
    friend istream& operator>>(istream& is, Polynomial& b);
};

//�غc�l��l�ƫ���
Polynomial::Polynomial() : hand(nullptr) {}

//�Ѻc�l ����O����
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

// �ƻs�غc�l  �ƻs�t�@�Ӧh����
Polynomial::Polynomial(const Polynomial& a) {
    hand = nullptr;
    Node* temp = a.hand;
    while (temp != nullptr) {
        Added(temp->coef, temp->exp);
        temp = temp->link;
    }
}

// �s�W�`�I���
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
            temp->coef += coef;  // �p�G���ƬۦP�A�X�֫Y��
            delete newNode;   // ����h�l���`�I
        }
        else {
            newNode->link = temp->link;
            temp->link = newNode;
        }
    }
}

//�h�������ۥ[
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

//�h�������۴�
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
    Node* tempA = hand;   // �Ĥ@�Ӧh����������
    Node* tempB = b.getHand();// �ĤG�Ӧh����������

    while (tempA != nullptr) {
        tempB = b.getHand();  // ���m tempB ���ĤG�Ӧh�������Y�`�I
        while (tempB != nullptr) {
            // �ۭ��G�Y�Ƭۭ��A���Ƭۥ[
            float newCoef = tempA->coef * tempB->coef;
            int newExp = tempA->exp + tempB->exp;

            // �N���G�[�J�쵲�G�h����
            result.Added(newCoef, newExp);

            tempB = tempB->link; // ���ʨ�ĤG�Ӧh�������U�@�Ӷ���
        }

        tempA = tempA->link; // ���ʨ�Ĥ@�Ӧh�������U�@�Ӷ���
    }

    return result;
}

Polynomial& Polynomial::operator=(const Polynomial& a) {
    if (this == &a) {
        return *this; // ����ۧڽ��
    }

    // �M����e�h�������`�I
    Node* temp;
    while (hand != nullptr) {
        temp = hand;
        hand = hand->link;
        delete temp;
    }

    hand = nullptr;

    // �ƻs a ���`�I
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
    // �M�ŭ�Ӫ��h�������
        int num;
        cout << "�п�J���X������: ";
        in >> num;
        for (int i = 0; i < num; i++)
        {//�@�Ӥ@�Ӧs
            cout << "�п�J�t�ƻP����(EX. 2 2 3 1 1 0) ";
            int exp;
            float coef;
            in >> coef >> exp;
            b.Added(coef, exp);//�s�W
        }
        return in;
}


int main() {
    Polynomial p1, p2, result;

    cout << "�п�J�Ĥ@�Ӧh����"<<endl;
    cin >> p1;
    cout << "�п�J�ĤG�Ӧh����"<<endl;
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
