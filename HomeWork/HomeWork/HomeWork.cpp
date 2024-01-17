

#include <iostream>
#include <consoleEngine/EngineDebug.h>

class IntArray
{
    // private: ����Ʈ �������� ������
public:
    // ����Ʈ ������
    IntArray(int _Size)
    {
        ReSize(_Size);
    }

    // ����Ʈ ���� ������
    IntArray(const IntArray& _Other)
    {
        Copy(_Other);

        //NumValue = _Other.NumValue;
        //ArrPtr = _Other.ArrPtr;
    }
    // ����Ʈ �Ҹ���
    ~IntArray()
    {
        Release();
    }
    // ����Ʈ ���Կ�����
    void operator=(const IntArray& _Other)
    {
        // ���ο� ī�Ƕ�� �θ��ϴ�.
        // �̰� ���� ������ �մϴ�.
        // ���� ���簡 �� ���� ����
        // ��û�� ���� �߻��ϴ� ��찡 �ִµ�.
        // ���� ���� => ���� <= �ƴϴ�.
        // ������ �����ϴ� ���縦 ���� ������ �մϴ�.
        // ArrPtr = _Other.ArrPtr;
        Copy(_Other);
    }

    int& operator[](int _Count)
    {
        return ArrPtr[_Count];
    }

    int Num()
    {
        return NumValue;
    }

    void Copy(const IntArray& _Other)
    {
        NumValue = _Other.NumValue;

        // ���� ���縦 ����� �մϴ�.
        ReSize(NumValue);
        for (int i = 0; i < NumValue; i++)
        {
            ArrPtr[i] = _Other.ArrPtr[i];
        }
    }

    void ReSize(int _Size)
    {
        if (0 >= _Size)
        {
            MsgBoxAssert("�迭�� ũ�Ⱑ 0�ϼ� �����ϴ�");
        }



        // ArrPtr [0][1][2][3][4]
        int* Ptr = ArrPtr;
        ArrPtr = new int[_Size];
        // ArrPtr [?][?][?][?][?][?][?][?][?][?]

        // Ptr    [0][1][2][3][4]
        // ArrPtr [?][?][?][?][?][?][?][?][?][?]


        for (int i = 0; i < NumValue; i++)
        {
            ArrPtr[i] = Ptr[i];
        }


        NumValue = _Size;

        if (nullptr != ArrPtr)
        {
            delete Ptr;
        }

    }

    void Release()
    {
        if (nullptr != ArrPtr)
        {
            delete[] ArrPtr;
            ArrPtr = nullptr;
        }
    }

private:
    int NumValue = 0;
    int* ArrPtr = nullptr;
};


int main()
{
    LeakCheck;
    IntArray NewArray = IntArray(5);
    // [?][?][?][?][?]

    for (int i = 0; i < NewArray.Num(); i++)
    {
        NewArray[i] = i;
    }
    // 1. �Ʒ��� ���� ����� ���������� �����ϰ�
    // 2. ���������� �Ʒ��� ���� ����� �ǵ��� ����ø� �˴ϴ�.
    // 3. ������ �����ϴ� ���� �����ϸ鼭 Ȯ���Ҽ� �ְ� ������.
    // 4. �������� �󸶵��� �׽�Ʈ�� �����Ҽ� �ִ�.
    // 5. �׽�Ʈ ���� �������� �����ϱ⿡ ���信 ����� ������� �����״� ������ �������.

    // �������� ���� �󸶵��� ����� �� �ִ�.

   // Resize�� NewArray�ּҰ����� �����ؾ��Ѵ�. 
   // ArrPtr�ּҰ��� Ptr�ּҰ����� �ű��


    NewArray.ReSize(10);



    // ?�� �������� �� �־ ������.
    // [0][1][2][3][4][?][?][?][?][?]

    for (size_t i = 0; i < NewArray.Num(); i++)
    {
        std::cout << NewArray[i] << std::endl;
    }


}
