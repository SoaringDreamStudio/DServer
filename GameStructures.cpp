#include "GameStructures.h"

gameObject::gameObject(std::string Passed_ClassName, int passed_ID, int *passed_MouseX, int *passed_MouseY,  int X, int Y, int W, int H, float *passed_CameraX, float *passed_CameraY, CSDL_Setup* passed_csdl_setup, coordinates* passed_spawn)
{
    csdl_setup = passed_csdl_setup;
    spawn = passed_spawn;
    ID = passed_ID;
    Rect.x = X;
    Rect.y = Y;
    Rect.w = W;
    Rect.h = H;
    invisible = true;
    ClassName = Passed_ClassName;
    FilePath = "data/configs/objects.dat";
	speed = 3;
	Follow = false;
	distance = 0;
	timeCheckMoving = SDL_GetTicks();
    LoadConfigs();
	Follow_Point_X = *MouseX - *CameraX - 110;
    Follow_Point_Y = *MouseY - *CameraY - 65;

}

gameObject::~gameObject(void)
{

}

void gameObject::LoadConfigs()
{
    //создается поток файловый для чтения
    std::ifstream LoadedFile(FilePath.c_str());

    //инициализация переменной-строки для чтения конфигов
    std::string line;

    //инициализация типа эффекта (осталось от чтения конфигов для игрового уровня)
    int CurrentType = TypeNone;

    //если файл был успешно открыт
    if (LoadedFile.is_open())
    {
        //выполнять до тех пор, пока нет ошибок
        while ( LoadedFile.good() )
        {
            //считать строку из файла
            std::getline(LoadedFile, line);

            //если линия соответствует названию класса
            if (line == ClassName)
            {
                //если класс gameItem, то установать его как текущий тип для считывания
                if(ClassName == "gameItem")
                    CurrentType = TypeItem;

                //если класс gameGround, то установать его как текущий тип для считывания
                if(ClassName == "gameGround")
                    CurrentType = TypeGround;

                //если класс gameWater, то установать его как текущий тип для считывания
                if(ClassName == "gameWater")
                    CurrentType = TypeWater;

                //если класс gameAbilityItem, то установать его как текущий тип для считывания
                if(ClassName == "gameAbilityItem")
                    CurrentType = TypeAbilityItem;

                if(ClassName == "gameFood")
                    CurrentType = TypeFood;
            }

            //если линия end, то сбросить текущий тип
            else if (line == "end")
            {
                CurrentType = TypeNone;
            }

            //в других случаях
            else
            {
                //если текущий тип не пустой
                if(CurrentType != TypeNone)
                {
                    //добаляет в поток строку из string
                    std::istringstream iss(line);

                    //создание временных переменных
                    std::string TempNameAnimation;
                    int TempBeginFrame = 0;
                    int TempEndFrame = 0;
                    int TempRow = 0;
                    int TempSpeed = 0;

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
                                                TempNameAnimation = word;

                                            //если предыдущее слово parameters
                                            if(PreviousWord == "parameters:")
                                            {
                                                //считываем номер начального кадра
                                                TempBeginFrame = atoi(word.c_str());

                                                //сдвигаемся на слово
                                                iss >> word;

                                                //считываем номер последнего кадра
                                                TempEndFrame = atoi(word.c_str());

                                                //сдвигаемся на слово
                                                iss >> word;

                                                //считываем номер ряда для кадров
                                                TempRow = atoi(word.c_str());

                                                //сдвигаемся на слово
                                                iss >> word;

                                                //считываем скорость анимации
                                                TempSpeed = atoi(word.c_str());

                                                //создаем переменную с информацией по анимации
                                                AnimationInfo tmpAI;

                                                //записываем считанные данные в переменную
                                                tmpAI.BeginFrame = TempBeginFrame;
                                                tmpAI.EndFrame = TempEndFrame;
                                                tmpAI.Row = TempRow;
                                                tmpAI.Speed = TempSpeed;

                                                //добавить данные о анимации в map анимаций
                                                animations[TempNameAnimation] = tmpAI;
                                            }
                                        }

                                        //если первое слово в строке hitbox:
                                        else if (FirstWord == "hitbox:")
                                        {
                                            //если предыдущее слово x:, то записать параметр х
                                            if (PreviousWord == "x:")
                                                hitbox.x = Rect.x*(static_cast<float>(atoi(word.c_str()))/100);

                                            //если предыдущее слово y:, то записать параметр y
                                            if (PreviousWord == "y:")
                                                hitbox.y = Rect.y*(static_cast<float>(atoi(word.c_str()))/100);

                                            //если предыдущее слово w:, то записать параметр w
                                            if (PreviousWord == "w:")
                                                hitbox.w = Rect.w*(static_cast<float>(atoi(word.c_str()))/100);

                                            //если предыдущее слово h:, то записать параметр h
                                            if (PreviousWord == "h:")
                                                hitbox.h = Rect.h*(static_cast<float>(atoi(word.c_str()))/100);
                                        }

                                        //если первое слово в строке effects:
                                        else if (FirstWord == "effects:")
                                        {
                                            //создать временную переменную
                                            EffectInfo tempEffectInfo;

                                            //если предыдущее слово ID:
                                            if (PreviousWord == "ID:")
                                            {
                                                //инициализируем временную переменную tempID
                                                int tempID = atoi(word.c_str());

                                                //сдвигаемся на слово
                                                iss >> word;

                                                //предыдущее слово приравнять к текущему
                                                PreviousWord = word;

                                                //сдвигаемся на слово
                                                iss >> word;

                                                //если предыдущее слово Time:
                                                if (PreviousWord == "Time:")
                                                {
                                                    //инициализируем переменную tempTime
                                                    int tempTime = atoi(word.c_str());

                                                    //добавляем считанный эффект в список связанных с этим объектом эффектов
                                                    effects.push_back(new EffectInfo(tempID,tempTime,this));
                                                }
                                            }
                                        }

                                        //если предыдущее слово name:, то считать название объекта
                                        else if (PreviousWord == "name:")
                                            ObjectName = word;

                                        //если предыдущее слово Follow:, то считать: преследует ли какую-либо точку объект
                                        else if (PreviousWord == "Follow:")
                                        {
                                            if(word == "Off")
                                                Follow = false;
                                            if(word == "On")
                                                Follow = true;
                                        }

                                        //если предыдущее слово FilePathSprite:, то считать местоположение картинки для спрайта
                                        else if (PreviousWord == "FilePathSprite:")
                                            FilePathSprite = word;

                                        //если предыдущее слово SetCrops:, то считать данные об обрезке на кадры картинки для спрайта
                                        else if (PreviousWord == "SetCrops:")
                                        {
                                            SpriteCropX = atoi(word.c_str());
                                            iss >> word;
                                            SpriteCropY = atoi(word.c_str());
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
        }
    }
    else // в случае невозможности открыть файл - выдать ошибку
    {
        std::cout << "File could not be open: " + FilePath << std::endl;
    }
}

void gameObject::Draw()
{
    //if(invisible)

    //проверка каждые 0,05 секунд и если объект идет к какой-то точке
    if (timeCheckMoving+50 < SDL_GetTicks() && Follow)
    {
        //рассчитать дистанцию
        distance = GetDistance(sprite->GetX(), sprite->GetY(), Follow_Point_X, Follow_Point_Y);

        //если дистанция больше 1
        if (distance > 1)
        {
            //если спрайт не достиг цели по х-координатам, то переместить его
            if (sprite->GetX() != Follow_Point_X)
                sprite->SetX(sprite->GetX() - (((sprite->GetX() - Follow_Point_X) / distance) * 1.0 )*speed);

            //если спрайт не достиг цели по y-координатам, то переместить его
            if (sprite->GetY() != Follow_Point_Y)
                sprite->SetY(sprite->GetY() - (((sprite->GetY() - Follow_Point_Y) / distance) * 1.0 )*speed);
        }

        // если объект достиг своей цели, отключить преследование
        else
            Follow = false;

        //тик таймера
        timeCheckMoving = SDL_GetTicks();
    }

    //если список анимаций объекта не пустой и есть обрезка на кадры - установить стандартную анимацию (an1)
    if( animations.size() != 0 && SpriteCropX > 0 && SpriteCropY > 0)
        sprite->PlayAnimation(animations["an1"].BeginFrame, animations["an1"].EndFrame, animations["an1"].Row, animations["an1"].Speed);

    //отрисовать объект
    sprite->DrawWithCoord(csdl_setup, *spawn);
}

double gameObject::GetDistance(int X1, int Y1, int X2, int Y2)
{
	double DifferenceX = X1 - X2;
	double DifferenceY = Y1 - Y2;
	double distance = sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
	return distance;
}

void gameGround::Draw()
{
    sprite->DrawWithCoord(csdl_setup, *spawn);
}

void gameAbilityItem::update()
{
    //первые секунды создания объекта он невидим
    if( timeCreate+(GetDistance(sprite->GetX(), sprite->GetY(), sprite->GetX()+64, sprite->GetY()+50)/speed) > SDL_GetTicks() )
    {
        //установить активную анимацию creating
        activeAnimation = "creating";

        //каждые 0,05 секунд если есть пункт назначения и активная анимация не dead
        if (timeCheckMoving+50 < SDL_GetTicks() && Follow && activeAnimation != "dead")
        {
            //просчет дистанции
            distance = GetDistance(sprite->GetX(), sprite->GetY(), Follow_Point_X, Follow_Point_Y);

            //если объект не достиг точки назначения
            if (distance > 1)
            {
                //если спрайт не достиг пункта назначения по оси Х, то сдвинуть
                if (sprite->GetX() != Follow_Point_X)
                {
                    sprite->SetX(sprite->GetX() - (((sprite->GetX() - Follow_Point_X) / distance) * 1.0 )*speed);
                }

                //если спрайт не достиг пункта назначения по оси У, то сдвинуть
                if (sprite->GetY() != Follow_Point_Y)
                {
                    sprite->SetY(sprite->GetY() - (((sprite->GetY() - Follow_Point_Y) / distance) * 1.0 )*speed);
                }
            }

            //если объект достиг точки назначения
            else
            {
                //триггер преследования - OFF
                Follow = false;
            }

            //тик таймера
            timeCheckMoving = SDL_GetTicks();
        }

        //тик таймера
        lifeTimer = SDL_GetTicks();

        //обновить анимацию
        updateAnimation();
    }
    else //если объект уже прошел стадию "невидимости"
    {
        if (timeCheckMoving+50 < SDL_GetTicks() && Follow && activeAnimation != "dead")
        {
            //просчет дистанции
            distance = GetDistance(sprite->GetX(), sprite->GetY(), Follow_Point_X, Follow_Point_Y);
            //если объект не достиг точки назначения
            if (distance > 1)
            {
                //если спрайт не достиг пункта назначения по оси Х, то сдвинуть
                if (sprite->GetX() != Follow_Point_X)
                {
                    sprite->SetX(sprite->GetX() - (((sprite->GetX() - Follow_Point_X) / distance) * 1.0 )*speed);
                }

                //если спрайт не достиг пункта назначения по оси Х, то сдвинуть
                if (sprite->GetY() != Follow_Point_Y)
                {
                    sprite->SetY(sprite->GetY() - (((sprite->GetY() - Follow_Point_Y) / distance) * 1.0 )*speed);
                }
            }

            //если объект достиг точки назначения
            else
            {
                //триггер преследования - OFF
                Follow = false;
            }

            //тик таймера
            timeCheckMoving = SDL_GetTicks();
        }

        //тик таймера времени жизни объекта
        lifeTime -= SDL_GetTicks() - lifeTimer;

        //если время жизни объекта еще не вышло и он двигается по направлению к пункту назначения - проиграть анимацию an1
        if (lifeTime > 0 && Follow)
            activeAnimation = "an1";

        //если время жизни закончилось или объект достиг пункта назначения
        else if (lifeTime <= 0 || !Follow)
        {
            //если время жизни больше нуля, то сбросить
            if(lifeTime > 0)
                lifeTime = 0;

            //текущая анимация dead
            activeAnimation = "dead";

            //если анимация смерти проигралась, то триггер самоуничтожения объекта - ON
            if(lifeTime <= 0 - ((animations["dead"].EndFrame - animations["dead"].BeginFrame) * animations["dead"].Speed))
                plsDestroyMe = true;
        }

        //тик таймера жизни объекта
        lifeTimer = SDL_GetTicks();

        //обновить анимацию
        updateAnimation();
    }
}

void gameAbilityItem::updateAnimation() //обновить анимацию
{
    sprite->PlayAnimation(animations[activeAnimation].BeginFrame, animations[activeAnimation].EndFrame, animations[activeAnimation].Row, animations[activeAnimation].Speed);
}

void gameAbilityItem::Draw() //отрисовать
{
    update();
    sprite->DrawWithCoord(csdl_setup, *spawn);
}

void gameAbilityItem::LoadAnimations() //прогрузить анимации для объекта
{
    //создается поток файловый для чтения
    std::ifstream LoadedFile(FilePath.c_str());

    //инициализация переменной-строки для чтения конфигов
    std::string line;

    //инициализация типа объекта
    int CurrentType = TypeNone;

    //если файл был успешно открыт
    if (LoadedFile.is_open())
    {
        //выполнять до тех пор, пока нет ошибок
        while ( LoadedFile.good() )
        {
            //считать строку из файла
            std::getline(LoadedFile, line);

            //если линия соответствует названию класса объекта
            if (line == ClassName)
            {
                //если название класса gameItem, то зафиксировать это
                if(ClassName == "gameItem")
                    CurrentType = TypeItem;

                //если название класса gameGround, то зафиксировать это
                if(ClassName == "gameGround")
                    CurrentType = TypeGround;

                //если название класса gameWater, то зафиксировать это
                if(ClassName == "gameWater")
                    CurrentType = TypeWater;

                //если название класса gameAbilityItem, то зафиксировать это
                if(ClassName == "gameAbilityItem")
                    CurrentType = TypeAbilityItem;
            }

            //если строчка end - сбросить текущий тип
            else if (line == "end")
                CurrentType = TypeNone;

            //в других случаях
            else
            {
                //если текущий тип TypeAbilityItem
                if(CurrentType == TypeAbilityItem)
                {
                    //добаляет в поток строку из string
                    std::istringstream iss(line);

                    //создание временных переменных
                    std::string TempNameAnimation;
                    int TempBeginFrame = 0;
                    int TempEndFrame = 0;
                    int TempRow = 0;
                    int TempSpeed = 0;

                    //создание переменный "прошлое слово в строке" и "первое слово в строке"
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
                                            //???
                                            bool effects = false;

                                            //если предыдущее слово name, то записываем слово во временную переменную
                                            if(PreviousWord == "name:")
                                                TempNameAnimation = word;

                                            //если предыдущее слово parameters
                                            if(PreviousWord == "parameters:")
                                            {
                                                //считываем номер начального кадра
                                                TempBeginFrame = atoi(word.c_str());

                                                //сдвигаемся на слово
                                                iss >> word;

                                                //считываем номер последнего кадра
                                                TempEndFrame = atoi(word.c_str());

                                                //сдвигаемся на слово
                                                iss >> word;

                                                //считываем номер ряда для кадров
                                                TempRow = atoi(word.c_str());

                                                //сдвигаемся на слово
                                                iss >> word;

                                                //считываем скорость анимации
                                                TempSpeed = atoi(word.c_str());

                                                //создаем переменную с информацией по анимации
                                                AnimationInfo tmpAI;

                                                //записываем считанные данные в переменную
                                                tmpAI.BeginFrame = TempBeginFrame;
                                                tmpAI.EndFrame = TempEndFrame;
                                                tmpAI.Row = TempRow;
                                                tmpAI.Speed = TempSpeed;

                                                //добавить данные о анимации в map анимаций
                                                animations[TempNameAnimation] = tmpAI;

                                                //сдвигаемся на слово
                                                iss >> word;

                                                //если первое слово в строке effects:
                                                if(word == "effects:")
                                                {
                                                    //сдвигаемся на слово
                                                    iss >> word;

                                                    //создать временную переменную
                                                    std::vector<EffectInfo*> tempEffectInfo;

                                                    //если предыдущее слово ID:
                                                    if (PreviousWord == "ID:")
                                                    {
                                                        //инициализируем временную переменную tempID
                                                        int tempID = atoi(word.c_str());

                                                        //сдвигаемся на слово
                                                        iss >> word;

                                                        //предыдущее слово приравнять к текущему
                                                        PreviousWord = word;

                                                        //сдвигаемся на слово
                                                        iss >> word;

                                                        //если предыдущее слово Time:
                                                        if (PreviousWord == "Time:")
                                                        {
                                                            //инициализируем переменную tempTime
                                                            int tempTime = atoi(word.c_str());

                                                            //добавляем считанный эффект в список связанных с этим объектом эффектов
                                                            tempEffectInfo.push_back(new EffectInfo(tempID,tempTime,this));

                                                        }
                                                    }
                                                    //добавить данные о анимации в map анимаций
                                                    animationEffects[TempNameAnimation] = tempEffectInfo;
                                                }
                                            }
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
        }
    }
    else //в случае ошибки
    {
        std::cout << "File could not be open: " + FilePath << std::endl;
    }
}

void gameFood::LoadConfigs()
{
    //создается поток файловый для чтения
    std::ifstream LoadedFile(FilePath.c_str());

    //инициализация переменной-строки для чтения конфигов
    std::string line;

    //инициализация типа эффекта (осталось от чтения конфигов для игрового уровня)
    int CurrentType = TypeNone;

    //если файл был успешно открыт
    if (LoadedFile.is_open())
    {
        //выполнять до тех пор, пока нет ошибок
        while ( LoadedFile.good() )
        {
            //считать строку из файла
            std::getline(LoadedFile, line);

            //если линия соответствует названию класса
            if (line == ClassName)
            {
                if(ClassName == "gameFood")
                    CurrentType = TypeFood;
            }

            //если линия end, то сбросить текущий тип
            else if (line == "end")
            {
                CurrentType = TypeNone;
            }

            //в других случаях
            else
            {
                //если текущий тип не пустой
                if(CurrentType != TypeNone)
                {
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

                                        if(PreviousWord == "Protein:")
                                        {
                                            Protein = atoi(word.c_str());
                                        }
                                        if(PreviousWord == "Carbohydrate:")
                                        {
                                            Carbohydrate = atoi(word.c_str());

                                        }
                                        if(PreviousWord == "Fat:")
                                        {
                                            Fat = atoi(word.c_str());

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
        }
    }
    else // в случае невозможности открыть файл - выдать ошибку
    {
        std::cout << "File could not be open: " + FilePath << std::endl;
    }
}
