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
                                if (PreviousWord == "Aggressive:")
                                    Aggressive = bool(word.c_str());

                                //если первое слово в строке hitbox:
                                else if (FirstWord == "AgroRange:")
                                {
                                    //если предыдущее слово x:, то записать параметр х
                                    if (PreviousWord == "x:")
                                        AgroRange.x = rect.x*(static_cast<float>(atoi(word.c_str()))/100);

                                    //если предыдущее слово y:, то записать параметр y
                                    if (PreviousWord == "y:")
                                        AgroRange.y = rect.y*(static_cast<float>(atoi(word.c_str()))/100);

                                    //если предыдущее слово w:, то записать параметр w
                                    if (PreviousWord == "w:")
                                        AgroRange.w = rect.w*(static_cast<float>(atoi(word.c_str()))/100);

                                    //если предыдущее слово h:, то записать параметр h
                                    if (PreviousWord == "h:")
                                        AgroRange.h = rect.h*(static_cast<float>(atoi(word.c_str()))/100);
                                }



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

