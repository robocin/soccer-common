#include "Field.h"

Field::Field(double fieldLength, double fieldWidth, double goalWidth, double goalDepth){
    this->m_fieldLength = fieldLength;
    this->m_fieldWidth = fieldWidth;
    this->m_goalDepth = goalDepth;
    this->m_goalWidth = goalWidth;
}

double Field::fieldLength() const{
    return this->m_fieldLength;
}

double Field::fieldWidth() const{
    return this->m_fieldWidth;
}

double Field::goalWidth() const{
    return this->m_goalWidth;
}

double Field::goalDepth() const{
    return this->m_goalDepth;
}