#ifndef VNormalH
#define VNormalH

class VNormal
 {
 private:
  // Atributos
  int _v;  // Índice del vértice que identifica unívocamente un vértice de la malla
  int _n;  // Índice de la normal que identifica unívocamente una cara de la malla

 public:
  // Constructores y destructor
  VNormal(int v,int n) {_v=v;_n=n;}
  // Getters y setters
  double getV() {return _v;}
  double getN() {return _n;}
  void setV(int v) {_v=v;}
  void setN(int n) {_n=n;}
 };

#endif