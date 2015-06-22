

#include "connectorDB.h"
connectorDB::connectorDB(char *host,
                char *user,
                char *passwd,
                char *db,
                unsigned int port)
{
    mysql.reconnect = true;
    mysql_init( &mysql );
    mysql = mysql_real_connect(mysql,
                        host,
                        user,
                        passwd,
                        db,
                        port,
                        NULL,
                        NULL);

}
connectorDB::~connectorDB(void)
{

}
bool connectorDB::loadToDB(std::string nameTable,
                            std::string nameColumn,
                            std::string value,
                            std::string firstColumn,
                            std::string valueOfFirst)
{
    char * query = CreateUpdateCommand(nameTable, nameColumn, value, firstColumn, valueOfFirst);
    int mysql_query(mysql, query) ;
}
bool connectorDB::loadAllToDB()
{
For(std::vector<Characters*>::iterator it = (*characters).begin(); it != (*characters).end(); it++)
{
char * query =  CreateFULLUpdateCharacterCommand((*it)-> Item1,
                                            (*it)-> Item2,
                                            (*it)-> Item3,
                                            (*it)-> Item4,
                                            (*it)-> Item5,
                                            (*it)-> Item6,
                                            (*it)-> Item7,
                                            (*it)-> Item8,
                                            (*it)-> Item9,
                                            (*it)-> Item10,
                                            (*it)-> Item11,
                                            (*it)-> Item12,
                                            (*it)-> WSLOT,
                                            (*it)-> ASLOT,
                                            (*it)->Hunger,
                                            (*it)->NickName);
int mysql_query(mysql, query) ;
query =  CreateFULLUpdateLiveCharacterCommand((*it)-> fpX,
                                            (*it)->  fpY,
                                            (*it)->  HP,
                                            (*it)->  MS,
                                            (*it)-> Range,
                                            (*it)-> AtteackDmg,
                                            (*it)-> Defense,
                                            (*it)-> AttakCDTime,
                                            (*it)-> AttackAnimationTime,
                                            (*it)-> NickName
                                            );

int mysql_query(mysql, query) ;
query =  ::CreateFULLUpdateEnvironmentCharacterCommand((*it)-> Hitbox,
                                            (*it)->  ExistOnMap,
                                            (*it)-> PosX,
                                            (*it)-> PosY,
                                            (*it)-> CameraX,
                                            (*it)-> CameraY,
                                            (*it)-> MovingCameraX,
                                            (*it)-> MovingCameraY,
                                            (*it)-> Orgin_X,
                                            (*it)-> Orgin_Y,
                                            (*it)-> image,
                                            (*it)-> hitbox,
                                            (*it)-> rect,
                                            (*it)-> crop,
(*it)->  img_width,
(*it)-> img_height,
(*it)-> CurrentFrame,
(*it)-> timeCheck,
(*it)-> animationDelay,
(*it)-> firstTime,
(*it)-> Amount_Frame_X,
(*it)-> Amount_Frame_Y,
(*it)-> ActiveAnimation,
                                            (*it)-> NickName
                                            )
int mysql_query(mysql, query) ;


}

По аналогии с остальными векторами:
	std::vector<Mobs*> * mobs;
	std::vector<Normal*> * normal;
	std::vector<Bullet*> * bullets;
	std::vector<Ground*> * ground;
}
char*  connectorDB::CreateUpdateCommand(std::string nameTable,
                                        std::string nameColumn,
                                        std::string value,
                                        std::string firstColumn,
                                        std::string valueOfFirst)
{
     return "UPDATE \`"+db+"\`.\`"
            +nameTable.c_str()+"\` SET \`"
            +nameColumn.c_str()+"\`=\'"
            +value.c_str()+"\' WHERE \`"
            +firstColumn.c_str()+"\`=\'"
            +valueOfFirst.c_str()+"\';";
}

