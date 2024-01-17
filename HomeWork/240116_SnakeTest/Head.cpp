#include "Head.h"
#include <conio.h>
#include <ConsoleEngine/EngineCore.h>
#include "BodyManager.h"
#include "Body.h"

// 
// 1. 내가 특정 방향으로 진행했다면 다음 입력때는 그 반대방향으로는 갈수가 없다.
//    내가 이동하는 방향의 반대방향으로는 가면 안된다.
// 2. 내가 이동을 해서 CurBody를 획득했다면 그 다음부터 그 바디는 나를 따라와야 한다.

void Head::Move()
{
		std::list<Part*>::iterator Next = HeadNext.begin();
		std::list<Part*>::iterator Ending = HeadNext.end();
	
		int2 tmp;
		int2 tmpp;
		
	for (; Next != Ending; Next++)
	{
		if (Next != HeadNext.begin()) //		
		{
			tmpp = (*Next)->GetPos();
			(*Next)->SetPos(tmp);
			tmp = tmpp;
		}
		else if (Next == HeadNext.begin()) // 맨처음 몸통
		{
			tmp = (*Next)->GetPos();
			(*Next)->SetPos(RPos);
		}
	}
	
}






void Head::Update()
{
	int InputCount = _kbhit();
	if (0 == InputCount)
	{
		return;
	}

	int Select = _getch();

	// InputCount = _kbhit();

	// X Y
	// 1 0

	RPos = GetPos();

	switch (Select)
	{
	case 'A':
	case 'a':
		if (ejPos != Right) // 만약 ejPos가 오른쪽이 아니라면
		{
			AddPos(Left);   // AddPos(Left) 왼쪽으로
			ejPos = Left;   // ejPos는 왼쪽
		}
		break;
	case 'S':
	case 's':
		if (ejPos != Up)
		{
			AddPos(Down);
			ejPos = Down;
		}
		break;
	case 'W':
	case 'w':
		if (ejPos != Down)
		{
			AddPos(Up);
			ejPos = Up;
		}
		break;
	case 'D':
	case 'd':
		if (ejPos != Left)  // 만약 ejPos가 왼쪽이 아니라면
		{
			AddPos(Right);  // AddPos(Right) 오른쪽으로
			ejPos = Right;  // ejPos는 오른쪽
		}
		break;
	case '1':
		GetCore()->EngineEnd();
		break;
	default:
		break;
	}

	FPos = GetPos();

	if (nullptr == BodyManager::GetCurBody())
	{
		MsgBoxAssert("먹을수 있는 바디가 존재하지 않습니다.");
		return;
	}

	Body* CurBody = BodyManager::GetCurBody();

	if (CurBody->GetPos() == GetPos())
	{
		BodyManager::ResetBody();
		// CurBody가 RPos자리로 이동해야 한다.
		CurBody->SetPos(RPos);

		// CurBody의 Front(주소)가 Head의 Back(주소)의 연결되야한다.
		HeadNext.push_back(CurBody);
		
		
		Move();
	}
	else
	{
		Move();
	}
	


}


