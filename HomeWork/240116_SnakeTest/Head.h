#pragma once
#include "Part.h"
#include <list>
#include <vector>


class Head : public Part
{



protected:
	void Update() override;
	int2 ejPos;
	int2 FPos; // �����ּ�
	void Move();
	std::list<Part*> HeadNext;
	int2 RPos;
};

