//
//  State.h
//  Logic
//
//  Created by Ryan Bartley on 4/9/13.
//
//

#pragma once

#include <vector>

enum EState {
    FLOATING = 0,
    HIGH = 1,
    LOW = -1
};

enum Gates {
    
    AND,
    OR,
    NOT,
    SOURCE,
    OUTPUT
    
};
