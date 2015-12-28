#include <iostream>
#include <math.h>
#include <time.h>
#include "gen_rand.h"
using namespace std;

const int IMAX = numeric_limits<int>::max();

class Client{//����� ����������� ������� ��� ������ �����
private:
	int a, K;
public:
	int g, p, secKey, A;
	Client(int a)
	{
		this->a = a;
		this->g = 0;
		this->p = 0;
		this->K = 0;
		this->A = 0;
		this->secKey = 0;
		cout << this->a;
	}
	void genPublicKey()//��������� ��������� �����
	{		
		this->A = modPow(this->g, this->a, this->p);
		cout << this->g << "^" << this->a << "mod" << this->p;
	}
	void secPublicKey(int B)//����� ��������� ����� ������� �������
	{
		this->secKey = B;
	}
	void genPrivateKey()// ��������� ��������� �����
	{		
		this->K = modPow(this->secKey, this->a, this->p);
	}
	void showPrivateKey()//����� ��������� �����
	{
		cout << this->K;
	}
	void startCommunication()
	{
		this->p = gen_prime(100, 99999);
		this->g = generator(this->p);
	}
};

int main()
{
	srand(time(0));

	cout << "Alice private Key : ";
	Client Alice(gen_prime(1000, 9999));//����� ������� �������� ���� a
	cout << "\nBob private Key : ";
	Client Bob(gen_prime(1000, 9999));//��� ������� �������� ���� b

	Alice.startCommunication(); //A: p - �������, g - ������������� ������ �� ������
	cout << "\n\np : " << Alice.p<<"\ng : "<< Alice.g;
	Bob.p = Alice.p;//A=>B: p
	Bob.g = Alice.g;//A=>B: g
	cout << "\n\nAlice public key = ";
	Alice.genPublicKey();// ����� ��������� �������� ���� g^a mod p
	cout << "\nA => B : Alice public key : " << Alice.A;
	cout << "\n\nBob public key = ";
	Bob.genPublicKey();
	cout << "\nB => A : Bob public key : " << Bob.A;

	Alice.secPublicKey(Bob.A);//B=>A: B
	Bob.secPublicKey(Alice.A);//A=>B: A
	Alice.genPrivateKey();//����� ��������� ����� ��������� ���� K = B^a mod p
	Bob.genPrivateKey();// K = A^b mod p
	cout << "\n\nAlice general private Key : ";
	Alice.showPrivateKey();
	cout << "\nBob general private Key : ";
	Bob.showPrivateKey();

	cout << "\n\n";
	system("pause");
	return 0;
}