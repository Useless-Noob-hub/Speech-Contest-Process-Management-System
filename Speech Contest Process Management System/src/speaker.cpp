#include "speaker.h"

Speaker::Speaker(string name)
{
    this->m_Name = name;
    this->m_Score[1] = 0;
    this->m_Score[2] = 0;
}

void Speaker::setScore(int i, int score)
{   
    this->m_Score[i] = score;
}

Speaker::~Speaker()
{

}
