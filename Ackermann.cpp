#include<iostream>
#include<math.h>
using namespace std;
int A_Dh(int m, int n)
{
	if (m == 0) { return n + 1; }
	else if (n == 0) { return A_Dh(m - 1, 1); }
	else { return A_Dh(m - 1, A_Dh(m, n - 1)); }
}

int A_unDh(int m,int n)
{
   if(m==0) return n+1;
   else if(m==1)
   {
      n=n+2; return n;
   }
   else if(m==2)
   {
   	  n=2*n+3;  return n;
   }
   else 
   {
   	  n=pow(2,(n+3))-3;
	  return n;
   }
  
   
}


int main()
{
	int m, n;
	cout << "�п�J�G���m,n --> A(m,n)  m<4,n<4" << endl;
	cin >> m >> n;
	while((m>3)||(n>3))
	{
		cout << "�п�J�G���m,n --> A(m,n)  m<4,n<4" << endl;
		cin >> m >> n;
	}
	cout <<"�ϥλ��j   : "<< A_Dh(m, n)<<endl;
	cout <<"�ϥΫD���j : "<<A_unDh(m, n)<<endl;
}
