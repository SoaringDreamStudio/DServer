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
    //��������� ����� �������� ��� ������
    std::ifstream LoadedFile(FilePath.c_str());

    //������������� ����������-������ ��� ������ ��������
    std::string line;

    //������������� ���� ������� (�������� �� ������ �������� ��� �������� ������)
    int CurrentType = TypeNone;

    //���� ���� ��� ������� ������
    if (LoadedFile.is_open())
    {
        //��������� �� ��� ���, ���� ��� ������
        while ( LoadedFile.good() )
        {
            //������� ������ �� �����
            std::getline(LoadedFile, line);

            //���� ����� ������������� �������� ������
            if (line == ClassName)
            {
                //���� ����� gameItem, �� ���������� ��� ��� ������� ��� ��� ����������
                if(ClassName == "gameItem")
                    CurrentType = TypeItem;

                //���� ����� gameGround, �� ���������� ��� ��� ������� ��� ��� ����������
                if(ClassName == "gameGround")
                    CurrentType = TypeGround;

                //���� ����� gameWater, �� ���������� ��� ��� ������� ��� ��� ����������
                if(ClassName == "gameWater")
                    CurrentType = TypeWater;

                //���� ����� gameAbilityItem, �� ���������� ��� ��� ������� ��� ��� ����������
                if(ClassName == "gameAbilityItem")
                    CurrentType = TypeAbilityItem;

                if(ClassName == "gameFood")
                    CurrentType = TypeFood;
            }

            //���� ����� end, �� �������� ������� ���
            else if (line == "end")
            {
                CurrentType = TypeNone;
            }

            //� ������ �������
            else
            {
                //���� ������� ��� �� ������
                if(CurrentType != TypeNone)
                {
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

                                        //���� ������ ����� � ������ Animation
                                        if (FirstWord == "Animation:")
                                        {
                                            //���� ���������� ����� name, �� ���������� ����� �� ��������� ����������
                                            if(PreviousWord == "name:")
                                                TempNameAnimation = word;

                                            //���� ���������� ����� parameters
                                            if(PreviousWord == "parameters:")
                                            {
                                                //��������� ����� ���������� �����
                                                TempBeginFrame = atoi(word.c_str());

                                                //���������� �� �����
                                                iss >> word;

                                                //��������� ����� ���������� �����
                                                TempEndFrame = atoi(word.c_str());

                                                //���������� �� �����
                                                iss >> word;

                                                //��������� ����� ���� ��� ������
                                                TempRow = atoi(word.c_str());

                                                //���������� �� �����
                                                iss >> word;

                                                //��������� �������� ��������
                                                TempSpeed = atoi(word.c_str());

                                                //������� ���������� � ����������� �� ��������
                                                AnimationInfo tmpAI;

                                                //���������� ��������� ������ � ����������
                                                tmpAI.BeginFrame = TempBeginFrame;
                                                tmpAI.EndFrame = TempEndFrame;
                                                tmpAI.Row = TempRow;
                                                tmpAI.Speed = TempSpeed;

                                                //�������� ������ � �������� � map ��������
                                                animations[TempNameAnimation] = tmpAI;
                                            }
                                        }

                                        //���� ������ ����� � ������ hitbox:
                                        else if (FirstWord == "hitbox:")
                                        {
                                            //���� ���������� ����� x:, �� �������� �������� �
                                            if (PreviousWord == "x:")
                                                hitbox.x = Rect.x*(static_cast<float>(atoi(word.c_str()))/100);

                                            //���� ���������� ����� y:, �� �������� �������� y
                                            if (PreviousWord == "y:")
                                                hitbox.y = Rect.y*(static_cast<float>(atoi(word.c_str()))/100);

                                            //���� ���������� ����� w:, �� �������� �������� w
                                            if (PreviousWord == "w:")
                                                hitbox.w = Rect.w*(static_cast<float>(atoi(word.c_str()))/100);

                                            //���� ���������� ����� h:, �� �������� �������� h
                                            if (PreviousWord == "h:")
                                                hitbox.h = Rect.h*(static_cast<float>(atoi(word.c_str()))/100);
                                        }

                                        //���� ������ ����� � ������ effects:
                                        else if (FirstWord == "effects:")
                                        {
                                            //������� ��������� ����������
                                            EffectInfo tempEffectInfo;

                                            //���� ���������� ����� ID:
                                            if (PreviousWord == "ID:")
                                            {
                                                //�������������� ��������� ���������� tempID
                                                int tempID = atoi(word.c_str());

                                                //���������� �� �����
                                                iss >> word;

                                                //���������� ����� ���������� � ��������
                                                PreviousWord = word;

                                                //���������� �� �����
                                                iss >> word;

                                                //���� ���������� ����� Time:
                                                if (PreviousWord == "Time:")
                                                {
                                                    //�������������� ���������� tempTime
                                                    int tempTime = atoi(word.c_str());

                                                    //��������� ��������� ������ � ������ ��������� � ���� �������� ��������
                                                    effects.push_back(new EffectInfo(tempID,tempTime,this));
                                                }
                                            }
                                        }

                                        //���� ���������� ����� name:, �� ������� �������� �������
                                        else if (PreviousWord == "name:")
                                            ObjectName = word;

                                        //���� ���������� ����� Follow:, �� �������: ���������� �� �����-���� ����� ������
                                        else if (PreviousWord == "Follow:")
                                        {
                                            if(word == "Off")
                                                Follow = false;
                                            if(word == "On")
                                                Follow = true;
                                        }

                                        //���� ���������� ����� FilePathSprite:, �� ������� �������������� �������� ��� �������
                                        else if (PreviousWord == "FilePathSprite:")
                                            FilePathSprite = word;

                                        //���� ���������� ����� SetCrops:, �� ������� ������ �� ������� �� ����� �������� ��� �������
                                        else if (PreviousWord == "SetCrops:")
                                        {
                                            SpriteCropX = atoi(word.c_str());
                                            iss >> word;
                                            SpriteCropY = atoi(word.c_str());
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
        }
    }
    else // � ������ ������������� ������� ���� - ������ ������
    {
        std::cout << "File could not be open: " + FilePath << std::endl;
    }
}

void gameObject::Draw()
{
    //if(invisible)

    //�������� ������ 0,05 ������ � ���� ������ ���� � �����-�� �����
    if (timeCheckMoving+50 < SDL_GetTicks() && Follow)
    {
        //���������� ���������
        distance = GetDistance(sprite->GetX(), sprite->GetY(), Follow_Point_X, Follow_Point_Y);

        //���� ��������� ������ 1
        if (distance > 1)
        {
            //���� ������ �� ������ ���� �� �-�����������, �� ����������� ���
            if (sprite->GetX() != Follow_Point_X)
                sprite->SetX(sprite->GetX() - (((sprite->GetX() - Follow_Point_X) / distance) * 1.0 )*speed);

            //���� ������ �� ������ ���� �� y-�����������, �� ����������� ���
            if (sprite->GetY() != Follow_Point_Y)
                sprite->SetY(sprite->GetY() - (((sprite->GetY() - Follow_Point_Y) / distance) * 1.0 )*speed);
        }

        // ���� ������ ������ ����� ����, ��������� �������������
        else
            Follow = false;

        //��� �������
        timeCheckMoving = SDL_GetTicks();
    }

    //���� ������ �������� ������� �� ������ � ���� ������� �� ����� - ���������� ����������� �������� (an1)
    if( animations.size() != 0 && SpriteCropX > 0 && SpriteCropY > 0)
        sprite->PlayAnimation(animations["an1"].BeginFrame, animations["an1"].EndFrame, animations["an1"].Row, animations["an1"].Speed);

    //���������� ������
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
    //������ ������� �������� ������� �� �������
    if( timeCreate+(GetDistance(sprite->GetX(), sprite->GetY(), sprite->GetX()+64, sprite->GetY()+50)/speed) > SDL_GetTicks() )
    {
        //���������� �������� �������� creating
        activeAnimation = "creating";

        //������ 0,05 ������ ���� ���� ����� ���������� � �������� �������� �� dead
        if (timeCheckMoving+50 < SDL_GetTicks() && Follow && activeAnimation != "dead")
        {
            //������� ���������
            distance = GetDistance(sprite->GetX(), sprite->GetY(), Follow_Point_X, Follow_Point_Y);

            //���� ������ �� ������ ����� ����������
            if (distance > 1)
            {
                //���� ������ �� ������ ������ ���������� �� ��� �, �� ��������
                if (sprite->GetX() != Follow_Point_X)
                {
                    sprite->SetX(sprite->GetX() - (((sprite->GetX() - Follow_Point_X) / distance) * 1.0 )*speed);
                }

                //���� ������ �� ������ ������ ���������� �� ��� �, �� ��������
                if (sprite->GetY() != Follow_Point_Y)
                {
                    sprite->SetY(sprite->GetY() - (((sprite->GetY() - Follow_Point_Y) / distance) * 1.0 )*speed);
                }
            }

            //���� ������ ������ ����� ����������
            else
            {
                //������� ������������� - OFF
                Follow = false;
            }

            //��� �������
            timeCheckMoving = SDL_GetTicks();
        }

        //��� �������
        lifeTimer = SDL_GetTicks();

        //�������� ��������
        updateAnimation();
    }
    else //���� ������ ��� ������ ������ "�����������"
    {
        if (timeCheckMoving+50 < SDL_GetTicks() && Follow && activeAnimation != "dead")
        {
            //������� ���������
            distance = GetDistance(sprite->GetX(), sprite->GetY(), Follow_Point_X, Follow_Point_Y);
            //���� ������ �� ������ ����� ����������
            if (distance > 1)
            {
                //���� ������ �� ������ ������ ���������� �� ��� �, �� ��������
                if (sprite->GetX() != Follow_Point_X)
                {
                    sprite->SetX(sprite->GetX() - (((sprite->GetX() - Follow_Point_X) / distance) * 1.0 )*speed);
                }

                //���� ������ �� ������ ������ ���������� �� ��� �, �� ��������
                if (sprite->GetY() != Follow_Point_Y)
                {
                    sprite->SetY(sprite->GetY() - (((sprite->GetY() - Follow_Point_Y) / distance) * 1.0 )*speed);
                }
            }

            //���� ������ ������ ����� ����������
            else
            {
                //������� ������������� - OFF
                Follow = false;
            }

            //��� �������
            timeCheckMoving = SDL_GetTicks();
        }

        //��� ������� ������� ����� �������
        lifeTime -= SDL_GetTicks() - lifeTimer;

        //���� ����� ����� ������� ��� �� ����� � �� ��������� �� ����������� � ������ ���������� - ��������� �������� an1
        if (lifeTime > 0 && Follow)
            activeAnimation = "an1";

        //���� ����� ����� ����������� ��� ������ ������ ������ ����������
        else if (lifeTime <= 0 || !Follow)
        {
            //���� ����� ����� ������ ����, �� ��������
            if(lifeTime > 0)
                lifeTime = 0;

            //������� �������� dead
            activeAnimation = "dead";

            //���� �������� ������ �����������, �� ������� ��������������� ������� - ON
            if(lifeTime <= 0 - ((animations["dead"].EndFrame - animations["dead"].BeginFrame) * animations["dead"].Speed))
                plsDestroyMe = true;
        }

        //��� ������� ����� �������
        lifeTimer = SDL_GetTicks();

        //�������� ��������
        updateAnimation();
    }
}

void gameAbilityItem::updateAnimation() //�������� ��������
{
    sprite->PlayAnimation(animations[activeAnimation].BeginFrame, animations[activeAnimation].EndFrame, animations[activeAnimation].Row, animations[activeAnimation].Speed);
}

void gameAbilityItem::Draw() //����������
{
    update();
    sprite->DrawWithCoord(csdl_setup, *spawn);
}

void gameAbilityItem::LoadAnimations() //���������� �������� ��� �������
{
    //��������� ����� �������� ��� ������
    std::ifstream LoadedFile(FilePath.c_str());

    //������������� ����������-������ ��� ������ ��������
    std::string line;

    //������������� ���� �������
    int CurrentType = TypeNone;

    //���� ���� ��� ������� ������
    if (LoadedFile.is_open())
    {
        //��������� �� ��� ���, ���� ��� ������
        while ( LoadedFile.good() )
        {
            //������� ������ �� �����
            std::getline(LoadedFile, line);

            //���� ����� ������������� �������� ������ �������
            if (line == ClassName)
            {
                //���� �������� ������ gameItem, �� ������������� ���
                if(ClassName == "gameItem")
                    CurrentType = TypeItem;

                //���� �������� ������ gameGround, �� ������������� ���
                if(ClassName == "gameGround")
                    CurrentType = TypeGround;

                //���� �������� ������ gameWater, �� ������������� ���
                if(ClassName == "gameWater")
                    CurrentType = TypeWater;

                //���� �������� ������ gameAbilityItem, �� ������������� ���
                if(ClassName == "gameAbilityItem")
                    CurrentType = TypeAbilityItem;
            }

            //���� ������� end - �������� ������� ���
            else if (line == "end")
                CurrentType = TypeNone;

            //� ������ �������
            else
            {
                //���� ������� ��� TypeAbilityItem
                if(CurrentType == TypeAbilityItem)
                {
                    //�������� � ����� ������ �� string
                    std::istringstream iss(line);

                    //�������� ��������� ����������
                    std::string TempNameAnimation;
                    int TempBeginFrame = 0;
                    int TempEndFrame = 0;
                    int TempRow = 0;
                    int TempSpeed = 0;

                    //�������� ���������� "������� ����� � ������" � "������ ����� � ������"
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
                                            //???
                                            bool effects = false;

                                            //���� ���������� ����� name, �� ���������� ����� �� ��������� ����������
                                            if(PreviousWord == "name:")
                                                TempNameAnimation = word;

                                            //���� ���������� ����� parameters
                                            if(PreviousWord == "parameters:")
                                            {
                                                //��������� ����� ���������� �����
                                                TempBeginFrame = atoi(word.c_str());

                                                //���������� �� �����
                                                iss >> word;

                                                //��������� ����� ���������� �����
                                                TempEndFrame = atoi(word.c_str());

                                                //���������� �� �����
                                                iss >> word;

                                                //��������� ����� ���� ��� ������
                                                TempRow = atoi(word.c_str());

                                                //���������� �� �����
                                                iss >> word;

                                                //��������� �������� ��������
                                                TempSpeed = atoi(word.c_str());

                                                //������� ���������� � ����������� �� ��������
                                                AnimationInfo tmpAI;

                                                //���������� ��������� ������ � ����������
                                                tmpAI.BeginFrame = TempBeginFrame;
                                                tmpAI.EndFrame = TempEndFrame;
                                                tmpAI.Row = TempRow;
                                                tmpAI.Speed = TempSpeed;

                                                //�������� ������ � �������� � map ��������
                                                animations[TempNameAnimation] = tmpAI;

                                                //���������� �� �����
                                                iss >> word;

                                                //���� ������ ����� � ������ effects:
                                                if(word == "effects:")
                                                {
                                                    //���������� �� �����
                                                    iss >> word;

                                                    //������� ��������� ����������
                                                    std::vector<EffectInfo*> tempEffectInfo;

                                                    //���� ���������� ����� ID:
                                                    if (PreviousWord == "ID:")
                                                    {
                                                        //�������������� ��������� ���������� tempID
                                                        int tempID = atoi(word.c_str());

                                                        //���������� �� �����
                                                        iss >> word;

                                                        //���������� ����� ���������� � ��������
                                                        PreviousWord = word;

                                                        //���������� �� �����
                                                        iss >> word;

                                                        //���� ���������� ����� Time:
                                                        if (PreviousWord == "Time:")
                                                        {
                                                            //�������������� ���������� tempTime
                                                            int tempTime = atoi(word.c_str());

                                                            //��������� ��������� ������ � ������ ��������� � ���� �������� ��������
                                                            tempEffectInfo.push_back(new EffectInfo(tempID,tempTime,this));

                                                        }
                                                    }
                                                    //�������� ������ � �������� � map ��������
                                                    animationEffects[TempNameAnimation] = tempEffectInfo;
                                                }
                                            }
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
        }
    }
    else //� ������ ������
    {
        std::cout << "File could not be open: " + FilePath << std::endl;
    }
}

void gameFood::LoadConfigs()
{
    //��������� ����� �������� ��� ������
    std::ifstream LoadedFile(FilePath.c_str());

    //������������� ����������-������ ��� ������ ��������
    std::string line;

    //������������� ���� ������� (�������� �� ������ �������� ��� �������� ������)
    int CurrentType = TypeNone;

    //���� ���� ��� ������� ������
    if (LoadedFile.is_open())
    {
        //��������� �� ��� ���, ���� ��� ������
        while ( LoadedFile.good() )
        {
            //������� ������ �� �����
            std::getline(LoadedFile, line);

            //���� ����� ������������� �������� ������
            if (line == ClassName)
            {
                if(ClassName == "gameFood")
                    CurrentType = TypeFood;
            }

            //���� ����� end, �� �������� ������� ���
            else if (line == "end")
            {
                CurrentType = TypeNone;
            }

            //� ������ �������
            else
            {
                //���� ������� ��� �� ������
                if(CurrentType != TypeNone)
                {
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
        }
    }
    else // � ������ ������������� ������� ���� - ������ ������
    {
        std::cout << "File could not be open: " + FilePath << std::endl;
    }
}
