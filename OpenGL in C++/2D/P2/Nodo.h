#ifndef NodoH
#define NodoH

template <class T> class Nodo
 {
 private:
  T* inf;  // La información es genérica
  Nodo* sig;  // Los nodos no, son de tipo nodo
  Nodo* ant;
 public:
  Nodo(T* t, Nodo<T>* sig1, Nodo<T>* ant1);
  ~Nodo();
  Nodo<T>* getSig();
  Nodo<T>* getAnt();
  void setSig(Nodo<T>* n);
  void setAnt(Nodo<T>* n);
  void setInf(T* t);
  T* getInf();
 };

template <class T> Nodo<T>::Nodo(T* t, Nodo<T>* sig1, Nodo<T>* ant1)
 {
 inf= t;
 sig=sig1;
 ant=ant1;
 }

template <class T> Nodo<T>::~Nodo()
 {
 delete inf;
 }

template <class T> Nodo<T>* Nodo<T>::getSig()
 {
 return sig;
 }

template <class T> Nodo<T>* Nodo<T>::getAnt()
 {
 return ant;
 }

template <class T> T* Nodo<T>::getInf()
 {
 return inf;
 }

template <class T> void Nodo<T>::setSig(Nodo<T>* n)
 {
 sig=n;
 }

template <class T> void Nodo<T>::setAnt(Nodo<T>* n)
 {
 ant=n;
 }

template <class T> void Nodo<T>::setInf(T* t)
 {
 inf=t;
 }

#endif
