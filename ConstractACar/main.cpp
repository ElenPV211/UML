#include<iostream>
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
	void fill(int fuel)  //заправка топлива
		//здесь важна инкапсуляция
	{
		if (fuel < 0)return;
		if (fuel_level + fuel > VOLUME)fuel_level = VOLUME;
		else fuel_level += fuel;
	}
	//-----Constractor
	Tank(int volume) :VOLUME(
		volume < MIN_TANK_VOLUME ? MIN_TANK_VOLUME ://после: выберается в противном случае
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
	
	void info() const
	{
		cout << "Consumption per 100 km:\t" << consumption << " liters.\n";
		cout << "Consumption per second:\t" << consumption_per_second << " liters.\n";
		cout << "Engine is " << (started() ? "started" : "stopped") << ".\n";
	}
};
#define MAX_SPEED_LOW_LIMIT 50
#define MAX_SPEED_HIGH_LIMIT 400
class Car
{
	Engine engine;
	Tank tank;
	int speed;
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
		cout << "Your car is ready, press Enter to get in" << endl;
	}
	~Car()
	{
		cout << "Your car is over" << endl;
	}
	void info()const
	{
		engine.info();
		tank.info();
		cout << "MAX speed:\t" << MAX_SPEED << "km/h.\n";
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
	mustang.info();
}