#include "Objects.h"

Objects::Objects(std::string passed_className,
            coordinates* passed_spawn,
            int passed_ID,
            int passed_PosX,
            int passed_PosY)
    :NonLive(passed_className,
                passed_spawn,
                passed_ID,
                passed_PosX,
                passed_PosY)

{
    LoadConfigs();
}

Objects::~Objects(void)
{

}

void Objects::LoadConfigs(void)
{
    if(!(className != "Characters" ||
       className != "Ground" ||
       className != "Mobs" ||
       className != "Normal" ||
       className != "Trigger" ||
       className != "Wtrig" ))
        std::cout << "Class not detected" << std::endl << "Ur: " << className << std::endl;


    //��������� ����� �������� ��� ������
    std::ifstream LoadedFile(("data/configs/" + className + ".dat").c_str());

    //������������� ����������-������ ��� ������ ��������
    std::string line;

    //���� ���� ��� ������� ������
    if (LoadedFile.is_open())
    {
        //��������� �� ��� ���, ���� ��� ������
        while ( LoadedFile.good() )
        {
            //������� ������ �� �����
            std::getline(LoadedFile, line);

            //�������� � ����� ������ �� string
            std::istringstream iss(line);

            //�������� ��������� ����������
            std::string TempNameAnimation;
            int TempBeginFrame = 0;
            int TempEndFrame = 0;
            int TempRow = 0;
            int TempSpeed = 0;

            //���������� "���������� ����� � ������" � "������ ����� � ������"
            std::string PreviousWord;
            std::string FirstWord;

            //���� �� ������ �� �����������
            while (iss)
            {
                //������� �����
                std::string word;

                //������� ����� ����������� �� ������
                iss >> word;

                //���� ���������� ����� ID:
                if (PreviousWord == "ID:")
                {
                    //���� ���������� ID ������������� �������, �� ���������� �������� ����������
                    if (ID == atoi(word.c_str()))
                    {
                        //��������� ����� ������
                        std::getline(LoadedFile, line);

                        //�������� � ����� ������ �� string
                        std::istringstream iss(line);

                        //��������� ������ �� ��� ���, ���� �� �������� "-"
                        while(line != "-")
                        {
                            //��������� ����� ������
                            std::getline(LoadedFile, line);

                            //�������� � ����� ������ �� string
                            std::istringstream iss(line);

                            //���������� "������ ����� � ������"
                            FirstWord = "";

                            //���� �� ������ �� �����������
                            while(iss)
                            {
                                //������� ����� ����������� �� ������
                                iss >> word;

                                //���� ���������� ����� Collision:, �� ������� �������������� �������� ��� �������
                                if (PreviousWord == "Collision:")
                                    Collision = bool(word.c_str());

                                else if (PreviousWord == "BulletCollision:")
                                    BulletCollision = bool(word.c_str());



                                //���� ������ ����� ��� �� ���������, �� �������� ���
                                if(FirstWord.begin() == FirstWord.end())
                                    FirstWord = word;

                                //���������� ����� ���������� � ��������
                                PreviousWord = word;
                            }
                        }
                    }
                }
                //���������� ����� ���������� � ��������
                PreviousWord = word;
            }


        }
    }
    else // � ������ ������������� ������� ���� - ������ ������
    {
        std::cout << "File could not be open "<< std::endl;
    }
}
