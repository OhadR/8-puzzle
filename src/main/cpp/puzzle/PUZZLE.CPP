
#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "list.h"
#include <stdio.h>

/*enum bool {false=0, true=1};   declared in "list.h"   */


/*-------------------------------------------
	class Point, we use it for locating the
	empty	place	on the board
 ---------------------------------------------*/
class Point
{
  public:
	 int x;
	 int y;
	 Point(int a=0,int b=0)
	 {
		x=a;
		y=b;
	 }

	 Point(const Point &);
	 void SetPoint(int a,int b)
	 {
		x=a;
		y=b;
	 }
    void show()
	 {
		cout<<"x="<<x<<"y="<<y;
	 }
};

Point::Point(const Point & point)
{
  x=point.x;
  y=point.y;
}


/*-------------------------------------------
	class Puzzle, defining the board as a matrix,
	including the empty space, and the calculated
	Manhatten Distance, and the "f" function, where:
	f = Manhatten Distance + number of steps
 ---------------------------------------------*/

class Puzzle
{
private:
  int matrix[3][3];
  Point empty_space;
  int Manhatten_Distance;
  int f;    	//f := Manhatten_Distance + number_of_steps

  Puzzle *previous;	//so i can know the actual course!!!

public:
  Puzzle();             		 //constructor
  Puzzle(int *vec);
  Puzzle(const Puzzle &);      //copy constructor
  Puzzle& operator=  (const Puzzle& p);
  friend bool 	 operator == (const Puzzle& p1, const Puzzle& p2);

  bool Check_Up();
  bool Check_Down();
  bool Check_Left();
  bool Check_Right();
  void Change_Up();
  void Change_Down();
  void Change_Left();
  void Change_Right();

  int Manhatten(int value,int i,int j);
  int get_f()					{return  f;}			//inline implementation
  void Set_f(int new_f)		{f = new_f;}   		//inline implementation
  void Set_previous(Puzzle* puzzle_father)	{previous = puzzle_father;} //inline impl.

  bool IsGoal();
  void Show_Puzzle();
  void Show_Course();

};


/*-------------------------------------------
			class Puzzle implementation
 -------------------------------------------*/

Puzzle::Puzzle()
{
	//no further initialization
}


Puzzle::Puzzle(const Puzzle & puz)
{
  f=puz.f;
  Manhatten_Distance=puz.Manhatten_Distance;
  for(int i=0;i<=2;i++)
	 for(int j=0;j<=2;j++)
			matrix[i][j]=puz.matrix[i][j];

  empty_space.SetPoint(puz.empty_space.x,puz.empty_space.y);
  previous = puz.previous;
}

//gets an one dimentional array and turns it to a 3x3 matrix - the puzzle
Puzzle::Puzzle(int *vec)
{
  Manhatten_Distance=0;
  int index=0;
  for(int i=0;i<=2;i++)
	 for(int j=0;j<=2;j++)
	 {
		if(vec[index]==0)
			  empty_space.SetPoint(i,j);

		matrix[i][j]=vec[index++];
		if(matrix[i][j]!=0)
		  Manhatten_Distance+=Manhatten(matrix[i][j],i,j);

	 }


  f=Manhatten_Distance;
  previous = NULL;
}


