#ifndef CL_BASE_H
#define CL_BASE_H
#include "teamstyle18-my-1.h"
class C_BASE
{
private:
	int TeamID;//队伍ID
	int BaseID;//基地ID
	int HPremain;//剩余血量
	int AttackPower;//攻击力
	int DefensivePower;//防御力
	int SkillCD;//普攻剩余CD
	int InitMeatNum;//开场需要建立小鲜肉个数
	int InitHaveMeat;//开局已经建立的小鲜肉个数
	Unit *BaseUnit;//指向基地的指针
	const double attack_type[5] = { 0.25,0.75,1,1,1 };
	Position BasePos;
	int first;//第一回合
public:
	C_BASE();//构造函数
public:
	//返回基地ID;
	int getID();
	//更新血量
	void updateHP();
	//更新攻击力
	void updateAttack();
	//更新防御力
	void updateDefense();
	//返回血量
	int getHP();
	//开局建立小鲜肉,执行n次，每次返回新生成的小鲜肉的ID
	int proMeatBegin();
	//是否初始化结束
	bool IsInitDone();
	//中途生产小鲜肉,返回小鲜肉的ID
	int proMeat();
	//计算攻击力,参数为攻击对象ID
	int getAttackPower(int attackID);
	//计算防御力，参数为攻击基地的对象ID
	int getDefensivePower(int defensiveID);
	//是否可以输出技能
	bool getSkillCD();

	//攻击行为
	//返回要攻击的对象ID
	int WhichToAttack();
	//发动攻击
	void LaunchAttack(int AttackID);

	//每回合应该调用的函数集合
	void BaseRun();
};
#endif // !CL_BASE_H

