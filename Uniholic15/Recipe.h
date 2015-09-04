#ifndef RECIPE_H
#define RECIPE_H


struct STEP {
	char temp;
	char time;
	//STEP(unsigned char temp, unsigned char time) : temp(temp), time(time) {};
};

struct HOP {
	char time;
};

class Recipe
{
public:
	Recipe();
	~Recipe();

	//Название рецепта
	const char* name;

	//Температура MashIn, °C
	char mashin;

	//Температурные паузы затирания
	STEP step[5];

	//Пролдолжительность варки
	char boil;

	//Массив внесения хмеля
	HOP hop[3];

};

#endif // RECIPE_H