char*  connectorDB::CreateFULLUpdateCharacterCommand(int Item1,
                                            int Item2,
                                            int Item3,
                                            int Item4,
                                            int Item5,
                                            int Item6,
                                            int Item7,
                                            int Item8,
                                            int Item9,
                                            int Item10,
                                            int Item11,
                                            int Item12,
                                            int WSLOT,
                                            int ASLOT,
                                            int Hunger,
                                            std::string NickName
                                            )
{
     return "UPDATE \`"+db+"\`.\`characters` SET \`"
            +"Item1"\`=\'"+char(Item1)+"\',"
            +"Item2"\`=\'"+char(Item2)+"\',"
            +"Item3"\`=\'"+char(Item3)+"\',"
            +"Item4"\`=\'"+char(Item4)+"\',"
            +"Item5"\`=\'"+char(Item5)+"\',"
            +"Item6"\`=\'"+char(Item6)+"\',"
            +"Item7"\`=\'"+char(Item7)+"\',"
            +"Item8"\`=\'"+char(Item8)+"\',"
            +"Item9"\`=\'"+char(Item9)+"\',"
            +"Item10"\`=\'"+char(Item10)+"\',"
            +"Item11"\`=\'"+char(Item11)+"\',"
            +"Item12"\`=\'"+char(Item12)+"\'"
            +" WHERE \`NickName\`=\'"+NickName.c_str()+"\';";
}

char*  connectorDB::CreateFULLUpdateLiveCharacterCommand(int fpX,
                                            int fpY,
                                            int HP,
                                            int MS,
                                            int Range,
                                            int AtteackDmg,
                                            int Defense,
                                            int AttakCDTime,
                                            int AttackAnimationTime,
                                            std::string NickName
                                            )
{
     return "UPDATE \`"+db+"\`.\`live` SET \`"
            +"fpX"\`=\'"+char(fpX)+"\',"
            +"fpY"\`=\'"+char(fpY)+"\',"
            +"HP"\`=\'"+char(HP)+"\',"
            +"MS"\`=\'"+char(MS)+"\',"
            +"Range"\`=\'"+char(Range)+"\',"
            +"AtteackDmg"\`=\'"+char(AtteackDmg)+"\',"
            +"Defense"\`=\'"+char(Defense)+"\',"
            +"AttakCDTime"\`=\'"+char(AttakCDTime)+"\',"
            +"AttackAnimationTime"\`=\'"+char(AttackAnimationTime)+"\',"
            +" WHERE \`NickName\`=\'"+NickName.c_str()+"\';";
}


char*  connectorDB::CreateFULLUpdateEnvironmentCharacterCommand(std::string Hitbox,
                                            int ExistOnMap,
                                            int PosX,
                                            int PosY,
                                            int CameraX,
                                            int CameraY,
                                            int MovingCameraX,
                                            int MovingCameraY,
                                            int Orgin_X,
                                            int Orgin_Y,
                                            std::string image,
                                            std::string hitbox,
                                            std::string rect,
                                            std::string crop,
int img_width,
int img_height,
int CurrentFrame,
int timeCheck,
int animationDelay,
int firstTime,
int Amount_Frame_X,
int Amount_Frame_Y,
int ActiveAnimation,
                                            std::string NickName
                                            )
{
     return "UPDATE \`"+db+"\`.\` environment` SET \`"
            +" ExistOnMap "\`=\'"+char(ExistOnMap)+"\',"
            +" PosX "\`=\'"+char(PosX)+"\',"
            +" PosY "\`=\'"+char(PosY)+"\',"
            +" CameraX "\`=\'"+char(CameraX)+"\',"
            +" MovingCameraX "\`=\'"+char(MovingCameraX)+"\',"
            +" MovingCameraY "\`=\'"+char(MovingCameraY)+"\',"
            +" Orgin_X "\`=\'"+char(Orgin_X)+"\',"
            +" Orgin_Y "\`=\'"+char(Orgin_Y)+"\',"
            +" image "\`=\'"+image.c_str()+"\',"
            +" hitbox "\`=\'"+ hitbox.c_str()+"\',"
            +" rect "\`=\'"+ rect.c_str()+"\',"
            +" crop "\`=\'"+ crop.c_str()+"\',"
            +" img_width "\`=\'"+char(img_width)+"\',"
            +" img_height "\`=\'"+char(img_height)+"\',"
            +" CurrentFrame "\`=\'"+char(CurrentFrame)+"\',"
            +" timeCheck "\`=\'"+char(timeCheck)+"\',"
            +" firstTime "\`=\'"+char(firstTime)+"\',"
            +" Amount_Frame_X "\`=\'"+char(Amount_Frame_X)+"\',"
            +" Amount_Frame_Y "\`=\'"+char(Amount_Frame_Y)+"\',"
            +" MovingCameraY "\`=\'"+char(MovingCameraY)+"\',"
            +" ActiveAnimation "\`=\'"+char(ActiveAnimation)+"\',"
            +" WHERE \`NickName\`=\'"+NickName.c_str()+"\';";


char*  connectorDB:: CreateFULLUpdateMobsCommand (int Aggressive,
                                            std::string AgroRenge,
                                            int idMobs
                                            )
{
     return "UPDATE \`"+db+"\`.\`Mobs` SET \`"
            +" Aggressive "\`=\'"+char(Aggressive)+"\',"
            +" AgroRenge "\`=\'"+AgroRenge.c_str()+"\'"
            +" WHERE \` idMobs \`=\'"+ char(idMobs)+"\';";
}

    char*  CreateFULLUpdateLiveMobsCommand(int fpX,
                                            int fpY,
                                            int HP,
                                            int MS,
                                            int Range,
                                            int AtteackDmg,
                                            int Defense,
                                            int AttakCDTime,
                                            int AttackAnimationTime,
                                            int idMobs
)
{
return "UPDATE \`"+db+"\`.\`live` SET \`"
            +"fpX"\`=\'"+char(fpX)+"\',"
            +"fpY"\`=\'"+char(fpY)+"\',"
            +"HP"\`=\'"+char(HP)+"\',"
            +"MS"\`=\'"+char(MS)+"\',"
            +"Range"\`=\'"+char(Range)+"\',"
            +"AtteackDmg"\`=\'"+char(AtteackDmg)+"\',"
            +"Defense"\`=\'"+char(Defense)+"\',"
            +"AttakCDTime"\`=\'"+char(AttakCDTime)+"\',"
            +"AttackAnimationTime"\`=\'"+char(AttackAnimationTime)+"\',"
            +" WHERE \` idMobs \`=\'"+ char(idMobs)+"\';";
}
char*  connectorDB:: CreateFULLUpdateEnvironmentMobsCommand (std::string Hitbox,
                                            int ExistOnMap,
                                            int PosX,
                                            int PosY,
                                            int CameraX,
                                            int CameraY,
                                            int MovingCameraX,
                                            int MovingCameraY,
                                            int Orgin_X,
                                            int Orgin_Y,
                                            std::string image,
                                            std::string hitbox,
                                            std::string rect,
                                            std::string crop,
int img_width,
int img_height,
int CurrentFrame,
int timeCheck,
int animationDelay,
int firstTime,
int Amount_Frame_X,
int Amount_Frame_Y,
int ActiveAnimation,
                                            int idMobs
                                            )
{
     return "UPDATE \`"+db+"\`.\` environment` SET \`"
            +" ExistOnMap "\`=\'"+char(ExistOnMap)+"\',"
            +" PosX "\`=\'"+char(PosX)+"\',"
            +" PosY "\`=\'"+char(PosY)+"\',"
            +" CameraX "\`=\'"+char(CameraX)+"\',"
            +" MovingCameraX "\`=\'"+char(MovingCameraX)+"\',"
            +" MovingCameraY "\`=\'"+char(MovingCameraY)+"\',"
            +" Orgin_X "\`=\'"+char(Orgin_X)+"\',"
            +" Orgin_Y "\`=\'"+char(Orgin_Y)+"\',"
            +" image "\`=\'"+image.c_str()+"\',"
            +" hitbox "\`=\'"+ hitbox.c_str()+"\',"
            +" rect "\`=\'"+ rect.c_str()+"\',"
            +" crop "\`=\'"+ crop.c_str()+"\',"
            +" img_width "\`=\'"+char(img_width)+"\',"
            +" img_height "\`=\'"+char(img_height)+"\',"
            +" CurrentFrame "\`=\'"+char(CurrentFrame)+"\',"
            +" timeCheck "\`=\'"+char(timeCheck)+"\',"
            +" firstTime "\`=\'"+char(firstTime)+"\',"
            +" Amount_Frame_X "\`=\'"+char(Amount_Frame_X)+"\',"
            +" Amount_Frame_Y "\`=\'"+char(Amount_Frame_Y)+"\',"
            +" MovingCameraY "\`=\'"+char(MovingCameraY)+"\',"
            +" ActiveAnimation "\`=\'"+char(ActiveAnimation)+"\',"
            +" WHERE \` idMobs \`=\'"+ char(idMobs)+"\';";
}

    char*  CreateFULLUpdateNormalCommand(bool PickUpAble,
                                            	int idNormal
)
{

     return "UPDATE \`"+db+"\`.\`normal` SET \`"
            +" PickUpAble "\`=\'"+char(PickUpAble)+"\',"
            +" WHERE \` idNormal \`=\'"+ char(idNormal)+"\';";

}
    char*  CreateFULLUpdateObjectsNormalCommand(bool Collision,
		bool BulletCollision,
int idNormal
)
{
return "UPDATE \`"+db+"\`.\` objects ` SET \`"
            +" Collision "\`=\'"+char(Collision)+"\',"
            +" BulletCollision "\`=\'"+char(BulletCollision)+"\'"
            +" WHERE \` idNormal \`=\'"+ char(idNormal)+"\';";

}
    char*  CreateFULLUpdateEnvironmentNormalCommand(std::string Hitbox,
                                            int ExistOnMap,
                                            int PosX,
                                            int PosY,
                                            int CameraX,
                                            int CameraY,
                                            int MovingCameraX,
                                            int MovingCameraY,
                                            int Orgin_X,
                                            int Orgin_Y,
                                            std::string image,
                                            std::string hitbox,
                                            std::string rect,
                                            std::string crop,
int img_width,
int img_height,
int CurrentFrame,
int timeCheck,
int animationDelay,
int firstTime,
int Amount_Frame_X,
int Amount_Frame_Y,
int ActiveAnimation,
                                            int idNormal
                                            )
{
return "UPDATE \`"+db+"\`.\` environment` SET \`"
            +" ExistOnMap "\`=\'"+char(ExistOnMap)+"\',"
            +" PosX "\`=\'"+char(PosX)+"\',"
            +" PosY "\`=\'"+char(PosY)+"\',"
            +" CameraX "\`=\'"+char(CameraX)+"\',"
            +" MovingCameraX "\`=\'"+char(MovingCameraX)+"\',"
            +" MovingCameraY "\`=\'"+char(MovingCameraY)+"\',"
            +" Orgin_X "\`=\'"+char(Orgin_X)+"\',"
            +" Orgin_Y "\`=\'"+char(Orgin_Y)+"\',"
            +" image "\`=\'"+image.c_str()+"\',"
            +" hitbox "\`=\'"+ hitbox.c_str()+"\',"
            +" rect "\`=\'"+ rect.c_str()+"\',"
            +" crop "\`=\'"+ crop.c_str()+"\',"
            +" img_width "\`=\'"+char(img_width)+"\',"
            +" img_height "\`=\'"+char(img_height)+"\',"
            +" CurrentFrame "\`=\'"+char(CurrentFrame)+"\',"
            +" timeCheck "\`=\'"+char(timeCheck)+"\',"
            +" firstTime "\`=\'"+char(firstTime)+"\',"
            +" Amount_Frame_X "\`=\'"+char(Amount_Frame_X)+"\',"
            +" Amount_Frame_Y "\`=\'"+char(Amount_Frame_Y)+"\',"
            +" MovingCameraY "\`=\'"+char(MovingCameraY)+"\',"
            +" ActiveAnimation "\`=\'"+char(ActiveAnimation)+"\',"
            +" WHERE \` idMobs \`=\'"+ char(idNormal)+"\';";

}

UPDATE `gamedb`.`bullet` SET `Speed`='2', `Damage`='2', `FollowPointX`='2', `FollowPointY`='2' WHERE `idBullet`='1';
char*  CreateFULLUpdateBulletCommand (int Speed,
				int Damage,
				int FollowPointX,
				int FollowPointY,
                                            	int idBullet
)
{

     return "UPDATE \`"+db+"\`.\`normal` SET \`"
            +" Speed "\`=\'"+char(Speed)+"\',"
            +" Damage "\`=\'"+char(Damage)+"\',"
            +" FollowPointX "\`=\'"+char(FollowPointX)+"\',"
            +" FollowPointY "\`=\'"+char(FollowPointY)+"\'"
            +" WHERE \` idBullet \`=\'"+ char(idBullet)+"\';";

}

char*  CreateFULLUpdateObjectsBulletCommand (bool Collision,
		bool BulletCollision,
int idBullet
)
{
return "UPDATE \`"+db+"\`.\` objects` SET \`"
            +" Collision "\`=\'"+char(Collision)+"\',"
            +" BulletCollision "\`=\'"+char(BulletCollision)+"\'"
            +" WHERE \` idBullet \`=\'"+ char(idBullet)+"\';";

}
    char*  CreateFULLUpdateEnvironmentBulletCommand (std::string Hitbox,
                                            int ExistOnMap,
                                            int PosX,
                                            int PosY,
                                            int CameraX,
                                            int CameraY,
                                            int MovingCameraX,
                                            int MovingCameraY,
                                            int Orgin_X,
                                            int Orgin_Y,
                                            std::string image,
                                            std::string hitbox,
                                            std::string rect,
                                            std::string crop,
int img_width,
int img_height,
int CurrentFrame,
int timeCheck,
int animationDelay,
int firstTime,
int Amount_Frame_X,
int Amount_Frame_Y,
int ActiveAnimation,
                                            int idBullet
                                            )
{
return "UPDATE \`"+db+"\`.\` environment` SET \`"
            +" ExistOnMap "\`=\'"+char(ExistOnMap)+"\',"
            +" PosX "\`=\'"+char(PosX)+"\',"
            +" PosY "\`=\'"+char(PosY)+"\',"
            +" CameraX "\`=\'"+char(CameraX)+"\',"
            +" MovingCameraX "\`=\'"+char(MovingCameraX)+"\',"
            +" MovingCameraY "\`=\'"+char(MovingCameraY)+"\',"
            +" Orgin_X "\`=\'"+char(Orgin_X)+"\',"
            +" Orgin_Y "\`=\'"+char(Orgin_Y)+"\',"
            +" image "\`=\'"+image.c_str()+"\',"
            +" hitbox "\`=\'"+ hitbox.c_str()+"\',"
            +" rect "\`=\'"+ rect.c_str()+"\',"
            +" crop "\`=\'"+ crop.c_str()+"\',"
            +" img_width "\`=\'"+char(img_width)+"\',"
            +" img_height "\`=\'"+char(img_height)+"\',"
            +" CurrentFrame "\`=\'"+char(CurrentFrame)+"\',"
            +" timeCheck "\`=\'"+char(timeCheck)+"\',"
            +" firstTime "\`=\'"+char(firstTime)+"\',"
            +" Amount_Frame_X "\`=\'"+char(Amount_Frame_X)+"\',"
            +" Amount_Frame_Y "\`=\'"+char(Amount_Frame_Y)+"\',"
            +" MovingCameraY "\`=\'"+char(MovingCameraY)+"\',"
            +" ActiveAnimation "\`=\'"+char(ActiveAnimation)+"\',"
            +" WHERE \` idBullet \`=\'"+ char(idBullet)+"\';";

}
char*  CreateFULLUpdateEnvironmentGroundCommand (std::string Hitbox,
                                            int ExistOnMap,
                                            int PosX,
                                            int PosY,
                                            int CameraX,
                                            int CameraY,
                                            int MovingCameraX,
                                            int MovingCameraY,
                                            int Orgin_X,
                                            int Orgin_Y,
                                            std::string image,
                                            std::string hitbox,
                                            std::string rect,
                                            std::string crop,
int img_width,
int img_height,
int CurrentFrame,
int timeCheck,
int animationDelay,
int firstTime,
int Amount_Frame_X,
int Amount_Frame_Y,
int ActiveAnimation,
                                            int idGround
                                            )
{
return "UPDATE \`"+db+"\`.\` environment` SET \`"
            +" ExistOnMap "\`=\'"+char(ExistOnMap)+"\',"
            +" PosX "\`=\'"+char(PosX)+"\',"
            +" PosY "\`=\'"+char(PosY)+"\',"
            +" CameraX "\`=\'"+char(CameraX)+"\',"
            +" MovingCameraX "\`=\'"+char(MovingCameraX)+"\',"
            +" MovingCameraY "\`=\'"+char(MovingCameraY)+"\',"
            +" Orgin_X "\`=\'"+char(Orgin_X)+"\',"
            +" Orgin_Y "\`=\'"+char(Orgin_Y)+"\',"
            +" image "\`=\'"+image.c_str()+"\',"
            +" hitbox "\`=\'"+ hitbox.c_str()+"\',"
            +" rect "\`=\'"+ rect.c_str()+"\',"
            +" crop "\`=\'"+ crop.c_str()+"\',"
            +" img_width "\`=\'"+char(img_width)+"\',"
            +" img_height "\`=\'"+char(img_height)+"\',"
            +" CurrentFrame "\`=\'"+char(CurrentFrame)+"\',"
            +" timeCheck "\`=\'"+char(timeCheck)+"\',"
            +" firstTime "\`=\'"+char(firstTime)+"\',"
            +" Amount_Frame_X "\`=\'"+char(Amount_Frame_X)+"\',"
            +" Amount_Frame_Y "\`=\'"+char(Amount_Frame_Y)+"\',"
            +" MovingCameraY "\`=\'"+char(MovingCameraY)+"\',"
            +" ActiveAnimation "\`=\'"+char(ActiveAnimation)+"\',"
            +" WHERE \` idGround \`=\'"+ char(idGround)+"\';";
