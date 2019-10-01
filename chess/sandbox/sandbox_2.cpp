#include <stdio.h> 
#include <iostream>
#include "sandbox.h"
using namespace std;


void doogle::set_doog(int x){
	doog = x;
}

int doogle::get_doog(){
	return doog;
}

int doogle::times(floogle* x){
	return (doog * x->get_floog());
}