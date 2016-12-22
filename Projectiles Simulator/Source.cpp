#include <iostream>
#include <math.h>
#include <string>
using namespace std;

class Projectile {
public: 
	float angle, m, vi, h, d, b, mu, v, a, x, y, vx, vy, ay, ax, deltaVy, deltaVx;
};

void motionEQN(Projectile proj) {
	proj.ay = ((-proj.m * 9.81) - (proj.b * proj.vy)) / proj.m;
	proj.ax = (-proj.b * proj.vx) / proj.m;
	
	proj.vy += proj.ay * 0.1;
	proj.vx += proj.ax * 0.1;

	proj.v = sqrt(pow(proj.vx, 2) + pow(proj.vy, 2));

	proj.x += proj.vx * 0.1;
	proj.y += proj.vy * 0.1;
}

void delta(Projectile proj) {
	
	proj.vy += proj.ay * 0.1;
	proj.vx += proj.ax * 0.1;
	
}

Projectile loadFile(string fileName) {
	Projectile proj;


	return proj;
}

void main() {

	int x;
	string fileName = "";
	Projectile proj;
	proj.m = 12;
	
	cout << "1- Load Parameters from file" << endl;
	cout << "2- Enter Parameters" << endl;
	cout << "3- Save Parameters to File" << endl;
	cout << "4- Do simulation" << endl;
	cin >> x;

	switch (x) {
	case 1:
		getline(cin, fileName);
		proj = loadFile(fileName);
		break;
	case 2:
		cout << "Enter Projectile data" << endl;
		cout << "Mass = ";
		cin >> proj.m;
		cout << "Viscous Coff = ";
		cin >> proj.b;
		cout << "Intial Velocity = ";
		cin >> proj.vi;
		cout << "Angle = ";
		cin >> proj.angle;
		proj.vx = proj.vi * cos(proj.angle);
		proj.vy = proj.vi * sin(proj.angle);
		cout << "Hieght = ";
		cin >> proj.h;
		proj.x = 0;
		proj.y = proj.h - 720;
		cout << "Diameter = ";
		cin >> proj.d;
		break;
	case 3:

		break;

	case 4:
		while (proj.v != 0) {
			motionEQN(proj);
		}

		break;
	}
}