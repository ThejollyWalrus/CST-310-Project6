// Mason Hamilton
// CST-310
// Project 6
// 3-8-20

//All the inlcluded libaries
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <string>
#include <map>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;
//This is my class the reads in the file and creates the string based on
//the correct grammar
class Fractal{


//Public class with my file reader and draw function
public:

Fractal(string file){
seen = false;
fstream inFile;
stringstream data;
string title, lineNum, rules;
inFile.open(file);
//getting the input from the called file
if(inFile.is_open()){
    while (getline(inFile, lineNum)){
        if(lineNum[0] != '#'){
            data.clear();
//if statements sorting out the correct keys to assign them to the laws that are defined in the grammar
            data.str(lineNum);
            if(lineNum.find("len") != string :: npos)
                data >> title >> len;

            else if(lineNum.find("iter") != string::npos)
                data >> title >> iter;

            else if(lineNum.find("rot") != string::npos)
                data >> title >> Xrot >> Yrot >> Zrot;

            else if(lineNum.find("start") != string::npos)
                data >> title >> runLine;
//setting all the laws and grammars
            else if(lineNum.find("rep") != string::npos){
                if(seen == false)
                    seen = true;
                data >> title >> rules;
                grammar[rules[0]] = rules[2];
            }
            else{
                data >> title >> rules;
                law[lineNum[0]] = rules;
            }
        }
        if(inFile.eof())
            break;
    }
//closes the open file
    inFile.close();

 }

//our grammar being instered into a string for the keys
	grammar['-'] = "-";
	grammar['+'] = "+";
	grammar['&'] = "&";
	grammar['^'] = "^";
	grammar['z'] = "z";
	grammar['/'] = "/";
	grammar[']'] = "]";
	grammar['['] = "[";
	grammar['|'] = "|";
    law['-'] = "-";
	law['+'] = "+";
	law['&'] = "&";
	law['^'] = "^";
	law['z'] = "z";
	law['/'] = "/";
	law[']'] = "]";
	law['['] = "[";
	law['|'] = "|";

 create();
}
//fucntion that actually draws the fractal
void draw(){
    glPushMatrix();

    glRotatef(270,0,0,1);
    //glRotatef(-30, 1,0,0);
    //glTranslatef(10.0f, -5.955f, -0.99f);
    //glRotatef(-90,0,1,0);
    for(int i = 0; i < runLine.size(); i++){
        char key = runLine[i];
//switch statement decieding witch key is doing what action
        switch (key){
            case 'F': {polyCylinder(); glTranslatef(0,0,len); break;}
			case 'f': {glTranslatef(0,0,len); break;}
			case '+': {glRotatef(Xrot,1,0,0); break;}
			case '-': {glRotatef(-Xrot,1,0,0);break;}
			case '&': {glRotatef(Yrot,0,1,0); break;}
			case '^': {glRotatef(-Yrot,0,1,0);break;}
			case 'z': {glRotatef(Zrot,0,0,1); break;}
			case '/': {glRotatef(-Zrot,0,0,1);break;}
			case '|': {glRotatef(-180,0,0,1); break;}
			case '[': {glPushMatrix();break;}
			case ']': {glPopMatrix(); break;}
        }
    }
    glPopMatrix();
}

//private section of my project 
private:
//Creating all the grammar were going to use to create the fractal
    int len, iter;
    bool seen;
    float Xrot, Yrot, Zrot;
    string runLine;
    map<char, string> law;
    map<char, string> grammar;
//taking in all the strings and puting them into one that can be read by our grammar
    void create(){
        for(int i=0; i<iter; i++){
            string nextLine = "";

            for(int i=0; i<runLine.size(); i++)
                nextLine += law[runLine[i]];
            runLine = nextLine;
        }
        if(seen){
            string nextLine = "";

            for(int i=0; i<runLine.size(); i++)
                nextLine += grammar[runLine[i]];
            runLine = nextLine;
        }
     }
//The polycylinder section of the project
//used to create the lines draw aka the cylinders 
//and the connecting points used as spheres
     void polyCylinder(){
        glPushMatrix();
            GLUquadricObj * quadratic;
            quadratic = gluNewQuadric();
            gluCylinder(quadratic, 0.1f, 0.1f, len,32,32);
        glPopMatrix();
        glPushMatrix();
            glutSolidSphere(0.1f, 10,10);
        glPopMatrix();
        glFlush();
     }


};

