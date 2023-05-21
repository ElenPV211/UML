#include<iostream>
#include<conio.h> //библиотека для функции _getch
#include<thread>//заголовок с потоками
#include<Windows.h>
using namespace std;
#define MIN_TANK_VOLUME 20
#define MAX_TANK_VOLUME 100


class Tank
{
	const int VOLUME; //объём - характеристика бака
	double fuel_level; //уровень топлива - состояние бака

public:
	int get_VOLUME() const
	{
		return VOLUME;
	}
	double get_fuel_level()const
	{
		return fuel_level;
	}
	double give_fuel(double amount)
	{
		fuel_level -= amount;
		if (fuel_level < 0)fuel_level = 0;
		return fuel_level;
	}
	void fill(double fuel)  //заправка топлива
		//здесь важна инкапсуляция
	{
		if (fuel < 0)return;
		if (fuel_level + fuel > VOLUME)fuel_level = VOLUME;
		else fuel_level += fuel;
	}
	//-----Constractor
	Tank(int volume) :VOLUME(
		volume < MIN_TANK_VOLUME ? MIN_TANK_VOLUME ://после: выбирается в противном случае
		volume > MAX_TANK_VOLUME ? MAX_TANK_VOLUME :
		volume	    //текущее значение
	), fuel_level(0)//с конвеера бак сошёл пустой
	{
		//константа уже создана и мы её перезаписываем
		//для того чтобы её проинициализировать мы в нашу константу в классе
		//создали define min и max
		//if (volume >= 20 && volume <= 100)this->VOLUME = volume;//инициализацию мы вынесли в заголовок
		//this->fuel_level = 0;
		cout << "Tank is ready" << endl;
	}
	~Tank()
	{
		cout << "Tank is over" << endl;
	}

	void info()const
	{
		cout << "Tank volume:\t" << get_VOLUME() << " liters.\n";
		cout << "Fuel level:\t" << get_fuel_level() << " liters.\n";
	}
};
#define MIN_ENGINE_CONSUMPTION 3
#define MAX_ENGINE_CONSUMPTION 25

class Engine
{
	int consumption;  //расход топлива на 100 км
	double consumption_per_second; //расход топлива за 1 секунду на холостом ходу
	bool is_started;
public://инкапсуляция
	Engine(int consumption) : consumption(
		consumption<MIN_ENGINE_CONSUMPTION ? MIN_ENGINE_CONSUMPTION :
		consumption>MAX_ENGINE_CONSUMPTION ? MAX_ENGINE_CONSUMPTION :
		consumption
	)
	{
		consumption_per_second = consumption * 3e-5;//3*10 в -5 степени
		is_started = false;
		cout << "Engine ready" << endl;
	}
	~Engine()
	{
		cout << "Engine is over" << endl;
	}
	void start()
	{
		is_started = true;
	}
	void stop()
	{
		is_started = false;
	}
	bool started()const
	{
		return is_started;
	}

	int get_consumption()const
	{
		return consumption;
	}
	double get_consumption_per_second()const
	{
		return consumption_per_second;
	}
	double get_consumption_per_second(int speed)
	{
		if (speed = 0)consumption_per_second = default_consumption_per_second * 20 / 3;
		else if (speed <= 60)consumption_per_second = default_consumption_per_second * 20 / 3;
		else if (speed <= 100)consumption_per_second = default_consumption_per_second * 48;
		else if (speed <= 140)consumption_per_second = default_consumption_per_second * 20 / 3;
		else if (speed <= 200)consumption_per_second = default_consumption_per_second * 8.33;
		else consumption_per_second = default_consumption_per_second * 10;
		return consumption_per_second;
	}

	void info() const
	{
		cout << "Consumption per 100 km:\t" << consumption << " liters.\n";
		cout << "Consumption per second:\t" << consumption_per_second << " liters.\n";
		cout << "Engine is " << (started() ? "started" : "stopped") << ".\n";
	}
};
#define MAX_SPEED_LOW_LIMIT 50
#define MAX_SPEED_HIGH_LIMIT 400

#define Enter 13
#define Escape 27

class Car
{
	Engine engine;
	Tank tank;
	bool driver_inside;
	int speed;
	const int MAX_SPEED;
	int accelleration = 10;
	struct//анонимная структура для панели
	{
		std::thread panel_thread;
		std::thread engine_idle;
		std::thread free_wheeling_thread;//движение по инерции

	}threads;//дали имя единственному объекту этой структуры
	const int MAX_SPEED;
public:
	Car(int engine_consumption, int tank_volume, int max_speed) :
		engine(engine_consumption),//агрегат
		tank(tank_volume),//агрегат вызывает конструкторы агрегаторов и соответственно 
		//создаются объекты
		MAX_SPEED(
			max_speed<MAX_SPEED_LOW_LIMIT ? MAX_SPEED_LOW_LIMIT :
			max_speed>MAX_SPEED_HIGH_LIMIT ? MAX_SPEED_HIGH_LIMIT :
			max_speed)
	{
		speed = 0;
		driver_inside = false;
		cout << "Your car is ready, press Enter to get in" << endl;
	}
	~Car()
	{
		cout << "Your car is over" << endl;
	}

