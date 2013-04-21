//
//  Builder.cpp
//  Logic
//
//  Created by Ryan Bartley on 4/9/13.
//
//
/*
#include "Builder.h"
#include <iostream>

using namespace std;

Builder::Builder(int howManyGates, int howManySources, int howManyLevels)
{
    
    if (howManyGates <= 0 || howManySources <= 1 || howManyLevels < 0) return;
    
    s1 = new Source(howManySources);
    s2 = new Source(howManySources);
    
    r = new Result(howManySources);
    
    n = new Not(howManySources);
    o = new Or(howManySources);
    a = new And(howManySources);
    
    w1 = new Wire(howManySources);
    w2 = new Wire(howManySources);
    w3 = new Wire(howManySources);
    w4 = new Wire(howManySources);
    w5 = new Wire(howManySources);
    w6 = new Wire(howManySources);
    
    s1->addOutput(w1);
    s2->addSourceOutputs(w2);
    s2->addSourceOutputs(w3);
    
    o->addInputs(w1, w2);
    o->addOutput(w4);
    n->addInput(w3);
    n->addOutput(w5);
    a->addInputs(w4, w5);
    a->addOutput(w6);
    
    r->addInput(w6);
    
    r->getResult();
    
//    Gates g[howManyGates];
//    
//    for (int i = 0; i < howManyGates; i++) {
//        int random;
//        
//        //check my logic here if, only if there are more than one
//        //can we have a not gate
//        if (howManyGates > 1)
//            random = rand()%3;
//        else
//            random = rand()%2;
//        
//        cout << random << " is the random number" << endl;
//        
//        if (random == 0) {
//            g[i] = AND;
//        } else if (random == 1) {
//            g[i] = OR; // this is where or would go
//        } else {
//            g[i] = NOT; // this is where not would go
//        }
//    }
//    
//    //construct the gates
//    vector<Gate*> gates;
//    
//    for (int i = 0; i < howManyGates; i++) {
//        if (g[i] == AND) {
//            cout << "i'm pushing stuff back" << endl;
//            gates.push_back(new And());
//        } else if (g[i] == OR) {
//            gates.push_back(new Or());
//        } else {
//            gates.push_back(new Not());
//        }
//    }
//    
//    //construct the levels
//    vector<Gate*>::iterator it = gates.begin();
    
    
}

Builder::~Builder()
{
    delete s1;
    delete s2;
    
    delete r;
    
    delete n;
    delete o; 
    delete a;
    
    delete w1;
    delete w2;
    delete w3;
    delete w4;
    delete w5;
    delete w6;
    
}
 */

