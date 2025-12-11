#include <iostream>
#include <vector>
#include <string>
using namespace std;



// Missing this class
class Color {
private:
  float r,g,b;
public:
  void print();
};
class Painter {
private:
  int type;
public:
  virtual void  print() const;
};

class Brush : public Painter {
public:
  void print() const final;
};
class BallPen : public Painter {
public:
  void print() const final;
};

class Shape {
private:
  static int current_id;
  int id;
public:
  struct Cordinate {
    float x, y;
  };
protected:
  vector<Cordinate> points;
  Color color;
  Painter painter;
public:
  Shape();
  Shape(vector<float> pos);
  Shape(const Shape& other);

  int  get_id() const;

  virtual bool equal(Shape* shape) const = 0;
  virtual void  print() const;      // this function must handle color, and brush to avoid overllap code for derived class
  virtual string name() const;
  virtual Shape* clone() const;
};


class Line : public Shape {
public:
  Line();
  Line(const Cordinate c1, const Cordinate c2,const Color* col,const Painter* pai);
  Line(const  Line& other);

  void print() const final;
  string name() const final;
  Shape* clone() const final;
};

class Rectangle : public Shape {
public:
  Rectangle();
  Rectangle(const Cordinate c1, const Cordinate c2,const Color* col,const Painter* pai);
  Rectangle(const Rectangle& other);

  bool equal(Shape* shape) const final {
    Rectangle* other = dynamic_cast<Rectangle*>(shape);
    if (other) {
      float h1 = this->points[0].y - this->points[1].y;
      float h2 = other->points[0].y - other->points[1].y;
      float w1 = this->points[1].x - this->points[0].x;
      float  w2 = other->points[1].x - other->points[0].x;

      return  h1 == h2 && w1 == w2;
    }
    return  false;
  }
  void  print() const final;
  string name() const final;
  Shape* clone() const final;
};
class Circle : public Shape {
private:
  float radius;
public:
  Circle();
  Circle(const Cordinate c1, const float r,const Color* col,const Painter* pai);
  Circle(const Circle& other);

  void print() const final;
  string name() const final;
  Shape* clone() const final;
};

class Image {
private:
  vector<Shape*> shapes;
  Shape* create_shape(const Shape* shape) const {
    return shape->clone();
  }
public:

  void  add_shape(const Shape* shape);
  void remove_shape();

  void  print() const;
};