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

    //создается поток файловый для чтения
    std::ifstream LoadedFile(("data/configs/" + className + ".dat").c_str());

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

                                //если первое слово в строке Animation
                                if (FirstWord == "Animation:")
                                {
                                    //если предыдущее слово name, то записываем слово во временную переменную
                                    if(PreviousWord == "name:")
                                        Animations.push_back(std::string(word));

                                }

                                //если первое слово в строке hitbox:
                                else if (FirstWord == "hitbox:")
                                {
                                    //если предыдущее слово x:, то записать параметр х
                                    if (PreviousWord == "x:")
                                        hitbox.x = rect.x*(static_cast<float>(atoi(word.c_str()))/100);

                                    //если предыдущее слово y:, то записать параметр y
                                    if (PreviousWord == "y:")
                                        hitbox.y = rect.y*(static_cast<float>(atoi(word.c_str()))/100);

                                    //если предыдущее слово w:, то записать параметр w
                                    if (PreviousWord == "w:")
                                        hitbox.w = rect.w*(static_cast<float>(atoi(word.c_str()))/100);

                                    //если предыдущее слово h:, то записать параметр h
                                    if (PreviousWord == "h:")
                                        hitbox.h = rect.h*(static_cast<float>(atoi(word.c_str()))/100);
                                }
                                //если предыдущее слово SetCrops:, то считать данные об обрезке на кадры картинки для спрайта
                                else if (PreviousWord == "Size:")
                                {
                                    rect.w = atoi(word.c_str());
                                    iss >> word;
                                    rect.h = atoi(word.c_str());
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
void Environment::changeXY(int X, int Y)
{
    PosX = X;
    PosY = Y;
    rect.x = X;
    rect.y = Y;

}