Puzzle& Puzzle::operator =(const Puzzle& p)
{
	for(int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			matrix[i][j] = p.matrix[i][j];
	Manhatten_Distance = p.Manhatten_Distance;
	empty_space.SetPoint(p.empty_space.x, p.empty_space.y);
	f = p.f;
	previous = p.previous;
	return *this;
}

//compare between two puzzles by comparing their matrixes
bool operator ==(const Puzzle& p1, const Puzzle& p2)
{
	for(int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			if (p1.matrix[i][j] != p2.matrix[i][j])
				return false;
	return true;
}



void Puzzle::Change_Up()
{
  f=(f- Manhatten_Distance);
  Manhatten_Distance=(Manhatten_Distance-(Manhatten(  matrix[empty_space.x+1][empty_space.y],empty_space.x+1,empty_space.y))+Manhatten(  matrix[empty_space.x+1][empty_space.y],empty_space.x,empty_space.y));
  f=(f+Manhatten_Distance+1);
  matrix[empty_space.x][empty_space.y]=matrix[( (empty_space.x )+1)][empty_space.y];
  matrix[( (empty_space.x )+1)][empty_space.y]=0;
  empty_space.SetPoint(((empty_space.x)+1),empty_space.y);
}


void Puzzle::Change_Down()
{
  f=(f- Manhatten_Distance);
  Manhatten_Distance=(Manhatten_Distance-(Manhatten(  matrix[empty_space.x-1][empty_space.y],empty_space.x-1,empty_space.y))+Manhatten(  matrix[empty_space.x-1][empty_space.y],empty_space.x,empty_space.y));
  f=(f+Manhatten_Distance+1);
  matrix[empty_space.x][empty_space.y]=matrix[( (empty_space.x )-1)][empty_space.y];
  matrix[( (empty_space.x )-1)][empty_space.y]=0;
  empty_space.SetPoint(((empty_space.x)-1),empty_space.y);
}


void Puzzle::Change_Right()
{
  f=(f- Manhatten_Distance);
  Manhatten_Distance=(Manhatten_Distance-(Manhatten(  matrix[empty_space.x][empty_space.y-1],empty_space.x,empty_space.y-1))+Manhatten(  matrix[empty_space.x][empty_space.y-1],empty_space.x,empty_space.y));
  f=(f+Manhatten_Distance+1);
  matrix[empty_space.x][empty_space.y]=matrix[empty_space.x][empty_space.y-1];
  matrix[empty_space.x][empty_space.y-1]=0;
  empty_space.SetPoint(empty_space.x,((empty_space.y)-1));
}


void Puzzle::Change_Left()
{
  f=(f- Manhatten_Distance);
  Manhatten_Distance=(Manhatten_Distance-(Manhatten(  matrix[empty_space.x][empty_space.y+1],empty_space.x,empty_space.y+1))+Manhatten(  matrix[empty_space.x][empty_space.y+1],empty_space.x,empty_space.y));
  f=(f+Manhatten_Distance+1);
  matrix[empty_space.x][empty_space.y]=matrix[empty_space.x][empty_space.y+1];
  matrix[empty_space.x][empty_space.y+1]=0;
  empty_space.SetPoint(empty_space.x,((empty_space.y)+1));
}


//this method was in use for testings
void Puzzle::Show_Puzzle()
{
  for(int i=0;i<=2;i++)
  {
	 cout<<'\n';
	 for(int j=0;j<=2;j++)
	 {
		cout.width(5);
		cout<<matrix[i][j];
	  }
  }
  cout<<'\n';
  cout<<"Manhatten_Distance: "<<Manhatten_Distance;
  cout<<'\n';
  cout<<"f: "<<f;
  cout<<'\n'<<'\n';
//  empty_space.show();
//  cout<<"previous: "<<previous;
}


int Puzzle::Manhatten(int value,int i,int j)
{
  int x,y;
  x=(value/3);
  y=(value%3);
  return ( (abs(x-i)) + (abs(y-j))  );

}


bool Puzzle::IsGoal()
{
  if(Manhatten_Distance==0)
	 return true;
  else
	 return false;
}


bool Puzzle::Check_Up()
{
if(empty_space.x!=2)
  return true;
else
  return false;
}



bool Puzzle::Check_Down()
{
if(empty_space.x!=0)
  return true;
else
  return false;
}



bool Puzzle::Check_Right()
{
if(empty_space.y!=0)
  return true;
else
  return false;
}




bool Puzzle::Check_Left()
{
if(empty_space.y!=2)
  return true;
else
  return false;
}


void Puzzle::Show_Course()
{
	for (	 Puzzle * p=this; p!=NULL ; p=p->previous)
		p->Show_Puzzle();

}


bool ValidateInput(int * vec)
{
  for(int i=0;i<=8;i++)
  {
	 if(vec[i]<0 || vec[i]>8)
	 {
			cout<<"The numbers are not between 0-8!\n";
			return false;
	 }

	 for(int j=0;j<=8;j++)
		if((j!=i)&&(vec[j]== vec[i]))
		{
		  cout<<"The number :"<<vec[i]<<" is already exists\n";
		  return false;
		}
  }
  return true;
}


void InsertToOpenList(doubleEndedList<Puzzle>& OpenList, list<Puzzle>& CloseList,  Puzzle& puz, int father_f)
{
	if(!(CloseList.Includes(puz)))
	{	if(!(OpenList.Includes(puz)))
				//compare with the f of the father, if equals enter to start-side.
				//otherwise enter to end-size
				if (puz.get_f() == father_f)
					OpenList.Add(puz);
				else
					OpenList.AddToEnd(puz);
		else
		{	Puzzle* temp = OpenList.ReturnValue(puz);
			if (temp->get_f() >= puz.get_f())
				temp->Set_f(puz.get_f());
		}
	}
}




int A_Star(Puzzle& initial_state, int& counter)
{
	counter = 0; 					//number of puzzles we generate
	doubleEndedList<Puzzle> OpenList;
	list<Puzzle>				CloseList;
	OpenList.Add(initial_state);		//enter the 1st component to OL
	while(!OpenList.IsEmpty() )
	{	Puzzle puzzle = OpenList.RemoveandReturnFirst();
		if( !(puzzle.IsGoal() ) )
		{
			counter++;
			Puzzle* temp_puz;		//will hold the allocated address of the puzzle if was entered to OL

			temp_puz = CloseList.Add(puzzle);    //add to CL and getting allocated memory address, so
													//this puzzle's childs can point at it. that's why i'm
													//adding to CL before the "if-s"

			if(puzzle.Check_Up())
			{	Puzzle p_copy1(puzzle);    //make copy of the puz so we can change it
													//without changing the origion

				p_copy1.Set_previous(temp_puz);
				p_copy1.Change_Up();
				//transfer f of the father so we can compare f's before enter to OL:
				InsertToOpenList(OpenList, CloseList, p_copy1, puzzle.get_f());
				//if the child was enterd to OL, temp_puz points to its father he'll point at his "dad":
			}

			if(puzzle.Check_Down())
			{	Puzzle p_copy2(puzzle);
				p_copy2.Set_previous(temp_puz);
				p_copy2.Change_Down();
				InsertToOpenList(OpenList, CloseList, p_copy2, puzzle.get_f());
			}
			if(puzzle.Check_Left())
			{	Puzzle p_copy3(puzzle);
				p_copy3.Set_previous(temp_puz);
				p_copy3.Change_Left();
				InsertToOpenList(OpenList, CloseList, p_copy3, puzzle.get_f());
			}
			if(puzzle.Check_Right())
			{	Puzzle p_copy4(puzzle);
				p_copy4.Set_previous(temp_puz);
				p_copy4.Change_Right();
				InsertToOpenList(OpenList, CloseList, p_copy4, puzzle.get_f());
			}

		}
		else  		//we found the goal!! now print the course to it
		{
			puzzle.Show_Course();
			return	puzzle.get_f();
			//return	counter;           //not needed, return by argument!!!
		}
	}
	assert( OpenList.IsEmpty() );
}


void GetDataFromFile()
{
	int index = 0;
	char input_line[30];
	char *string1, *string2;
	FILE *fp;
	int int_array[9],
		 course_length,		//holds the "f", meaning the course length
		 counter,				//holds the number of puzzles that have been generated
		 counter_sum=0,			//holds the sum of counters
		 course_length_sum=0;	//holds the sum of course-lengths


	fp = fopen("inputs.txt", "r");
	while(!feof(fp))              //keep reading strings from file
	{	fgets(input_line, 30, fp);
		string1 = strtok(input_line, " ");
		index = atoi(string1);
		int i=0;
		while(string2 = strtok(NULL, " ")) //moving on the input line
			int_array[i++] = atoi(string2);
		assert(ValidateInput(int_array));  //check input!!!
		Puzzle created_puzzle(int_array);
		course_length = A_Star(created_puzzle, counter);
		cout<<index<<".\t"<<course_length<<"\t\t"<<counter<<"\n";
		counter_sum+=counter;
		course_length_sum+=course_length;
	}
	cout<<" the average of course-lengths is: "<<( double(course_length_sum)/100)<<"\n";
	cout<<" the average of generated puzzles is: "<<( double(counter_sum)/100)<<"\n";
}




void main()
{
	int vec[9] = {2,4,8,3,7,6,1,5,0};
	Puzzle puzzle(vec);
	int counter;
	int length = A_Star(puzzle, counter);
	cout<<"counter: "<<counter<<"\tlength: "<<length;
}
