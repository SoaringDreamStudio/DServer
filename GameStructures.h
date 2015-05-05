#include <time.h>
#include <string>
#include <vector>
class gameObject
{
public:
	gameObject(std::string Passed_ClassName, int passed_ID, int X, int Y, int W, int H);
	~gameObject(void);

    std::vector<EffectInfo*> getEffects() {return effects;}
    double GetDistance(int X1, int Y1, int X2, int Y2);
    void setFollowPoint(int X, int Y) {Follow_Point_X = X; Follow_Point_Y = Y;}

    void LoadConfigs();

protected:
    std::string ClassName;
    std::string ObjectName;
    int ID;
    bool invisible;
    CSDL_Setup* csdl_setup;
    SDL_Rect Rect;
    SDL_Rect hitbox;
    SDL_Rect crop;
    std::string FilePath;

    bool Follow;
	int Follow_Point_X;
	int Follow_Point_Y;

    int timeCheckMoving;

	float distance;
    float speed;

    std::vector<EffectInfo*> effects;
    std::map<std::string,AnimationInfo> animations;
};

class gameSpace : public gameObject
{
public:
    gameSpace(std::string Passed_ClassName, int passed_ID, int X, int Y, int W, int H) :  gameObject(Passed_ClassName, passed_ID, X, Y, W, H)
    { }

	~gameSpace(void) {};
};

class gameItem : public gameSpace
{
public:
    gameItem(int passed_ID, int X, int Y, int W, int H) :  gameSpace("gameItem", passed_ID, X, Y, W, H)
    {ClassName = "gameItem";}
    gameItem(std::string Passed_ClassName, int passed_ID, int X, int Y, int W, int H) :  gameSpace(Passed_ClassName, passed_ID, X, Y, W, H, CameraX, CameraY)
    {ClassName = Passed_ClassName;}

	~gameItem(void) {};
};

class gameFood : public gameItem
{
public:
    gameFood(int passed_ID, int X, int Y, int W, int H) :  gameItem("gameFood", passed_ID, X, Y, W, H, CameraX, CameraY)
    {ClassName = "gameFood"; LoadConfigs();}

	~gameFood(void) {};
	int GetEnergy()
	{
	    return static_cast<int>(Protein*4 + Carbohydrate*3,75 + Fat*9);
	}
	int GetProtein() {return Protein;}
	int GetCarbohydrate() {return Carbohydrate;}
	int GetFat() {return Fat;}
	void LoadConfigs();
private:
    int Energy;
    int Protein;
    int Carbohydrate;
    int Fat;
};

class gameAbilityItem : public gameSpace
{
public:
    gameAbilityItem(int passedLifeTime, int passed_ID, int X, int Y, int W, int H) :  gameSpace("gameAbilityItem", passed_ID, X, Y, W, H)
    {ClassName = "gameAbilityItem"; lifeTime = passedLifeTime; lifeTimer = SDL_GetTicks(); plsDestroyMe = false; LoadAnimations(); timeCreate=SDL_GetTicks();
        AnimationInfo tmpAI;tmpAI.BeginFrame = 998;tmpAI.EndFrame = 999;tmpAI.Row = 0;
        tmpAI.Speed = 1;animations["creating"] = tmpAI;
    }
	~gameAbilityItem(void) {};
    bool Destroy() {return plsDestroyMe;}
    void LoadAnimations();
	void Draw();
	std::map<std::string,std::vector<EffectInfo*> > getAnimationEffects() {return animationEffects;}
	std::string getActiveAnimation() {return activeAnimation;}
private:
    void update();
    void updateAnimation();
    int lifeTime;
    int lifeTimer;
    int timeCreate;
    std::string activeAnimation;
    std::map<std::string,std::vector<EffectInfo*> > animationEffects;
    bool plsDestroyMe;
};

class gameFloor : public gameSpace
{
public:
    gameFloor(std::string Passed_ClassName, int passed_ID, int X, int Y, int W, int H) :  gameSpace(Passed_ClassName, passed_ID, X, Y, W, H)
    { }


	~gameFloor(void) {};
};

class gameGround : public gameFloor
{
public:
    gameGround(int passed_ID, int X, int Y, int W, int H) :  gameFloor("gameGround", passed_ID, X, Y, W, H)
    {ClassName = "gameGround"; }

	~gameGround(void) {};
    void Draw();
};

class gameWater : public gameFloor
{
public:
    gameWater(int passed_ID, int X, int Y, int W, int H) :  gameFloor("gameWater", passed_ID, X, Y, W, H)
    {ClassName = "gameWater"; }

	~gameWater(void) {};
};

class gameActor : public gameObject
{
public:
    gameActor(std::string Passed_ClassName, int passed_ID, int X, int Y, int W, int H) :  gameObject(Passed_ClassName, passed_ID, X, Y, W, H)
    { }

	~gameActor(void) {};
};
