#include <iostream>

using namespace std;
class Box {
//Implement the class Box  
//l,b,h are integers representing the dimensions of the box
private:
  int l, b, h;
// The class should have the following functions : 
public:
// Constructors: 
  Box(): l(0), b(0), h(0) {}
  Box(int ll, int bb, int hh): l(ll), b(bb), h(hh) {}
  Box(const Box& B): l(B.l), b(B.b), h(B.h) {}


  int getLength() {return l;} // Return box's length
  int getBreadth() {return b;} // Return box's breadth
  int getHeight() {return h;}  //Return box's height
  long long CalculateVolume() {return (long long) l * b * h;} // Return the volume of the box

  //Overload operator < as specified
  bool operator<(Box& B) {return l < B.l || (l == B.l && b < B.b) || (l == B.l && b == B.b && h < B.h);}

//Overload operator << as specified
  friend ostream& operator<<(ostream& out, Box& B);
  
};

ostream& operator<<(ostream& out, Box& B) {
  out << B.getLength() << ' ' << B.getBreadth() << ' ' << B.getHeight(); return out;
}

void check2()
{
	int n;
	cin>>n;
	Box temp;
	for(int i=0;i<n;i++)
	{
		int type;
		cin>>type;
		if(type ==1)
		{
			cout<<temp<<endl;
		}
		if(type == 2)
		{
			int l,b,h;
			cin>>l>>b>>h;
			Box NewBox(l,b,h);
			temp=NewBox;
			cout<<temp<<endl;
		}
		if(type==3)
		{
			int l,b,h;
			cin>>l>>b>>h;
			Box NewBox(l,b,h);
			if(NewBox<temp)
			{
				cout<<"Lesser\n";
			}
			else
			{
				cout<<"Greater\n";
			}
		}
		if(type==4)
		{
			cout<<temp.CalculateVolume()<<endl;
		}
		if(type==5)
		{
			Box NewBox(temp);
			cout<<NewBox<<endl;
		}

	}
}

int main()
{
	check2();
}
