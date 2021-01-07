#include <SFML/Graphics.hpp>
#include <vector>
#define FOR(i,min,max) for(int i=(min);i<(max);i++)
using namespace sf;
using namespace std;
class Alive
{
	public:
		Alive();
		Alive(vector<int>&);
		void setLWW(Vector2f &);
		Vector2f & getLWW();
		void setLWM(vector<int> &);
		vector<int> & getLWM();
		bool getCondition(vector<vector<char> >&);
		int side;
		int frame;
	private:
		Vector2f LWW;
		vector<int> LWM;
		bool condition;
};
class nonAlive
{
	public:
		bool visibility;
		int frame;
		Image image[4];
		Texture texture[4];
		Sprite sprite;
		Vector2f LWW;
		virtual void show(RenderWindow &window,vector<vector<char> >& world,int,int)=0;
};
class Princess:public nonAlive
{
	public:
		void create(vector<int>&);
		virtual void show(RenderWindow &window,vector<vector<char> >& world,int,int);
};
class Coin: public nonAlive
{
	public:
		bool full;
		Coin(vector<int>&);
		int getMoney();
		virtual void show(RenderWindow &window,vector<vector<char> >& world,int,int);
	private:
		int money;
};
class Enemy: public Alive
{
	public:
		bool visibility;
		virtual bool move(RenderWindow &window,vector<vector<char> >&,int,int)=0;
		Image image[5];
		Texture texture[5];
		Sprite sprite;
};
class Goomba: public Enemy 
{
	public:
		Goomba(char,vector<int>&);
		virtual bool move(RenderWindow &window,vector<vector<char> >&,int,int);
		virtual bool dead();
};
class Koopa: public Enemy
{
	public:
		int state;
		int count;
		Koopa(char,vector<int>&);
		virtual bool move(RenderWindow &window,vector<vector<char> >&,int,int);
		virtual bool dead();
};
class Monster: public Alive
{
	public:
		Monster();
		Vector2f lastPos;
		int falling;
		bool breath;
		bool Win;
		bool Lose;
		Image image[4];
		Texture texture[4];
		Sprite sprite;
		//bool getCondition(vector<vector<char> > &);
		void create(vector<int>&);
		unsigned int getScore();
		void setScore(unsigned int);
		int getCoin();
		void setCoin(int);
		void jumping(vector<vector<char> >&);
		void walking(vector<vector<char> > &,int&,int&,int);
		void move(vector<vector<char> > &,int&,int&,int);
		int accident(vector<vector<char> > & world,Princess &princess,vector<Goomba> &,vector<Koopa> &,vector<Coin> &);
		void lose();
		void win();
	private:
		unsigned int score;
		int coin;
};
