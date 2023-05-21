#include<iostream>
#include<thread>
using namespace std;
//для того чтобы упорядочить управление напишем
using namespace std::chrono_literals; //1s,1ms, задавать временные интервалы
bool finish = false;

void Plus()
{
	while (!finish)
	{
		cout << "+ ";
		std::this_thread::sleep_for(1s);//задержка 1 сек затормозили выполнение потока
	}
}
	void Minus()
	{
		while (!finish)
		{
			cout << "- ";
		    std::this_thread::sleep_for(1s);//задержка 1 сек
		}
	}
	void main()
	{
		//Plus();
		//Minus();

		cout << Plus << endl;//имя функции является указателем на функцию
		std::thread plus_thread(Plus);//функция Plus выполняется в отдельном потоке
		std::thread minus_thread(Minus);//
		cin.get();//метод get() ожидает нажатия enter после этого finish поменяется на true
		finish = true; 
		if(plus_thread.joinable())(plus_thread.join());//синхронизация потоков с main
		if (minus_thread.joinable())minus_thread.join();
}