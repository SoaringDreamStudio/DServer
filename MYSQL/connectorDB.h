#include "my_pthread.h"
#include "MY_SYS.H"
#include "Mysql.h"
#include "mysql_com.h"
#include "mysql_version.h"
#include "mysqld_error.h"
#include "RAID.H"

class connectorDB
{
public:
	connectorDB(char *host,
                char *user,
                char *passwd,
                char *db,
                unsigned int port);
	~connectorDB(void);
	bool loadToDB(std::string nameTable,
                    std::string nameColumn,
                    std::string value,
                    std::string firstColumn,
                    std::string valueOfFirst);
	bool loadAllToDB();

private:
    char*  CreateUpdateCommand();
    char*  CreateFULLUpdateCharacterCommand();
    char*  CreateFULLUpdateLiveCharacterCommand();
    char*  CreateFULLUpdateEnvironmentCharacterCommand();

    char*  CreateFULLUpdateMobsCommand();
    char*  CreateFULLUpdateLiveMobsCommand();
    char*  CreateFULLUpdateEnvironmentMobsCommand();

    char*  CreateFULLUpdateNormalCommand();
    char*  CreateFULLUpdateObjectsNormalCommand();
    char*  CreateFULLUpdateEnvironmentNormalCommand();

    char*  CreateFULLUpdateBulletCommand();
    char*  CreateFULLUpdateObjectsBulletCommand();
    char*  CreateFULLUpdateEnvironmentBulletCommand();

    char*  CreateFULLUpdateEnvironmentGroundCommand();

    MYSQL mysql;
    MYSQL_ROW row;
    MYSQL_RES *res;

    char *db;

	std::vector<Characters*> * characters;
	std::vector<Mobs*> * mobs;
	std::vector<Normal*> * normal;
	std::vector<Bullet*> * bullets;
	std::vector<Ground*> * ground;
};
