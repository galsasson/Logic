//
//  Result.cpp
//  Logic
//
//  Created by Ryan Bartley on 4/12/13.
//
//

#include "Result.h"
#include "Wire.h"
#include "Gate.h"

#define POINTS 30
#define RESULT_WIDTH 300
#define RESULT_HEIGHT 100
Result::Result(ofVec2f p, int pNum)
{
    pos = p;
    portsNum = pNum;
    
    gotResult = false;
    resultSet = false;
}

Result::~Result()
{
    result.clear();
}

bool Result::connectToInputs(vector<Wire*> wires, GatePortType type)
{
    if (wires.size() != portsNum)
        return false;
    
    for (int i=0; i<portsNum; i++)
    {
        if (type == GATEPORT_INPUTTOP)
        {
            float x = portsNum*GATE_SQUARE_SIZE/2 - GATE_SQUARE_SIZE/2 - i*GATE_SQUARE_SIZE;
            float y = -(portsNum+1)*GATE_SQUARE_SIZE/2 - 18;
            GatePort *gp = new GatePort(this, ofVec2f(x, y), type);
            gp->connect(wires[i]);
            inputsTop.push_back(gp);
        }
    }
        
    return true;
}

vector<EState> Result::getResult()
{
    vector<EState> res;
    
    if (portsNum != inputsTop.size())
        return res;
    
    for (int i=0; i<portsNum; i++)
    {
        res.push_back(inputsTop[i]->getStateImmediately());
    }

    return res;
}

void Result::reset()
{
    for (int i=0; i<inputsTop.size(); i++)
    {
        inputsTop[i]->reset();
    }
}

void Result::draw()
{

    ofPushMatrix();
    ofTranslate(pos);
    
    ofFill();
    if(resultSet){
        ofSetColor(40);
    }
    else{
        ofSetColor(30);
    }
    
    ofRect(-RESULT_WIDTH/2, -RESULT_HEIGHT/2, RESULT_WIDTH, RESULT_HEIGHT);
    
    for (int i=0; i<inputsTop.size(); i++)
    {
        inputsTop[i]->draw();
    }

    ofPopMatrix();
/*
    ofSetLineWidth(2);
    ofSetColor(128);
    //result complement
    ofBeginShape();
    for (int i=0; i<POINTS; i++)
    {
        ofVertex((float)i*inc-20, resultDeform.getAt(POINTS-i));
    }
    ofEndShape();
    
    ofSetColor(200);
    ofSetLineWidth(2);
    
    
    //incoming wire
    if (wireResult.size()>0||resultSet) {
        ofBeginShape();
        for (int i=0; i<POINTS; i++)
        {
            ofVertex((float)i*inc-20, deform->getAt(POINTS-i));
        }
        ofEndShape();
        
    }
    
    for (int i=0; i<inputsTop.size(); i++)
    {
        inputsTop[i]->draw();
    }
    
    ofPopMatrix();
    
    if(gotResult){
        gotResult = false;
        int x =0;
        for (int i=0; i<result.size(); i++) {
            
            cout<<result[i]<<" "<<-(wireResult[i*6]/10)<<endl;
            //Update: This will not exist in the final implementation.
            //The result class will get user input form getResult and compare it to result provided by config file
            
            //The draw loop will only be used to draw the wires not check for results.
            
            //this is where the comparison between the incoming value and stored result is happening
            //there are 6 values for each bit in the wireResult and the sign is the complement of the logic as that is whats required for drawing. That is why there is a -ve sign in front of it.
            if(result[i] == -(wireResult[i*6])/10){
                x++;
            }
            
            
        }
        if(x==3){
            cout<<"right answer"<<endl;
            resultSet = true;
            
        }
        wireResult.clear();
        
        
    }
 */
    
    
}
