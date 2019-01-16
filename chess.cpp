#include <iostream>
using namespace std;
#define N 8

typedef unsigned long long ull;

class Board;
class Cell
{
private:
	Board *board;
	int x, y;
	ull rice;
public:
	Cell(int _x, int _y,Board *b) {
		x = _x;
		y = _y;
		board = b;
		rice=0;
	}
	ull getRice() const {
		return rice;
	}
	void setRice(ull rice) {
        this->rice=rice;
	}
};
class Board
{
private:
	Cell *cells[N][N];
public:
	Board()
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cells[i][j] = new Cell(j, i, this);
	}
	Cell** begin()
	{
		return &cells[0][0];
	}
	Cell** end()
	{
		return &cells[N - 1][N];
	}

	class Iterator
	{
	private:
		Cell **current;
	public:
		Iterator(Cell **c) {
			current = c;
		}
		void set(Cell **c) {
			current=c;
		}
		Cell* operator*() {
			return *current;
		}
		Iterator& operator++() {
			current++;
			return *this;
		}
		Cell** getCurrent() {
			return current;
		}
	};
};

class RiceCounter
{
   private:
   	 ull total;
   public:
   	 RiceCounter():total(0) {}
   	 ull getTotal() {
   	 	return total;
   	 }
   	 void operator()(ull rice) {
        total+=rice;
   	 }
};

int main()
{
	Board chess;
	Board::Iterator iter(chess.begin());
	ull rice=1;
	while (iter.getCurrent() != chess.end())
	{
		(*iter)->setRice(rice);
		++iter;
		rice*=2;
	}
	iter.set(chess.begin());
	RiceCounter rcounter;
	while (iter.getCurrent() != chess.end())
	{
		rcounter((*iter)->getRice());
		++iter;
	}	
	cout<<rcounter.getTotal()<<endl;
	return 0;
}