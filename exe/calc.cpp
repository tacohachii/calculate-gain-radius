#include <fstream>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

#define PI 3.14159265359
#define G 6.67430e-11   //m^3/kg.s
#define M_sun 1.989e+30 //kg

void calcGR(string name);
int getLastLine(string filename);
void getDataFrom(string filename, double data[1200][5]);
void calcGainRadius(double data[1200][5], int last_line);
void writeDataTo(string filename, double data[1200][5], int last_line);

int main()
{
  // 引数：.data のファイル名
  calcGR("s12");
  calcGR("s15s7b2");
  calcGR("s22");
  calcGR("s25");

  return 0;
}

void calcGR(string filename)
{
  cout << "Start: " << filename << endl;

  int last_line = getLastLine(filename);

  // 0: radius, 1: mass, 2: density, 3: calculated t, 4: calculated r_g
  double data[last_line][5];

  getDataFrom(filename, data);
  calcGainRadius(data, last_line);
  writeDataTo(filename, data, last_line);

  cout << "Finish: " << filename << endl;
  cout << endl;
}

int getLastLine(string filename)
{
  string inputfile = filename + ".data";
  ifstream ifs("./data-in/" + inputfile);
  string line;
  int column = 0;
  getline(ifs, line);
  getline(ifs, line);
  while (ifs && getline(ifs, line))
  {
    column++;
  }
  return column;
}

void getDataFrom(string filename, double data[1200][5])
{
  string inputfile = filename + ".data";
  ifstream ifs("./data-in/" + inputfile);
  string line;
  int column = 0;
  string s;

  char stmp;
  double mass, radius, dtmp, density;

  getline(ifs, line);
  getline(ifs, line);
  while (ifs && getline(ifs, line))
  {
    sscanf(line.c_str(), "%s %lf %lf %lf %lf", &stmp, &mass, &radius, &dtmp, &density);
    data[column][0] = radius * 1e-2;  // cm -> m
    data[column][1] = mass * 1e-3;    // g -> kg
    data[column][2] = density * 1e+3; // g/cm^3 -> kg/m^3
    column++;
  }
  cout << "Read: " << filename << endl;
  cout << "Line: " << column << endl;
}

void calcGainRadius(double data[1200][5], int last_line)
{
  for (int i = 0; i < last_line; i++)
  {
    double r = data[i][0];   // m
    double M = data[i][1];   // kg
    double rho = data[i][2]; // kg/m^3
    double average_densty = M / (4 / 3 * PI * r * r * r);
    double infall_time = sqrt(PI / (4 * G * average_densty));
    double mass_accretion_rate = 2 * M / infall_time * rho / (average_densty - rho);
    double r_0 = 12;  // km
    double r_1 = 120; // km
    double r_tmp = pow(r_1, 3) * (mass_accretion_rate / M_sun) * pow((M / M_sun), -3) + pow(r_0, 3);
    double r_g = pow(r_tmp, 1.0 / 3.0);
    data[i][3] = infall_time; //s
    data[i][4] = r_g;         //km
  }
  cout << "Calclated!!" << endl;
}

void writeDataTo(string filename, double data[1200][5], int last_line)
{
  string outputfile = filename + ".out";
  ofstream ofs("./data-out/" + outputfile);

  ofs << filename << endl;
  ofs << "No radius mass density time r_g" << endl;

  for (int i = 0; i < last_line; ++i)
  {
    ofs << i + 1 << ' ' << data[i][0] << ' ' << data[i][1] << ' ' << data[i][2] << ' ' << data[i][3] << ' ' << data[i][4] << endl;
  }

  cout << "Write: " << filename << endl;
}
