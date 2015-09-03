#ifndef RECIPE_H
#define RECIPE_H

struct STEP {
	float temp;
	int time;
};

struct HOP {
	int time;
};

class Recipe
{
public:
	Recipe();
	~Recipe();

	//Название рецепта
	const char* name;

	//Температeра MashIn, градусы Цельсия
	float mashin;

	//Массив температурных пауз Затирания
	STEP step[5];

	//Температура MashOut, градусы Цельсия
	float mashout;

	//Продолжительность варки, минут
	int boil;

	//Массив вносов хмеля
	HOP hop[3];

};

#endif // RECIPE_H
