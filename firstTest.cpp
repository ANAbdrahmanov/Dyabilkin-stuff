#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <memory>

#define CARS_COUNT 10
#define MAX_POWER 1000


//1
class Car {
	//a
	int power;
	std::string model;

public:
	//k
	int getPower() {
		return power;
	}
	std::string getModel() {
		return model;
	}
	void setPower(int power) {
		this->power = power;
	}
	void setModel(std::string model) {
		this->model = model;
	}
	//b
	Car(const std::string& m)
		:model(m)
	{
	}
	//c
	Car(int p, const std::string& m)
		:power(p),
		model(m)
	{
	}
	//d???
	~Car() {}
	//e
	Car(const Car& c)
		:power(c.power),
		model(c.model)
	{
	}
	//f
	Car(Car&& c) 
		:power(c.power),
		model(std::move(model))
	{
		c.power = 0;
	}
	//g
	virtual Car* clone() const = 0; //наверн надо было не сырой указатель но переделывать уже поленился

	//h
	Car& operator=(const Car& c) {
		power = c.power;
		model = c.model;
		return *this;
	}
	Car& operator=(Car&& c) {
		power = c.power;
		c.power = 0;
		model = std::move(c.model);
		return *this;
	}
	//i
	bool operator==(const Car& c) {
		return (c.model == model) && (c.power == power);
	}

	bool operator!=(const Car& c) {
		return (c.model != model) && (c.power != power);
	}
	//j
	virtual void Drive() = 0;
};

//2
class Honda : public Car {
public:
	//a
	Honda(int p)
		:Car(p, "Honda")
	{
	}
	//b
	Honda* clone() const override {
		return new Honda(*this);
	}
	//c
	void Drive() {
		std::srand(unsigned(std::time(0)));
		std::cout << "Honda: " << (std::rand() % MAX_POWER) * getPower() << std::endl;
	}
};

//3
class Toyota : public Car {
//a
	int speed;
public:
//b
	Toyota(int p)
		:Car(p, "Toyota")
	{
		speed = (std::rand() % MAX_POWER) * p;
	}
//c
	Toyota* clone() const override {
		return new Toyota(*this);
	}
//d
	void Drive() {
		std::srand(unsigned(std::time(0)));
		speed += (std::rand() % MAX_POWER) * getPower();
		std::cout << "Toyota: " << speed << std::endl;
	}
};

//4
class Subaru : public Car{
public:
//a
	Subaru(int p)
		:Car(p, "Subaru")
	{
	}
//b
	Subaru* clone() const override {
		return new Subaru(*this);
	}
//c
	void Drive() {
		std::cout << "Subaru: I don't want to do something without good fuel" << std::endl;
	}
};

void Race(const std::vector<std::unique_ptr<Car>>& cars) {
	for (int i = 0; i < 5; i++) {
		std::cout << "Round " << i + 1 << std::endl;
		for (auto& car : cars) {
			car->Drive();
		}
	}
}

enum class carsEnum {  //наверн зря
	Honda = 0,
	Toyota,
	Subaru,
	MAX_CAR
};

int main() {
	std::vector<std::unique_ptr<Car>> cars;
	int randomSeed = unsigned(std::time(0));
	for (int i = 0; i < CARS_COUNT; i++) {
		std::srand(randomSeed);
		carsEnum carType = static_cast<carsEnum>(std::rand() % static_cast<int>(carsEnum::MAX_CAR));
		switch (carType) {
		case carsEnum::Honda:
			cars.push_back(std::make_unique<Honda>(randomSeed = std::rand() % MAX_POWER));
			break;
		case carsEnum::Toyota:
			cars.push_back(std::make_unique<Toyota>(randomSeed = std::rand() % MAX_POWER));
			break;
		case carsEnum::Subaru:
			cars.push_back(std::make_unique<Subaru>(randomSeed = std::rand() % MAX_POWER));
			break;
		}
	}
	Race(cars);
	std::cin.get();
	return 0;
}