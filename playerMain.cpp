//选手1写入ai
#include <math.h>
#include "teamstyle18-my-1.h"
bool not_occupied(Position p,int unitSize,Unit* allUnit)
{
	for(int i=0;i<unitSize;i++)
		if(allUnit[i].position.x==p.x&&allUnit[i].position.y==p.y)
			return false;
	return true;
}
void player_main(void)
{
	//write your AI here
	int Id=getTeamId()?1:0;
	int unitSize=getUnitSize();
	Unit* allUnit=getUnit();
	for(int i=0;i<unitSize;i++)
	{
		Unit* currentUnit=&allUnit[i];
		if(currentUnit->flag!=Id)
			continue;
		switch(currentUnit->type_name)
		{
		case __BASE:
			produce(currentUnit->unit_id);
			break;
		case MEAT:
		{
			int min=300;
			int target_id=0;
			for(int j=0;j<unitSize;j++)
			{
				if(allUnit[j].flag!=-1)
					continue;
				int distance=abs(allUnit[j].position.x-currentUnit->position.x)+abs(allUnit[j].position.y-currentUnit->position.y);
				if(distance<min)
				{
					min=distance;
					target_id=j;
				}
			}
			Unit temp=allUnit[target_id];
			if(min==1)
				capture(currentUnit->unit_id,temp.unit_id);
			else if(min<=3)
			{
				if(currentUnit->position.x>=temp.position.x)
					Move(currentUnit->unit_id,Position(temp.position.x+1,temp.position.y));
				else if(currentUnit->position.x<temp.position.x)
					Move(currentUnit->unit_id,Position(temp.position.x-1,temp.position.y));
			}
			else
			{
				bool _ok=true;
				if(temp.position.x>currentUnit->position.x)
				{
					if(temp.position.y>currentUnit->position.y&&not_occupied(Position(currentUnit->position.x+1,currentUnit->position.y+1),unitSize,allUnit))
					{
						Move(currentUnit->unit_id,Position(currentUnit->position.x+1,currentUnit->position.y+1));
						_ok=false;
					}
					else if(temp.position.y=currentUnit->position.y&&not_occupied(Position(currentUnit->position.x+1,currentUnit->position.y),unitSize,allUnit))
					{
						Move(currentUnit->unit_id,Position(currentUnit->position.x+1,currentUnit->position.y));
						_ok=false;
					}
					else if(not_occupied(Position(currentUnit->position.x+1,currentUnit->position.y-1),unitSize,allUnit))
					{
						Move(currentUnit->unit_id,Position(currentUnit->position.x+1,currentUnit->position.y-1));
						_ok=false;
					}
				}
				else if(temp.position.x=currentUnit->position.x||_ok)
				{
					if(temp.position.y>currentUnit->position.y&&not_occupied(Position(currentUnit->position.x,currentUnit->position.y+1),unitSize,allUnit))
					{
						Move(currentUnit->unit_id,Position(currentUnit->position.x,currentUnit->position.y+1));
						_ok=false;
					}
					else if(not_occupied(Position(currentUnit->position.x,currentUnit->position.y-1),unitSize,allUnit))
					{
						Move(currentUnit->unit_id,Position(currentUnit->position.x,currentUnit->position.y-1));
						_ok=false;
					}
				}
				else if(_ok)
				{
					if(temp.position.y>currentUnit->position.y&&not_occupied(Position(currentUnit->position.x-1,currentUnit->position.y+1),unitSize,allUnit))
					{
						Move(currentUnit->unit_id,Position(currentUnit->position.x-1,currentUnit->position.y+1));
						_ok=false;
					}
					else if(temp.position.y=currentUnit->position.y&&not_occupied(Position(currentUnit->position.x-1,currentUnit->position.y),unitSize,allUnit))
					{
						Move(currentUnit->unit_id,Position(currentUnit->position.x-1,currentUnit->position.y));
						_ok=false;
					}
					else if(not_occupied(Position(currentUnit->position.x-1,currentUnit->position.y-1),unitSize,allUnit))
					{
						Move(currentUnit->unit_id,Position(currentUnit->position.x-1,currentUnit->position.y-1));
						_ok=false;
					}
				}
			}
			break;
		}
	}
	}
}
