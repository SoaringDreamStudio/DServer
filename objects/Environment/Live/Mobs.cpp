#include "Mobs.h"

Mobs::Mobs(coordinates* passed_spawn,
                        int passed_ID,
                        int passed_PosX,
                        int passed_PosY
                        )
        : Live("Mobs",
                passed_spawn,
                passed_ID,
                passed_PosX,
                passed_PosY)
{
    LoadConfigs();
}

Mobs::~Mobs(void)
{

}

void Mobs::LoadConfigs(void)
{
    if(!(className != "Characters" ||
       className != "Ground" ||
       className != "Mobs" ||
       className != "Normal" ||
       className != "Trigger" ||
       className != "Wtrig" ))
        std::cout << "Class not detected" << std::endl << "Ur: " << className << std::endl;


    //��������� ����� �������� ��� ������
    std::ifstream LoadedFile(("data/configs/" + className).c_str());

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

                                //���� ���������� ����� fpX:, �� ������� �������������� �������� ��� �������
                                if (PreviousWord == "Aggressive:")
                                    Aggressive = bool(word.c_str());

                                //���� ������ ����� � ������ hitbox:
                                else if (FirstWord == "AgroRange:")
                                {
                                    //���� ���������� ����� x:, �� �������� �������� �
                                    if (PreviousWord == "x:")
                                        AgroRange.x = rect.x*(static_cast<float>(atoi(word.c_str()))/100);

                                    //���� ���������� ����� y:, �� �������� �������� y
                                    if (PreviousWord == "y:")
                                        AgroRange.y = rect.y*(static_cast<float>(atoi(word.c_str()))/100);

                                    //���� ���������� ����� w:, �� �������� �������� w
                                    if (PreviousWord == "w:")
                                        AgroRange.w = rect.w*(static_cast<float>(atoi(word.c_str()))/100);

                                    //���� ���������� ����� h:, �� �������� �������� h
                                    if (PreviousWord == "h:")
                                        AgroRange.h = rect.h*(static_cast<float>(atoi(word.c_str()))/100);
                                }



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
        std::cout << "File could not be open " << std::endl;
    }
}

