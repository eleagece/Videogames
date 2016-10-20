#ifndef VNormalH
#define VNormalH

class VNormal
 {
 private:
  // Atributos
  int _v;  // �ndice del v�rtice que identifica un�vocamente un v�rtice de la malla
  int _n;  // �ndice de la normal que identifica un�vocamente una cara de la malla

 public:
  // Constructoras y destructora
  VNormal(int v,int n) {_v=v;_n=n;}
  // M�todos p�blicos
  double getV() {return _v;}
  double getN() {return _n;}
  void setV(int v) {_v=v;}
  void setN(int n) {_n=n;}
 };

#endif
