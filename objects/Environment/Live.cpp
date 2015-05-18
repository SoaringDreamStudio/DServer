#include "Live.h"

Live::Live(std::string passed_className,
            coordinates* passed_spawn,
            int passed_ID,
            int passed_PosX,
            int passed_PosY)
    :Environment(passed_className,
                passed_spawn,
                passed_ID,
                passed_PosX,
                passed_PosY)

{

}

Live::~Live(void)
{

}

void Live::LoadConfigs(void)
{
    if(!(className != "Characters" ||
       className != "Ground" ||
       className != "Mobs" ||
       className != "Normal" ||
       className != "Trigger" ||
       className != "Wtrig" ))
        std::cout << "Class not detected" << std::endl << "Ur: " << className << std::endl;


    //создается поток файловый для чтения
    std::ifstream LoadedFile(("data/configs/" + className).c_str());

    //инициализация переменной-строки для чтения конфигов
    std::string line;

    //если файл был успешно открыт
    if (LoadedFile.is_open())
    {
        //выполнять до тех пор, пока нет ошибок
        while ( LoadedFile.good() )
        {
            //считать строку из файла
            std::getline(LoadedFile, line);

            //добаляет в поток строку из string
            std::istringstream iss(line);

            //переменные "предыдущее слово в строке" и "первое слово в строке"
            std::string PreviousWord;
            std::string FirstWord;

            //пока не строка не закончилась
            while (iss)
            {
                //текущее слово
                std::string word;

                //текущее слово вставляется из потока
                iss >> word;


                //если предыдущее слово ID:
                if (PreviousWord == "ID:")
                {
                    //если написанный ID соответствует нужному, то начинается загрузка параметров
                    if (ID == atoi(word.c_str()))
                    {
                        //считываем новую строку
                        std::getline(LoadedFile, line);

                        //добаляет в поток строку из string
                        std::istringstream iss(line);

                        //считываем данные до тех пор, пока не встретим "-"
                        while(line != "-")
                        {
                            //считываем новую строку
                            std::getline(LoadedFile, line);

                            //добаляет в поток строку из string
                            std::istringstream iss(line);

                            //сбрасываем "первое слово в строке"
                            FirstWord = "";

                            //пока не строка не закончилась
                            while(iss)
                            {
                                //текущее слово вставляется из потока
                                iss >> word;

                                //если предыдущее слово fpX:, то считать местоположение картинки для спрайта
                                if (PreviousWord == "fpX:")
                                    fpX = int(word.c_str());

                                else if (PreviousWord == "fpY:")
                                    fpY = int(word.c_str());
                                else if (PreviousWord == "HP:")
                                    HP = int(word.c_str());
                                else if (PreviousWord == "MS:")
                                    MS = int(word.c_str());
                                else if (PreviousWord == "Range:")
                                    Range = int(word.c_str());
                                else if (PreviousWord == "AttackDmg:")
                                    AttackDmg = int(word.c_str());
                                else if (PreviousWord == "Defense:")
                                    Defense = int(word.c_str());
                                else if (PreviousWord == "AttackCDTime:")
                                    AttackCDTime = int(word.c_str());
                                else if (PreviousWord == "AttackAnimationTime:")
                                    AttackAnimationTime = int(word.c_str());


                                //если первое слово еще не заполнено, то записать его
                                if(FirstWord.begin() == FirstWord.end())
                                    FirstWord = word;

                                //предыдущее слово приравнять к текущему
                                PreviousWord = word;
                            }
                        }
                    }
                }
                //предыдущее слово приравнять к текущему
                PreviousWord = word;
            }


        }
    }
    else // в случае невозможности открыть файл - выдать ошибку
    {
        std::cout << "File could not be open " << std::endl;
    }
}
