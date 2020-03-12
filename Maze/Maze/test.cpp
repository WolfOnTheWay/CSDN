// 20190226.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <iostream>
using namespace std;

/*
��OOP����Թ�·����Ѱ�����⣬�������Ҫ�����£�
�������Թ����������� 5 5
�������Թ�·���ڵ���Ϣ��1��ʾ�����ߣ�0��ʾ���ߣ�
0 0 1 0 1
0 0 1 0 0
1 0 0 1 0
0 1 0 0 0
��ʼѰ���Թ�·���������Ͻǵ����½ǵ�һ����ͨ�е�·����:
�Թ������ڿ�ͨ�е�·��
* * 1 0 1
0 * 1 0 0
1 * * 1 0
0 1 * * *
*/
const int WAY_CNT = 4;   // �ܵķ�����Ŀ
const int WAY_RIGHT = 0;
const int WAY_DOWN = 1;
const int WAY_LEFT = 2;
const int WAY_UP = 3;

const int WAY_STATE_OK = 5; // ·�������������
const int WAY_STATE_ERR = 6;  // ·������������

class MazeNode  // �Թ��ڵ�����
{
public:
	void setVal(int val) { _val = val; }
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
	void setWayState(int way,int val) 
	{
		_state[way] = val;
	}
	int getVal() { return _val; }
	int getX() { return _x; }
	int getY() { return _y; }
	int* getState()
	{
		return _state;
	}
private:
	int _val;
	int _x;
	int _y;
	int _state[WAY_CNT];
};
class CSeqtack  // ջ����
{
public:
	CSeqtack(int t = 0, int size = 10) :_top(t), _size(size)
	{
		_stack = new MazeNode[size];
	}
	~CSeqtack()
	{
		delete[] _stack;
		
	}
	bool isFull()
	{
		return _top == _size;
	}
	void push(const MazeNode &data)
	{
		if (isFull())
		{
			MazeNode *ptmp = new MazeNode[_size * 2];
			for (int i = 0; i < _size; i++)
			{
				ptmp[i] = _stack[i];
			}
			delete[]_stack;
			_stack = ptmp;
			_size *= 2;
		}
		_stack[_top++] = data;
	}
	bool isEmpty()
	{
		return _top == 0;
	}
	MazeNode  top()
	{
		return _stack[_top - 1];
	}
	void pop()
	{
		if (isEmpty())
		{
			return;
		}
		--_top;
	}

private:
	MazeNode *_stack;
	int _top;
	int _size;
};
class Maze  // �Թ�����
{
public:
	Maze(int r = 10, int c = 10,int t=0,int size =10):_row(r),_col(c),_stack(t,size)
	{
		_pMazes = new MazeNode*[_row];
		for (int i = 0; i < _row; ++i)
		{
			_pMazes[i] = new MazeNode[_col];
		}
	}
	~Maze()
	{
		delete[] _pMazes;
	}
	void initMazeNode(int i, int j, int data)
	{
		_pMazes[i][j].setX(i);
		_pMazes[i][j].setY(j);
		_pMazes[i][j].setVal(data);
		for (int m = 0; m < 4; ++m)
		{
			_pMazes[i][j].setWayState(m, WAY_STATE_OK);
		}

	}
	CSeqtack getStack()
	{
		return _stack;
	}
	MazeNode ** getMazes()
	{
		return _pMazes;
	}
	void adjustMazeNode()
	{
		for (int i = 0; i < _row; ++i)
		{
			for (int j = 0; j < _col; ++j)
			{
				//�߽�״̬����
				if (_pMazes[i][j].getVal() == 1)
				{
					continue;
				}
				if (i == 0)
				{
					_pMazes[i][j].setWayState(WAY_UP, WAY_STATE_ERR);
				}
				if (j == 0)
				{
					_pMazes[i][j].setWayState(WAY_LEFT, WAY_STATE_ERR);
				}
				if (i == _row - 1)
				{
					_pMazes[i][j].setWayState(WAY_DOWN, WAY_STATE_ERR);
				}
				if (j == _col - 1)
				{
					_pMazes[i][j].setWayState(WAY_RIGHT, WAY_STATE_ERR);
				}
				//�м�״̬����

				if ( j < _col - 1 &&_pMazes[i][j + 1].getVal() == 1)
				{
					_pMazes[i][j].setWayState(WAY_RIGHT, WAY_STATE_ERR);
				}
				if (i < _row - 1&& _pMazes[i + 1][j].getVal() == 1 )
				{
					_pMazes[i][j].setWayState(WAY_DOWN, WAY_STATE_ERR);
				}
				if (j > 0 && _pMazes[i][j - 1].getVal() == 1)
				{
					_pMazes[i][j].setWayState(WAY_LEFT, WAY_STATE_ERR);
				}
				if (i > 0&&_pMazes[i - 1][j].getVal() == 1  )
				{
					_pMazes[i][j].setWayState(WAY_UP, WAY_STATE_ERR);
				}

				

			}
		}
	
	}
	void findMazePath()
	{
		if (_pMazes[0][0].getVal() == 1)
		{
			return;
		} 
		_stack.push(_pMazes[0][0]);
		
		while (!_stack.isEmpty())
		{
			MazeNode node = _stack.top();
			int x = node.getX();
			int y = node.getY();
			if (x == _row - 1 && y == _col - 1)
			{
				return;
			}
			if (_pMazes[x][y].getState()[WAY_RIGHT] == WAY_STATE_OK)//����
			{
				_pMazes[x][y].setWayState(WAY_RIGHT, WAY_STATE_ERR);
				_pMazes[x][y + 1].setWayState(WAY_LEFT, WAY_STATE_ERR);
				_stack.push(_pMazes[x][y + 1]);
				continue;
			}
			if ( _pMazes[x ][y].getState()[WAY_DOWN] == WAY_STATE_OK)//����
			{
				_pMazes[x][y].setWayState(WAY_DOWN, WAY_STATE_ERR);
				_pMazes[x+1][y].setWayState(WAY_UP, WAY_STATE_ERR);
				_stack.push(_pMazes[x+1][y]);
				continue;
				
			}
			if (_pMazes[x][y].getState()[WAY_LEFT] == WAY_STATE_OK)//����
			{
				_pMazes[x][y].setWayState(WAY_LEFT, WAY_STATE_ERR);
				_pMazes[x][y-1].setWayState(WAY_RIGHT, WAY_STATE_ERR);
				_stack.push(_pMazes[x][y-1]);
				continue;

			}
			if (_pMazes[x][y].getState()[WAY_UP] == WAY_STATE_OK)//����
			{
				_pMazes[x][y].setWayState(WAY_UP, WAY_STATE_ERR);
				_pMazes[x -1][y].setWayState(WAY_DOWN, WAY_STATE_ERR);
				_stack.push(_pMazes[x-1][y]);
				continue;

			}
		}




		
	
	}
	void showMazePath()
	{
		if (_stack.isEmpty())
		{
			cout << "error" << endl;
		}
		while (!_stack.isEmpty())
		{
			MazeNode top = _stack.top();
			_pMazes[top.getX()][top.getY()].setVal('*');
			_stack.pop();
		
		}
		cout << endl;
		for (int i = 0; i < _row; ++i)
		{
			for (int j = 0; j < _col; ++j)
			{
				if (_pMazes[i][j].getVal() == '*')
				{
					cout << "*" << ends;
				}
				else
				{
					cout << _pMazes[i][j].getVal() << ends;
				}
			}
			cout << endl;
		}
	}
private:
	int _row;
	int _col;
	MazeNode **_pMazes;
	CSeqtack _stack;
};
int main()
{
	cout << "�������Թ���������:";
	int row, col;
	cin >> row >> col;

	Maze maze(row, col);

	cout << "�������Թ�·���ڵ���Ϣ��1��ʾ�����ߣ�0��ʾ���ߣ�:" << endl;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			int data;
			cin >> data;
			// data i, j
			maze.initMazeNode(i, j, data);
		}
	}
	maze.adjustMazeNode();

	maze.findMazePath();
	maze.showMazePath();
	
	system("pause");
	// �����Թ��ڵ㷽�������״̬
	//maze.adjustMazeNode();
	// ��ʼѰ���Թ�·��
	//maze.findMazePath();
	// ��ӡ�Թ�Ѱ�ҵĽ��
	//maze.showMazePath();
}



