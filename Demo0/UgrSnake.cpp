////
// Un comment the code and run the snake game!
////

//#include <Windows.h>
//#include <UgrCGL.hpp>
//#include <map>
//#pragma warning(disable:4996)
//using namespace ugr;
//Vector2i g_ScreenSize;
//class State
//{
//public:
//	enum class States
//	{
//		Exit = 0, MainMenu, Game
//	};
//	State(ConsoleWindow* CW) :m_CW(CW) {}
//	inline virtual void OnCreate() = 0;
//	inline virtual void OnUpdate(const float& dt) = 0;
//	inline virtual void OnRender() = 0;
//	inline virtual States ReturnStateValue() = 0;
//	bool m_bQuit = false;
//	ConsoleWindow* m_CW;
//};
//
//class Game : public State
//{
//public:
//	Game(ConsoleWindow* CW) : State(CW), direction(Direction::UP) {}
//	inline void OnCreate() override
//	{
//		this->player.pos = { 10, 10 };
//		this->player.cp.Char.UnicodeChar = 0x2588;
//		this->player.cp.Color = 0x88;
//		this->player.TailLength = 2;
//
//		this->food = { 10, 5 };
//	}
//	inline void OnUpdate(const float& dt) override
//	{
//		if (this->m_CW->Keyboard(0x1B).bStrokeReleased)
//		{
//			this->m_State = States::Exit;
//			this->m_bQuit = true;
//		}
//
//		if (this->m_CW->Keyboard(0x25).bStrokePressed) this->direction = Direction::LEFT;
//		if (this->m_CW->Keyboard(0x27).bStrokePressed) this->direction = Direction::RIGHT;
//		if (this->m_CW->Keyboard(0x26).bStrokePressed) this->direction = Direction::UP;
//		if (this->m_CW->Keyboard(0x28).bStrokePressed) this->direction = Direction::DOWN;
//
//		switch (direction)
//		{
//		case Game::Direction::UP:
//			this->player.pos.y--;
//			break;
//		case Game::Direction::DOWN:
//			this->player.pos.y++;
//			break;
//		case Game::Direction::LEFT:
//			this->player.pos.x--;
//			break;
//		case Game::Direction::RIGHT:
//			this->player.pos.x++;
//			break;
//		default:
//			break;
//		}
//		Vector2i prev = this->player.tail[0];
//		Vector2i prev2;
//		this->player.tail[0] = this->player.pos;
//		for (int i = 0; i < this->player.TailLength; i++)
//		{
//			prev2 = this->player.tail[i];
//			this->player.tail[i] = prev;
//			prev = prev2;
//		}
//		if (this->player.pos.x == this->food.x && this->player.pos.y == this->food.y)
//		{
//			this->food = { rand() % g_ScreenSize.x, rand() % g_ScreenSize.y };
//			this->player.TailLength++;
//		}
//		if (this->player.pos.x >= g_ScreenSize.x) this->player.pos.x = 0; else if (this->player.pos.x <= 0) this->player.pos.x = g_ScreenSize.x - 1;
//		if (this->player.pos.y >= g_ScreenSize.y)  this->player.pos.y = 0; else if (this->player.pos.y <= 0) this->player.pos.y = g_ScreenSize.y - 1;
//
//	}
//	inline void OnRender() override
//	{
//		for (INT i = 1; i < this->player.TailLength; i++)
//		{
//			this->m_CW->SetPixel(this->player.tail[i], 0x2588, 0x11);
//		}
//		this->m_CW->SetPixel(this->player.pos, this->player.cp.Char.UnicodeChar, this->player.cp.Color);
//		this->m_CW->SetPixel(this->food, 0x2588, 0x22);
//	}
//	inline States ReturnStateValue() override
//	{
//		return this->m_State;
//	}
//	struct
//	{
//		Vector2i pos{};
//		CharPixel cp{};
//		INT TailLength = 0;
//		Vector2i tail[100]{};
//	}player;
//	enum class Direction
//	{
//		UP = 0, DOWN, LEFT, RIGHT
//	}direction;
//	Vector2i food;
//	State::States m_State;
//};
//
//class MainMenu : public State
//{
//public:
//	MainMenu(ConsoleWindow* CW) : State(CW) 
//	{
//		this->m_CW->SetFullScreen(false);
//		this->m_CW->ShutDown();
//		this->m_CW->InitConsoleWindow();
//		this->m_CW->CreateConsoleBufferWindow(Vector2i(240, 120), Vector2i(8, 8));
//	}
//	~MainMenu() {}
//	inline void OnCreate() override
//	{
//
//	}
//	inline void OnUpdate(const float& dt) override
//	{
//		if (this->m_CW->Keyboard(0x1B).bStrokeReleased)
//		{
//			this->m_bQuit = true;
//		}
//	}
//	inline void OnRender() override
//	{
//
//	}
//	inline State::States ReturnStateValue() override
//	{
//		return State::States::Exit;
//	}
//};
//
//class Application : private ConsoleWindow
//{
//public:
//	Application()
//	{
//		
//		g_ScreenSize = { 30, 16 };
//		this->InitConsoleWindow();
//		this->CreateConsoleBufferWindow(g_ScreenSize, Vector2i(64, 64));
//		this->SetFullScreen(true);
//
//		this->m_mapStates.insert(std::make_pair<State::States, State*>(State::States::Game, new Game(this)));
//		this->m_mapStates[State::States::Game]->OnCreate();
//
//		/*this->m_mapStates.insert(std::make_pair<State::States, State*>(State::States::MainMenu, new MainMenu(this)));
//		this->m_mapStates[State::States::MainMenu]->OnCreate();*/
//
//		this->m_currentState = State::States::Game;
//	}
//	~Application()
//	{
//		if (!this->m_mapStates.empty())
//		{
//			for (std::map<State::States, State*>::iterator it = this->m_mapStates.begin(); it != this->m_mapStates.end(); it++)
//			{
//				delete it->second;
//			}
//			this->m_mapStates.clear();
//		}
//		this->ShutDown();
//	}
//	void run()
//	{
//		char buffer[128]{};
//		while (this->m_bIsRunning)
//		{
//			this->ProcessFPS();
//			this->ProcessEvents();
//			SetConsoleTitleA(itoa(this->GetFPS(), buffer, 10));
//
//			if (!this->m_mapStates.empty())
//			{
//				if (this->m_mapStates[m_currentState]->m_bQuit)
//				{
//					this->ManageStates();
//				}
//			}
//			else
//			{
//				this->m_bIsRunning = false;
//			}
//
//			if (!this->m_mapStates.empty())
//				this->m_mapStates[this->m_currentState]->OnUpdate(this->dt);
//
//			this->ClearScreen();
//
//			if (!this->m_mapStates.empty())
//				this->m_mapStates[this->m_currentState]->OnRender();
//
//			this->Display();
//			_sleep(50);
//		}
//	}
//private:
//	inline void ManageStates()
//	{
//		switch (this->m_mapStates[this->m_currentState]->ReturnStateValue())
//		{
//		default:
//			break;
//		case State::States::Game:
//			break;
//
//		case State::States::Exit:
//			for (std::map<const State::States, State*>::iterator it = this->m_mapStates.begin(); it != this->m_mapStates.end(); it++)
//				delete it->second;
//			this->m_mapStates.clear();
//		}
//	}
//	bool m_bIsRunning = true;
//	std::map<State::States, State*> m_mapStates;
//	State::States m_currentState;
//};
//
//int main()
//{
//	Application app;
//	app.run();
//}