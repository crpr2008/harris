//============================================================================
// Name        : harris.cpp
// Author      : carcmg
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>

using namespace std;

class sense{
	double input;
	int initialInstinctResponse; //none, fear, i know this, wow, ...
	void processInput();
	int addressInitialReaction();
protected:
	void getCurrentStatus() { cout << "Current status is blablabla" << endl; }
public:
	virtual char * identify() { return "Sense"; }
	sense();
	~sense();
	double getInput() { return input; }
	int getInitialResponse() { return initialInstinctResponse; }
};

sense::sense()
{
	input = 1.0;
	initialInstinctResponse = 1;
	cout << "sense initialized" << endl;
}

sense::~sense()
{
	input = 0.9;
	initialInstinctResponse = 0;
	cout << "sense is done" << endl;
}

void sense::processInput()
{
	cout << "enter number from 1 to 1.9: ";
	cin >> input;
	cout << endl;
	input > 1.9 || input < 1 ? cout << "Number entered [" << input << "] is invalid.  try again." << endl : cout << "Input [" << input << "] accepted" << endl;
}

int sense::addressInitialReaction()
{
	cout << "Processing input value [" << input << "]." << endl;
	return 1;
}

#define HAZARD_STRING_SIZE 10

class vision : public sense {
	double road; //smooth thru very bumpy, 1.0 thu 1.9
	char hazard[HAZARD_STRING_SIZE]; //object on road, shcool, consturtion
	int weather; //dry, sandy, wet, flooded
	int instrument; // speedo, tach, engine lights, radio
public:
	virtual char * identify() { return "Vision"; }
	vision();
	~vision();
	void setRoad(double r) { road = r; }
	void setHazard(char *p) { strncpy(hazard,p,sizeof(hazard)); }
	void setWeather(int w) { weather = w; }
	void setInstrument(int i) { instrument = i; }
	char * getHazard() { return &hazard[0]; }
};

vision::vision()
{
	cout << "creating a vision object" << endl;
	road = 1.5;
	for (int i=0; i< sizeof(hazard);i++) hazard[i]='\0';
	weather = 2;
	instrument = 2;
	getCurrentStatus();
}

vision::~vision()
{
	cout << " vision object done for " << endl;
}

void printVisionValues(vision *v);

int main() {
	char c=0;
	vision *v=0;
	sense *s=0;
	char word[10];
	char hazardString[HAZARD_STRING_SIZE]= "dry";
	ifstream in("input.txt");
	ofstream out("out.txt" );


	cout << "HHs esto lo vamos a aprender, enter 0 or (Vision, Hearing, Flavor, Smell, Touch: " << endl; // prints HHs
	cin >> c;
	switch (c)
	{
		case 'V':
		case 'v':
		{
			v = new vision;
			s =v;
			v->setHazard(hazardString);
			printVisionValues(v);
			cout << "Identity = " << s->identify() << endl; //when identity is virtual,this will print vision, otherwise sense
			while (!in.eof())
			{
				in >> word;
				out << word;
			}
			in.close();
			out.close();

			break;
		}
		case 'H':
		case 'h':
		case 'F':
		case 'f':
		case 'S':
		case 's':
		case 'T':
		case 't':
		{
			cout << "creating a valid sense [" << c << "], but not implemented yet" << endl;
			break;
		}
		default:
			cout << "invalid sense [" << c << "]." << endl;
	}

	delete v;
	cout << " that's all folks " << endl;
	return 0;
}

void printVisionValues(vision *v)
{
	cout << "vision hazard = " << v->getHazard() << endl;
	cout << "sense input = " << v->getInput() << endl;
//	v->getCurrentStatus();//this is protected hence, it may not be called from non member
}
