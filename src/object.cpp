#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "alive.h"
#define FOR(i,min,max) for(int i=(min);i<(max);i++)
using namespace std;
using namespace sf;
Coin::Coin(vector<int> & t)
{
	LWW.x=t[0]*32;
	LWW.y=t[1]*32;
	image[0].loadFromFile("c2.png");
	image[1].loadFromFile("c1.png");
	image[2].loadFromFile("c0.png");
	image[3].loadFromFile("c3.png");
	FOR(i,0,4) texture[i].loadFromImage(image[i]);
	frame=-1;
	sprite.scale(2,2);
	sprite.setPosition(LWW);
	srand(time(0)+rand());
	srand(rand());
	srand(rand());
	money=rand()%41-20;
	full=true;
}
void Coin::show(RenderWindow &window,vector<vector<char> >& world,int dp,int d)
{
	frame++;
	frame=frame%4;
	Vector2f dr=LWW;
	dr.x-=32*dp+d;
	dr.y-=32;
	sprite.setPosition(dr);
	sprite.setTexture(texture[frame]);
	if(dr.x<=world.size()*32)
	{
		visibility=true;
		window.draw(sprite);
	}
	else
		visibility=false;
}
int Coin::getMoney()
{
	full=false;
	return money;
}
void Princess::create(vector<int> & t)
{
	LWW.x=t[0]*32+8;
	LWW.y=t[1]*32+8;
	image[0].loadFromFile("p0.png");
	image[1].loadFromFile("p1.png");
	image[2].loadFromFile("p2.png");
	image[3].loadFromFile("p3.png");
	FOR(i,0,4) texture[i].loadFromImage(image[i]);
	frame=-1;
	sprite.setPosition(LWW);
}
void Princess::show(RenderWindow &window,vector<vector<char> >& world,int dp,int d)
{
	frame++;
	frame=frame%4;
	Vector2f dr=LWW;
	dr.x-=32*dp+d;
	dr.y-=32;
	sprite.setPosition(dr);
	sprite.setTexture(texture[frame]);
	if(dr.x<=world.size()*32)
	{
		visibility=true;
		window.draw(sprite);
	}
	else
		visibility=false;
}
Alive::Alive(){ }
Alive::Alive(vector<int>& lwm)
{
	Vector2f a(lwm[0]*32,lwm[1]*32);
	setLWW(a);
	setLWM(lwm);
	frame=0;
}
void Alive::setLWM(vector<int> & lwm){LWM=lwm;}
vector<int> & Alive::getLWM(){return LWM;}
void Alive::setLWW(Vector2f & lww){LWW=lww;}
Vector2f & Alive::getLWW(){return LWW;}	
bool Alive::getCondition(vector<vector<char> >& world)
{
	vector<int> place(2);
	Vector2f pl(getLWW());
	place[1]=pl.y/32;
	place[0]=pl.x/32;
	float wy=pl.y/32;
	float wx=pl.x/32;
	if(wy==place[1])
	{
		if(wx==place[0])
		{
			if(world[place[1]+1][place[0]]=='#')
				return false;
		}
		else
		{
			if(world[place[1]+1][place[0]]=='#'||(world[place[1]+1][place[0]+1]=='#'))
				return false;
		}
	}
	return true;
}
Goomba::Goomba(char name,vector<int> & a)
{
	image[0].loadFromFile("G5.png");
	image[1].loadFromFile("G4.png");
	image[2].loadFromFile("G3.png");
	image[3].loadFromFile("G4.png");
	image[4].loadFromFile("G6.png");
	if(name=='g')
	{ 
		side=-1;
		FOR(i,0,4) image[i].flipHorizontally();
		FOR(i,0,5) texture[i].loadFromImage(image[i]);
		
	}
	else 
	{
		side=1;
		FOR(i,0,5) texture[i].loadFromImage(image[i]);
		
	}
	setLWM(a);
	Vector2f b(a[0]*32,a[1]*32);
	setLWW(b);
	frame=-1;
	sprite.scale(2,2);
}	
bool Goomba::move(RenderWindow &window,vector<vector<char> >& world,int dp,int d)
{
	bool w=getCondition(world);
	if(w)
	{
		frame=2;
		Vector2f t=getLWW();
		t.y+=8;
		setLWW(t);
		if(getLWW().y==(getLWM()[1]+1)*32)
		{
			vector<int> tt=getLWM();
			tt[1]++;
			setLWM(tt);
		}
	}
	else
	{
		frame++;
		frame=frame%4;
		vector<int> place(2);
		Vector2f pl(getLWW());
		place[1]=pl.y/32;
		place[0]=pl.x/32;
		float ww=pl.x/32;
		pl.x=pl.x+side*4;
		if(ww==place[0])
		{
			if(world[place[1]][place[0]+side]!='#')
			{
				setLWW(pl);
			}
			else
			{
				side*=-1;
				FOR(i,0,4) image[i].flipHorizontally();
				FOR(i,0,4) texture[i].loadFromImage(image[i]);
				frame=0;
			}
		}
		else
			setLWW(pl);
	}
	Vector2f dr=getLWW();
	dr.x-=32*dp+d;
	dr.y-=32;
	sprite.setPosition(dr);
	sprite.setTexture(texture[frame]);
	if(dr.x<=world.size()*32)
	{
		visibility=true;
		window.draw(sprite);
	}
	else
		visibility=false;
	if(dr.y>=(world.size()-2)*32)
		return true;
	else
		return false;
}
bool Goomba::dead()
{}
Koopa::Koopa(char name,vector<int> &a)
{
	image[0].loadFromFile("k1.png");
	image[1].loadFromFile("k0.png");
	image[2].loadFromFile("k3.png");
	state=0;
	frame=-1;
	if(name=='k') 
	{
		side=-1;
		FOR(i,0,2) image[i].flipHorizontally();
		FOR(i,0,3) texture[i].loadFromImage(image[i]);	
	}
	else 
	{
		side=1;
		FOR(i,0,3) texture[i].loadFromImage(image[i]);
	}
	setLWM(a);
	Vector2f b(a[0]*32,a[1]*32);
	setLWW(b);
	sprite.scale(2,1);
	count=0;
}
bool Koopa::move(RenderWindow &window,vector<vector<char> >& world,int dp,int d)
{
	bool w=getCondition(world);
	if(count==100){ state=0;count=0;}
	if(state==0)
		if(w)
		{
			frame=1;
			Vector2f t=getLWW();
			t.y+=8;
			setLWW(t);
			if(getLWW().y==(getLWM()[1]+1)*32)
			{
				vector<int> tt=getLWM();
				tt[1]++;
				setLWM(tt);
			}
		}
		else
		{
			frame++;
			frame=frame%2;
			vector<int> place(2);
			Vector2f pl(getLWW());
			place[1]=pl.y/32;
			place[0]=pl.x/32;
			float ww=pl.x/32;
			pl.x=pl.x+side*4;
			if(ww==place[0])
			{
				if(world[place[1]][place[0]+side]!='#'&&world[place[1]+1][place[0]+side]=='#')
				{
					setLWW(pl);
				}
				else
				{
					side*=-1;
					FOR(i,0,2) image[i].flipHorizontally();
					FOR(i,0,2) texture[i].loadFromImage(image[i]);
					frame=0;
				}
			}
			else
				setLWW(pl);
		}
	else if(state==1)
	{
		count++;
		frame=2;
	}
	else if(state==2)
	{
		frame=2;
		count++;
		if(w)
		{
			frame=2;
			Vector2f t=getLWW();
			t.y+=8;
			setLWW(t);
			if(getLWW().y==(getLWM()[1]+1)*32)
			{
				vector<int> tt=getLWM();
				tt[1]++;
				setLWM(tt);
			}
		}
		else
		{
			vector<int> place(2);
			Vector2f pl(getLWW());
			place[1]=pl.y/32;
			place[0]=pl.x/32;
			float ww=pl.x/32;
			pl.x=pl.x+side*4;
			if(ww==place[0])
			{
				if(world[place[1]][place[0]+side]!='#')
				{
					setLWW(pl);
				}
				else
				{
					side*=-1;
					FOR(i,0,2) image[i].flipHorizontally();
					FOR(i,0,2) texture[i].loadFromImage(image[i]);
				}
			}
			else
				setLWW(pl);
		}
	}
	Vector2f dr=getLWW();
	dr.x-=32*dp+d;
	dr.y-=32;
	sprite.setPosition(dr);
	sprite.setTexture(texture[frame]);
	if(dr.x<=world.size()*32)
	{
		visibility=true;
		window.draw(sprite);
	}
	else
		visibility=false;
	if(dr.y>=(world.size()-2)*32)
		return true;
	else
		return false;
}
bool Koopa::dead()
{
	if(state==0)
	{
		state=1;
		return false;
	}
	else if(state==1)
	{
		state=2;
		return false;
	}
	else if(state=3)
		return true;
	
}
Monster::Monster(){}
void Monster::create(vector<int>& a)
{
	setLWM(a);
	side=1;
	frame=-1;
	falling=0;
	score=0;
	coin=0;
	Vector2f b(a[0]*32,a[1]*32);
	setLWW(b);
	lastPos=b;
	image[0].loadFromFile("0.png");
	image[1].loadFromFile("1.png");
	image[2].loadFromFile("2.png");
	image[3].loadFromFile("1.png");
	FOR(i,0,4) texture[i].loadFromImage(image[i]);
	sprite.scale(2,2);
	sprite.scale(1,0.8);
	breath=true;
	Win=false;
	Lose=false;
}
void Monster::jumping(vector<vector<char> >& world)
{
	vector<int> place(2);
	Vector2f pl(getLWW());
	place[1]=pl.y/32;
	place[0]=pl.x/32;
	float ww=pl.y/32;
	float wx=pl.x/32;
	if(falling==1)
	{
		frame=2;
		pl.y-=16;
		if(lastPos.y-pl.y<=3.5*32&&pl.y>=32)
			if(ww==place[1])
			{
				if(wx==place[0])
				{
					if(world[place[1]-1][place[0]]!='#')
						setLWW(pl);
					else
						falling=-1;
				}
				else
				{
					if(world[place[1]-1][place[0]]!='#'&&(world[place[1]-1][place[0]+1]!='#'))
						setLWW(pl);
					else
						falling=-1;
				}
			}
			else
			{
				setLWW(pl);
			}
		else
		{
			falling=-1;
			pl.y+=32;
			setLWW(pl);
		}
	}
	else if((falling==-1||falling==0)&&getCondition(world))
	{
		pl.y+=16;
		setLWW(pl);
		frame=2;
	}
	else if(getCondition(world)==0)
	{
		lastPos=pl;
		falling=0;
	}
	
}
void Monster::walking(vector<vector<char> >& world,int& d,int& dp,int direct)
{
	if(getCondition(world))
	{
		frame=2;
	}
	else
	{
		frame++;
		frame=frame%4;
		lastPos=getLWW();
	}
	if(direct!=side)
	{
		FOR(i,0,4) image[i].flipHorizontally();
		FOR(i,0,4) texture[i].loadFromImage(image[i]);
		vector<int> place(getLWM());
		side=direct;
	}
	vector<int> place(2);
	Vector2f pl(getLWW());
	place[1]=pl.y/32;
	place[0]=pl.x/32;
	float ww=pl.x/32;
	/*if(place[1]!=pl.y/32)
		place[1]++;*/
	if(side==1)
	{
		pl.x+=8;
		if(dp>world[0].size()-1-world.size()-1||place[0]-dp<world.size()/3)
		{
			if(ww==place[0]||ww==place[0]+1)
			{
				if(place[1]==pl.y/32||place[1]+1==pl.y/32)
					if(world[place[1]][place[0]+1]!='#')
					{
						setLWW(pl);
					}
				else
					if(world[place[1]][place[0]+1]!='#'&&world[place[1]+1][place[0]+1]!='#')
						setLWW(pl);
			}
			else
			{
				setLWW(pl);
			}
		}
		else
		{
			if(ww==place[0]||ww==place[0]+1)
			{
				if(place[1]==pl.y/32||place[1]+1==pl.y/32)
					if(world[place[1]][place[0]+1]!='#')
					{
						d+=8;
						setLWW(pl);
					}
				else
					if(world[place[1]][place[0]+1]!='#'&&world[place[1]+1][place[0]+1]!='#')
					{
						d+=8;
						setLWW(pl);
					}
			}
			else
			{
				d+=8;
				setLWW(pl);
			}
			if(d>=32)
			{
				d=0;
				dp++;
			}
			if(d<=-32)
			{
				d=0;
				dp--;
			}
		}
	}
	else
	{
		pl.x-=8;
		if(dp<1||place[0]-dp>=2*(world.size()/3))
		{
			if(ww==place[0]||ww==place[0]+1)
			{
				if(place[1]==pl.y/32||place[1]+1==pl.y/32)
					if(world[place[1]][place[0]-1]!='#')
					{
						setLWW(pl);
					}
				else
					if(world[place[1]][place[0]-1]!='#'&&world[place[1]+1][place[0]-1]!='#')
						setLWW(pl);
			}
			else
			{
				setLWW(pl);
			}
		}
		else
		{
			if(ww==place[0]||ww==place[0]+1)
			{
				if(place[1]==pl.y/32||place[1]+1==pl.y/32)
					if(world[place[1]][place[0]-1]!='#')
					{
						d-=8;
						setLWW(pl);
					}
				else
					if(world[place[1]][place[0]-1]!='#'&&world[place[1]+1][place[0]-1]!='#')
					{
						d-=8;
						setLWW(pl);
					}
			}
			else
			{
				d-=8;
				setLWW(pl);
			}
			if(d>=32)
			{
				d=0;
				dp++;
			}
			if(d<=-32)
			{
				d=0;
				dp--;
			}
		}
	}
	if(getLWW().x<0)
	{
		Vector2f tr(getLWW());
		tr.x=0;
		setLWW(tr);
	}
	if(getLWW().x>=(world[0].size()-2)*32-64)
	{
		Vector2f tr(getLWW());
		tr.x=(world[0].size()-2)*32-64;
		setLWW(tr);
	}
}
void Monster::move(vector<vector<char> > &world,int&d,int&dp,int direct)
{
	if(direct==0)
	{
		frame=0;	
	}
	else
		walking(world,d,dp,direct);
	jumping(world);	
	Vector2f dr=getLWW();
	dr.x=dr.x-(32*dp+d);
	dr.y-=32;
	if(dr.y>=(world.size()-2)*32)
		lose();
	sprite.setPosition(dr);
	sprite.setTexture(texture[frame]);
}
int Monster::accident(vector<vector<char> > & world,Princess &princess,vector<Goomba> & goomba,vector<Koopa> & koopa,vector<Coin> & coin)
{
	Vector2f place=getLWW();
	float LH=place.x-32,HH=place.x+32,LW=place.y+32,HW=place.y-32;
	int i=0,j=0,k=0;
	while(i<goomba.size()||j<koopa.size()||k<coin.size())
	{
		if(i<goomba.size()&&goomba[i].visibility)
		{
			Vector2f enemy(goomba[i].getLWW());
			if((enemy.x==LH||enemy.x==HH)&&(HW<enemy.y&&enemy.y<LW))
				lose();
			if(enemy.y==HW&&(LH<enemy.x&&enemy.x<HH))
				lose();
			if((LH<enemy.x&&enemy.x<HH)&&(HW<enemy.y&&enemy.y<LW))
				lose();
			if((LH<=enemy.x&&enemy.x<=HH)&&(enemy.y==LW)&&getCondition(world))
			{
				setScore(getScore()+100);
				lastPos=enemy;
				falling=1;
				goomba.erase(goomba.begin()+i);
				i--;
			}
		}
		if(j<koopa.size()&&koopa[j].visibility)
		{
			Vector2f enemy(koopa[j].getLWW());
			if((enemy.x==LH||enemy.x==HH)&&(HW<enemy.y&&enemy.y<LW))
				lose();
			if(enemy.y==HW&&(LH<enemy.x&&enemy.x<HH))
				lose();
			if((LH<enemy.x&&enemy.x<HH)&&(HW<enemy.y&&enemy.y<LW))
				lose();
			if((LH<=enemy.x&&enemy.x<=HH)&&(enemy.y==LW)&&getCondition(world))
			{
				setScore(getScore()+150);
				lastPos=enemy;
				falling=1;
				if(koopa[j].dead())
					{
						setScore(getScore()+250);
						koopa.erase(koopa.begin()+i);
						j--;
					}
			}
		}
		if(k<coin.size()&&coin[k].visibility)
		{
			Vector2f ccoin(coin[k].LWW);
			//cout<<coin[k].getMoney()<<endl;
			if(ccoin.y==HW&&(LH<ccoin.x&&ccoin.x<HH)&&coin[k].full)
				setCoin(getCoin()+coin[k].getMoney());
		}
		if(princess.visibility)
		{
			Vector2f p(princess.LWW);
			if(((p.x==LH||p.x==HH)&&(HW<p.y&&p.y<LW))||((p.y>=HW||p.y<=LW)&&(LH<=p.x&&p.x<=HH)))
				win();
		}
		i++;
		j++;
		k++;
	}
}
unsigned int Monster::getScore(){	return score;	}
void Monster::setScore(unsigned int t){	score=t; }
int Monster::getCoin(){	return coin;	}
void Monster::setCoin(int t){	coin=t; }
void Monster::lose()
{
	if(score<10000){
		breath=false;
		Lose=true;
	}
	else
		score-=10000;
}
void Monster::win()
{
	breath=false;
	Win=true;
}
