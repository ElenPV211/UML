#include<iostream>
#include<thread>
using namespace std;
//��� ���� ����� ����������� ���������� �������
using namespace std::chrono_literals; //1s,1ms, �������� ��������� ���������
bool finish = false;

void Plus()
{
	while (!finish)
	{
		cout << "+ ";
		std::this_thread::sleep_for(1s);//�������� 1 ��� ����������� ���������� ������
	}
}
	void Minus()
	{
		while (!finish)
		{
			cout << "- ";
		    std::this_thread::sleep_for(1s);//�������� 1 ���
		}
	}
	void main()
	{
		//Plus();
		//Minus();

		cout << Plus << endl;//��� ������� �������� ���������� �� �������
		std::thread plus_thread(Plus);//������� Plus ����������� � ��������� ������
		std::thread minus_thread(Minus);//
		cin.get();//����� get() ������� ������� enter ����� ����� finish ���������� �� true
		finish = true; 
		if(plus_thread.joinable())(plus_thread.join());//������������� ������� � main
		if (minus_thread.joinable())minus_thread.join();
}