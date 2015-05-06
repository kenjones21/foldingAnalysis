#include <iostream>
#include "atom.h"
#include <cmath>

using namespace std;

bool debug = true;

void Atom::newpos(float x, float y, float z) {
  if (debug) {
    cout << "Assigning new position to atom " << this->sysnum << endl;
  }
  this->x = x;
  this->y = y;
  this->z = z;
}

Atom::Atom (int elnum, int sysnum, float x, float y, float z, float weight) {
  if (debug) {
    cout << "Creating to atom, sysnum " << sysnum << " elnum " << elnum << endl;
  }
  this->elnum = elnum;
  this->sysnum = sysnum;
  this->x = x;
  this->y = y;
  this->z = z;
  this->weight = weight;
}

Atom::Atom (int elnum, int sysnum, float weight) {
  this->elnum = elnum;
  this->sysnum = sysnum;
  this->weight = weight;
}

Atom::Atom () {
  
}

void Atom::setInfo(int elnum, int sysnum, float weight) {
  this->elnum = elnum;
  this->sysnum = sysnum;
  this->weight = weight;
}

float Atom::distance(Atom other) {
  float xdist = this->x - other.x;
  float ydist = this->y - other.y;
  float zdist = this->z - other.z;
  return sqrt(pow(xdist, 2) + pow(ydist, 2) +
              pow(zdist, 2));
}

void Atom::makeBond(Atom* other) {
  this->bondedTo.push_back(other);
  other->bondedTo.push_back(this);
}

void Atom::printBonds() {
  cout << "This atom is bonded to " << bondedTo.size() << " atoms" << endl;
}

bool Atom::isHeavy() {
  return elnum > 2;
}

int Atom::getSysnum() {
  return this->sysnum;
}

int Atom::getElnum() {
  return this->elnum;
}

float Atom::getWeight() {
  return this->weight;
}
