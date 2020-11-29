#ifndef FIELD_H
#define FIELD_H

class Field{
    private:
        double m_fieldLength;                       
        double m_fieldWidth;                        

        double m_goalWidth;                    
        double m_goalDepth;                    

    public:
        Field(double filedLength, double fieldWidth, double goalWidth, double goalDepth);

        double fieldLength() const;
        double fieldWidth() const;
        double goalWidth() const;
        double goalDepth() const;
};

#endif 