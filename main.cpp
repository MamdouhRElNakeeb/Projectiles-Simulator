


#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <conio.h>

using namespace std;

class Projectile {
public:
	float angle=0, m, vi=0, h, d, b, mu, v, a, x, y, vx, vy, ay, ax, deltaVy, deltaVx, e;
};

void motionEQN(Projectile proj) {

    ofstream f;
    f.open("Readings.csv");
    f << "x,y" << "\n";
    f << proj.x << "," << proj.y << "\n";
    float t = 0;
    int flag1=0;
    do{
		proj.ay = ((-proj.m * 9.81) - (proj.b * proj.vy)) / proj.m;
		proj.ax = (-proj.b * proj.vx) / proj.m;

		proj.vy += proj.ay * 0.1;
		proj.vx += proj.ax * 0.1;

		proj.x += proj.vx * 0.1;
		proj.y += proj.vy * 0.1;

		if (proj.y < 0){
            proj.y = 0;
            f << proj.x << "," << proj.y << "\n";
		}

		if(proj.y == 0){
            proj.vy = - proj.e * proj.vy;
            proj.vx = proj.vx + (proj.mu *(proj.e - 1) * proj.vx);

            proj.v = sqrt(pow(proj.vx, 2) + pow(proj.vy, 2));

            proj.x += proj.vx * 0.1;
            proj.y += proj.vy * 0.1;
		}

		cout << t << " -- " << proj.ax << " --- " << proj.ay << " --- " << proj.vx << " --- " << proj.vy << " --- " << proj.x << " --- " << proj.y << "\n";
		f << proj.x << "," << proj.y << "\n";
		t = t + 0.1;

	}while (t <= 20);

}

void delta(Projectile proj) {

	proj.vy += proj.ay * 0.1;
	proj.vx += proj.ax * 0.1;

}

Projectile loadFile() {
	Projectile proj;
	fstream f;
	f.open("projectile.csv");
	string values[8];
	int i=0;

	while (f.is_open() && i <8){
        getline(f, values[i], ',');
        i++;
	}
	if(!f.is_open()){
        cout<< "Cannot open file!" << endl;
	}
	else{
        cout << "File Loaded" << endl;
	}

	proj.m = atof(values[0].c_str());
    proj.d = atof(values[1].c_str());
    proj.vi = atof(values[2].c_str());
    proj.angle = atof(values[3].c_str());
    proj.b = atof(values[4].c_str());
    proj.e = atof(values[5].c_str());
    proj.mu = atof(values[6].c_str());
    proj.h = atof(values[7].c_str());
	return proj;
}

int showMenu(){
    int x=0;
    cout << "1- Load Parameters from file" << endl;
	cout << "2- Enter Parameters" << endl;
	cout << "3- Save Parameters to File" << endl;
	cout << "4- Do simulation" << endl;
	cout << "5- Exit" << endl;
	cin >> x;
	return x;
}

//Don't remove any of the existing code lines

int main()
{
    string fileName = "";
	Projectile proj;
    int flag = 0;
    int flag1=1;
    int entry =0;
    ofstream f;

	do{
        switch (showMenu()) {
        case 1:
            // load projectile values from file
            proj = loadFile();
            flag =1;
            break;
        case 2:
            flag = 1;
            //
            f.open("projectile.csv");
            //f<< "Mass (kg),Diameter(m),Initial velocity(m/s),Initial angle(degrees),b(N.s/m), e ,mu,Height(m) \n";
            cout << "Enter Projectile data" << endl;
            cout << "Mass = ";
            cin >> proj.m;
            cout << "Diameter = ";
            cin >> proj.d;
            cout << "Initial Velocity and Initial Angel Entry" << endl;
            cout << "1- Manual Entry \n2- Keys Entry" << endl;

            cin >>entry;
            if (entry ==2){
                cout << "- UP Arrow to increase Angel \n- DOWN Arrow to decrease Angel \n- Press Space to increase Velocity \n- Press ESC when Finished" << endl;
                do{
                    if (kbhit()){
                        char ch = getch();
                        switch(ch){
                            case 72: proj.angle++; flag1 =1; break;
                            case 80: proj.angle--; flag1 =1; break;
                            case 32: proj.vi++; flag1 =1; break;
                            case 27: flag1 =0; break;
                        }
                    }
                }
                while(flag1 == 1);
                    cout << "Initial Velocity = "<< proj.vi << endl;
                    cout << "Initial Angel = "<< proj.angle << endl;
            }
            else if (entry == 1){
                cout << "Initial Velocity = ";
                cin >> proj.vi;
                cout << "Initial Angle = ";
                cin >> proj.angle;
            }

            proj.vx = proj.vi * cos(proj.angle * 3.14 / 180);
            proj.vy = proj.vi * sin(proj.angle * 3.14 / 180);
            cout << proj.vx << " --- " << proj.vy << endl;
            cout << "Viscous Coff = ";
            cin >> proj.b;
            cout << "e = ";
            cin>> proj.e;
            cout << "mu = ";
            cin >> proj.mu;
            cout << "Height = ";
            cin >> proj.h;
            proj.x = 0;
            proj.y = proj.h;
            cout << "Values Entered" << endl;
            break;

        case 3:
            flag = 1;
            //save parameters to file
            f<< proj.m << "," << proj.d << "," << proj.vi << "," << proj.angle << "," << proj.b << "," << proj.e << "," << proj.mu << "," <<proj.h << "\n";
            f.close();
            cout << "Saving Done" << endl;
            break;

        case 4:
            flag=1;
            //simulate the motion and save readings into file
            motionEQN(proj);
            break;

        case 5:
            flag = 0;
            cout << "Good Bye" << endl;
            break;
        }
	}
	while(flag==1);


}
