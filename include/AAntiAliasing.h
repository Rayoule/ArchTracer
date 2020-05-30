#pragma once

struct SAASample {
    float u;
    float v;
};

class AAntiAliasing {

public:

    AAntiAliasing() {}


    int samplesNum = 9;
    SAASample samples[9] = {    {0.0,0.0},
                                {1.0,0.0},
                                {0.0,1.0},
                                {1.0,1.0},
                                {0.5,0.0},
                                {0.0,0.5},
                                {0.5,1.0},
                                {1.0,0.5},
                                {1.0,1.0} };
    
    
};