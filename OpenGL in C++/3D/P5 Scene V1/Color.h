#ifndef ColorH
#define ColorH

class Color
 {
 private:
  // Atributos
  float r;  // RGB
  float g;
  float b;

 public:
  // Constructoras y destructor
  Color(int r, int g, int b);  // Constructora: valores 0..255 (y pasarlos a 0..1)
  Color(float r, float g, float b);  // Constructora: valores 0..1
  // M�todos p�blicos
  float getR();  // Getters
  float getG();
  float getB();
  void setR(float c);  // Setters
  void setG(float c);
  void setB(float c);
 };

#endif