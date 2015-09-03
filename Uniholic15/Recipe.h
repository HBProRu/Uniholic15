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

	//�������� �������
	const char* name;

	//��������e�� MashIn, ������� �������
	float mashin;

	//������ ������������� ���� ���������
	STEP step[5];

	//����������� MashOut, ������� �������
	float mashout;

	//����������������� �����, �����
	int boil;

	//������ ������ �����
	HOP hop[3];

};

#endif // RECIPE_H
