#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include "object.cpp"
using namespace std;
using namespace sf;
string codeOfPic(int x,int y,vector<vector<char> > &);
void normalUpdate(RenderWindow &window,vector<vector<char> > & world,vector<Goomba> &goomba,vector<Koopa> &koopa,vector<Coin>&coin,int& d,int &dp);
int main()
{
	int x,y,dp,d=0;;
	ifstream cinp("t7",ios::in);
	cinp>>x>>y;
	//cin>>x>>y;
	vector<vector<char> > world(x+2);
	Monster mario;
	vector<Goomba> goomba;
	vector<Koopa> koopa;
	vector<Coin> coin; 
	Princess princess;
	vector<int> pos(2);
	FOR(i,1,x+1)
		FOR(j,1,y+1)
		{
			char a;
			cinp>>a;
			//cin>>a;
			pos[0]=j;
			pos[1]=i;
			if(a=='s')
			{
				mario.create(pos);
				dp=j-1;
			}
			if(a=='g'||a=='G')
			{
				Goomba t(a,pos);
				goomba.insert(goomba.end(),t);
			}
			if(a=='k'||a=='K')
			{
				Koopa t(a,pos);
				koopa.insert(koopa.end(),t);
			}
			if(a=='m'||a=='c')
			{
				a='#';
				Coin t(pos);
				coin.insert(coin.end(),t);
			}
			if(a=='e')
			{
				a='.';
				princess.create(pos);
			}
			world[i].insert(world[i].end(),a);
		}
	FOR(i,0,y)
	{
		world[0].insert(world[0].end(),world[1][i]);
		world[x+1].insert(world[x+1].end(),world[x][i]);
	}
	FOR(i,0,x+2)
	{
		world[i].insert(world[i].begin(),world[i][0]);
		world[i].insert(world[i].end(),world[i][world[i].size()-1]);
	}
	/*FOR(i,1,x+1){
		FOR(j,1,y+1)
			cout<<world[i][j];
		cout<<endl;
	}*/
	RenderWindow fwindow(VideoMode(320,320),"MARIO");fwindow.setPosition(Vector2i(300,100));
	Font font;font.loadFromFile("calibri.ttf");
	Text Tscore("score ",font),Nscore,Tcoin("coin ",font),Ncoin;
	Tscore.setCharacterSize(19);Tscore.setColor(Color::Yellow);
	Nscore.setCharacterSize(19);Nscore.setColor(Color::Yellow);
	Tcoin.setCharacterSize(19);Tcoin.setColor(Color::Yellow);
	Ncoin.setCharacterSize(19);Ncoin.setColor(Color::Yellow);
	Tcoin.setPosition(10,0);Tscore.setPosition(200,0);
	Ncoin.setFont(font);Nscore.setFont(font);
	Ncoin.setPosition(50,0);Nscore.setPosition(250,0);
	bool start=true;
	Image image[2];
	Texture texture[2];image[0].loadFromFile("bt2.png");image[1].loadFromFile("bt1.png");
	Sprite ss;ss.setPosition(113,130);
	FOR(i,0,2) texture[i].loadFromImage(image[i]);
	Image animation[18];
	animation[0].loadFromFile("a1.png");animation[1].loadFromFile("a2.png");animation[2].loadFromFile("a8.png");
	animation[3].loadFromFile("a3.png");animation[4].loadFromFile("a5.png");animation[5].loadFromFile("a6.png");
	animation[6].loadFromFile("a7.png");animation[7].loadFromFile("a4.png");animation[8].loadFromFile("a9.png");
	animation[9].loadFromFile("a10.png");animation[10].loadFromFile("a9.png");animation[11].loadFromFile("a4.png");
	animation[12].loadFromFile("a7.png");animation[13].loadFromFile("a6.png");animation[14].loadFromFile("a5.png");
	animation[15].loadFromFile("a3.png");animation[16].loadFromFile("a8.png");animation[17].loadFromFile("a2.png");
	Texture tanimation[18];
	FOR(i,0,18) tanimation[i].loadFromImage(animation[i]);
	Clock anim;
	int animf=0;
	Font pfont;pfont.loadFromFile("CANDY___.otf");Text play("play",font);play.setCharacterSize(50);play.setPosition(118,120);
	while(fwindow.isOpen()&&start)
	{
		Event e;	
		while(fwindow.pollEvent(e))
			if(e.type==Event::Closed)
				fwindow.close();
		if (Mouse::isButtonPressed(Mouse::Left)&& (113<Mouse::getPosition(fwindow).x&&Mouse::getPosition(fwindow).x<113+94)&&(130<Mouse::getPosition(fwindow).y&&Mouse::getPosition(fwindow).y<130+57) )
		{
			ss.setTexture(texture[0]);
			start=false;
			fwindow.close();					
		}
		else
			ss.setTexture(texture[1]);					
		Sprite s;
		s.setPosition(160-31,10);
		s.scale(3,3);
		if(anim.getElapsedTime().asSeconds()>=1.f/8)
		{
			fwindow.clear();
			Text me("programmed by amirhosein kazeminia",pfont);
			me.setPosition(50,280);
			fwindow.draw(me);
			fwindow.draw(ss);
			s.setTexture(tanimation[animf]);
			fwindow.draw(s);
			fwindow.draw(play);
			animf++;
			animf=animf%16;
			anim.restart();
		}
		fwindow.display();
	}
	RenderWindow window(VideoMode(x*32,x*32),"MARIO");window.setPosition(Vector2i(300,100));
	Clock c;
	while(window.isOpen()&&mario.breath&&start==false)
	{
		Event e;
		while(window.pollEvent(e))
			if(e.type==Event::Closed)
				window.close();
		int f=0;
		Time t=c.getElapsedTime();
		if(t.asSeconds()>=1.f/15)
		{
			if(Keyboard::isKeyPressed(Keyboard::Right))
			{
				f=1;
			}
			if(Keyboard::isKeyPressed(Keyboard::Left))
			{
				f=-1;
			}
			if(mario.getCondition(world)==0&&Keyboard::isKeyPressed(Keyboard::Space))
				mario.falling=1;
			mario.move(world,d,dp,f);
			normalUpdate(window,world,goomba,koopa,coin,d,dp);
			mario.accident(world,princess,goomba,koopa,coin);
			princess.show(window,world,dp,d);
			window.draw(mario.sprite);
			Ncoin.setString(static_cast<ostringstream*>(&(ostringstream()<<mario.getCoin()))->str());
			Nscore.setString(static_cast<ostringstream*>(&(ostringstream()<<mario.getScore()))->str());
			window.draw(Tcoin);window.draw(Tscore);
			window.draw(Ncoin);window.draw(Nscore);
			window.display();
			c.restart();
		}
	}
	window.close();
	RenderWindow ewindow(VideoMode(490,320),"MARIO");ewindow.setPosition(Vector2i(300,100));
	Image end[6];
	end[0].loadFromFile("e.png");end[1].loadFromFile("ek.png");end[2].loadFromFile("ed1.png");end[3].loadFromFile("ed2.png");
	end[4].loadFromFile("end.png");end[5].loadFromFile("enk.png");
	Texture tend[6];
	FOR(i,0,6) tend[i].loadFromImage(end[i]);
	Text exit("exit",font);exit.setCharacterSize(50);
	if(mario.Win)
	{
		string win1="you win! and find your princess";
		string win2;
		Text ending1;
		Text ending2;
		ending1.setFont(font);
		ending2.setFont(font);
		if(mario.getCoin()<0)
		{
			win2="unfortnetly U couldn't catch enough coin :(( \n and U should give me ";
			win2+=static_cast<ostringstream*>(&(ostringstream()<<-mario.getCoin()))->str();
			win2+=" coin";
			ending2.setCharacterSize(30);
		}
		else
		{
			win2="and you got ";
			win2+=static_cast<ostringstream*>(&(ostringstream()<<mario.getCoin()))->str();
			win2+=" coin";
		}
		ending1.setString(win1);
		ending2.setString(win2);
		ending1.setPosition(30,0);
		ending2.setPosition(40,180);
		while(ewindow.isOpen())
		{
			ewindow.clear();
			if (Mouse::isButtonPressed(Mouse::Left)&& (390<Mouse::getPosition(ewindow).x&&Mouse::getPosition(ewindow).x<390+94)&&(260<Mouse::getPosition(ewindow).y&&Mouse::getPosition(ewindow).y<260+57) )
			{
				ewindow.close();					
			}
			ss.setTexture(texture[1]);
			ss.setPosition(390,260);
			exit.setPosition(390+7,254);
			ewindow.draw(ss);
			ewindow.draw(exit);
			ewindow.draw(ending1);
			ewindow.draw(ending2);
			Sprite s[4];
			s[0].scale(2,2);s[1].scale(2,2);s[2].scale(2,2);s[3].scale(2,2);
			s[2].setTexture(tend[0]);
			s[2].setPosition(185,250);
			ewindow.draw(s[2]);
			s[3].setTexture(tend[5]);
			s[3].setPosition(150,100);
			ewindow.draw(s[3]);
			ewindow.display();
		}
	}
	if(mario.Lose)
	{
		string win1="you lose! and you miss your princess!";
		string win2;
		Text ending1;
		Text ending2;
		ending1.setFont(font);
		ending2.setFont(font);
		if(mario.getCoin()<0)
		{
			win2="and unfortnetly U couldn't catch enough coin :(( \n and U should give me ";
			win2+=static_cast<ostringstream*>(&(ostringstream()<<-mario.getCoin()))->str();
			win2+=" coin";
			ending2.setCharacterSize(20);
		}
		else
		{
			win2="but you got ";
			win2+=static_cast<ostringstream*>(&(ostringstream()<<mario.getCoin()))->str();
			win2+=" coin";
		}
		ending1.setString(win1);
		ending2.setString(win2);
		ending1.setPosition(18,0);
		ending2.setPosition(10,160);
		while(ewindow.isOpen())
		{
			ewindow.clear();
			if (Mouse::isButtonPressed(Mouse::Left)&& (390<Mouse::getPosition(ewindow).x&&Mouse::getPosition(ewindow).x<390+94)&&(260<Mouse::getPosition(ewindow).y&&Mouse::getPosition(ewindow).y<260+57) )
			{
				ewindow.close();					
			}
			ss.setTexture(texture[1]);
			ss.setPosition(390,260);
			exit.setPosition(390+7,254);
			ewindow.draw(ss);
			ewindow.draw(exit);
			ewindow.draw(ending1);
			ewindow.draw(ending2);
			Sprite s[4];
			s[0].scale(2,2);s[1].scale(2,2);s[2].scale(2,2);s[3].scale(2,2);
			s[2].setTexture(tend[2]);
			s[2].setPosition(185,250);
			ewindow.draw(s[2]);
			s[3].setTexture(tend[2]);
			s[3].setPosition(100,400);
			ewindow.draw(s[3]);
			ewindow.display();
		}
	}
	return 0;
}
string codeOfPic(int x,int y,vector<vector<char> > & world)
{
	string answer;
	int a[5][2]={-1,-1,-1,0,-1,1,0,-1,0,1};
	if(world[x][y]=='#')
		FOR(i,0,5)
		{
 			if(world[x+a[i][0]][y+a[i][1]]=='#')
				answer=answer+"1";
			else
				answer=answer+"0";
		}
	else
		answer+="null";
	answer+=".png";
	return answer;
}
void normalUpdate(RenderWindow &window,vector<vector<char> > & world,vector<Goomba> &goomba,vector<Koopa>&koopa,vector<Coin> &coin,int& d,int &dp)
{
	window.clear();
	Image image;
	Texture t;
	int x=world.size()-2,y=world[0].size()-2;
	FOR(i,1,x+1)
		for(int j=((dp-1>=0)?dp-2:0);j<x+dp+2;j++)
		{
			image.loadFromFile(codeOfPic(i,j,world));
			t.loadFromImage(image);
			Sprite s(t);
			s.setPosition((j-dp)*32-d,(i-1)*32);
			s.scale(2,2);
			window.draw(s);
		}
	FOR(i,0,coin.size()) coin[i].show(window,world,dp,d);
	FOR(i,0,goomba.size()) 
		if(goomba[i].move(window,world,dp,d))
		{
			goomba.erase(goomba.begin()+i);
			i--;
		}
	FOR(i,0,koopa.size()) 
		if(koopa[i].move(window,world,dp,d))
		{
			koopa.erase(koopa.begin()+i);
			i--;
		}
}