	void get_in()//надо как то залазить и вылазить из машины
	{
		driver_inside = true;
		//panel(); //перегружаем панель приборов
		threads.panel_thread = std::thread(&Car::panel, this);//порождаем поток в котором будет выполнятся pfnel()
		//мы panel_thread прописали в defolt constractor в безымянной структуре поэтому 
	}
	void get_out()
	{
		driver_inside = false;
		if (threads.panel_thread.joinable())threads.panel_thread.join();
		cout << "You are out of your car" << endl;
	}
	void start()
	{
		if (driver_inside && tank.get_fuel_level())
		{
			engine.start();
			thread.engine_inle_thread = std::thread(&Car::engine_idle, this);
		}
	}
	void stop()
	{

		engine.start();
		if (threads.engine_idle_thread.joinable())threads.engine_idle_thread.join();

	}
	void accellerate()
	{
		if (driver_inside)
		{
			speed += accelleration;
			if (speed > MAX_ENGINE_CONSUMPTION)
				std::this_thread::sleep_for(1s);
			if (!threads.free_wheeling_thread.joinable())
				threads.free_wheeling_thread = std::thread(&Car::free_wheeling, this);
		}
	}
	void slow_down()
	{
		if (driver_inside)
		{
			speed -= accelleration;
			if (speed < 0)speed = 0;
			std::this_thread::sleep_for(1s);
			if (speed < 0)speed = 0;

		}
	}
	//основной метод который управляет машиной
	void control()
	{

		char key; //команда с клавиатуры
		do
		{
			if (_kbhit());//проверяет консольна предмет ввода с клавиатуры не 0 если была нажата клавиша иначе 0
			{key = _getch();//функция ожидает нажатия клавиши и возвращает ASCII код нажатой клавиши
			switch (key)
			{
			case Enter:
				if (driver_inside)get_out();
				else get_in();
				break;

			case 'F':case'f':
				if (driver_inside)
				{
					cout << "Для начала выйдите из машины" << endl;
				}
				double fuel;
				cout << "Введите объём топлива: "; cin >> fuel;
				tank.fill(fuel);
				break;
			case 'I':case'i'://Ignition
				!engine.started() ? start() : stop();
				break;
			case'W':case'w':case'72':
				accellerate();
			case'S':case's':case'75':
				accellerate();

			case Escape:
				get_out();
			}
			if (tank.get_fuel_level() == 0)stop();
			}
		} while (key != Escape);
	}
	void free_wheeling()
	{
		while (speed--)
		{
			if (speed < 0)speed = 0;
			engine.get_consumption_per_second();
		}
	}
	void engine_idle()
	{
		while (engine.started() && tank.give_fuel(engine.get_consumption_per_second()))
			std::this_thread;
	}
	void panel()
	{
		while (driver_inside)

		{
			system("CLS"); //чтобы обновлялось
			cout << "Speed:\t\t" << speed << "km/h.\n";
			cout << "Fuel level:\t" << tank.get_fuel_level() << " liters.\n";
			if (tank.get_fuel_level() <= 5)
			{
				HANDLE hConsole = GetSTDHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 0xCF);
				cout << "LOW FUEL";
				SetConsoleTextAttribute(hConsole, 0x07);
			}
			cout << endl;
			cout << "Engine " << (engine.started() ? "started" : "stopped") << endl;
			cout << "Consumption:\t" << (!engine.started()) << ;
			std::this_thread::sleep_for(1s);
		}
	}

	void info()const
	{
		engine.info();
		tank.info();
		cout << "Max speed:\t" << MAX_SPEED << "km/h.\n";
	}
};

//#define TANK_CHECK
//#define ENGINE_CHECK
void main()
{
	setlocale(0, "");
#ifdef TANK_CHECK
	//Tank tank(4);//выведет 20 литров в баке
//Tank tank(140);//выведет 100 литров в баке
	Tank tank(40);
	tank.info();
	int fuel;
	do {
		cout << "Введите уровень топлива: "; cin >> fuel;
		tank.fill(fuel);//заправим бак
		tank.info();
	} while (fuel);
#endif // TANK_CHECK
#ifdef ENGINE_CHECK
	Engine engine(8);
	engine.info();
#endif // ENGINE_CHECK
	Car mustang(10, 80, 250);
	mustang.control();

	}