#include "Environment.h"
Environment::Environment(std::string passed_className,
                        coordinates* passed_spawn,
                        int passed_ID,
                        int passed_PosX,
                        int passed_PosY)
{
    className = passed_className;
    ID = passed_ID;
    PosX = passed_PosX;
    PosY = passed_PosY;
    LoadConfigs();
    rect.x = passed_PosX;
    rect.y = passed_PosY;
}

Environment::~Environment(void)
{

}

void Environment::LoadConfigs(void)
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

                                //���� ������ ����� � ������ Animation
                                if (FirstWord == "Animation:")
                                {
                                    //���� ���������� ����� name, �� ���������� ����� �� ��������� ����������
                                    if(PreviousWord == "name:")
                                        Animations.push_back(std::string(word));

                                }

                                //���� ������ ����� � ������ hitbox:
                                else if (FirstWord == "hitbox:")
                                {
                                    //���� ���������� ����� x:, �� �������� �������� �
                                    if (PreviousWord == "x:")
                                        hitbox.x = rect.x*(static_cast<float>(atoi(word.c_str()))/100);

                                    //���� ���������� ����� y:, �� �������� �������� y
                                    if (PreviousWord == "y:")
                                        hitbox.y = rect.y*(static_cast<float>(atoi(word.c_str()))/100);

                                    //���� ���������� ����� w:, �� �������� �������� w
                                    if (PreviousWord == "w:")
                                        hitbox.w = rect.w*(static_cast<float>(atoi(word.c_str()))/100);

                                    //���� ���������� ����� h:, �� �������� �������� h
                                    if (PreviousWord == "h:")
                                        hitbox.h = rect.h*(static_cast<float>(atoi(word.c_str()))/100);
                                }
                                //���� ���������� ����� SetCrops:, �� ������� ������ �� ������� �� ����� �������� ��� �������
                                else if (PreviousWord == "Size:")
                                {
                                    rect.w = atoi(word.c_str());
                                    iss >> word;
                                    rect.h = atoi(word.c_str());
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
void Environment::changeXY(int X, int Y)
{
    PosX = X;
    PosY = Y;
    rect.x = X;
    rect.y = Y;

}
