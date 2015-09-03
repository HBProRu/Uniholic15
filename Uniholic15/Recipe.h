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

	//Температура MashIn, °C
	float mashin;

	//Температурные паузы затирания
	STEP step[5];

	//MashOut
	STEP mashout;

	//Пролдолжительность варки
	int boil;

	//Массив внесения хмеля
	HOP hop[3];

};

#endif // RECIPE_H
