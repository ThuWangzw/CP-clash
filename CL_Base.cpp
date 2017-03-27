#include "CL_Base.h"
//构造函数
C_BASE::C_BASE()
{
	TeamID = getTeamId();//赋值TeamID
	Unit *allUnit = getUnit();
	for (int i = 0, sum = getUnitSize(); i < sum; i++)//赋值基地ID
	{
		if (allUnit[i].unit_type == __BASE&&allUnit[i].flag == TeamID)
		{
			BaseUnit = &allUnit[i];
			BaseID = allUnit[i].unit_id;
			HPremain = allUnit[i].health_now;
			AttackPower = allUnit[i].attack_now;
			DefensivePower = allUnit[i].defense_now;
			BasePos = allUnit[i].position;
			break;
		}
	}
	InitMeatNum = 20;//预估开场建立小鲜肉个数为20
	InitHaveMeat = 0;
	first = 1;
	SkillCD = 0;//初始技能CD为0
}

int C_BASE::getID()
{
	return BaseID;
}

void C_BASE::updateHP()
{
	Unit *allUnit = getUnit();
	int sum = getUnitSize();
	for (int i = 0; i < sum; i++)
	{
		if (allUnit[i].unit_id == BaseID)
		{
			HPremain=allUnit[i].health_now;
			return;
		}
	}
}

void C_BASE::updateAttack()
{
	Unit *allUnit = getUnit();
	int sum = getUnitSize();
	for (int i = 0; i < sum; i++)
	{
		if (allUnit[i].unit_id == BaseID)
		{
			AttackPower = allUnit[i].attack_now;
			return;
		}
	}
}

void C_BASE::updateDefense()
{
	Unit *allUnit = getUnit();
	int sum = getUnitSize();
	for (int i = 0; i < sum; i++)
	{
		if (allUnit[i].unit_id == BaseID)
		{
			DefensivePower = allUnit[i].defense_now;
			return;
		}
	}
}

int C_BASE::getHP()
{
	return HPremain;
}

int C_BASE::proMeatBegin()
{
	int MeatID;
	//初始化结束
	if (IsInitDone()) return -1;
	//生产
	produce(BaseID);
	InitHaveMeat++;
	//输出生产的小鲜肉ID
	Unit *allUnit = getUnit();
	for (int i = 0, sum = getUnitSize(); i < sum; i++)
	{
		if (allUnit[i].flag == TeamID && allUnit[i].unit_type == MEAT && allUnit[i].position.x == BasePos.x && allUnit[i].position.y == BasePos.y)
		{
			return allUnit[i].unit_id;
		}
	}
	return -1;
}

bool C_BASE::IsInitDone()
{
	if (InitHaveMeat >= InitMeatNum) return true;
	return false;
}

int C_BASE::proMeat()
{
	int MeatID;
	//初始化结束
	if (IsInitDone()) return -1;
	//生产
	produce(BaseID);
	//输出生产的小鲜肉ID
	Unit *allUnit = getUnit();
	int sum = getUnitSize();
	for (int i = 0; i < sum; i++)
	{
		if (allUnit[i].flag == TeamID && allUnit[i].unit_type == MEAT && allUnit[i].position.x == BasePos.x && allUnit[i].position.y == BasePos.y)
		{
			return allUnit[i].unit_id;
		}
	}
	return -1;
}

int C_BASE::getAttackPower(int attackID)
{
	Unit *allUnit = getUnit();
	int sum = getUnitSize();
	int attackNum;
	int attackPower;
	for (attackNum = 0; attackNum < sum; attackNum++)
	{
		if (allUnit[attackNum].unit_id == attackID) break;
	}
	//普攻伤害//应该是有
	attackPower = allUnit[attackNum].attack_now*(1-DefensivePower/1000);
	switch (allUnit[attackNum].unit_type)
	{
	case SUPERMAN:
		attackPower *= attack_type[ELEC];
		break;
	case BATTLE_TANK:
		attackPower *= attack_type[ARTILLERY];
		break;
	case NUKE_TANK:
		attackPower *= attack_type[PENETRATING];
		break;
	case UAV:
		attackPower *= attack_type[MACHINEGUN];
		break;
	case EAGLE:
		attackPower *= attack_type[EXPLOSION];
		break;
	}
	return attackPower;
}

int C_BASE::getDefensivePower(int defensiveID)
{
	return DefensivePower;
}

bool C_BASE::getSkillCD()
{
	Unit *allUnit = getUnit();
	int sum = getUnitSize();
	for (int i = 0; i < sum; i++)
	{
		if (allUnit[i].unit_id == BaseID)
		{
			if (allUnit[i].skill_last_release_time1 != 0) return false;
			else return true;
		}
	}
	return false;
}

int C_BASE::WhichToAttack()
{
	//攻击范围内血量最低的
	Unit *allUnit = getUnit();
	int sum = getUnitSize();
	int AHPRemain = 10000;
	int AttackID;
	for (int i = 0; i < sum; i++)
	{
		//在距离之内且血量最低
		if (allUnit[i].flag == 1 && allUnit[i].health_now < AHPRemain && ((abs(allUnit[i].position.x - BasePos.x) + abs(allUnit[i].position.y - BasePos.y)) < 12)) 
			AttackID = allUnit[i].unit_id;
	}
	return AttackID;
}

void C_BASE::LaunchAttack(int AttackID)
{
	skill_1(BaseID, AttackID, BasePos);
}

void C_BASE::BaseRun()
{
	if (first)
	{
		getID();
	}
	//更新血量
	updateHP();
	//更新攻击力
	updateAttack();
	//更新防御力
	updateDefense();
}
