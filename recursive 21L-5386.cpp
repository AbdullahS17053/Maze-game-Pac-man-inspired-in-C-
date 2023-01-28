//#include<iostream>
//#include <windows.h>
//#include <conio.h>
//#include <fstream>
//using namespace std;
//
//#define KEY_UP 72
//#define KEY_DOWN 80
//#define KEY_LEFT 75
//#define KEY_RIGHT 77
//#define VK_KEY_Q 113
//
//class position// class to hold co-ordinates and room number
//{
//private:
//
//	int x;
//	int y;
//	int roomnum;
//	friend class maze;
//
//public:
//
//	position()
//	{
//		x = y = roomnum = 0;
//	}
//
//	position(int xcoord, int ycoord, int r)
//	{
//		x = xcoord;
//		y = ycoord;
//		roomnum = r;
//	}
//
//	void print()
//	{
//		cout << x << "\t " << y << "\t   " << roomnum;
//	}
//};
//
//
//template <class type>
//class stack
//{
//
//private:
//
//	class node
//	{
//
//	public:
//
//		type data;
//		node* next;
//		node()
//		{
//
//		}
//		node(type v, node* ptr)
//		{
//			data = v;
//			next = ptr;
//		}
//		node(type* v, node* ptr)
//		{
//			data = *v;
//			next = ptr;
//		}
//		~node()
//		{
//
//		}
//
//
//	};
//	node* head;
//	node* tail;
//
//public:
//
//	stack()
//	{
//		head = tail = NULL;
//	}
//
//	void push(type element)
//	{
//		if (tail == NULL)
//		{
//			head = tail = new node(element, NULL);
//
//		}
//		else
//		{
//			tail->next = new node(element, NULL);
//			tail = tail->next;
//
//		}
//	}
//
//	void pop()
//	{
//		if (head == NULL)
//		{
//			return;
//		}
//		else if (head == tail)
//		{
//			delete head;
//			head = tail = NULL;
//		}
//		else
//		{
//			node* temp = head;
//			for (; temp->next != tail; temp = temp->next);
//			delete tail;
//			tail = temp;
//			tail->next = NULL;
//		}
//	}
//
//	bool isEmpty()
//	{
//		return head == NULL;
//	}
//
//	void print()//print path
//	{
//		node* temp = head;
//		
//		for (; temp != NULL; temp = temp->next)
//		{
//			temp->data.print();
//			cout << endl;
//		}
//		cout << endl;
//	}
//
//	type top()
//	{
//		if (tail != NULL)
//		{
//			return tail->data;
//		}
//	}
//
//	type prev()
//	{
//		node* temp = head;
//		for (; temp->next != tail; temp = temp->next);
//		return temp->data;
//	}
//
//	~stack()
//	{
//		while (head != NULL)
//		{
//			pop();
//		}
//	}
//
//};
//
//
//class room
//{
//
//private:
//
//	friend class maze;
//	int x;//starting co ordinates
//	int y;
//	int rows;
//	int columns;
//	char** map;
//	bool treasure;//has treasure or not
//
//public:
//
//	room()
//	{
//		x = y = rows = columns = treasure = 0;
//		map = NULL;
//	}
//
//	void loadData(ifstream& fin)//loads rooms text file
//	{
//		int i, j, counter = 0;
//		fin >> rows;
//		fin >> columns;
//		fin >> x;
//		fin >> y;
//		map = new char* [rows];
//		for (i = 0; i < rows; i++)
//		{
//			map[i] = new char[columns];
//		}
//		for (i = 0; i < rows; i++)
//		{
//			for (j = 0; j < columns; j++)
//			{
//				fin >> map[i][j];
//				if (map[i][j] == 'T')
//				{
//					treasure = true;
//				}
//			}
//		}
//	}
//
//	bool isWall(int xpos, int ypos)
//	{
//		return map[xpos][ypos] == 'X';
//	}
//
//	void print(int xpos, int ypos)
//	{
//		system("cls");
//		for (int i = 0; i < rows; i++)
//		{
//			for (int j = 0; j < columns; j++)
//			{
//				if (i == xpos && j == ypos)
//				{
//					cout << " *  ";
//				}
//				else if (map[i][j] == 'X')
//				{
//					cout << "|_| ";
//
//				}
//				else
//				{
//					cout << " -  ";
//				}
//			}
//			cout << endl;
//		}
//	}
//
//	~room()
//	{
//		int i;
//		for (i = 0; i < rows; i++)
//		{
//			delete[]  map[i];
//		}
//		delete[] map;
//	}
//
//};
//
//
//class maze
//{
//
//private:
//
//	int x;//current position of player
//	int y;
//	stack<int> currentroom;//stack to hold current room
//	stack<position>* currentpos;//stack to hold current position
//	int totalrooms;
//	room* rooms;//pointer to hold all rooms
//	bool gasper = false;
//	position portalTemp;
//
//public:
//
//	maze()
//	{
//		x = y = totalrooms = 0;
//		rooms = NULL;
//		srand((unsigned)(time(0)));
//		currentpos = new stack<position>;
//	}
//
//	void loadRooms()//opens hauntedhouse.txt and loads all subsequent room files in loop
//	{
//		int i;
//		string tempfile, map;
//		ifstream fin("hauntedhouse.txt"), fin1;
//		fin >> totalrooms;
//		rooms = new room[totalrooms];
//		for (i = 0; i < totalrooms; i++)
//		{
//			fin >> tempfile;
//			fin1.open(tempfile);
//			rooms[i].loadData(fin1);
//			fin1.close();
//		}
//		i = rand() % (totalrooms);
//		currentroom.push(i + 1);
//		currentpos->push(position(rooms[i].x, rooms[i].y, i + 1));
//		x = rooms[i].x;
//		y = rooms[i].y;
//		rooms[i].print(x, y);
//
//	}
//
//	void play(int& recurse)//recurse is always 0, only set to 1 if function recurses
//	{
//		int c;
//		
//		if (checkDevil() == true || checkTres() == true)//end game
//		{
//			return;
//		}
//
//		if (rooms[currentroom.top() - 1].map[x][y] == 'P' && gasper == true)
//		{
//			cout << "\n\nIt seems you have stepped on a portal after you just found a gasper....and are dealt with for your folly! So very sorry.\n\n";
//			return;
//		}
//
//		if (checkPortal() == true)//pop top room and recurse function back
//		{
//			currentroom.pop();
//			recurse = 1;
//			return;
//		}
//
//		checkGhost();
//
//		c = 0;
//
//			switch ((c = _getch()))
//			{
//
//			case KEY_UP:
//				if (x > 0 && rooms[currentroom.top() - 1].map[x - 1][y] != 'X')
//				{
//					x = x - 1;
//					currentpos->push(position(x, y, currentroom.top()));
//					rooms[currentroom.top() - 1].print(x, y);
//				}
//				break;
//			case KEY_DOWN:
//				if (x < rooms[currentroom.top() - 1].rows - 1 && rooms[currentroom.top() - 1].map[x + 1][y] != 'X')
//				{
//					x = x + 1;
//					currentpos->push(position(x, y, currentroom.top()));
//					rooms[currentroom.top() - 1].print(x, y);
//				}
//				break;
//			case KEY_LEFT:
//				if (y > 0 && rooms[currentroom.top() - 1].map[x][y - 1] != 'X')
//				{
//					y = y - 1;
//					currentpos->push(position(x, y, currentroom.top()));
//					rooms[currentroom.top() - 1].print(x, y);
//				}
//				break;
//			case KEY_RIGHT:
//				if (y < rooms[currentroom.top() - 1].columns - 1 && rooms[currentroom.top() - 1].map[x][y + 1] != 'X')
//				{
//					y = y + 1;
//					currentpos->push(position(x, y, currentroom.top()));
//					rooms[currentroom.top() - 1].print(x, y);
//				}
//				break;
//			case VK_KEY_Q:
//				cout << "\n\nThank you for playing!\n";
//				return;
//			default:
//				break;
//			}
//			play(recurse);
//			if (recurse == 1)//recursion caught here
//			{
//				if (currentroom.isEmpty())
//				{
//					cout << "\n\nOh no! It seems you have stepped on a portal....and are kicked from the game! So very sorry.\n\n";
//					recurse = 0;
//					return;
//				}
//				else if (!currentroom.isEmpty())
//				{
//					int r = currentroom.top() - 1;// change room to previous room
//					x = portalTemp.x;
//					y = portalTemp.y;
//					portalTemp = currentpos->prev();
//					currentpos->push(position(x, y, r + 1));
//					rooms[r].print(x, y);
//					cout << "\n\nOh no! It seems you have stepped on a portal....and are teleported to the previous room!\n\n";
//					recurse = 0;
//					play(recurse);
//				}
//			}
//			
//			
//	}
//
//	void changeRooms(int r)//change room given room number, r is generated randomly for random starting, teleporting etc
//	{
//		srand((unsigned)(time(0)));
//		do
//		{
//			x = rand() % rooms[r].rows;
//			y = rand() % rooms[r].columns;
//		} 
//		while (rooms[r].map[x][y] != '0');
//		currentroom.push(r + 1);
//		currentpos->push(position(x, y, r + 1));
//		rooms[r].print(x, y);
//	}
//
//	bool checkDevil() //check to kill person if they land on 'D'
//	{
//		if (rooms[currentroom.top() - 1].map[x][y] == 'D')
//		{
//			cout << "\n\nOh no! It seems a devil has found you....and eaten you up alive. Oh well, thank you for playing!\n\n";
//			return true;
//		}
//		return false;
//	}
//
//	void checkGhost()//check to teleport person to room with treasure if they land on 'G'
//	{
//		int i = 0;
//		if (rooms[currentroom.top() - 1].map[x][y] == 'G')
//		{
//			gasper = true;
//			for (i = 0; i < totalrooms; i++)
//			{
//				if (rooms[i].treasure == true)
//				{
//					changeRooms(i);
//					break;
//				}
//			}
//			cout << "\n\nOh no! It seems a Ghost has found you....and teleported you to the treasure room! Goodluck...\n\n";
//		}
//	}
//
//	bool checkPortal()//check to see if person lands on 'P'
//	{
//		int num = currentroom.top() - 1;
//		if (rooms[currentroom.top() - 1].map[x][y] == 'P')
//		{
//			srand((unsigned)(time(0)));
//
//			if (rand() % (2) == 0)//heads
//			{
//				while (num == currentroom.top() - 1)
//				{
//					num = rand() % (totalrooms);
//				}
//				portalTemp = currentpos->prev();
//				changeRooms(num);
//				cout << "\n\nOh no! It seems you have stepped on a portal....and are teleported to a random room!\n\n";
//				return false;
//			}
//			else//tails
//			{
//				return true;
//			}
//
//		}
//		return false;
//		
//	}
//
//	bool checkTres()//check to end game if person lands on 'T'
//	{
//		if (rooms[currentroom.top() - 1].map[x][y] == 'T')
//		{
//			cout << "\n\nCongratulations! You have found the treasure and....are still alive! We hope you visit us again!\n\n";
//			cout << "Co-ordinates of treasure: \n\n" << "x   \t y  \t room  \n\n";
//			currentpos->top().print();//print co-ordinates of treasure
//			cout << endl << endl;
//			currentpos->pop();
//			cout << "Path taken until treasure is reached: \n\n" << "x \t y  \t room  \n\n";
//			currentpos->print();//print entire path to treasure from starting 
//			return true;
//		}
//		return false;
//	}
//
//	~maze()
//	{
//		delete[] rooms;
//		delete currentpos;
//	}
//
//};
//
//
//int main()
//{
//	int recurse = 0;
//	maze hauntedhouse;
//	hauntedhouse.loadRooms();
//	hauntedhouse.play(recurse);
//
//}