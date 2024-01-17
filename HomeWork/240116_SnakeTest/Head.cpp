#include "Head.h"
#include <conio.h>
#include <ConsoleEngine/EngineCore.h>
#include "BodyManager.h"
#include "Body.h"

// 
// 1. ���� Ư�� �������� �����ߴٸ� ���� �Է¶��� �� �ݴ�������δ� ������ ����.
//    ���� �̵��ϴ� ������ �ݴ�������δ� ���� �ȵȴ�.
// 2. ���� �̵��� �ؼ� CurBody�� ȹ���ߴٸ� �� �������� �� �ٵ�� ���� ����;� �Ѵ�.

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
		else if (Next == HeadNext.begin()) // ��ó�� ����
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
		if (ejPos != Right) // ���� ejPos�� �������� �ƴ϶��
		{
			AddPos(Left);   // AddPos(Left) ��������
			ejPos = Left;   // ejPos�� ����
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
		if (ejPos != Left)  // ���� ejPos�� ������ �ƴ϶��
		{
			AddPos(Right);  // AddPos(Right) ����������
			ejPos = Right;  // ejPos�� ������
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
		MsgBoxAssert("������ �ִ� �ٵ� �������� �ʽ��ϴ�.");
		return;
	}

	Body* CurBody = BodyManager::GetCurBody();

	if (CurBody->GetPos() == GetPos())
	{
		BodyManager::ResetBody();
		// CurBody�� RPos�ڸ��� �̵��ؾ� �Ѵ�.
		CurBody->SetPos(RPos);

		// CurBody�� Front(�ּ�)�� Head�� Back(�ּ�)�� ����Ǿ��Ѵ�.
		HeadNext.push_back(CurBody);
		
		
		Move();
	}
	else
	{
		Move();
	}
	


}


